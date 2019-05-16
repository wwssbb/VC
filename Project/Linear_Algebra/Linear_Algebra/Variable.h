#pragma once
#include"string.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
#include<iostream>
using namespace std;

typedef enum
{
	False=0,
	True=1,
}Bool;

typedef double MatrixType;

typedef double VectorType;

typedef struct
{
	unsigned row, column, height;
	MatrixType* array;
}Matrix;

typedef struct
{
	unsigned length;
	VectorType* array;
}Vector;

typedef enum
{
	Zero = 0,
	Element = 1,
}ElementType;

typedef enum
{
	OrthogonalMatrix,
	NonOrthogonalMatrix,
	LinearCorrelationMatrix,
	NonLinearCorrelationMatrix,
	InvertibleMatrix,
	UnInvertibleMatrix,
	ZeroDeterminant,
	NonZeroDeterminant,

}MatrixDefinition;
