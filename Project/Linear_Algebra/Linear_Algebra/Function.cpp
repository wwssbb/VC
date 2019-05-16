#include"Variable.h"

Bool SetMatrixSize(Matrix *matrix, const unsigned row, const unsigned column, const unsigned height)

{

	unsigned size = row * column * height * sizeof(MatrixType);

	if (size <= 0)

	{

		return False;

	}



	matrix->array = (MatrixType*)malloc(size);



	//如果分配内存成功

	if (matrix->array)

	{

		matrix->row = row;

		matrix->column = column;

		matrix->height = height;

		return True;

	}

	else

	{

		matrix->row = matrix->column = matrix->height = 0;

		return False;

	}

}



//设置Matrix矩阵中的所有元素大小为ele

void SetMatrixElement(Matrix *matrix, MatrixType element)

{

	unsigned size = matrix->row * matrix->column * matrix->height;

	unsigned i;



	for (i = 0; i < size; ++i)

	{

		matrix->array[i] = element;

	}

}



//设置Matrix矩阵中的所有元素大小为0

void SetMatrixZero(Matrix*matrix)

{

	SetMatrixElement(matrix, 0);

}



//判断矩阵是否为空，若为空则返回1，否则返回0

Bool IsNullMatrix(const Matrix* matrix)

{

	unsigned size = matrix->row * matrix->column * matrix->column;



	if (size <= 0 || matrix->array == NULL)

	{

		return True;

	}

	return False;

}



//销毁矩阵，即释放为矩阵动态分配的内存,并将矩阵的长宽高置0

void DestroyMatrix(Matrix *matrix)

{

	if (!IsNullMatrix(matrix))

	{

		free(matrix->array);

		matrix->array = NULL;

	}



	matrix->row = matrix->column = matrix->height = 0;
	matrix = NULL;
}



//计算矩阵可容纳元素个数，即return row*column*height

unsigned MatrixCapacity(const Matrix*matrix)

{

	return matrix->row * matrix->column * matrix->height;

}





//||matrix||_2  求A矩阵的2范数

MatrixType MatrixNorm2(const Matrix *matrix)

{

	unsigned size = matrix->row * matrix->column *matrix->height;

	unsigned i;

	MatrixType norm = 0;



	for (i = 0; i < size; ++i)

	{

		norm += (matrix->array[i]) *(matrix->array[i]);

	}



	return (MatrixType)sqrt(norm);

}



//matrixB = matrix(:,:,height)即拷贝三维矩阵的某层，若matrix为二维矩阵，需将height设置为0

Bool CopyMatrix(Matrix* matrixB, Matrix *matrix, unsigned height)

{

	unsigned size, i;

	Matrix matrixA;



	//判断height值是否正确

	if (height < 0 || height >= matrix->height)

	{

		printf("ERROR: CopyMatrix() parameter error！\n");

		return False;

	}



	//将matrix(:,:,height) 转换为二维矩阵matrixA

	matrixA.row = matrix->row;

	matrixA.column = matrix->column;

	matrixA.height = 1;

	matrixA.array = matrix->array + height * matrix->row * matrix->column;



	//判断两矩阵指向的内存是否相等

	if (matrixA.array == matrixB->array)

	{

		return True;

	}



	//计算matrixA的容量

	size = MatrixCapacity(&matrixA);

	//判断matrixB的容量与matrixA的容量是否相等

	if (MatrixCapacity(matrixB) != size)

	{

		DestroyMatrix(matrixB);

		SetMatrixSize(matrixB, matrixA.row, matrixA.column, matrixA.height);

	}

	else

	{

		matrixB->row = matrixA.row;

		matrixB->column = matrixA.column;

		matrixB->height = matrixA.height;

	}



	for (i = 0; i < size; ++i)

	{

		matrixB->array[i] = matrixA.array[i];

	}



	return True;

}



//matrixC = matrixA * matrixB

Bool MatrixMultiMatrix(Matrix *matrixC, const Matrix* matrixA, const Matrix* matrixB)

