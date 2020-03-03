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

// ugly patch against the inclusion loop problem...
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x05000
#endif


//#define UNICODE

#include <windows.h>
#pragma warning (disable : 4251)
#include <SpeechOutputAgent.h>
#include <ReachinMicoleApplication.h>
#include <SolarSystemAgent.h>
#include <LoggerAgent.h>
#include <KeyboardSenderAgent.h>
#include <MouseSenderAgent.h>
#include <MouseGuideAgent.h>
#include <AudioOutputAgent.h>
#include <wxCommentAgent.h>
#include <BeaconAgent.h>

#include <SimpleMsgNodeAgent.h>
#include <SimpleMsgNode.h>
#include <listeners.h>

#include <Vrml.h>
#include <Display.h>
#include <Scene.h>
#include <Node.h>
#include <Field.h>

#include <Shape.h>
#include <Appearance.h>
#include <Material.h>
#include <Sphere.h>

#include <iostream>
#include <SceneSwitcherAgent.h>

using namespace Reachin;
using namespace std;

IMPLEMENT_APP_NO_MAIN(wxCommentAgent);

//static string DATA_ROOT("C:\\jouni\\micole\\solarsystem\\data\\");
static string DATA_ROOT("C:\\solarsystem\\data\\");

//int main(int argc, char* argv[])
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	/*
	if( argc < 2 )
	{
		cerr << "Usage: " << argv[0] << " [VRML file]" << endl;
		exit(1);
	}
	*/
	
	char user[128];
	wcstombs(user, lpCmdLine,128);
	
	ReachinMicoleApplication * ama = ReachinMicoleApplication::getInstance();
	
	LoggerAgent * la = new LoggerAgent();
	SolarSystemAgent *ssa = new SolarSystemAgent(DATA_ROOT);
	SimpleMsgNodeAgent * sma = new SimpleMsgNodeAgent();
	AudioOutputAgent *aaa = new AudioOutputAgent(DATA_ROOT + "wav");
	MouseSenderAgent *mse = new MouseSenderAgent(10);
	MouseGuideAgent *mga = new MouseGuideAgent();
	SpeechOutputAgent *soa = new SpeechOutputAgent();
	KeyboardSenderAgent *ksa = new KeyboardSenderAgent();
	SimpleMsgNode *msgNode = new SimpleMsgNode();

	BeaconAgent *bca = new BeaconAgent();
	wxCommentAgent *coma = new wxCommentAgent();
	coma->setParams(hInstance);
	coma->start();
	MessageListener<SimpleMsgNodeAgent *> outMessageHandler(sma, msgNode);
	msgNode->ready->route(&outMessageHandler);
	ama->getDisplay()->children->add(msgNode);
	
	SceneSwitcherAgent *sswa = new SceneSwitcherAgent(DATA_ROOT);

	string ucommand="OUT COMMENT : user=";
	ucommand+=user;
	ucommand+=";";
	ama->sendBusMessage(ucommand.c_str());

	ama->startScene();
	cout<<"Start scene"<<endl;
	return 0;
}



