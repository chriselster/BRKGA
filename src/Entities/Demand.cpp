#include "../Headers/Demand.hpp"
#include "../Headers/Log.hpp"
#include <iostream>

Demand::Demand()
{
}

Demand::Demand(std::ifstream &file)
{
	uint num_lectures, num_teachers;
	file >> code_ >> student_qtt_ >> num_teachers;
	file.ignore();
	std::string teacher;
	std::getline(file, teacher); // remove endl
	while (num_teachers--)
	{
		std::getline(file, teacher);
		teachers_.push_back(teacher);
	}
	file >> num_lectures;
	while (num_lectures--)
	{
		Lecture lecture = Lecture(file);
		lectures_.push_back(lecture);
	}
}

Demand::~Demand()
{
}

void Demand::Print()
{
	Log::GetInstance().Print(code_);
	for (auto &&lecture : lectures_)
	{
		lecture.Print();
	}
}

bool Demand::operator<(Demand &other)
{
	return student_qtt_ <= other.student_qtt_;
}

uint Demand::value()
{
	return student_qtt_;
}

std::vector<Lecture> Demand::GetLectures()
{
	return lectures_;
}

uint Demand::GetStudentQtt()
{
	return student_qtt_;
}

void Demand::Allocate()
{
	allocated = true;
}

bool Demand::is_allocated()
{
	return allocated;
}