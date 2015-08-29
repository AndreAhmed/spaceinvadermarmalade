#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"

#include "Invader.h"
#include "Ship.h"
#include "Bullet.h"
#include "Barrier.h"
#include "Saucer.h"
#include "resources.h"
#include  <list>
#include  <map>


/************************************************************************/
/*Lots of stuff can added for better code quality
use smart pointers, better scene handling, a common sprite class,..etc
*/
/************************************************************************/

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace std;

#define FRAME_TIME  (30.0f / 1000.0f)
#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

// invaders
enum direction_t { left, right, stationary };

struct Invaders_t
{
	vector<Invader*> *invaders;
	direction_t  direction;
	float speed;
	int killed;
	bool alive;
};

struct Invaders_t g_Invaders;

void Init_Invaders(Resources *resources)
{
	g_Invaders.direction = right;
	g_Invaders.speed = 0.01f;
	g_Invaders.killed = 0;

	g_Invaders.invaders = new vector<Invader*>();
	int patterns[5] = { 1, 2, 2, 3, 3 };

	int counter = 0;
	int x_spacing = 0;
	int y_spacing = 50;
	for (int j = 0; j < 5; j++)
	{
		x_spacing = 15;
		for (int i = 0; i < 8; i++)
		{
			Invader *invader = new Invader();
			if (patterns[counter] == 1)
			{
				invader->Init(TOP_ALIEN, resources->getAlienImageTop());
				invader->Points = 100;
			}
			else if (patterns[counter] == 2)
			{
				invader->Init(MIDDLE_ALIEN, resources->getAlienImageMid());
				invader->Points = 200;
			}
			else if (patterns[counter] == 3)
			{
				invader->Init(BOTTOM_ALIEN, resources->getAlienImageBot());
				invader->Points = 300;
			}

			invader->Alive = true;
			invader->AlienSprite->m_X = x_spacing;
			invader->AlienSprite->m_Y = y_spacing;
			g_Invaders.invaders->push_back(invader);
			x_spacing += 40;
		}
		y_spacing += 30;
		counter++;
	}
}

void Move_Invaders(float delta)
{

	switch (g_Invaders.direction)
	{
	case right:

		for (vector<Invader*>::iterator it = g_Invaders.invaders->begin(); it != g_Invaders.invaders->end(); it++)
		{
			if ((*it)->AlienSprite->m_X > Iw2DGetSurfaceWidth() - 15)
			{
				g_Invaders.direction = left;

				for (vector<Invader*>::iterator it = g_Invaders.invaders->begin(); it != g_Invaders.invaders->end(); it++)
				{
					(*it)->AlienSprite->m_Y += 0.2f * delta;
				}
			}

			(*it)->AlienSprite->m_X += g_Invaders.speed * delta;
			(*it)->Update(delta);
			(*it)->Render();
		}
		break;

	case left:

		for (vector<Invader*>::iterator it = g_Invaders.invaders->begin(); it != g_Invaders.invaders->end(); it++)
		{
			if ((*it)->AlienSprite->m_X < 15)
			{
				g_Invaders.direction = right;

				for (vector<Invader*>::iterator it = g_Invaders.invaders->begin(); it != g_Invaders.invaders->end(); it++)
				{
					(*it)->AlienSprite->m_Y += 0.2f * delta;
				}
			}

			(*it)->AlienSprite->m_X -= g_Invaders.speed * delta;
			(*it)->Update(delta);
			(*it)->Render();
		}
		break;
	}

}
bool CheckCollision(float left, float top, float SpriteX, float SpriteWidth, float SpriteY, float SpriteHeight)
{
	return !((left > SpriteX + SpriteWidth) ||
		(top > SpriteY + SpriteHeight) ||
		(SpriteX > left + SpriteWidth) ||
		(SpriteY > top + SpriteHeight));

}


cRect Intersection(const cRect& boundsA, const cRect& boundsB)
{
	int x1 = Maximum(boundsA.x, boundsB.x);
	int y1 = Maximum(boundsA.y, boundsB.y);
	int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
	int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

	int width = x2 - x1;
	int height = y2 - y1;

	if (width > 0 && height > 0)
	{
		cRect intersect;
		intersect.x = x1;
		intersect.y = y1;
		intersect.w = width;
		intersect.h = height;
		return intersect;
	}
	else
	{
		cRect intersect;
		intersect.x = 0;
		intersect.y = 0;
		intersect.w = 0;
		intersect.h = 0;
		return intersect;
	}
}


bool IntersectsWith(cRect rectA, cRect rectB)
{
	if (rectB.x < rectA.x + rectA.w && rectA.x < rectB.x + rectB.w && rectB.y < rectA.y + rectA.h)
		return rectA.y < rectB.y + rectB.h;
	else
		return false;
}

