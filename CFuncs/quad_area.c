#include "quad.h"
#include <math.h>

void cross(double u[], double v[], double w[]){
	w[0] = u[1] * v[2] - u[2] * v[1];
	w[1] = u[2] * v[0] - u[0] * v[2];
	w[2] = u[0] * v[1] - u[1] * v[0];
}

double quad_area(quad q){
	
	double area = 0;

	double x[4];
        double y[4];
	double u[3];
	double v[3];
	double w[3];

        x[0] = q.node1.x;
        x[1] = q.node2.x;
        x[2] = q.node3.x;
	x[3] = q.node4.x;
	
	y[0] = q.node1.y;
	y[1] = q.node2.y;
        y[2] = q.node3.y;
	y[3] = q.node4.y;

	u[0] = x[2] - x[0]; v[0] = x[1] - x[0];
	u[1] = y[2] - y[0]; v[1] = y[1] - y[0];
	u[2] = 0; 	    v[2] = 0;
	
	cross(u, v, w);
	area = 0.5 * fabs(w[2]);
	
	u[0] = x[2] - x[3]; v[0] = x[1] - x[3];
        u[1] = y[2] - y[3]; v[1] = y[1] - y[3];
        u[2] = 0;           v[2] = 0;
	
	cross(u, v, w);
	area += 0.5 * fabs(w[2]);

	return area;
}	
