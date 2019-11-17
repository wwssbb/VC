#pragma once
#include<iostream>
#include<string>
#include<Eigen>
#include <time.h>
#include <math.h>
using namespace std;
using namespace Eigen;

double gaussrand()
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}



class KalMan_std
{
public:
	int dimension;
	int length;

	Matrix<double, Dynamic, 1>* Target = NULL;
	Matrix<double, Dynamic, 1>* ErrV = NULL;
	Matrix<double, Dynamic, 1>* Predict = NULL;
	Matrix<double, Dynamic, 1>* ErrW = NULL;
	Matrix<double, Dynamic, 1>* Measure = NULL;
	Matrix<double, Dynamic, Dynamic>* UnCertain = NULL;

	Matrix<double, Dynamic, Dynamic> A;
	Matrix<double, Dynamic, 1> U;
	Matrix<double, Dynamic, Dynamic> H;

public:
	KalMan_std(int di, int len);
	int setErrorMatrix(Matrix<double, Dynamic, 1>& matrix);
	int identify(Matrix<double, Dynamic, Dynamic>& matrix);
	int identify_vect(Matrix<double, Dynamic, 1>& matrix);
	~KalMan_std();
};

KalMan_std::KalMan_std(int di, int len) : dimension(di), length(len)
{
	Target = (Matrix<double, Dynamic, 1>*)calloc(length, sizeof(Matrix<double, Dynamic, 1>));
	ErrV = (Matrix<double, Dynamic, 1>*)calloc(length, sizeof(Matrix<double, Dynamic, 1>));

	Predict = (Matrix<double, Dynamic, 1>*)calloc(length, sizeof(Matrix<double, Dynamic, 1>));
	ErrW = (Matrix<double, Dynamic, 1>*)calloc(length, sizeof(Matrix<double, Dynamic, 1>));

	Measure = (Matrix<double, Dynamic, 1>*)calloc(length, sizeof(Matrix<double, Dynamic, 1>));

	UnCertain = (Matrix<double, Dynamic, Dynamic>*)calloc(length, sizeof(Matrix<double, Dynamic, Dynamic>));

	A.resize(dimension, dimension);
	identify(A);
	A = A * 3;

	H.resize(dimension, dimension);
	identify(H);

	U.resize(dimension, 1);
	identify_vect(U);
	U = U * 2;

	Predict[0].resize(dimension, 1);
	Measure[0].resize(dimension, 1);
	ErrV[0].resize(dimension, 1);
	ErrW[0].resize(dimension, 1);
	UnCertain[0].resize(dimension, dimension);
	Target[0].resize(dimension, 1);

	setErrorMatrix(Target[0]);
	setErrorMatrix(ErrV[0]);
	setErrorMatrix(ErrW[0]);
	//Target[0].Random();


	Predict[0] = Target[0];
	Measure[0] = Target[0] + ErrV[0];

	UnCertain[0] = ErrW[0] * ErrW[0].transpose();

	for (int i = 1; i < length; i++)
	{
		Matrix<double, Dynamic, Dynamic> KalmanInc;
		KalmanInc.resize(dimension, dimension);
		Matrix<double, Dynamic, 1> Predict_opt;
		Predict_opt.resize(dimension, 1);
		Matrix<double, Dynamic, 1> Measure_opt;
		Measure_opt.resize(dimension, 1);
		Matrix<double, Dynamic, Dynamic> UnCertain_opt;
		UnCertain_opt.resize(dimension, dimension);
		Matrix<double, Dynamic, Dynamic> I;
		I.resize(dimension, dimension);
		identify(I);

		Target[i].resize(dimension, 1);
		Predict[i].resize(dimension, 1);
		Measure[i].resize(dimension, 1);
		ErrV[i].resize(dimension, 1);
		ErrW[i].resize(dimension, 1);
		UnCertain[i].resize(dimension, dimension);

		setErrorMatrix(ErrV[i]);
		setErrorMatrix(ErrW[i]);

		Target[i] = A * Target[i - 1] + U;
		Measure[i] = Target[i] + ErrV[i];

		Predict_opt = A * Predict[i - 1] + U;
		UnCertain_opt = A * UnCertain[i - 1] * A.transpose() + ErrW[i] * ErrW[i].transpose();
		//Measure_opt= Target[i]- H* Predict_opt
		Measure_opt = Measure[i] - H * Predict_opt;
		KalmanInc = UnCertain_opt * H.transpose() * ((H * UnCertain_opt * H.transpose() + ErrV[i] * ErrV[i].transpose()).inverse());
		Predict[i] = Predict_opt + KalmanInc * Measure_opt;
		UnCertain[i] = (I - KalmanInc * H) * UnCertain_opt;
	}

}

KalMan_std::~KalMan_std()
{
	dimension = 0;
	length = 0;

	free(Target);
	Target = NULL;
	free(ErrV);
	ErrV = NULL;
	free(Predict);
	Predict = NULL;
	free(ErrW);
	ErrW = NULL;
	free(Measure);
	Measure = NULL;
	free(UnCertain);
	UnCertain = NULL;
}

int KalMan_std::setErrorMatrix(Matrix<double, Dynamic, 1>& matrix)
{
	for (int i = 0; i < matrix.rows(); i++)
	{
		matrix(i, 0) = gaussrand();
	}

	return 0;
}

int KalMan_std::identify(Matrix<double, Dynamic, Dynamic>& matrix)
{
	if (matrix.rows() != matrix.cols())
	{
		cout << "We need a square matrix" << endl;
	}
	else
	{
		for (int i = 0; i < matrix.rows(); i++)
		{
			for (int j = 0; j < matrix.cols(); j++)
			{
				if (i == j)
				{
					matrix(i, j) = 1.0;
				}
				else
				{
					matrix(i, j) = 0.0;
				}
			}

		}
	}

	return 0;
}

int KalMan_std::identify_vect(Matrix<double, Dynamic, 1>& matrix)
{
	for (int i = 0; i < matrix.rows(); i++)
	{
		matrix(i, 0) = 1;
	}
	return 0;
}