{

	size_t row_i, column_i, i;

	size_t indexA, indexB, indexC;

	MatrixType temp;

	Matrix tempC;



	if (IsNullMatrix(matrixA) || IsNullMatrix(matrixB))

	{

		return False;

	}



	if (matrixA->column != matrixB->row)

	{

		return False;

	}



	if (MatrixCapacity(matrixC) != matrixA->row * matrixB->column)

	{

		SetMatrixSize(&tempC, matrixA->row, matrixB->column, 1);

	}

	else

	{

		tempC.array = matrixC->array;

		tempC.row = matrixA->row;

		tempC.column = matrixB->column;

		tempC.height = 1;

	}



	for (row_i = 0; row_i < tempC.row; ++row_i)

	{

		for (column_i = 0; column_i < tempC.column; ++column_i)

		{

			temp = 0;

			for (i = 0; i < matrixA->column; ++i)

			{

				indexA = row_i * matrixA->column + i;

				indexB = i * matrixB->column + column_i;



				temp += matrixA->array[indexA] * matrixB->array[indexB];

			}

			indexC = row_i * tempC.column + column_i;



			tempC.array[indexC] = temp;

		}

	}





	if (tempC.array != matrixC->array)

	{

		DestroyMatrix(matrixC);



		matrixC->array = tempC.array;

	}



	matrixC->row = tempC.row;

	matrixC->column = tempC.column;

	matrixC->height = tempC.height;







	return True;

}



//对vector中所有元素排序，sign= 0 时为升序，其余为降序

void SortVector(Matrix *vector, int sign)

{

	MatrixType mid;

	int midIndex;

	int size = MatrixCapacity(vector);

	int i, j;



	if (0 == sign)

	{

		for (i = 0; i < size; ++i)

		{

			mid = vector->array[i];

			midIndex = i;

			for (j = i + 1; j < size; ++j)

			{

				if (mid > vector->array[j])

				{

					mid = vector->array[j];

					midIndex = j;

				}

			}



			vector->array[midIndex] = vector->array[i];

			vector->array[i] = mid;

		}

	}

	else

	{

		for (i = 0; i < size; ++i)

		{

			mid = vector->array[i];

			midIndex = i;

			for (j = i + 1; j < size; ++j)

			{

				if (mid < vector->array[j])

				{

					mid = vector->array[j];

					midIndex = j;

				}

			}



			vector->array[midIndex] = vector->array[i];

			vector->array[i] = mid;

		}

	}

}



//打印矩阵

void PrintMatrix(const Matrix *matrix)

{

	size_t row_i, column_i, height_i, index;



	for (height_i = 0; height_i < matrix->height; ++height_i)

	{

		(matrix->height == 1) ? printf("[:,:] = \n") : printf("[%d,:,:] = \n", height_i);



		for (row_i = 0; row_i < matrix->row; ++row_i)

		{

			for (column_i = 0; column_i < matrix->column; ++column_i)

			{

				index = height_i * matrix->row * matrix->column + row_i * matrix->column + column_i;

				printf("%12.4g", matrix->array[index]);

			}

			printf("\n");

		}

	}

}



//----------------------QR分解-------------------------------------------



//将A分解为Q和R

void QR(Matrix *A, Matrix *Q, Matrix *R)

{

	unsigned  i, j, k, m;

	unsigned size;

	const unsigned N = A->row;

	MatrixType temp;



	Matrix a, b;



	//如果A不是一个二维方阵，则提示错误，函数计算结束

	if (A->row != A->column || 1 != A->height)

	{

		printf("ERROE: QR() parameter A is not a square matrix!\n");

		return;

	}



	size = MatrixCapacity(A);

	if (MatrixCapacity(Q) != size)

	{

		DestroyMatrix(Q);

		SetMatrixSize(Q, A->row, A->column, A->height);

		SetMatrixZero(Q);

	}

	else

	{

		Q->row = A->row;

		Q->column = A->column;

		Q->height = A->height;

	}



	if (MatrixCapacity(R) != size)

	{

		DestroyMatrix(R);

		SetMatrixSize(R, A->row, A->column, A->height);

		SetMatrixZero(R);

	}

	else

	{

		R->row = A->row;

		R->column = A->column;

		R->height = A->height;

	}



	SetMatrixSize(&a, N, 1, 1);

	SetMatrixSize(&b, N, 1, 1);



	for (j = 0; j < N; ++j)

	{

		for (i = 0; i < N; ++i)

		{

			a.array[i] = b.array[i] = A->array[i * A->column + j];

		}



		for (k = 0; k < j; ++k)

		{

			R->array[k * R->column + j] = 0;



			for (m = 0; m < N; ++m)

			{

				R->array[k * R->column + j] += a.array[m] * Q->array[m * Q->column + k];

			}



			for (m = 0; m < N; ++m)

			{

				b.array[m] -= R->array[k * R->column + j] * Q->array[m * Q->column + k];

			}

		}



		temp = MatrixNorm2(&b);

		R->array[j * R->column + j] = temp;



		for (i = 0; i < N; ++i)

		{

			Q->array[i * Q->column + j] = b.array[i] / temp;

		}

	}



	DestroyMatrix(&a);

	DestroyMatrix(&b);

}



