#ifndef REVERSE_MATRIX_H
#define REVERSE_MATRIX_H

typedef struct optionMatrix
{
    double **matrix;
    int size;
}matrixAndSize;

matrixAndSize *createMatrix(int size);
void destroyMatrixAndSize(matrixAndSize *aMatrix);

void addNumbToMatrix(matrixAndSize *aMatrix);

void print_matrix(matrixAndSize *aMatrix);

int reverseMatrix(matrixAndSize *aMatrix);

#endif //REVERSE_MATRIX_H
