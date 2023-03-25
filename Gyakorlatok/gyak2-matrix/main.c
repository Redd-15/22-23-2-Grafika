#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];
    float identity[3][3];

    printf("Identity matrix:\n");

    init_identity_matrix(identity);
    print_matrix(identity);

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;
    
    printf("\nMatrix A:\n");
    print_matrix(a);
    printf("\nMatrix B:\n");
    print_matrix(b);
    
    printf("\nAdded matrices:\n");

    add_matrices(a, b, c);

    print_matrix(c);

    float point[3] = { 1.0f, 2.0f, 3.0f};
    float trans_mx[3][3];
    init_identity_matrix(trans_mx);

    printf("\nPoint:\n");
    print_point(point);

    transform_point(point, trans_mx);

    scale(trans_mx, 5);
    transform_point(point, trans_mx);

    printf("\n5 times scaled point:\n");
    print_point(point);

    float sh[2] = {2,4};
    shift(trans_mx, sh);
    transform_point(point, trans_mx);

    init_identity_matrix(trans_mx);
    printf("\n2,4 shifted point:\n");
    print_point(point);

    init_identity_matrix(trans_mx);
    rotate(trans_mx, 42);
    transform_point(point, trans_mx);

    printf("\n42 degree rotated point:\n");
    print_point(point);

    init_identity_matrix(trans_mx);
    float point2[3] = { 1.0f, 2.0f, 3.0f};
    float vect[3] = {6,8};
    printf("\n\n6,8 shifting, 90 degree rotating and 10 times scaling the point:\n");
    
    printf("\nOriginal point:\n");
    print_point(point2);


    shift(trans_mx, vect);
    rotate(trans_mx, 90);
    scale(trans_mx, 10);

    printf("\n\nThe final transformation matrix:\n\n");
    print_matrix(trans_mx);

    transform_point(point2, trans_mx);

    printf("\nPoint after transformation:\n");
    print_point(point2);

	return 0;
}

