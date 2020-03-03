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

#include "simplemsgnode.h"


const Interface SimpleMsgNode::interface(
  "SimpleMsgNode", typeid(SimpleMsgNode), 
  Create<SimpleMsgNode>::create,
  field( "content", &SimpleMsgNode::content   ) +
  field( "inbound", &SimpleMsgNode::inbound ) +
  exposedField( "ready", &SimpleMsgNode::ready   ) 
 );