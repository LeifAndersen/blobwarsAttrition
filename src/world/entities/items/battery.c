/*
Copyright (C) 2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "battery.h"

void initBattery(Entity *e)
{
	initConsumable(e);

	e->spriteFrame = 0;
	e->spriteTime = -1;
}

void touch(Entity *other)
{
	if (touchedPlayer(other))
	{
		world.bob->power = MIN(world.bob->power + self->power, world.bob->powerMax);

		setGameplayMessage(MSG_STANDARD, "Picked up a %s", self->name);

		pickupItem();

		playSound(SND_ITEM, CH_ITEM);
	}
}