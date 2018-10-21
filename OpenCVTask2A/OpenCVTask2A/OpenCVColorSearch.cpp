#include "OpenCVColorSearch.h"

OpenCVColorSearch::OpenCVColorSearch() : capture(0) {
	if (capture.isOpened() == false) {
		std::cerr << "Error, can not find capture divice\n";
		return;
	}
}

void OpenCVColorSearch::searchColor() {
	char port_name[20] = "\\\\.\\COM4";
	SerialPort arduino(port_name);

	if (arduino.isConnected()) {
		cout << "connect" << endl;
	}
	else {
		cerr << "disconnected" << endl;
	}

	Mat frame;
	Mat hsv;

	char ch = ' ';

	while (1) {
		capture >> frame;

		if (frame.empty()) {
			std::cerr << "ERROR! Unable to open camera\n";
			break;
		}

		cvtColor(frame, hsv, COLOR_BGR2HSV);

		int rowsMiddle = hsv.rows / 2;
		int colsMiddle = hsv.cols / 2;

		uchar h = hsv.at<Vec3b>(rowsMiddle, colsMiddle)[0];
		uchar s = hsv.at<Vec3b>(rowsMiddle, colsMiddle)[1];
		uchar v = hsv.at<Vec3b>(rowsMiddle, colsMiddle)[2];

		if (MIN_VALUE < s && s < MAX_VALUE && MIN_VALUE < v && v < MAX_VALUE) {
			if (STOP < h && h < STOP + 10) {
				ch = 's';
			}
			else if (FRONT - 10 < h && h < FRONT + 10) {
				ch = 'f';
			}
			else if (RIGHT - 10 < h && h < RIGHT + 10) {
				ch = 'r';
			}
			else if (LEFT - 10 < h && h < LEFT + 10) {
				ch = 'l';
			}
		}
		
		imshow("이진화 영상", hsv);
		imshow("원본 영상", frame);

		if (waitKey(100) >= 0) {
			if (arduino.isConnected()) {
				arduino.writeSerialPort(&ch, 1);
				cout << ch << endl;
			}
		}
	}

}
