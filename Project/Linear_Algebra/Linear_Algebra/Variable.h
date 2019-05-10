#pragma once
#include"string.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
using namespace std;

typedef enum
{
	False=0,
	True=1,
}Bool;

typedef double MatrixType;

typedef struct
{
	unsigned row, column, height;
	MatrixType* array;
}Matrix;

