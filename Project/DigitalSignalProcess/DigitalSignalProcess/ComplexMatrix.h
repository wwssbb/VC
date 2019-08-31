#pragma once
#include<string.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<vector>


using namespace std;

//constexpr auto Pi = 3.141592654;

typedef unsigned int uint;

typedef enum typeclass
{
	realzero,
	realrandom,
	complexzero,
	complexrandom,
};

typedef struct complex
{
	double real;
	double imagine;
};

template<typename T>
class matrix
{
public:
	uint row;
	uint column;
	uint height;
	typeclass type;

	T*** content0 = NULL;
	T*** content1 = NULL;
	T**  content2 = NULL;
	T*   content3 = NULL;

	vector<vector<vector<T>>> content4;
	vector<vector<T>>content5;
	vector<T>content6;

public:
	matrix();
	matrix(uint row, uint column, uint height, typeclass type);
	matrix(uint row, uint column, typeclass type);
	matrix(uint row, typeclass type);

	ostream& operator>>(ostream& out);

};

template<typename T>
matrix<T>::matrix() : row(0.0), column(0.0), height(0.0)
{

}

template<typename T>
matrix<T>::matrix(uint row, typeclass type) : row(row), type(type)
{

}

template<typename T>
matrix<T>::matrix(uint row, uint column, typeclass type) : row(row), column(column), type(type)
{

}

template<typename T>
matrix<T>::matrix(uint row, uint column, uint height, typeclass type) : row(row), column(column), height(height), type(type)
{
	if (this->row != 0 && this->column != 0 && this->height != 0)
	{
		content0 = (T***)calloc(this->height, sizeof(T**));
		
		for (uint i = 0; i < this->height; i++)
		{
			content0[i] = (T**)calloc(this->row, sizeof(T*));

			for (uint j = 0; j < this->row; j++)
			{
				content0[i][j] = (T*)calloc(this->column, sizeof(T));

				//if (this->type == complexzero || this->type == complexrandom)
				//{
				//	switch (this->type)
				//	{
				//	case complexzero:

				//		for (uint z = 0; z < this->column; z++)
				//		{
				//			content0[i][j][z].real = 0.0;
				//			content0[i][j][z].imagine = 0.0;
				//		}
				//		break;

				//	case complexrandom:

				//		for (uint z = 0; z < this->column; z++)
				//		{
				//			content0[i][j][z].real = rand();
				//			content0[i][j][z].imagine = rand();
				//		}
				//		break;
				//	}
				//}

				if (this->type == realzero || this->type == realrandom)
				{
					switch (this->type)
					{
					case realzero:

						for (uint z = 0; z < this->column; z++)
						{
							content0[i][j][z] = 0.0;
						}
						break;

					case realrandom:

						for (uint z = 0; z < this->column; z++)
						{
							content0[i][j][z] = rand();
						}
						break;
					}
				}
			}
		}
	}

	else
	{
		cout << "Please recheck the size of input matrix." << endl;
	}
}

template<typename T>
ostream& matrix<T>::operator>>(ostream& out)
{
	if (content0 != NULL)
	{
		for (uint i = 0; i < this->height; i++)
		{
			cout << "The " << i + 1 << " st layer is :" << endl;

			for (uint j = 0; j < this->row; j++)
			{
				for (uint k = 0; k < this->column; k++)
				{
	/*				if (this->type == complexzero || this->type == complexrandom)
					{
						cout << content0[i][j][k].real << " + j " << content0[i][j][k].imagine << ", ";
					}*/

					if (this->type == realzero || this->type == realrandom)
					{
						cout << content0[i][j][k] << ", ";
					}
				}

				cout << " ; " << endl;
			}

			cout << "********************************" << endl;
		}
	}
	else
	{
		cout << "The matrix has nothing." << endl;
	}

	return out;
}