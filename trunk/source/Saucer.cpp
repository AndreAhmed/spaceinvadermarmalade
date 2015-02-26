#include "Saucer.h"

Saucer::Saucer()
{

}

Saucer::~Saucer()
{

}

void Saucer::Init(CIw2DImage *Saucerimage, Direction direction)
{
	mDirection = direction;
	mAlive = false;
	mSaucerImage = Saucerimage;
	Position.x = 0;
	Position.y = 30;
}

void Saucer::Update(float dt)
{
	if (!mAlive)
		return;

	if (mDirection == RIGHT)
	{
		Position.x += 0.1f*dt;
		
		if (Position.x > Iw2DGetSurfaceWidth() - 10)
		{
			mDirection = LEFT;
			Position.x = Iw2DGetSurfaceWidth() + 10;
			mAlive = false;
		}
	}
	else if (mDirection == LEFT)
	{
		Position.x -= 0.1f * dt;
		if (Position.x < 0)
		{
			mAlive = false;
			mDirection = RIGHT;
		}
	}
}

void Saucer::Render()
{
	if (!mAlive)
		return;

	if (mSaucerImage)
	{
	 	// Build transform
		CIwFMat2D Transform;
		Transform.SetIdentity();
		// Build transform
		Transform.SetIdentity();
		Transform.SetRot(0);
		Transform.ScaleRot(1);
		Transform.SetTrans(Position);
		Iw2DSetTransformMatrix(Transform);

		Iw2DSetColour(0xffffffff);

		Iw2DDrawImage(mSaucerImage,
			CIwFVec2(-mSaucerImage->GetWidth() / 2, -mSaucerImage->GetHeight() / 2),
			CIwFVec2(mSaucerImage->GetWidth(), mSaucerImage->GetHeight()));
	}
}

