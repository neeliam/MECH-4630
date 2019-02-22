#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CShip.h"
#include "Serial.h"
#include "CControl.h"
#include "CAsteroidGame.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

CShip::CShip ()
{
	srand(time(NULL)); //seed rand with Time
	multiplier = ((float)rand() / (float)RAND_MAX); //random direction for ball to move in

	_radius = 40 * multiplier; //size of asteroid
	_velocity = cv::Point2f(10 * multiplier, 10 * multiplier);
	_position = cv::Point2f(canvas_x/2, canvas_y/2);
	_lives = 10;
}
CShip::~CShip() {}

