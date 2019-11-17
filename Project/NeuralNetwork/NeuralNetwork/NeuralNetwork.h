#pragma once
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<time.h>

using namespace std;

typedef unsigned int uint;

enum activate
{
	sigmoid,
	tanhh,
	relu,
	prelu,
	elu,
	maxout
};

enum optimizer
{
	gradient,
	momentum,
	rmsprop,
	adam
};

enum loss
{
	leastsquare,
	logloss,
	adaboost,
	hinge
};

class Layer
{
public:
	uint number;
	uint midnumber;
	uint times;
	uint numindex1;
	uint numindex2;
	uint inputrow;
	uint datachannel;
	uint outputrow;
	uint testdatachannel;
	activate act;
	optimizer opt;
	loss los;
	int count;

	uint* layernumber = NULL;
	double** celllayer = NULL;
	double*** weightlayer = NULL;
	double*** detaweightlayer = NULL;
	double** backcelllayer = NULL;
	uint** weightnumber = NULL;
	double*  expectoutput = NULL;
	double* deviate = NULL;
	double** inputdata = NULL;
	double** expectdata = NULL;
	double** outputdata = NULL;
	double** testinputdata = NULL;
	double** testexpectdata = NULL;
	double** testoutputdata = NULL;

	//used for record the previous weight in optimzing the gradient
	double*** historyweightlayer = NULL;
	double*** historyweightlayer2 = NULL;

	//used for optimizer
	double Beta;

	//used for optimizer
	double e;

	//used for optimizer
	double a;

	//learning rate, I hope different celllayer could have their own different learning rate.
	double* weight = NULL;

public:
	Layer(uint t, loss los, activate a, optimizer opt);
	~Layer();
	int Normalize(double* layer, int layerindex);
	int ForwardPropagate();
	int BackwardPropagate();
	int Predict();
	int Evaluate();
	int findmax();
	int PrintCellLayer();
	int PrintWeightLayer();
	int PrintBackCellLayer();
	int PrintInputData();
	int PrintOutputData();
	int PrintExpectData();
	int PrintTestInputData();
	int PrintTestOutputData();
	int PrintTestExpectData();
};

Layer::~Layer()
{
	//release inputdata、outputdat、expectdata
	for (int i = 0; i < datachannel; i++)
	{
		free(inputdata[i]);
		free(outputdata[i]);
		free(expectdata[i]);
		inputdata[i] = NULL;
		outputdata[i] = NULL;
		expectdata[i] = NULL;
	}
	free(inputdata);
	inputdata = NULL;
	free(outputdata);
	outputdata = NULL;
	free(expectdata);
	expectdata = NULL;

	//release testinputdata、testoutputdat、testexpectdata
	for (int i = 0; i < testdatachannel; i++)
	{
		free(testinputdata[i]);
		free(testoutputdata[i]);
		free(testexpectdata[i]);
		testinputdata[i] = NULL;
		testoutputdata[i] = NULL;
		testexpectdata[i] = NULL;
	}
	free(testinputdata);
	testinputdata = NULL;
	free(testoutputdata);
	testoutputdata = NULL;
	free(testexpectdata);
	testexpectdata = NULL;

	//release cell layer
	for (int i = 1; i < number; i++)
	{
		if (celllayer[i] != NULL)
		{
			free(celllayer[i]);
			celllayer[i] = NULL;
		}
	}
	free(celllayer);
	celllayer = NULL;

	//release weight、deviate、expectoutput
	free(weight);
	weight = NULL;

	free(deviate);
	deviate = NULL;

	//free(expectoutput);
	//expectoutput = NULL;

	//release weightlayer、detaweightlayer、weightnumber
	for (int i = 0; i < midnumber; i++)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			free(weightlayer[i][j]);
			free(detaweightlayer[i][j]);
			free(historyweightlayer[i][j]);
			free(historyweightlayer2[i][j]);
			weightlayer[i][j] = NULL;
			detaweightlayer[i][j] = NULL;
			historyweightlayer[i][j] = NULL;
			historyweightlayer2[i][j] = NULL;
		}
		free(weightlayer[i]);
		weightlayer[i] = NULL;
		free(detaweightlayer[i]);
		detaweightlayer[i] = NULL;
		free(historyweightlayer[i]);
		historyweightlayer[i] = NULL;
		free(historyweightlayer2[i]);
		historyweightlayer2[i] = NULL;
		free(weightnumber[i]);
		weightnumber[i] = NULL;
		free(backcelllayer[i]);
		backcelllayer[i] = NULL;
	}
	free(weightlayer);
	weightlayer = NULL;
	free(detaweightlayer);
	detaweightlayer = NULL;
	free(historyweightlayer);
	historyweightlayer = NULL;
	free(historyweightlayer2);
	historyweightlayer2 = NULL;
	free(weightnumber);
	weightnumber = NULL;
	free(backcelllayer);
	backcelllayer = NULL;

	//release layer number
	free(layernumber);
	layernumber = NULL;

	//reset the constants
	number = 0;
	midnumber = 0;
	times = 0;
	numindex1 = 0;
	numindex2 = 0;
	datachannel = 0;
	inputrow = 0;
	outputrow = 0;
	testdatachannel = 0;
}

