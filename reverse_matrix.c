#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "reverse_matrix.h"

//declarations
matrixAndSize *copyMatrixAndSize(matrixAndSize *aMatrix);
double determinant(matrixAndSize *aMatrix);
void transpositionMatrix(matrixAndSize *aMatrix);
void multiplicationMatrixByNumb(double numb, matrixAndSize *aMatrix);
void minorMatrix(matrixAndSize *aMatrix);
void algAdd(matrixAndSize *aMatrix);


//Main Functions

matrixAndSize *createMatrix(int size)
{
    matrixAndSize *aMatrixAndSize=(matrixAndSize *)malloc(sizeof(matrixAndSize));

    if(aMatrixAndSize!=NULL)
    {
        aMatrixAndSize->size=size;

        aMatrixAndSize->matrix=(double **)malloc(size*sizeof(double *));
        if(aMatrixAndSize->matrix!=NULL)
        {
            for (int i = 0; i < size; ++i) {
                aMatrixAndSize->matrix[i]=(double *)calloc(size, sizeof(double));
            }

        }

    }

    return aMatrixAndSize;
}

void addNumbToMatrix(matrixAndSize *aMatrix) 
{
	if(aMatrix==NULL) {printf("Error: couldn't multiply number to matrix\n"); return;}
	
	FILE *fp_rand;
	if ((fp_rand = fopen("/dev/random", "rb")) == NULL) {printf("Error: couldn't multiply number to matrix\n"); return;}
	unsigned int seed;
	fread(&seed, sizeof(seed), 1, fp_rand);
	if (ferror(fp_rand)) {printf("Error: couldn't multiply number to matrix\n"); return;}
	fclose(fp_rand);
	srand(seed);
	
    for(int i=0; i < aMatrix->size; i++)
    {
		for(int j=0; j < aMatrix->size; j++)
		{
			aMatrix->matrix[i][j]=rand()%10+1;	
			}
		}
}

void destroyMatrixAndSize(matrixAndSize *aMatrix) 
{
    if(aMatrix!=NULL)
    {
        for (int i = 0; i < aMatrix->size; ++i) {
            if(aMatrix->matrix[i]!=NULL)
                free(aMatrix->matrix[i]);
        }
        free(aMatrix);
    }
}

void print_matrix(matrixAndSize *aMatrix)
{
	if(aMatrix==NULL) {printf("Error: couldn't print matrix\n"); return;}
	
    for(int i=0; i<aMatrix->size; i++)
    {
        for (int j = 0; j < aMatrix->size; ++j) {
            printf("%.3f ", aMatrix->matrix[i][j]);
        }
        printf("\n");
    }
}

int reverseMatrix(matrixAndSize *aMatrix)
{
	if(aMatrix==NULL) {printf("Error: couldn't reverse matrix\n"); return;}
	
    double aDeterminant=roundf(determinant(aMatrix)*1000)/1000;

    if(aDeterminant==0)
    {
        printf("Determinant=0 Reverse matrix impossible\n");
        return -1;
    }

    algAdd(aMatrix);
    transpositionMatrix(aMatrix);

    multiplicationMatrixByNumb(1/aDeterminant, aMatrix);

    return 0;

}

//Help functions

double determinant(matrixAndSize *aMatrix)  //find determinant
{

    int width = aMatrix->size;

    matrixAndSize *copyMatrix=copyMatrixAndSize(aMatrix);

    double determinant = 1;

    for (int k = 0; k < width-1; ++k) {

        for (int j = 1; j < width-k; ++j) {

            if(copyMatrix->matrix[j+k][k]!=0 && copyMatrix->matrix[k][k]!=0)
            {
                double time=copyMatrix->matrix[j+k][k]/copyMatrix->matrix[k][k];
                for (int i = 0; i < width-k; ++i) {

                    copyMatrix->matrix[k][i+k]=copyMatrix->matrix[k][i+k]*time;
                    copyMatrix->matrix[j+k][i+k]=copyMatrix->matrix[j+k][i+k]-copyMatrix->matrix[k][i+k];
                    copyMatrix->matrix[k][i+k]=copyMatrix->matrix[k][i+k]*(1/time);
                }
            }

        }
    }

    for (int f = 0; f < width; ++f) {
        determinant=determinant*copyMatrix->matrix[f][f];
    }

	destroyMatrixAndSize(copyMatrix);
	
    return determinant;
}

void minorMatrix(matrixAndSize *aMatrix) //convert aMatrix to minor matrix
{
    int width = aMatrix->size;
    double **matrix = aMatrix->matrix;

    matrixAndSize *aCopyMatrix=copyMatrixAndSize(aMatrix);
    matrixAndSize *miniMatrix=createMatrix(width-1);


    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < width; ++y) {

            int f=0;
            int g=0;

            for (int i = 0; i < width; ++i) {
                if(i!=x)
                {
                    for (int j = 0; j < width; ++j) {
                        if(j!=y)
                        {
                            miniMatrix->matrix[f][g]=aCopyMatrix->matrix[i][j];
                            g++;
                        }
                    }
                    g=0;
                    f++;
                }

            }

            matrix[x][y]=determinant(miniMatrix);

        }
    }

    destroyMatrixAndSize(miniMatrix);
    destroyMatrixAndSize(aCopyMatrix);


}

void algAdd(matrixAndSize *aMatrix) 
{
    minorMatrix(aMatrix);

    double f;
    for (int i = 0; i < aMatrix->size; ++i) {
        for (int j = 0; j < aMatrix->size; ++j) {
            f=powf(-1, i+j);
            aMatrix->matrix[i][j]=f*aMatrix->matrix[i][j];

        }
    }

}

void transpositionMatrix(matrixAndSize *aMatrix)
{
    int width = aMatrix->size;
    double **matrix = aMatrix->matrix;
    double tmp=0;

    for (int j = 0; j < width-1; ++j) {
        for (int i = 1; i < width-j; ++i) {

            tmp=matrix[0+j][i+j];
            matrix[0+j][i+j]=matrix[i+j][0+j];
            matrix[i+j][0+j]=tmp;

        }
    }
}

void multiplicationMatrixByNumb(double numb, matrixAndSize *aMatrix)
{
    int width = aMatrix->size;
    double **matrix = aMatrix->matrix;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j]=numb*matrix[i][j];
        }
    }
}

matrixAndSize *copyMatrixAndSize(matrixAndSize *aMatrix)
{
    int width = aMatrix->size;
    double **matrix = aMatrix->matrix;

    matrixAndSize *copyMatrixAndSize=createMatrix(width);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < width; ++j) {
            copyMatrixAndSize->matrix[i][j]=matrix[i][j];
        }
    }
    return copyMatrixAndSize;
}




