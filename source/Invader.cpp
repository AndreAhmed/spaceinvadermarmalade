#include "Invader.h"

using namespace std;
using namespace Iw2DSceneGraph;

#define FRAME_TIME  (30.0f / 1000.0f)
Invader::Invader()
{
	Points = 0;
	Alive = 0;
	Hit = false;

 
}

Invader::Invader(const Invader&other)
{		// Create EnemyTop atlas
	 
	//Bullets = new std::list<Bullet*>();
	//*Bullets = *other.Bullets;
	 //mImageAlien = other.mImageAlien;
	 //// Create EnemyTop atlas
	 //int frame_w = (int)(mImageAlien->GetWidth() / 2);
	 //int frame_h = (int)(mImageAlien->GetHeight());
	 //AlienAtals = new CAtlas(frame_w, frame_h, 2, mImageAlien);
  //  *AlienAtals = *other.AlienAtals;
	
	 //AlienSprite = new Iw2DSceneGraph::CSprite();
	 //*AlienSprite = *other.AlienSprite;
	
	 //AlienSprite->SetAtlas(AlienAtals);
	 //AlienSprite->m_W = (float)AlienAtals->GetFrameWidth();
	 //AlienSprite->m_H = (float)AlienAtals->GetFrameHeight();
	 //AlienSprite->m_AnchorX = 0.5;
	 //AlienSprite->SetAnimDuration(2);
	
}

Invader::~Invader()
{
	/*for (std::list<Bullet*>::iterator it = Bullets->begin(); it != Bullets->end(); ++it)
		delete *it;*/

	//delete Bullets;
	delete AlienAtals;
	delete AlienSprite;
}


void Invader::Init(InvaderTypes invadertype, CIw2DImage *AlienImage)
{

		//SetAlienImage(AlienImage);
		mImageAlien = AlienImage;
		// Create EnemyTop atlas
		int frame_w = (int)(mImageAlien->GetWidth() / 2);
		int frame_h = (int)(mImageAlien->GetHeight());
		AlienAtals = new CAtlas(frame_w, frame_h, 2, mImageAlien);
		AlienSprite = new CSprite();
		AlienSprite->m_X = 0;
		AlienSprite->m_Y = 0;
		AlienSprite->SetAtlas(AlienAtals);
		AlienSprite->m_W = (float)AlienAtals->GetFrameWidth();
		AlienSprite->m_H = (float)AlienAtals->GetFrameHeight();
		AlienSprite->m_AnchorX = 0.5;
		AlienSprite->SetAnimDuration(3);

		BoundingRect.x = AlienSprite->m_X - AlienAtals->GetFrameWidth()/2;
		BoundingRect.y = AlienSprite->m_Y - AlienAtals->GetFrameHeight() / 2;
		BoundingRect.w = (float)AlienAtals->GetFrameWidth();
		BoundingRect.h = (float)AlienAtals->GetFrameHeight();

		Visible = true;
	//	Bullets = new std::list<Bullet*>();
		Canfire = true;
}

void Invader::Render()
{
	if (Visible)
	{
 
		Transform.SetIdentity();
		Transform.SetRot(Angle);
		Transform.ScaleRot(Scale);
		Transform.SetTrans(Position);
		Iw2DSetTransformMatrix(Transform);
		AlienSprite->Render();
	}

	CIwFVec2 pos = Transform.t;
	BoundingRect.x = pos.x ;
	BoundingRect.y = pos.y;
	BoundingRect.w = (float)AlienAtals->GetFrameWidth();
	BoundingRect.h = (float)AlienAtals->GetFrameHeight();
	 
#if 1
	Iw2DSetColour(0xff0000ff); // Set red
	Iw2DDrawRect(CIwFVec2(BoundingRect.x, BoundingRect.y),
		CIwFVec2(BoundingRect.w, BoundingRect.h));
#endif 



	/*for (list<Bullet*>::iterator it = Bullets->begin(); it != Bullets->end(); it++)
	{
		(*it)->Render();
	}
	*/
}

void Invader::Update(float dt)
{
 
	if (AlienSprite->m_X > Iw2DGetSurfaceWidth() - 10 || AlienSprite->m_X < 2)
	{
		Hit = true;
	}
	else
	{
		Hit = false;
	}

	//cnt-=dt;
	//if (cnt < 0)
	//{
	//	cnt=500;
	//	AlienSprite->m_X += dt * 0.10f*direction;
	//}
	//else
	//{
	//	AlienSprite->Update(FRAME_TIME+0.03, 1);
	//}
	//AlienSprite->m_X += dt * 0.03f*direction;
	AlienSprite->Update(FRAME_TIME + 0.03, 1);
}
