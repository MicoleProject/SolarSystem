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

#ifndef SIMPLEMSGNODEAGENT_H
#define SIMPLEMSGNODEAGENT_H
#include <Child.h>
#include <Fields.h>
#include "micoleagent.h"
#include "simplemsgnode.h"

using namespace Reachin;

class SimpleMsgNodeAgent: public MicoleAgent{

public:
	/**
	*	When the Python script has set the ready field to true,
	*	the MessageSend sends the message by calling MicoleMessageNode::sendMessage()
	*/
	struct MessageSend : public Dependent <SFBool> {
		
		MessageSend(SimpleMsgNodeAgent *_s, SimpleMsgNode *_n){
			s = _s;
			n = _n;
		}
		SimpleMsgNode *n;
		SimpleMsgNodeAgent *s;
		
		virtual void update()
		{
			if(((SFBool *)notif)->get())
			{
				s->sendMessage((string&)n->content->get());
				cout<<"JEEE"<<endl;
			}
		}
	};
	//auto_ptr<MessageSend> send;
	SimpleMsgNodeAgent();
	//void initSend(SimpleMsgNode *sn);
	


};


#endif