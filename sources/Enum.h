#pragma once

#include <string>

class Enum
{
private:

	std::string code;
	std::string headerComment;

public:

	void setCode(std::string s);
	std::string getCode();
	void setHeader(std::string h);
	std::string getHeader();

};

