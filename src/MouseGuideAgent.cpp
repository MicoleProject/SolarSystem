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
#include <Shape.h>
#include <Appearance.h>
#include <Material.h>
#include <Box.h>
#include "MouseGuideAgent.h"
#include "ReachinMicoleApplication.h"
#include <MicoleStringStream.h>

MouseGuideAgent::MouseGuideAgent()
:MicoleAgent("MouseGuideAgent","InputAgent")
{
	follow=false;
	bindMessage( "^IN MSE : pos=\\((.*)\\); evt=\\((.*)\\);$", BUS_CALLBACK_OF(MouseGuideAgent, handleMousePress));
	bindMessage( "^IN MSE : pos=\\((.*), (.*)\\);$", BUS_CALLBACK_OF(MouseGuideAgent, handleMouseMove));	
	bindMessage( "^IN FOO : pos=there;$", BUS_CALLBACK_OF(MouseGuideAgent, handleReLocation));	

	xform1 = new Reachin::Transform();
	xform1->translation->set( Vec3f(0.05, 0.0, 0.005) );
	Shape *shape1 = new Shape();
	Shape *shape2 = new Shape();
	Appearance *app1 = new Appearance();
	Material *mat1 = new Material();
	Box *boxX = new Box();
	Box *boxY = new Box();
	boxX->size->set( Vec3f(0.005, 0.001, 0.001) );
	boxY->size->set( Vec3f(0.001, 0.005, 0.001) );
	mat1->diffuse_color->set( RGB(1.0, 0.0, 0.0) );
	app1->material->set( mat1 );
	shape1->appearance->set( app1 );
	shape2->appearance->set( app1 );
	shape1->geometry->set( boxX );
	shape2->geometry->set( boxY );
	xform1->children->add( shape1 );
	xform1->children->add( shape2 );
	ReachinMicoleApplication::getInstance()->getDisplay()->children->add( xform1 );

}

MouseGuideAgent::~MouseGuideAgent()
{
}

void MouseGuideAgent::handleReLocation(MicoleBus *app, int argc, const char **argv)
{
	/*
	sendMessage("handleReLocation handleReLocation");
	if(follow==false) {
		MicoleStringStream ss;
		ss << "OUT FF3D GUIDE : none;";
		sendMessage(ss.getString().c_str());
	}
	*/
}
void MouseGuideAgent::handleMouseMove(MicoleBus *app, int argc, const char **argv)
{
	/*
	if(follow) {
		MicoleStringStream ss;
		ss << "OUT FF3D GUIDE : point=("<<argv[0]<< ", 1.0);";
		sendMessage(ss.getString().c_str());
	}
	*/

	if (argc < 2)
		return;
	Vec3f position;
	try
	{
		position.x = atof(argv[0]);
		position.y = atof(argv[1]);
		position.z = atof("0.005");
		xform1->translation->set(position);
	}
	catch (...) //can append for truncated packet or bad transmission
	{
		return;
	}
	
}

void MouseGuideAgent::handleMousePress(MicoleBus *app, int argc, const char **argv)
{
	if(argc!=2)
		return; //fixed number or parameters.
	onMouse(argv[0],argv[1]);
}

void MouseGuideAgent::onMouse(string coords, string evt)
{
	if(evt.compare("BT1_PRESSED")==0)
	{
		follow=!follow;
		MicoleStringStream ss;
		ss << "OUT BCON : point=("<<coords<< ", 0.020);";
		sendMessage(ss.getString().c_str());
	}
}

