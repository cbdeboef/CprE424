#include "quad.h"
#include <math.h>
#include <stdio.h>

void quad_angle(quad q){

	// Declare variables	
	double x[4];
        double y[4];

        x[0] = q.node1.x;
        x[1] = q.node2.x;
        x[2] = q.node3.x;
        x[3] = q.node4.x;

        y[0] = q.node1.y;
        y[1] = q.node2.y;
        y[2] = q.node3.y;
        y[3] = q.node4.y;

	// Find lengths between each point on quad
        double AB = sqrt(pow((x[0]-x[1]),2)+pow((y[0]-y[1]),2));
        double BC = sqrt(pow((x[1]-x[2]),2)+pow((y[1]-y[2]),2));
        double CD = sqrt(pow((x[2]-x[3]),2)+pow((y[2]-y[3]),2));
        double DA = sqrt(pow((x[3]-x[0]),2)+pow((y[3]-y[0]),2));
	double AC = sqrt(pow((x[0]-x[2]),2)+pow((y[0]-y[2]),2));
	double BD = sqrt(pow((x[1]-x[3]),2)+pow((y[1]-y[3]),2));
	
	// Apply law of cosines to each angle on the quad
	double a = acos((pow(AB,2) + pow(DA,2) - pow(BD,2)) / (2 * AB * DA));
	double b = acos((pow(BC,2) + pow(AB,2) - pow(AC,2)) / (2 * BC * AB));
	double c = acos((pow(CD,2) + pow(BC,2) - pow(BD,2)) / (2 * CD * BC));
	double d = acos((pow(DA,2) + pow(CD,2) - pow(AC,2)) / (2 * DA * CD));
	
	// Print out each angle and the sum, which should be 2*Pi
	printf("\nangle 1 is %lf, angle 2 is %lf, angle 3 is %lf, angle 4 is %lf, and the total of all angles is %lf\n",a,b,c,d,a+b+c+d);
}
