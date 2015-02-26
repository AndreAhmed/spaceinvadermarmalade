#pragma  once
#include "Iw2D.h"
#include "IwGx.h"
#include "Input.h"
#include "Rect.h"
#include "resources.h"

class Barrier
{
public:
	Barrier();
	~Barrier();

	void Init(CIw2DImage *Barrierimage, CIw2DImage *Barrierimage_first, CIw2DImage *Barrierimage_second
		, CIw2DImage *Barrierimage_third, CIw2DImage *Barrierimage_fourth);
	void Update();
	void Render();
	CIwFVec2        Position;               // Position of the sprite
	float           Angle;                  // Rotation of sprite in radians
	float           Scale;                  // Scale of sprite
 	bool            Visible;                // Sprites visible state

	CIwFMat2D       Transform;              // Transform matrix
	CIw2DImage		*mBarrierImage;
	CIw2DImage		*mButtonDamgeImageFirst;
	CIw2DImage		*mButtonDamgeImageSecond;
	CIw2DImage		*mButtonDamgeImageThird;
	CIw2DImage		*mButtonDamgeImageFourth;
	cRect			BoundingRect;
	int				numHits;
};