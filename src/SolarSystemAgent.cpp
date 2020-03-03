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

#include "solarsystemagent.h"
#include <MicoleStringStream.h>
#include <stdlib.h>




SolarSystemAgent::SolarSystemAgent(string dataroot):MicoleAgent("SolarSystemAgent","MicroworldAgent")
{
	path = dataroot;

//	lang.push_back("EN");
//	lang.push_back("FI");
//	lang.push_back("SE");
//	lang_iterator = lang.begin();

	current = "SOLARSYSTEM";
	loadSolarSystemComments();

	bindMessage("^IN SA : (obj=(.*));(type=(.*));$", BUS_CALLBACK_OF(SolarSystemAgent, handleMicroWorldInput));
	bindMessage("^IN SA : cmd=(.*);obj=(.*);$",BUS_CALLBACK_OF(SolarSystemAgent, handleCommand));
}

void SolarSystemAgent::handleCommand(MicoleBus *app, int argc, const char **argv)
{
	MicoleStringStream st;
	string cmd = argv[0];
	string obj = argv[1]; 
	if (cmd.compare("load") == 0){
		st<<"OUT SPCH : STOP;";
		sendMessage(st.str());
		st.flush();
		st<<"OUT SND : name=beep.wav;type=1;vol=100;spk=FRONT;pan=0;";
		sendMessage(st.str());
		st.flush();
		current = obj;

		if (obj == "SOLARSYSTEM"){
			planet_comments.clear();
			st<<"OUT COMMENT : command=OK;";
			sendMessage(st.str());
			st.flush();
		}else {
			loadPlanetComments(obj);
		}
		st<<"OUT SSWA : scene="<<obj<<";";
		sendMessage(st.str());
		st.flush();
		
	}else if (cmd.compare("teach") == 0){
		if(comm_iterator == planet_comments.end()){
			st<<"OUT SPCH : STOP;";
			sendMessage(st.str());
			st.flush();
			st<<"OUT SND : name=kiling.wav;type=1;vol=100;spk=FRONT;pan=0;";
			sendMessage(st.str());
			st.flush();
			comm_iterator = planet_comments.begin();
		}
		else {
			st<<"OUT SPCH : str="+ *comm_iterator +";priority=true;";
			sendMessage(st.str());
			st.flush();
			comm_iterator++;
		}
	} 
}
	

void SolarSystemAgent::handleMicroWorldInput(MicoleBus *app, int argc, const char **argv)
{
	MicoleStringStream os;
	string obj = argv[1];
	string type = argv[3];

	string key = type + "_" + obj;
	
	string data = solar_comments.find(key)->second;
	os<<"OUT SPCH : str="+ data +";priority=true;";
	sendMessage(os.str());
	os.flush();

	if(type.compare("PLANET") == 0){
		os<<"OUT COMMENT : active="+ obj +";";
		sendMessage(os.str());
		os.flush();
	}

}

SolarSystemAgent::~SolarSystemAgent()
{
}

void SolarSystemAgent::reset()
{

}

void SolarSystemAgent::loadPlanetComments(string object)
{
	string file = path + "text\\";
//	file.append(*lang_iterator);
//	file.append("FI");
	file.append(object + ".txt");

	string line;
	MicoleStringStream os;
//	os<<"loadPlanetCommenets() - loading file: "<<file;
//	sendMessage(os.str());
//	os.flush();

	ifstream textfile;
	textfile.open(file.c_str(), ios_base::in);
	while(getline(textfile,line)){
		planet_comments.push_back(line);
	}
	textfile.close();
	comm_iterator = planet_comments.begin();
}

void SolarSystemAgent::loadSolarSystemComments()
{
	string file = path + "text\\";
//	file.append(*lang_iterator);
//	file.append("FI");
	file.append("solarsystem.txt");

	string line;
	string key;
	string data;
	size_t found;

	ifstream textfile;
	textfile.open(file.c_str(), ios_base::in);
	while(getline(textfile,line)){
		found=line.find("=");
		if (found!=string::npos){
			key = line.substr(0,found);
			data = line.substr(found+1); 
			solar_comments.insert( pair<string,string>(key,data) );
		}
	}
	textfile.close();
}
