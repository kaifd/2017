// sp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdafx.h"
#include <windows.h>  //包含Sleep()函数
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;
//播放视频开始

int main(int argc, char** argv)
{
	//========================================================
	// CvCapture 是一个结构体，用来保存图像捕获所需要的信息。
	// opencv提供两种方式从外部捕获图像，一种是从摄像头中，一种
	// 是通过解码视频得到图像。两种方式都必须从第一帧开始一帧一帧
	// 的按顺序获取，因此每获取一帧后都要保存相应的状态和参数。
	// 比如从视频文件中获取，需要保存视频文件的文件名，相应的******
	// 类型，下一次如果要获取将需要解码哪一帧等。 这些信息都保存在
	// CvCapture结构中，每获取一帧后，这些信息都将被更新，获取下一帧
	// 需要将新信息传给获取的api接口
	//=======================================================
	CvCapture* capture = 0;
	//===========================================================
	// IplImage 是结构体类型，用来保存一帧图像的信息，也就是一帧
	// 图像的所有像素值构成的一个矩阵
	//===========================================================
	IplImage *frame, *frame_copy = 0;

	// 创建一个窗口，用“result”作为窗口的标识符
	cvNamedWindow("result", 1);

	// ==========================================
	// 初始化一个视频捕获操作。
	// 告诉底层的捕获api我想从 Capture1.avi中捕获图片，
	// 底层api将检测并选择相应的******并做好准备工作
	//==============================================
	//capture = cvCaptureFromFile("c://Capture1.avi");
	capture = cvCaptureFromFile("E:\\迅雷下载\\【lol电影天堂www.loldytt.com】钢刀.TC1280清晰国语中英双字.mp4");

		// 如果 初始化失败，那么capture为空指针，程序停止，
		// 否则进入捕获循环
		if (capture)
		{
		// 捕获循环
		for (;;)
		{
			// 调用cvGrabFrame,让底层api解码一帧图像
			// 如果解码失败，就退出循环
			// 如果成功，解码的图像保存在底层api的缓存中
			if (!cvGrabFrame(capture))
				break;

			// 将解码得到图像信息从缓存中转换成IplImage格式放在frame中
			frame = cvRetrieveFrame(capture);

			// 如果获取缓存或转换失败，则退出循环
			if (!frame)
				break;

			// 将frame中的图像信息在窗口result中显示
			cvShowImage("result", frame);

			// 暂停一会儿，让你看一下图像
			
			Sleep(20);//延迟图片播放时间
			
			// 如果你敲了键盘，就退出程序，否则继续捕获下一帧
			if (cvWaitKey(10) >= 0)
				break;
		}

		// 退出程序之前要清理一下堆栈中的内存，免得内存泄露
		//cvReleaseImage( &frame );注意不需要这句，因为frame是从视频中捕获的，没有单独分配内存，无需释放，当capture 释放的时候frame自然就释放了。

		// 退出之前结束底层api的捕获操作，免得它们占着茅坑不拉屎
		// 比如会使得别的程序无法访问已经被它们打开的文件
		cvReleaseCapture(&capture);

		}
	cvDestroyWindow("result");


	return 0;
}
