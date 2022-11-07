#include "../Headers/Log.hpp"
#include <iostream>

Log::Log()
{
	log_file_.open("log.txt", std::ios::out);
}

Log::~Log()
{
}

void Log::Print()
{
	log_file_ << std::endl;
}

Log &Log::GetInstance()
{
	static Log INSTANCE;
	return INSTANCE;
}