#include<iostream>
#include<string>
#include<vector>
#include"Eigen"

using namespace Eigen;
using namespace std;

int main()
{
	Matrix3d A;
	A << 1, 1, 1, 2, -1, -1, 2, -4, 5;

	HouseholderQR<Matrix3d> qr;
	qr.compute(A);
	MatrixXd R = qr.matrixQR().triangularView<Eigen::Upper>();
	MatrixXd Q = qr.householderQ();
	cout << "HouseholderQR" << endl;
	cout << "A " << endl << A << endl << endl;
	cout << "qr.matrixQR()" << endl << qr.matrixQR() << endl << endl;
	cout << "Q " << endl << Q << endl << endl;
	cout << "Q*Q " << endl << Q * Q.transpose() << endl << endl;
	cout << "R" << endl << R << endl << endl;
	cout << "Q*R" << endl << Q * R << endl;

	return 0;

}
