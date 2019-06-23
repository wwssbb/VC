#pragma once
#include"string.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
#include<iostream>
#include<complex.h>

using namespace std;

constexpr auto Pi = 3.141592654;

class ComplexType
{
public:
	double Real;
	double Imaginary;
	int Period;

public:
	ComplexType();
	ComplexType(double real, double imaginary, int n);
	~ComplexType();
	int W(double con);
	int multiByConst(double con);
	int Add(ComplexType* B);
};

ComplexType::ComplexType()
{
	this->Real = 0;
	this->Imaginary = 0;
	this->Period = 0.0;
}

ComplexType::ComplexType(double real, double imaginary,int n)
{
	this->Real = real;
	this->Imaginary = imaginary;
	this->Period = n;
};

int ComplexType::W(double con)
{
	this->Real = cos(this->Real * con * 2 * Pi / this->Period);
	this->Imaginary = sin(-(this->Imaginary *  con * 2 * Pi / this->Period));

	return 0;
};

int ComplexType::multiByConst(double con)
{
	this->Real = con * this->Real;
	this->Imaginary = this->Imaginary *  con;

	return 0;
};

int ComplexType::Add(ComplexType* B)
{
	this->Real = this->Real+ B->Real;
	this->Imaginary = this->Imaginary + B->Imaginary;

	return 0;
};

ComplexType::~ComplexType()
{

}

typedef enum
{
	Zero=0,
	Unit,
	Rand,
	Symatric,
	Fourier,
	
}InitialMatrixType;

template<typename Template> 
class MatrixComplex
{
public:
	unsigned row;
	unsigned column;
	unsigned height;
	Template*** matrixcomplex;

public:
	 MatrixComplex(unsigned row, unsigned column, unsigned height,InitialMatrixType type);

	 ~MatrixComplex();

	 int FourierTransform(double* input, Template* output);

	 int PrintMatrixComplex();
};

template<typename Template>
MatrixComplex<Template>::MatrixComplex(unsigned row, unsigned column, unsigned height, InitialMatrixType type)
{
	this->row = row;
	this->column = column;
	this->height = height;
	this->matrixcomplex = (Template***)malloc(sizeof(Template**)*height);

	for (unsigned i = 0; i < this->height; i++)
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
			case Fourier:
				for (unsigned k = 0; k < this->column; k++)
				{
					matrixcomplex[i][j][k] = new ComplexType(j, j, this->column);
					matrixcomplex[i][j][k]->W(k);
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
int MatrixComplex<Template>::FourierTransform(double* input, Template* output)
{
	//for (unsigned i = 0; i < this->height; i++)
	//{
		for (unsigned j = 0; j < this->row; j++)
		{
			for (unsigned k = 0; k < this->column; k++)
			{
				matrixcomplex[0][j][k]->multiByConst(input[k]);
				output[j]->Add(matrixcomplex[0][j][k]);
			}
			//cout << output[j]->Real << endl;
			//getchar();
			output[j]->multiByConst(1 / sqrt(this->row));
		}
	//}

	return 0;
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
				cout << matrixcomplex[i][j][k]->Real<<","<< matrixcomplex[i][j][k]->Imaginary<< "  ";
			}
			cout << endl;
		}
		
		cout << "********************" << endl;
	}

	return 0;
}

