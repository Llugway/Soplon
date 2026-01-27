#pragma once

#include "Prototype.h"
#include <iostream>
#include "Auxilaire.h"


class Function
{
private:

	Prototype * prototype;
	float commentsPercentages;
	bool withHeader;
	std::string code;
	std::string header;
	std::string comments;
	int nbLineHeader;

	std::vector<std::string> commentsLanguages;
	std::vector<std::string> codeLanguages;

public:

	Function();
	~Function();

	float getCommentsPercentages();
	bool getWithHeader();
	std::string getCode();
	std::string getPrototype();
	std::string getHeader();
	std::string getComments();
	int getNbLineHeader();

	std::vector<std::string> getCommentsLanguages();
	std::vector<std::string> getCodeLanguages();

	void setCommentsPercentages(float per);
	void setWithHeader(bool header);
	void setCode(std::string code);
	void setPrototype(std::string s);
	void setHeader(std::string h);

	void calculatePercentages();
	void analysePrototype();
	void setComments();
	void setUpFunction();

	void findLanguage();

};

