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

#include "SpeechOutputAgent.h"
#include <comutil.h>	// header for function _com_util::ConvertStringToBSTR
SpeechOutputAgent::SpeechOutputAgent():MicoleAgent("SpeechOutputAgent","SpeechOutput")
{
	CoInitialize( NULL ); //Initializes COM library
	HRESULT	hr;
	WCHAR * spk;
	
	hr = m_cpVoice.CoCreateInstance(CLSID_SpVoice);
	if (FAILED(hr))
	{
		cout<<"Initialisation of instance of SpVoice class failed"<<endl;
		cout<<"Speech Output Agent can not be created"<<endl;
		return;
	}
	else
	{
		//bszSpeak = SysAllocString(L"Speech");
		spk = L"Speech";
		hr=m_cpVoice->Speak(spk, SPF_PURGEBEFORESPEAK, NULL);
		if (FAILED(hr)) cout<<"Agent can not speak"<<endl;
		
		bindMessage( "^OUT SPCH : str=(.*);priority=(.*);$",BUS_CALLBACK_OF(SpeechOutputAgent, handleStringOutputMessage ));
		bindMessage( "^OUT SPCH : file=(.*);$",BUS_CALLBACK_OF(SpeechOutputAgent, handleFileOutputMessage ));
		bindMessage( "^OUT SPCH : STOP;$",BUS_CALLBACK_OF(SpeechOutputAgent, handleStopSpeechMessage ));
	}
}
void SpeechOutputAgent::handleStopSpeechMessage(MicoleBus *app, int argc, const char **argv)
{
	HRESULT hr = m_cpVoice->Speak(NULL,SPF_PURGEBEFORESPEAK , NULL);
}

SpeechOutputAgent::~SpeechOutputAgent()
{

	CoUninitialize();	// Closes the COM library on the current thread

}

void SpeechOutputAgent::handleStringOutputMessage(MicoleBus *app, int argc, const char **argv)
{
	bool pr = true;
	string priority = argv[1];
	if(priority.compare("false") == 0)
		pr = false;

	HRESULT hr;
	BSTR spk = _com_util::ConvertStringToBSTR(argv[0]);
	hr = speak(spk, false, pr);
	SysFreeString(spk);

		
}
void SpeechOutputAgent::handleFileOutputMessage(MicoleBus *app, int argc, const char **argv)
{
	if(argc != 1){
		cout<<"BAD NUMBER OF SPEECH ARGUMENTS"<<endl;
		return;
	}
	HRESULT hr;
	BSTR spk = _com_util::ConvertStringToBSTR(argv[0]);
	hr=speak(spk, true, true);
	//cout<<hr<<":::"<<S_OK<<endl;
	SysFreeString(spk);

}


HRESULT SpeechOutputAgent::speak(const WCHAR *str, bool fromFile, bool priority)
{
	//cout<<"Trying to speak: "<<str<<endl;
	HRESULT	hr;
	SPVOICESTATUS status;
	hr=m_cpVoice->GetStatus(&status, NULL);
	if(priority == true){
		hr=m_cpVoice->Speak(NULL,SPF_PURGEBEFORESPEAK , NULL);
		if(fromFile)
			hr=m_cpVoice->Speak(str,SPF_ASYNC|SPF_IS_XML|SPF_IS_FILENAME , NULL);
		else
			hr=m_cpVoice->Speak(str,SPF_ASYNC|SPF_IS_XML , NULL);
	}
	else{
		if(status.dwRunningState == SPRUNSTATE::SPRS_DONE){
			hr=m_cpVoice->Speak(NULL,SPF_PURGEBEFORESPEAK , NULL);
			if(fromFile)
				hr=m_cpVoice->Speak(str,SPF_ASYNC|SPF_IS_XML|SPF_IS_FILENAME , NULL);
			else
				hr=m_cpVoice->Speak(str,SPF_ASYNC|SPF_IS_XML , NULL);
		}
	}
	return hr;
}

