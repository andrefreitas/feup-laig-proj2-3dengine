#include "LSFrender.h"
#include "LSFobjects.h"
#include <iostream>
#include "LSFvertex.h"
#include "LSFprimitive.h"

using namespace std;
void LSFrender::render(map<string, LSFnode*> &nodes, string &rootNode,
		map<string, LSFappearance*> appearances,
		stack<LSFappearance*> &appearancesStack,map<string,LSFanimation*> animations, double timeSeconds) {

	if (nodes[rootNode] == 0)
		return;

	// Animations
	bool haveAnimation=nodes[rootNode]->animationRef!="none";
	if(haveAnimation){
		glPushMatrix();
		LSFanimation* animationp=animations[nodes[rootNode]->animationRef];
		// if invalid reference
		if (animationp==0) {
			haveAnimation=0;
			glPopMatrix();
			}
		else {
		LSFvertex displacement=animationp->getDisplacementAt(timeSeconds);
		glTranslated(displacement.x,displacement.y,displacement.z);
		}
	}


	if (nodes[rootNode]->isDisplayList) {
		glCallList(nodes[rootNode]->displayList);
		//cout << "\n É Display List!" << rootNode << endl;
		if(haveAnimation) glPopMatrix();

		return;
	}
	//cout << "\n Não era Display List!" << endl;

	// Transforms
	glPushMatrix();
	glMultMatrixf(nodes[rootNode]->transformMatrix);

	// Appearances
	LSFappearance *currentAppearance;
	if (nodes[rootNode]->appearance == "inherit")
		currentAppearance = appearancesStack.top();
	else
		currentAppearance = appearances[nodes[rootNode]->appearance];
	appearancesStack.push(currentAppearance);
	glMaterialfv(GL_EMISSION, GL_FRONT_AND_BACK, currentAppearance->emissive);
	currentAppearance->appearance->apply();

	// Process the primitives
	for (int unsigned i = 0; i < nodes[rootNode]->childPrimitives.size(); i++) {
		LSFprimitive primitive;
		primitive.draw(nodes[rootNode]->childPrimitives[i], currentAppearance);
	}

	// Process the noderefs
	for (int unsigned i = 0; i < nodes[rootNode]->childNoderefs.size(); i++)
		render(nodes, nodes[rootNode]->childNoderefs[i], appearances,appearancesStack,animations,timeSeconds);

	appearancesStack.pop();
	glPopMatrix();

	// End Animation
	if(haveAnimation){
		glPopMatrix();
	}
}
