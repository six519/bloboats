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

#ifndef _MODEL_H_
#define _MODEL_H_

#include <SDL.h>
#include <math.h>
#include <assert.h>

#include "graphics.h"

#include "vec.h"
#include "particle.h"
#include "spring.h"
#include "wall.h"
#include "model_tex.h"

#define ENEMY_TENTACLE 0
#define ENEMY_INVADER 1
#define ENEMY_BOULDER 2
#define ENEMY_TUX 3

class model {
public:
	model(double cx, double cy, double angle, double scale);
	model(double hardness);
	model();
	virtual ~model();

	bool loadmodel(char *filename, double cx, double cy, double angle, double scale, double hardness, double damp);

	bool flip(wall *walls, int numwalls);

	virtual void springs_act(double dt);
	virtual void particles_act(double dt, wall *walls, int numwalls, double t);

	virtual void display ();

	vec midpoint();
	vec midv();

	void momentum(double M, double dt);

	virtual void bendleft(double dt);
	virtual void bendright(double dt);

	virtual void stretchup(double dt);
	virtual void stretchdown(double dt);

	virtual void strive(double dt);
	virtual void duck(double dt);

	virtual void update(double dt);


	virtual void stick(bool onoff);

	virtual void settime(double t);

	virtual bool checkgoal(vec goal, float goalr);

	virtual float getdamage();
	virtual float getwaterdamage();

	virtual void updatewalls();
	virtual bool checkwalls(vec mp);
	
	void precision();

	particle *p;
	spring *s;
	model_tex *t;

	int numparticles;
	int numsprings;
	int numtriangles;


	double hardness;
	double hardness_p;

	double minhardness;
	double maxhardness;

	double time;

	float radius;

	float ugly_r, ugly_g, ugly_b;

	GLuint texID;


	int inwater;


	int type;

private:
	void corrupt(char *filename);

};

#endif
