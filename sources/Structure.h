#pragma once

#include <string>

class Structure
{
private:
	std::string buffer;
	std::string name;
	std::string header;
	
	bool typeDef;
	bool withHeader;

public:
	std::string getName();
	std::string getStructure();
	std::string getHeader();

	bool getWithHeader();

	void setBuffer(std::string s);
	void setHeader(std::string s);


	void setUpStruct();

};