Layer::Layer(uint t, loss los, activate act, optimizer opt) : times(t), los(los), act(act), opt(opt)
{
	//initial the number of middle layer
	cout << "How many middle layer you prefer?" << endl;
	cin >> number;
	number += 2;

	if (number < 2)
	{
		cout << "The network should at least have two layers." << endl;
	}
	else
	{
		numindex1 = number - 1;
		numindex2 = number - 2;
		midnumber = number - 1;
		srand((unsigned)time(0));
		Beta = 0.9;
		e = 1e-8;
		a = 0.01;
		count = 0;

		/**********************************
		This part initial the matrix of inputdata,
		outputdat, and expectdata
		**********************************/
		//initial the row of inputdata
		cout << "Please set the row of inputdata." << endl;
		cin >> inputrow;

		//initial the channel of sample
		cout << "Please set the data channel." << endl;
		cin >> datachannel;

		//initial the row of outputdata
		cout << "Please set the row of output data." << endl;
		cin >> outputrow;

		//initial the inputdata、expectdata、outputdata
		inputdata = (double**)calloc(datachannel, sizeof(double*));
		expectdata = (double**)calloc(datachannel, sizeof(double*));
		outputdata = (double**)calloc(datachannel, sizeof(double*));

		for (int i = 0; i < datachannel; i++)
		{
			inputdata[i] = (double*)calloc(inputrow, sizeof(double));
			outputdata[i] = (double*)calloc(outputrow, sizeof(double));
			expectdata[i] = (double*)calloc(outputrow, sizeof(double));

			for (int j = 0; j < inputrow; j++)
			{
				cout << "Please set the " << j + 1 << " st element of " << i + 1 << "st input data channel." << endl;
				cin >> inputdata[i][j];
			}

			for (int j = 0; j < outputrow; j++)
			{
				cout << "Please set the " << j + 1 << " st element of " << i + 1 << "st expect data channel." << endl;
				cin >> expectdata[i][j];
			}
		}


		/*******************************
		This part initial the old version's
		celllayer, especially the weightlayer
		*******************************/
		//set the layernumber
		layernumber = (uint*)calloc(number, sizeof(uint));
		celllayer = (double**)calloc(number, sizeof(double*));
		weightlayer = (double***)calloc(midnumber, sizeof(double**));
		detaweightlayer = (double***)calloc(midnumber, sizeof(double**));
		historyweightlayer = (double***)calloc(midnumber, sizeof(double**));
		historyweightlayer2 = (double***)calloc(midnumber, sizeof(double**));
		backcelllayer = (double**)calloc(midnumber, sizeof(double*));
		weightnumber = (uint**)calloc(midnumber, sizeof(uint*));
		weight = (double*)calloc(midnumber, sizeof(double));

		//set the number of cell in each layer(old version)
		for (int i = 0; i < number; i++)
		{
			if (i == 0)
			{
				layernumber[i] = inputrow;
			}
			else if (i == numindex1)
			{
				layernumber[i] = outputrow;
				expectoutput = (double*)calloc(layernumber[i], sizeof(double));
				deviate = (double*)calloc(layernumber[i], sizeof(double));
			}
			else
			{
				cout << "Please input the number of cell in the " << i << " st middle layer" << endl;
				cin >> layernumber[i];
			}
			celllayer[i] = (double*)calloc(layernumber[i], sizeof(double));
		}

		//set the number of weightlayer and backcelllayer
		for (int i = 0; i < midnumber; i++)
		{
			//set each weightlayer's learning rate
			cout << "Please set the " << i + 1 << "st weightlayer's learning rate" << endl;
			cin >> weight[i];

			//set each weightlayer's weightnumber
			weightnumber[i] = (uint*)calloc(2, sizeof(uint));
			weightnumber[i][0] = layernumber[i + 1];
			weightnumber[i][1] = layernumber[i] + 1;

			//set each layer of weightlayer
			weightlayer[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));
			detaweightlayer[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));
			historyweightlayer[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));
			historyweightlayer2[i] = (double**)calloc(weightnumber[i][0], sizeof(double*));

			for (int j = 0; j < weightnumber[i][0]; j++)
			{
				weightlayer[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));
				detaweightlayer[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));
				historyweightlayer[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));
				historyweightlayer2[i][j] = (double*)calloc(weightnumber[i][1], sizeof(double));

				for (int k = 0; k < weightnumber[i][1]; k++)
				{
					//randomly set the weight and bias
					weightlayer[i][j][k] = ((double)rand()) / RAND_MAX - 0.5;
				}
			}

			//set the number of each backcelllayer
			backcelllayer[i] = (double*)calloc(layernumber[i + 1], sizeof(double));
		}

		/*******************************
		This part implement the deep learning
		*******************************/
		//iterate the input and expect data
		for (int m = 0; m < datachannel; m++)
		{
			celllayer[0] = inputdata[m];
			Normalize(celllayer[0], 0);

			expectoutput = expectdata[m];
			Normalize(expectoutput, numindex1);

			//implement first forward propagate
			uint time = times;
			ForwardPropagate();
			while (time)
			{
				//PrintCellLayer();
				//cout << "******************" << endl;
				//PrintWeightLayer();
				//cout << endl;
				//getchar();

				BackwardPropagate();
				ForwardPropagate();
				time--;
				count++;
			}

			for (int i = 0; i < outputrow; i++)
			{
				outputdata[m][i] = celllayer[numindex1][i];
			}
			count = 0;
		}

		//set the inputlayer and outputlayer
		//for (int i = 0; i < layernumber[0]; i++)
		//{
		//	cout << "Please input the "<< i+1 <<" st cell of inpputlayer" << endl;
		//	cin >> celllayer[0][i];
		//}

		//Normalize(celllayer[0],0);

		//for (int i = 0; i < layernumber[numindex1]; i++)
		//{
		//	cout << "Please input the " << i + 1 << " st cell of outputlayer" << endl;
		//	cin >> expectoutput[i];
		//}

		//Normalize(expectoutput,numindex1);

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

			//add up the bias which at the end of each weight layer
			celllayer[i + 1][j] += weightlayer[i][j][weightnumber[i][1] - 1];

			//make sure use which activate function
			switch (act)
			{
			case sigmoid:
				celllayer[i + 1][j] = 1 / (1 + exp(-celllayer[i + 1][j]));
				break;

			case tanhh:
				celllayer[i + 1][j] = (exp(celllayer[i + 1][j]) - exp(-celllayer[i + 1][j])) / (exp(celllayer[i + 1][j]) + exp(-celllayer[i + 1][j]));
				break;

			case relu:
				if (celllayer[i + 1][j] < 0)
				{
					celllayer[i + 1][j] = 0;
				}
				break;

				//orignal formula is f(x)=max(ax,x) preset 'a' as 0.01
			case prelu:
				if (celllayer[i + 1][j] < celllayer[i + 1][j] * a)
				{
					celllayer[i + 1][j] = celllayer[i + 1][j] * a;
				}
				break;

				//orignal formula is f(x)=a(e^x-1) preset 'a' as 0.01
			case elu:
				if (celllayer[i + 1][j] <= 0)
				{
					celllayer[i + 1][j] = (exp(celllayer[i + 1][j]) - 1) * a;
				}
				break;

				//unclear yet
				//case maxout:

			}
		}
	}
	return 0;
}