//----------------------使用特征值计算矩阵特征向量-----------------

//eigenVector为计算结果即矩阵A的特征向量

//eigenValue为矩阵A的所有特征值，

//A为要计算特征向量的矩阵

void Eigenvectors(Matrix *eigenVector, Matrix *A, Matrix *eigenValue)

{

	unsigned i, j, q;

	unsigned count;

	int m;

	const unsigned NUM = A->column;

	MatrixType eValue;

	MatrixType sum, midSum, mid;

	Matrix temp;



	SetMatrixSize(&temp, A->row, A->column, A->height);



	for (count = 0; count < NUM; ++count)

	{

		//计算特征值为eValue，求解特征向量时的系数矩阵

		eValue = eigenValue->array[count];

		CopyMatrix(&temp, A, 0);

		for (i = 0; i < temp.column; ++i)

		{

			temp.array[i * temp.column + i] -= eValue;

		}



		//将temp化为阶梯型矩阵

		for (i = 0; i < temp.row - 1; ++i)

		{

			mid = temp.array[i * temp.column + i];

			for (j = i; j < temp.column; ++j)

			{

				temp.array[i * temp.column + j] /= mid;

			}



			for (j = i + 1; j < temp.row; ++j)

			{

				mid = temp.array[j * temp.column + i];

				for (q = i; q < temp.column; ++q)

				{

					temp.array[j * temp.column + q] -= mid * temp.array[i * temp.column + q];

				}

			}

		}

		midSum = eigenVector->array[(eigenVector->row - 1) * eigenVector->column + count] = 1;

		for (m = temp.row - 2; m >= 0; --m)

		{

			sum = 0;

			for (j = m + 1; j < temp.column; ++j)

			{

				sum += temp.array[m * temp.column + j] * eigenVector->array[j * eigenVector->column + count];

			}

			sum = -sum / temp.array[m * temp.column + m];

			midSum += sum * sum;

			eigenVector->array[m * eigenVector->column + count] = sum;

		}



		midSum = sqrt(midSum);

		for (i = 0; i < eigenVector->row; ++i)

		{

			eigenVector->array[i * eigenVector->column + count] /= midSum;

		}

	}

	DestroyMatrix(&temp);

}

int BuildMatrix(Matrix* matrix, unsigned row, unsigned column, unsigned height)
{
	matrix->column = row;
	matrix->height = height;
	matrix->row = column;
	matrix->array = (MatrixType*)malloc(row * column * height * sizeof(MatrixType));

	return 0;
}

int MatrixTranspose(const Matrix* matrix, Matrix* C)
{
	BuildMatrix(C, matrix->row, matrix->column, matrix->height);

	for (unsigned  i=0 ; i < matrix->height; i++)
	{
		for (unsigned j = 0; j < matrix->row; j++)
		{
			for (unsigned k = 0; k < C->row; k++)
			{
					C->array[i * C->row * C->column + k *(C->column) + j] = matrix->array[i* matrix->row * matrix->column + j*(matrix->column)+k];
			}
		}
	}

	return 0;
}

int MatrixAdd(const Matrix* A, const Matrix*B, Matrix* C)
{
	if (IsNullMatrix(A)||(IsNullMatrix(B)))
	{
		cout << "The input added Matrix is invalid. " << endl;
	}
	else
	{
		if ((A->row != B->row) || (A->height != B->height) || (A->column != B->column))
		{
			cout << "The size of the input matrixs could not match each other." << endl;
		}
		else
		{
			unsigned size = A->row * A->column * A->height;			
			BuildMatrix(C, A->row, A->column, A->height);

			for (unsigned i = 0; i < size; i++)
			{
				C->array[i] = A->array[i] + B->array[i];
			}

		}
	}

	return 0;
}

