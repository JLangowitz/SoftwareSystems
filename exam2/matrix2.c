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
    int i;
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->data = malloc(rows * sizeof(double *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (i=0; i<rows; i++) {
	// use calloc to initialize to 0
	matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

// Frees a matrix and all it's data when you are done with it
void destroy_matrix(Matrix *A){
    int i;
    for (i = 0; i < A->rows; ++i)
    {
        free(A->data[i]);
    }
    free(A->data);
    free(A);
}

// Takes a matrix and returns a heap allocated matrix that is it's transpose
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

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j, k;

    assert(A->rows == B->cols);
    assert(A->rows == C->rows);
    assert(B->cols == C->cols);

    for (i=0; i<C->rows; i++) {
	for (j=0; j<C->cols; j++) {
	    for (k=0; k<A->cols; k++) {
		C->data[i][j] += A->data[i][k] * B->data[k][j];
	    }
	}
    }
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, B->cols);
    mult_matrix(A, B, C);
    return C;
}

double matrix_sum1(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (i=0; i<A->rows; i++) {
    	for (j=0; j<A->cols; j++) {
    	    total += A->data[i][j];
    	}
    }
    return total;
}
    
double matrix_sum2(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (j=0; j<A->cols; j++) {
    	for (i=0; i<A->rows; i++) {
    	    total += A->data[i][j];
    	}
    }
    return total;
}
    

// Adds up the rows of A and returns a heap-allocated array of doubles.
double *row_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->rows * sizeof(double));

    for (i=0; i<A->rows; i++) {
    	total = 0.0;
    	for (j=0; j<A->cols; j++) {
    	    total += A->data[i][j];
    	}
    	res[i] = total;
    }
    return res;
}

// Returns a heap allocated array of the sums of diagonal entries of square matrix A, 
// with the first element being the forward diagonal and the second being the backwards.
double *matrix_diagonal_sums(Matrix *A){
    double *res = calloc(2, sizeof(double));
    int i;
    for (i=0; i<A->rows; i++){
        res[0] += A->data[i][i];
        res[1] += A->data[i][A->rows - 1 - i];
    }
    return res;
}

// Returns a heap allocated array of all sums of nxn matrix A
// The first n entries are the row sums, second n are col sums,
// last two are forward and then backward diagonal sums
double *all_sums(Matrix *A){
    Matrix *A_transpose = transpose_matrix(A);
    double *row_sums = row_sum(A);
    double *col_sums = row_sum(A_transpose);
    double *diag_sums = matrix_diagonal_sums(A);
    double *res = malloc((2*A->rows + 2) * sizeof(double));

    memcpy (res, row_sums, A->rows * sizeof(double));
    memcpy (&res[A->rows], col_sums, A->rows * sizeof(double));
    memcpy (&res[2 * A->rows], diag_sums, 2 * sizeof(double));

    free(row_sums);
    free(col_sums);
    free(diag_sums);
    destroy_matrix(A_transpose);
    return res;
}

int all_equal(double *array, int len){
    int i;
    for (i = 1; i < len; ++i)
    {
        if (array[0] != array[i])
            return 0;
    }
    return 1;
}

/* 
   http://en.wikipedia.org/wiki/Magic_square

   A magic square is an arrangement of numbers (usually integers) in a
   square grid, where the numbers in each row, and in each column, and
   the numbers in the forward and backward main diagonals, all add up
   to the same number. 

   Write a function called is_magic_square() that takes a matrix and 
   returns an int, 1 if the matrix is a magic square, and 0 otherwise.

   Feel free to use row_sum().
*/

// Checks whether a matrix is a magic square, returns 1 if it is, 0 otherwise
int is_magic_square(Matrix *A) {
    if (A->rows != A->cols) return 0;
    double *sums = all_sums(A);
    int res = all_equal(sums, 2 * (A->rows + 1));
    free(sums);
    return res;
}


int main() {
    int i;

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

    double sum = matrix_sum1(A);
    printf("sum = %lf\n", sum);

    sum = matrix_sum2(A);
    printf("sum = %lf\n", sum);

    double *sums = row_sum(A);
    for (i=0; i<A->rows; i++) {
	printf("row %d\t%lf\n", i, sums[i]);
    }
    // should print 6, 22, 38

    Matrix *E = make_matrix(3, 3);

    printf("E\n");
    print_matrix(E);
    printf("%s\n", "Should be a magic square");
    printf("%i\n", is_magic_square(E));

    memcpy(E->data[0], (double[]){2, 7, 6}, 3 * sizeof(double));
    memcpy(E->data[1], (double[]){9, 5, 1}, 3 * sizeof(double));
    memcpy(E->data[2], (double[]){4, 3, 8}, 3 * sizeof(double));

    printf("E\n");
    print_matrix(E);
    printf("%s\n", "Should be a magic square");
    printf("%i\n", is_magic_square(E));

    memcpy(E->data[0], (double[]){2, 3, 6}, 3 * sizeof(double));
    memcpy(E->data[1], (double[]){9, 5, 1}, 3 * sizeof(double));
    memcpy(E->data[2], (double[]){4, 3, 8}, 3 * sizeof(double));

    printf("E\n");
    print_matrix(E);
    printf("%s\n", "Should not be a magic square");
    printf("%i\n", is_magic_square(E));

    printf("A\n");
    print_matrix(A);
    printf("%s\n", "Should not be a magic square");
    printf("%i\n", is_magic_square(A));

    free(sums);
    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);
    destroy_matrix(D);
    destroy_matrix(E);
    return 0;
}
