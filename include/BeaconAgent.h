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

#ifndef BEACONAGENT_H
#define BEACONAGENT_H
#include "micolelib.h"

//#include <winsock2.h> // great!

#include <Shape.h>
#include <Sphere.h>
#include <Cone.h>
#include <Appearance.h>
#include <FrictionalSurface.h>
#include <Child.h>
#include <Transform.h>
#include <Display.h>

#include <MicoleAgent.h>
#include <ReachinMicoleApplication.h>
//using namespace Reachin;

#include "FF3DForceModel.h"


class BeaconAgent : public MicoleAgent, public Child
{
	public:
		BeaconAgent();
		virtual ~BeaconAgent();

		/**
		 * you can specify a force model
		 * @param fm FF3DForceModel who constraint FF3DDevice
		 * @warning ForceModel is deleted automatically if replaced (no clone of object)
		 * @note if you use IvyBus, you don't need to use this function
		 */
		void setForceModel(FF3DForceModel * fm) 
		{
			
			if (_fm=fm) //if it is the same force model
			{
				return;
			} 
			if (_fm) //if _fm is not null
			{
				delete(_fm);
			}
			_fm = fm;
			
		}

	struct BeaconCollider : public Collider
	{
		BeaconAgent *_parent;

		virtual void collide( CollisionState *cs)
		{ 
			Child::Collider::collide( cs ); 
			if (_parent->_fm)
				cs->addAbsoluteLocalFM( _parent->_fm );
		}
	};

	protected:
		virtual void handlePointForceModel ( MicoleBus *app, int argc, const char **argv );
		virtual void handleNoForceModel ( MicoleBus *app, int argc, const char **argv );

	private:
		FF3DForceModel * _fm; /**< current force model */
		Transform * _transform; /**<  */

		void pointReached()
		{
			delete _fm;
		}

	
	struct PointForceModel : FF3DForceModel
	{
		
		mgFloat _stiffness, _d; 
		Vec3f _stick_point;
		BeaconAgent *_beacon;
		bool released;
		int count;

		PointForceModel::PointForceModel(BeaconAgent *beac, const Vec3f &pPoint, const mgFloat &stiffness=10, const mgFloat &d = 0.85 )
			: _stick_point(pPoint), _stiffness(stiffness), _d(d), _beacon(beac)
		{
			released=false;
			count=0;
		}
		
		PointForceModel::PointForceModel(const PointForceModel &fm)
			: _stick_point(fm._stick_point),_stiffness(fm._stiffness), _beacon(fm._beacon)
		{
		}

		virtual FF3DForceModel * clone() { return new PointForceModel(*this); }

		virtual Vec3f evaluate( const Vec3f &pos, const mgFloat &w ) 
		{
		
			Vec3f diff = _stick_point - pos; 
			Vec3f x = diff;
			x.normalizeSafe();

			mgFloat dist = diff.length();

			if(released)
			{
				if(count > 1000)
				{
					_beacon->setForceModel(NULL);
					return Vec3f(0,0,0);
				}
				else
				{
					count++;
					_stiffness/=2;
					return (x *_stiffness);
				}
			}	

			//Vec3f res = _stiffness * diff;
			if (diff.length()<_d) {
				//_beacon->setForceModel(NULL);
				released=true;
				//return x;
				return (x *_stiffness);
			}
			return (x *_stiffness);
		
		}
};



};

#endif
