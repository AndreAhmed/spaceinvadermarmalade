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
		Transform.SetTrans(Position);
		Iw2DSetTransformMatrix(Transform);
		Iw2DSetColour(Colour);
		// Render image
		if (ShipBullet != 0)
			Iw2DDrawImage(ShipBullet, CIwFVec2(0, 0));
		
		CIwFVec2 pos = Transform.t;
		BoundingRect.x = pos.x;
		BoundingRect.y = pos.y;
		BoundingRect.w = (float)ShipBullet->GetWidth();
		BoundingRect.h = (float)ShipBullet->GetHeight() ;

#if 1
		Iw2DSetColour(0xff0000ff); // Set red
		Iw2DDrawRect(CIwFVec2(pos.x, pos.y),
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
	 

}

Bullet::~Bullet()
{
	
}

Bullet::Bullet()
{

}
