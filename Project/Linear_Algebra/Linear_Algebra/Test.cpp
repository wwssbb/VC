#include"Function.h"
#include"Variable.h"

int main()

{

	//const unsigned NUM = 50; //最大迭代次数



	//unsigned N = 3;

	//unsigned k;



	//Matrix A, Q, R, temp;

	//Matrix eValue;





	////分配内存

	//SetMatrixSize(&A, N, N, 1);

	//SetMatrixSize(&Q, A.row, A.column, A.height);

	//SetMatrixSize(&R, A.row, A.column, A.height);

	//SetMatrixSize(&temp, A.row, A.column, A.height);

	//SetMatrixSize(&eValue, A.row, 1, 1);



	////A设置为一个简单矩阵

	//A.array[0] = -1;

	//A.array[1] = 2;

	//A.array[2] = 1;

	//A.array[3] = 2;

	//A.array[4] = 4;

	//A.array[5] = -1;

	//A.array[6] = 1;

	//A.array[7] = 1;

	//A.array[8] = -6;





	////拷贝A矩阵元素至temp

	//CopyMatrix(&temp, &A, 0);



	////初始化Q、R所有元素为0

	//SetMatrixZero(&Q);

	//SetMatrixZero(&R);

	////使用QR分解求矩阵特征值

	//for (k = 0; k < NUM; ++k)

	//{

	//	QR(&temp, &Q, &R);

	//	MatrixMultiMatrix(&temp, &R, &Q);

	//}

	////获取特征值，将之存储于eValue

	//for (k = 0; k < temp.column; ++k)

	//{

	//	eValue.array[k] = temp.array[k * temp.column + k];

	//}



	////对特征值按照降序排序

	//SortVector(&eValue, 1);



	////根据特征值eValue，原始矩阵求解矩阵特征向量Q

	//Eigenvectors(&Q, &A, &eValue);



	////打印特征值

	//printf("特征值：");

	//PrintMatrix(&eValue);



	////打印特征向量

	//printf("特征向量");

	//PrintMatrix(&Q);


	//getchar();

	//DestroyMatrix(&A);

	//DestroyMatrix(&R);

	//DestroyMatrix(&Q);

	//DestroyMatrix(&eValue);

	//DestroyMatrix(&temp);





	const unsigned NUM = 50; //最大迭代次数



	unsigned N = 3;

	Matrix A;

	Matrix* B;

	SetMatrixSize(&A, N, N, 1);

	A.array[0] = -1;

	A.array[1] = 2;

	A.array[2] = 1;

	A.array[3] = 2;

	A.array[4] = 4;

	A.array[5] = -1;

	A.array[6] = 1;

	A.array[7] = 1;

	A.array[8] = -6;

	PrintMatrix(&A);

	B = (MatrixTranspose(&A));

	PrintMatrix(B);

	getchar();
	return 0;

}