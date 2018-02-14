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

#include "init.h"

static void loadConfig(void);
static void initJoypad(void);
static void showLoadingStep(float step, float maxSteps);

void init18N(int argc, char *argv[])
{
	int i;
	int languageId = -1;

	setlocale(LC_NUMERIC, "");

	for (i = 1 ; i < argc ; i++)
	{
		if (strcmp(argv[i], "-language") == 0)
		{
			languageId = i + 1;

			if (languageId >= argc)
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "You must specify a language to use with -language. Using default.");
			}
		}
	}

	setLanguage("blobwarsAttrition", languageId == -1 ? NULL : argv[languageId]);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Numeric is %s", setlocale(LC_NUMERIC, "C"));
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "atof(2.75) is %f", atof("2.75"));
}

void initSDL(void)
{
	int rendererFlags, windowFlags;
	
	/* done in src/plat/ */
	createSaveFolder();

	loadConfig();
	
	app.winWidth = SCREEN_WIDTH;
	app.winHeight = SCREEN_HEIGHT;

	rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	
	windowFlags = 0;
	
	if (app.config.fullscreen)
	{
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialize SDL Mixer\n");
		exit(1);
    }

    Mix_AllocateChannels(64);

	Mix_Volume(-1, app.config.soundVolume * (MIX_MAX_VOLUME / 10));
	Mix_VolumeMusic(app.config.musicVolume * (MIX_MAX_VOLUME / 10));

	app.window = SDL_CreateWindow("Blob Wars : Attrition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app.winWidth, app.winHeight, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}

	initJoypad();
}

static void initJoypad(void)
{
	int i, n;

	n = SDL_NumJoysticks();

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%d joysticks available", n);

	for (i = 0 ; i < n ; i++)
	{
		app.joypad = SDL_JoystickOpen(i);
		
		if (app.joypad)
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Using joystick '%s'", SDL_JoystickNameForIndex(i));
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "\tAxes: %d", SDL_JoystickNumAxes(app.joypad));
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "\tButtons: %d", SDL_JoystickNumButtons(app.joypad));
			return;
		}
	}
}

void initGameSystem(void)
{
	int i, numInitFuns;
	void (*initFuncs[]) (void) = {
		initGraphics,
		initFonts,
		initAtlas,
		initWidgets,
		initSounds,
		initSprites,
		initEntityFactory
	};

	numInitFuns = sizeof(initFuncs) / sizeof(void*);

	for (i = 0 ; i < numInitFuns ; i++)
	{
		showLoadingStep(i + 1, numInitFuns);

		initFuncs[i]();
	}
}

/*
 * Just in case the initial loading takes a while on the target machine. The rest of the loading a pretty quick by comparison.
 */
static void showLoadingStep(float step, float maxSteps)
{
	SDL_Rect r;

	prepareScene();

	r.w = SCREEN_WIDTH - 400;
	r.h = 14;
	r.x = (SCREEN_WIDTH / 2) - r.w / 2;
	r.y = (SCREEN_HEIGHT / 2) - r.h / 2;

	SDL_SetRenderDrawColor(app.renderer, 128, 128, 128, 255);
	SDL_RenderDrawRect(app.renderer, &r);

	r.w *= (step / maxSteps);
	r.x += 2;
	r.y += 2;
	r.w -= 4;
	r.h -= 4;

	SDL_SetRenderDrawColor(app.renderer, 128, 196, 255, 255);
	SDL_RenderFillRect(app.renderer, &r);

	presentScene();

	SDL_Delay(1);
}


