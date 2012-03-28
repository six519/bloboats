/*
    Bloboats - a boat racing game by Blobtrox
    Copyright (C) 2006  Markus "MakeGho" Kettunen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "graphics.h"
#include "SDL.h"
#include <iostream>

#include "config.h"

#include "compiling_settings.h"

using namespace std;


extern window Window;
extern config Config;

graphics::graphics(){
}

graphics::~graphics(){}

SDL_Surface * graphics::LoadPicture(char *file)
{
	SDL_Surface *picture;
	picture=IMG_Load(file);
	if (!picture) {
		fprintf(stderr, "Couldn't load file \"%s\" .. \n", file);
		exit (1);
	}

	SDL_Surface *newpic;
	newpic = SDL_DisplayFormatAlpha(picture);
	if (newpic==NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}

	SDL_FreeSurface(picture);

#if DEBUG == 1
	fprintf (stderr, "Loaded file \"%s\" .. \n", file);
#endif

	return newpic;
}

void graphics::DrawIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, destsurface, &dest);
}

void graphics::DrawPartOfIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y, int w, int h, int x2, int y2)
{
	SDL_Rect dest;
	SDL_Rect dest2;
	dest.x = x;
	dest.y = y;
	dest2.x = x2;
	dest2.y = y2;
	dest2.w = w;
	dest2.h = h;
	SDL_BlitSurface(img, &dest2, destsurface, &dest);
}

void graphics::SetTransparentColor(SDL_Surface *image, Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, MapRGB(image, r, g, b));
}

void graphics::RemoveTransparentColor(SDL_Surface *image, Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetColorKey(image, 0, 0);
}

Uint32 graphics::MapRGB(SDL_Surface *image, Uint8 r, Uint8 g, Uint8 b) {
	return SDL_MapRGB(image->format, r, g, b);
}

void graphics::GetRGB(Uint32 pixel, SDL_PixelFormat *fmt, Uint8 *r, Uint8 *g, Uint8 *b) {
	return SDL_GetRGB(pixel, fmt, r, g, b);
}

void graphics::PutPixel(SDL_Surface *image, Uint32 c, int x, int y) {
	if (x>=0 && x<image->w && y >= 0 && y<image->h) {
		*((Uint32 *)image->pixels + y*image->w + x) = c;
	}
}

void graphics::PutPixel(SDL_Surface *image, Uint32 c, Uint32 p,int x, int y) {
	if (x>=0 && x<image->w && p>=0 && p < image->w*image->h) {
		*((Uint32 *)image->pixels + p) = c;
	}
}

void graphics::DrawLine(float r, float g, float b, int x1, int y1, int x2, int y2) {
	glDisable(GL_TEXTURE_2D);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
}

void graphics::DrawTextured(GLuint texID, float x1, float y1, float x2, float y2, float x3, float y3,
float tx1, float ty1, float tx2, float ty2, float tx3, float ty3) {

	if (Config.decoration != DEC_UGLY) {

		glBindTexture(GL_TEXTURE_2D, texID);
		glBegin(GL_TRIANGLES);

		glTexCoord2f(tx1, ty1);
		glVertex2f(x1, y1);

		glTexCoord2f(tx2, ty2);
		glVertex2f(x2, y2);

		glTexCoord2f(tx3, ty3);
		glVertex2f(x3, y3);

		glEnd();

	} else {
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y1);
		glVertex2f(x3, y3);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);

		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

}

/*
glBindTexture(GL_TEXTURE_2D, texID);
glBegin(GL_TRIANGLES);
glEnd();
*/

void graphics::DrawTextured(float x1, float y1, float x2, float y2, float x3, float y3,
float tx1, float ty1, float tx2, float ty2, float tx3, float ty3) {

	glTexCoord2f(tx1, ty1);
	glVertex2f(x1, y1);

	glTexCoord2f(tx2, ty2);
	glVertex2f(x2, y2);

	glTexCoord2f(tx3, ty3);
	glVertex2f(x3, y3);
}

void graphics::DrawSolid(float x1, float y1, float x2, float y2, float x3, float y3) {
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
}

void graphics::OutlineTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x3, y3);
	glVertex2f(x1, y1);
}


int graphics::projectx(double x) {
	return (int)(Window.width*(x-Window.centerx)/Window.showx) + Window.width/2;
}

int graphics::projecty(double y) {
	return (int)(Window.height*(-y+Window.centery)/Window.showy) + Window.height/2;
}

double graphics::backprojectx(int x) {
	return (x - Window.width/2)*Window.showx/Window.width+Window.centerx;
}

double graphics::backprojecty(int y) {
	return (Window.height/2 - y)*Window.showy/Window.height+Window.centery;
}

GLuint graphics::maketexture(char *filename) {
	GLuint texID;
	SDL_Surface *s = LoadPicture(filename);

// Swap bytes
#ifdef __BIG_ENDIAN__
	for (Uint32 *p = (Uint32*)(s->pixels); p < (Uint32*)(s->pixels)+s->w*s->h; p++) {
		*p = ((*p&0xff000000)>>24)|((*p&0x00ff0000)>>8)|((*p&0x0000ff00)<<8)|((*p&0x000000ff)<<24);
	}
#endif

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, s->w, s->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	SDL_FreeSurface(s);

	surfacelist.push_back(texfile(filename, texID));

	return texID;
}



GLuint graphics::remaketexture(char *filename) {
	GLuint texID;
	SDL_Surface *s = LoadPicture(filename);

// Swap bytes
#ifdef __BIG_ENDIAN__
	for (Uint32 *p = (Uint32*)(s->pixels); p < (Uint32*)(s->pixels)+s->w*s->h; p++) {
		*p = ((*p&0xff000000)>>24)|((*p&0x00ff0000)>>8)|((*p&0x0000ff00)<<8)|((*p&0x000000ff)<<24);
	}
#endif

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, s->w, s->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	SDL_FreeSurface(s);

	return texID;
}



void graphics::deletetexture(GLuint tex) {
	std::list<texfile>::iterator it = surfacelist.begin();

	// delete current entry from the list
	for (; it != surfacelist.end(); it++) {
		if (it->id == tex) {
			surfacelist.erase(it);
			break;
		}
	}

	glDeleteTextures(1, &tex);
}

void graphics::reloadtextures() {
	std::list<texfile>::iterator it;

	// remove all
	for (it = surfacelist.begin(); it != surfacelist.end(); it++) {
		glDeleteTextures(1, &it->id);
		remaketexture( (char*)it->fname.c_str() );
	}

}

void graphics::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();

	glTranslatef(0, Window.height, 0);
	glScalef(1, -1, 1);
}
