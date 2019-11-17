#include"Function.h"
//#include"Variable.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include"Eigen"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

int main()

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	const unsigned NUM = 50; //最大迭代次数

	unsigned N = 3;

	unsigned M = 3;

	unsigned layer = 1;

	Matrix* A = new Matrix;

	Matrix* AA = new Matrix;

	Matrix* Mid1 = new Matrix;

	Matrix* Mid2 = new Matrix;

	//Matrix* H = new Matrix;

	//Matrix* P = new Matrix;

	//Matrix* At = new Matrix;

	//Matrix* Q = new Matrix;

	//Matrix* R = new Matrix;

	//Matrix* Q1 = new Matrix;

	//Matrix* R1 = new Matrix;

	//Matrix* I = new Matrix;

	//Matrix* D = new Matrix;

	//Vector* Uk = new Vector;
	//MatrixType Lambda=0.0;

	Matrix* E = new Matrix;
	Matrix* EV = new Matrix;

	Matrix* U = new Matrix;
	Matrix* V = new Matrix;
	Matrix* T = new Matrix;

	//Vector* determinant = new Vector;

	//BuildVector(determinant, layer);;


	BuildMatrix(A, N, M, layer);

	A->array[0] = 1;

	A->array[1] = 0;

	A->array[2] = 1;

	A->array[3] = -1;

	A->array[4] = -2;

	A->array[5] = 0;

	A->array[6] = 0;

	A->array[7] = 1;

	A->array[8] = -1;


	//A->array[0] = 1;

	//A->array[1] = 5;

	//A->array[2] = 7;

	//A->array[3] = 6;

	//A->array[4] = 1;

	//A->array[5] = 2;

	//A->array[6] = 1;

	//A->array[7] = 10;

	//A->array[8] = 4;

	//A->array[9] = 4;

	//A->array[10] = 3;

	//A->array[11] = 6;

	//A->array[12] = 7;

	//A->array[13] = 5;

	//A->array[14] = 2;


	//for (unsigned i = 0; i < layer * N * M; i++)
	//{
	//	A->array[i] = rand();
	//}

	PrintMatrix(A);

	cout << endl;


	//RealMatrixDeterminant(A, determinant);
	//PrintVector(determinant);
	//cout << endl;
	//getchar();

	//RealGivens(A, Q, R);
	//RealQR(A, Q1, R1);
	//RealMatrixSchmitOrthogonal(A, I, D);

	//PrintMatrix(I);
	//PrintMatrix(D);
	//getchar();
	//cout << endl;

	//PrintMatrix(R1);
	//cout << endl;
	//PrintMatrix(Q1);
	//cout << endl;
	//getchar();

	//PrintMatrix(R);
	//PrintMatrix(Q);
	//cout << endl;
	//getchar();

	//MatrixMultibyMatrix(Q1, R1, At);

	//PrintMatrix(At);
	//cout << endl;
	//getchar();

	//EginVectorReal(A, Uk, Lambda);

	//PrintMatrix(A);
	//PrintVector(Uk);

	//cout << Lambda << endl;
	//getchar();

	//RealHessenBurg(A, H, P);
	//PrintMatrix(H);
	//PrintMatrix(P);
	//cout << endl;
	//getchar();

	//EginValue(A, E,EV);
	//PrintMatrix(E);
	//PrintMatrix(EV);
	//cout << endl;
	//getchar();

	SVDReal(A, U, T, V);
	PrintMatrix(U);
	PrintMatrix(V);
	PrintMatrix(T);
	cout << endl;
	getchar();

	MatrixMultibyMatrix(U, T, Mid1);

	MatrixMultibyMatrix(Mid1, V, Mid2);

	PrintMatrix(Mid2);

	cout << endl;
	getchar();

	//SVDInv(A, AA);
	//PrintMatrix(AA);
	//getchar();

	//MatrixDeterminant(A, determinant);
	DestroyMatrix(A);
	//DestroyMatrix(At);
	//DestroyVector(determinant);
	//DestroyMatrix(R);
	//DestroyMatrix(Q);
	//DestroyMatrix(I);
	//DestroyMatrix(D);
	//DestroyMatrix(R1);
	//DestroyMatrix(Q1);
	//DestroyVector(Uk);
	DestroyMatrix(E);
	DestroyMatrix(EV);
	//DestroyMatrix(H);
	//DestroyMatrix(P);
	DestroyMatrix(U);
	DestroyMatrix(V);
	DestroyMatrix(T);
	DestroyMatrix(Mid1);
	DestroyMatrix(Mid2);
	DestroyMatrix(AA);

	_CrtDumpMemoryLeaks();

	return 0;

}