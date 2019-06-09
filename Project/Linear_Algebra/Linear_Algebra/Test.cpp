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
	/*unsigned N = 2;*/

	//unsigned k;



	//Matrix A, Q, R, temp;

	//Matrix eValue;





	////�����ڴ�

	/*SetMatrixSize(&A, N, N, 1);
*/
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



	unsigned N = 5;

	Matrix* A=new Matrix;

	Matrix* Q = new Matrix;

	Matrix* R = new Matrix;

	Matrix* Q1 = new Matrix;

	Matrix* R1 = new Matrix;

	Matrix* I=new Matrix;

	Matrix* D = new Matrix;

	Matrix* H = new Matrix;

	Matrix* P = new Matrix;

	Matrix* E = new Matrix;
	Matrix* EV = new Matrix;
	//Matrix* B=new Matrix;

	//Matrix* C = new Matrix;

	SetMatrixSize(A, N, N, 1);
	//double* determinant = new double[N] {};
	//SetMatrixSize(B, 3, 1, 1);

	//A->array[0] = 1;

	//A->array[1] = 3;

	//A->array[2] = 3;

	//A->array[3] = 4;

	//A->array[4] = 3;

	//A->array[5] = 1;

	//A->array[6] = 2;

	//A->array[7] = 3;

	//A->array[8] = 3;

	//A->array[9] = 2;

	//A->array[10] = 1;

	//A->array[11] = 5;

	//A->array[12] = 4;

	//A->array[13] = 3;

	//A->array[14] = 5;

	//A->array[15] = 1;


	//A->array[0] = 5;

	//A->array[1] = -3;

	//A->array[2] = 2;

	//A->array[3] = 6;

	//A->array[4] = -4;

	//A->array[5] = 4;

	//A->array[6] = 4;

	//A->array[7] = -4;

	//A->array[8] = 5;
	//A->array[9] = 4;

	//A->array[10] = 1;

	//A->array[11] = 2;

	//A->array[12] = 4;

	//A->array[13] = 1;

	//A->array[14] = 2;

	//A->array[15] = 3;
	//A->array[16] = 0;
	//A->array[17] = 1;
	//A->array[18] = 1;
	//A->array[19] = 1;
	//A->array[20] = 0;
	//A->array[21] = 0;
	//A->array[22] = 0;
	//A->array[23] = 0;
	//A->array[24] = 1;



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
	//PrintMatrix(A);
	//RealHessenBurg(A, H, P);
	EginValue(A, E,EV);
	PrintMatrix(A);
	PrintMatrix(E);
	//PrintMatrix(EV);
	//PrintMatrix(H);
	//PrintMatrix(P);
	cout << endl;
	getchar();

	RealGivens(A, Q, R);
	RealQR(A, Q1, R1);
	MatrixSchmitOrthogonal(A, I, D);

	PrintMatrix(A);
	cout << endl;

	PrintMatrix(R1);
	PrintMatrix(Q1);
	cout << endl;

	PrintMatrix(R);
	PrintMatrix(Q);
	cout << endl;

	PrintMatrix(I);
	PrintMatrix(D);
	getchar();
	/*MatrixSchmitOrthogonal(A, I, D);*/
	//PrintMatrix(I);
	//PrintMatrix(D);
	//DestroyMatrix(A);

	//MatrixDeterminant(A, determinant);
	DestroyMatrix(A);
	DestroyMatrix(R);
	DestroyMatrix(Q);
	DestroyMatrix(I);
	DestroyMatrix(D);
	DestroyMatrix(R1);
	DestroyMatrix(Q1);
	DestroyMatrix(H);
	DestroyMatrix(P);
	DestroyMatrix(E);
	DestroyMatrix(EV);
	//cout << determinant[0] << endl;
	//A = NULL;
	//DestroyMatrix(I);
	//I = NULL;
	//DestroyMatrix(D);
	//PrintMatrix(B);
	//PrintMatrix(C);
	//DestroyMatrix(B);
	//DestroyMatrix(C);
	//delete determinant;
	//determinant = NULL;


	
	
	//getchar();
	_CrtDumpMemoryLeaks();
	
	return 0;

}