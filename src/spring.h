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

#ifndef _SPRING_H_
#define _SPRING_H_

#include "graphics.h"

#include "vec.h"
#include "particle.h"


class spring {
public:

	spring();
	spring(particle *p1, particle *p2, double nlen, double maxdiff, double a, double damp);

	void act(double dt);

	void display(float r, float g, float b);

	void normlen_reset();
	void normlen_modify(double k);


	bool alive; // if false, we don't operate anymore

	particle *p1;
	particle *p2;
	double nlen; // normal length
	double maxdiff; // spring breaks if len>nlen*maxdiff or len<nlen/maxdiff;
	double a; // spring constant

	double origlen; // original normal length used to alter nlen.
	double damp;

	double edamp;

};


#endif
