#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "CGameObject.h"
#include "CAsteroid.h"
#include "Serial.h"
#include "CControl.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

CAsteroid::CAsteroid()
{
	srand(time(NULL)); //seed rand with Time
	multiplier = ((float)rand() / (float)RAND_MAX); //random direction for ball to move in

	_radius = 10* multiplier; //size of asteroid
	_velocity = cv::Point2f(10 * multiplier, 10 * multiplier);
	_position = cv::Point2f(canvas_x*multiplier, 0);
	_lives = 1;
}

CAsteroid::~CAsteroid(){}

