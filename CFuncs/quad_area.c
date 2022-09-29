#include "quad.h"
#include <math.h>

double quad_area(quad q){
	
	// Declare Variables
	double quad_perimeter(quad q);
        double area = 0;

        double x[4];
        double y[4];
	
	// Set x and y coordinates to x and y vectors for ease of understanding
        x[0] = q.node1.x;
        x[1] = q.node2.x;
        x[2] = q.node3.x;
        x[3] = q.node4.x;
        y[0] = q.node1.y;
        y[1] = q.node2.y;
        y[2] = q.node3.y;
        y[3] = q.node4.y;

	// Apply Brahmagupta's formula for area
	double s = quad_perimeter(q) / 2;
	double A = sqrt(pow((x[0]-x[1]),2)+pow((y[0]-y[1]),2));
        double B = sqrt(pow((x[1]-x[2]),2)+pow((y[1]-y[2]),2));
        double C = sqrt(pow((x[2]-x[3]),2)+pow((y[2]-y[3]),2));
        double D = sqrt(pow((x[3]-x[0]),2)+pow((y[3]-y[0]),2));

	area = sqrt((s-A)*(s-B)*(s-C)*(s-D));
 
	// Return the Area
	return area;
}
