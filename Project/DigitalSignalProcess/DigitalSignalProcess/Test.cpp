#include "FunctionHeader.h"
#include"ComplexMatrix.h"

int main()
{
	//unsigned row = 20;
	//unsigned column = 20;
	//unsigned height = 3;

	//double* input = new double[row];
	//for (int i = 0; i < row; i++)
	//{
	//	input[i] = rand();
	//}


	//ComplexType** output = new ComplexType*[row];
	//for (int i = 0; i < row; i++)
	//{
	//	output[i] = new ComplexType();
	//}

	//MatrixComplex<ComplexType*> matrix(row, column, height, Fourier);

	//matrix.PrintMatrixComplex();
	////getchar();

	//matrix.FourierTransform(input, output);

	//for (int i = 0; i < row; i++)
	//{
	//	cout << input[i] << " ";
	//	cout<< output[i]->Real<<",i"<< output[i]->Imaginary<<";";
	//	cout << endl;
	//}
	//
	//getchar();

	////MatrixComplex<double> matrix(row, column, height, Rand);

	//delete input;
	//input = NULL;

	//for (int i = 0; i < row; i++)
	//{
	//	delete output[i];
	//	output[i] = NULL;
	//}
	//output = NULL;

	//getchar();



	matrix<double> m(5, 5, 1, realrandom);

	m >> cout;

	getchar();

	return 0;






}