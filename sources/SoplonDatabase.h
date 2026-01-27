#pragma once

#include <mariadb/conncpp.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Auxilaire.h"

#define DATABASE_DIAGRAM_FILE "database.txt"

//Database infos
//const SAString database = "@Soplon";
//const SAString user = "root";
//const SAString pass = "root";

class SoplonDatabase
{
private:
	sql::Statement* stm;
	std::string path;
    std::unordered_map<std::string,std::vector<std::pair<std::string, std::string>>> tables;
public:
	SoplonDatabase(std::string path);
	~SoplonDatabase();
	void loadDatabaseDiagram(std::string path);
	bool query_insert_file(std::shared_ptr<sql::PreparedStatement>& stmnt,sql::SQLString name, unsigned int nbLines);
	bool query_insert_chunk(std::shared_ptr<sql::PreparedStatement>& stmnt, unsigned int idFile, unsigned int lineBegin, unsigned int lineEnd, int author);
	bool query_insert_author(std::shared_ptr<sql::PreparedStatement>& stmnt, int author);
	bool query_insert_denomination(std::shared_ptr<sql::PreparedStatement>& stmnt,sql::SQLString name);
	bool query_delete(std::shared_ptr<sql::PreparedStatement>& stmnt, std::string table);
	void displayTables();
	sql::Statement * getStatement();
	std::vector<std::pair<std::string, std::string>> getFieldsFromTable(std::string table);
	std::unique_ptr<sql::Connection> conn = nullptr;
};

