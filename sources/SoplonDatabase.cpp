#include "SoplonDatabase.h"
#include <fstream>

SoplonDatabase::SoplonDatabase(const std::string& path)
    : session("mysqlx://root:root@127.0.0.1:3306")  
    , db(session.getSchema("Soplon", true))          
{
    try {
        std::cout << "Connected to database: " << db.getName() << std::endl;
        loadDatabaseDiagram(path);
    }
    catch (const mysqlx::Error& err) {
        std::cerr << "Database connection error: " << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (const std::exception& ex) {
        std::cerr << "Standard exception: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

SoplonDatabase::~SoplonDatabase()
{
    std::cout << "Database disconnected!" << std::endl;
}

void SoplonDatabase::executeSQL(const std::string& sql) {
    try {
        session.sql(sql).execute();
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "SQL execution error: " << e.what() << std::endl;
    }
}

void SoplonDatabase::loadDatabaseDiagram(const std::string& path)
{
    std::string namefile = path + DATABASE_DIAGRAM_FILE;
    std::ifstream file(namefile);
    if (!file.is_open()) {
        std::cerr << "Cannot open diagram file: " << namefile << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(file, ligne)) {
        if (ligne.empty() || ligne[0] == '#' || ligne[0] == '-') continue;

        try {
            session.sql(ligne).execute();
        }
        catch (const mysqlx::Error& err) {
            std::cerr << "Error executing schema statement: " << err.what() << "\nStatement: " << ligne << std::endl;
        }
    }
    file.close();
    std::cout << "Database diagram loaded from " << namefile << std::endl;
}

// Exemple de query (adapte les noms de tables/colonnes)
bool SoplonDatabase::query_insert_file(std::shared_ptr<void> stmnt, const std::string& name, unsigned int nbLines)
{
    try {
        session.sql("INSERT INTO file (nom, nb_lignes) VALUES (?, ?)")
            .bind(name)
            .bind(static_cast<int>(nbLines))
            .execute();
        return true;
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "Error insert file: " << e.what() << std::endl;
        return false;
    }
}

// ... adapte les autres query_insert_* de la même façon (session.sql(...).bind(...).execute())