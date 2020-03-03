/*
 * This file is part of Space Application made in MICOLE project.
 *
 * Copyright (C) 2007 Micole partners
 *
 * Space Application is free software: you can redistribute it 
 * and/or modify it under the terms of the GNU Lesser General 
 * Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or (at your option) any 
 * later version.
 *
 * Space Application is distributed in the hope that it will be 
 * useful, * but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE.  See the GNU Lesser General Public License for more 
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Space Application.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _SWIRLSURFACE_H_
#define _SWIRLSURFACE_H_

//#include "SimpleSurface.h"
#include "ImageSurface.h"

using namespace Reachin;

class SwirlSurface : public ImageSurface //SimpleSurface 
{
protected:

	//class Contact : public SimpleSurface::Contact 
	class Contact : public SimpleSurface::Contact 
	{
	public:
		//
		// Constructor
		// initialise any state variables of the contact, possibly
		// copying from the field values of the surface.
		inline Contact( SwirlSurface *s, mgFloat pwr ) : 
		SimpleSurface::Contact( s ), direction(0), power(pwr) {}
		//	ImageSurface::Contact( s ), direction(0), power(pwr) {}
		
		//
		// Constructor
		// we require the void constructor in all sub-classes.
		inline Contact() : power(0.1) {}
			
		// 
		// we define evaluate to produce the rendering force and update
		// the proxy position.
		inline virtual void evaluate( const Vec3f &finger,
										const Vec2f &ds,
										const Vec2f &dt,
										const Vec2f &st_origin,
										Vec3f &force,
										Vec2f &proxy_movement ) 
		{
			// implement the surface forces here.
			SimpleSurface::Contact::evaluate(finger, ds, dt, st_origin, force, proxy_movement );
			//ImageSurface::Contact::evaluate(finger, ds, dt, st_origin, force, proxy_movement );
			direction+=0.03;
			if(direction > Util::two_pi ) 
				direction -= Util::two_pi;

			mgFloat ds2 = ds * ds;
			if(mgAbs(ds2) < Util::epsilon ) 
				return;
			if(mgAbs(power) > 0.6) 
				power = 0.6;
			Vec2f dir = ds * ( power / mgSqrt(ds2));

			mgFloat cosd = mgCos( direction );
			mgFloat sind = mgSin( direction );
			dir = Vec2f( cosd * dir.x - sind * dir.y, sind * dir.x + cosd * dir.y );
			force.x += dir.x;
			force.y += dir.y;
		}

		mgFloat direction;
		mgFloat power;
	};
	
public:
	auto_ptr<SFFloat> power;

	//
	// Constructor.
	// create new fields and/or specialise fields in BaseSurface here.
	inline SwirlSurface() : power(new SFFloat) 
	{
		power.get()->set(0.1);
	}

	// 
	// sub-classes should contain exactly the following in order to 
	// register their new Contact sub-classes.
	inline virtual Surface::Contact *newContact() 
	{
	  return new Contact( this, power.get()->get() );
	}
	inline virtual Surface::Contact *copyContact() 
	{
	  return copyContactT( new Contact );
	}
	

	//
	// our VRML interface.
	//
	const static Interface interface;
};


#endif
