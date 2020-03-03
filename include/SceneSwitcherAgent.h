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

#ifndef _SCENE_SWITCHER_AGENT_H_
#define _SCENE_SWITCHER_AGENT_H_

#include <lock.h>
#include "MicoleAgent.h"
#include "micolelib.h"
#include <Vrml.h>
#include <Group.h>
#include <Display.h>
using namespace Reachin;

/*




#include <Display.h>
#include <Scene.h>
#include <Node.h>
#include <Field.h>


*/

#include <Switch.h>

class SceneSwitcherAgent : public MicoleAgent
{
public:
	SceneSwitcherAgent(string dataroot);
	~SceneSwitcherAgent(void);

	void switchScene(const char *fname);
	void handleSceneSwitch( MicoleBus *app, int argc, const char **argv );
private:
	bool initialized;
	//AutoRef<Group> g;
	//Group *g;
	Switch *swt;
	//DEFMap *sceneMap;
	//DEFMap *s1;
	//DEFMap *s2;
	//map<string,string> microworlds;
	map<Group *, DEFMap *> microworlds;
	map<string,int> midx;
};

#endif