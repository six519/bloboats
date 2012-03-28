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

#ifndef _BOULDER_H_
#define _BOULDER_H_

#include "../model.h"
#include "../wall.h"

#define BOULDER_SPLASH 2

//const int BOULDER_splash[BOULDER_SPLASH]={12, 26};

class boulder : public model {
public:
	boulder(double cx, double cy, double angle, double scale, char *tex);
	~boulder();

	void bendleft(double dt);
	void bendright(double dt);

	void nobend(double dt);

	void stretchup(double dt);
	void stretchdown(double dt);
	void nostretch(double dt);

	void strive(double dt);

	void update(double dt);

	float getdamage();
	float getwaterdamage();

	void updatewalls();
	bool checkwalls(vec mp);

	void display();

	void springs_act(double dt);
	void particles_act(double dt, wall *walls, int numwalls, double t);



	double a_bend;
	double a_stretch;

	double a_strive;
	bool striven;

	int alive;

	wall walls[5];

	bool collided;

private:

};

#endif
