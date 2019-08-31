#pragma once
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<time.h>

using namespace std;

typedef unsigned int uint;

class Layer
{
public:
	uint number;
	uint midnumber;
	uint times;
	uint numindex1;
	uint numindex2;

	uint* layernumber=NULL;
	double** celllayer = NULL;
	double*** weightlayer = NULL;
	double*** detaweightlayer = NULL;
	double** backcelllayer = NULL;
	uint** weightnumber = NULL;
	double*  expectoutput= NULL;
	double* deviate = NULL;
	double* weight = NULL;

public:
	Layer(uint num, uint t);
	~Layer();
	int ForwardPropagate();
	int BackwardPropagate();
	int PrintCellLayer();
	int PrintWeightLayer();
	int PrintBackCellLayer();
};

Layer::~Layer()
{
	//release cell layer
	for (int i = 0; i < number; i++)
	{
		free(celllayer[i]);
		celllayer[i] = NULL;
	}
	free(celllayer);
	celllayer = NULL;

	//release weight、deviate、expectoutput
	free(weight);
	weight = NULL;

	free(deviate);
	deviate = NULL;

	free(expectoutput);
	expectoutput = NULL;
	
	//release weightlayer、detaweightlayer、weightnumber
	for (int i = 0; i < midnumber; i++)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			free(weightlayer[i][j]);
			free(detaweightlayer[i][j]);
			weightlayer[i][j] = NULL;
			detaweightlayer[i][j] = NULL;
		}
		free(weightlayer[i]);
		weightlayer[i] = NULL;
		free(detaweightlayer[i]);
		detaweightlayer[i] = NULL;
		free(weightnumber[i]);
		weightnumber[i] = NULL;
		free(backcelllayer[i]);
		backcelllayer[i] = NULL;
	}
	free(weightlayer);
	weightlayer = NULL;
	free(detaweightlayer);
	detaweightlayer = NULL;
	free(weightnumber);
	weightnumber = NULL;
	free(backcelllayer);
	backcelllayer = NULL;

	//release layer number
	free(layernumber);
	layernumber = NULL;

	//reset the constants
	number=0;
	midnumber=0;
	times=0;
	numindex1=0;
	numindex2=0;
}

Layer::Layer(uint num, uint t) :number(num), times(t)
{
	if (num < 2)
	{
		cout << "The network should at least have two layers." << endl;
	}
	else
	{
		numindex1 = number - 1;
		numindex2 = number - 2;
		midnumber = number - 1;
		srand((unsigned)time(0));

		//set the layernumber
		layernumber = (uint*)calloc(number, sizeof(uint));
		celllayer = (double**)calloc(number, sizeof(double*));
		weightlayer = (double***)calloc(midnumber, sizeof(double**));
		detaweightlayer = (double***)calloc(midnumber, sizeof(double**));
		backcelllayer = (double**)calloc(midnumber, sizeof(double*));
		weightnumber = (uint**)calloc(midnumber, sizeof(uint*));
		weight = (double*)calloc(midnumber, sizeof(double));
	
		//set the number of cell in each layer
		for (int i = 0; i < number; i++)
		{
			cout << "Please input the number of cell in the " << i + 1 << " st layer"<<endl;
			cin >> layernumber[i];

			celllayer[i] = (double*)calloc(layernumber[i], sizeof(double));

			if (i == numindex1)
			{
				expectoutput = (double*)calloc(layernumber[i],sizeof(double));
				deviate = (double*)calloc(layernumber[i], sizeof(double));
			}
		}

		//set the inputlayer and outputlayer
		for (int i = 0; i < layernumber[0]; i++)
		{
			cout << "Please input the "<< i+1 <<" st cell of inpputlayer" << endl;
			cin >> celllayer[0][i];
		}

		for (int i = 0; i < layernumber[numindex1]; i++)
		{
			cout << "Please input the " << i + 1 << " st cell of outputlayer" << endl;
			cin >> expectoutput[i];
		}

		//set the number of weightlayer and backcelllayer
		for (int i = 0; i < midnumber; i++)
		{
			cout << "Please set the " << i + 1 << "st weightlayer's weight" << endl;
			cin >> weight[i];

			//set eachlayer of weightnumber
			weightnumber[i] = (uint*)calloc(2, sizeof(uint));
			weightnumber[i][0] = layernumber[i + 1];
			weightnumber[i][1] = layernumber[i] + 1;

			//set each layer of weightlayer
			weightlayer[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));
			detaweightlayer[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));
			for (int j = 0; j < weightnumber[i][0]; j++)
			{
				weightlayer[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));
				detaweightlayer[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));

				for (int k = 0; k < weightnumber[i][1]; k++)
				{
					weightlayer[i][j][k] = ((double)rand()) / RAND_MAX;
				}
			}

			//set the number of each backcelllayer
			backcelllayer[i] = (double*)calloc(layernumber[i + 1], sizeof(double));
		}

		//implement first forward propagate
		ForwardPropagate();

		while (times)
		{
			BackwardPropagate();
			ForwardPropagate();
			times--;
		}


	}

}

