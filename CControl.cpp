#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "CControl.h"
#include "Serial.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

// for deleting part of string: https://en.cppreference.com/w/cpp/string/basic_string/find_last_of

CControl::CControl() {}
CControl::~CControl() {}

void CControl::init_com(int comport) {

	std::string word = "COM"; 
	std::string comName;
	comName = word + std::to_string(comport); //attach desired number to COM
	
	_com.open(comName);
	_com.flush(); //add check : if (_com.isOpened() == true)
}

bool CControl::get_data(int type, int channel, float &result) {

	// TX and RX strings
	std::string tx_str = "G " + std::to_string(type) + " " + std::to_string(channel) + "\n"; //load the string with the user choice input
	std::string rx_str;

	// Send TX string
	_com.write(tx_str.c_str(), tx_str.length());
	Sleep(10); // wait for ADC conversion, etc. May not be needed? 

	// temporary storage
	char buff[2];

	// start timeout count
	double start_time = cv::getTickCount();

	buff[0] = 0;
	// Read 1 byte and if an End Of Line then exit loop
	// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
	while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0) //testing for a second
	{
		if (_com.read(buff, 1) > 0)
		{
			rx_str = rx_str + buff[0]; //writes to string as it comes in from com (?)			}
		}//endif
	}//endwhile

		// 3 spaces at end of string - find and delete past the space; all that will be left is value at end
		// ie what comes in is "A 1 15 482\n", want to delete everthing but value 482
		//const std::string path = "/root/config";
		auto pos = rx_str.find_last_of(' ');
		auto temp = rx_str.substr(pos + 1);

		rx_str = temp;
		
		result = stoi(rx_str);

	return true;
}

bool CControl::set_data(int type, int channel, int val) {

	// TX strings
	std::string tx_str = "S " + std::to_string(type) + " " + std::to_string(channel) + " " + std::to_string(val) + "\n"; // gather user input
	std::string rx_str;

	// Send TX string
	_com.write(tx_str.c_str(), tx_str.length());
	Sleep(10); // wait for ADC conversion, etc. May not be needed? 
	
	//temporary storage
	char buff[2];

	//start timeout count
	double start_time = cv::getTickCount();

	buff[0] = 0;
	// Read 1 byte and if an End Of Line then exit loop
	//Timeout after 1 second, if debugging step by step this will cause you to exit the loop
	while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0) //testing for a second
	{
		if (_com.read(buff, 1) > 0)
		{
			rx_str = rx_str + buff[0];
		}//endif
	}//endwhile

	return true;
}

void CControl::get_button(int button, int &count) // 33 for S1, 32 for S2
{
	int button_first = 1; //button status (0 if pressed)
	float result;
	int tracker; //input from micro

	get_data(0, button, result); //get digital data from selected button, store in button first

	if (button_first == result)
	{
		tracker = 1;
	} else {
		tracker = 0;
		button_first = result;
	}//end ifelse
	if ((button_first == 0) && (tracker == 0)) {
			count++;
			Sleep(10);
			tracker = 1;
		}//end if
}
 
void CControl::get_analog(float &outputA, float &outputB)
{
	get_data(1, 9, outputB); //get y data
	outputB = (outputB*1.5-250);

	get_data(1, 15, outputA); //get x data
	outputA = (outputA*1.5-200); //give a percentage
}
