#include"Function.h"
#include"Variable.h"

int main()

{

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