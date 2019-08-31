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
	// Usage�� <cmd> <file_in> <file_out>
	//��ȡԭʼͼ��
	in_image = imread(argv[0], IMREAD_UNCHANGED);
	if (in_image.empty()) {
		//����Ƿ��ȡͼ��
		cout << "Error! Input image cannot be read...\n";
		return -1;
	}
	//������������ͼ�����ƵĴ���
	namedWindow(argv[1], WINDOW_GUI_NORMAL);
	namedWindow(argv[2], WINDOW_GUI_NORMAL);
	//��֮ǰ�����Ĵ�������ʾͼƬ
	imshow(argv[1], in_image);
	cvtColor(in_image, out_image, COLOR_BGR2GRAY);
	imshow(argv[2], out_image);
	//cout << "Press any key to exit...\n";
	waitKey(); // Wait for key press
	////д��ͼ��
	//imwrite(argv[2], in_image);
	free(argv);
	argv = NULL;
	return 0;
}