#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "Serial.h"
#include "CControl.h"
#include "CAsteroidGame.h"
#include "CGameObject.h"
#include "CShip.h"
#include "CAsteroid.h"
#include "CMissile.h"
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
#define singleLife 1;
#define shipLives 10;
#define shipSize 20;

CAsteroidGame::CAsteroidGame(int _size, int comport) //constructor - properly initialize the object
{
	Control.init_com(comport); //initialize the comport
	_canvas = (cv::Mat::zeros(cv::Size(canvas_x, canvas_y), CV_8UC3)); //create my canvas

	Control.get_analog(joy_x, joy_y);//get current joystick position so it doesn't start at 0,0 - initialize
}
CAsteroidGame::~CAsteroidGame() {}

void CAsteroidGame::update()
{
	//read joystick position to draw ship
	Control.get_analog(joy_x, joy_y);
	cv::Point2f _position(joy_x, joy_y);
	Ship.set_pos(_position);

	//read two pushbutton inputs - fire n reset
	// flag if psuhed, print event to scree (Cout)
	//loop over vector for asteroids + missiles detect collisions + determine remmainig lives
	//loop over again and remove objects with lives<=0
	//loop over remaining objects to draw
}

void CAsteroidGame::draw() 
{

	double startTick, freq;
	freq = cv::getTickFrequency(); //tick freq
	startTick = cv::getTickCount(); //get number of ticks since event
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(32);


	cv::imshow("Image", _canvas); //create the black canvas

	
	Ship.draw(_canvas);

	//draw objects - ship, vector of asteroids, vector of missiles
	//call draw method
	//player score, number of lives of ship

	//TEXT
	int pLives = 10, score = 100;
	std::string scorep1 = "Player One: " + std::to_string(score) + " Lives: " + std::to_string(pLives);
	cv::putText(_canvas, scorep1, cv::Point(170, 50), CV_FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(2000, 200, 200), 1, 8);
	std::string Title = "ASTEROIDS";
	cv::putText(_canvas, Title, cv::Point(canvas_x / 2 - 42, 25), CV_FONT_HERSHEY_TRIPLEX, 1, cv::Scalar(150, 2000, 150), 1, 8);

	//timing stuff
	std::this_thread::sleep_until(end_time); //sleep
	timecount = (cv::getTickCount() - startTick) / freq;
	frameRate = 1 / timecount; //fps to display
}

void CAsteroidGame::run() 
{
	do 
	{
		CAsteroidGame::draw();
		exit = cv::waitKey(1);
	} while (exit != 'q');

	//start();
	//while (1);
	//cv::waitKey(500);
	//randomly create asteroid every few sec
	//initialize asteroid object
	//CAsteroid astro();
	//_asteroid_list.push_back(astro);
}

