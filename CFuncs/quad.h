#ifndef __QUAD_H__
#define __QUAD_H__
#include <math.h>
typedef struct point point;
struct point{
	double x;
	double y;
};

typedef struct quad quad;
struct quad{
	point node1;
	point node2;
	point node3;
	point node4;
};

double quad_perimeter(quad q){
        double perim = 0;

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

	perim  = sqrt(pow((x[0]-x[1]),2)+pow((y[0]-y[1]),2));
	perim += sqrt(pow((x[1]-x[2]),2)+pow((y[1]-y[2]),2));
	perim += sqrt(pow((x[2]-x[3]),2)+pow((y[2]-y[3]),2));
	perim += sqrt(pow((x[3]-x[0]),2)+pow((y[3]-y[0]),2));

        return perim;

}

void cross(double u[], double v[], double w[]){
        w[0] = u[1] * v[2] - u[2] * v[1];
        w[1] = u[2] * v[0] - u[0] * v[2];
        w[2] = u[0] * v[1] - u[1] * v[0];
}

double quad_area(quad q){

        double area = 0;

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

	double s = quad_perimeter(q) / 2;
	double A = sqrt(pow((x[0]-x[1]),2)+pow((y[0]-y[1]),2));
	double B = sqrt(pow((x[1]-x[2]),2)+pow((y[1]-y[2]),2));
	double C = sqrt(pow((x[2]-x[3]),2)+pow((y[2]-y[3]),2));
	double D = sqrt(pow((x[3]-x[0]),2)+pow((y[3]-y[0]),2));

	area = sqrt((s-A)*(s-B)*(s-C)*(s-D));

	return area;
}

#endif