void DrawScore()
{
	//// Set the current font
	//Iw2DSetFont(Font);

	//// Reset the visual transform
	//Iw2DSetTransformMatrix(CIwMat2D::g_Identity);

	//// Set the texts colour to black
	//Iw2DSetColour(0xff000000);

	//// Draw the score label
	//Iw2DDrawString("Score:", CIwSVec2(10, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);

	//// Convert the score number to text
	//char str[32];
	//snprintf(str, 32, "%d", Score);

	//// Draw the score number
	//Iw2DDrawString(str, CIwSVec2(100, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
}


void CheckBulletsSaucerCollision(Saucer *saucer, Ship *ship)
{
	bool isCollision = false;
	for (list<Bullet*>::iterator it = ship->Bullets->begin(); it != ship->Bullets->end();)
	{
		float left = (*it)->Position.x - 5;
		float top = (*it)->Position.y - 13;

		if (CheckCollision(left, top, (saucer)->Position.x,
			22
			, (saucer)->Position.y - (saucer)->mSaucerImage->GetHeight()
			, 30))
		{
			Bullet *bullet = *it;
			it = ship->Bullets->erase(it);
			delete bullet;
			ship->Canfire = true;
			isCollision = true;
			saucer->mAlive = false;

			if (saucer->mDirection == LEFT)
			{
				saucer->Position.x = -1;
				saucer->mDirection = RIGHT;
			}

			if (saucer->mDirection == RIGHT)
			{
				saucer->Position.x = Iw2DGetSurfaceWidth() + 10;
				saucer->mDirection = LEFT;
			}
		}
		else
		{
			it++;
		}
	}

}
void CheckBulletsBarriersCollision(Ship * ship, vector<Barrier*> *barriers, Resources *resources)
{
	bool isCollision = false;
	for (vector<Barrier*>::iterator itBarrier = barriers->begin(); itBarrier != barriers->end();)
	{
		for (list<Bullet*>::iterator it = ship->Bullets->begin(); it != ship->Bullets->end();)
		{
			float left = (*it)->Position.x - 5;
			float top = (*it)->Position.y - 13;

			if (CheckCollision(left, top, (*itBarrier)->Position.x,
				22
				, (*itBarrier)->Position.y - (*itBarrier)->mBarrierImage->GetHeight()
				, 30))
			{

				(*itBarrier)->numHits++;

				Bullet *bullet = *it;
				it = ship->Bullets->erase(it);
				delete bullet;
				ship->Canfire = true;
				isCollision = true;
			}
			else
			{
				it++;
			}
		}


		if ((*itBarrier)->numHits == 4)
		{
			Barrier *barrier = *itBarrier;
			itBarrier = barriers->erase(itBarrier);
			delete barrier;
		}
		else
		{
			itBarrier++;
		}
	}
}

void CheckBulletsInvadersCollision(Ship *ship)
{
	for (vector<Invader*>::iterator invIter = g_Invaders.invaders->begin(); invIter != g_Invaders.invaders->end();)
	{
		if ((*invIter)->Alive)
		{
			bool isBulletsInvaderCollided = false;

			for (list<Bullet*>::iterator it = ship->Bullets->begin(); it != ship->Bullets->end();)
			{

				float left = (*it)->Position.x;
				float top = (*it)->Position.y;

				if (CheckCollision(left, top, (*invIter)->AlienSprite->m_X, (*invIter)->AlienAtals->GetFrameWidth()-20
					, (*invIter)->AlienSprite->m_Y, (*invIter)->AlienAtals->GetFrameHeight()))
				{
					isBulletsInvaderCollided = true;
					Bullet *bullet = *it;
					it = ship->Bullets->erase(it);
					delete bullet;

					ship->Canfire = true;
				}
				else
				{
					it++;
				}

			}
			if (isBulletsInvaderCollided)
			{
				Invader *inv = *invIter;
				g_Invaders.invaders->erase(invIter);
				delete inv;
				g_Invaders.killed++;
				g_Invaders.alive = false;
			}
			else
			{
				invIter++;
			}
		}
	}
}


void Init_Barriers(vector<Barrier*> *barriers, Resources *gameResources)
{
	int widthOffset = 0;
	for (int i = 0; i < 3; i++)
	{
		Barrier *barrier = new Barrier();
		barrier->Init(gameResources->getBarrierImage(), gameResources->getButtonDamgeImageFirst(), gameResources->getButtonDamgeImageSecond(),
			gameResources->getButtonDamgeImageThird(), gameResources->getButtonDamgeImageFourth());
		barrier->Position.x = 50 + widthOffset;
		barrier->Position.y = 540;
		barrier->BoundingRect.x = barrier->Position.x - 46 / 2;
		barrier->BoundingRect.y = barrier->Position.y - 36 / 2;
		widthOffset += 100;

		barriers->push_back(barrier);
	}

}

