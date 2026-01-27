#pragma once

// #include "Auxilaire.h"

#include <vector>
#include <string>


class Prototype
{

private:

	std::string proto;
	std::string type;

	int countUpper;
	int countUnderscore ;

	bool firstCharUpperCase;
	bool upperIsPresent;
	bool underscoreIsPresent;
	bool fullUpper;

public:
	Prototype();
	std::string getPrototype();
	void setPrototype(std::string p);
	void setType(std::string t);
	std::string getType();
	bool getFirstCharUpperCase();
	void setFirstCharUpperCase(bool b);
	bool getUpperIsPresent();
	void setUpperIsPresent(bool b);

	void setUp();


};

