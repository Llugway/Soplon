#pragma once

#include <string>

class Macro
{
private:
	std::string buffer;
	std::string name;
	std::string headerComment;
public:
	Macro();

	std::string getMacro();
	std::string getName();
	std::string getHeader();

	void setBuffer(std::string s);
	void setHeader(std::string s);
	void setUpMacro();
};

