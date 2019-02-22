#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "CBase4618.h"
#include "Serial.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

CBase4618::CBase4618() {}  //constructor - properly initialize the object
CBase4618::~CBase4618() {}   //destructor - do any clean up required before memory is freed up

void CBase4618::update() {}//end update()

void CBase4618::draw() {}//end draw()

void CBase4618::run()
{
	
	//do 
	//{
	//	draw();
	//	update();
	//} while (cv::waitKey(1) != 'q');
}//end run()