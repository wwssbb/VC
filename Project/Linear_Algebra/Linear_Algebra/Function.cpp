#include"Function.h"

int BuildMatrix(Matrix* matrix, unsigned row, unsigned column, unsigned height)
{
	matrix->column = column;
	matrix->height = height;
	matrix->row = row;
	matrix->array = (MatrixType*)malloc(row * column * height * sizeof(MatrixType));

	unsigned size = height * row * column;
	
	for (unsigned i = 0; i < size; i++)
	{
		matrix->array[i] = 0.0;
	}

	return 0;
}

Bool IsNullMatrix(const Matrix* matrix)
{
	int size = matrix->row * matrix->column * matrix->column;

	if (size <= 0 || matrix->array == NULL)
	{
		return True;
	}
	else
	{
		return False;
	}
}

int DestroyMatrix(Matrix *matrix)
{
	if (!IsNullMatrix(matrix))
	{
		free(matrix->array);
		matrix->array = NULL;
	}

	matrix->row = matrix->column = matrix->height = 0;
	matrix = NULL;

	return 0;
}

int MatrixTranspose(const Matrix* matrix, Matrix* C)
{
	int trigger = 0;

	if (IsNullMatrix(C))
	{
		BuildMatrix(C, matrix->column, matrix->row, matrix->height);
	}
	else
	{
		if ((matrix->height != C->height) || (matrix->row != C->column) || (matrix->column != C->row))
		{
			cout << "The size of input matrixs could not match each other" << endl;
			trigger = 1;
		}
	}

	if (!trigger)
	{
		for (unsigned i = 0; i < matrix->height; i++)
		{
			for (unsigned j = 0; j < matrix->row; j++)
			{
				for (unsigned k = 0; k < C->row; k++)
				{
					//这里的赋值模式要格外小心，不能是常规的数组下标变换就行
					C->array[i * C->row * C->column + k * (C->column) + j] = matrix->array[i* matrix->row * matrix->column + j * (matrix->column) + k];
				}
			}
		}
	}

	return 0;
}

int MatrixAdd(const Matrix* A, const Matrix*B, Matrix* C)
{
	if (IsNullMatrix(A)||(IsNullMatrix(B)))
	{
		cout << "The input matrixs couldn't be null. " << endl;
	}
	else
	{
		if ((A->row != B->row) || (A->height != B->height) || (A->column != B->column))
		{
			cout << "The size of the input matrixs could not match each other." << endl;
		}
		else
		{
			int trigger = 0;

			if (IsNullMatrix(C))
			{
				BuildMatrix(C, A->row, A->column, A->height);
			}
			else  
			{
				if ((A->row != C->row) || (A->height != C->height) || (A->column != C->column))
				{
					cout << "The size of input matrixs could not match each other" << endl;
					trigger = 1;
				}
			}

			if (!trigger)
			{
				unsigned size = A->row * A->column * A->height;

				for (unsigned i = 0; i < size; i++)
				{
					C->array[i] = A->array[i] + B->array[i];
				}
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
			int trigger = 0;

			if (IsNullMatrix(C))
			{
				BuildMatrix(C, A->row, A->column, A->height);
			}
			else
			{
				if ((A->row != C->row) || (A->height != C->height) || (A->column != C->column))
				{
					cout << "The size of input matrixs could not match each other" << endl;
					trigger = 1;
				}
			}

			if (!trigger)
			{
				unsigned size = A->row * A->column * A->height;

				for (unsigned i = 0; i < size; i++)
				{
					C->array[i] = A->array[i] - B->array[i];
				}
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
			int trigger = 0;

			if (IsNullMatrix(C))
			{
				BuildMatrix(C, A->row, B->column, A->height);
			}
			else
			{
				if ((A->row != C->row) || (A->height != C->height) || (B->column != C->column))
				{
					cout << "The size of input matrixs could not match each other" << endl;
					trigger = 1;
				}
			}

			if (!trigger)
			{
				//这是之前偷懒的转置写法
				//Matrix* B_template = new Matrix;
				//Matrix* C_template = new Matrix;
				//MatrixTranspose(B, B_template);
				//MatrixTranspose(C, C_template);

				//for (unsigned h = 0; h < A->height; h++)
				//{
				//	for (unsigned i = 0; i < B_template->row; i++)
				//	{
				//		for (unsigned j = 0; j < A->row; j++)
				//		{
				//			MatrixType row_template = 0.0;

				//			for (unsigned k = 0; k < B_template->column; k++)
				//			{
				//				row_template += B_template->array[h*B_template->row*B_template->column + i * B_template->column + k] * A->array[h * A->row * A->column + j * A->column + k];
				//			}

				//			C_template->array[h*C_template->column*C_template->row + i * C_template->column + j] = row_template;

				//		}
				//	}
				//}

				//MatrixTranspose(C_template, C);
				//DestroyMatrix(C_template);
				//DestroyMatrix(B_template);


				for (int h = 0; h < A->height; h++)
				{
					for (int i = 0; i < B->column; i++)
					{
						for (int j = 0; j < A->row; j++)
						{
							MatrixType row_template = 0.0;

							for (int k = 0; k < A->column; k++)
							{
								row_template += B->array[h * B->row * B->column + i + k * B->column] * A->array[h * A->row * A->column + j * A->column + k];
							}

							C->array[h * C->column * C->row + i + C->column * j] = row_template;

						}
					}
				}
			}
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
		int trigger = 0;

		if (IsNullMatrix(C))
		{
			BuildMatrix(C, matrix->row, matrix->column, matrix->height);
		}
		else
		{
			if ((matrix->row != C->row) || (matrix->height != C->height) || (matrix->column != C->column))
			{
				cout << "The size of input matrixs could not match each other" << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			unsigned size = matrix->row * matrix->column * matrix->height;

			for (unsigned i = 0; i < size; i++)
			{
				C->array[i] = matrix->array[i];
			}
		}
	}

	return 0;
}

int MatrixMultibyConst(const Matrix* matrix, Matrix* C, const MatrixType con)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		int trigger = 0;

		if (IsNullMatrix(C))
		{
			BuildMatrix(C, matrix->row, matrix->column, matrix->height);
		}
		else
		{
			if ((matrix->row != C->row) || (matrix->height != C->height) || (matrix->column != C->column))
			{
				cout << "The size of input matrixs could not match each other" << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			unsigned size = matrix->row * matrix->column * matrix->height;

			for (unsigned i = 0; i < size; i++)
			{
				C->array[i] = matrix->array[i] * con;
			}
		}
	}

	return 0;
}

int MatrixAddbyConst(const Matrix* matrix, Matrix* C, const MatrixType con)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		int trigger = 0;

		if (IsNullMatrix(C))
		{
			BuildMatrix(C, matrix->row, matrix->column, matrix->height);
		}
		else
		{
			if ((matrix->row != C->row) || (matrix->height != C->height) || (matrix->column != C->column))
			{
				cout << "The size of input matrixs could not match each other" << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			unsigned size = matrix->row * matrix->column * matrix->height;

			for (unsigned i = 0; i < size; i++)
			{
				C->array[i] = matrix->array[i] + con;
			}
		}
	}

	return 0;
}

int PrintMatrix(const Matrix* matrix)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The matrix is empty." << endl;
	}
	else
	{
		for (unsigned i = 0; i < matrix->height; i++)
		{
			cout << "The " << i << " sth layer is: " << endl;
			for (unsigned j = 0; j < matrix->row; j++)
			{
				for (unsigned k = 0; k < matrix->column; k++)
				{
					cout << matrix->array[i*matrix->row*matrix->column + j * matrix->column + k] << "\t";
				}
				cout << endl;
			}
			cout << "**************************" << endl;
		}
	}

	return 0;
}

