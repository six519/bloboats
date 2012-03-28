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

#ifndef _PAATTI_H_
#define _PAATTI_H_

#include "../model.h"

#define PAATTI_SPLASH 2
#define PAATTI_TOUCHPOINTS 20

const int paatti_splash[PAATTI_SPLASH]={12, 26};
const int paatti_tp[PAATTI_TOUCHPOINTS]={0,1,2,4,6,12,15,18,19,20,24,28,27,26,25,21,11,10,9,8};


class paatti : public model {
public:
	paatti(double cx, double cy, double angle, double scale, char *tex);
	~paatti();

	void update(double dt);

	float getdamage();
	float getwaterdamage();

	
	void bendleft(double dt);
	void bendright(double dt);

	void stretchup(double dt);
	void stretchdown(double dt);

	void strive(double dt);



	double a_bend;
	double a_stretch;

	double a_strive;
	bool striven;

private:
};

#endif
