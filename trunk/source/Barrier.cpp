#include "Barrier.h"

void Barrier::Init(CIw2DImage *Barrierimage, CIw2DImage *Barrierimage_first, CIw2DImage *Barrierimage_second
	, CIw2DImage *Barrierimage_third, CIw2DImage *Barrierimage_fourth)
{
	Position.x = 0;
	Position.y = 0;
	Visible = true;
	Angle = 0;
	Scale = 1;
	numHits = 0;
	mBarrierImage = Barrierimage;
	mButtonDamgeImageFirst = Barrierimage_first;
	mButtonDamgeImageSecond = Barrierimage_second;
	mButtonDamgeImageThird = Barrierimage_third;
	mButtonDamgeImageFourth = Barrierimage_fourth;
	BoundingRect.x = 0;
	BoundingRect.y =0;
	BoundingRect.w = (float)mBarrierImage->GetWidth();
	BoundingRect.h = (float)mBarrierImage->GetHeight();

}

void Barrier::Update()
{

}

Barrier::Barrier()
{

}

Barrier::~Barrier()
{

}

void Barrier::Render()
{
	 
	if (mBarrierImage)
	{
		CIwFMat2D Transform;
		// Build transform
		Transform.SetIdentity();
		Transform.SetRot(0);
		Transform.ScaleRot(1);
		Transform.SetTrans(Position);
		Iw2DSetTransformMatrix(Transform);

		Iw2DSetColour(0xffffffff);
		if (numHits == 0)
		{
			Iw2DDrawImage(mBarrierImage,
				CIwFVec2(0, 0),
				CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight()));

		}
		else if (numHits == 11)
		{
			Iw2DDrawImage(mButtonDamgeImageFirst,
				CIwFVec2(0, 0),
				CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight()));
		}
		else if (numHits == 22)
		{
			Iw2DDrawImage(mButtonDamgeImageSecond,
				CIwFVec2(0, 0),
				CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight()));
		}

		else if (numHits == 33)
		{
			Iw2DDrawImage(mButtonDamgeImageThird,
				CIwFVec2(0, 0),
				CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight()));
		}
		else if (numHits == 44)
		{
			Iw2DDrawImage(mButtonDamgeImageFourth,
				CIwFVec2(0, 0),
				CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight()));
		}
	}
	CIwFVec2 pos = Transform.t;
	BoundingRect.x = Position.x;
	BoundingRect.y = Position.y;
	BoundingRect.w = (float)mBarrierImage->GetWidth();
	BoundingRect.h = (float)mBarrierImage->GetHeight();
	Iw2DSetColour(0xff0000ff); // Set red
	Iw2DDrawRect(CIwFVec2(pos.x, pos.y), CIwFVec2(mBarrierImage->GetWidth(), mBarrierImage->GetHeight())); // Draw red outline

}

