#pragma once
// some pong code from https://www.youtube.com/watch?v=Z6hUxXCzKYE
//lots of code straight from Craig's notes
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "time.h"
#include "CBase4618.h"
#include "Serial.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")
#define canvas_x 1000
#define canvas_y 650
#define padWidth 20
#define padLength 50

enum eDir { STOP = 0, UPLEFT, DOWNLEFT, UPRIGHT, DOWNRIGHT };

/**
*
* @brief CPong class inherits from CBase
*
* This class contains the code for the game of Pong
*
* @author Aileen Maynard
*
*/
class CPong : public CBase4618
{

private:
	int pad_y, pad_x; ///< analog input from the joystick;
	//use points, then use p = po+v*deltaT
	int ball_y, ball_x; ///< ball position
	int result, button_first, button_next; ///< to track button pushes; 
	int _reset; ///< tracking reset (true or false); 
	int score1 = 0; ///< track the player 1 score
	int score2 = 0; ///< track the player 2 score
	double x = canvas_x/2; ///< x position 
	double y = canvas_y/2; ///< y position 
	int comp_y; ///<computer y coordinate
	double timecount; ///<time counter
	double velocity = 400; ///< velocity to speed up ball
	eDir direction = STOP; ///< direction of ball
	int frameRate; ///< FPS rate

	bool _thread_exit=false;
	std::mutex draw_mutex;
	static void update_thread(CPong* ptr);
	static void draw_thread(CPong* ptr);


public:
	CPong(int size, int comport);  ///<constructor - properly initialize the object
	~CPong();  ///<destructor - do any clean up required before memory is freed up

	void start();
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

	/**
	* @brief tracks both pad positions
	*
	* @param none
	* @return nothing to return
	*/
	void pad_position();

	/**
	* @brief picks a random direction to start the ball in 
	*
	* @param none
	* @return nothing to return
	*/
	void randomDir();
	
	/**
	* @brief move the ball around
	*
	* @param none
	* @return nothing to return
	*/
	void Move();

	/**
	* @brief change direction if the ball hits a wall or paddle
	*
	* @param none
	* @return nothing to return
	*/
	void changeDir(eDir d);

	/**
	* @brief get the current direction of the ball
	*
	* @param none
	* @return nothing to return
	*/
	inline eDir getDir();
	
};