MatrixType*** MatrixTo3DimensionPointer(const Matrix* matrix, ElementType e)
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

				switch (e)
				{
				case Zero:
					for (unsigned k = 0; k < matrix->column; k++)
					{
						temp[i][j][k] = 0.0;
					}
					break;

				case Element:
					for (unsigned k = 0; k < matrix->column; k++)
					{
						temp[i][j][k] = matrix->array[i * matrix->row * matrix->column + j * matrix->column + k];
					}
					break;
				}
			}
		}
		return temp;
	}
}

MatrixType*** Build3DimensionPointer(unsigned row, unsigned column, unsigned height)
{
	MatrixType*** temp = (MatrixType***)malloc(sizeof(MatrixType**)*height);

	for (unsigned i = 0; i < height; i++)
	{
		temp[i] = (MatrixType**)malloc(sizeof(MatrixType*)*row);

		for (unsigned j = 0; j < row; j++)
		{
			temp[i][j] = (MatrixType*)malloc(sizeof(MatrixType)*column);

			for (unsigned k = 0; k < column; k++)
			{
				temp[i][j][k] = 0.0;
			}
		}
	}

	return temp;
}

int Destroy3DimensionPointer(MatrixType*** temp,unsigned row, unsigned height)
{
	for(unsigned i=0;i<height;i++)
	{
		for(unsigned j=0;j<row;j++)
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

MatrixType** Build2DimensionPointer(unsigned row, unsigned column)
{
	MatrixType** temp = (MatrixType**)malloc(sizeof(MatrixType*)*row);

	for (unsigned i = 0; i < row; i++)
	{
		temp[i] = (MatrixType*)malloc(sizeof(MatrixType)*column);

		for (unsigned j = 0; j < column; j++)
		{
			temp[i][j] = 0.0;
		}
	}

	return temp;
}

int Destroy2DimensionPointer(MatrixType** temp, unsigned row)
{
	for (unsigned i = 0; i < row; i++)
	{
		free(temp[i]);
		temp[i] = NULL;
	}
	free(temp);
	temp = NULL;

	return 0;
}

MatrixType* Build1DimensionPointer(unsigned row)
{
	MatrixType* temp = (MatrixType*)malloc(sizeof(MatrixType)*row);

	for (unsigned i = 0; i < row; i++)
	{
		temp[i] = 0.0;
	}

	return temp;
}

int Destroy1DimensionPointer(MatrixType* temp)
{
	free(temp);
	temp = NULL;

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerMultiby3DimensionPointer(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, unsigned columnB, const MatrixType*** B, MatrixType*** C)
{ 
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned p = 0; p < columnB; p++)
		{
			for (unsigned j = 0; j < rowA; j++)
			{
				for (unsigned k = 0; k < columnA; k++)
				{
					C[i][j][p] += A[i][j][k] * B[i][k][p];
				}
			}
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerTranspose(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, MatrixType*** C)
{
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < rowA; j++)
		{
			for (unsigned k = 0; k < columnA; k++)
			{
				C[i][k][j] = A[i][j][k];
			}
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int __3DimensionPointerCopytoMatrix(MatrixType*** temp, unsigned row,unsigned column, unsigned height, Matrix* matrix)
{
	if (IsNullMatrix(matrix))
	{
		BuildMatrix(matrix, row, column, height);
	}
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < matrix->row; j++)
		{
			for (unsigned k = 0; k < matrix->column; k++)
			{
				matrix->array[i * matrix->column * matrix->row + j * matrix->column + k] = temp[i][j][k];
			}
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerAdd(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA,const MatrixType*** B, MatrixType*** C)
{
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < rowA; j++)
		{
			for (unsigned k = 0; k < columnA; k++)
			{
				C[i][j][k] = A[i][j][k]+B[i][j][k];
			}
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerSubstract(const MatrixType*** A, unsigned height, unsigned rowA, unsigned columnA, const MatrixType*** B, MatrixType*** C)
{
	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < rowA; j++)
		{
			for (unsigned k = 0; k < columnA; k++)
			{
				C[i][j][k] = A[i][j][k] - B[i][j][k];
			}
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerAddby2DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[layer][i][j] + B[i][j];			
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerSubstractby2DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[layer][i][j] - B[i][j];
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerAddbyConst(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType con, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[layer][i][j] + con;
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerMultibyConst(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType con, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[layer][i][j] * con;
		}
	}

	return 0;

}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerMultiby2DimensionPointer(MatrixType** A, unsigned rowA, unsigned columnA, unsigned columnB, MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < columnB; i++)
	{
		for (unsigned j = 0; j < rowA; j++)
		{
			for (unsigned k = 0; k < columnA; k++)
			{
				C[j][i] += A[j][k] * B[k][i];
			}
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerCopyto2DimensionPointer(MatrixType** A, unsigned rowA, unsigned columnA, MatrixType** B)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			B[i][j] = A[i][j];
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerMultiby2DimensionPointer(const MatrixType*** A,unsigned layer, unsigned rowA, unsigned columnA, unsigned columnB, const MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < columnB; i++)
	{
		for (unsigned j = 0; j < rowA; j++)
		{
			for (unsigned k = 0; k < columnA; k++)
			{
				C[j][i] += A[layer][j][k] * B[k][i];
			}
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _3DimensionPointerMultiby1DimensionPointer(const MatrixType*** A, unsigned layer, unsigned rowA, unsigned columnA, const MatrixType* B, MatrixType* C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i] += A[layer][i][j] * B[j];
		}
	}
	
	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerMultiby1DimensionPointer(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType* B, MatrixType* C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i] += A[i][j] * B[j];
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerTranspose(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[j][i] = A[i][j];
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerAdd(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{			
			C[i][j] = A[i][j] + B[i][j];			
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerSubstract(const MatrixType** A, unsigned rowA, unsigned columnA, const MatrixType** B, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerAddbyConst(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType con, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[i][j] + con;
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerMultibyConst(const MatrixType** A, unsigned rowA, unsigned columnA, MatrixType con, MatrixType** C)
{
	for (unsigned i = 0; i < rowA; i++)
	{
		for (unsigned j = 0; j < columnA; j++)
		{
			C[i][j] = A[i][j] * con;
		}
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _2DimensionPointerCopytoMatrix(Matrix* matrix, unsigned layer, unsigned rowA, unsigned columnA, MatrixType** A)
{
	int trigger = 0;

	if (IsNullMatrix)
	{
		BuildMatrix(matrix, rowA, columnA, layer);
	}
	else
	{
		if (matrix->row != rowA || matrix->column != columnA || matrix->height < layer)
		{
			cout << "Please recheck the size." << endl;
		}
		trigger = 1;
	}
	if (!trigger)
	{
		for (unsigned i = 0; i < rowA; i++)
		{
			for (unsigned j = 0; j < columnA; j++)
			{
				matrix->array[layer * rowA * columnA + i * columnA + j] = A[i][j];
			}
		}
	}

	return 0;
}
//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _1DimensionPointerMultiby1DimensionPointer(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType& C)
{
	for (unsigned i = 0; i < columnA; i++)
	{
		C += A[i] * B[i];
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _1DimensionPointerSubstract(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType* C)
{
	for (unsigned i = 0; i < columnA; i++)
	{
		C[i] = A[i] - B[i];	
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _1DimensionPointerAdd(const MatrixType* A, unsigned columnA, const MatrixType* B, MatrixType* C)
{
	for (unsigned i = 0; i < columnA; i++)
	{
		C[i] = A[i] + B[i];
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _1DimensionPointerMultibyConst(const MatrixType* A, unsigned columnA, MatrixType con, MatrixType* C)
{
	for (unsigned i = 0; i < columnA; i++)
	{
		C[i]= A[i] * con;
	}

	return 0;
}

//因为无法判别指针所指内存的长度，所以在运算前自行确保矩阵的长宽高相互匹配
int _1DimensionPointerAddbyConst(const MatrixType* A, unsigned columnA, MatrixType con, MatrixType* C)
{
	for (unsigned i = 0; i < columnA; i++)
	{
		C[i] = A[i] + con;
	}

	return 0;
}

///////////////////////////////////////////////////////////////
int BuildVector(Vector* vector, unsigned n)
{
	vector->length = n;
	vector->array = (VectorType *)malloc(sizeof(VectorType)*n);
	//memset(vector, 0.0, n * sizeof(VectorType));

	for (unsigned i = 0; i < vector->length; i++)
	{
		vector->array[i] = 0.0;
	}

	return 0;
}

Bool IsNullVector(const Vector* vector)
{
	int size = vector->length;

	if (size <= 0 || vector->array == NULL)
	{
		return True;
	}
	else
	{
		return False;
	}
}

int VectorCopyToVector(const Vector* A, Vector* B)
{
	if (!IsNullVector(A))
	{
		int judge = 1;

		if (IsNullVector(B))
		{
			BuildVector(B, A->length);
		}
		else if (A->length != B->length)
		{
			cout << "The size of two Vectors can not match.";
			judge = 0;
		}

		if (judge)
		{
			for (unsigned i = 0; i < A->length; i++)
			{
				B->array[i] = A->array[i];
			}
		}

	}
	else
	{
		cout << "The replicated Vector couldn't be Null." << endl;
	}

	return 0;
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

//由于无法获知指针所指向内容大小，所以尺寸得自行判断
int Destroy2DimensionVector(Vector** vector, unsigned column)
{
	for (unsigned i = 0; i < column; i++)
	{
		DestroyVector(vector[i]);
	}
	free(vector);
	vector = NULL;

	return 0;
}

int PrintVector(Vector* vector)
{
	if (!IsNullVector(vector))
	{
		for (unsigned i = 0; i < vector->length; i++)
		{
			cout << vector->array[i] << " "<<endl;
		}
		cout << endl;
	}
	else
	{
		cout << "The input Vector can't be Null." << endl;
	}

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

MatrixType VectorAbsMax(const Vector* vector)
{
	MatrixType Max = 0.0;

	if (!IsNullVector(vector))
	{
		for (unsigned i = 0; i < vector->length; i++)
		{
			if (i == 0)
			{
				Max = abs(vector->array[i]);
			}
			else
			{
				abs(vector->array[i]) >= Max ? Max = abs(vector->array[i]) : Max = Max;
			}
		}
	}
	else
	{
		cout << "The input Vector is invalid." << endl;
	}

	return Max;
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
			int trigger = 0;

			if (IsNullVector(C))
			{
				BuildVector(C, A->length);
			}
			else
			{
				if (C->length != A->length)
				{
					cout << "The input matrixs could not match each other." << endl;
					trigger = 1;
				}
			}

			if (!trigger)
			{
				for (unsigned i = 0; i < A->length; i++)
				{
					C->array[i] = A->array[i] - B->array[i];
				}
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

//向量和矩阵相乘，只能选择三维矩阵的任意第三维的一个二维空间
int MatrixMultibyVector(const Matrix* matrix, unsigned layer, const Vector* vector, Vector* result)
{
	if (IsNullMatrix(matrix)||(IsNullVector(vector)))
	{
		cout << "The input matrix or vector is invalid" << endl;
	}
	else
	{
		if (matrix->column != vector->length)
		{
			cout << "The size of input matrix and vector could not match each other" << endl;
		}
		else
		{
			int trigger = 0;

			if (IsNullVector(result))
			{
				BuildVector(result, matrix->row);
			}
			else
			{
				if (result->length != matrix->row)
				{
					cout << "The size of recept vector could not match the row size of input matrix"<< endl;
					trigger = 1;
				}			
			}

			if (!trigger)
			{
				for (unsigned j = 0;j < matrix->row;j++)
				{
					for (unsigned k = 0; k < matrix->column; k++)
					{
						result->array[j] += matrix->array[layer * matrix->row * matrix->column + j * matrix->column + k] * vector->array[k];
					}
				}
			}
		}
	}

	return 0;
}

//向量和矩阵相乘，只能选择三维矩阵的任意第三维的一个二维空间,由于无法获知指针所指向内容大小，所以尺寸得自行判断
int _3DimensionPointerMultibyVector(const MatrixType*** temp, unsigned row, unsigned column, unsigned layer, const Vector* vector, Vector* result)
{
	if (vector->length != column)
	{
		cout << "The size of input pointer and vector could not match each other" << endl;
	}
	else
	{
		int trigger = 0;

		if (IsNullVector(result))
		{
			BuildVector(result, row);
		}
		else
		{
			if (result->length != row)
			{
				cout << "The size of recept vector could not match the row size of input matrix" << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			for (unsigned j = 0; j < row; j++)
			{
				for (unsigned k = 0; k < column; k++)
				{
					result->array[j] += temp[layer][j][k] * vector->array[k];
				}
			}
		}
	}

	return 0;
}

//由于无法获知指针所指向内容大小，所以尺寸得自行判断
int _2DimensionPointerMultibyVector(const MatrixType** temp, unsigned row, unsigned column, const Vector* vector, Vector* result)
{
	if (vector->length != column)
	{
		cout << "The size of input pointer and vector could not match each other" << endl;
	}
	else
	{
		int trigger = 0;

		if (IsNullVector(result))
		{
			BuildVector(result, row);
		}
		else
		{
			if (result->length != row)
			{
				cout << "The size of recept vector could not match the row size of input matrix" << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			for (unsigned j = 0; j < row; j++)
			{
				for (unsigned k = 0; k < column; k++)
				{
					result->array[j] += temp[j][k] * vector->array[k];
				}
			}
		}
	}

	return 0;
}

//由于无法获知指针所指向内容大小，所以尺寸得自行判断
int _1DimensionPointerMultibyVector(const MatrixType* temp, unsigned column, const Vector* vector, MatrixType& result)
{
	if (vector->length != column)
	{
		cout << "The size of input pointer and vector could not match each other" << endl;
	}
	else
	{
		for (unsigned i = 0; i < column; i++)
		{
			result += temp[i] * vector->array[i];
		}			
	}

	return 0;
}

int VectorMultibyConst(const Vector* A, Vector* C, VectorType cons)
{
	if (IsNullVector(A))
	{
		cout << "The input vectors are invalid" << endl;
	}
	else
	{
		int trigger = 0;

		if (IsNullVector(C))
		{
			BuildVector(C, A->length);
		}
		else
		{
			if (C->length != A->length)
			{
				cout << "The input matrixs could not match each other." << endl;
				trigger = 1;
			}
		}

		if (!trigger)
		{
			for (int i = 0; i < A->length; i++)
			{
				C->array[i] = A->array[i] * cons;
			}
		}
	}

	return 0;
}

//由于无法获知指针所指向内容大小，所以尺寸得自行判断
Vector** _3DimensionPointerCopyto2DimensionVector(const MatrixType*** temp, unsigned layer, unsigned row, unsigned column)
{
	Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * column);

	for (unsigned n = 0; n < column; n++)
	{
		DividedByVector[n] = new Vector;
		BuildVector(DividedByVector[n], row);
	}

	for (unsigned j = 0; j < column; j++)
	{
		for (unsigned k = 0; k < row; k++)
		{
			DividedByVector[j]->array[k] = temp[layer][k][j];
		}
	}

	return DividedByVector;
}

Vector** MatrixCopyto2DimensionVector(const Matrix* matrix, unsigned layer)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
		return NULL;
	}
	else
	{
		Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * matrix->column);
		//memset(DividedByVector, 0.0, matrix->column * sizeof(Vector*));

		for (unsigned n = 0; n < matrix->column; n++)
		{
			DividedByVector[n] = new Vector;
			BuildVector(DividedByVector[n], matrix->row);
		}

		for (unsigned j = 0; j < matrix->column; j++)
		{
			for (unsigned k = 0; k < matrix->row; k++)
			{
				DividedByVector[j]->array[k] = matrix->array[layer * matrix->row * matrix->column + j + k * matrix->column];
			}
		}
		return DividedByVector;
	}
}

int RealMatrixSchmitOrthogonal(const Matrix* matrix, Matrix *I,Matrix* D)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		//正交分解要求原矩阵为方阵
		if (matrix->column != matrix->row)
		{
			cout << "The the input matrix is not a square." << endl;
		}
		else
		{
			unsigned size = matrix->row * matrix->column * matrix->height;
			BuildMatrix(I, matrix->row, matrix->column, matrix->height);
			BuildMatrix(D, matrix->row, matrix->column, matrix->height);

			//temp2用于暂存新正交矩阵，temp3用于暂存上三角归一化后倍数矩阵
			MatrixType***temp2 = MatrixTo3DimensionPointer(matrix, Zero);
			MatrixType***temp3 = MatrixTo3DimensionPointer(matrix, Zero);

			for (unsigned i = 0; i < matrix->height; i++)
			{
				Vector** DividedByVector = MatrixCopyto2DimensionVector(matrix, i);

				//初始化上三角矩阵，对角线都为1
				for (unsigned j = 0; j < matrix->column; j++)
				{
					temp3[i][j][j] = 1;

				}

				//这里相当于是给Beta1赋值，Beta1==Alpha1，其实就是原矩阵第一列
				for (unsigned k = 0; k < matrix->row; k++)
				{
					temp2[i][k][0] = DividedByVector[0]->array[k];
				}

				for (unsigned j = 1; j < matrix->column; j++)
				{
					for (int m = (j - 1); m >= 0; m--)
					{
						for (unsigned k = 0; k < matrix->row; k++)
						{
							temp2[i][k][j] += VectorDotProduct(DividedByVector[j], DividedByVector[m]) / VectorDotProduct(DividedByVector[m], DividedByVector[m]) * DividedByVector[m]->array[k];
						}
						temp3[i][m][j] = VectorDotProduct(DividedByVector[j], DividedByVector[m]) / VectorDotProduct(DividedByVector[m], DividedByVector[m]);
					}

					for (unsigned k = 0; k < matrix->row; k++)
					{
						DividedByVector[j]->array[k] = DividedByVector[j]->array[k] - temp2[i][k][j];
						temp2[i][k][j] = DividedByVector[j]->array[k];
					}
				}

				MatrixType div = 0.0;

				//为求得的正交矩阵归一化，并把倍数赋值到上三角矩阵
				for (unsigned j = 0; j < matrix->column; j++)
				{
					div = VectorNorm(DividedByVector[j]);

					for (unsigned k = 0; k < matrix->row; k++)
					{
						temp2[i][k][j] = temp2[i][k][j] / div;
					}

					for (unsigned q = 0; q < matrix->column; q++)
					{
						temp3[i][j][q] = temp3[i][j][q] * div;
					}

				}

				Destroy2DimensionVector(DividedByVector, matrix->column);
			}
			__3DimensionPointerCopytoMatrix(temp2, matrix->row, matrix->column, matrix->height, I);
			__3DimensionPointerCopytoMatrix(temp3, matrix->row, matrix->column, matrix->height, D);
			Destroy3DimensionPointer(temp2, matrix->row, matrix->height);
			Destroy3DimensionPointer(temp3, matrix->row, matrix->height);
		}
	}

	return 0;
}

int RealMatrixDeterminant(const Matrix* matrix, Vector* determinant)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		//求行列式必须为方阵
		if (matrix->column != matrix->row)
		{
			cout << "The the input matrix is not a square." << endl;
		}
		else
		{	
			//用temp1暂存初始矩阵
			MatrixType***temp1 = MatrixTo3DimensionPointer(matrix, Element);
			int trigger0 = 0;

			if(IsNullVector(determinant))
			{
				BuildVector(determinant, matrix->height);
			}
			else
			{
				if (determinant->length != matrix->height)
				{
					cout << "The input size of vector could not match that of the matrix's third dimension." << endl;
					trigger0 = 1;
				}
			}
		
			if (!trigger0)
			{
				for (unsigned i = 0; i < matrix->height; i++)
				{
					int index = 1;

					//行列式的返回值
					double sum = 1.0;

					//用于暂存中间变量（要调换的列）
					MatrixType middle = 0.0;

					int trigger = 1;

					//对角线找主元和向下消主元是同时进行的，一经发现对角线非主元立刻向下消元
					for (unsigned j = 0; j < matrix->row; j++)
					{
						//如果对角线为0，向右找主元
						if (temp1[i][j][j] == 0)
						{
							for (unsigned m = j + 1; m <= matrix->column; m++)
							{
								if (m < matrix->column)
								{
									//行列式互换相邻行和列需要乘以-1
									if (temp1[i][j][m] == 0)
									{
										index *= -1;
									}
									else
									{
										for (unsigned w = 0; w < matrix->row; w++)
										{
											//vectemp->array[w] = temp1[i][w][j];
											middle = temp1[i][w][j];
											temp1[i][w][j] = temp1[i][w][m];
											temp1[i][w][m] = middle;
										}
										index *= -1;
										break;
									}
								}
								//如果主元到了最后一个元素还是为0，行列式就为0
								else
								{
									sum = 0.0;
									trigger = 0;
									break;
								}
							}
						}

						//这里开始进行消元法，从上至下构造上三角矩阵
						if (trigger)
						{
							double div = 0.0;
							for (unsigned h = j + 1; h < matrix->row; h++)
							{
								div = temp1[i][h][j] / temp1[i][j][j];
								for (unsigned k = 0; k < matrix->column; k++)
								{
									temp1[i][h][k] = temp1[i][h][k] - div * temp1[i][j][k];
								}
							}

						}
					}

					//行列式为对角线主元的累积，同时还要考虑对换列引起的符号变化
					for (unsigned l = 0; l < matrix->row; l++)
					{
						sum *= temp1[i][l][l];
					}
					sum = sum * index;
					determinant->array[i] = sum;
				}						
			}
			Destroy3DimensionPointer(temp1, matrix->row, matrix->height);
		}
	}

	return 0;

}

int RealQR(const Matrix* matrix,Matrix* Q, Matrix* R)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		unsigned row = 0;
		unsigned column = 0;

		//如果为方阵（非稀疏）则不考虑锁定行和列，如果列数大于行数，只计算前面第总行数的列（需要优化），如果行数大于列数则不处理，
		//因为Househoder变换一定能把需要变为0的行全变为0
		if (matrix->column >= matrix->row)
		{
			row = matrix->row;
			column = matrix->row;
		}
		else if (matrix->column < matrix->row)
		{
			column = matrix->column;
			row = matrix->row;
		}

		BuildMatrix(Q, row, row, matrix->height);
		BuildMatrix(R, row, row, matrix->height);

		//temp1用于暂存原矩阵，temp2暂存正交矩阵，temp3暂存上三角矩阵
		MatrixType***temp1 = MatrixTo3DimensionPointer(matrix, Element);
		MatrixType***temp2 = MatrixTo3DimensionPointer(R, Zero);
		MatrixType***temp3 = MatrixTo3DimensionPointer(Q, Zero);

		for (unsigned i = 0; i < matrix->height; i++)
		{
			//Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * column);

			//for (unsigned n = 0; n < column; n++)
			//{
			//	DividedByVector[n] = new Vector;
			//	BuildVector(DividedByVector[n], row);
			//}

			//for (unsigned j = 0; j < column; j++)
			//{
			//	for (unsigned k = 0; k < row; k++)
			//	{
			//		DividedByVector[j]->array[k] = temp1[i][k][j];
			//	}
			//}

			Vector** DividedByVector = MatrixCopyto2DimensionVector(matrix, i);

			unsigned num = row;
			unsigned t = 0;

			//为了暂存H矩阵累乘的中间结果
			MatrixType** tempHI = Build2DimensionPointer(row, row);
			for (unsigned hi = 0; hi < row; hi++)
			{
				tempHI[hi][hi] = 1;
			}

			//MatrixType** tempHM = Build2DimensionPointer(row, row);

			//为矩阵的前（n-1）列创建HouseHolder矩阵
			for (unsigned j = 0; j < column-1; j++)
			{
				//构造原始列向量要映射到的单位坐标系
				Vector* norm = new Vector;
				BuildVector(norm, num);
				norm->array[0] = 1;

				Vector* DividedByVectortemp = new Vector;
				BuildVector(DividedByVectortemp, num);

				unsigned tt = 0;
				for (unsigned q = t; q < row; q++)
				{
					DividedByVectortemp->array[tt] = DividedByVector[j]->array[q];
					tt++;
				}

				//Vector* tempnorm = new Vector;
				//VectorMultibyConst(norm, tempnorm, VectorNorm(DividedByVectortemp));
				VectorMultibyConst(norm, norm, VectorNorm(DividedByVectortemp));

				//Vector* tempnorm2 = new Vector;
				//VectorSubstractVector(DividedByVectortemp, tempnorm, tempnorm2);
				VectorSubstractVector(DividedByVectortemp, norm, norm);

				//Vector* tempnorm3 = new Vector;
				//VectorMultibyConst(tempnorm2, tempnorm3, 1 / VectorNorm(tempnorm2));
				VectorMultibyConst(norm, norm, 1 / VectorNorm(norm));


				//用来存放单位矩阵
				//MatrixType** tempI = Build2DimensionPointer(tempnorm3->length, tempnorm3->length);
				MatrixType** tempI = Build2DimensionPointer(norm->length, norm->length);

				//用来存放2*w*w（转置）
				//MatrixType** tempW = Build2DimensionPointer(tempnorm3->length, tempnorm3->length);
				MatrixType** tempW = Build2DimensionPointer(norm->length, norm->length);

				//用来暂存（n-1）此H矩阵累乘的转置（正交矩阵）
				MatrixType** tempR = Build2DimensionPointer(row, column);

				//用来暂存原始（n-1）次原始矩阵左侧的H矩阵（Householder变换）
				MatrixType** tempH= Build2DimensionPointer(row, row);

				for (unsigned q = 0; q < row; q++)
				{
					tempH[q][q] = 1;
				}

				//for (unsigned q = 0; q < tempnorm3->length; q++)
				for (unsigned q = 0; q < norm->length; q++)
				{
					//for (unsigned p = 0; p < tempnorm3->length; p++)
					for (unsigned p = 0; p < norm->length; p++)
					{
						//tempW[p][q] = tempnorm3->array[p] * tempnorm3->array[q];
						tempW[p][q] = norm->array[p] * norm->array[q];
					}
					tempI[q][q] = 1;
				}

				for (unsigned p = 0; p < num; p++)
				{
					for (unsigned q =0 ; q < num; q++)
					{
						//htemp[j][t + p][t + q] = tempI[p][q]-2*tempW[p][q];
						tempH[t + p][t + q]= tempI[p][q] - 2 * tempW[p][q];
					}
				}

				for (unsigned p = 0; p < row; p++)
				{					
					for (unsigned q = 0; q < row; q++)
					{
						MatrixType te = 0.0;

						for (unsigned m = 0; m < row; m++)
						{
							te += tempHI[q][m] * tempH[m][p];
						}

						temp3[i][q][p] = te;
					}
				}

				//_2DimensionPointerMultiby2DimensionPointer(tempHI, row, row, row, tempH, tempHM);
				//_2DimensionPointerCopyto2DimensionPointer(tempHM, row,row,tempHI);


				for (unsigned p = 0; p < row; p++)
				{
					for (unsigned q = 0; q < row; q++)
					{
						tempHI[p][q] = temp3[i][p][q];
					}
				}

				for (unsigned p = 0; p < column; p++)
				{
					for (unsigned q = 0; q < row; q++)
					{
						for (unsigned m = 0; m < row; m++)
						{
							tempR[q][p] += tempH[q][m] * DividedByVector[p]->array[m];
						}				
					}
				}

				for (unsigned p = 0; p < column; p++)
				{
					for (unsigned q = 0; q < row; q++)
					{
						DividedByVector[p]->array[q] = tempR[q][p];
					}
				}

				DestroyVector(norm);
				DestroyVector(DividedByVectortemp);
				//DestroyVector(tempnorm);
				//DestroyVector(tempnorm2);
				//DestroyVector(tempnorm3);

				//Destroy2DimensionPointer(tempI, tempnorm3->length);
				Destroy2DimensionPointer(tempI, norm->length);
				//Destroy2DimensionPointer(tempW, tempnorm3->length);
				Destroy2DimensionPointer(tempW, norm->length);
				Destroy2DimensionPointer(tempR, row);
				Destroy2DimensionPointer(tempH, row);

				t++;
				num--;
			}
			for (unsigned p = 0; p < column; p++)
			{
				for (unsigned q = 0; q < row; q++)
				{
					temp2[i][q][p] = DividedByVector[p]->array[q];
				}
			}

			//_2DimensionPointerCopytoMatrix(Q, i, row, row, tempHI);
			//for (unsigned q = 0; q < row; q++)
			//{
			//	for (unsigned p= 0; p < row; p++)
			//	{
			//		R->array[i*row*row + q * row + p] = temp2[i][q][p];
			//		Q->array[i*row*row + q * row + p]= temp3[i][q][p];
			//	}
			//}

			//for (unsigned p = 0; p < column; p++)
			//{
			//	DestroyVector(DividedByVector[p]);
			//}
			//free(DividedByVector);
			//DividedByVector = NULL;

			Destroy2DimensionVector(DividedByVector, column);
			Destroy2DimensionPointer(tempHI, row);
			//Destroy2DimensionPointer(tempHM, row);

		}
		__3DimensionPointerCopytoMatrix(temp2, row, column, matrix->height, R);
		__3DimensionPointerCopytoMatrix(temp3, row, column, matrix->height, Q);
		Destroy3DimensionPointer(temp1, matrix->row, matrix->height);
		Destroy3DimensionPointer(temp2, row, matrix->height);
		Destroy3DimensionPointer(temp3, row, matrix->height);
	}

	return 0;
}

int RealGivens(const Matrix* matrix, Matrix* Q, Matrix* R)
{
	if (IsNullMatrix(matrix)||matrix->row<2)
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		unsigned row = 0;
		unsigned column = 0;

		if (matrix->column >= matrix->row)
		{
			cout << "." << endl;
			row = matrix->row;
			column = matrix->row;
		}
		else if (matrix->column < matrix->row)
		{
			cout << "." << endl;
			column = matrix->column;
			row = matrix->row;
		}

		BuildMatrix(Q, row, row, matrix->height);
		BuildMatrix(R, row, row, matrix->height);

		MatrixType***temp1 = MatrixTo3DimensionPointer(matrix, Element);
		MatrixType***temp2 = MatrixTo3DimensionPointer(R, Zero);
		MatrixType***temp3 = MatrixTo3DimensionPointer(Q, Zero);

		for (unsigned i = 0; i < matrix->height; i++)
		{
			Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * column);

			for (unsigned n = 0; n < column; n++)
			{
				DividedByVector[n] = new Vector;
				BuildVector(DividedByVector[n], row);
			}

			for (unsigned j = 0; j < column; j++)
			{
				for (unsigned k = 0; k < row; k++)
				{
					DividedByVector[j]->array[k] = temp1[i][k][j];
				}
			}

			unsigned index = 0;

			MatrixType** tempHI = Build2DimensionPointer(row, row);

			for (unsigned hi = 0; hi < row; hi++)
			{
				tempHI[hi][hi] = 1;
			}

			for (unsigned j = 0; j < column - 1; j++)
			{		
				MatrixType** tempRt= Build2DimensionPointer(row, row);

				for (unsigned zz = index+1; zz < row; zz++)
				{	
					MatrixType** tempR = Build2DimensionPointer(row, row);

					for (unsigned z = 0; z < row; z++)
					{
						tempR[z][z] = 1;
					}

					MatrixType C = DividedByVector[j]->array[index] / (sqrt(DividedByVector[j]->array[index] * DividedByVector[j]->array[index] + DividedByVector[j]->array[zz] * DividedByVector[j]->array[zz]));
					MatrixType S= DividedByVector[j]->array[zz] / (sqrt(DividedByVector[j]->array[index] * DividedByVector[j]->array[index] + DividedByVector[j]->array[zz] * DividedByVector[j]->array[zz]));

					tempR[index][index] = C;
					tempR[index][zz] = S;
					tempR[zz][index] = -S;
					tempR[zz][zz] = C;


					//for (unsigned p = 0; p < row; p++)
					//{
					//	for (unsigned q = 0; q < row; q++)
					//	{
					//		cout << tempR[p][q] << " ";
					//	}
					//	cout << endl;
					//}
					//getchar();

					//for (unsigned p = 0; p < row; p++)
					//{
					//	for (unsigned q = 0; q < column; q++)
					//	{
					//		cout << DividedByVector[q]->array[p] << " ";
					//	}
					//	cout << endl;
					//}
					//getchar();



					for (unsigned p = 0; p < column; p++)
					{
						for (unsigned q = 0; q < row; q++)
						{
							MatrixType d = 0.0;

							for (unsigned m = 0; m < row; m++)
							{
								d += tempR[q][m] * DividedByVector[p]->array[m];
							}
							tempRt[q][p] = d;
						}

					}

					//
					//for (unsigned p = 0; p < row; p++)
					//{
					//	for (unsigned q = 0; q < row; q++)
					//	{
					//		cout << tempRt[p][q] << " ";
					//	}
					//	cout << endl;
					//}
					//getchar();


					for (unsigned p = 0; p < column; p++)
					{
						for (unsigned q = 0; q < row; q++)
						{
							DividedByVector[p]->array[q] = tempRt[q][p];
						}
					}

					for (unsigned p = 0; p < row; p++)
					{
						for (unsigned q = 0; q < row; q++)
						{
							MatrixType te = 0.0;

							for (unsigned m = 0; m < row; m++)
							{
								te += tempHI[q][m] * tempR[m][p];
							}

							temp3[i][q][p] = te;
						}
					}


					//
					//for (unsigned p = 0; p < row; p++)
					//{
					//	for (unsigned q = 0; q < row; q++)
					//	{
					//		cout << temp3[i][p][q] << " ";
					//	}
					//	cout << endl;
					//}
					//getchar();


					for (unsigned p = 0; p < row; p++)
					{
						for (unsigned q = 0; q < row; q++)
						{
							tempHI[p][q] = temp3[i][p][q];
						}
					}
					
					Destroy2DimensionPointer(tempR, row);

				}

				for (unsigned p = 0; p < row; p++)
				{
					for (unsigned q = 0; q < row; q++)
					{
						temp2[i][p][q] = tempRt[p][q];
					}
				}

				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < column; q++)
				//	{
				//		cout << temp2[i][q][p] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				Destroy2DimensionPointer(tempRt, row);

				index++;

			}

			for (unsigned q = 0; q < row; q++)
			{
				for (unsigned p = 0; p < row; p++)
				{
					R->array[i*row*row + q * row + p] = temp2[i][q][p];
					Q->array[i*row*row + q * row + p] = temp3[i][q][p];
				}
			}

			for (unsigned p = 0; p < column; p++)
			{
				DestroyVector(DividedByVector[p]);
			}
			free(DividedByVector);
			DividedByVector = NULL;

			Destroy2DimensionPointer(tempHI, row);

		}
		Destroy3DimensionPointer(temp1, matrix->row, matrix->height);
		Destroy3DimensionPointer(temp2, row, matrix->height);
		Destroy3DimensionPointer(temp3, row, matrix->height);
		
	}

	return 0;
}



int RealHessenBurg(const Matrix* matrix, Matrix* H, Matrix* P)
{
	if (IsNullMatrix(matrix) || matrix->column != matrix->row)
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		unsigned row = matrix->row;
		unsigned column = matrix->column;

		BuildMatrix(H, row, row, matrix->height);
		BuildMatrix(P, row, row, matrix->height);
		Matrix* H1 = new Matrix;
		BuildMatrix(H1, row, row, matrix->height);

		MatrixType***temp1 = MatrixTo3DimensionPointer(matrix, Element);
		MatrixType***temp2 = MatrixTo3DimensionPointer(H, Zero);
		MatrixType***temp3 = MatrixTo3DimensionPointer(P, Zero);

		for (int i = 0; i < matrix->height; i++)
		{
			Vector** DividedByVector = (Vector**)malloc(sizeof(Vector*) * column);

			for (int n = 0; n < column; n++)
			{
				DividedByVector[n] = new Vector;
				BuildVector(DividedByVector[n], row);
			}

			for (int j = 0; j < column; j++)
			{
				for (int k = 0; k < row; k++)
				{
					DividedByVector[j]->array[k] = temp1[i][k][j];
				}
			}

			unsigned num = row-1;
			unsigned t = 1;

			MatrixType** tempHI = Build2DimensionPointer(row, row);
			for (int hi = 0; hi < row; hi++)
			{
				tempHI[hi][hi] = 1;
			}

			for (int j = 0; j < column - 2; j++)
			{

				Vector* norm = new Vector;
				BuildVector(norm, num);
				norm->array[0] = 1;

				Vector* DividedByVectortemp = new Vector;
				BuildVector(DividedByVectortemp, num);

				int tt = 0;
				for (int q = t; q < row; q++)
				{
					DividedByVectortemp->array[tt] = DividedByVector[j]->array[q];
					tt++;
				}

				Vector* tempnorm = new Vector;
				VectorMultibyConst(norm, tempnorm, VectorNorm(DividedByVectortemp));

				Vector* tempnorm2 = new Vector;
				VectorSubstractVector(DividedByVectortemp, tempnorm, tempnorm2);

				Vector* tempnorm3 = new Vector;
				VectorMultibyConst(tempnorm2, tempnorm3, 1 / VectorNorm(tempnorm2));

				MatrixType** tempI = Build2DimensionPointer(tempnorm3->length, tempnorm3->length);

				MatrixType** tempW = Build2DimensionPointer(tempnorm3->length, tempnorm3->length);

				MatrixType** tempH = Build2DimensionPointer(row, row);

				MatrixType** tempP = Build2DimensionPointer(row, row);

				for (int q = 0; q < row; q++)
				{
					tempP[q][q] = 1;
				}

				for (int q = 0; q < tempnorm3->length; q++)
				{
					for (int p = 0; p < tempnorm3->length; p++)
					{
						tempW[p][q] = tempnorm3->array[p] * tempnorm3->array[q];
					}
					tempI[q][q] = 1;
				}

				for (int p = 0; p < num; p++)
				{
					for (int q = 0; q < num; q++)
					{
						tempP[t + p][t + q] = tempI[p][q] - 2 * tempW[p][q];
					}
				}


				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < row; q++)
				//	{
				//		cout << tempHI[p][q] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				for (int p = 0; p < row; p++)
				{
					for (int q = 0; q < row; q++)
					{
						MatrixType te = 0.0;

						for (int m = 0; m < row; m++)
						{
							te += tempP[q][m] * tempHI[m][p];
						}

						temp3[i][q][p] = te;
					}
				}

				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < row; q++)
				//	{
				//		cout << temp3[i][p][q] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				for (int p = 0; p < row; p++)
				{
					for (int q = 0; q < row; q++)
					{
						tempHI[p][q] = temp3[i][p][q];
					}
				}

				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < row; q++)
				//	{
				//		cout << htemp[j][p][q] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				for (int p = 0; p < column; p++)
				{
					for (int q = 0; q < row; q++)
					{
						for (int m = 0; m < row; m++)
						{
							tempH[q][p] += tempP[q][m] * DividedByVector[p]->array[m];
						}
					}
				}

				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < row; q++)
				//	{
				//		cout << tempH[p][q] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				//
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < column; q++)
				//	{
				//		cout << tempR[p][q]<< " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				for (int p = 0; p < column; p++)
				{
					for (int q = 0; q < row; q++)
					{
						DividedByVector[p]->array[q] = tempH[q][p];
					}
				}

				
				//for (unsigned p = 0; p < row; p++)
				//{
				//	for (unsigned q = 0; q < column; q++)
				//	{
				//		cout << DividedByVector[p]->array[q] << " ";
				//	}
				//	cout << endl;
				//}
				//getchar();

				DestroyVector(norm);
				DestroyVector(DividedByVectortemp);
				DestroyVector(tempnorm);
				DestroyVector(tempnorm2);
				DestroyVector(tempnorm3);

				Destroy2DimensionPointer(tempI, tempnorm3->length);
				Destroy2DimensionPointer(tempW, tempnorm3->length);
				Destroy2DimensionPointer(tempH, row);
				Destroy2DimensionPointer(tempP, row);

				t++;
				num--;
			}
			for (int p = 0; p < column; p++)
			{
				for (int q = 0; q < row; q++)
				{
					temp2[i][q][p] = DividedByVector[p]->array[q];
				}
			}

			for (int q = 0; q < row; q++)
			{
				for (int p = 0; p < row; p++)
				{
					H1->array[i*row*row + q * row + p] = temp2[i][q][p];
					P->array[i*row*row + q * row + p] = temp3[i][q][p];
				}
			}

			for (int p = 0; p < column; p++)
			{
				DestroyVector(DividedByVector[p]);
			}
			free(DividedByVector);
			DividedByVector = NULL;
			Destroy2DimensionPointer(tempHI, row);

		}

		MatrixMultibyMatrix(H1,P, H);

		DestroyMatrix(H1);
		Destroy3DimensionPointer(temp1, matrix->row, matrix->height);
		Destroy3DimensionPointer(temp2, row, matrix->height);
		Destroy3DimensionPointer(temp3, row, matrix->height);
	}


	return 0;
}

int EginValue(const Matrix* matrix,Matrix* E,Matrix* EV)
{
	if (IsNullMatrix(matrix) || matrix->column != matrix->row)
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		Matrix* P = new Matrix;
		RealHessenBurg(matrix, E, P);
		int trigger = 0;

		for (int i = 0; i < 2000; i++)
		{
			Matrix *Q = new Matrix;
			Matrix *R = new Matrix;

			RealQR(E, Q, R);

			MatrixMultibyMatrix(R, Q, E);

			//if (i == 999)
			//{
			//	MatrixCopy(Q, EV);
			//}
			
			DestroyMatrix(Q);
			DestroyMatrix(R);
		}

		BuildMatrix(EV, E->row, E->column, E->height);

		MatrixType***temp2 = MatrixTo3DimensionPointer(EV, Zero);
		
		for (int i = 0; i < E->row; i++)
		{
			Matrix* gama = new Matrix;
			Matrix* deta = new Matrix;
			Matrix *Q1 = new Matrix;
			Matrix *R1 = new Matrix;

			BuildMatrix(gama, E->row, E->column, E->height);

			for (int h = 0; h < E->height; h++)
			{
				for (int j = 0; j < E->row; j++)
				{
					gama->array[h * gama->row * gama->column + j * gama->column + j] = E->array[h * E->row * E->column + i * E->column + i];
				}				
			}

			MatrixSubstract(gama, matrix,deta);

			//直接QR分解构造上三角矩阵
			//RealQR(deta, Q1, R1);

			//Gaussian主元法
			/*********这部分测试使用*******/
			//PrintMatrix(deta);
			//getchar();
			MatrixType***tp1 = MatrixTo3DimensionPointer(deta, Element);

			for (unsigned i = 0; i < deta->height; i++)
			{
				//用于暂存中间变量（要调换的列）
				MatrixType middle = 0.0;

				//对角线找主元和向下消主元是同时进行的，一经发现对角线非主元立刻向下消元
				for (unsigned j = 0; j < deta->row; j++)
				{
					//如果对角线为0，向右找主元
					if (tp1[i][j][j] == 0)
					{
						for (unsigned m = j + 1; m <= deta->column; m++)
						{
							if (m < deta->column)
							{
								//行列式互换相邻行和列需要乘以-1
								if (tp1[i][j][m] == 0)
								{

								}
								else
								{
									for (unsigned w = 0; w < deta->row; w++)
									{
										middle = tp1[i][w][j];
										tp1[i][w][j] = tp1[i][w][m];
										tp1[i][w][m] = middle;
									}
									break;
								}
							}
						}
					}

					double div = 0.0;
					for (unsigned h = j + 1; h < deta->row; h++)
					{
						div = tp1[i][h][j] / tp1[i][j][j];
						for (unsigned k = 0; k < deta->column; k++)
						{
							tp1[i][h][k] = tp1[i][h][k] - div * tp1[i][j][k];
						}
					}
				}
			}
			__3DimensionPointerCopytoMatrix(tp1, deta->row, deta->column, deta->height, R1);

			//PrintMatrix(R1);
			//getchar();
			Destroy3DimensionPointer(tp1, deta->row, deta->height);
			/****************这部分测试使用******************/



			MatrixType***temp1 = MatrixTo3DimensionPointer(R1, Element);

			for (int h = 0; h < R1->height; h++)
			{
				temp2[h][R1->row - 1][i] = 1.0;

				for (int ii = R1->row - 2; ii >= 0; ii--)
				{
					MatrixType T = 0.0;

					for (int jj = ii + 1; jj < R1->column; jj++)
					{
						T += temp1[h][ii][jj] * temp2[h][jj][i];

						temp2[h][ii][i] = -T / temp1[h][ii][ii];
					}
				}

				//normalize the eigen vector
				MatrixType TT = 0.0;
				
				for (int jj = 0; jj <R1->row; jj++)
				{
					TT += temp2[h][jj][i]* temp2[h][jj][i];
				}

				TT = sqrt(TT);

				for (int jj = 0; jj < R1->row; jj++)
				{
					temp2[h][jj][i] = temp2[h][jj][i]/TT;
				}							
			}

			DestroyMatrix(gama);
			DestroyMatrix(deta);
			DestroyMatrix(Q1);
			DestroyMatrix(R1);
			Destroy3DimensionPointer(temp1, E->row, E->height);
		}


		__3DimensionPointerCopytoMatrix(temp2, E->row, E->column, E->height, EV);
		Destroy3DimensionPointer(temp2, E->row, E->height);

		DestroyMatrix(P);

	}

	return 0;
}

int EginVectorReal(const Matrix* matrix, Vector* EV, MatrixType& Lambda)
{
	if (IsNullMatrix(matrix) || matrix->column != matrix->row)
	{
		cout << "The input matrix is invalid" << endl;
	}
	else
	{
		MatrixType***temp1 = MatrixTo3DimensionPointer(matrix, Element);

		BuildVector(EV, matrix->row);

		for (unsigned i = 0; i < matrix->height; i++)
		{
			Vector* v = new Vector;
			BuildVector(v, matrix->row);

			while (1)
			{
				for (unsigned t = 0; t < v->length; t++)
				{
					v->array[t] = rand();
					//v->array[t] = 1;
				}

				if (VectorNorm(v) != 0)
				{
					break;
				}
			}

			//
			//PrintVector(v);
			//getchar();

			for (unsigned times = 0; times < 1000; times++)
			{

				Vector* vn = new Vector;
				BuildVector(vn, matrix->row);

				for (unsigned j = 0; j < matrix->row; j++)
				{
					for (unsigned k = 0; k < matrix->column; k++)
					{
						vn->array[j] += temp1[i][j][k] * v->array[k];
					}
				}

				//
				//PrintVector(vn);
				///getchar();

				//
				//cout << VectorAbsMax(vn) << endl;
				//getchar();

				VectorMultibyConst(vn, v, 1 / VectorAbsMax(vn));

				DestroyVector(vn);
				//
				//PrintVector(v);
				//getchar();

				//VectorCopyToVector(vn, v);
			}

			VectorCopyToVector(v, EV);

			Vector* vn = new Vector;
			BuildVector(vn, matrix->row);

			for (unsigned j = 0; j < matrix->row; j++)
			{
				for (unsigned k = 0; k < matrix->column; k++)
				{
					vn->array[j] += temp1[i][j][k] * v->array[k];
				}
			}

			//
			//PrintVector(vn);
			//PrintVector(v);
			//getchar();

			VectorMultibyConst(vn, v, 1 / VectorAbsMax(v));

			//
			//PrintVector(v);
			//getchar();

			Lambda = VectorAbsMax(v);

			DestroyVector(v);
			DestroyVector(vn);
		}
		Destroy3DimensionPointer(temp1, matrix->row, matrix->height);
	}

	return 0;
}

int SVDReal(const Matrix* matrix, Matrix* U, Matrix* T, Matrix* V)
{
	if (IsNullMatrix(matrix))
	{
		cout << "The input matrix is empty." << endl;
	}
	else
	{
		int row = (matrix->column < matrix->row) ? matrix->column : matrix->row;

		Matrix* MT = new Matrix;

		Matrix* MT1 = new Matrix;

		Matrix* MT2 = new Matrix;

		Matrix* UE = new Matrix;

		Matrix* VE = new Matrix;

		MatrixTranspose(matrix, MT);

		MatrixMultibyMatrix(matrix, MT, MT1);

		MatrixMultibyMatrix(MT, matrix, MT2);


		EginValue(MT2, VE, V);

		BuildMatrix(T, matrix->row, matrix->column, matrix->height);

		for (int h = 0; h < T->height; h++)
		{
			for (int i = 0; i < row; i++)
			{
				T->array[h * T->row * T->column + i * T->column + i] = sqrt(VE->array[h * VE->row * VE->column + i * VE->column + i]);
			}
		}

		//MatrixMultibyMatrix(matrix, V, U);

		//for (int h = 0; h < U->height; h++)
		//{
		//	for (int j = 0; j < U->column; j++)
		//	{
		//		for (int i = 0; i < U->row; i++)
		//		{
		//			U->array[h * U->row * U->column + i * U->column + j] = U->array[h * U->row * U->column + i * U->column + j] / T->array[h * T->row * T->column + j * T->column + j];
		//		}
		//	}
		//}

		MatrixTranspose(V,V);

		EginValue(MT1, UE, U);

		DestroyMatrix(MT);
		DestroyMatrix(MT1);
		DestroyMatrix(MT2);
		DestroyMatrix(UE);
		DestroyMatrix(VE);

	}

	return 0;
}

int SVDInv(const Matrix* matrix, Matrix* C)
{
	Matrix* U = new Matrix;
	Matrix* T = new Matrix;
	Matrix* V = new Matrix;
	Matrix* Cm1 = new Matrix;

	SVDReal(matrix, U, T, V);

	MatrixTranspose(T, T);

	MatrixTranspose(U, U);

	MatrixMultibyMatrix(V, T, Cm1);

	MatrixMultibyMatrix(Cm1,U,C);

	DestroyMatrix(U);
	DestroyMatrix(T);
	DestroyMatrix(V);
	DestroyMatrix(Cm1);

	return 0;
}