/*#include "LSFanimation.h"
#include <iostream>
#include "LSFvertex.h"
using namespace std;
int main() {
	LSFvertex cp1(0, 0, 0);
	LSFvertex cp2(3, 0, 0);
	LSFvertex cp3(6, 0, 0);
	LSFvertex cp4(6, 3, 0);
	LSFvertex cp5(0, 0, 0);

	vector<LSFvertex> cps;
	cps.push_back(cp1);
	cps.push_back(cp2);
	cps.push_back(cp3);
	cps.push_back(cp4);
	cps.push_back(cp5);

	LSFanimation anim(cps, 1);
	double p1 = 1;
	LSFvertex displacement = anim.getDisplacementAt(p1);
	cout << " - r ( " << displacement.x << " , " << displacement.y << " , "
			<< displacement.z << " )\n";

	return 0;
}
*/
