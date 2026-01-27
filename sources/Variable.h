#pragma once

#include <string>

class Variable
{
private:
	std::string name;
	std::string code;
	std::string headerComment;

public:
	std::string getCode();
	std::string getName();
	std::string getHeader();

	void setCode(std::string s);
	void setUpVariable();
	void setUpName();
	void setHeader(std::string h);

};

