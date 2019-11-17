#pragma once
#include"Variable.h"

//Matrix类头文件
int BuildMatrix(Matrix* matrix, unsigned row, unsigned column, unsigned height);

Bool IsNullMatrix(const Matrix* matrix);

int DestroyMatrix(Matrix* matrix);

int MatrixTranspose(const Matrix* matrix, Matrix* C);

int MatrixAdd(const Matrix* A, const Matrix*B, Matrix* C);

int MatrixSubstract(const Matrix* A, const Matrix*B, Matrix* C);

int MatrixMultibyMatrix(const Matrix* A, const Matrix* B, Matrix* C);

int MatrixCopy(const Matrix* matrix, Matrix* C);

int MatrixMultibyConst(const Matrix* matrix, Matrix* C, const MatrixType con);

int MatrixAddbyConst(const Matrix* matrix, Matrix* C, const MatrixType con);

int PrintMatrix(const Matrix* matrix);

int RealMatrixSchmitOrthogonal(const Matrix* matrix, Matrix *I,Matrix* D);

MatrixType*** MatrixTo3DimensionPointer(const Matrix* matrix, ElementType e);

MatrixType*** Build3DimensionPointer(unsigned row, unsigned column, unsigned height);

int Destroy3DimensionPointer(MatrixType*** temp, unsigned row, unsigned height);

MatrixType** Build2DimensionPointer(unsigned row, unsigned column);

int Destroy2DimensionPointer(MatrixType** temp, unsigned row);

MatrixType* Build1DimensionPointer(unsigned row);

int Destroy1DimensionPointer(MatrixType* temp);

int _3DimensionPointerMultiby3DimensionPointer(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, unsigned columnB, const MatrixType*** B, MatrixType*** C);

int _3DimensionPointerTranspose(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, MatrixType*** C);

int __3DimensionPointerCopytoMatrix(const MatrixType*** temp, unsigned row, unsigned column, unsigned height, Matrix* matrix);

int _3DimensionPointerAdd(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, const MatrixType*** B, MatrixType*** C);

int _3DimensionPointerSubstract(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, const MatrixType*** B, MatrixType*** C);

int _3DimensionPointerAddby2DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C);

int _3DimensionPointerSubstractby2DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C);

int _3DimensionPointerAddbyConst(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType con, MatrixType** C);

int _3DimensionPointerMultibyConst(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType con, MatrixType** C);

int _2DimensionPointerMultiby2DimensionPointer(MatrixType** A, unsigned rowA, unsigned columnA, unsigned columnB, MatrixType** B, MatrixType** C);

int _3DimensionPointerMultiby2DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, unsigned columnB, const MatrixType** B, MatrixType** C);

int _3DimensionPointerMultiby1DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType* B, MatrixType* C);

int _2DimensionPointerMultiby1DimensionPointer(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType* B, MatrixType* C);

int _2DimensionPointerTranspose(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType** C);

int _2DimensionPointerAdd(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C);

int _2DimensionPointerSubstract(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C);

int _2DimensionPointerAddbyConst(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType con, MatrixType** C);

int _2DimensionPointerMultibyConst(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType con, MatrixType** C);

int _2DimensionPointerCopyto2DimensionPointer(MatrixType** A, unsigned rowA, unsigned columnA, MatrixType** B);

int _2DimensionPointerCopytoMatrix(Matrix* matrix, unsigned layer, unsigned rowA, unsigned columnA, MatrixType** A);

int _1DimensionPointerMultiby1DimensionPointer(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType& C);

int _1DimensionPointerSubstract(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType* C);

int _1DimensionPointerAdd(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType* C);

int _1DimensionPointerMultibyConst(const MatrixType* A, unsigned columnA, MatrixType con, MatrixType* C);

int _1DimensionPointerAddbyConst(const MatrixType* A, unsigned columnA, MatrixType con, MatrixType* C);





//Vector类头文件
int BuildVector(Vector* vector, unsigned n);

int DestroyVector(Vector* vector);

int Destroy2DimensionVector(Vector** vector, unsigned column);

Bool IsNullVector(const Vector* vector);

MatrixType VectorAbsMax(const Vector* vector);

int VectorCopyToVector(const Vector* A, Vector* B);

int PrintVector(Vector* vector);

int VectorAddByVector(const Vector* A, const Vector* B, Vector* C);

int VectorSubstractVector(const Vector* A, const Vector* B, Vector* C);

VectorType VectorDotProduct(const Vector* A, const Vector* B);

VectorType VectorNorm(const Vector* A);

int MatrixMultibyVector(const Matrix* matrix, unsigned layer, const Vector* vector, Vector* result);

int _3DimensionPointerMultibyVector(const MatrixType*** temp, unsigned row, unsigned column, unsigned layer, const Vector* vector, Vector* result);

int _2DimensionPointerMultibyVector(const MatrixType** temp, unsigned row, unsigned column, const Vector* vector, Vector* result);

int _1DimensionPointerMultibyVector(const MatrixType* temp, unsigned column, const Vector* vector, MatrixType& result);

int VectorMultibyConst(const Vector* A, Vector* C, VectorType cons);

Vector** _3DimensionPointerCopyto2DimensionVector(const MatrixType*** temp, unsigned layer, unsigned row, unsigned column);

Vector** MatrixCopyto2DimensionVector(const Matrix* matrix, unsigned layer);

int RealMatrixDeterminant(const Matrix* matrix, Vector* determinant);

int RealQR(const Matrix* matrix, Matrix* Q, Matrix* R);

int RealGivens(const Matrix* matrix, Matrix* Q, Matrix* R);

int RealHessenBurg(const Matrix* matrix, Matrix* H, Matrix* P);

int EginValue(const Matrix* matrix, Matrix* E, Matrix* EV);

int EginVectorReal(const Matrix* matrix, Vector* EV, MatrixType& Lambda);

int SVDReal(const Matrix* matrix, Matrix* U, Matrix* T, Matrix* V);

int SVDInv(const Matrix* matrix, Matrix* C);