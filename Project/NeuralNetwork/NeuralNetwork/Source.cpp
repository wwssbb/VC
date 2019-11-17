#include"NeuralNetwork.h"

int main()
{
	Layer l1(1000, leastsquare, sigmoid, gradient);
	getchar();

	//l1.PrintCellLayer();
	l1.PrintInputData();
	getchar();

	//l1.PrintWeightLayer();
	l1.PrintOutputData();
	getchar();

	l1.PrintExpectData();
	getchar();

	while (true)
	{
		l1.Predict();
		getchar();

		l1.PrintWeightLayer();
		getchar();

		l1.PrintTestInputData();
		getchar();

		l1.PrintTestExpectData();
		getchar();

		l1.PrintTestOutputData();
		getchar();
	}


	//l1.Evaluate();
	//getchar();

	return 0;
}