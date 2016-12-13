#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <iostream>
#include "opencv2/opencv.hpp"
//------------------------------------
/*
*/

using namespace cv;
using namespace std;

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, char* argv[])
{

	bool recording = false;
	bool startNewRecording = false;
	bool firstRun = true;
	int videoNumber = 0;

	VideoCapture cap(0); // open the video camera no. 0

	cv::VideoWriter writer;

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
		return -1;
	}

	char* windowName = "Webcam Feed";
	namedWindow(windowName, CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed

	//fourcc integer

	int fcc = CV_FOURCC('D', 'I', 'V', '3');

	//frames per sec integer

	int fps = 4;

	//frame size

	cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));


	Mat frame; 


	while (1) {

		if (startNewRecording == true)
		{
 
			startNewRecording = false;
			recording = true;

			//videoNumber++;

		}

		bool bSuccess = cap.read(frame); // read a new frame from camera feed

		if (!bSuccess) //test if frame successfully read
		{
			cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
			break;
		}


		if (recording == true)
		{
			writer.write(frame);

			putText(frame, "REC", Point(0, 60), 2, 2, Scalar(0, 0, 255));
		}

		imshow(windowName, frame); //show the frame in "MyVideo" window

		//listen for 10ms for a key to be pressed
		switch (waitKey(10)){

		case 27:
			//'esc' has been pressed (ASCII value for 'esc' is 27)
			//exit program.
			return 0;

		case 114:
			//r button is pressed
				//toggle recording

			recording = !recording;

			if (recording == true) cout << "Begin Recording" << endl;
			else cout << "Recording Paused" << endl;

				//insert code here

			if (firstRun)
			{

				//filename string

				string filename = "D:\myVideo0.avi";
				writer = VideoWriter(filename, fcc, fps, frameSize);

				if (!writer.isOpened())
				{
					cout << "ERROR OPENING FILE FOR WRITE" << endl;
					getchar();

					return -1;
				}

			}

			break;

		case 110:
			//n button is pressed

				//start new recording

			startNewRecording = true;

			cout << "New Recording started" << endl;

			if (firstRun == true) firstRun = false;

				//insert code here

			break;

		}


	}

	return 0;

}
////////////////////////////////////////////////////////////////////////////////////////////
