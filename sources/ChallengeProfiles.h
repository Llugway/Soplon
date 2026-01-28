#pragma once

#include "File.h"
#include "SoplonDatabase.h"
#include <map>
#include <iterator>
#include <limits.h>
#include <filesystem>
#include <thread>
#include <time.h>
#include <chrono>
#include <filesystem>
#include "ThreadPool.h"
#include <sstream>
#include <filesystem>
#include "platform.h"

namespace fs = std::filesystem;

const std::string TOTAL_WORD_USED = "TOTAL_WORD_USED_AUTHOR_98";

enum Treatment { SIMPLE, BACKUP, COMPLETE, PARTIAL, CSV, SOCCO};

const unsigned int NB_THREAD = std::thread::hardware_concurrency();

const std::string DATA_A = "../datasets/data-A/";
const std::string DATA_B = "..datasets/data-B/";

const std::string DATA_SOCO_2020 = "C:/Users/Antonin/source/repos/ChallengeProfiles/AI-SOCO/data_dir/";

const std::string RESERVED_WORDS_C = "C:/Users/Antonin/source/repos/ChallengeProfiles/reservedWordsC.txt";
const std::string RESERVED_WORDS_CPP = "C:/Users/Antonin/source/repos/ChallengeProfiles/reservedWordsCpp.txt";

const std::string LOG_A = "Soplon_A.log";
const std::string LOG_B = "Soplon_B.log";
const std::string LOG_SOCO_2020 = "Soplon_SOCO_2020.log";

const std::string DEBUG_A = "Debug_A.log";
const std::string DEBUG_B = "Debug_B.log";
const std::string DEBUG_SOCO_2020 = "Debug_SOCO_2020.log";

const std::string DENOMS_A = "denoms_written_A.log";
const std::string DENOMS_B = "denoms_written_B.log";

const std::string RESULTS_A = "results_A.log";
const std::string RESULTS_B = "results_B.log";

const std::string WORDS_WEIGTH = "WordsWeight/wordsWeight.log";

const std::string CHUNKS_BY_FILE = "chunksByFileSave.txt";
const std::string CHUNKS_BY_FILE_ALL = "chunksByFileSaveAll.txt";

const bool ALL_AUTHORS = false;

const char data_A = 'A';
const char data_B = 'B';
const char data_SOCO_2020 = 'C';

const char data = 'A';

const bool ACTIVE_DEBUG = false;

const unsigned int ANSWERS_LENGTH = 10;

namespace fs = std::filesystem;

class ChallengeProfiles {
private:

	SoplonDatabase* database;

	std::map<std::string, unsigned int> fileId;

	Treatment t;
	std::ofstream saveFile;
	std::ofstream debug;

	int* scoring = new int[ANSWERS_LENGTH];
	unsigned int found = 0;
	unsigned int previousAnswer = 0;

	unsigned int nb_noAnswers = 0;
	unsigned int nb_answers = 0;

	unsigned int * numbersFiles;
	unsigned int nbFolders;

	unsigned int * chunksNoAnswer;
	unsigned int * chunksAnswer;
	
	std::vector<File*> files;

	std::set<int> authorsList;

	std::vector<std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>> chunksByFile;

	// unsigned int authorsAssociations[2048][2048];

	std::map<int, std::map<std::string, unsigned int>> mapWordsByAuhtor;
	std::map<int, Style> mapStyleByAuhtor;
	std::vector<std::string> debugChunkVec;

	std::map<std::string, std::set<std::string>> mapAssociationsLinks;
	std::map<std::string, std::map<int, int>> mapAssociationsWeight;

	std::vector<std::map<std::string,std::vector<std::pair<unsigned int, std::vector<std::pair<float, std::string>>>>>> weight_debug;

	std::vector<std::string> filesUsed;
	std::vector<std::string> chunkUsed;

	std::map<std::string, std::string> mapExtractedLines;

	std::map<std::string,std::vector<int>> answers;
	std::map<std::string,std::vector<unsigned>> answersWeight;
	std::map<std::string, int> trueAnswers;
	
	void actualizeFilesAssociationsThreaded(std::string path,int indexStart, int indexEnd, int indexThread);
	void readPartOfCSV(char* buffer, std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>> & mapChunksByFile, unsigned int size, int indexStart, int indexEnd, int indexThread);
	void readPartofChunksByFileSave(char* buffer, std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>> & mapChunksByFile, unsigned int size, int indexStart, int indexEnd, int indexThread);
	void createDenomsStructs(std::string path, std::vector<std::map<int, std::map<std::string, unsigned int>>> & vectorMapWordsByAuhtor, std::vector<std::map<int, Style>> &vectorMapStyleByAuhtor, std::vector<std::map<std::string, std::set<std::string>>>& vectorMapAssociationsLinks, std::vector<std::map<std::string, std::map<int, int>>>& vectorMapAssociationsWeight, int index);
	void answerChunkThreaded(std::string path, int index,unsigned int it);
	void insertThread(SoplonDatabase * db, unsigned int index);
	void readAuthorWords(std::string namefile,unsigned int auth);

public:	

	ChallengeProfiles(Treatment t);
	~ChallengeProfiles();

	void setUpAuthorsCode(std::string path);
	void backUpChunksByFile(std::ifstream & file, std::string filename);

	void generateOverallStructs(std::string path);
	void letsAnalyse();

	std::string ExtractLines(std::string nomFichier, int x, int y);

	void saveLogs();
	
	void loadFromCSV(std::string path, std::string filename);
	void saveAsCSV();

	void getAuthorsFromFile(std::string path);

	void getDenomResults(std::string path);

	void backupDenoms(std::string path);
	void backupWordsWeigth(std::string path);

	void filterReservedWords();

	void loadTestFile(std::string path);
	void loadResultFile(std::string path);

	void actualizeFilesAssociations(std::string path);

	void answerByChunk(std::string path,unsigned int it);
	void answerByFile(std::string path);
	
	void displayResult(unsigned int it);

	void filter();

	void debugChunk(std::string path);
	void debugChunkThreaded(std::string s , unsigned int index);

    void FillDatabase();
    void discoverDataset(std::string basePath);

	// void test(std::string filename);
};

// std::vector<Author*> authors;
// std::map<int, std::map<std::string,std::vector<int*>>> mapByAuthor;
