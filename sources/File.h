#pragma once

#include "Function.h"
#include <fstream>
#include "Structure.h"
#include "Macro.h"
#include "Header.h"
#include "Variable.h"
#include "Enum.h"
#include <set>
#include "Chunk.h"

/* PERCENTAGES */
#define NBPARAMPERCENTS 4

#define PERCENTFUNCCOMMENT 0
#define PERCENTFUNCWITHHEADER 1
#define MEAN 2
#define STANDARDDEVIATION 3

/* NUMBERS FUNCTIONS */
#define NBPARAMFUNCTIONS 3

#define NBFUNCTIONS 0
#define NBCOMMENTFUNC 1
#define NBFUNCWITHHEADER 2

/* BOOLEANS */
#define NBPARAMBOOL 2

#define UPPER 0
#define FIRSTCHARUPPER 1
#define UNDERSCORE 2


static const std::string PATH = "C:/Users/Antonin/source/repos/ChallengeProfiles/ResultsFile/";

class File
{
private:

	std::ifstream fichier;

	std::string path;

	std::string namefile;

	Header * header;

	std::vector<std::string> buffer;

	std::map<std::string,std::set<int>> AssociationsLinked;
	std::map<std::string, std::map<int, int>> associationsWeight;

	std::map<std::string, int> chunks;
	std::set<std::pair<unsigned int, unsigned int>> linesSet;

	std::map<std::pair<unsigned int, unsigned int>, Chunk*> chunksKnown; 
	std::map<std::pair<unsigned int,unsigned int>, Chunk*> chunksUnKnown; 

	std::map<unsigned int, std::map<std::string, unsigned int>> wordsByAuthor;
	std::map<unsigned int, Style> styleByAuthor;

	std::map<std::string, std::vector<int>> answers;

	std::string result;

public:
	File();
	File(std::string path, std::string namefile);
	File(std::string path,std::string namefile, std::set<std::pair<std::pair<unsigned int,unsigned int>,int>>chunks);
	~File();

	std::string getNamefile();
	
	bool isCommentLine(std::string s);
	bool isCommentBlockB(std::string s);
	bool isCommentBlockE(std::string s);

	void DisplayInfos();
	void FileToChunks();
	void FileToBuffer();

	void setUpHeader();

	Header* getHeader();
	std::map<std::pair<unsigned int, unsigned int>, Chunk*> getChunksUnknow();

	void removeChunkUnknow(std::string cu);

	void SaveResult();

	void loadBuffer();

	void linkAnonymousDenoms();

	std::set<int>getDenomLinks(std::string s);
	int getDenomWeigth(std::string s, int author);

	void setDenomLinks(std::string s, std::set<int> list);
	void setDenomWeigth(std::string s, std::map<int,int> m);

	void freeMemories();
	//std::string getBuffer();
	std::vector<std::string> getBuffer();

	std::map<std::string, std::vector<int>> getAnswers();
	std::map<unsigned int, std::map<std::string, unsigned int>> getWordsByAuthor();
	std::map<unsigned int, Style> getStyleByAuthor();

	void appendChunksBuffer(unsigned int it);

	static std::string getKeyChunkByLines(unsigned int first, unsigned int second);

	static std::string getKeyChunkByLines(std::pair<unsigned int, unsigned int> p);

	static std::pair<unsigned int, unsigned int> getLinesChunkByKey(std::string key);
	// void add(chunksKnown)
};

