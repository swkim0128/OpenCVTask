#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "SerialPort.h"
using namespace std;
using namespace cv;

class OpenCVColorSearch {
private:
	const uchar FRONT = 100;
	const uchar STOP = 0;
	const uchar LEFT = 30;
	const uchar RIGHT = 60;
	const uchar MAX_VALUE = 255;
	const uchar MIN_VALUE = 100;

	VideoCapture capture;

public:	
	OpenCVColorSearch();

	void searchColor();
};