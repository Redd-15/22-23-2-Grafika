#ifndef MATRIX_H
#define MATRIX_H


void init_identity_matrix(float matrix[3][3]);
void init_zero_matrix(float matrix[3][3]);

void print_matrix(const float matrix[3][3]);
void print_point(const float[3]);
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void multiply_skalar(float a[3][3], float num);
void multiply_matrices(float first[3][3],float second[3][3], float result[3][3]);
void transform_point(float point[3], float transformation[3][3]);
void scale(float trans_mx[3][3], float scale);
void shift(float trans_mx[3][3], float vector[2]);
void rotate(float trans_mx[3][3], float angle);

#endif // MATRIX_H

