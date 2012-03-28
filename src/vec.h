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

#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>

class vec {
public:
	vec();
	vec(double x, double y);
	vec(const vec &b);
	double abscross(vec &b);
	double cross(vec &b);
	double dot(vec &b);
	double abs();
	double abs2();

	void display();

	void rotate(double cosx, double sinx);

	vec &operator=(const vec& b);

	vec operator+(const vec& b);
	vec &operator+=(const vec& b);

	vec operator-(const vec& b);
	vec &operator-=(const vec& b);

	vec operator*(double b);
	vec &operator*=(double b);

	vec operator/(double b);
	vec &operator/=(double b);

	double x, y;

private:


};


#endif
