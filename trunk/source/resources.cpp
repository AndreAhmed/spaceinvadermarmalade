/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
    // Load images
	ShipBullet	  = Iw2DCreateImage("textures/ship_bullet.png");
	SaucerImage   = Iw2DCreateImage("textures/saucer.png");
	AlienImageTop = Iw2DCreateImage("textures/enemy_top.png");
	AlienImageMid =  Iw2DCreateImage("textures/enemy_mid.png");
	AlienImageBot = Iw2DCreateImage("textures/enemy_bot.png");
	BarrierImage  = Iw2DCreateImage("textures/barrier.png");
	DamageImage = Iw2DCreateImage("textures/damage.png");
	ButtomDamageImage_First = Iw2DCreateImage("textures/barrier_1.png");
	ButtomDamageImage_Second = Iw2DCreateImage("textures/barrier_2.png");
	ButtomDamageImage_Third = Iw2DCreateImage("textures/barrier_3.png");
	ButtomDamageImage_Fourth = Iw2DCreateImage("textures/barrier_4.png");
	
	// Load fonts
	Font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
	delete DamageImage;
	delete BarrierImage;
	delete AlienImageTop;
	delete AlienImageMid;
	delete AlienImageBot;
	delete ShipBullet;
	delete SaucerImage;
	delete ButtomDamageImage_First;
	delete ButtomDamageImage_Second;
	delete ButtomDamageImage_Third;
	delete ButtomDamageImage_Fourth;
	delete Font;
}

// Global resources
Resources* g_pResources = 0;