int Layer::BackwardPropagate()
{
	//set the backcell layer (set the last backcell layer firstly)
	switch (los)
	{
	case leastsquare:
		switch (act)
		{
		case sigmoid:
			for (int i = 0; i < layernumber[numindex1]; i++)
			{
				deviate[i] = expectoutput[i] - celllayer[numindex1][i];

				backcelllayer[numindex2][i] = deviate[i] * -2 / layernumber[numindex1] * celllayer[numindex1][i] * (1 - celllayer[numindex1][i]);
			}
			break;

		case tanhh:
			for (int i = 0; i < layernumber[numindex1]; i++)
			{
				deviate[i] = expectoutput[i] - celllayer[numindex1][i];

				backcelllayer[numindex2][i] = deviate[i] * -2 / layernumber[numindex1] * (1 - celllayer[numindex1][i] * celllayer[numindex1][i]);
			}
			break;
		}
		break;

	case logloss:
		switch (act)
		{
		case sigmoid:
			for (int i = 0; i < layernumber[numindex1]; i++)
			{
				//deviate[i] = expectoutput[i] - celllayer[numindex1][i];

				backcelllayer[numindex2][i] = ((1 - expectoutput[i]) / (1 - celllayer[numindex1][i]) - expectoutput[i] / celllayer[numindex1][i]) / layernumber[numindex1] * celllayer[numindex1][i] * (1 - celllayer[numindex1][i]);
			}
			break;

		case tanhh:
			for (int i = 0; i < layernumber[numindex1]; i++)
			{
				//deviate[i] = expectoutput[i] - celllayer[numindex1][i];

				backcelllayer[numindex2][i] = ((1 - expectoutput[i]) / (1 - celllayer[numindex1][i]) - expectoutput[i] / celllayer[numindex1][i]) / layernumber[numindex1] * (1 - celllayer[numindex1][i] * celllayer[numindex1][i]);
			}
			break;
		}
		break;

	}



	//set the others backsell layer
	switch (act)
	{
	case sigmoid:
		for (int i = numindex2 - 1; i >= 0; i--)
		{
			for (int j = 0; j < weightnumber[i + 1][1] - 1; j++)
			{
				for (int k = 0; k < weightnumber[i + 1][0]; k++)
				{
					backcelllayer[i][j] += backcelllayer[i + 1][k] * weightlayer[i + 1][k][j];
				}
				backcelllayer[i][j] = backcelllayer[i][j] * celllayer[i + 1][j] * (1 - celllayer[i + 1][j]);
			}
		}
		break;

	case tanhh:
		for (int i = numindex2 - 1; i >= 0; i--)
		{
			for (int j = 0; j < weightnumber[i + 1][1] - 1; j++)
			{
				for (int k = 0; k < weightnumber[i + 1][0]; k++)
				{
					backcelllayer[i][j] += backcelllayer[i + 1][k] * weightlayer[i + 1][k][j];
				}
				backcelllayer[i][j] = backcelllayer[i][j] * (1 - celllayer[i + 1][j] * celllayer[i + 1][j]);
			}
		}
		break;

	}


	//set the detaweight layer
	for (int i = numindex2; i >= 0; i--)
	{
		for (int j = 0; j < weightnumber[i][0]; j++)
		{
			for (int k = 0; k < weightnumber[i][1] - 1; k++)
			{
				detaweightlayer[i][j][k] = backcelllayer[i][j] * celllayer[i][k];

				switch (opt)
				{
				case gradient:
					detaweightlayer[i][j][k] = detaweightlayer[i][j][k] * weight[i];
					break;

					//without normalize, the initial gradient will be obviously deviate from the real value
				case momentum:
					historyweightlayer[i][j][k] += Beta * historyweightlayer[i][j][k] + (1 - Beta)* detaweightlayer[i][j][k];
					detaweightlayer[i][j][k] = historyweightlayer[i][j][k] * weight[i];
					break;

				case rmsprop:
					historyweightlayer[i][j][k] += Beta * historyweightlayer[i][j][k] + (1 - Beta) * detaweightlayer[i][j][k] * detaweightlayer[i][j][k];
					detaweightlayer[i][j][k] = weight[i] * detaweightlayer[i][j][k] / sqrt(historyweightlayer[i][j][k] + e);
					break;

				case adam:
					if (count == 0)
					{
						historyweightlayer[i][j][k] = detaweightlayer[i][j][k];
						historyweightlayer2[i][j][k] = detaweightlayer[i][j][k] * detaweightlayer[i][j][k];
					}
					else
					{
						historyweightlayer[i][j][k] += Beta * historyweightlayer[i][j][k] + (1 - Beta) * detaweightlayer[i][j][k];
						historyweightlayer2[i][j][k] += Beta * historyweightlayer2[i][j][k] + (1 - Beta) * detaweightlayer[i][j][k] * detaweightlayer[i][j][k];
					}
					detaweightlayer[i][j][k] = weight[i] * historyweightlayer[i][j][k] / sqrt(historyweightlayer2[i][j][k] + e);
				}

				//update the weight matrix immediately
				weightlayer[i][j][k] = weightlayer[i][j][k] - detaweightlayer[i][j][k];
			}
		}
	}

	//Update the weight matrix
	//for (int i = 0; i < midnumber; i++)
	//{
	//	for (int j = 0; j < weightnumber[i][0]; j++)
	//	{
	//		for (int k = 0; k < weightnumber[i][1]-1; k++)
	//		{
	//			weightlayer[i][j][k] = weightlayer[i][j][k] - detaweightlayer[i][j][k];
	//		}
	//	}
	//}

	return 0;
}

