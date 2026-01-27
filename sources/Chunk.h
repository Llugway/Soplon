#pragma once
#include <string>
#include <set>
#include <map>

#include "Style.h"


static const std::set<char> specialChar = { '\t' ,'\n' ,',', ';', '|', '*','(', ')' ,'[', ']','{', '}','<','>','/','+', '-','=','.','%','\\',':','!','?','\'','&' ,'"','\'','^','#','@','$' };

static const std::set<char> compareSymbols = {'<','>','!','='};

static const std::set<char> affectationSymbols = {'+','-','*','/','%','&','^','|'};

class Chunk
{
private:
	Style chunkStyle;
	std::string buffer;
	std::map<std::string, unsigned int> words;

	unsigned int begin;
	unsigned int end;
	int author;
	unsigned int nb_resolve; // for chunks unknown

	// std::set<uint64_t> patterns;

public:
	Chunk(std::vector<std::string>& fileBuffer, std::string buffer, unsigned int begin, unsigned int end, int author);
	Chunk(unsigned int begin, unsigned int end, int author);
	~Chunk();
	std::string getBuffer();
	void setBuffer(std::string s);
	int getAuthor();
	std::map<std::string, unsigned int> getWords();
	void freeMemories();

	std::string realBuffer;
	unsigned int getItResolve();

	void appendBuffer(std::string extraBuffer);

	unsigned int getLineBegin();
	unsigned int getLineEnd();
	std::pair<unsigned int, unsigned int> getLines();

	void displayStyle();
	Style getStyle();

};

