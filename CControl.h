#pragma once
#include "stdafx.h"
#include "Serial.h"

#include <string>
#include <iostream>
#include <thread>

#include "conio.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")


/**
*
* @brief Collects input and initializes the comport, and checks if command is successful
*
* This class is meant to contain all the variables related to
* the control.
*
* @author Aileen Maynard
*
*/
class CControl { 

	private:   
		Serial _com; ///< serial port object
	public:   
		CControl();   ///<constructor - properly initialize the object
		~CControl();   ///<destructor - do any clean up required before memory is freed up

		/** 
		* @brief initializes the serial port to the com port passed as a parameter to the method
		*
		* @param int comport
		* @return nothing to return
		*/
		void init_com(int comport);   

		/**
		* @brief type variable is enm for D, A or S. Returns TRUE if command succeeded, FALSE if it timed out
		*
		* @param int type, int channel, int &result
		* @return return TRUE or FALSE
		*/
		bool get_data(int type, int channel, float &result);   

		/**
		* @brief type variable is enm for D, A or S. Returns TRUE if command succeeded, FALSE if it timed out
		*
		* @param int type, int channel, int val 
		* @return return TRUE or FALSE
		*/
		bool set_data(int type, int channel, int val); 

		/**
		* @brief uses pointers to return x and y data
		*
		* @param
		* @return no return
		*/
		void get_analog(float &outputA, float &outputB);

		/**
		* @brief reads digital input and debounces it (1 second timeout)
		*
		* @param button (push button choice, sw1 or sw2) and count (tracking the button pushes)
		* @return no return
		*/
		void get_button(int button, int &count);


};

