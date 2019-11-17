#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main(int argc, char** argv) {
	string xml = "D:/projects/models/vehicle-license-plate-detection-barrier-0106/FP32/vehicle-license-plate-detection-barrier-0106.xml";
	string bin = "D:/projects/models/vehicle-license-plate-detection-barrier-0106/FP32/vehicle-license-plate-detection-barrier-0106.bin";
	Mat src = imread("D:/images/vehicle_01.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_NORMAL);
	namedWindow("ssd-model optimizer demo", WINDOW_NORMAL);
	imshow("input", src);

	// ����ģ��
	Net net = readNetFromModelOptimizer(xml, bin);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);

	// ��������
	printf("ssd network model loaded...\n");
	Mat blob = blobFromImage(src, 1.0, Size(300, 300), Scalar(), true, false, 5);
	net.setInput(blob);

	// �ƶ�Ԥ��
	float threshold = 0.5;
	Mat detection = net.forward();

	// ��ȡ�ƶ�ʱ��
	vector<double> layerTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layerTimings) / freq;
	ostringstream ss;
	ss << "infernece : " << time << " ms";
	putText(src, ss.str(), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2, 8);

	// ����������
	Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
	for (int i = 0; i < detectionMat.rows; i++) {
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > threshold) {
			size_t obj_index = (size_t)detectionMat.at<float>(i, 1);
			float tl_x = detectionMat.at<float>(i, 3) *  src.cols;
			float tl_y = detectionMat.at<float>(i, 4) *  src.rows;
			float br_x = detectionMat.at<float>(i, 5) *  src.cols;
			float br_y = detectionMat.at<float>(i, 6) *  src.rows;
			Rect object_box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int(br_y - tl_y)));
			rectangle(src, object_box, Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	imshow("ssd-model optimizer demo", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
