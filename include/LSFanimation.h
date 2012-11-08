#ifndef LSFANIMATION_H_
#define LSFANIMATION_H_
#include "LSFvertex.h"
#include <vector>
class LSFanimation{
	protected:
		vector<LSFvertex> controlPoints; /* the animation control points */
		double totalTime; /* the total time of the animation */
		double totalPathLen; /* the length of the complete path */
		vector<LSFvertex> pathVelocity; /* the unit velocity vectors correspondent to each section v=x/t */
		vector<LSFvertex> pathDisplacement;
		vector<double> pathTime;
		vector<double> pathDistance;
	public:
		LSFanimation(vector<LSFvertex> controlPoints, double totalTime);
		LSFvertex getDisplacementAt(double elapsedTime);
		LSFvertex getRotationAt(double elapsedTime);
		int getPathAt(double &elapsedTime);

};


#endif
