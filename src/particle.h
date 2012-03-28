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

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vec.h"
#include "wall.h"

#include "graphics.h"
#include "window.h"

#define BOUNCE_EPSILON 0.01  // m/s

class particle {
public:
	particle();
	particle(vec p, vec v, double mass, double g, double bfactor); // location, velocity, mass, gravitation, bounce factor

	void set(vec p, vec v);

	void act(double dt, wall **walls, int numwalls); // delta time

	void display(double r, double g, double b);

	void detectcollision (double dt, vec &p, vec &v, wall **walls, int numwalls, int *nearestwall);
	int detectcollision (double dt, vec &p, vec &v, wall *walls);
	int detectcollision_nov (vec &p, wall *walls); // no velocity

	bool is_onwall(vec &centerab, vec &ab, vec &ab_hat, double lenp2); 

	double t_to_edge(vec AP, vec V, vec AB, double ABxAP, double VxAB);


	vec  p, v;
	double mass, g, bfactor;
	int onwall;

	bool alive;

	bool sticky;
	bool immobile;

	float damage;
	bool inwater;

	bool cheatmode;

private:


};

#endif
