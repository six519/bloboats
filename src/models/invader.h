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

#ifndef _INVADER_H_
#define _INVADER_H_

#include "../model.h"
#include "../wall.h"

#define INVADER_SPLASH 2

//const int invader_splash[INVADER_SPLASH]={12, 26};
//const int invader_bendr[INVADER_BENDR]={};
//const int invader_update[INVADER_UPDATE]={};

//const int invader_strive[INVADER_STRIVE]={};
//const int invader_stretch[INVADER_STRETCH]={
//22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};


class invader : public model {
public:
	invader(double cx, double cy, double angle, double scale, char *tex);
	~invader();

	void bendleft(double dt);
	void bendright(double dt);

	void stretchup(double dt);
	void stretchdown(double dt);

	void strive(double dt);

	void update(double dt);

	float getdamage();
	float getwaterdamage();

	void updatewalls();
	bool checkwalls(vec mp);

	void display();


	double a_bend;
	double a_stretch;

	double a_strive;
	bool striven;

	wall walls[15];

	double minx, maxx;

	int dir;

private:

};

#endif
