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

#ifndef LISTENERS_H
#define LISTENERS_H
#include <Shape.h>
#include <Appearance.h>
#include <Material.h>
#include <FrictionalSurface.h>
#include <Sphere.h>
#include <Scene.h>
#include <AutoRef.h>
#include <Group.h>
#include <Vrml.h>
#include <DeviceInfo.h>
#include <vrmlsingle.h>
#include <child.h>
#include <typedmfnode.h>
#include <typedsfnode.h>
#include <fields.h>
#include <Device.h>
#include <PositionInterpolator.h>
#include <CoordinateInterpolator.h>
#include <TimeSensor.h>
#include <Timer.h>
#include <Transform.h>

#include "simplemsgnode.h"


template <typename T> class MessageListener : public Dependent<SFBool> {
public:
	MessageListener(T m, SimpleMsgNode *mn) {
		master=m;
		messagenode=mn;
		locked=false;
	}

	virtual void update() {
		while(1) {
			cout << "outMessageHandler: notif is " << (((SFBool *)notif)->get()) << endl;
			if(((SFBool *)notif)->get() && !locked) {
				locked=true;
				cout << "COPYING MESSAGENODE TO MESSAGE\n";
				string m =(string &)messagenode->content->get();


				//messagenode->locked->set(0);
				//cout << "5" << endl;
				messagenode->ready->set(0);
				//cout << "6" << endl;

				master->sendMessage(m);
				//cout << "7" << endl;
				locked=false;
				break;
			} else if(locked) {
				//delay(500);
				//Sleep(0.1);
				break;
			} else {
				break;
			}
		}
	}

private:
	T master;
	SimpleMsgNode *messagenode;
	bool locked;
};

#endif