#pragma  once

#include "Iw2D.h"
#include "IwGx.h"
#include "Input.h"
#include "Bullet.h"
#include <list>

// a good place for inheriting from a common sprite
class Ship
{
public:
	Ship();
	~Ship();
public:
	void Init();
	void Update(float dt);
	void Render();
	void        setPosition(float x, float y) { Position.x = x; Position.y = y; }
	CIwFVec2    getPosition() const         { return Position; }
	void        setAngle(float angle)       { Angle = angle; }
	float       getAngle() const            { return Angle; }
	void        setScale(float scale)       { Scale = scale; }
	float       getScale() const            { return Scale; }
	void        setColour(unsigned int colour) { Colour = colour; }
	unsigned int getColour() const           { return Colour; }
	void        setVisible(bool show)       { Visible = show; }
	bool        isVisible() const           { return Visible; }
	void        SetShipBulletImage(CIw2DImage * image) { ShipBulletImage = image; }
	
	CIw2DImage *ShipBulletImage; 
	std::list<Bullet*> *Bullets;
	CIwFMat2D       Transform;              // Transform matrix
	CIw2DImage*     Image;				    // curr image 
	CIwFVec2        Position;               // Position of the sprite
	float           Angle;                  // Rotation of sprite in radians
	float           Scale;                  // Scale of sprite
	unsigned int    Colour;                 // Colour of sprite
	bool            Visible;                // Sprites visible state
	bool			Canfire;
	int				NumFire;
};