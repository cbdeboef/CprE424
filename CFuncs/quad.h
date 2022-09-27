#ifndef __QUAD_H__
#define __QUAD_H__

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

#endif
