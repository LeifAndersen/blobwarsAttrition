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

#ifndef REVISION
#define REVISION 0
#endif

#ifndef DATA_DIR
#define DATA_DIR ""
#endif

#define _(string) getTranslatedString(string)

#define PI 3.14159265358979323846
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CAROLINE(a,b) MIN(a,b)
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define TO_RAIDANS(angleDegrees) (angleDegrees * PI / 180.0)
#define TO_DEGREES(angleRadians) (angleRadians * 180.0 / PI)

#define SAVE_FILENAME		"game.save"
#define CONFIG_FILENAME		"config.json"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

#define MAX_KEYBOARD_KEYS	350
#define MAX_MOUSE_BUTTONS	6

#define FPS				60
#define LOGIC_RATE		(1000.0 / FPS)

#define MAX_FONTS					64
#define NUM_TEXT_BUCKETS			64
#define TEXT_TTL					(1000 * 20)

#define MAX_NAME_LENGTH				32
#define MAX_DESCRIPTION_LENGTH		512
#define MAX_LINE_LENGTH				1024
#define MAX_FILENAME_LENGTH			1024

#define NUM_TEXTURE_BUCKETS			32
#define NUM_ATLAS_BUCKETS			64

#define MAP_WIDTH					200
#define MAP_HEIGHT					200

#define MAP_RENDER_WIDTH 			((SCREEN_WIDTH / MAP_TILE_SIZE) + 1)
#define MAP_RENDER_HEIGHT			((SCREEN_HEIGHT / MAP_TILE_SIZE) + 1)

#define MAP_TILE_SIZE				64
#define MAP_TILE_AIR				0
#define MAP_TILE_WATER				1
#define MAP_TILE_SLIME				2
#define MAP_TILE_LAVA				3
#define MAP_TILE_SOLID				4
#define MAP_TILE_NON_SOLID			200
#define MAP_TILE_ANIMATED_WATER		240
#define MAP_TILE_ANIMATED_SLIME		245
#define MAP_TILE_ANIMATED_LAVA		250
#define MAP_TILE_OUTSIDE			255
#define MAP_TILE_MAX				256

#define JUMP_POWER					-12
#define MAX_OXYGEN					(FPS * 10)
#define MAX_KEY_TYPES				8
#define MAX_ITEMS					14

#define MAX_CHECKPOINTS				15

#define MAX_ENTS_TO_OBSERVE			12

#define MAX_SND_CHANNELS			64

#define MAX_SAVE_SLOTS				5

enum
{
	ET_NONE,
	ET_EFFECT,
	ET_TRAP,
	ET_BOB,
	ET_ENEMY,
	ET_TEEKA,
	ET_BOSS,
	ET_HEART,
	ET_CELL,
	ET_KEY,
	ET_ITEM,
	ET_CONSUMABLE,
	ET_MIA,
	ET_DECORATION,
	ET_DOOR,
	ET_LIFT,
	ET_PUSHBLOCK,
	ET_DESTRUCTABLE,
	ET_POWER_POINT,
	ET_CARD_READER,
	ET_PRESSURE_PLATE,
	ET_TELEPORTER,
	ET_ITEM_PAD,
	ET_POOL,
	ET_EXIT,
	ET_INFO_POINT
};

#define EF_NONE					0
#define EF_WEIGHTLESS			(2 << 0)
#define EF_BOUNCES				(2 << 1)
#define EF_TELEPORTING			(2 << 2)
#define EF_NO_ENVIRONMENT		(2 << 3)
#define EF_SWIMS				(2 << 4)
#define EF_HALT_AT_EDGE			(2 << 5)
#define EF_NO_CLIP				(2 << 6)
#define EF_EXPLODES				(2 << 7)
#define EF_IGNORE_BULLETS		(2 << 8)
#define EF_FLICKER				(2 << 9)
#define EF_FRICTIONLESS			(2 << 10)
#define EF_WATER_BREATHING		(2 << 11)
#define EF_IMMUNE				(2 << 12)
#define EF_BOMB_SHIELD			(2 << 13)
#define EF_GONE					(2 << 14)
#define EF_KILL_OFFSCREEN		(2 << 15)
#define EF_ALWAYS_PROCESS		(2 << 16)
#define EF_NO_TELEPORT			(2 << 17)
#define EF_NO_OBSERVE			(2 << 18)
#define EF_BULLET_HIT			(2 << 19)
#define EF_CRUSHABLE			(2 << 20)

#define GRAVITY_POWER				0.5f
#define FRICTION					0.75f

enum
{
	JOYPAD_AXIS_X,
	JOYPAD_AXIS_Y,
	JOYPAD_AXIS_MAX
};

enum
{
	FACING_RIGHT,
	FACING_LEFT,
	FACING_DIE
};

enum
{
	DOOR_OPEN,
	DOOR_CLOSED
};

enum
{
	LIFT_GOTO_FINISH,
	LIFT_GOTO_START
};

enum
{
	WPN_PISTOL,
	WPN_PLASMA,
	WPN_SPREAD,
	WPN_LASER,
	WPN_GRENADES,
	WPN_ANY,
	WPN_AIMED_PISTOL,
	WPN_MACHINE_GUN,
	WPN_SHOTGUN,
	WPN_MISSILE
};

enum
{
	ALIVE_ALIVE,
	ALIVE_DYING,
	ALIVE_DEAD
};

enum
{
	CONTROL_LEFT,
	CONTROL_RIGHT,
	CONTROL_UP,
	CONTROL_DOWN,
	CONTROL_FIRE,
	CONTROL_JUMP,
	CONTROL_JETPACK,
	CONTROL_PAUSE,
	CONTROL_MAP,
	CONTROL_MAX
};

