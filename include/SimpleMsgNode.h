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

#ifndef SIMPLEMSGNODE_H
#define SIMPLEMSGNODE_H
#include <Child.h>
#include <Fields.h>

using namespace Reachin;

class SimpleMsgNode: public Child{

public:
	static const Interface interface;
	
	auto_ptr< SFString > content;
	auto_ptr<SFBool> ready;
	auto_ptr<SFBool> inbound;
	SimpleMsgNode(	Defined <SFString> _msg = 0, 
					Defined <SFBool> _ready = 0,
					Defined <SFBool> _inbound = 0) :
		content(_msg),
		ready(_ready),
		inbound(_inbound),
		Child(){};

};

#endif