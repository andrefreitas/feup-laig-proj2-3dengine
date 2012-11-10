/****************************************************************************
 * Author:      - Andr� Freitas, p.andrefreitas@gmail.com
 * Author:      - Paulo Ara�jo, paulojmaraujo@gmail.com
 * Copyright:   - 14/10/2012, LAIG, FEUP
 *****************************************************************************
 * This header defines all the possible objects in the LSF scene. We are
 * keeping the code "simple and sincere" and easy to change.
 ****************************************************************************/
#ifndef LSFNODE_H
#define LSFNODE_H

#include <map>
#include <string>
#include <CGFappearance.h>
#include "CGFlight.h"
#include "CGFcamera.h"
#include "LSFvertex.h"

/**
 * Primitive: a class for holding all existing primitives
 * OOP is not necessary because we have a map that is for the attributes
 */
enum PrimitiveType{ rectangle,triangle,cylinder,sphere,torus,plane, patch};
class Primitive{
	public:
		PrimitiveType type;
		map<string,float> attr;
		GLfloat *controlPoints;
		GLenum compute;
		LSFvertex normal;
		vector<LSFvertex> uvCoords;
		Primitive(PrimitiveType type):type(type){};
};

/**
 * Transform a class for holding all existing transformations
 * OOP is not necessary because we have a map that is for the attributes
 */
enum TransformType{ translate,rotateX,rotateY,rotateZ,scale};
class Transform{
	public:
	    TransformType type;
		map<string,float> attr;
		Transform(TransformType type):type(type){};

};

/**
 * LSFlight a class to define a light in a scene
 * The supported lights are spotlights and free lights (use isspotLight)
 */
class LSFlight {
	public:
		string id;
		bool enabled;
		bool isspotLight;
		int lightNum;
		int isActivated;
		CGFlight* light;
		float spotExponent;
		float angle;
};

/**
 * LSFcamera, a clas for defining a camera that can be ortho or perspective
 */
class LSFcamera{
	private:
		float position[3]; //= {0.0,0.0,-25.0};
		float target[3]; //= {0.0,0.0,0.0};
		float rotation[3];// = {0.0,0.0,0.0};
		enum CAMERA_MODE { EXAMINE_MODE, WALK_MODE, TARGET_MODE };
		CAMERA_MODE mode;
	public:
		string id;
		string view;
		bool initial;
		float _near, _far, angle;
		float left, right, top, bottom;
		float fromX, fromY, fromZ;
		float toX, toY, toZ;
		int cameraNum;
		int isActivated;

		CGFcamera* camera;

		void setPosition(float x, float y, float z);
		void setTarget(float x, float y, float z);
		void setStartRotation();
		void translate(int axis, float value);
		void updateProjectionMatrix(int width, int height);
		void applyView();
};

/**
 * LSFnode: a class that is for the nodes in the scenegraph
 */
class LSFnode{
	public:
		LSFnode();
		char *id;
		float transformMatrix[16]; // When the node is parsed, the transformations are put in a stack
		string appearance; // Reference to the map of appearances
		vector<Primitive> childPrimitives; // All the basic primitives
		vector<string> childNoderefs; // All the child nodes
		bool isDisplayList;
		int displayList;
		string animationRef;
};
/**
 * LSFappearance is a class that defines and appearance
 */
class LSFappearance{
	public:
		string id;
		float emissive[4];
		float length_s,length_t;
		CGFappearance* appearance;
		bool haveTexture;
};
#endif
