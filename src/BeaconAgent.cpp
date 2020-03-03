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

#include "stdafx.h"
//#include "define.h"
#include <BeaconAgent.h>


BeaconAgent::BeaconAgent()
: MicoleAgent("BeaconAgent","Output"), Child( new BeaconCollider()),  _fm(NULL), _transform(new Transform())
{
	
	((BeaconCollider *)this->collider.get())->_parent = this;
	Display * dis = ReachinMicoleApplication::getInstance()->getDisplay();
	_transform->children->add(this);
	if(dis!=NULL)
		dis->children->push_back( _transform );  

	bindMessage( "^OUT BCON : point=\\((.*), (.*), (.*)\\);$", 
		BUS_CALLBACK_OF(BeaconAgent, handlePointForceModel ));
	bindMessage( "^OUT BCON : none;$", 
		BUS_CALLBACK_OF(BeaconAgent, handleNoForceModel ));

}

BeaconAgent::~BeaconAgent()
{
	delete _fm;
//	delete _transform;
}

void BeaconAgent::handlePointForceModel ( MicoleBus *app, int argc, const char **argv )
{
	if (argc < 3)
		return;
	Vec3f position;
	try
	{
		position.x = atof(argv[0]);
		position.y = atof(argv[1]);
		position.z = atof(argv[2]);
	}
	catch (...) //can append for truncated packet or bad transmission
	{
		return;
	}

	_transform->translation->set(Vec3f(0,0,0));
	_transform->rotation->set( Rotation( Vec3f(0, 0, 0), 0 ) );

	setForceModel(new PointForceModel(this,position,1,0.005));
}

void BeaconAgent::handleNoForceModel ( MicoleBus *app, int argc, const char **argv ) 
{
	setForceModel(NULL);
}
