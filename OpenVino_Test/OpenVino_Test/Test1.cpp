#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\WSB\\Desktop\\lusi.jpg", IMREAD_UNCHANGED);
	imshow("Lusi", src);

	waitKey(0);
	return 0;
}