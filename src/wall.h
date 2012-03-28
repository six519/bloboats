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

#ifndef _WALL_H_
#define _WALL_H_

#include "SDL.h"
#include "SDL_opengl.h"

#include "vec.h"
#include "graphics.h"
#include "window.h"


#define WALL_ONWALL_DIST 0.05

#define WALL_TYPES 3

#define WALL_DEFAULT 0
#define WALL_GROUND 1
#define WALL_ICE 2

class wall {
public:
	wall();
	wall(GLuint texID, vec oa, vec ob, vec oc);

	void seticetexture(GLuint tex);
	void setgroundtexture(GLuint tex);

	void displayground();
	void displayground_solid();

	void displayedges();

	void drawedge(GLuint tex, vec OA, vec AB, double AB_LEN, double F_AB);

	bool max_midedge(vec &mp, float &r);

	vec ab, ac, bc, centerab, centerac, centerbc, ab_hat, ac_hat, bc_hat;
	vec oa, ob, oc;

	double ab_x_ac;
	double ab_x_ac_inv;


	double ab_len2, ac_len2, bc_len2;

	double ab_lenp2, ac_lenp2, bc_lenp2;
	double ab_lenp2_2, ac_lenp2_2, bc_lenp2_2;

	double ab_len, ac_len, bc_len;


	vec mp;
	double r2;
	float r;

	GLuint texID;
	bool tex;

	GLuint groundID;
	bool groundtex;

	GLuint iceID;
	bool icetex;

	int type_ab, type_ac, type_bc;
	double f_ab, f_ac, f_bc;

	bool alive;
};

#endif
