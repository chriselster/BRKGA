#include "../Headers/Lecture.hpp"
#include "../Headers/Log.hpp"
#include <iostream>
Lecture::Lecture()
{
}

Lecture::Lecture(std::ifstream &file)
{
	file >> name_ >> begin_ >> end_ >> day_;
}

Lecture::~Lecture()
{
}

void Lecture::Print()
{
	Log::GetInstance().Print(name_, begin_, end_, day_);
}

void Lecture::PrintName()
{
	Log::GetInstance().PrintSingle(name_);
}

uint Lecture::GetEnd()
{
	return end_;
}

uint Lecture::GetBegin()
{
	return begin_;
}

uint Lecture::GetDay()
{
	return day_;
}