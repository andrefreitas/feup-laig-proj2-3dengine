#include "LSFprimitive.h"

using namespace std;

LSFprimitive::LSFprimitive(PrimitiveType type):type(type){
	compute = GL_FILL;
	attr["order"] = 1;
	attr["partsU"] = 2;
	attr["partsV"] = 2;
}

void LSFprimitive::createEvaluator(GLfloat *ctrlpoints, GLfloat *nrmlcompon = NULL, GLfloat *textpoints = NULL,
                                   GLfloat *colorpoints = NULL, int startU = 0, int startV = 0){
	float u,v;
	u=1/(float)appearance->length_s;
	v=1/(float)appearance->length_t;
	int partsU, partsV;

	if(type == plane){
		partsU = partsV = attr["parts"];
	}
	else{
		partsU = attr["partsU"];
		partsV = attr["partsV"];
	}

	if(nrmlcompon == NULL) glFrontFace(GL_CW);

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, (attr["order"]+1),
			                  0.0, 1.0, 3*(attr["order"]+1), (attr["order"]+1), ctrlpoints);

	if(textpoints == NULL){
		GLfloat texturespoints[4][2] = {{0.0, 0.0},{u, 0.0},{0.0, v},{u, v}};
		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturespoints[0][0]);
	}
	else
		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, textpoints);

	if(nrmlcompon != NULL)
		glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, (attr["order"]+1),
				                0.0, 1.0, 3*(attr["order"]+1), (attr["order"]+1), nrmlcompon);

	if(colorpoints != NULL)
		glMap2f(GL_MAP2_COLOR_4, 0.0, 1.0, 4, (attr["order"]+1),
						         0.0, 1.0, 4*(attr["order"]+1), (attr["order"]+1), colorpoints);
	else
		glColor3f(1.0,1.0,1.0);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	if(nrmlcompon == NULL)
		glEnable(GL_AUTO_NORMAL);
	else
		glEnable(GL_MAP2_NORMAL);

	if(colorpoints != NULL)
		glEnable(GL_MAP2_COLOR_4);

	glMapGrid2f(partsU, 0.0,1, partsV, 0.0,1);
	glEvalMesh2(compute, startU, partsU, startV, partsV);

	if(nrmlcompon == NULL) glFrontFace(GL_CCW);
}

void LSFprimitive::draw(){
	switch(type){
		case rectangle:{
			glNormal3f(0,0,1);
			glBegin(GL_QUADS);
				float width= attr["x2"]-attr["x1"];
				float height= attr["y2"]-attr["y1"];
				float u,v;
				u=width/(float)appearance->length_s;
				v=height/(float)appearance->length_t;
				glTexCoord2d(0.0,0.0); glVertex3d(attr["x1"],attr["y1"],0);
				glTexCoord2d(u,0.0); glVertex3d(attr["x2"],attr["y1"],0);
				glTexCoord2d(u,v); glVertex3d(attr["x2"],attr["y2"],0);
				glTexCoord2d(0.0,v); glVertex3d(attr["x1"],attr["y2"],0);

			glEnd();
		}break;
		case triangle:{
			glNormal3f(normal.x, normal.y, normal.z);
			glBegin(GL_TRIANGLES);

				// Compute the height and width of the triangle
				LSFvertex p1,p2,p3;
				p1=LSFvertex(attr["x1"], attr["y1"], attr["z1"]);
				p2=LSFvertex(attr["x2"], attr["y2"], attr["z2"]);
				p3=LSFvertex(attr["x3"], attr["y3"], attr["z3"]);
				float width=computeNormBetween(p1,p2);
				float sFactor=(width/appearance->length_s);
				float height=computeTriangleHeight(p1,p2,p3);
				float tFactor=(height/appearance->length_t);
				// -->
				glTexCoord2d(0,0); // don't need s and t in the first coord
				glVertex3d(attr["x1"], attr["y1"], attr["z1"]);

				glTexCoord2d(uvCoords[1].x*sFactor, uvCoords[1].y*tFactor);
				glVertex3d(attr["x2"], attr["y2"], attr["z2"]);

				glTexCoord2d(uvCoords[2].x*sFactor, uvCoords[2].y*tFactor);
				glVertex3d(attr["x3"], attr["y3"], attr["z3"]);
			glEnd();
		}break;
		case cylinder:{
			GLUquadric *a=gluNewQuadric();
			gluQuadricNormals(a,GL_SMOOTH);
			gluQuadricTexture(a,GL_TRUE);
			gluCylinder(a, attr["base"], attr["top"], attr["height"], attr["slices"], attr["stacks"]);
		} break;
		case sphere:{
			GLUquadric *a=gluNewQuadric();
			gluQuadricNormals(a,GL_SMOOTH);
			gluQuadricTexture(a,GL_TRUE);
			gluSphere(a, attr["radius"], attr["slices"], attr["stacks"]);
		}break;
		case torus:{

			glutSolidTorus(attr["inner"], attr["outer"], attr["slices"], attr["loops"]);
		} break;
		case patch:{
			createEvaluator(ctrlpoints);
		}break;
		case plane:{
			GLfloat controlpoints[4][3] = {
								{ -0.5, 0, 0.5},{ 0.5, 0, 0.5},
								{-0.5, 0, -0.5},{ 0.5, 0, -0.5}};

			createEvaluator(&controlpoints[0][0]);
		}break;
		case vehicle:{
			attr["order"] = 3;
			attr["partsU"] = 5;
			attr["partsV"] = 5;

			GLfloat bodypoints[16][3] = {
								{0.0, 0.0, 0.0},
								{1.0, 1.0, 0.5},
								{2.0, 1.0, 0.5},
								{3.0, 0.0, 0.0},

								{0.0, 0.0, -1.0},
								{1.0, 1.0, -0.5},
								{2.0, 1.0, -0.5},
								{3.0, 0.0, -1.0},

								{0.0, 0.0, -2.0},
								{1.0, 1.0, -1.5},
								{2.0, 1.0, -1.5},
								{3.0, 0.0, -2.0},

								{0.0, 0.0, -3.0},
								{1.0, 1.0, -2.5},
								{2.0, 1.0, -2.5},
								{3.0, 0.0, -3.0}};
			createEvaluator(&bodypoints[0][0]);
		}break;
	}
}


LSFprimitive::~LSFprimitive() {
	// TODO Auto-generated destructor stub
}

