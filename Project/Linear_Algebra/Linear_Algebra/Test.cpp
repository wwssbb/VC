#include"Function.h"
#include"Variable.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

int main()

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	//const unsigned NUM = 50; //����������
	//unsigned N = 3;

	//unsigned k;



	//Matrix A, Q, R, temp;

	//Matrix eValue;





	////�����ڴ�

	//SetMatrixSize(&A, N, N, 1);

	//SetMatrixSize(&Q, A.row, A.column, A.height);

	//SetMatrixSize(&R, A.row, A.column, A.height);

	//SetMatrixSize(&temp, A.row, A.column, A.height);

	//SetMatrixSize(&eValue, A.row, 1, 1);



	////A����Ϊһ���򵥾���

	//A.array[0] = -1;

	//A.array[1] = 2;

	//A.array[2] = 1;

	//A.array[3] = 2;

	//A.array[4] = 4;

	//A.array[5] = -1;

	//A.array[6] = 1;

	//A.array[7] = 1;

	//A.array[8] = -6;





	////����A����Ԫ����temp

	//CopyMatrix(&temp, &A, 0);



	////��ʼ��Q��R����Ԫ��Ϊ0

	//SetMatrixZero(&Q);

	//SetMatrixZero(&R);

	////ʹ��QR�ֽ����������ֵ

	//for (k = 0; k < NUM; ++k)

	//{

	//	QR(&temp, &Q, &R);

	//	MatrixMultiMatrix(&temp, &R, &Q);

	//}

	////��ȡ����ֵ����֮�洢��eValue

	//for (k = 0; k < temp.column; ++k)

	//{

	//	eValue.array[k] = temp.array[k * temp.column + k];

	//}



	////������ֵ���ս�������

	//SortVector(&eValue, 1);



	////��������ֵeValue��ԭʼ������������������Q

	//Eigenvectors(&Q, &A, &eValue);



	////��ӡ����ֵ

	//printf("����ֵ��");

	//PrintMatrix(&eValue);



	////��ӡ��������

	//printf("��������");

	//PrintMatrix(&Q);


	//getchar();

	//DestroyMatrix(&A);

	//DestroyMatrix(&R);

	//DestroyMatrix(&Q);

	//DestroyMatrix(&eValue);

	//DestroyMatrix(&temp);





	const unsigned NUM = 50; //����������



	unsigned N = 10;

	Matrix* A=new Matrix;

	Matrix* I=new Matrix;

	//Matrix* B=new Matrix;

	//Matrix* C = new Matrix;

	SetMatrixSize(A, 12, 12, 1);
	//SetMatrixSize(B, 3, 1, 1);

	//A->array[0] = -1;

	//A->array[1] = 2;

	//A->array[2] = 1;

	//A->array[3] = 2;

	//A->array[4] = 4;

	//A->array[5] = -1;

	//A->array[6] = 1;

	//A->array[7] = 1;

	//A->array[8] = -6;


	//A->array[0] = 1;

	//A->array[1] = -1;

	//A->array[2] = 1;

	//A->array[3] = -1;

	//A->array[4] = 1;

	//A->array[5] = 1;

	//A->array[6] = 0;

	//A->array[7] = 1;

	//A->array[8] = 1;

	for (unsigned i = 0; i < N*N; i++)
	{
		A->array[i] = rand();
	}



	//B->array[0] = 2;

	//B->array[1] = 5;

	//B->array[2] = 0;
	//PrintMatrix(A);

	//MatrixTranspose(A,B);
	//MatrixMultibyMatrix(A, B, C);
	PrintMatrix(A);
	MatrixSchmitOrthogonal(A, I);
	PrintMatrix(I);

	DestroyMatrix(A);
	A = NULL;
	DestroyMatrix(I);
	I = NULL;
	//PrintMatrix(B);
	//PrintMatrix(C);
	//DestroyMatrix(B);
	//DestroyMatrix(C);
	
	getchar();
	_CrtDumpMemoryLeaks();
	
	return 0;

}