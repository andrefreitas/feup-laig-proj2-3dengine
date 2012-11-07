/****************************************************************************
 * Author:      - André Freitas, p.andrefreitas@gmail.com
 * Author:      - Paulo Araújo, paulojmaraujo@gmail.com
 * Copyright:   - 14/10/2012, LAIG, FEUP
 *****************************************************************************
 * This header defines all the possible primitives. We are
 * keeping the code "simple and sincere" and easy to change.
 ****************************************************************************/

#include "LSFobjects.h"

#ifndef LSFPRIMITIVE_H_
#define LSFPRIMITIVE_H_

class LSFprimitive {
public:
	LSFprimitive();
	void draw(Primitive primitive, LSFappearance *currentAppearance);
	virtual ~LSFprimitive();
};

#endif /* LSFPRIMITIVE_H_ */
