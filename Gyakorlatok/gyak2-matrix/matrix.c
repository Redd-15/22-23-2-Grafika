#include "matrix.h"

#include <stdio.h>
#include <math.h>

void init_identity_matrix(float matrix[3][3]){

for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i==j){matrix[i][j] = 1.0;}
            else {matrix[i][j] = 0.0;}
        }
    }

}

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_point(const float point[3]){

    printf(" %f, %f, %f", point[0],point[1],point[2]);
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_skalar(float a[3][3], float num){

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            a[i][j] *= num;
        }
    }
}

void multiply_matrices(float first[3][3],float second[3][3], float result[3][3]) {

   init_zero_matrix(result);

   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         for (int k = 0; k < 3; ++k) {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }
}


void transform_point(float point[3], float transformation[3][3]){

float temp[3];

for (int i = 0; i < 3; i++){

temp[i] = point[i];
point[i]=0;

}

for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
            point[i] += temp[i] * transformation[i][j];
      }
   }

}

void scale(float trans_mx[3][3], float scale){

    float temp[3][3];
    float mx[3][3]={ scale,     0,  0,
                         0, scale,  0,
                         0,     0,  1};
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = trans_mx[i][j];
        }
    }

    multiply_matrices(temp, mx, trans_mx);

}
void shift(float trans_mx[3][3], float vector[2]){

    float temp[3][3];
    float mx[3][3]={ 1, 0,  vector[0],
                    0, 1,  vector[1],
                    0, 0,         1};
                
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = trans_mx[i][j];
        }
    }

    multiply_matrices(temp, mx, trans_mx);

}
void rotate(float trans_mx[3][3], float angle){

    float temp[3][3];
    float mx[3][3]={  cos(angle), sin(angle),  0,
                     -sin(angle), cos(angle),  0,
                               0,          0,  1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = trans_mx[i][j];
        }
    }

    multiply_matrices(temp, mx, trans_mx);
}
