#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "Serial.h"
#include "CControl.h"
#include "CPong.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")


#define XAXIS 15
#define YAXIS 9
#define pButton1 33
#define pButton2 32 
#define titleLine 60

int _reset = FALSE; //reset flag

CPong::CPong(int _size, int comport) //constructor - properly initialize the object
{
	Control.init_com(comport); //initialize the comport
	_canvas = (cv::Mat::zeros(cv::Size(_size, _size), CV_8UC3)); //create my canvas

	Control.get_analog(pad_x, pad_y);//get current joystick position so it doesn't start at 0,0 - initialize
}

CPong::~CPong() {}  //destructor - do any clean up required before memory is freed up

void CPong::update_thread(CPong* ptr)
{
	while (ptr ->_thread_exit == false)
	{
		ptr->update();
	}
}

void CPong::draw_thread(CPong* ptr)
{
	while (ptr->_thread_exit == false)
	{
		ptr->draw();
	}
}

void CPong::start()
{
	std::thread t1(&CPong::update_thread, this);
	std::thread t2(&CPong::draw_thread, this);
	t1.detach();
	t2.detach();
}

void CPong::run()
{
	start();
	while (1);
	cv::waitKey(500);
}

void CPong::pad_position()
{	
	static cv::Point p_old;
	static cv::Point p_new;
	static int tracker = 0;
	int clear = 0;
	int temp = pad_y;//to avoid glitchiness with threading

	Control.get_analog(pad_x, temp);//get current joystick position
	if (temp < padLength + titleLine) temp = padLength + titleLine;
	if (temp > (canvas_y - padLength)) temp = (canvas_y - padLength);

	pad_y = temp;

	comp_y = y; //computer tracks ball
	if (comp_y > canvas_y - padLength)
	{
		comp_y = canvas_y- padLength;
	}//end if
	if (comp_y < padLength+titleLine) {
		comp_y = padLength+titleLine;
	}
}

void CPong::randomDir()
{
	srand(time(NULL));
	direction = (eDir)((rand() % 4) + 1); //random direction for ball to move in
}

void CPong::changeDir(eDir d)
{
	direction = d;
}

inline eDir CPong::getDir()
{
	return direction;
}

void CPong::Move()
{
	switch (direction)
	{
	case STOP:
		break;
	case UPRIGHT:
		x+=10;
		y-=10;
		break;
	case DOWNRIGHT:
		x+=10;
		y+=10;
		break;
	case UPLEFT:
		x-=10;
		y-=10;
		break;
	case DOWNLEFT:
		x-=10;
		y+=10;
		break;
	default:
		break;
	}
}

void CPong::update() // read vertical input for paddle position
{
	CPong::pad_position();
}

