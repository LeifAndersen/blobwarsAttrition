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

typedef struct Texture Texture;
typedef struct Lookup Lookup;
typedef struct Quadtree Quadtree;
typedef struct Entity Entity;
typedef struct Objective Objective;
typedef struct Trigger Trigger;
typedef struct Marker Marker;
typedef struct Particle Particle;
typedef struct Sprite Sprite;
typedef struct Tuple Tuple;
typedef struct HubMission HubMission;
typedef struct Widget Widget;
typedef struct Atlas Atlas;
typedef struct Bullet Bullet;

typedef struct {
	int debug;
	int takeScreenshots;
	char *screenshotFolder;
	int showFPS;
	int cheatHealth;
	int cheatPower;
	int cheatOxygen;
	int cheatKeys;
	int cheatLevels;
	int cheatReload;
	int cheatBlind;
	int fps;
} Dev;

struct Texture {
	char name[MAX_DESCRIPTION_LENGTH];
	long hash;
	long ttl;
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
	float x;
	float y;
} PointF;

typedef struct {
	SDL_Color red;
	SDL_Color orange;
	SDL_Color yellow;
	SDL_Color green;
	SDL_Color blue;
	SDL_Color cyan;
	SDL_Color purple;
	SDL_Color white;
	SDL_Color black;
	SDL_Color lightGrey;
	SDL_Color darkGrey;
} Colors;

struct Lookup {
	char name[MAX_NAME_LENGTH];
	long value;
	Lookup *next;
};

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
	void (*handleClick)(int x, int y, int btn);
	void (*handleDrag)(int x, int y, int dx, int dy, int cx, int cy);
	void (*handleMouseUp)(int x, int y, int btn);
} Delegate;

struct Entity {
	unsigned long uniqueId;
	char name[MAX_NAME_LENGTH];
	char spriteName[MAX_NAME_LENGTH];
	int type;
	float x;
	float y;
	int w;
	int h;
	int health;
	int healthMax;
	int alive;
	int oxygen;
	int startX;
	int startY;
	float dx;
	float dy;
	int tx;
	int ty;
	int reload;
	int isOnGround;
	int effectType;
	int bleedTime;
	int facing;
	int damage;
	int weaponType;
	int shotsToFire;
	int maxShotsToFire;
	int isSolid;
	int environment;
	int isStatic;
	int isMissionTarget;
	int thinkTime;
	int plane;
	int value;
	int canCarryItem;
	int spawnedIn;
	int spawnedInTimer;
	int shudderTimer;
	int starTimer;
	int teleportTimer;
	int stunTimer;
	int weakAgainst;
	int power;
	int powerMax;
	int collected;
	int canBeCarried;
	int canBePickedUp;
	int provided;
	long flags;
	SDL_Rect bounds;
	int sprite[3];
	int spriteTime;
	int spriteFrame;
	Entity *carriedItem;
	Entity *owner;
	void (*action)(void);
	void (*walk)(void);
	void (*attack)(void);
	void (*touch)(Entity *other);
	void (*tick)(void);
	void (*die)(void);
	int (*canFire)(Entity *target);
	void (*reset)(void);
	void (*activate)(int active);
	void (*changeEnvironment)(void);
	int (*getCurrentSprite)(void);
	void (*animate)(void);
	void (*applyDamage)(int amount);
	SDL_Rect (*getBounds)(void);
	Entity *next;
};

