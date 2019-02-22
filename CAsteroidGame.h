#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CGameObject.h"
#include "CShip.h"
#include "CAsteroid.h"
#include "CMissile.h"
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

class CAsteroidGame : public CBase4618
{
private:
	float joy_x, joy_y; ///<joystick positions
	int frameRate; ///< FPS rate
	double timecount; ///<time counter
	int multiplier; ///<random multiplier
	char exit;

public:
	CAsteroidGame(int size, int comport);  ///<constructor - properly initialize the object
	~CAsteroidGame();  ///<destructor - do any clean up required before memory is freed up

	CShip Ship; ///<ship object

	//std::vector<CAsteroid> vecAsteroids; ///<vector of asteroids
	//std::vector<CMissile> vecMissiles; ///<vector of missiles

	//void start();

	/**
	* @brief Run is used to being the program
	* @param none
	* @return nothing to return
	*/
	void run();

	/**
	* @brief Update is used to update internal variables
	*		ex reads joystick for y coordinates for paddle position
	*
	* @param none
	* @return nothing to return
	*/
	void update();

	/**
	* @brief Draw will compute the ball position and determine if the
	*		ball has collided and the corresponding action to follow
	*		also renders display with paddles, ball and score
	*
	* @param none
	* @return nothing to return
	*/
	void draw();

	//void resetGame();

};