void Render_Barriers(vector<Barrier*> *barriers)
{
	for (vector<Barrier*>::iterator it = barriers->begin(); it != barriers->end(); it++)
	{
		(*it)->Render();
#if 0
		Iw2DSetColour(0xff00ff00);
		Iw2DDrawRect(CIwFVec2(-(*it)->mBarrierImage->GetWidth() / 2, -(*it)->mBarrierImage->GetHeight() / 2),
			CIwFVec2((*it)->mBarrierImage->GetWidth(), (*it)->mBarrierImage->GetHeight()));
#endif
	}
}

bool CheckCollision(int barrierX, int barrierY, Ship *ship, CIwTexture *tex, uint8*pixels, Resources *gameResources)
{
	bool isCollision = false;

	cRect barrierRect;
	barrierRect.x = barrierX;
	barrierRect.y = barrierY;
	barrierRect.w = 51;
	barrierRect.h = 35;
	CIwFMat2D t;
	t.SetIdentity();
	Iw2DSetTransformMatrix(t);
	Iw2DSetColour(0xDDDDDDDD); // Set red
	Iw2DDrawRect(CIwFVec2(barrierRect.x, barrierRect.y), CIwFVec2(barrierRect.w, barrierRect.h)); // Draw red outline

	for (list<Bullet*>::iterator it = ship->Bullets->begin(); it != ship->Bullets->end();)
	{

		bool didHit = false;
		// if there is intersection
		if (IntersectsWith((*it)->BoundingRect, barrierRect))
		{
			std::map<int, int> hits;

			// subtract (*it) bullet position from barrrier's rect 
			int normX = (*it)->Position.x - barrierRect.x;
			int normY = (*it)->Position.y - barrierRect.y;

			// barrier image pixels 
			uint32* ptr = (uint32*)pixels;

			for (int y = 0; y < 35; y++)
			{
				for (int x = 0; x < 51; x++)
				{
					int pixelOffset = y * 51 + x;
					unsigned int color = ptr[pixelOffset];
					if (color != 0xFF000000)
					{
						// if this pixel is in bullet's rect
						if (CheckCollision(x, y, normX, 3, normY, 13))
						{
							didHit = true;

							hits[x] = y;
						}
					}
				}
			 }

			for (std::map<int, int>::iterator it = hits.begin(); it != hits.end(); it++)
			{
				//	blast a circle around that bullet hit position
				int radius = 4;
				for (int yy = -radius; yy <= radius; yy++)
				{
					for (int xx = -radius; xx <= radius; xx++)
					{
						if (xx*xx + yy*yy <= radius*radius)
						{
							int hitX = it->first;
							int hitY = it->second;

							int j = xx  + hitX;
							int i = yy  + hitY;

							if ( (j >= 0 && j < 51) && (i >= 0 && i < 35))
							{
								int pixelOffset = i*51 + j;
								ptr[pixelOffset] = 0xff000000;
							}
						}
					}
				}
			}
		}

		if (didHit)
		{
			//delete the bullet
			Bullet *bullet = *it;
			it = ship->Bullets->erase(it);
			delete bullet;
			ship->Canfire = true;
			isCollision = true;
		}
		else
		{
			it++;
		}
 	}

	tex->ChangeTexels(pixels);
	tex->Upload();
	return isCollision;
}

void DrawImage(CIwTexture* tex, float X, float Y, float W, float H, float Angle = 0.0f)
{
	CIwMaterial* material = IW_GX_ALLOC_MATERIAL();
	material->SetTexture(tex);
	material->SetFiltering(true);
	material->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	IwGxSetMaterial(material);

	CIwFVec2* vrt_stream = IW_GX_ALLOC(CIwFVec2, 4);
	vrt_stream[0] = CIwFVec2(X, Y);
	vrt_stream[1] = CIwFVec2(X, Y + H);
	vrt_stream[2] = CIwFVec2(X + W, Y + H);
	vrt_stream[3] = CIwFVec2(X + W, Y);

	if (Angle != 0.0f)
	{
		CIwFMat2D mat;
		mat.SetRot(Angle * 0.017453292f, CIwFVec2(X + W * 0.5f, Y + H * 0.5f));
		for (uint32 j = 0; j < 4; ++j) vrt_stream[j] = mat.TransformVec(vrt_stream[j]);
	}

	CIwFVec2* uv_stream = IW_GX_ALLOC(CIwFVec2, 4);
	uv_stream[0] = CIwFVec2(0.0f, 0.0f);
	uv_stream[1] = CIwFVec2(0.0f, 1.0f);
	uv_stream[2] = CIwFVec2(1.0f, 1.0f);
	uv_stream[3] = CIwFVec2(1.0f, 0.0f);

	IwGxSetVertStreamScreenSpace(vrt_stream, 4);
	IwGxSetUVStream(uv_stream);
	IwGxSetColStream(NULL);

	IwGxDrawPrims(IW_GX_QUAD_LIST, NULL, 4);
}

