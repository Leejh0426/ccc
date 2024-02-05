#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std::chrono;

//function to get time
std::string get_time();

void device_wait(int time_to_wait);



