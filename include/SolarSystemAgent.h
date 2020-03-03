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

#ifndef SOLARSYSTEMAGENT_H
#define SOLARSYSTEMAGENT_H

#include <windows.h>
#include "MicoleAgent.h"
#include <map>
#include <list>
#include <iostream>
#include <fstream>


class SolarSystemAgent: public MicoleAgent{

public:
	
	SolarSystemAgent(string dataroot);
	void handleMicroWorldInput( MicoleBus *app, int argc, const char **argv );
	void handleCommand( MicoleBus *app, int argc, const char **argv );
	void reset();
	void loadSolarSystemComments( string str );
	void loadPlanetComments( string str );
	void loadSolarSystemComments();
	~SolarSystemAgent();

private:
	string path;
	string current;

//	list< string > lang;
//	list< string >::iterator lang_iterator; 

	map< string,string > solar_comments;
	
	list< string > planet_comments;
	list< string >::iterator comm_iterator; 
};

#endif
