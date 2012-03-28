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

#include "level.h"

#include "water.h"
#include "compat.h"


#include "path.h"

extern path *Path;

extern graphics Graphics;
extern window Window;
extern config Config;
extern water Water;

level::level(char *filename, double cx, double cy, double angle, double scale, char *tex) {
	if (!loadlevel(filename, cx, cy, angle, scale, tex)) {
		fprintf (stderr, "Error in loading file \"%s\"! Critical!\n", filename);
		fprintf (stderr, "Örr.\n");
		exit(1);
	}
	waterheight=0;
}

level::level(FILE *fp, char *tex) {
	if (!loadlevel(fp, tex)) {
		fprintf (stderr, "Error in loading level!\n");
		exit(1);
	}
	waterheight=0;
}

level::level() {
}

level::~level() {
	Graphics.deletetexture(texID);
	delete[] w;
}

bool level::loadlevel(char *filename, double cx, double cy, double angle, double scale, char *tex) {
	// loads the level (surprise!)

	texID = Graphics.maketexture( Path->data(tex) );

	FILE *fp = fopen( Path->data(filename), "r");

	if (!fp) {
		fprintf(stderr, "Can't open file \"%s\"!\n", Path->data(filename) );
		return false;
	}

	// read number of vertices and number of edges
	int numvertices;
	if ( fscanf(fp, "%d %d\n", &numvertices, &numwalls) != 2) {
		fprintf(stderr, "Corrupted file!\n");
		return false;
	}

	// let maximum number of vertices be 10000
	if (numvertices < 0 || numvertices >= 10000) {
		fprintf (stderr, "Number of vertices in \"%s\" isn't clever.\n", filename);
		return false;
	}

	// let maximum number of edges be 10000
	if (numwalls < 0 || numwalls >= 10000) {
		fprintf (stderr, "Number of edges in \"%s\" isn't clever.\n", filename);
		return false;
	}

	vec *verts = new vec[numvertices];
	if (!verts) {
		fprintf(stderr, "Couldn't get memory!\n");
		return false;
	}

	w = new wall[numwalls];
	if (!w) {
		fprintf(stderr, "Couldn't get memory!\n");
		return false;
	}

	double cosx = cos(angle);
	double sinx = sin(angle);

	// read vertices

	for (int i=0; i<numvertices; i++) {
		verts[i] = vec(0,0);

		float x, y;
		if (fscanf(fp, "%f %f\n", &x, &y)!=2) {
			fprintf (stderr, "Corrupted file!\n");
			return false;
		}

		verts[i].x = x;
		verts[i].y = y;

		verts[i].rotate(cosx, sinx);

		verts[i] += vec(cx, cy);

		verts[i]*=scale;
	}

	for (int i=0; i<numwalls; i++) {
		int a, b, c;
		if (fscanf(fp, "%d %d %d\n", &a, &b, &c)!=3) {
			fprintf (stderr, "Corrupted file! (i=%d)\n", i);
			return false;
		}
		if (a>=0 && b>=0 && c>=0 && a<numvertices && b<numvertices && c<numvertices) {
			w[i] = wall( texID, verts[a], verts[b], verts[c] );
		} else {
			fprintf(stderr, "Corrupted file!\n");
			return false;
		}
	}

	delete[] verts;

	fclose(fp);

	return true;
}


bool level::loadlevel(FILE *fp, char *tex) {
	texID = Graphics.maketexture( Path->data(tex) );

	compat::FromFile_SInt(fp, &numwalls);

	w = new wall[numwalls];

	if (!w) {
		fprintf(stderr, "Couldn't get memory!\n");
		return false;
	}

	for (int i=0; i<numwalls; i++) {
		float ax, ay, bx, by, cx, cy;

		compat::FromFile_Float(fp, &ax);
		compat::FromFile_Float(fp, &ay);
		compat::FromFile_Float(fp, &bx);
		compat::FromFile_Float(fp, &by);
		compat::FromFile_Float(fp, &cx);
		compat::FromFile_Float(fp, &cy);

		w[i] = wall( texID, vec(ax,ay), vec(bx,by), vec(cx,cy) );

	}

	return true;
}


void level::savelevel(FILE *fp) {
	compat::ToFile_SInt(fp, numwalls);

	for (int i=0; i<numwalls; i++) {
		compat::ToFile_Float(fp, w[i].oa.x);
		compat::ToFile_Float(fp, w[i].oa.y);
		compat::ToFile_Float(fp, w[i].ob.x);
		compat::ToFile_Float(fp, w[i].ob.y);
		compat::ToFile_Float(fp, w[i].oc.x);
		compat::ToFile_Float(fp, w[i].oc.y);
	}

}

void level::display() {

	glDisable(GL_TEXTURE_2D);

	if (Config.decoration != DEC_UGLY) {
		if (Config.decoration == DEC_LOW) {
			glDisable(GL_BLEND);
			glColor3f(0.4, 0.4, 1.0);
		} else {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.4, 0.4, 1.0, 0.8);
		}

		glBegin(GL_LINES);

		for (int x=0; x<=Window.width; x++) {
			double wx = Graphics.backprojectx(x);
			int y = Graphics.projecty( Water.w(wx) );
			if (y<=Window.height) {
				glVertex2f(x, y);
				glVertex2f(x, Window.height);
			}
		}

		glEnd();

		if (Config.decoration == DEC_LOW) {
			glColor3f(0.85,0.68,0.26);
			glBegin(GL_TRIANGLES);
			for (int i=0; i<numwalls; i++) {
				w[i].displayground_solid();
			}
			glEnd();
	
			glColor3f(1.0,1.0,1.0);
	
			glEnable(GL_TEXTURE_2D);
		} else {
			// display ground texture
	
			glColor4f(1.0,1.0,1.0,1.0);
			glDisable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);

			if (numwalls > 0) {
	
				GLuint tex = w[0].texID;
	
				glBindTexture(GL_TEXTURE_2D, w[0].texID);
				glBegin(GL_TRIANGLES);
		
				w[0].displayground();
		
				for (int i=1; i<numwalls; i++) {
					if (w[i].texID != tex) {
						tex = w[i].texID;
						glBindTexture(GL_TEXTURE_2D, tex);
					}
					w[i].displayground();
				}
		
				glEnd();
			}
	
		}

	} else { // ugly-mode
 
		glDisable(GL_BLEND);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);

		int nx=0;
		int ny = Graphics.projecty(Water.w(Graphics.backprojectx(nx)));
		glVertex2d(nx, ny);
		
		for (int i=0; i<20; i++) {
			nx += Window.width/20;
			ny = Graphics.projecty(Water.w(Graphics.backprojectx(nx)));
			glVertex2d(nx, ny);
			glVertex2d(nx, ny);
		}

		glVertex2d( Window.xlast, Graphics.projecty(Water.w(Graphics.backprojectx(Window.xlast))) );

		glEnd();

		glColor3f( 1.0, 1.0, 1.0 );

	}


	for (int i=0; i < numwalls; i++) {
		w[i].displayedges();
	}

	if (Config.decoration == DEC_UGLY) glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
}

