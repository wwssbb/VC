#include"Kalman.h"

int main()
{

	KalMan_std K(4, 20);
	KalMan_std* K2 = new KalMan_std(4, 20);

	for (int i = 0; i < K.length; i++)
	{
		cout << K.Target[i] << "         ;         " << K.Predict[i] << "      ;       " << endl;
		getchar();
	}

	cout << endl;
	getchar();

	//for (int i = 0; i < K.length; i++)
	//{
	//	cout << K.Predict[i] << "  ;  ";
	//}
	//cout << endl;
	//getchar();

	//for (int i = 0; i < K.length; i++)
	//{
	//	cout << K.Measure[i] << "  ;  ";
	//}

	cout << endl;
	getchar();

	return 0;
}