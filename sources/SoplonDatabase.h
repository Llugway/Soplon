#pragma once

#include <mysqlx/xdevapi.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

#define DATABASE_DIAGRAM_FILE "database.txt"

class SoplonDatabase
{
private:

    mysqlx::Session session;
    mysqlx::Schema db;
    std::string db_name = "Soplon";

    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> tables;

public:
    explicit SoplonDatabase(const std::string& path);
    ~SoplonDatabase();

    void loadDatabaseDiagram(const std::string& path);

    void executeSQL(const std::string& sql);

    // Méthodes query – adaptées à X DevAPI
    bool query_insert_file(std::shared_ptr<void> stmnt, const std::string& name, unsigned int nbLines);
    bool query_insert_chunk(std::shared_ptr<void> stmnt, unsigned int idFile, unsigned int lineBegin, unsigned int lineEnd, int author);
    bool query_insert_author(std::shared_ptr<void> stmnt, int author);
    bool query_insert_denomination(std::shared_ptr<void> stmnt, const std::string& name);
    bool query_delete(std::shared_ptr<void> stmnt, const std::string& table);

    void displayTables() const;
    std::vector<std::pair<std::string, std::string>> getFieldsFromTable(const std::string& table) const;

};

