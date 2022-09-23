#include "quad.h"
#include <stdio.h>
#include <math.h>
//#include "quad_perimeter.c"
//#include "quad_area.c"

int main(){
	
	double quad_perimeter(quad q);
	double quad_area(quad q);

	quad q;

	printf("Type point 1 of the quadrilateral using the form (x,y)\n");
	scanf("%lf %lf", &q.node1.x, &q.node1.y);
        printf("Type point 2 of the quadrilateral using the form (x,y)\n");
        scanf("%lf %lf", &q.node2.x, &q.node2.y);
        printf("Type point 3 of the quadrilateral using the form (x,y)\n");
        scanf("%lf %lf", &q.node3.x, &q.node3.y);
        printf("Type point 4 of the quadrilateral using the form (x,y)\n");
        scanf("%lf %lf", &q.node4.x, &q.node4.y);	
	
	printf("%lf\n", quad_perimeter(q));
	printf("%lf\n", quad_area(q));

	return q.node4.x;

}
