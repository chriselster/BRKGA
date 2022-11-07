#ifndef __LOG_H__
#define __LOG_H__
#include <fstream>
#include <string>

class Log
{
private:
	std::ofstream log_file_;
	Log();

public:
	~Log();
	static Log &GetInstance();

	template <typename T, typename... Types>
	void Print(T &&var1, Types &&...var2)
	{
		log_file_ << var1 << " ";
		Print(var2...);
	}
	void Print();

	template <typename T>
	void PrintSingle(T value)
	{
		log_file_ << value;
	}
};

#endif // __LOG_H__