int Layer::Predict()
{
	/**********************************
	This part initial the matrix of testinputdata,
	testoutputdat, and testexpectdata
	**********************************/

	//initial the channel of testsample
	cout << "Please set the data channel." << endl;
	cin >> testdatachannel;

	//initial the testinputdata、testexpectdata、testoutputdata
	testinputdata = (double**)calloc(testdatachannel, sizeof(double*));
	testexpectdata = (double**)calloc(testdatachannel, sizeof(double*));
	testoutputdata = (double**)calloc(testdatachannel, sizeof(double*));

	for (int i = 0; i < testdatachannel; i++)
	{
		testinputdata[i] = (double*)calloc(inputrow, sizeof(double));
		testoutputdata[i] = (double*)calloc(outputrow, sizeof(double));
		testexpectdata[i] = (double*)calloc(outputrow, sizeof(double));

		for (int j = 0; j < inputrow; j++)
		{
			cout << "Please set the " << j + 1 << " st element of " << i + 1 << "st test input data channel." << endl;
			cin >> testinputdata[i][j];
		}

		for (int j = 0; j < outputrow; j++)
		{
			cout << "Please set the " << j + 1 << " st element of " << i + 1 << "st test expect data channel." << endl;
			cin >> testexpectdata[i][j];
		}
	}

	/*******************************
	This part predict the test sample
	through	previous trained network
	*******************************/
	//iterate the input and expect test data
	for (int m = 0; m < testdatachannel; m++)
	{
		celllayer[0] = testinputdata[m];
		Normalize(celllayer[0], 0);

		expectoutput = testexpectdata[m];
		Normalize(expectoutput, numindex1);

		//implement predict 
		ForwardPropagate();

		//get predict result
		for (int i = 0; i < outputrow; i++)
		{
			testoutputdata[m][i] = celllayer[numindex1][i];
		}
		count = 0;
	}

	return 0;
}

