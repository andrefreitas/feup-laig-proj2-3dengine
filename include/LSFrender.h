/****************************************************************************
 * Author:      - Andr� Freitas, p.andrefreitas@gmail.com
 * Author:      - Paulo Ara�jo, paulojmaraujo@gmail.com
 * Copyright:   - 14/10/2012, LAIG, FEUP
 ****************************************************************************/
#ifndef LSFRENDER_H_
#define LSFRENDER_H_
#include <map>
#include <string>
#include "LSFobjects.h"
#include "CGFapplication.h"
#include <stack>
#include "LSFanimation.h"
/**
 * LSFrender is a class that receives all the scene objects and render it in OPENGL
 */
class LSFrender{
	public:
		static void render(map<string,LSFnode*> &nodes,string &rootNode,map<string,LSFappearance*> appearances,stack<LSFappearance*> &appearancesStack,map<string,LSFanimation*> animations, double timeSeconds);
};
#endif