int Layer::ForwardPropagate()
{
	for (int i = 0; i < midnumber; i++)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			for (int k = 0; k < weightnumber[i][1] - 1; k++)
			{
				celllayer[i + 1][j] += celllayer[i][k] * weightlayer[i][j][k];
			}
			celllayer[i + 1][j] += weightlayer[i][j][weightnumber[i][1]-1];

			celllayer[i + 1][j] = 1 / (1 + exp(-celllayer[i + 1][j]));
		}
	}
	return 0;
}

int Layer::BackwardPropagate()
{
	//set the backcell layer
	for (int i = 0; i < layernumber[numindex1]; i++)
	{
		deviate[i] = expectoutput[i] - celllayer[numindex1][i];

		backcelllayer[numindex2][i]=deviate[i] * -2 / layernumber[numindex1] * celllayer[numindex1][i] * (1- celllayer[numindex1][i]);
	}

	for(int i=numindex2-1;i>=0;i--)
	{ 
		for (int j = 0; j < weightnumber[i+1][1]-1; j++)
		{
			for (int k = 0; k < weightnumber[i+1][0]; k++)
			{
				backcelllayer[i][j] += backcelllayer[i + 1][k] * weightlayer[i+1][k][j];
			}
			backcelllayer[i][j] = backcelllayer[i][j] * celllayer[i+1][j] * (1 - celllayer[i+1][j]);
		}
	}

	//set the detaweight layer
	for (int i = numindex2; i >= 0; i--)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			for (int k = 0; k < weightnumber[i][1]-1; k++)
			{
				detaweightlayer[i][j][k]=backcelllayer[i][j] * celllayer[i][k];
				detaweightlayer[i][j][k] = detaweightlayer[i][j][k] * weight[i];
			}
		}
	}

	for (int i = 0; i < midnumber; i++)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			for (int k = 0; k < weightnumber[i][1]-1; k++)
			{
				weightlayer[i][j][k] = weightlayer[i][j][k] - detaweightlayer[i][j][k];
			}
		}
	}

	return 0;
}

int Layer::PrintBackCellLayer()
{
	for (int i = 0; i < midnumber; i++)
	{
		cout << "The " << i + 1 << " st back cell layer is :" << endl;
		for (int j = 0; j < layernumber[i+1]; j++)
		{
			cout << backcelllayer[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::PrintCellLayer()
{
	for (int i = 0; i < number; i++)
	{
		cout << "The " << i + 1 << " st cell layer is :" << endl;
		for (int j = 0; j < layernumber[i]; j++)
		{
			cout << celllayer[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::PrintWeightLayer()
{
	for (uint i = 0; i < midnumber; i++)
	{
		cout << "The " << i + 1 << " st weight layer is :" << endl;
		for (uint j = 0; j < weightnumber[i][0]; j++)
		{
			for (uint k = 0; k < weightnumber[i][1]; k++)
			{
				cout << weightlayer[i][j][k]<< " , ";
			}
			cout << " ; " << endl;
			
		}
		cout << " **************************" << endl;
	}

	return 0;
}