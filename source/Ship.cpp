#include "Ship.h"

using namespace std;
void Ship::Init()
{
	Image = Iw2DCreateImage("textures/ship.png");
	if (Image == nullptr)
		return;

	Position.x = 120;
	Position.y = 650;

	Visible = true;
	Angle = 0;
	Scale = 1;
	Colour = 0xffffffff;
	Bullets = new std::list<Bullet*>();
	Canfire = true;
	ShipBulletImage = nullptr;
	NumFire = 0;
}

void Ship::Render()
{
	if (Visible)
	{
		// Build transform
		Transform.SetIdentity();
		Transform.SetRot(Angle);
		Transform.ScaleRot(Scale);
		Transform.SetTrans(Position);
		Iw2DSetTransformMatrix(Transform);
		Iw2DSetColour(Colour);

		// Render image
		if (Image != 0)
		{
			int x = -(Image->GetWidth() / 2);
			int y = -(Image->GetHeight() / 2);

			Iw2DDrawImage(Image, CIwFVec2(x, y), CIwFVec2(Image->GetWidth(), Image->GetHeight()));
		}
	}

	for (list<Bullet*>::iterator it = Bullets->begin(); it != Bullets->end(); it++)
	{
		(*it)->Render();
	}
}

void Ship::Update(float dt)
{
	if (g_Input.isKeyDown(s3eKeyLeft))
	{
		Position.x-=dt*0.10;
	}
	if (g_Input.isKeyDown(s3eKeyRight))
	{
		Position.x+=dt*0.10;
	}

	if (g_Input.isKeyDown(s3eKeySpace) && Canfire)
	{
 		Bullet *bullet = new Bullet();
		bullet->Init();
		bullet->SetShipBullet(ShipBulletImage);
	
		bullet->setPosition(Position.x + 2, Position.y - 10);
		Bullets->push_back(bullet);
		Canfire = false;
		NumFire++;
		 
	}

	if (Position.x > Iw2DGetSurfaceWidth() - 15)
	{
		Position.x = Iw2DGetSurfaceWidth() - 15;
	}
 
	if (Position.x < 15)
	{
		Position.x = 15;
	}

	for (list<Bullet*>::iterator it = Bullets->begin(); it != Bullets->end();)
	{ 
		(*it)->Update(dt);
		
		if ((*it)->IsDestroyed)
		{
			Canfire = true;
			delete (*it);
			it = Bullets->erase(it);
		}
		else
		{
		 	it++;
			Canfire = false;
			
		} 
		
	}

}

Ship::~Ship()
{
	for (std::list<Bullet*>::iterator it = Bullets->begin(); it != Bullets->end(); ++it)
		delete *it;
	delete Bullets;
	delete Image;
}

Ship::Ship()
{

}
