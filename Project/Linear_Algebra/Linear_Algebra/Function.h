#pragma once
#include"Variable.h"

Bool SetMatrixSize(Matrix *matrix, const unsigned row, const unsigned column, const unsigned height);

void SetMatrixElement(Matrix* matrix, MatrixType element);

void SetMatrixZero(Matrix* matrix);

Bool IsNullMatrix(const Matrix* matrix);

void DestroyMatrix(Matrix* matrix);

unsigned MatrixCapacity(const Matrix* matrix);

MatrixType MatrixNorm2(const Matrix* matrix);

Bool CopyMatrix(Matrix* matrixB, Matrix* matrix, unsigned height);

Bool MatrixMultiMatrix(Matrix* matrixC, const Matrix* matrixA, const Matrix* matrixB);

void SortVector(Matrix* vector, int sign);

void PrintMatrix(const Matrix* matrix);

void QR(Matrix* A, Matrix* Q, Matrix* R);

void Eigenvectors(Matrix *eigenVector, Matrix *A, Matrix *eigenValue);

int MatrixTranspose(const Matrix* matrix, Matrix* C);

int MatrixAdd(const Matrix* A, const Matrix*B, Matrix* C);

int BuildMatrix(Matrix* matrix, unsigned row, unsigned column, unsigned height);

int MatrixSubstract(const Matrix* A, const Matrix*B, Matrix* C);

int MatrixMultibyMatrix(const Matrix* A, const Matrix* B, Matrix* C);

int MatrixCopy(const Matrix* matrix, Matrix* C);

int MatrixMultibyConst(const Matrix* matrix, Matrix* C, MatrixType con);