int MatrixSubstract(const Matrix* A, const Matrix*B, Matrix* C)
{
	if (IsNullMatrix(A) || (IsNullMatrix(B)))
	{
		cout << "The input added Matrix is invalid. " << endl;
	}
	else
	{
		if ((A->row != B->row) || (A->height != B->height) || (A->column != B->column))
		{
			cout << "The size of the input matrixs could not match each other." << endl;
		}
		else
		{
			unsigned size = A->row * A->column * A->height;
			BuildMatrix(C, A->row, A->column, A->height);

			for (unsigned i = 0; i < size; i++)
			{
				C->array[i] = A->array[i] - B->array[i];
			}

		}
	}

	return 0;
}

int MatrixMultibyMatrix(const Matrix* A,const Matrix* B, Matrix* C)
{
	if (IsNullMatrix(A) || IsNullMatrix(B))
	{
		cout << "The input matrixs are inavalid." << endl;
	}
	else
	{
		if ((A->column != B->row) || (A->height != B->height))
		{
			cout << "The size of the input matrixs could not match each other." << endl;
		}
		else
		{
			BuildMatrix(C, A->row, B->column, A->height);
			Matrix* B_template = new Matrix;
			Matrix* C_template = new Matrix;
			MatrixTranspose(B, B_template);
			MatrixTranspose(C, C_template);

			for (unsigned h = 0; h < A->height; h++)
			{
				for (unsigned i = 0; i < B_template->row; i++)
				{		
					for (unsigned j = 0; j < A->row; j++)
					{
						MatrixType row_template = 0.0;

						for (unsigned k = 0; k < B_template->column; k++)
						{
							row_template += B_template->array[h*B_template->row*B_template->column + i*B_template->column + k] * A->array[h*j*A->row*j*A->column + j*A->column + k];
						}

						C_template->array[h*C_template->column*C_template->row + i*C_template->column+j] = row_template;
	
					}
				}
			}

			MatrixTranspose(C_template, C);
			DestroyMatrix(C_template);
			DestroyMatrix(B_template);
		}
	}

	return 0;
}

int MatrixCopy(const Matrix* matrix,Matrix* C)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		unsigned size = matrix->row * matrix->column * matrix->height;
		BuildMatrix(C, matrix->row, matrix->column, matrix->height);

		for (unsigned i = 0; i < size; i++)
		{
			C->array[i] = matrix->array[i];
		}
	}

	return 0;
}

int MatrixMultibyConst(const Matrix* matrix, Matrix* C, MatrixType con)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		unsigned size = matrix->row * matrix->column * matrix->height;
		BuildMatrix(C, matrix->row, matrix->column, matrix->height);

		for (unsigned i = 0; i < size; i++)
		{
			C->array[i] = matrix->array[i]*con;
		}
	}

	return 0;
}

MatrixType*** MatrixToVector(const Matrix* matrix, ElementType e)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
		return NULL;
	}
	else
	{
		MatrixType*** temp = (MatrixType***)malloc(sizeof(MatrixType**) * matrix->height);

		for (unsigned i = 0; i < matrix->height; i++)
		{
			temp[i] = (MatrixType**)malloc(sizeof(MatrixType*) * matrix->row);

			for (unsigned j = 0; j < matrix->row; j++)
			{
				temp[i][j] = (MatrixType*)malloc(sizeof(MatrixType)*matrix->column);

				if (0 == (int)e)
				{
					for (unsigned k = 0; k < matrix->column; k++)
					{
						temp[i][j][k] = 0;
					}
				}
				else if (1 == (int)e)
				{
					for (unsigned k = 0; k < matrix->column; k++)
					{
						temp[i][j][k] = matrix->array[i*matrix->row*matrix->column + j* matrix->column+k];
					}
				}
			}
		}
		return temp;
	}
}

int BuildVector(Vector* vector, unsigned n)
{
	vector->length = n;
	vector->array = (VectorType *)malloc(sizeof(VectorType)*n);

	return 0;
}

Bool IsNullVector(const Vector* vector)

{
	unsigned size = vector->length;

	if (size <= 0 || vector->array == NULL)

	{
		return True;
	}

	return False;
}

int DestroyVector(Vector* vector)
{
	if (!IsNullVector(vector))
	{
		free(vector->array);
		vector->array = NULL;
	}
	vector->length = 0;
	vector = NULL;

	return 0;
}

