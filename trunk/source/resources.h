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

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
	CIw2DImage*     ShipBullet;
	CIw2DImage*     SaucerImage;
	CIw2DImage*		AlienImageTop;
	CIw2DImage*     AlienImageMid;
	CIw2DImage*     AlienImageBot;
 	CIw2DImage*     ButtomDamageImage_First;
	CIw2DImage*     ButtomDamageImage_Second;
	CIw2DImage*     ButtomDamageImage_Third;
	CIw2DImage*     ButtomDamageImage_Fourth;
	CIw2DImage*		BarrierImage;
	CIw2DImage*		DamageImage;

	CIw2DFont*      Font;
public:
	CIw2DImage*     getDamageImage()					{ return DamageImage;				}
	CIw2DImage*     getSaucerImage()					{ return SaucerImage;			    }
	CIw2DImage*     getShipBullet()						{ return ShipBullet;				}
	CIw2DImage*		getAlienImageTop()					{ return AlienImageTop;				}
	CIw2DImage*		getAlienImageMid()					{ return AlienImageMid;				}
	CIw2DImage*		getAlienImageBot()					{ return AlienImageBot;		        }
	CIw2DImage*		getBarrierImage()					{ return BarrierImage;			    }
	CIw2DImage*     getButtonDamgeImageFirst()			{ return ButtomDamageImage_First;   }
	CIw2DImage*     getButtonDamgeImageSecond()			{ return ButtomDamageImage_Second;  }
	CIw2DImage*     getButtonDamgeImageThird()			{ return ButtomDamageImage_Third;   }
	CIw2DImage*     getButtonDamgeImageFourth()			{ return ButtomDamageImage_Fourth;  }
	CIw2DFont*      getFont()						    { return Font;						}
	
public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


