#pragma  once
#include "Iw2D.h"
#include "IwGx.h"
#include "Input.h"
#include "Rect.h"
#include "resources.h"

enum Direction
{
	LEFT,
	RIGHT
};
class Saucer
{
public:
	Saucer();
	~Saucer();

	void Init(CIw2DImage *Saucerimage, Direction direction);
	void Update(float dt);
	void Render();
	CIwFVec2        Position;               // Position of the sprite
	float           Angle;                  // Rotation of sprite in radians
	float           Scale;                  // Scale of sprite
	bool            Visible;                // Sprites visible state
	CIwFMat2D       Transform;              // Transform matrix
	CIw2DImage		*mSaucerImage;
	cRect			BoundingRect;
	Direction		mDirection;
	bool			mAlive;
};