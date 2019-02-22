#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <thread>

#include "CBase4618.h"
#include "CGameObject.h"
#include "Serial.h"
#include "CControl.h"
#include "CAsteroidGame.h"
#include "time.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

class CAsteroid : public CGameObject
{
private:
	float multiplier;
public:
	CAsteroid();
	~CAsteroid();
};
