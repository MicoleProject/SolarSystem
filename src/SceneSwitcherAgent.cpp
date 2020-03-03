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
#include "SceneSwitcherAgent.h"
#include <windows.h>
#include <ReachinMicoleApplication.h>

SceneSwitcherAgent::SceneSwitcherAgent(string dataroot)
:MicoleAgent("SceneSwitcherAgent","OutputAgent")
{
/*
	microworlds["SOLARSYSTEM"]=dataroot + "vrml\\solarsystem.wrl";
	microworlds["SUN"]=dataroot + "vrml\\sun.wrl";
	microworlds["EARTH"]=dataroot + "vrml\\earth.wrl";
	microworlds["MARS"]=dataroot + "vrml\\mars.wrl";
	microworlds["MERCURY"]=dataroot + "vrml\\mencury.wrl";
	microworlds["NEPTUNUS"]=dataroot + "vrml\\neptunus.wrl";
	microworlds["PLUTO"]=dataroot + "vrml\\pluto.wrl";
	microworlds["JUPITER"]=dataroot + "vrml\\jupiter.wrl";
	microworlds["SATURN"]=dataroot + "vrml\\saturn.wrl";
	microworlds["URANUS"]=dataroot + "vrml\\uranus.wrl";
	microworlds["VENUS"]=dataroot + "vrml\\venus.wrl";
*/
	swt = new Switch();
	int count = 0;
	DEFMap *d1 = new DEFMap();
	Group *g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\solarsystem.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["SOLARSYSTEM"]=count;
	count++;
	swt->choice->push_back(g1);


	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\earth.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["EARTH"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1= VRML::createVrmlFromURL(string(dataroot + "vrml\\pluto.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["PLUTO"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\jupiter.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["JUPITER"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\sun.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["SUN"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\mars.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["MARS"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\mercury.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["MERCURY"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\neptunus.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["NEPTUNE"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\saturn.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["SATURN"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\uranus.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["URANUS"]=count;
	count++;
	swt->choice->push_back(g1);

	d1 = new DEFMap();
	g1 = VRML::createVrmlFromURL(string(dataroot + "vrml\\venus.wrl").c_str(), d1);
	microworlds[g1] = d1;
	midx["VENUS"]=count;
	swt->choice->push_back(g1);

	ReachinMicoleApplication::getInstance()->getDisplay()->children->add(swt);
	swt->which_choice->set(0);
	SFBool bol(1);
	d1=microworlds[(Group *)swt->choice->get(swt->which_choice->get())];
	bol.routeAndTouch(d1->find("SCRIPT.initializer"));
	bol.unroute(d1->find("SCRIPT.initializer"));


//	DEFMap *s1 = new DEFMap();
//	microworlds["PLUTO"]=pair<Group *, DEFMap *>(VRML::createVrmlFromURL(string(dataroot + "vrml\\pluto.wrl").c_str(),s1),s1);
//	DEFMap *s2 = new DEFMap();
//	microworlds["JUPITER"]=pair<Group *, DEFMap *>(VRML::createVrmlFromURL(string(dataroot + "vrml\\jupiter.wrl").c_str(),s2),s2);
	//DEFMap *s3 = new DEFMap();
	//microworlds["EARTH"]=pair<Group *, DEFMap *>(VRML::createVrmlFromURL(string(dataroot + "vrml\\earth.wrl").c_str(),s3),s3);
	initialized = false;
	//g=NULL;
	bindMessage( "^OUT SSWA : scene=(.*);$", BUS_CALLBACK_OF(SceneSwitcherAgent, handleSceneSwitch));
	//switchScene(startscene);
	initialized=true;
}

SceneSwitcherAgent::~SceneSwitcherAgent()
{
}

void SceneSwitcherAgent::handleSceneSwitch(MicoleBus *app, int argc, const char **argv)
{
	if(argc!=1)
		return; //fixed number or parameters.
	switchScene(argv[0]);
}

void SceneSwitcherAgent::switchScene(const char *fname)
{
	string sss=string("scene: ") + string(fname);
	sendMessage(sss.c_str());
	if(initialized)
	{
		SFBool bol=SFBool(1);
		DEFMap *m; 
		m=microworlds[(Group *)swt->choice->get(swt->which_choice->get())];
		bol.routeAndTouch(m->find("SCRIPT.finalizer"));
		bol.unroute(m->find("SCRIPT.finalizer"));

		//ReachinMicoleApplication::getInstance()->getDisplay()->children->remove(g);
		//ReachinMicoleApplication::getInstance()->getDisplay()->children->remove(g.get());
		//delete g;
		//delete sceneMap;
		
		map<string,int>::iterator i = midx.find(fname);
		if(i == midx.end())
			swt->which_choice->set(0);
		else
			swt->which_choice->set((*i).second);
		bol.set(1);
		m=microworlds[(Group *)swt->choice->get(swt->which_choice->get())];
		bol.routeAndTouch(m->find("SCRIPT.initializer"));
		bol.unroute(m->find("SCRIPT.initializer"));
	}
	
		
	//map<string,string>::iterator i=microworlds.find(fname);
	//map<string,pair<Group *, DEFMap *> >::iterator i=microworlds.find(fname);
	//string mworld;
	//if(i!=microworlds.end())
	//	mworld=(*i).second; // mworld= (*i).second;
		//g=((*i).second.first);
	//else
		//mworld = microworlds["EMPTY"]; //mworld= microworlds["EMPTY"];

	//sceneMap = new DEFMap();
	//sceneMap = (*i).second.second;
	// "C:\\rami\\micole_cvs\\micole\\solarsystem\\data\\vrml\\solarsystem.wrl"
	//g.reset(VRML::createVrmlFromURL(mworld.c_str(), sceneMap));
	//ReachinMicoleApplication::getInstance()->getDisplay()->children->add(g.get());
	//ReachinMicoleApplication::getInstance()->getDisplay()->children->add(g);
	//ReachinMicoleApplication::getInstance()->sendIvyMessage("CHILDREN ADDED");
	//SFBool bol=SFBool(1);
	//bol.routeAndTouch(sceneMap->find("SCRIPT.initializer"));
	//bol.unroute(sceneMap->find("SCRIPT.initializer"));
	
	sendMessage("SCRIPT INITIALIZED");
}
