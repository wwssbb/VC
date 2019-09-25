#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
using namespace std;

#define err 1e-4;
typedef unsigned int uint;

class Kmeans
{
public:

	uint pointnum;
	uint dimension;
	uint centernum;
	double J;
	uint Times = 100;

	double** Points = NULL;
	double** Weight = NULL;
	double** Centers = NULL;

	Kmeans(uint pn, uint di, uint cen);
	Kmeans();
	double Distance(double* point, double* center);
	int PrintWeight();
	int PrintPoints();
	int PrintCenters();
	int Normalize(double* weight);
	int FindMin(double* weight);
	~Kmeans();

};

Kmeans::Kmeans()
{
}

Kmeans::Kmeans(uint pn, uint di, uint cen) :pointnum(pn), dimension(di), centernum(cen)
{
	srand((unsigned)time(0));

	int count = 0;

	Points = (double**)calloc(pointnum, sizeof(double*));
	Weight = (double**)calloc(pointnum, sizeof(double*));
	Centers = (double**)calloc(centernum, sizeof(double*));

	for (int i = 0; i < pointnum; i++)
	{
		Points[i] = (double*)calloc(dimension, sizeof(double));
		for (int j = 0; j < dimension; j++)
		{
			Points[i][j] = ((double)rand()) / RAND_MAX;
		}
		Weight[i] = (double*)calloc(centernum, sizeof(double));
	}

	for (int i = 0; i < centernum; i++)
	{
		Centers[i] = (double*)calloc(dimension, sizeof(double));
		for (int j = 0; j < dimension; j++)
		{
			Centers[i][j] = ((double)rand()) / RAND_MAX;
		}
	}

	while (Times)
	{
		//计算每个点对每个聚类中心的隶属度
		for (int i = 0; i < this->pointnum; i++)
		{
			for (int j = 0; j < this->centernum; j++)
			{
				Weight[i][j] = Distance(Points[i], Centers[j]);
			}

			FindMin(Weight[i]);
			Normalize(Weight[i]);
		}
	
		PrintWeight();
		getchar();

		//刷新聚类中心
		for (int i = 0; i < centernum; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				double count = 0.0;
				for (int k = 0; k < pointnum; k++)
				{
					Centers[i][j] += Points[k][j] * Weight[k][i];
					count += Weight[k][i];
				}
				Centers[i][j] = Centers[i][j] / count;
			}
		}	
		PrintCenters();
		getchar();

		//计算所有点与相对应的聚类中心的总距离
		for (int i = 0; i < pointnum; i++)
		{
			for (int j = 0; j < centernum; j++)
			{
				J += Distance(Points[i], Centers[j])*Distance(Points[i], Centers[j])*Weight[i][j];
			}
		}

		//
		cout << "The "<<count+1<<" sth iteration Distance: "<<J << endl;
		getchar();

		J = 0.0;


		count++;
		Times--;

	}

	cout << "chenggong" << endl;
	cout << J << endl;
	getchar();

}

Kmeans::~Kmeans()
{
	for (int i = 0; i < pointnum; i++)
	{
		free(Points[i]);
		Points[i] = NULL;

		free(Weight[i]);
		Weight[i] = NULL;
	}

	free(Points);
	Points = NULL;

	free(Weight);
	Weight = NULL;

	for (int i = 0; i < centernum; i++)
	{
		free(Centers[i]);
		Centers[i] = NULL;
	}

	free(Centers);
	Centers = NULL;

	pointnum=0;
	dimension=0;
	centernum=0;
	J=0.0;
	Times= 0;

}

double Kmeans::Distance(double* point, double* center)
{
	double distance = 0.0;

	for (int i = 0; i < this->dimension; i++)
	{
		distance += (point[i] - center[i])*(point[i] - center[i]);
	}
	distance = sqrt(distance);

	return distance;
}

int Kmeans::Normalize(double* weight)
{
	double Norm = 0.0;

	for (int i = 0; i < this->centernum; i++)
	{
		Norm += weight[i];
	}

	for (int i = 0; i < this->centernum; i++)
	{
		weight[i] = weight[i]/ Norm;
	}

	return 0;
}

int Kmeans::FindMin(double* weight)
{
	double Min = weight[0];

	for (int i = 1; i < this->centernum; i++)
	{
		if (Min > weight[i])
		{
			Min=weight[i];
		}
	}

	for (int i = 0; i < this->centernum; i++)
	{
		if (Min == weight[i])
		{
			 weight[i] = 1.0;
		}
		else
		{
			weight[i] = 0.0;
		}
	}

	return 0;
}

