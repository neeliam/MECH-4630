#pragma once
#include "stdafx.h"
#include "Serial.h"
#include "CControl.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

/**
*
* @brief Base class to hold common code
*
* This class is meant to contain all the common code for this course
*
* @author Aileen Maynard
*
*/
class CBase4618 {

private:
public:
	CBase4618();   ///<constructor - properly initialize the object
	~CBase4618();   ///<destructor - do any clean up required before memory is freed up

	cv::Mat _canvas; ///<image matrix

	CControl Control; ///< Object of type control

	/**
	* @brief Run will call update and draw in a loop
	*		while waiting for the user to enter 'q' to exit
	*
	* @param none
	* @return nothing to return
	*/
	virtual void run();

	/**
	* @brief update will be overloaded in child class
	*
	* @param none
	* @return nothing to return
	*/
	virtual void update() = 0;

	/**
	* @brief Draw will be overloaded in child class
	* @param none
	* @return nothing to return
	*/
	virtual void draw() = 0;
};