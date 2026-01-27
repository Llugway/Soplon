#include "SoplonDatabase.h"

SoplonDatabase::SoplonDatabase(std::string path) {

	try {

		sql::Driver* driver = sql::mariadb::get_driver_instance();
	
		sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/Soplon");
		
		sql::Properties properties({
			  {"user", "root"},
			  {"password", "root"}
			});

		conn = std::unique_ptr<sql::Connection>((driver->connect(url, properties)) );
		conn->setAutoCommit(false);


		stm = conn->createStatement();
		stm->execute("USE Soplon");	

	}
	catch (...) {
		std::cerr << "Invalid database connection" << std::endl;
		exit(EXIT_FAILURE);
	}
}

SoplonDatabase::~SoplonDatabase() {
	conn->close();
    printf("Database disconnected!\n");
}

void SoplonDatabase::loadDatabaseDiagram(std::string path)
{
	std::string namefile = path + DATABASE_DIAGRAM_FILE;
	std::ifstream file(namefile);
    std::string ligne;

    while (getline(file, ligne)){
        std::string bufferRequest(ligne);
        stm->execute(bufferRequest);
    }
}

bool SoplonDatabase::query_insert_chunk(std::shared_ptr<sql::PreparedStatement>& stmnt, unsigned int idFile, unsigned int lineBegin, unsigned int lineEnd, int author) {
	try {
		
		stmnt->setInt(1, idFile);
		stmnt->setInt(2, lineBegin);
		stmnt->setInt(3, lineEnd);
		stmnt->setInt(4, author);

		// Execute Statement
		stmnt->executeUpdate();

		return true;
	}

	// Catch Exception
	catch (sql::SQLException& e) {
		std::cerr << "Error insert chunk: "
			<< e.what() << std::endl;
	}
}

bool SoplonDatabase::query_insert_author(std::shared_ptr<sql::PreparedStatement>& stmnt, int author) {
	try {

		stmnt->setInt(1, author);

		stmnt->executeUpdate();

		return true;

	}
	catch (sql::SQLException& e) {
		std::cerr << "Error insert author: "
			<< e.what() << std::endl;
	}
}

bool SoplonDatabase::query_insert_denomination(std::shared_ptr<sql::PreparedStatement>& stmnt, sql::SQLString name)
{
	try {
		stmnt->setString(1, name);

		stmnt->executeUpdate();

		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "Error insert denomination: "
			<< e.what() << std::endl;
		return false;
	}
}

bool SoplonDatabase::query_insert_file(std::shared_ptr<sql::PreparedStatement>& stmnt,sql::SQLString name, unsigned int nbLines) {
	try {

		stmnt->setString(1, name);
		stmnt->setInt(2, nbLines);

		// Execute Statement
		stmnt->executeUpdate();

		return true;
	}

	// Catch Exception
	catch (sql::SQLException& e) {
		std::cerr << "Error insert file: "
			<< e.what() << std::endl;
		return false;
	}
}

bool SoplonDatabase::query_delete(std::shared_ptr<sql::PreparedStatement>& stmnt, std::string table)
{

	try {

		stmnt->setString(1, table);
		// Execute Statement
		stmnt->executeUpdate();
	}

	// Handle Exceptions
	catch (sql::SQLException& e) {
		std::cerr << "Error in delete operation: "
			<< e.what() << std::endl;
		return false;
	}

	return true;
}


void SoplonDatabase::displayTables()
{
	for (const std::pair<std::string, std::vector<std::pair<std::string, std::string>>>& v : tables) {
		std::cout << "Table : " << v.first << std::endl;
		for (std::pair<std::string, std::string> p : v.second) {
			std::cout << p.first << " (" << p.second << "); ";
		}
		std::cout << "\n" << std::endl;
	}
}

sql::Statement *SoplonDatabase::getStatement()
{
	return stm;
}

std::vector<std::pair<std::string, std::string>> SoplonDatabase::getFieldsFromTable(std::string table)
{
	return tables[table];
}