int Kmeans::PrintWeight()
{
	cout << "The Weight Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < pointnum; i++)
	{
		for (int j = 0; j < centernum; j++)
		{
			cout << Weight[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Kmeans::PrintPoints()
{
	cout << "The Point Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < pointnum; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << Points[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Kmeans::PrintCenters()
{
	cout << "The Center Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < centernum; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << Centers[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}


class Cmeans: public Kmeans
{
public:

	uint pointnum;
	uint dimension;
	uint centernum;
	double J;
	double Cw;
	uint Times = 100;

	double** Points = NULL;
	double** Weight = NULL;
	double** Centers = NULL;

	Cmeans(uint pn, uint di, uint cen, double cw);
	Cmeans();
	double Distance(double* point, double* center);
	int PrintWeight();
	int PrintPoints();
	int PrintCenters();
	int Normalize(double* weight);
	~Cmeans();

};

Cmeans::Cmeans()
{

}

Cmeans::Cmeans(uint pn, uint di, uint cen, double cw) :pointnum(pn), dimension(di), centernum(cen), Cw(cw)
{
	srand((unsigned)time(0));

	int count = 0;

	Points = (double**)calloc(pointnum, sizeof(double*));
	Weight = (double**)calloc(pointnum, sizeof(double*));
	Centers = (double**)calloc(centernum, sizeof(double*));

	for (int i = 0; i < pointnum; i++)
	{
		Points[i] = (double*)calloc(dimension, sizeof(double));
		for (int j = 0; j < dimension; j++)
		{
			Points[i][j] = ((double)rand()) / RAND_MAX;
		}
		Weight[i] = (double*)calloc(centernum, sizeof(double));
	}

	for (int i = 0; i < centernum; i++)
	{
		Centers[i] = (double*)calloc(dimension, sizeof(double));
		for (int j = 0; j < dimension; j++)
		{
			Centers[i][j] = ((double)rand()) / RAND_MAX;
		}
	}

	while (Times)
	{
		//计算每个点对每个聚类中心的隶属度
		for (int i = 0; i < this->pointnum; i++)
		{
			for (int j = 0; j < this->centernum; j++)
			{
				for (int k = 0; k < this->centernum; k++)
				{
					Weight[i][j] += pow((Distance(Points[i], Centers[j]) / Distance(Points[i], Centers[k])),(2/(Cw-1)));
				}
				Weight[i][j] = 1 / Weight[i][j];
			}

			Normalize(Weight[i]);
		}

		PrintWeight();
		getchar();

		//刷新聚类中心
		for (int i = 0; i < centernum; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				double count = 0.0;
				for (int k = 0; k < pointnum; k++)
				{
					Centers[i][j] += Points[k][j] * pow(Weight[k][i],Cw);
					count += pow(Weight[k][i], Cw);
				}
				Centers[i][j] = Centers[i][j] / count;
			}
		}
		PrintCenters();
		getchar();

		//计算所有点与相对应的聚类中心的总距离
		for (int i = 0; i < pointnum; i++)
		{
			for (int j = 0; j < centernum; j++)
			{
				J += Distance(Points[i], Centers[j])*Distance(Points[i], Centers[j])*pow(Weight[i][j], Cw);
			}
		}

		//
		cout << "The " << count + 1 << " sth iteration Distance: " << J << endl;
		getchar();

		J = 0.0;


		count++;
		Times--;

	}

	cout << "chenggong" << endl;
	cout << J << endl;
	getchar();

}
Cmeans::~Cmeans()
{
	for (int i = 0; i < pointnum; i++)
	{
		free(Points[i]);
		Points[i] = NULL;

		free(Weight[i]);
		Weight[i] = NULL;
	}

	free(Points);
	Points = NULL;

	free(Weight);
	Weight = NULL;

	for (int i = 0; i < centernum; i++)
	{
		free(Centers[i]);
		Centers[i] = NULL;
	}

	free(Centers);
	Centers = NULL;

	pointnum = 0;
	dimension = 0;
	centernum = 0;
	Cw = 0.0;
	J = 0.0;
	Times = 0;

}

double Cmeans::Distance(double* point, double* center)
{
	double distance = 0.0;

	for (int i = 0; i < this->dimension; i++)
	{
		distance += (point[i] - center[i])*(point[i] - center[i]);
	}
	distance = sqrt(distance);

	return distance;
}

int Cmeans::Normalize(double* weight)
{
	double Norm = 0.0;

	for (int i = 0; i < this->centernum; i++)
	{
		Norm += weight[i];
	}

	for (int i = 0; i < this->centernum; i++)
	{
		weight[i] = weight[i] / Norm;
	}

	return 0;
}

int Cmeans::PrintWeight()
{
	cout << "The Weight Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < pointnum; i++)
	{
		for (int j = 0; j < centernum; j++)
		{
			cout << Weight[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Cmeans::PrintPoints()
{
	cout << "The Point Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < pointnum; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << Points[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Cmeans::PrintCenters()
{
	cout << "The Center Matrix is : " << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < centernum; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << Centers[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}