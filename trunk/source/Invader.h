#pragma  once
#include "Iw2D.h"
#include "IwGx.h"
#include "Input.h"
#include "Bullet.h"
#include <list>
#include "Iw2DSceneGraph.h"
#include "Rect.h"

enum InvaderTypes
{
	TOP_ALIEN,
	MIDDLE_ALIEN,
	BOTTOM_ALIEN
};
// a good place for inheriting from a common sprite
class Invader
{
public:
	Invader(const Invader&other);
	Invader();
	~Invader();
public:
	void Init(InvaderTypes invadertype, CIw2DImage *AlienImage);
	void Update(float dt);
	void Render();
	void SetAlienImage(CIw2DImage *image){ mImageAlien = image; }

	void        setVisible(bool show)       { Visible = show; }
	bool        isVisible() const           { return Visible; }
	

	Iw2DSceneGraph::CSprite			*AlienSprite;
	Iw2DSceneGraph::CAtlas			*AlienAtals;
	CIw2DImage						*mImageAlien;
	//std::list<Bullet*>				*Bullets;
	CIwFMat2D					    Transform;              // Transform matrix
	CIwFVec2						 Position;               // Position of the sprite
	float							 Angle;                  // Rotation of sprite in radians
	float							 Scale;                  // Scale of sprite
	unsigned int					 Colour;                 // Colour of sprite
	bool							 Visible;                // Sprites visible state
	 
	bool							 Canfire;
	bool							 Hit;
	int								 Points;
	int								 Alive;
	cRect							 BoundingRect;
};