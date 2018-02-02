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

#include "text.h"

static void loadFont(int size);
static SDL_Texture *getCachedText(unsigned long hash);
static void cacheText(unsigned long hash, SDL_Texture *t);
static void drawTextNormal(int x, int y, int size, int align, SDL_Color c, const char *text);
static void drawTextSplit(int x, int y, int size, int align, SDL_Color c, char *text);
void textSize(const char *text, int size, int *w, int *h);

static char drawTextBuffer[MAX_LINE_LENGTH];
static TTF_Font *font[MAX_FONTS];
static Texture textures[NUM_TEXT_BUCKETS]; 
static int maxWidth = 0;
static int cacheSize = 0;
static int textShadow = 1;
static SDL_Color textShadowColor;

void initFonts(void)
{
	memset(&font, 0, sizeof(TTF_Font*) * MAX_FONTS);
	memset(&textures, 0, sizeof(Texture) * NUM_TEXT_BUCKETS);
}

void drawText(int x, int y, int size, int align, SDL_Color c, const char *format, ...)
{
	va_list args;

	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

	va_start(args, format);
	vsprintf(drawTextBuffer, format, args);
	va_end(args);
	
	if (maxWidth == 0)
	{
		drawTextNormal(x, y, size, align, c, drawTextBuffer);
	}
	else
	{
		drawTextSplit(x, y, size, align, c, drawTextBuffer);
	}
}

static void drawTextNormal(int x, int y, int size, int align, SDL_Color c, const char *text)
{
	SDL_Surface *surface;
	SDL_Texture *t;
	int w, h;
	long hash;
	
	if (size >= MAX_FONTS)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "ERROR: %d exceeds max font size index of %d\n", size, MAX_FONTS);
		exit(1);
	}
	
	if (!font[size])
	{
		loadFont(size);
	}

	hash = hashcode(text) + size;

	t = getCachedText(hash);

	if (!t)
	{
		surface = TTF_RenderText_Blended(font[size], text, colors.white);
		t = SDL_CreateTextureFromSurface(app.renderer, surface);
		SDL_FreeSurface(surface);
		
		cacheText(hash, t);
	}

	SDL_QueryTexture(t, NULL, NULL, &w, &h);

	if (align == TA_CENTER)
	{
		x -= (w / 2);
	}
	else if (align == TA_RIGHT)
	{
		x -= w;
	}
	
	if (textShadow)
	{
		SDL_SetTextureColorMod(t, textShadowColor.r, textShadowColor.g, textShadowColor.b);
		
		blit(t, x + 1, y + 1, 0);
		blit(t, x + 2, y + 2, 0);
	}
	
	SDL_SetTextureColorMod(t, c.r, c.g, c.b);

	blit(t, x, y, 0);
}

static void drawTextSplit(int x, int y, int size, int align, SDL_Color c, char *text)
{
	char drawTextBuffer[MAX_DESCRIPTION_LENGTH];
	char *token;
	int w, h, currentWidth;
	
	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));
	
	token = strtok(text, " ");
	
	currentWidth = 0;
	
	while (token)
	{
		textSize(token, size, &w, &h);
		
		if (currentWidth + w > maxWidth)
		{
			drawTextNormal(x, y, size, align, c, drawTextBuffer);
			
			currentWidth = 0;
			y += h;
			memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));
		}
		
		strcat(drawTextBuffer, token);
		strcat(drawTextBuffer, " ");
		
		currentWidth += w;
		
		token = strtok(NULL, " ");
	}
	
	drawTextNormal(x, y, size, align, c, drawTextBuffer);
}

int getWrappedTextHeight(const char *text, int size)
{
	char textBuffer[MAX_DESCRIPTION_LENGTH];
	char *token;
	int w, h, currentWidth;
	int y;
	
	STRNCPY(textBuffer, text, MAX_DESCRIPTION_LENGTH);
	
	token = strtok(textBuffer, " ");
	
	y = 0;
	currentWidth = 0;
	
	while (token)
	{
		textSize(token, size, &w, &h);
		
		if (currentWidth + w > maxWidth)
		{
			currentWidth = 0;
			y += h;
		}
		
		currentWidth += w;
		
		token = strtok(NULL, " ");
	}
	
	return y + h;
}

void textSize(const char *text, int size, int *w, int *h)
{
	if (!font[size])
	{
		loadFont(size);
	}
	
	TTF_SizeText(font[size], text, w, h);
}

void limitTextWidth(int width)
{
	maxWidth = width;
}

void useTextShadow(int enable, int r, int g, int b)
{
	textShadow = 1;
	textShadowColor.r = r;
	textShadowColor.g = g;
	textShadowColor.b = b;
}

static SDL_Texture *getCachedText(unsigned long hash)
{
	Texture *t;
	int i;

	i = hash % NUM_TEXT_BUCKETS;

	t = textures[i].next;

	for (t = textures[i].next ; t != NULL ; t = t->next)
	{
		if (t->hash == hash)
		{
			t->ttl = SDL_GetTicks() + TEXT_TTL;
			return t->texture;
		}
	}

	return NULL;
}

static void cacheText(unsigned long hash, SDL_Texture *texture)
{
	Texture *t, *new;
	int i;

	i = hash % NUM_TEXT_BUCKETS;

	t = &textures[i];

	/* horrible bit to find the tail */
	while (t->next)
	{
		t = t->next;
	}

	new = malloc(sizeof(Texture));
	memset(new, 0, sizeof(Texture));

	new->hash = hash;
	new->texture = texture;
	new->ttl = SDL_GetTicks() + TEXT_TTL;

	t->next = new;
	
	cacheSize++;
}

void expireTexts(int all)
{
	Texture *t, *prev;
	int i, n;
	long now;
	
	n = 0;
	now = SDL_GetTicks();

	for (i = 0 ; i < NUM_TEXT_BUCKETS ; i++)
	{
		prev = &textures[i];
		
		for (t = textures[i].next ; t != NULL ; t = t->next)
		{
			if (t->ttl <= now || all)
			{
				prev->next = t->next;
				SDL_DestroyTexture(t->texture);
				free(t);
				
				cacheSize--;
				
				n++;
				
				t = prev;
			}
			
			prev = t;
		}
	}
	
	if (n > 0)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Expired %d texts", n);
	}
}

static void loadFont(int size)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "loadFonts(%d)", size);
	
	font[size] = TTF_OpenFont(getFileLocation("gfx/fonts/Roboto-Medium.ttf"), size);
}

void destroyFonts(void)
{
	int i;

	for (i = 0 ; i < MAX_FONTS ; i++)
	{
		if (font[i])
		{
			TTF_CloseFont(font[i]);
		}
	}
}
