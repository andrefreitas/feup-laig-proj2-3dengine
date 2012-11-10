#include "LSFrender.h"
#include "LSFobjects.h"
#include <iostream>
#include "LSFvertex.h"
#include "LSFnode.h"
#include "LSFprimitive.h"

using namespace std;
void LSFrender::render(map<string, LSFnode*> &nodes, string &rootNode,
		map<string, LSFappearance*> appearances,
		stack<LSFappearance*> &appearancesStack) {

	if (nodes[rootNode] == 0)
		return;
	if (nodes[rootNode]->isDisplayList) {
		glCallList(nodes[rootNode]->displayList);
		//cout << "\n É Display List!" << rootNode << endl;
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
		LSFprimitive primitive(nodes[rootNode]->childPrimitives[i]);
		primitive.appearance = currentAppearance;
		primitive.draw();
	}

	// Process the noderefs
	for (int unsigned i = 0; i < nodes[rootNode]->childNoderefs.size(); i++)
		render(nodes, nodes[rootNode]->childNoderefs[i], appearances,appearancesStack);

	appearancesStack.pop();
	glPopMatrix();

}
