#pragma once

#include <string>
#include <vector>
#include "Auxilaire.h"
#include <map>
#include <iostream>
#include <unordered_set>



static const std::vector<std::string> copyrightAnnouncers = {"COPYRIGHT", "Copyright","©" , "(C)" , "(c)" };
static const std::vector<std::string> authorAnnouncers = { "Author(s):","Authors:", "Author:", "AUTHOR(S):","AUTHORS:", "AUTHOR:" };
static const std::vector<std::string> writtenByAnnouncers = { "by:", "By:", "BY:", "Written by","Written By", "Modifications by" };

static const std::vector<std::string> copyrightNoises = { "©" ,"Â", "(C)" , "(c)","ALL RIGHTS RESERVED", "All rights reserved","All Rights Reserved","All right reserved","All rights rsvd","All rights","All Rights"};
static const std::vector<std::string> noises = {"by" };

class Header
{
private:

	std::map<std::string,std::set<unsigned int>> mailAddress;
	std::map<std::string, std::set<unsigned int>> webAddress;

	std::string headerComment;
	std::vector<std::string> headerCommentVector;

	std::vector<std::pair<std::pair<unsigned int, unsigned int>, int>> authorsLines;

	int nbChars;
	bool withHeader;

	bool withSimpleCommentLine; // Full //
	bool withStars;				// Full /*************/

	bool authorPresent;
	bool withLicense;

	unsigned int begin;
	unsigned int end;


public:

	// std::unordered_set<std::string>* denom;
	// std::map<std::string,std::pair<unsigned int,unsigned int>>* denom;
	std::map<std::string, std::set<unsigned int>> denom;

	Header();
	std::string getHeader();
	int getNbChars();
	bool getWithHeader();

	void setHeader(std::string h);
	void setHeaderVector(std::vector<std::string> v);

	void setHeaderBegin(unsigned int i);
	unsigned int getHeaderBegin();
	void setHeaderEnd(unsigned int i);
	unsigned int getHeaderEnd();

	void setAuthorsLines(std::vector<std::pair<std::pair<unsigned int, unsigned int>, int>> s);
	void parseHeader();
	void parseHeader2();

	void findCustomMailAddress();

	void countChars();

	void freeMemories();
};

