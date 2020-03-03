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

#ifndef MOUSEGUIDEAGENT_H
#define MOUSEGUIDEAGENT_H

#include <lock.h>
#include <Transform.h>
#include <MicoleAgent.h>

//#include "micolelib.h"

using namespace Reachin;

class MouseGuideAgent : public MicoleAgent
{
	public:
		MouseGuideAgent();
		~MouseGuideAgent();

		void handleMousePress( MicoleBus *app, int argc, const char **argv );
		void handleMouseMove( MicoleBus *app, int argc, const char **argv );
		void handleReLocation(MicoleBus *app, int argc, const char **argv);

		virtual void onMouse(string, string);
private:
	bool follow;
	Transform *xform1;
};

#endif