int DestoryVectorPoint(MatrixType*** temp, unsigned row, unsigned height)
{
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < row; j++)
		{
			free(temp[i][j]);
			temp[i][j] = NULL;
		}
		free(temp[i]);
		temp[i] = NULL;
	}
	free(temp);
	temp = NULL;

	return 0;
}

int VectorAddByVector(const Vector* A, const Vector* B, Vector* C)
{
	if (IsNullVector(A) || IsNullVector(B))
	{
		cout << "The input vectors are invalid" << endl;
	}
	else
	{
		if (A->length != B->length)
		{
			cout << "The size of the input vectors could not match each other." << endl;
		}
		else
		{
			BuildVector(C, A->length);

			for (unsigned i = 0; i < A->length; i++)
			{
				C->array[i] = A->array[i] + B->array[i];
			}
		}
	}

	return 0;
}

int VectorSubstractVector(const Vector* A, const Vector* B, Vector* C)
{
	if (IsNullVector(A) || IsNullVector(B))
	{
		cout << "The input vectors are invalid" << endl;
	}
	else
	{
		if (A->length != B->length)
		{
			cout << "The size of the input vectors could not match each other." << endl;
		}
		else
		{
			BuildVector(C, A->length);

			for (unsigned i = 0; i < A->length; i++)
			{
				C->array[i] = A->array[i] - B->array[i];
			}
		}
	}

	return 0;
}

VectorType VectorDotProduct(const Vector* A, const Vector* B)
{
	if (IsNullVector(A) || IsNullVector(B))
	{
		cout << "The input vectors are invalid" << endl;
		return 0.0;
	}
	else
	{
		if (A->length != B->length)
		{
			cout << "The size of the input vectors could not match each other." << endl;
			return 0.0;
		}
		else
		{
			VectorType C = 0.0;
			for (unsigned i = 0; i < A->length; i++)
			{
				C += A->array[i] * B->array[i];
			}

			return C;
		}
	}
}

VectorType VectorNorm(const Vector* A)
{
	if (IsNullVector(A))
	{
		cout << "The input vectors are invalid" << endl;
		return 0.0;
	}
	else
	{
		VectorType C = 0.0;
		for (unsigned i = 0; i < A->length; i++)
		{
			C += A->array[i] * A->array[i];
		}
		C = sqrt(C);

		return C;
	}
}

int VectorMultibyConst(const Vector* A, Vector* C, VectorType cons)
{
	if (IsNullVector(A))
	{
		cout << "The input vectors are invalid" << endl;
	}
	else
	{
		BuildVector(C, A->length);

		for (unsigned i = 0; i < A->length; i++)
		{
			C->array[i] = A->array[i] * cons;
		}
	}

	return 0;
}


