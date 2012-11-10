/****************************************************************************
 * Author:      - André Freitas, p.andrefreitas@gmail.com
 * Author:      - Paulo Araújo, paulojmaraujo@gmail.com
 * Copyright:   - 14/10/2012, LAIG, FEUP
 *****************************************************************************
 * This header defines all the possible primitives. We are
 * keeping the code "simple and sincere" and easy to change.
 ****************************************************************************/

#ifndef LSFPRIMITIVE_H_
#define LSFPRIMITIVE_H_

#include <iostream>
#include "LSFobjects.h"
#include "LSFvertex.h"

enum PrimitiveType{ rectangle,triangle,cylinder,sphere,torus,plane, patch, vehicle};
class LSFprimitive{
public:
	GLfloat *ctrlpoints;
	GLfloat *nrmlcompon;
	GLfloat *textpoints;
	GLfloat *colorpoints;

	LSFappearance *appearance;
	PrimitiveType type;
	map<string,float> attr;
	GLenum compute;
	LSFvertex normal;
	vector<LSFvertex> uvCoords;

	LSFprimitive(PrimitiveType type);
	void createEvaluator(GLfloat *ctrlpoints, GLfloat *nrmlcompon, GLfloat *textpoints,
			             GLfloat *colorpoints, int startU, int startV);
	void draw();
	virtual ~LSFprimitive();
};

#endif /* LSFPRIMITIVE_H_ */
