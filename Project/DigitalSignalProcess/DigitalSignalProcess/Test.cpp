#include "FunctionHeader.h"

int main()
{
	unsigned row = 8;
	unsigned column = 8;
	unsigned height = 3;

	double* input = new double[row];
	for (int i = 0; i < row; i++)
	{
		input[i] = rand();
	}


	ComplexType** output = new ComplexType*[row];
	for (int i = 0; i < row; i++)
	{
		output[i] = new ComplexType();
	}

	MatrixComplex<ComplexType*> matrix(row, column, height, Fourier);

	matrix.PrintMatrixComplex();
	getchar();

	matrix.FourierTransform(input, output);

	for (int i = 0; i < row; i++)
	{
		cout << input[i] << " ";
		cout<< output[i]->Real<<","<< output[i]->Imaginary<<";";
		cout << endl;
	}
	
	getchar();

	//MatrixComplex<double> matrix(row, column, height, Rand);

	delete input;
	input = NULL;

	for (int i = 0; i < row; i++)
	{
		delete output[i];
		output[i] = NULL;
	}
	output = NULL;

	getchar();
}