// Main entry point for the application
int main()
{

	Iw2DInit();

	g_Input.Init();

	Resources * gameResources = new Resources();

	// barriers
	vector<Barrier*> *barriers = new  vector<Barrier*>();
	Init_Barriers(barriers, gameResources);

	// Ship
	Ship *ship = new Ship();
	ship->Init();
	ship->SetShipBulletImage(gameResources->getShipBullet());

	// invader
	Init_Invaders(gameResources);

	// saucer 
	Saucer saucer;
	saucer.Init(gameResources->getSaucerImage(), RIGHT);

	Iw2DSetFont(gameResources->getFont());

	CIwImage* image = new CIwImage;
	image->LoadFromFile("textures/barrier.png");
	CIwTexture*barrier_1 = new CIwTexture();

	barrier_1->CopyFromImage(image);
	uint8 * pixels_barrier1 = barrier_1->GetTexels();
	uint32 pitch_barrier1 = barrier_1->GetPitch();
	barrier_1->SetFormatHW(CIwImage::ABGR_8888);
	barrier_1->SetMipMapping(false);
	barrier_1->SetModifiable(true);
	barrier_1->Upload();

	CIwTexture*barrier_2 = new CIwTexture();
	barrier_2->CopyFromImage(image);
	uint8 * pixels_barrier2 = barrier_2->GetTexels();
	uint32 pitch_barrier2 = barrier_2->GetPitch();
	barrier_2->SetFormatHW(CIwImage::ABGR_8888);
	barrier_2->SetMipMapping(false);
	barrier_2->SetModifiable(true);
	barrier_2->Upload();


	CIwTexture*barrier_3 = new CIwTexture();
	barrier_3->CopyFromImage(image);
	uint8 * pixels_barrier3 = barrier_3->GetTexels();
	uint32 pitch_barrier3 = barrier_3->GetPitch();
	barrier_3->SetFormatHW(CIwImage::ABGR_8888);
	barrier_3->SetMipMapping(false);
	barrier_3->SetModifiable(true);
	barrier_3->Upload();

	int score = 0;


	uint32 timer = (uint32)s3eTimerGetMs();
	// Loop forever, until the user or the OS performs some action to quit the app
	while (!s3eDeviceCheckQuitRequest())
	{
		// Calculate the amount of time that's passed since last frame
		int delta = uint32(s3eTimerGetMs()) - timer;
		timer += delta;

		g_Input.Update();

		Iw2DSurfaceClear(0x00000000);

		Move_Invaders(delta);


		CheckCollision(50, 490, ship, barrier_1, pixels_barrier1, gameResources);
		CheckCollision(150, 490, ship, barrier_2, pixels_barrier2, gameResources);
		CheckCollision(250, 490, ship, barrier_3, pixels_barrier3, gameResources);
		DrawImage(barrier_1, 50, 490, image->GetWidth(), image->GetHeight());
		DrawImage(barrier_2, 150, 490, image->GetWidth(), image->GetHeight());
		DrawImage(barrier_3, 250, 490, image->GetWidth(), image->GetHeight());


		ship->Update(delta);
		ship->Render();

		if (ship->NumFire == 9)
		{
			ship->NumFire = 0;
			saucer.mAlive = true;
		}
		saucer.Update(delta);
		saucer.Render();

		if (g_Invaders.killed == 5)
			g_Invaders.speed = 0.02f;
		if (g_Invaders.killed == 25)
			g_Invaders.speed = 0.05f;

		if (g_Invaders.killed == 35)
			g_Invaders.speed = 0.09f;

		if (g_Invaders.killed == 39)
			g_Invaders.speed = 0.10f;

		CheckBulletsSaucerCollision(&saucer, ship);
		CheckBulletsInvadersCollision(ship);
		//Iw2DDrawString("Score = ", CIwFVec2(10, 10), CIwFVec2(50, 50), IW_2D_FONT_ALIGN_CENTRE, IW_2D_FONT_ALIGN_CENTRE);
		//Draws Surface to screen
		Iw2DSurfaceShow();

		// Sleep for 0ms to allow the OS to process events etc.
		s3eDeviceYield(0);
	}

	g_Input.Release();

	delete image;
	delete barrier_1;
	delete barrier_2;
	delete barrier_3;

	for (std::vector<Barrier*>::iterator it = barriers->begin(); it != barriers->end(); ++it)
		delete *it;

	delete barriers;


	for (std::vector<Invader*>::iterator it = g_Invaders.invaders->begin(); it != g_Invaders.invaders->end(); ++it)
		delete *it;
	delete g_Invaders.invaders;

	delete gameResources;
	delete ship;

	Iw2DTerminate();

	// Return
	return 0;
}
