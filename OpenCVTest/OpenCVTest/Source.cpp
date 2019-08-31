#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int arg,char* ar)
{
	Mat in_image, out_image;
	string* argv=NULL;
	argv = (string*)calloc(3, sizeof(string));
	argv[0] = "C:\\Users\\WSB\\Desktop\\lusi.jpg";
	argv[1] = "C:\\Users\\WSB\\Desktop\\lusi2.jpg";
	argv[2] = "C:\\Users\\WSB\\Desktop\\lusi3.jpg";
	// Usage： <cmd> <file_in> <file_out>
	//读取原始图像
	in_image = imread(argv[0], IMREAD_UNCHANGED);
	if (in_image.empty()) {
		//检查是否读取图像
		cout << "Error! Input image cannot be read...\n";
		return -1;
	}
	//创建两个具有图像名称的窗口
	namedWindow(argv[1], WINDOW_GUI_NORMAL);
	namedWindow(argv[2], WINDOW_GUI_NORMAL);
	//在之前创建的窗口中显示图片
	imshow(argv[1], in_image);
	cvtColor(in_image, out_image, COLOR_BGR2GRAY);
	imshow(argv[2], out_image);
	//cout << "Press any key to exit...\n";
	waitKey(); // Wait for key press
	////写入图像
	//imwrite(argv[2], in_image);
	free(argv);
	argv = NULL;
	return 0;
}