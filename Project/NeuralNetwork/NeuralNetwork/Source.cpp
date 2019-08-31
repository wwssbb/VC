#include"NeuralNetwork.h"

int main()
{
	Layer l1(10, 1000);

	l1.PrintCellLayer();
	getchar();

	l1.PrintWeightLayer();
	getchar();

	return 0;
}