int Layer::PrintBackCellLayer()
{
	for (int i = 0; i < midnumber; i++)
	{
		cout << "The " << i + 1 << " st back cell layer is :" << endl;
		for (int j = 0; j < layernumber[i + 1]; j++)
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
				cout << weightlayer[i][j][k] << " , ";
			}
			cout << " ; " << endl;

		}
		cout << " **************************" << endl;
	}

	return 0;
}

int Layer::Normalize(double* layer, int layerindex)
{
	double temp = 0.0;

	for (int i = 0; i < layernumber[layerindex]; i++)
	{
		temp += layer[i];
	}

	for (int i = 0; i < layernumber[layerindex]; i++)
	{
		layer[i] = layer[i] / temp;
	}

	return 0;
}

int findmax()
{

	return 0;
}

int Layer::PrintInputData()
{
	for (int i = 0; i < datachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of input data is :" << endl;
		for (int j = 0; j < inputrow; j++)
		{
			cout << inputdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Layer::PrintOutputData()
{
	for (int i = 0; i < datachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of output data is :" << endl;
		for (int j = 0; j < outputrow; j++)
		{
			cout << outputdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}
int Layer::PrintExpectData()
{
	for (int i = 0; i < datachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of expect data is :" << endl;
		for (int j = 0; j < outputrow; j++)
		{
			cout << expectdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::PrintTestInputData()
{
	for (int i = 0; i < testdatachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of input data is :" << endl;
		for (int j = 0; j < inputrow; j++)
		{
			cout << testinputdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::PrintTestOutputData()
{
	for (int i = 0; i < testdatachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of output data is :" << endl;
		for (int j = 0; j < outputrow; j++)
		{
			cout << testoutputdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::PrintTestExpectData()
{
	for (int i = 0; i < testdatachannel; i++)
	{
		cout << "The " << i + 1 << " st channel of expect data is :" << endl;
		for (int j = 0; j < outputrow; j++)
		{
			cout << testexpectdata[i][j] << " , ";
		}
		cout << " ; " << endl;
	}

	return 0;
}

int Layer::Evaluate()
{
	for (int i = 0; i < testdatachannel; i++)
	{
		for (int j = 0; j < outputrow; j++)
		{
			double deta = sqrt(testexpectdata[i][j] * testexpectdata[i][j] - testoutputdata[i][j] * testoutputdata[i][j]);
			cout << deta << " , ";
		}
		cout << "********************************************" << endl;
	}

	return 0;
}