struct Objective {
	char id[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
	char targetName[MAX_NAME_LENGTH];
	int currentValue;
	int targetValue;
	int totalValue;
	int required;
	Objective *next;
};

/* How you going, Dave? */
struct Trigger {
	char name[MAX_NAME_LENGTH];
	char message[MAX_DESCRIPTION_LENGTH];
	char targetNames[MAX_DESCRIPTION_LENGTH];
	int x;
	int y;
	int w;
	int h;
	Trigger *next;
};

struct HubMission {
	char id[MAX_NAME_LENGTH];
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
	float x;
	float y;
	int status;
	int unlockCount;
	float distance;
	HubMission *next;
};

struct Tuple {
	char key[MAX_NAME_LENGTH];
	union {
		char s[MAX_NAME_LENGTH];
		int i;
		float f;
	} value;
	Tuple *next;
};

typedef struct {
	SDL_Rect bounds;
	float shakeAmount;
	int x;
	int y;
} Camera;

typedef struct {
	int x;
	int y;
	int w;
	int h;
	int dx;
	int dy;
	int button[MAX_MOUSE_BUTTONS];
	int dragging;
} Mouse;

typedef struct {
	char saveDir[MAX_FILENAME_LENGTH];
	int winWidth;
	int winHeight;
	float scaleX;
	float scaleY;
	int fullscreen;
	int musicVolume;
	int soundVolume;
	int hideMouse;
	Mouse mouse;
	int keyboard[MAX_KEYBOARD_KEYS];
	SDL_Texture *backBuffer;
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int awaitingWidgetInput;
	int lastKeyPressed;
	int lastButtonPressed;
	int keyControls[CONTROL_MAX];
} App;

typedef struct {
	int sound;
	int music;
} Config;

typedef struct {
	int cells;
	int hearts;
	int keysFound;
	int totalMIAs;
	int totalTargets;
	int totalCells;
	int totalHearts;
	int totalKeys;
	int deaths;
	int statShotsFired[WPN_ANY];
	int statShotsHit[WPN_ANY];
	int enemiesKilled;
	int missionsPlayed;
	long timePlayed;
	unsigned long entityCounter;
	char worldId[MAX_NAME_LENGTH];
	int isResumingMission;
	int isComplete;
	char **mias;
	char **targets;
	int keys[MAX_KEY_TYPES][MAX_NAME_LENGTH];
	Tuple missionStatusHead, *missionStatusTail;
	Config config;
} Game;

struct Marker {
	int sprite;
	float value;
	float y;
	Marker *next;
};

typedef struct {
	int data[MAP_WIDTH][MAP_HEIGHT];
	int decal[MAP_WIDTH][MAP_HEIGHT];
	SDL_Rect bounds;
} Map;

struct Quadtree {
	int depth;
	int x, y, w, h;
	Entity **ents;
	int capacity;
	int numEnts;
	int addedTo;
	Quadtree *node[4];
};

struct Sprite {
	char name[MAX_NAME_LENGTH];
	SDL_Rect frames[MAX_SPRITE_FRAMES];
	int times[MAX_SPRITE_FRAMES];
	char filenames[MAX_SPRITE_FRAMES][MAX_FILENAME_LENGTH];
	int currentFrame;
	float currentTime;
	int w;
	int h;
	int numFrames;
	Sprite *next;
};

struct Particle {
	int type;
	int plane;
	float health;
	float x;
	float y;
	float dx;
	float dy;
	int size;
	float r;
	float g;
	float b;
	int spriteIndex;
	double spriteTime;
	int spriteFrame;
	int destroyAfterAnim;
	int onScreen;
	Particle *next;
};

struct Bullet {
	int x;
	int y;
	int facing;
	int damage;
	int health;
	int weaponType;
	float dx;
	float dy;
	int sprite[2];
	Entity *owner;
	Bullet *next;
};

typedef struct {
	char id[MAX_NAME_LENGTH];
	int state;
	Entity *bob, *boss;
	Map map;
	int allObjectivesComplete;
	int frameCounter;
	int currentStatus;
	int isBossMission;
	int isBossActive;
	int isOutpostMission;
	PointF checkpoints[MAX_CHECKPOINTS];
	Quadtree quadtree;
	Entity entityHead, *entityTail;
	Particle particleHead, *particleTail;
	Bullet bulletHead, *bulletTail;
	Objective objectiveHead, *objectiveTail;
	Trigger triggerHead, *triggerTail;
} World;

struct Widget {
	int type;
	int x;
	int y;
	int w;
	int h;
	int visible;
	int enabled;
	char name[MAX_NAME_LENGTH];
	char group[MAX_NAME_LENGTH];
	char label[MAX_NAME_LENGTH];
	char options[MAX_WIDGET_OPTIONS][MAX_NAME_LENGTH];
	int value;
	int clicked;
	Widget *next;
};

struct Atlas {
	char filename[MAX_FILENAME_LENGTH];
	SDL_Rect rect;
	Atlas *next;
};
