#include "Bullet.h"

void Bullet::Init()
{
	//BulletType = bulletType;
	//if (BulletType == SHIP_BULLET)
	//{
	//	ShipBullet = Iw2DCreateImage("textures/ship_bullet.png");
	//	if (ShipBullet == nullptr)
	//		return;

	//}
	//else if (BulletType == ENEMY_BULLET)
	//{
	//	ShipBullet = Iw2DCreateImage("textures/enemy_bullet.png");
	//	if (ShipBullet == nullptr)
	//		return;

	//}
	Position.x = 0;
	Position.y = 0;

	Visible = true;
	Angle = 0;
	Scale = 1;
	Colour = 0xffffffff;
	IsDestroyed = false;
	ShipBullet = nullptr;

}

void Bullet::Render()
{
	if (ShipBullet == nullptr)
		return;

	if (Visible)
	{
		Transform.SetIdentity();

		// Build transform
		Transform.SetRot(Angle);
		Transform.ScaleRot(Scale);
		Transform.SetTrans(prevPosition);
		Iw2DSetTransformMatrix(Transform);
		Iw2DSetColour(Colour);
		CIwFVec2 pos = Transform.t;

		// Render image
		 
		int x = -(ShipBullet->GetWidth() / 2);
		int y = -(ShipBullet->GetHeight() / 2);
		Iw2DDrawImage(ShipBullet, CIwFVec2(x, y), CIwFVec2(ShipBullet->GetWidth(), ShipBullet->GetHeight()));

		BoundingRect.x = prevPosition.x;
		BoundingRect.y = prevPosition.y;
		BoundingRect.w = (float)ShipBullet->GetWidth();
		BoundingRect.h = Position.y - prevPosition.y  + (float)ShipBullet->GetHeight();
		 


#if 1
		Iw2DSetColour(0xff0000ff); // Set red
		Iw2DDrawRect(CIwFVec2(x, y),
			CIwFVec2(ShipBullet->GetWidth(),ShipBullet->GetHeight()));
#endif 

	}
}

void Bullet::Update(float dt)
{
	Position.y -= 0.50 * dt;
 
	if (Position.y < 0)
	{
		IsDestroyed = true;
	}
	else
		IsDestroyed = false;

	prevPosition = Position;

}

Bullet::~Bullet()
{
	
}

Bullet::Bullet()
{

}
