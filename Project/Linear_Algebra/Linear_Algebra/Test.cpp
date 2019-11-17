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
	//Eigen::MatrixXd m(2, 2);
	//m(0, 0) = 3;
	//m(1, 0) = 2.5;
	//m(0, 1) = -1;
	//m(1, 1) = m(1, 0) + m(0, 1);
	//std::cout << "Here is the matrix m:\n" << m << std::endl;
	//Eigen::VectorXd v(2);
	//v(0) = 4;
	//v(1) = v(0) - 1;
	//std::cout << "Here is the vector v:\n" << v << std::endl;







	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	const unsigned NUM = 50; //最大迭代次数

	unsigned N = 3;

	unsigned layer = 1;

	Matrix* A=new Matrix;

	Matrix* Q = new Matrix;

	Matrix* R = new Matrix;

	Matrix* Q1 = new Matrix;

	Matrix* R1 = new Matrix;

	Matrix* I=new Matrix;

	Matrix* D = new Matrix;

	Vector* determinant=new Vector;

	BuildVector(determinant, layer);;

	Matrix* H = new Matrix;

	Matrix* P = new Matrix;

	//Matrix* E = new Matrix;
	//Matrix* EV = new Matrix;

	//Vector* Uk = new Vector;
	//MatrixType Lambda=0.0;

	//Matrix* B=new Matrix;

	//Matrix* C = new Matrix;

	//SetMatrixSize(A, N, N, 1);
	BuildMatrix(A, N, N, layer);
	//BuildVector(determinant, layer);
	
	//SetMatrixSize(B, 3, 1, 1);


	//A->array[0] = 1;

	//A->array[1] = 1;

	//A->array[2] = 1;

	//A->array[3] = 2;

	//A->array[4] = -1;

	//A->array[5] = -1;

	//A->array[6] = 2;

	//A->array[7] = -4;

	//A->array[8] = 5;

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



	for (unsigned i = 0; i <layer * N * N; i++)
	{
		A->array[i] = rand();
	}

	PrintMatrix(A);

	cout << endl;


	//B->array[0] = 2;

	//B->array[1] = 5;

	//B->array[2] = 0;
	//PrintMatrix(A);

	//MatrixTranspose(A,B);
	//MatrixMultibyMatrix(A, B, C);
	//PrintMatrix(A);
	RealHessenBurg(A, H, P);


	//EginVectorReal(A, Uk, Lambda);

	//PrintMatrix(A);
	//PrintVector(Uk);

	//cout << Lambda << endl;
	//getchar();

	//EginValue(A, E,EV);
	//PrintMatrix(A);
	//PrintMatrix(E);
	//PrintMatrix(EV);
	PrintMatrix(H);
	PrintMatrix(P);
	//cout << endl;
	//getchar();

	RealMatrixDeterminant(A, determinant);
	PrintVector(determinant);
	cout << endl;
	getchar();

	RealGivens(A, Q, R);
	RealQR(A, Q1, R1);
	RealMatrixSchmitOrthogonal(A, I, D);

	PrintMatrix(I);
	PrintMatrix(D);
	getchar();
	cout << endl;

	PrintMatrix(R1);
	cout << endl;
	PrintMatrix(Q1);
	cout << endl;
	getchar();

	PrintMatrix(R);
	PrintMatrix(Q);
	cout << endl;
	getchar();


	//MatrixDeterminant(A, determinant);
	DestroyMatrix(A);
	DestroyVector(determinant);
	DestroyMatrix(R);
	DestroyMatrix(Q);
	DestroyMatrix(I);
	DestroyMatrix(D);
	DestroyMatrix(R1);
	DestroyMatrix(Q1);
	DestroyMatrix(H);
	DestroyMatrix(P);
	//DestroyMatrix(E);
	//DestroyMatrix(EV);
	//DestroyVector(Uk);
	//delete Lambda;
	//Lambda = NULL;
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