void CPong::draw() //draws paddle, ball and score; compute ball position plus collision
{
	double startTick, freq;
	freq = cv::getTickFrequency(); //tick freq
	startTick = cv::getTickCount(); //get number of ticks since event
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(32);

	draw_mutex.lock();
	cv::imshow("Image", _canvas); //create the black canvas
	if (cv::waitKey(1) == 'q')
	{
		_thread_exit = true;
	}
	draw_mutex.unlock();

	//make da ball to start
	float radius = 15; //radius
	cv::Point center = cv::Point(x, y); //center
	cv::circle(_canvas, center, radius, cv::Scalar(200, 200, 200), CV_FILLED, 2); //start

	if ((score1 < 5) & (score2 < 5)) {
		_canvas = (cv::Mat::zeros(cv::Size(canvas_x, canvas_y), CV_8UC3)); //recreate my canvas to hide old images
		cv::rectangle(_canvas, cv::Point(canvas_x / 2 - 2, titleLine), cv::Point(canvas_x / 2 + 2, canvas_y), cv::Scalar(200, 100, 50), CV_FILLED, 8); //divider v
		cv::rectangle(_canvas, cv::Point(0, titleLine - 2), cv::Point(canvas_x, titleLine+2), cv::Scalar(200, 100, 50), CV_FILLED, 8); //divider h


		//move da ball - if it stops restart!
		while (direction == STOP)
		{
			CPong::randomDir();//start in a random diagonal
			x = canvas_x / 2;
			y = canvas_y / 2;
		}

		//CPong::Move();//move in the direction
		switch (direction)
		{
		case STOP:
			break;
		case UPRIGHT:
			x += 15;
			y -= 15;
			break;
		case DOWNRIGHT:
			x += 15;
			y += 15;
			break;
		case UPLEFT:
			x -= 15;
			y -= 15;
			break;
		case DOWNLEFT:
			x -= 15;
			y += 15;
			break;
		default:
			break;
		}

		//bouncing off walls
		//bottom wall
		if (y >= canvas_y - radius)
		{
			y = canvas_y - radius;
			CPong::changeDir(CPong::getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT); //if going downright go upright else go upleft
		}
		//top wall
		if (y <= titleLine + radius)
		{
			y = titleLine+radius;
			CPong::changeDir(CPong::getDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		}
		//bounce off paddles
		//player paddle
		if ((y <= (pad_y + padLength) && y >= (pad_y - padLength)) && (x<= padWidth + 15))
		{
			x = padWidth + 15;
			CPong::changeDir(CPong::getDir() == DOWNLEFT ? DOWNRIGHT : UPRIGHT);
		}
		//comp paddle
		if (x >= canvas_x - padWidth - 15) // comp tracks ball so don't need y param (y <= (y + padLength) && y >= (y - padLength)) && 
		{
			x = canvas_x - padWidth-15;
			CPong::changeDir(CPong::getDir() == DOWNRIGHT ? DOWNLEFT : UPLEFT);
		}
		//increment scores
		if (x >= canvas_x - radius) //if ball hits right edge
		{
			x = _canvas.size().width*0.5;//middle of the canvas
			score1++;
			direction = STOP;
		}
		if (x <= radius)
		{
			x = _canvas.size().width*0.5;//middle of the canvas
			score2++;
			direction = STOP;
		}

		cv::Point New = cv::Point(x, y); //new position
		cv::circle(_canvas, New, radius, cv::Scalar(200, 200, 200), CV_FILLED, 2); //start

		//make da paddle
		cv::rectangle(_canvas, cv::Point(0, (pad_y - padLength)), cv::Point(padWidth, (pad_y + padLength)), cv::Scalar(200, 200, 200), CV_FILLED, 8); //paddle rectangle
		cv::rectangle(_canvas, cv::Point(canvas_x, comp_y- padLength), cv::Point((canvas_x - padWidth), comp_y+ padLength), cv::Scalar(200, 200, 200), CV_FILLED, 8); //paddle rectangle

		//TEXT
		std::string scorep1 = "Player One: " + std::to_string(score1);
		cv::putText(_canvas, scorep1, cv::Point(170, 50), CV_FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(2000, 200, 200), 1, 8);
		std::string scorep2 = "Player Two: " + std::to_string(score2);
		cv::putText(_canvas, scorep2, cv::Point(canvas_x/2+170, 50), CV_FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(2000, 200, 200), 1, 8);
		std::string FPS = "FPS: " + std::to_string(frameRate);
		cv::putText(_canvas, FPS, cv::Point(canvas_x/2-35, 50), CV_FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 0, 200), 1, 8);
		std::string Title = "PONG";
		cv::putText(_canvas, Title, cv::Point(canvas_x / 2 - 42, 25), CV_FONT_HERSHEY_TRIPLEX, 1, cv::Scalar(150, 2000, 150), 1, 8);
	}
	else { //game over after five points
		_canvas = (cv::Mat::zeros(cv::Size(canvas_x, canvas_y), CV_8UC3)); //recreate my canvas to hide old image
		cv::putText(_canvas, "WASTED", cv::Point(_canvas.size().width*0.5-65, _canvas.size().height*0.5), CV_FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0, 0, 200), 5, 8);
		//if (kbhit)
		}
	std::this_thread::sleep_until(end_time); //sleep
	timecount = (cv::getTickCount() - startTick) / freq;
	frameRate = 1 / timecount; //fps to display
}