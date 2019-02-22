#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "Serial.h"
#include "CControl.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

#define canvas_x 1000
#define canvas_y 650

class CGameObject {
protected:
	cv::Point2f _position;
	cv::Point2f _velocity;
	int _radius;
	int _lives;
public:
	void move();
	bool collide(CGameObject &obj);
	bool collide_wall(cv::Size board);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(cv::Point2f pos) { _position = pos; }
	cv::Point2f get_pos() { return _position; }
	void draw(cv::Mat &im);
};