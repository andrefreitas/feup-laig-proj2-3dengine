#include "CGFapplication.h"
#include "LSFprimitive.h"
#include <iostream>
using namespace std;
LSFprimitive::LSFprimitive() {

}

void LSFprimitive::draw(Primitive primitive, LSFappearance *currentAppearance){
	switch(primitive.type){
		case rectangle:{
			glNormal3f(0,0,1);
			glBegin(GL_QUADS);
				float width=primitive.attr["x2"]-primitive.attr["x1"];
				float height=primitive.attr["y2"]-primitive.attr["y1"];
				float u,v;
				u=width/(float)currentAppearance->length_s;
				v=height/(float)currentAppearance->length_t;
				glTexCoord2d(0.0,0.0); glVertex3d(primitive.attr["x1"],primitive.attr["y1"],0);
				glTexCoord2d(u,0.0); glVertex3d(primitive.attr["x2"],primitive.attr["y1"],0);
				glTexCoord2d(u,v); glVertex3d(primitive.attr["x2"],primitive.attr["y2"],0);
				glTexCoord2d(0.0,v); glVertex3d(primitive.attr["x1"],primitive.attr["y2"],0);

			glEnd();
		}break;
		case triangle:{
			glNormal3f(primitive.normal.x,primitive.normal.y,primitive.normal.z);
			glBegin(GL_TRIANGLES);

				// Compute the height and width of the triangle
				LSFvertex p1,p2,p3;
				p1=LSFvertex(primitive.attr["x1"],primitive.attr["y1"],primitive.attr["z1"]);
				p2=LSFvertex(primitive.attr["x2"],primitive.attr["y2"],primitive.attr["z2"]);
				p3=LSFvertex(primitive.attr["x3"],primitive.attr["y3"],primitive.attr["z3"]);
				float width=computeNormBetween(p1,p2);
				float sFactor=(width/currentAppearance->length_s);
				float height=computeTriangleHeight(p1,p2,p3);
				float tFactor=(height/currentAppearance->length_t);
				// -->
				glTexCoord2d(0,0); // don't need s and t in the first coord
				glVertex3d(primitive.attr["x1"],primitive.attr["y1"],primitive.attr["z1"]);

				glTexCoord2d(primitive.uvCoords[1].x*sFactor,primitive.uvCoords[1].y*tFactor);
				glVertex3d(primitive.attr["x2"],primitive.attr["y2"],primitive.attr["z2"]);

				glTexCoord2d(primitive.uvCoords[2].x*sFactor,primitive.uvCoords[2].y*tFactor);
				glVertex3d(primitive.attr["x3"],primitive.attr["y3"],primitive.attr["z3"]);
			glEnd();
		}break;
		case cylinder:{
			GLUquadric *a=gluNewQuadric();
			gluQuadricNormals(a,GL_SMOOTH);
			gluQuadricTexture(a,GL_TRUE);
			gluCylinder(a, primitive.attr["base"], primitive.attr["top"], primitive.attr["height"], primitive.attr["slices"], primitive.attr["stacks"]);
		} break;
		case sphere:{
			GLUquadric *a=gluNewQuadric();
			gluQuadricNormals(a,GL_SMOOTH);
			gluQuadricTexture(a,GL_TRUE);
			gluSphere(a,primitive.attr["radius"],primitive.attr["slices"],primitive.attr["stacks"]);
		}break;
		case torus:{

			glutSolidTorus(primitive.attr["inner"],primitive.attr["outer"],primitive.attr["slices"],primitive.attr["loops"]);
		} break;
		case patch:{

		}
		case plane:{
			GLfloat ctrlpoints[4][3] = {
								{ -0.5, 0, 0.5},
								{-0.5, 0, -0.5},
								{ 0.5, 0, 0.5}, 
								{ 0.5, 0, -0.5}};
			float u,v;
			u=1/(float)currentAppearance->length_s;
			v=1/(float)currentAppearance->length_t;
			GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
											{ 0.0, v},
											{ u, 0.0},
											{ u, v} };

			//glEnable(GL_AUTO_NORMAL);
			glNormal3f(0,1,0);
			glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
			glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

			// Interpolators
			glEnable(GL_MAP2_VERTEX_3);
			glEnable(GL_MAP2_TEXTURE_COORD_2);

			glMapGrid2f(primitive.attr["parts"], 0.0,1, primitive.attr["parts"], 0.0,1); 


			glEvalMesh2(GL_FILL, 0,primitive.attr["parts"], 0,primitive.attr["parts"]);

		}break;
	}
}


LSFprimitive::~LSFprimitive() {
	// TODO Auto-generated destructor stub
}