int MatrixSchmitOrthogonal(const Matrix* matrix, Matrix *I,Matrix* D)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		if (matrix->column != matrix->row)
		{
			cout << "The the input matrix is not a square." << endl;
		}
		else
		{
			unsigned size = matrix->row * matrix->column * matrix->height;
			BuildMatrix(I, matrix->row, matrix->column, matrix->height);
			BuildMatrix(D, matrix->row, matrix->column, matrix->height);

			//这里也可以不用构造double***，直接矩阵转置后for循环赋值也可以，只是这么写比较直观一些
			MatrixType***temp1 = MatrixToVector(matrix, Element);
			MatrixType***temp2 = MatrixToVector(matrix, Zero);
			MatrixType***temp3 = MatrixToVector(matrix, Zero);

			for (unsigned i = 0; i < matrix->height; i++)
			{
				Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * matrix->column);
						
				for (unsigned n = 0; n < matrix->column; n++)
				{
					DividedByVector[n] = new Vector;
					BuildVector(DividedByVector[n], matrix->row);
				}

				for (unsigned j = 0; j < matrix->column; j++)
				{
					temp3[i][j][j] = 1;

					for (unsigned k = 0; k < matrix->row; k++)
					{
						DividedByVector[j]->array[k] = temp1[i][k][j];
					}
				}

				for (unsigned k = 0; k < matrix->row; k++)
				{
					temp2[i][k][0] =DividedByVector[0]->array[k];
				}

				for (unsigned j = 1; j < matrix->column; j++)
				{
					for (int m = (j - 1); m >= 0; m--)
					{
						for (unsigned k = 0; k < matrix->row; k++)
						{
							temp2[i][k][j] += VectorDotProduct(DividedByVector[j], DividedByVector[m]) / VectorDotProduct(DividedByVector[m], DividedByVector[m]) * DividedByVector[m]->array[k];	
							temp3[i][m][j] = VectorDotProduct(DividedByVector[j], DividedByVector[m]) / VectorDotProduct(DividedByVector[m], DividedByVector[m]);
						}
					}

					for (unsigned k = 0; k < matrix->row; k++)
					{
						DividedByVector[j]->array[k] = DividedByVector[j]->array[k] - temp2[i][k][j];
						temp2[i][k][j] = DividedByVector[j]->array[k];
					}
				}
				
				Vector* norm = new Vector;
				BuildVector(norm, matrix->row);

				unsigned rowindex = 0;
				MatrixType div = 0.0;

				for (unsigned j = 0; j < matrix->column; j++)
				{
					for (unsigned k = 0; k < matrix->row; k++)
					{						
						norm->array[k] = temp2[i][k][j];
					}

					div = VectorNorm(norm);

					for (unsigned k = 0; k < matrix->row; k++)
					{
						temp2[i][k][j] = temp2[i][k][j] / div;
					}

					for (unsigned q = 0; q < matrix->column; q++)
					{
						temp3[i][rowindex][q] = temp3[i][rowindex][q] * div;
					}

					rowindex++;

				}
				DestroyVector(norm);

				for (unsigned k = 0; k < matrix->row; k++)
				{
					for (unsigned j = 0; j < matrix->column; j++)
					{
						I->array[i*matrix->column*matrix->row + k * matrix->column + j] = temp2[i][k][j];
						D->array[i*matrix->column*matrix->row + k * matrix->column + j] = temp3[i][k][j];
					}
				}

				for (unsigned n = 0; n < matrix->column; n++)
				{
					DestroyVector(DividedByVector[n]);
				}
				free(DividedByVector);
				DividedByVector = NULL;
			}

			DestoryVectorPoint(temp1,matrix->row,matrix->height);
			DestoryVectorPoint(temp2, matrix->row, matrix->height);
			DestoryVectorPoint(temp3, matrix->row, matrix->height);

		}
	}

	return 0;
}

int MatrixDeterminant(const Matrix* matrix, double* determinant)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		if (matrix->column != matrix->row)
		{
			cout << "The the input matrix is not a square." << endl;
		}
		else
		{	
			for (unsigned i = 0; i < matrix->height; i++)
			{		
				int index = 1;
				double sum = 1.0;
				MatrixType***temp1 = MatrixToVector(matrix, Element);
				Vector* vectemp = new Vector;
				BuildVector(vectemp, matrix->row);
				unsigned goon = 1;

				for (unsigned j = 0; j < matrix->row; j++)
				{
					if (temp1[i][j][j] == 0)
					{
						for (unsigned m = j + 1; m <= matrix->column; m++)
						{
							if (m < matrix->column)
							{
								if (temp1[i][j][m] == 0)
								{
									index *= -1;
								}
								else
								{
									for (unsigned w = 0; w < matrix->row; w++)
									{
										vectemp->array[w] = temp1[i][w][j];
										temp1[i][w][j] = temp1[i][w][m];
										temp1[i][w][m] = vectemp->array[w];
									}
									index *= -1;
									break;
								}
							}
							else
							{
								sum = 0.0;
								goon = 0;
								break;
							}
						}
					}

					if(goon)
					{
						double temvar = 0.0;
						for (unsigned h = j + 1; h < matrix->row; h++)
						{
							temvar = temp1[i][h][j] / temp1[i][j][j];
							for (unsigned k = 0; k < matrix->column; k++)
							{
								temp1[i][h][k] = temp1[i][h][k] - temvar * temp1[i][j][k];
							}
						}
						
					}
				}

				for (unsigned l = 0; l < matrix->row; l++)
				{
					sum *= temp1[i][l][l];
				}
				sum=sum * index;
				determinant[i] = sum;

				//for (unsigned r = 0; r < matrix->row; r++)
				//{
				//	for (unsigned y = 0; y < matrix->column; y++)
				//	{
				//		
				//		cout << temp1[i][r][y] << " ";
				//	}

				//	cout << endl;
				//}
				//getchar();

				DestroyVector(vectemp);
				DestoryVectorPoint(temp1, matrix->row, matrix->height);
				
			}
		}
	}

	return 0;

}
