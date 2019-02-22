#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "Serial.h"
#include "CControl.h"
#include "CMissile.h"
#include "CAsteroidGame.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

CMissile::CMissile() {
	srand(time(NULL)); //seed rand with Time
	multiplier = ((float)rand() / (float)RAND_MAX); //random direction for ball to move in

	_radius = 20; //size of missile
	_velocity = cv::Point2f(10, 10); //constant velocity
	_lives = 1;
//	cv::circle(_canvas, center, _radius, cv::Scalar(200, 200, 200), 4, 2); //create the asteroid
}