enum
{
	TA_LEFT,
	TA_RIGHT,
	TA_CENTER
};

enum
{
	MS_LOCKED,
	MS_INCOMPLETE,
	MS_PARTIAL,
	MS_MISSING_HEART_CELL,
	MS_COMPLETE
};

enum
{
	MT_NORMAL,
	MT_TRAINING,
	MT_OUTPOST,
	MT_BOSS
};

enum
{
	WS_START,
	WS_IN_PROGRESS,
	WS_PAUSED,
	WS_GAME_COMPLETE,
	WS_OBSERVING,
	WS_COMPLETE,
	WS_MISSION_COMPLETE,
	WS_GAME_OVER,
	WS_QUIT
};

enum
{
	PLANE_BACKGROUND,
	PLANE_FOREGROUND
};

enum
{
	ENV_AIR,
	ENV_WATER,
	ENV_SLIME,
	ENV_LAVA
};

enum
{
	PT_LINE,
	PT_POINT,
	PT_TEXTURED
};

enum
{
	MSG_STANDARD,
	MSG_GAMEPLAY,
	MSG_PROGRESS,
	MSG_OBJECTIVE
};

enum
{
	SND_MENU_SELECT,
	SND_MENU_BACK,
	SND_MENU_NAV,
	SND_PISTOL,
	SND_MACHINE_GUN,
	SND_PLASMA,
	SND_THROW,
	SND_SPREAD,
	SND_SHOTGUN,
	SND_LASER,
	SND_MISSILE,
	SND_RICO_1,
	SND_RICO_2,
	SND_GRENADE_BOUNCE,
	SND_EXPLOSION,
	SND_FLESH_HIT,
	SND_METAL_HIT,
	SND_DEATH_1,
	SND_DEATH_2,
	SND_DEATH_3,
	SND_SPLAT,
	SND_DROID_DIE_1,
	SND_DROID_DIE_2,
	SND_PRESSURE_PLATE,
	SND_DOOR_START,
	SND_DOOR_FINISH,
	SND_CHERRY,
	SND_ITEM,
	SND_KEY,
	SND_WEAPON,
	SND_TELEPORT,
	SND_APPEAR,
	SND_MIA,
	SND_WATER_IN,
	SND_WATER_OUT,
	SND_SLIME,
	SND_DROWN,
	SND_DENIED,
	SND_CONFIRMED,
	SND_MISSION_COMPLETE,
	SND_HEART_CELL,
	SND_TROPHY,
	SND_ELECTRIC_HIT,
	SND_ITEM_PAD,
	SND_POWER_POOL,
	SND_POP,
	SND_MAX
};

enum
{
	WT_BUTTON,
	WT_SLIDER,
	WT_SPINNER,
	WT_INPUT
};

enum
{
	TROPHY_UNEARNED,
	TROPHY_BRONZE,
	TROPHY_SILVER,
	TROPHY_GOLD,
	TROPHY_PLATINUM,
	TROPHY_MAX
};

enum
{
	STAT_MISSIONS_COMPLETE,
	STAT_KEYS_FOUND,
	STAT_CELLS_FOUND,
	STAT_HEARTS_FOUND,
	STAT_TARGETS_DEFEATED,
	STAT_MIAS_RESCUED,
	STAT_DEATHS,
	STAT_SHOTS_FIRED,
	STAT_SHOTS_HIT,
	STAT_SHOT_ACCURACY,
	STAT_EYE_DROID_EXPLOSION_KILLS,
	STAT_FLY_TIME,
	STAT_SWIM_TIME,
	STAT_CHERRIES_PICKED_UP,
	STAT_BATTERIES_PICKED_UP,
	STAT_WEAPONS_PICKED_UP,
	STAT_ENEMIES_KILLED,
	STAT_MISSIONS_PLAYED,
	STAT_PERCENT_COMPLETE,
	STAT_TIME_PLAYED,
	STAT_MAX
};

enum
{
	ST_MISSION_COMPLETE,
	ST_OBJECTIVES,
	ST_INCOMPLETE,
	ST_COMPLETE,
	ST_PRESS_FIRE,
	ST_OPTIONS,
	ST_CONTROLS,
	ST_TROPHIES,
	ST_PAGE,
	ST_HIDDEN,
	ST_WEAPON,
	ST_CELL,
	ST_HEART,
	ST_TELEPORTER,
	ST_LASERS,
	ST_POWER_POINT,
	ST_LIFT,
	ST_EXIT,
	ST_LOCKED,
	ST_OPENED,
	ST_GOT_GRENADES,
	ST_PICKED_UP,
	ST_REMOVED,
	ST_REQUIRED,
	ST_CANNOT_CARRY,
	ST_RESCUED,
	ST_JETPACK_POWER,
	ST_AQUALUNG_POWER,
	ST_QUIT_HUB,
	ST_QUIT_TUTORIAL,
	ST_QUIT_SAVE,
	ST_QUIT_LOSE,
	ST_MIAS,
	ST_ITEMS,
	ST_TARGETS,
	ST_OBJECTIVE_COMPLETE,
	ST_CHERRY_BUNCH,
	ST_CHERRY_PAIR,
	ST_CHERRY_SMALL,
	ST_BATTERY_FULL,
	ST_BATTERY,
	ST_USED_BATTERY,
	ST_WEAK_BATTERY,
	ST_CHOOSE_SAVE,
	ST_LOAD,
	ST_OVERWRITE_1,
	ST_OVERWRITE_2,
	ST_FREEPLAY,
	ST_HEART_CELL,
	ST_HUB_MISSIONS,
	ST_HUB_MIAS,
	ST_HUB_TARGETS,
	ST_HUB_KEYS,
	ST_HUB_HEARTS,
	ST_HUB_CELLS,
	ST_MAX
};
