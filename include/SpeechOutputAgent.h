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

#ifndef SPEECHOUTPUTAGENT_H
#define SPEECHOUTPUTAGENT_H

#include <sapi.h>
#include <atlbase.h>
#include "MicoleAgent.h"

/*
Speech output agent 
*/
class SpeechOutputAgent: public MicoleAgent{
public:
	
	SpeechOutputAgent(void);
	/**
	* Handles messages of type "OUT SPCH : str=Hello world;"
	* Speaks the content of the str parameter. If the str is empty,
	* the agent stops the speech: "OUT SPCH : str=;"
	*/
	void handleStringOutputMessage(MicoleBus *app, int argc, const char **argv);
	/**
	* Handles messages of type "OUT SPCH : file=c:\data\hello.txt;"
	* The parameter file must contain fully qualified path to the file. The 
	* contents of the file is spoken.
	*/
	void handleFileOutputMessage(MicoleBus *app, int argc, const char **argv);
	/**
	* Handles the "OUT SPCH : STOP;" message. Stops the speaking.
	* The speech can be stopped also by sending an empty string to the agent.
	*/
	void handleStopSpeechMessage(MicoleBus *app, int argc, const char **argv);
	
	~SpeechOutputAgent();
private:
	CComPtr<ISpVoice>   m_cpVoice;
	HRESULT speak(const WCHAR * str, bool fromFile, bool priority);
	//ULONG *s ;
	//BSTR	bszSpeak;
	//bool busy;
};
#endif