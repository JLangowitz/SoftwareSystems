/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    double **data;
    int rows, cols;
} Matrix;


// Makes a new matrix and sets all elements to zero.
Matrix *make_matrix(int rows, int cols) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = malloc(sizeof(double *) * rows);
    int i;
    for (i = 0; i < rows; ++i)
    {
        matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

void destroy_matrix(Matrix *A){
    int i;
    for (i = 0; i < A->rows; ++i)
    {
        free(A->data[i]);
    }
    free(A->data);
    free(A);
}

// Prints the elements of a matrix.
void print_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    printf("%lf ", matrix->data[i][j]);
	}
	printf("\n");
    }
}

// Adds a scalar to all elements of a matrix.
void increment_matrix(Matrix *matrix, int incr) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] += incr;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void consecutive_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] = i * matrix->cols + j;
	}
    }
}

// Adds two matrices elementwise and stores the result in the given
// destination matrix (C).
void add_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j;

    assert(A->rows == B->rows && B->rows == C->rows);
    assert(A->cols == B->cols && B->cols == C->cols);

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    C->data[i][j] =  A->data[i][j] + B->data[i][j];
	}
    }
}

// Adds two matrices elementwise and returns a new matrix.
Matrix *add_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, A->cols);
    add_matrix(A, B, C);
    return C;
}

Matrix *transpose_matrix(Matrix *A) {
    int rows = A->cols;
    int cols = A->rows;
    Matrix *Res = make_matrix(rows, cols);
    int i;
    int j;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            Res->data[i][j] = A->data[j][i];
        }
    }
    return Res;
}

double dot_product(double *u, double *v, int len){
    double ret = 0;
    int i;
    for (i = 0; i < len; ++i)
    {
        ret+= u[i]*v[i];
    }
    return ret;
}

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    // Fill this in
    // Note that it is asking for matrix multiplication, not
    // elementwise multiplication
    if ((A->cols != B->rows) || (A->rows != C->rows) || (B->cols != C->cols)){
        printf("%s\n", "DIM Mismatch");
        exit(1);
    }
    Matrix *BT = transpose_matrix(B);
    int i, j;
    for (i = 0; i < A->rows; ++i)
    {
        for (j = 0; j < B->cols; ++j)
        {
            C->data[i][j] = dot_product(A->data[i], BT->data[j], A->cols);
        }
    }
    destroy_matrix(BT);
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *Ret = make_matrix(A->rows, B->cols);
    mult_matrix(A,B,Ret);
    return Ret;
}

int main() {
    Matrix *A = make_matrix(3, 4);
    consecutive_matrix(A);
    printf("A\n");
    print_matrix(A);

    Matrix *C = add_matrix_func(A, A);
    printf("A + A\n");
    print_matrix(C);

    Matrix *B = make_matrix(4, 3);
    increment_matrix(B, 1);
    printf("B\n");
    print_matrix(B);

    Matrix *D = mult_matrix_func(A, B);
    printf("D\n");
    print_matrix(D);

    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);
    destroy_matrix(D);
    return 0;
}
