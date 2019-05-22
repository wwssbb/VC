#pragma once
#include"Variable.h"

Bool SetMatrixSize(Matrix *matrix, const unsigned row, const unsigned column, const unsigned height);

void SetMatrixElement(Matrix* matrix, MatrixType element);

void SetMatrixZero(Matrix* matrix);

Bool IsNullMatrix(const Matrix* matrix);

void DestroyMatrix(Matrix* matrix);

int DestoryVectorPoint(MatrixType*** temp, unsigned row, unsigned height);

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

int MatrixSchmitOrthogonal(const Matrix* matrix, Matrix *I,Matrix* D);

MatrixType*** MatrixToVector(const Matrix* matrix, ElementType e);

int BuildVector(Vector* vector, unsigned n);

int DestroyVector(Vector* vector);

MatrixType** Build2DimensionPointer(unsigned row, unsigned column);

int Destory2DimensionPointer(MatrixType** temp, unsigned row);

MatrixType*** Build3DimensionPointer(unsigned row, unsigned column, unsigned height);

Bool IsNullVector(const Vector* vector);

int VectorAddByVector(const Vector* A, const Vector* B, Vector* C);

int VectorSubstractVector(const Vector* A, const Vector* B, Vector* C);

VectorType VectorDotProduct(const Vector* A, const Vector* B);

VectorType VectorNorm(const Vector* A);

int VectorMultibyConst(const Vector* A, Vector* C, VectorType cons);

int MatrixDeterminant(const Matrix* matrix, double* determinant);

int RealQR(const Matrix* matrix, Matrix* Q, Matrix* R);

int RealGivens(const Matrix* matrix, Matrix* Q, Matrix* R);