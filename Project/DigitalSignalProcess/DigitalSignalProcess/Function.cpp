#include"FunctionHeader.h"

template<typename Template>
MatrixComplex<Template>::MatrixComplex(unsigned row, unsigned column, unsigned height,InitialMatrixType type)
{
	this->row = row;
	this->column = column;
	this->height = height;
	this->matrixcomplex = (Template***)malloc(sizeof(Template**)*height);

	for (unsigned i = 0;i < this->height; i++)
	{
		matrixcomplex[i] = (Template**)malloc(sizeof(Template*)*row);

		for (unsigned j = 0; j < this->row; j++)
		{
			matrixcomplex[i][j] = (Template*)malloc(sizeof(Template)*column);

			switch (type)
			{
			case Zero:
				memset(matrixcomplex, 0.0, sizeof(Template)*column);
				break;
			case Rand:
				for (unsigned k = 0; k < this->column; k++)
				{
					matrixcomplex[i][j][k] = (Template)rand();
				}
				break;
			}			
		}
	}
}

template<typename Template>
MatrixComplex<Template>::~MatrixComplex()
{
	for (unsigned i = 0; i < this->height; i++)
	{
		for (unsigned j = 0; j < this->row; j++)
		{
			free(matrixcomplex[i][j]);
			matrixcomplex[i][j] = NULL;
		}
		free(matrixcomplex[i]);
		matrixcomplex[i] = NULL;
	}
	free(matrixcomplex);
	matrixcomplex = NULL;
}

template<typename Template> 
int MatrixComplex<Template>::PrintMatrixComplex()
{
	for (unsigned i = 0; i < this->height; i++)
	{
		cout << "The " << i << " sth layer :" << endl;
		for (unsigned j = 0; j < this->row; j++)
		{
			for (unsigned k = 0; k < this->column; k++)
			{
				cout << matrixcomplex[i][j][k] << " ";
			}
			cout << endl;			
		}
		cout << "********************" << endl;
	}

	return 0;
}

template<typename Template>
int MatrixComplex<Template>::HelloWorld()
{
	cout << "HelloWorld." << endl;
	return 0;
}