static void initDefaultConfig(void)
{
	int i;
	
	app.config.hudInventory = 1;
	app.config.blood = 1;

	app.config.musicVolume = 8;
	app.config.soundVolume = 10;

	app.config.keyControls[CONTROL_LEFT] = SDL_SCANCODE_A;
	app.config.keyControls[CONTROL_RIGHT] = SDL_SCANCODE_D;
	app.config.keyControls[CONTROL_UP] = SDL_SCANCODE_W;
	app.config.keyControls[CONTROL_DOWN] = SDL_SCANCODE_S;
	app.config.keyControls[CONTROL_JUMP] = SDL_SCANCODE_I;
	app.config.keyControls[CONTROL_FIRE] = SDL_SCANCODE_J;
	app.config.keyControls[CONTROL_JETPACK] = SDL_SCANCODE_L;
	app.config.keyControls[CONTROL_MAP] = SDL_SCANCODE_TAB;
	app.config.keyControls[CONTROL_PAUSE] = SDL_SCANCODE_P;

	/* can't use memset here, as it doesn't work */
	for (i = 0 ; i < CONTROL_MAX ; i++)
	{
		app.config.joypadControls[i] = -1;
	}
	
	app.config.joypadControls[CONTROL_JUMP] = 1;
	app.config.joypadControls[CONTROL_FIRE] = 3;
	app.config.joypadControls[CONTROL_JETPACK] = 2;
	app.config.joypadControls[CONTROL_MAP] = 6;
	app.config.joypadControls[CONTROL_PAUSE] = 7;
}

static void loadConfig(void)
{
	int i;
	cJSON *root, *controlsJSON, *node;
	char *text;

	initDefaultConfig();

	if (fileExists(getSaveFilePath(CONFIG_FILENAME)))
	{
		text = readFile(getSaveFilePath(CONFIG_FILENAME));

		root = cJSON_Parse(text);

		app.config.fullscreen = cJSON_GetObjectItem(root, "fullscreen")->valueint;
		app.config.musicVolume = cJSON_GetObjectItem(root, "musicVolume")->valueint;
		app.config.soundVolume = cJSON_GetObjectItem(root, "soundVolume")->valueint;
		
		app.config.hudInventory = cJSON_GetObjectItem(root, "hudInventory")->valueint;
		app.config.blood = cJSON_GetObjectItem(root, "blood")->valueint;

		controlsJSON = cJSON_GetObjectItem(root, "controls");
		if (controlsJSON)
		{
			node = cJSON_GetObjectItem(controlsJSON, "keys")->child;
			while (node)
			{
				i = lookup(node->string);

				app.config.keyControls[i] = node->valueint;

				node = node->next;
			}

			node = cJSON_GetObjectItem(controlsJSON, "joypad")->child;
			while (node)
			{
				i = lookup(node->string);

				app.config.joypadControls[i] = node->valueint;

				node = node->next;
			}
		}

		cJSON_Delete(root);
		free(text);
	}
}

void saveConfig(void)
{
	int i;
	char *out, *configFilename;
	cJSON *root, *controlsJSON, *keysJSON, *joypadJSON;

	configFilename = getSaveFilePath(CONFIG_FILENAME);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Saving config ...");

	root = cJSON_CreateObject();
	
	cJSON_AddNumberToObject(root, "fullscreen", app.config.fullscreen);
	cJSON_AddNumberToObject(root, "musicVolume", app.config.musicVolume);
	cJSON_AddNumberToObject(root, "soundVolume", app.config.soundVolume);
	
	cJSON_AddNumberToObject(root, "blood", app.config.blood);
	cJSON_AddNumberToObject(root, "hudInventory", app.config.hudInventory);

	keysJSON = cJSON_CreateObject();
	for (i = 0 ; i < CONTROL_MAX ; i++)
	{
		cJSON_AddNumberToObject(keysJSON, getLookupName("CONTROL_", i), app.config.keyControls[i]);
	}

	joypadJSON = cJSON_CreateObject();
	for (i = 0 ; i < CONTROL_MAX ; i++)
	{
		cJSON_AddNumberToObject(joypadJSON, getLookupName("CONTROL_", i), app.config.joypadControls[i]);
	}

	controlsJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(controlsJSON, "keys", keysJSON);
	cJSON_AddItemToObject(controlsJSON, "joypad", joypadJSON);
	cJSON_AddItemToObject(root, "controls", controlsJSON);

	out = cJSON_Print(root);

	if (!writeFile(configFilename, out))
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to save config");
	}

	cJSON_Delete(root);
	free(out);
}

void cleanup(void)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cleaning up ...");
	
	destroyLookups();
	
	destroyFonts();
	
	destroyTextures();
	
	expireTexts(1);
	
	destroyGame();

	if (app.joypad != NULL) {
		SDL_JoystickClose(app.joypad);
	}
	
	SDL_DestroyRenderer(app.renderer);
	
	SDL_DestroyWindow(app.window);
	
	TTF_Quit();
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Done.");
	
	SDL_Quit();
}
