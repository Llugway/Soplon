#include "ChallengeProfiles.h"

ChallengeProfiles::ChallengeProfiles(Treatment t)
{
    auto start_overall = std::chrono::system_clock::now();
    std::time_t start_time_overall = std::chrono::system_clock::to_time_t(start_overall);

    std::string path;

    if (data == data_A)
        path = DATA_A;
    else if (data == data_B)
        path = DATA_B;
    else if (data == data_SOCO_2020)
        path = DATA_SOCO_2020;

    this->t = t;

    for (int i = 0; i < ANSWERS_LENGTH; i++) {
        scoring[i] = 0;
    }

    saveLogs();
    database = new SoplonDatabase(path);

    if (t == SIMPLE) {
        std::cout << "On est dans le code" << std::endl;
        //path += "Codes/";
        //std::string key = "r58/1649";
        //std::cout << key << std::endl;
        //File* f = new File(path, key);
        //f->loadBuffer();
        //f->setUpHeader();
        //delete f;

        //database = new SoplonDatabase(path);
        //database->query_select("file");

        //std::vector<std::pair<std::string, std::string>> updates;
        //std::vector<std::pair<std::string, std::string>> inserts;
        //std::vector<std::string> conditions;

        //updates.push_back(std::make_pair("nom", "file3"));
        //conditions.push_back("id = '5'");

        //d->query_update("file",updates,conditions);

        //inserts.push_back(std::make_pair("nom", "file3"));
        //inserts.push_back(std::make_pair("nb_lignes", "10"));

        //d->query_insert("file",inserts);

        //thread_pool pool(NB_THREAD);
        //pool.setShowProgress(false);
        //pool.wait_for_tasks();

    }
    else if (t == BACKUP) {

        std::string request = "DELETE from ";

        std::vector<std::string> t = { "DenominationLinkedAuthor","Denomination" }; // L'ordre a de l'importance vis à vis des contraintes
        //                if (filesUsed.size() == 20000)
        //                    break;
        try {
            for (const auto& p : t) {
                database->getStatement()->execute(request + p);
                database->conn->commit();
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what(); // information from error printed
        }

        if(data == 'A' || data == 'B')
            getAuthorsFromFile(path);

        backupWordsWeigth(path);
        backupDenoms(path);
        loadResultFile(path);

        if (data == 'A' || data == 'B') {
            loadFromCSV(path, "test_labels.csv");

            unsigned it = 0;
            bool first = true;

            while ((filesUsed.size() != 0 && it != 100) || first) {

                auto start = std::chrono::system_clock::now();

                answerByChunk(path, it);
                displayResult(it);
                it++;

                if (first)
                    first = false;

                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed = (end - start) / 60;
                std::cout << "overall elapsed time : " << elapsed.count() << "m\n" << std::endl;

            }
        }
    }
    else if (t == COMPLETE) {
        if (data == data_A || data == data_B) {
            database->loadDatabaseDiagram(path);
            discoverDataset(path);
            getAuthorsFromFile(path);
            setUpAuthorsCode(path);
            FillDatabase();
            generateOverallStructs(path);
            getDenomResults(path);
        }
    }
    else if (t == PARTIAL) {
        // countRepositories(path);
        getAuthorsFromFile(path);
        loadFromCSV(path, "test_labels.csv");
        debugChunk(path);

        //loadTestFile(path);
        //generateOverallStructs(path);
        //backupWordsWeigth(path);
        //filter();
        //getDenomResults(path);
    }
    else if (t == SOCCO) {

        for (unsigned int i = 0; i < 1000; i++)
            authorsList.insert(i);

        //loadFromCSV(path, "train.csv");
        //generateOverallStructs(path);
        //getDenomResults(path);

        //filesUsed.clear();

        backupWordsWeigth(path);	// Récupérer que par rapport à AuthorList (DONNEES A : 800 MO)
        loadResultFile(path);
        loadFromCSV(path, "dev_test.csv");
        answerByFile(path);
        displayResult(0);

        std::cout << "Building CSV !\n";

        std::ofstream resultFile;
        resultFile.open(path + "answer_dev.csv");
        resultFile << "uid,pid\n";

        for (std::pair<std::string, int> p : trueAnswers) {
            resultFile << p.second << "," << p.first << "\n";
        }

        resultFile.close();
    }
    else if (t == CSV) {

        /*saveLogs();
        countRepositories(path);
        generateOverallStructs(path);

        std::cout << "Building CSV !\n";

        std::ofstream idFiles, fileLinks;
        idFiles.open("files.csv");
        idFiles << "IdFile;NameFile\n";

        fileLinks.open("links.csv");
        fileLinks << "idFile";
        for (int i = 0; i < 30; i++) {
            fileLinks << ";link" << i;
        }
        fileLinks << "\n";

        int count = 0;
        std::cout << files.size() << std::endl;
        for (std::pair<std::string, File*> occ : files) {

            std::unordered_set<std::string> denominations = *(occ.second->getHeader()->denom);
            idFiles << count << ';' << occ.first << '\n';
            if (denominations.size() != 0) {
                fileLinks << count;

                for (const std::string deno : denominations) {
                    std::string s = ';' + deno;
                    fileLinks << ';' << deno;
                }
                fileLinks << '\n';

            }
            count++;
        }

        idFiles.close();
        fileLinks.close();*/

    }

    auto end_overall = std::chrono::system_clock::now();
    std::time_t end_time_overall = std::chrono::system_clock::to_time_t(end_overall);

    std::chrono::duration<double> elapsed = (end_overall - start_overall) / 60;

    std::cout << "overall elapsed time : " << elapsed.count() << "m\n" << std::endl;

    std::cout << "Begin at " << std::ctime(&start_time_overall) << std::endl;
    std::cout << "Finished at " << std::ctime(&end_time_overall) << std::endl;

}

ChallengeProfiles::~ChallengeProfiles()
{
    saveFile.close();

    for (File* f : files)
        if (f != nullptr)
            delete f;

    if (chunksAnswer != NULL)
        free(chunksAnswer);
    if (chunksNoAnswer != NULL)
        free(chunksNoAnswer);

    if (scoring != nullptr)
        delete scoring;

    delete database;

}

void ChallengeProfiles::setUpAuthorsCode(std::string path)
{

    std::string request = "INSERT INTO Author (id)  VALUES";

    for (int i = -1; i < 2048; i++) {

        if (i == 2048 - 1) {
            request += " ('" + std::to_string(i) + "');";
        }
        else {
            request += " ('" + std::to_string(i) + "'),";
        }
    }

    database->getStatement()->execute(request);
    database->conn->commit();

    std::ifstream chunksByFileSave;
    std::string filename;

    if(ALL_AUTHORS)
        filename = CHUNKS_BY_FILE_ALL;
    else
        filename = CHUNKS_BY_FILE;

    chunksByFileSave.open(path + filename);

    if (chunksByFileSave)
        backUpChunksByFile(chunksByFileSave, filename);
    else {
        loadFromCSV(path, "train_labels.csv");
    }
}

void ChallengeProfiles::backUpChunksByFile(std::ifstream & file, std::string filename)
{

    if (!file) {
        std::cout << "Error to read " << filename << std::endl;
        exit(1);
    }
    else {
        std::cout << "Starting BackUp : " << filename << std::endl;
        std::filebuf* pbuf = file.rdbuf();
        std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
        pbuf->pubseekpos(0, file.in);

        char* buffer = new char[size];

        pbuf->sgetn(buffer, size);

        file.close();

        std::vector<std::thread> threads;
        std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>> vectorMapChunksByFile;

        unsigned linesByThread = size / NB_THREAD;

        for (int i = 0; i < NB_THREAD; i++)
            vectorMapChunksByFile.push_back({});

        for (int i = 0; i < NB_THREAD - 1; i++)
            threads.push_back(std::thread(std::bind(&ChallengeProfiles::readPartofChunksByFileSave, this, buffer, std::ref(vectorMapChunksByFile), size, i * linesByThread, (i + 1) * linesByThread, i + 1)));
        // readPartofChunksByFileSave( buffer,vectorMapChunksByFile, size, i * linesByThread, (i + 1) * linesByThread, i + 1);

        threads.push_back(std::thread(std::bind(&ChallengeProfiles::readPartofChunksByFileSave, this, buffer, std::ref(vectorMapChunksByFile), size, (NB_THREAD - 1) * linesByThread, size, NB_THREAD)));
        // readPartofChunksByFileSave( buffer, vectorMapChunksByFile, size, (NB_THREAD - 1) * linesByThread, size, NB_THREAD);


        for (std::thread& t : threads)
            t.join();

        threads.clear();

        std::cout << "Merging structure ChunksByFile ..." << std::endl;

        unsigned int nb_chunks = 0;

        for (unsigned int i = 0; i < NB_THREAD; i++) {
            for (const std::pair< std::string, std::set < std::pair<std::pair<unsigned int, unsigned int>, int>>>& p : vectorMapChunksByFile[i]) {
                chunksByFile.push_back(p.second);
                filesUsed.push_back(p.first);
                nb_chunks += p.second.size();

                //	if (filesUsed.size() == 20000)
                //		break;
            }
            //if (filesUsed.size() == 20000)
            //	break;
        }

        delete[] buffer;

        std::cout << "BackupChunksByFile finished. Nombre de fichiers cibles par les chunks : " << filesUsed.size() << std::endl;
        std::cout << "BackupChunksByFile finished. Nombre de chunks cibles : " << nb_chunks << std::endl;

    }

}

std::string getCurrentDir() {
    //	char buff[160];
    //	GetModuleFileName(NULL, (LPWSTR)buff, 160);
    //	std::string::size_type position = std::string(buff).find_last_of("\\/");
    //	return std::string(buff).substr(0, position);
    return "";
}

void ChallengeProfiles::readPartOfCSV(char* buffer, std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>>& mapChunksByFile, unsigned int size, int indexStart, int indexEnd, int indexThread) {

    std::this_thread::sleep_for (std::chrono::milliseconds(indexThread*100));
    std::cout << "Thread " << std::to_string(indexThread) << " is starting.  = [" << indexStart << " ; " << indexEnd << "[." << std::endl;
    unsigned int total = 0;
    unsigned doubleocc = 0;
    int i = indexStart;

    while (i != 0 && buffer[i - 1] != '\n')
        i--;

    indexStart = i;

    while (indexEnd != 0 && buffer[indexEnd - 1] != '\n')
        indexEnd--;

    while (i < size && (i - indexEnd < 0)) {
        try {

            if (data == data_A || data == data_B) {
                std::string tab[4];
                for (int j = 0; j < 4; j++) {
                    while (buffer[i] != ',' && buffer[i] != '\n') {
                        tab[j] += buffer[i];
                        i++;
                    }
                    i++;
                }

                if(ALL_AUTHORS)
                    mapChunksByFile[indexThread - 1][tab[3]].insert(std::make_pair(std::make_pair(stoul(tab[1]), stoul(tab[2])), stoi(tab[0])));
                else if (stoi(tab[0]) == -1 || authorsList.find(stoi(tab[0])) != authorsList.end())
                    mapChunksByFile[indexThread - 1][tab[3]].insert(std::make_pair(std::make_pair(stoul(tab[1]), stoul(tab[2])), stoi(tab[0])));

            }
            else if (data == data_SOCO_2020) {
                std::string tab[2];
                for (int j = 0; j < 2; j++) {
                    while (buffer[i] != ',' && buffer[i] != '\n') {
                        tab[j] += buffer[i];
                        i++;
                    }
                    i++;
                }

                if (tab[0] == "")
                    tab[0] = "-1";

                mapChunksByFile[indexThread - 1][tab[1]].insert(std::make_pair(std::make_pair(0, 0), stoi(tab[0])));

            }
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }

    std::cout << "Thread " << indexThread << " finished." << std::endl;
}

void ChallengeProfiles::readPartofChunksByFileSave(char* buffer, std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>>& mapChunksByFile, unsigned int size, int indexStart, int indexEnd, int indexThread) {

    std::this_thread::sleep_for (std::chrono::milliseconds(indexThread*100));
    std::cout << "Thread " << std::to_string(indexThread) << " is starting.  = [" << indexStart << " ; " << indexEnd << "[." << std::endl;

    int i = indexStart;

    while (i != 0 && buffer[i - 1] != '\n')
        i--;

    indexStart = i;

    while (indexEnd != 0 && buffer[indexEnd - 1] != '\n')
        indexEnd--;

    while (i < size && (i - indexEnd < 0)) {
        try {
            if (data == data_A || data == data_B) {
                std::string key;
                std::string tab[3];

                while (buffer[i] != ':') {
                    key += buffer[i];
                    i++;
                }

                i++;

                while (buffer[i] != '\n') {
                    for (int j = 0; j < 3; j++) {
                        while (buffer[i] != ',' && buffer[i] != ';') {
                            tab[j] += buffer[i];
                            i++;
                        }
                        i++;
                    }

                    mapChunksByFile[indexThread - 1][key].insert(std::make_pair(std::make_pair(stoul(tab[0]), stoul(tab[1])), stoi(tab[2])));
                    tab[0] = "";
                    tab[1] = "";
                    tab[2] = "";

                }
                i++;
            }
            /*else if (data == data_SOCO_2020) {
                std::string tab[2];
                for (int j = 0; j < 2; j++) {
                    while (buffer[i] != ',' && buffer[i] != '\n') {
                        tab[j] += buffer[i];
                        i++;
                    }
                    i++;
                }

                if (tab[0] == "")
                    tab[0] = "-1";

                mapChunksByFile[indexThread - 1][tab[1]].insert(std::make_pair(std::make_pair(0, 0), stoi(tab[0])));

            }*/
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }

    std::cout << "Thread " << indexThread << " finished." << std::endl;
}


void ChallengeProfiles::loadFromCSV(std::string path, std::string filename)
{
    std::ifstream file((path + filename).c_str());

    if (!file) {
        std::cout << path + filename << std::endl;
        std::cout << "Error to read csv : " << filename.c_str() << std::endl;
        exit(1);
    }
    else {
        std::cout << "Starting LoadFromCSV : " << filename << std::endl;
        std::filebuf* pbuf = file.rdbuf();
        std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
        pbuf->pubseekpos(0, file.in);

        char* buffer = new char[size];

        pbuf->sgetn(buffer, size);

        file.close();

        std::vector<std::thread> threads;
        std::vector<std::map <std::string, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>>>> vectorMapChunksByFile;
        std::map< std::string, std::set <std::pair<std::pair<unsigned int, unsigned int>, int>>> mapChunksByFile;

        unsigned linesByThread = size / NB_THREAD;

        for (int i = 0; i < NB_THREAD; i++)
            vectorMapChunksByFile.push_back({});

        for (int i = 0; i < NB_THREAD - 1; i++)
            threads.push_back(std::thread(std::bind(&ChallengeProfiles::readPartOfCSV, this, buffer, std::ref(vectorMapChunksByFile), size, i * linesByThread, (i + 1) * linesByThread, i + 1)));
        //readPartOfCSV( buffer, vectorMapChunksByFile, size, i* linesByThread, (i + 1)* linesByThread, i + 1);

        threads.push_back(std::thread(std::bind(&ChallengeProfiles::readPartOfCSV, this, buffer, std::ref(vectorMapChunksByFile), size, (NB_THREAD - 1) * linesByThread, size, NB_THREAD)));
        //threads.push_back(std::thread(std::bind(&ChallengeProfiles::readPartOfCSV, this, buffer, std::ref(vectorMapChunksByFile), size, (NB_THREAD - 1) * linesByThread, size, NB_THREAD)));

        for (std::thread& t : threads)
            t.join();

        threads.clear();

        std::cout << "Merging structure ChunksByFile ..." << std::endl;

        mapChunksByFile = vectorMapChunksByFile[0];

        ThreadPool pool(NB_THREAD);
        pool.setShowProgress(false);

        //if (t == COMPLETE) {
        //	for (int i = 0; i < nbFolders; i++) {
        //		std::string folder = "r" + std::to_string(i) + '/';
        //		total += numbersFiles[i];
        //		for (int j = 0; j < numbersFiles[i]; j++) { // REMPLACER PAR nbFolders
        //
        //			std::string file = std::to_string(j);
        //			std::string key = folder + file;

        //			mapChunksByFile[key];

        //			pool.submit([vectorMapChunksByFile, &mapChunksByFile, key]() {
        //				for (int i = 1; i < NB_THREAD; i++) {
        //					if (vectorMapChunksByFile[i].find(key) != vectorMapChunksByFile[i].end()) {
        //						std::set<std::pair<std::pair<unsigned int, unsigned int>, int>> temp = vectorMapChunksByFile[i][key];
        //						mapChunksByFile[key].insert(temp.begin(), temp.end());
        //					}
        //				}
        //			});
        //		}
        //	}
        //	pool.wait_for_tasks();
        //}


        for (unsigned int i = 1; i < NB_THREAD; i++) {
            for (const std::pair< std::string, std::set < std::pair<std::pair<unsigned int, unsigned int>, int>>>& p : vectorMapChunksByFile[i]) {
                mapChunksByFile[p.first].insert(p.second.begin(), p.second.end());
                //for (const std::pair<std::pair<unsigned int, unsigned int>, int >& a : p.second) {
                //	authorsList.insert(a.second);
                //}
            }
        }

        // }

        for (int i = 0; i < NB_THREAD; i++) {
            pool.submit([&vectorMapChunksByFile, i] {vectorMapChunksByFile[i].clear(); });
        }

        std::cout << "Building and saving final structures... " << std::endl;
        std::ofstream chunksByFileSave;
        if("train_labels.csv" == filename)
            chunksByFileSave.open(path + CHUNKS_BY_FILE);

        unsigned int mb_chunks = 0;
        for (const std::pair< std::string, std::set < std::pair<std::pair<unsigned int, unsigned int>, int>>>& p : mapChunksByFile) {

            if (p.second.size() != 0) {

                std::string key = p.first;
                mb_chunks += p.second.size();

                chunksByFile.push_back(p.second);
                filesUsed.push_back(key);

                if (chunksByFileSave)
                    chunksByFileSave << p.first << ":";

                for (auto& elem : p.second) {
                    if(t == BACKUP)
                        answers[p.first + '-' + File::getKeyChunkByLines(elem.first)];

                    if (t == SOCCO)
                        answers[p.first];

                    if (chunksByFileSave) {
                        chunksByFileSave << elem.first.first << "," << elem.first.second << "," << elem.second << ";";
                    }
                }
                if(chunksByFileSave)
                    chunksByFileSave << "\n";

//                if (filesUsed.size() == 20000)
//                    break;

            }
        }

        if (chunksByFileSave)
            chunksByFileSave.close();

        delete[] buffer;
        pool.wait_for_tasks();

        std::cout << "LoadFromCSV finished. Nombre de chunks cibles  : " << mb_chunks << std::endl;
        std::cout << "LoadFromCSV finished. Nombre de fichiers cibles par les chunks : " << filesUsed.size() << std::endl;

    }
}

void ChallengeProfiles::saveAsCSV()
{
    std::cout << "Starting  save" << std::endl;
    std::ofstream myfile;
    //myfile.open("authors.csv");
    //myfile << "id:ID(AUTHOR_ID),:LABEL" << '\n';
    //for (int i = 0; i < 2048; i++) {
    //	// myfile << i << ',' << i+1 << '\n';
    //	myfile << i << ",Author";
    //	myfile << std::endl;
    //}

    //myfile.close();

    //myfile.open("authors_relationships64.csv");

    //std::map<std::string, std::unordered_set<int>> temp = mapAuthorsByFile;
    //std::map<std::pair<int, int>, int> csvStruct;

    //for (std::pair<std::string, std::unordered_set<int>> p : temp) {
    //	std::vector<int> set;
    //	set.assign(p.second.begin(), p.second.end());

    //	for (int i = 0; i < set.size() - 1; i++) {
    //		for (int j = i + 1; j < set.size(); j++) {
    //			if (authorsList.find(set[i]) != authorsList.end() || authorsList.find(set[j]) != authorsList.end()) {
    //				if (set[i] < set[j]) {
    //					csvStruct[std::make_pair(set[i], set[j])]++;
    //				}
    //				else
    //					csvStruct[std::make_pair(set[j], set[i])]++;
    //			}
    //		}
    //	}
    //}

    //myfile << ":START_ID(AUTHOR_ID),:END_ID(AUTHOR_ID),:TYPE,weigth:int\n";
    //for (std::pair<std::pair<int, int>, int> occ : csvStruct) {
    //	myfile << occ.first.first << "," << occ.first.second << ",WORK_WITH," << occ.second;
    //	myfile << std::endl;
    //	// myfile << occ.first.first << ',' << occ.first.second << ',' << occ.second << '\n';
    //}
}

void ChallengeProfiles::backupDenoms(std::string path) {

    std::cout << "Starting backup denominations !" << std::endl;

    std::string namefile;
    if (data == data_A)
        namefile = path + DENOMS_A;
    else
        namefile = path + DENOMS_B;

    std::ifstream file(namefile);
    std::string ligne;

    if(file){
        std::string baseRequest = "INSERT INTO denomination (id,nom) VALUES ";
        std::string inter = "";

        std::string baseRequestDenomAssociation = "INSERT INTO DenominationLinkedAuthor (id_denom,id_author,occ) VALUES ";
        std::string inter2 = "";

        std::vector<std::string> reqs;

        unsigned int count = 0;
        unsigned int count_link = 0;

        while (getline(file, ligne))
        {
            std::string denom = ligne.substr(0,ligne.find("("));
            std::vector<std::string> temp = split(ligne, ":");

            unsigned int authorsIndex = temp.size() - 1;

            std::vector<std::string>authors = split(temp[authorsIndex], ",");

            /*		if (authors.size() == 1) {
                unsigned int nb = stoi(authors[0].substr(authors[0].find('(') + 1, authors[0].find(')') - 1));
                authors[0] = authors[0].substr(0, authors[0].find('('));
                mapAssociationsWeight[denom][stoi(authors[0])] = nb;
            }
            else*/
            if (authors.size() != 0) {
                for (int i = 0; i < authors.size(); i++) {
                    unsigned int nb = stoi(authors[i].substr(authors[i].find('(') + 1, authors[i].find(')') - 1));
                    authors[i] = authors[i].substr(0, authors[i].find('('));
                    mapAssociationsWeight[denom][stoi(authors[i])] = nb;

                    if (count_link % 999 == 0) {
                        inter2 += "('" + std::to_string(count) + "','" + authors[i] + "','" + std::to_string(nb) + "')";
                    }
                    else if (count_link % 999 == 998) {
                        inter2 += ", ('" + std::to_string(count) + "','" + authors[i] + "','" + std::to_string(nb) + "')";
                        reqs.push_back(baseRequestDenomAssociation + inter2);
                        inter2 = "";
                    }
                    else
                        inter2 += ", ('" + std::to_string(count) + "','" + authors[i] + "','" + std::to_string(nb) + "')";

                    count_link++;

                }
            }

            if (count % 999 == 0) {
                inter += "('" + std::to_string(count) + "','" + denom + "')";
            }
            else if (count % 999 == 998 ) {
                inter += ", ('" + std::to_string(count) + "','" + denom + "')";
                database->getStatement()->execute(baseRequest + inter);
                database->conn->commit();
                inter = "";
            }
            else
                inter += ", ('" + std::to_string(count) + "','" + denom + "')";

            count++;

        }

        if (count % 999 != 998) {
            database->getStatement()->execute(baseRequest + inter);
            database->conn->commit();
        }

        if (count_link % 999 != 0) {
            reqs.push_back(baseRequestDenomAssociation + inter2);
        }

        for (std::string s : reqs) {
            database->getStatement()->execute(s);
            database->conn->commit();
        }

        file.close();

         std::cout << "finished backup, AssociationsWeights : " << mapAssociationsWeight.size() << std::endl;
    }
    else{
         std::cout << "No file detected."<< std::endl;
    }

}

void ChallengeProfiles::readAuthorWords(std::string namefile, unsigned int auth)
{
    std::ifstream file(namefile);
    std::string ligne;
    uint64_t total = 0;
    if (file) {
        while (getline(file, ligne))
        {
            std::vector<std::string> temp = split(ligne, ":");
            mapWordsByAuhtor[auth][temp[0]] += stoi(temp[1]);
            total += stoi(temp[1]);
        }
        mapWordsByAuhtor[auth][TOTAL_WORD_USED] = total;
        file.close();
    }
    else {
        std::cout << "Can't open " << namefile << std::endl;
    }

}

void ChallengeProfiles::backupWordsWeigth(std::string path)
{
    std::cout << "Starting backup Words Weigth !" << std::endl;

    std::string namefile;
    if (data == data_A)
        namefile = path + WORDS_WEIGTH;
    else
        namefile = path + WORDS_WEIGTH;

    ThreadPool pool(NB_THREAD);

    pool.setShowProgress(false);

    namefile = path + "WordsWeight/wordsWeight.log";
    mapWordsByAuhtor[-1];
    pool.submit(std::bind(&ChallengeProfiles::readAuthorWords, this, namefile, -1));

    if (data == 'A' || data == 'B') {
        for (unsigned int i : authorsList) {
            namefile = path + "WordsWeight/words_" + std::to_string(i) + ".log";
            mapWordsByAuhtor[i];
            pool.submit(std::bind(&ChallengeProfiles::readAuthorWords, this, namefile, i));
        }
    }
    else if (data == 'C') {
        for (unsigned int i = 0; i < 1000; i++) {
            namefile = path + "WordsWeight/words_" + std::to_string(i) + ".log";
            mapWordsByAuhtor[i];
            pool.submit(std::bind(&ChallengeProfiles::readAuthorWords, this, namefile, i));
        }
    }

    pool.wait_for_tasks();

    if (data == 'C') {
        for (unsigned int i = 0; i < 1000; i++) {
            if (mapWordsByAuhtor[i].size() == 0)
                mapWordsByAuhtor.erase(i);
        }
    }

    std::cout << "finished backup, Words Weigth by Author : " << mapWordsByAuhtor.size() << std::endl;
    std::cout << "finished backup, Total Words Weigth : " << mapWordsByAuhtor[-1].size() << std::endl;
}

void ChallengeProfiles::filterReservedWords()
{
    std::cout << "Filter reservedWords !" << std::endl;

    std::string reserved_words;

    if (t == SOCCO) {
        reserved_words = RESERVED_WORDS_CPP;
    }
    else {
        reserved_words = RESERVED_WORDS_C;
    }

    std::ifstream file(reserved_words);
    std::string ligne;

    while (getline(file, ligne))
    {
        for (int i : authorsList) {
            mapWordsByAuhtor[i].erase(ligne);
        }
        mapWordsByAuhtor[-1].erase(ligne);
    }

    std::cout << "End Filter reservedWords" << std::endl;
}

void ChallengeProfiles::loadTestFile(std::string path)
{

    std::cout << "Starting to read -1 file" << std::endl;

    std::ifstream file((path + "test_labels.csv").c_str());
    std::filebuf* pbuf = file.rdbuf();
    std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
    pbuf->pubseekpos(0, file.in);

    char* buffer = new char[size];

    pbuf->sgetn(buffer, size);

    file.close();

    int i = 0;

    std::map< std::string, std::set <std::pair<std::pair<unsigned int, unsigned int>, int>>> mapChunksByFile;

    while (i < size) {
        try {
            std::string tab[4];
            for (int j = 0; j < 4; j++) {
                while (buffer[i] != ',' && buffer[i] != '\n') {
                    tab[j] += buffer[i];
                    i++;
                }
                i++;
            }
            mapChunksByFile[tab[3]].insert(std::make_pair(std::make_pair(stoul(tab[1]), stoul(tab[2])), stoi(tab[0])));
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }

    for (auto& elem : mapChunksByFile) {
        filesUsed.push_back(elem.first);
        chunksByFile.push_back(elem.second);
    }

    delete[] buffer;

    std::cout << "Map FilesByLines finished. Nombre de fichiers cibles par les chunks a trouver : " << filesUsed.size() << std::endl;
}

void ChallengeProfiles::loadResultFile(std::string path)
{
    std::cout << "Starting to read RESULT file" << std::endl;

    std::string namefile;

    if (data == 'A' || data == 'B')
        namefile = path + "test_labels_truth.csv";
    else if (data == 'C')
        namefile = path + "dev.csv";

    std::ifstream file((namefile).c_str());
    std::filebuf* pbuf = file.rdbuf();
    std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
    pbuf->pubseekpos(0, file.in);

    char* buffer = new char[size];

    pbuf->sgetn(buffer, size);

    file.close();

    int i = 0;
    std::string last;
    if (data == 'A' || data == 'B') {
        while (i < size) {
            try {
                std::string tab[4];
                for (int j = 0; j < 4; j++) {
                    while (buffer[i] != ',' && buffer[i] != '\n') {
                        tab[j] += buffer[i];
                        i++;
                    }
                    i++;
                }

                trueAnswers[tab[3] + '-' + tab[1] + '-' + tab[2]] = stoi(tab[0]);

            }
            catch (std::exception e) {
                std::cout << e.what() << std::endl;
                break;
            }
        }
    }
    else if (data == 'C') {
        while (i < size) {
            std::string tab[2];
            try {

                for (int j = 0; j < 2; j++) {
                    while (i < size && buffer[i] != ',' && buffer[i] != '\n') {
                        tab[j] += buffer[i];
                        i++;
                    }
                    i++;
                }

                trueAnswers[tab[1]] = stoi(tab[0]);
                last = tab[1];

            }
            catch (std::exception e) {
                std::cout << last << "\n";
                std::cout << e.what() << std::endl;
                break;
            }
        }
    }

    delete[] buffer;

    std::cout << "Map TrueAnswer finished : " << trueAnswers.size() << std::endl;
}

void ChallengeProfiles::actualizeFilesAssociations(std::string path)
{

    std::cout << "Starting Actualize FilesInfos !" << std::endl;

    int filesByThread = filesUsed.size() / NB_THREAD;

    std::thread t1(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 0, filesByThread, 1);
    std::thread t2(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, filesByThread, 2 * filesByThread, 2);
    std::thread t3(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 2 * filesByThread, 3 * filesByThread, 3);
    std::thread t4(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 3 * filesByThread, 4 * filesByThread, 4);
    std::thread t5(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 4 * filesByThread, 5 * filesByThread, 5);
    std::thread t6(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 5 * filesByThread, 6 * filesByThread, 6);
    std::thread t7(&ChallengeProfiles::actualizeFilesAssociationsThreaded, this, path, 6 * filesByThread, filesUsed.size(), 7);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    std::cout << "End Actualize FilesInfos !" << std::endl;

}
void ChallengeProfiles::answerByFile(std::string path) {

    unsigned int nb_files = filesUsed.size();

    std::cout << "Starting Answer ... " << nb_files << " files used." << std::endl;

    if (chunksAnswer == NULL) { /// Utiliser qu'une structure de données pour comptabiliser
        chunksAnswer = (unsigned int*)malloc(nb_files * sizeof(unsigned int));
    }
    else {
        chunksAnswer = (unsigned int*)realloc(chunksAnswer, nb_files * sizeof(unsigned int));
    }

    if (chunksNoAnswer == NULL) {
        chunksNoAnswer = (unsigned int*)malloc(nb_files * sizeof(unsigned int));
    }
    else {
        chunksNoAnswer = (unsigned int*)realloc(chunksNoAnswer, nb_files * sizeof(unsigned int));
    }

    if (files.size() == 0) {
        for (int i = 0; i < nb_files; i++) {
            files.push_back(nullptr);
            if (ACTIVE_DEBUG)
                weight_debug.push_back({}); // DEBUG
        }
    }

    ThreadPool pool(NB_THREAD);
    pool.setMaxLength(nb_files); //filesUsed.size()

    for (unsigned int i = 0; i < nb_files; i++) // filesUsed.size()
        // answerChunkThreaded(path, i, 0);
        pool.submit(std::bind(&ChallengeProfiles::answerChunkThreaded, this, path, i, 0));

    pool.wait_for_tasks();

}

void ChallengeProfiles::answerByChunk(std::string path, unsigned int it)
{
    unsigned int nb_files = filesUsed.size();

    std::cout << "Starting Answer ... Iteration " << it << " & " << nb_files << " files used." << std::endl;

    if (chunksAnswer == NULL) { /// Utiliser qu'une structure de données pour comptabiliser
        chunksAnswer = (unsigned int*)malloc(nb_files * sizeof(unsigned int));
    }
    else {
        chunksAnswer = (unsigned int*)realloc(chunksAnswer, nb_files * sizeof(unsigned int));
    }

    if (chunksNoAnswer == NULL) {
        chunksNoAnswer = (unsigned int*)malloc(nb_files * sizeof(unsigned int));
    }
    else {
        chunksNoAnswer = (unsigned int*)realloc(chunksNoAnswer, nb_files * sizeof(unsigned int));
    }

    if (files.size() == 0) {
        for (int i = 0; i < nb_files; i++) {
            files.push_back(nullptr);
            if (ACTIVE_DEBUG)
                weight_debug.push_back({}); // DEBUG
        }
    }

    ThreadPool pool(NB_THREAD);
    pool.setMaxLength(nb_files); //filesUsed.size()

    for (unsigned int i = 0; i < nb_files; i++){
        //if(i%100 == 0) std::cout << i << "\n";
        pool.submit(std::bind(&ChallengeProfiles::answerChunkThreaded, this, path, i, it));
        // answerChunkThreaded(path, i, it);
    }

    pool.wait_for_tasks();

    std::cout << "Cleaning Chunks whitch need to be found ! " << std::endl;

    if (chunksByFile.size() != 0)
        chunksByFile.clear();

    nb_answers = 0;
    nb_noAnswers = 0;

    std::vector<File*> temp;
    std::vector<std::string> nextFiles;

    for (unsigned int i = 0; i < nb_files; i++) {

        nb_answers += chunksAnswer[i];
        nb_noAnswers += chunksNoAnswer[i];

        if (files[i] != nullptr) {
            nextFiles.push_back(filesUsed[i]);
            temp.push_back(files[i]);
        }
    }

    filesUsed = nextFiles;
    files = temp;

    std::cout << "End filesUsed for future is cleaned" << std::endl;
}

void ChallengeProfiles::actualizeFilesAssociationsThreaded(std::string path, int indexStart, int indexEnd, int indexThread)
{
    /*Sleep(indexThread * 100);
    std::cout << "Thread " << indexThread << " is starting. = [" << indexStart << " ; " << indexEnd << "[." << std::endl;

    for (int i = indexStart; i < indexEnd; i++) {
        File* f = files[filesUsed[i]];

        if (f == nullptr) {
            f = new File(path + "Codes/", filesUsed[i], mapChunksByFile[filesUsed[i]]);
            f->loadBuffer();
            f->setUpHeader();
            files[filesUsed[i]] = f;
        }

        for (const std::string denom : *(f)->getHeader()->denom) {
            f->setDenomLinks(denom, associationsLinks[denom]);
            f->setDenomWeigth(denom, associationsWeight[denom]);
        }
        f->linkAnonymousDenoms();
        for (std::pair<std::string, std::vector<int>> rep : f->getAnswers()) {
            answers[filesUsed[i] + '-' + rep.first] = rep.second;

        }

        delete f;
    }

    std::cout << "Thread " << indexThread << " is finished." << std::endl;*/
}


void ChallengeProfiles::displayResult(unsigned int it)
{

    std::cout << "DisplayResult" << std::endl;

    float mean = 0;
    std::map<std::string, std::vector<int>> futureAnswers;
    bool good;
    for (const std::pair<std::string, std::vector<int>> result : answers) {
        good = false;
        for (int i = 0; i < result.second.size() && i < ANSWERS_LENGTH; i++) {
            if (trueAnswers[result.first] == result.second[i]) {
                scoring[i]++;
                found++;
                good = true;
                break;
            }
        }
        if (!good) {
            futureAnswers[result.first];
        }
    }


    for (int i = 0; i < ANSWERS_LENGTH; i++) {
        mean += (i + 1) * scoring[i];
    }

    mean += (answers.size() + previousAnswer - found) * 37;
    mean /= answers.size() + previousAnswer;

    std::string path;

    if (data == data_A)
        path = DATA_A + DEBUG_A;
    else if (data == data_B)
        path = DATA_B + DEBUG_B;
    else if (data == data_SOCO_2020)
        path = DATA_SOCO_2020 + DEBUG_SOCO_2020;


    debug.open(path, std::ios_base::app);

    if (debug) {
        debug << "\n-------------------------------------------------------------\n";
        debug << found << " d'occurences trouvees. (" << (float)found / ((float)answers.size() + previousAnswer - nb_noAnswers) * 100.0 << "% sur les " << answers.size() + previousAnswer - nb_noAnswers << " reponses  donnees)." << '\n';

        float pourcentPondere = 0;
        for (int i = 0; i < ANSWERS_LENGTH; i++) {
            float pourcent = (float)scoring[i] / ((float)answers.size() + (float)previousAnswer - (float)nb_noAnswers);
            debug << pourcent * 100.0 << "\n";
            pourcentPondere += pourcent * (ANSWERS_LENGTH - i);
        }

        debug << "Pourcentage pondere : " << pourcentPondere / ANSWERS_LENGTH << "\n";

        debug << '\n';
        debug << "Moyenne de place parmi les trouvees est " << mean << " sur les reponses donnees par rapport a l echantillon." << '\n';
        debug << "TOTAL = " << trueAnswers.size() << " (" << (float)found / (float)trueAnswers.size() * 100.0 << "%)" << '\n';
        debug << "TOTAL DE L ECHANTILLON = " << answers.size() + previousAnswer << " (" << ((float)found / ((float)answers.size() + (float)previousAnswer)) * 100.0 << "% )" << '\n';

        debug << "\n\n";
        debug << "Pour cette iterration : " << it << "\n";
        debug << "Chunks answer : " << nb_answers << "(" << (float)nb_answers / (float)(nb_answers + nb_noAnswers) * 100.0 << " %)\n";
        debug << "Chunks Noanswer : " << nb_noAnswers << "(" << (float)nb_noAnswers / float(nb_answers + nb_noAnswers) * 100.0 << " %)\n";

        debug << "\n";

        if (ACTIVE_DEBUG) {
            for (std::map<std::string, std::vector<std::pair<unsigned int, std::vector<std::pair<float, std::string>>>>> m : weight_debug)
                for (const std::pair<std::string, std::vector<std::pair<unsigned int, std::vector<std::pair<float, std::string>>>>>& p : m) {
                    debug << p.first << "\n";
                    debug << "TA : " << trueAnswers[split(p.first, ":")[0]] << "\n";
                    for (std::pair<unsigned int, std::vector<std::pair<float, std::string>>> pond : p.second) {
                        debug << pond.first << " : ";
                        float f = 0;
                        for (std::pair<float, std::string> ww : pond.second) {
                            debug << ww.second << " (" << ww.first << "); ";
                            f += ww.first;
                        }
                        debug << " TOTAL : " << f << "\n";
                    }
                    debug << "\n\n";
                }

            for (std::map<std::string, std::vector<std::pair<unsigned int, std::vector<std::pair<float, std::string>>>>>& m : weight_debug) {
                m.clear();
            }
        }

        debug.close();
    }
    else{
        std::cout << "ERREUR - ResultFile not opened : " << path << std::endl;
    }

    previousAnswer += answers.size() - futureAnswers.size();
    answers = futureAnswers;

    std::cout << "End Result ! Still in progress !" << std::endl;
}

void ChallengeProfiles::getAuthorsFromFile(std::string path)
{
    std::cout << "Debut de la recuperation des auteurs de la finale." << std::endl;
    std::ifstream file;

    file.open(path + "test_authors.csv");

    std::string line;

    if (file) {
        std::getline(file, line);
        while (file && !line.empty()) {
            authorsList.insert(stoi(line));
            std::getline(file, line);
        }
        file.close();
    }
    else {
        std::cout << path + "test_authors.csv not opened." << std::endl;
    }
    std::cout << "Fin de la recuperation des auteurs." << std::endl;
}




//void ChallengeProfiles::countRepositories(std::string path)
//{
//	std::cout << "Starting count files." << std::endl;
//
//	if (data == data_A)
//		nbFolders = 301;
//	else if (data == data_B)
//		nbFolders = 414;
//
//	numbersFiles = (unsigned int*)malloc(nbFolders * sizeof(unsigned int));
//
//	for (int j = 0; j < nbFolders; j++) { // REMPLACER PAR nbFolders
//
//		std::string folder;
//	
//		folder = "r" + std::to_string(j) + '/';
//
//		unsigned int nb_files = 0;
//
//		for (auto& p : fs::directory_iterator(path + "Codes/" + folder))
//			nb_files++;
//
//		numbersFiles[j] = nb_files;
//	}
//
//	std::cout << "End count files." << std::endl;
//
//}


void ChallengeProfiles::createDenomsStructs(std::string path, std::vector<std::map<int, std::map<std::string, unsigned int>>>& vectorMapWordsByAuhtor, std::vector<std::map<int, Style>>& vectorMapStyleByAuhtor, std::vector<std::map<std::string, std::set<std::string>>>& vectorMapAssociationsLinks, std::vector<std::map<std::string, std::map<int, int>>>& vectorMapAssociationsWeight, int index)
{
    File* f = new File(path, filesUsed[index], chunksByFile[index]);

    //if (filesUsed[index] == "r0/18533"|| filesUsed[index] == "r0/16078"|| filesUsed[index] == "r0/14395"|| filesUsed[index] == "r0/17924"|| filesUsed[index] == "r0/14140" )
    //	std::cout << filesUsed[index] << std::endl;

    f->loadBuffer();
    f->setUpHeader();

    std::map<std::string,std::set<unsigned int>> denominations = f->getHeader()->denom;
    std::map<unsigned int, std::map<std::string, unsigned int>> wordsByAuthor = f->getWordsByAuthor();

    // std::map<unsigned int, Style> styleByAuthor = f->getStyleByAuthor();

    for (std::pair<std::string, std::set<unsigned int>> p : denominations) {
        if (p.second.size() > 0) {
            for (const unsigned int& auth : p.second) {
                vectorMapAssociationsWeight[index][p.first][auth] += 1;
            }
            vectorMapAssociationsLinks[index][p.first].insert(filesUsed[index]);
        }
        //else
        //	vectorMapAssociationsWeight[index][p.first][-2] += 1;
    }

    for (const auto& p : wordsByAuthor) {
        for (const auto& w : p.second) {
            vectorMapWordsByAuhtor[index][p.first][w.first] += w.second;
            vectorMapWordsByAuhtor[index][-1][w.first] += w.second;
        }
    }

    //for (const auto& p : styleByAuthor) {
    //	vectorMapStyleByAuhtor[index][p.first].styleAppend(p.second);
    //}

    //std::cout << f->getNamefile() << std::endl;
    //for (std::pair<unsigned int, Style> p : f->getStyleByAuthor()) {
    //	std::cout << p.first << std::endl;
    //	p.second.displayStyle();
    //	std::cout << "\n";
    //}

    if (f != nullptr) {
        delete(f);
        f = nullptr;
    }
}


void ChallengeProfiles::getDenomResults(std::string path)
{
    std::cout << "Starting build results" << std::endl;
    //std::vector<std::string> authorsDenom[2048];
    //std::map<std::string, std::vector<std::string>> groupsDenom;

    std::string result;

    if (data == data_A)
        result = path + DENOMS_A;
    else if (data == data_B)
        result = path + DENOMS_B;

    std::string const tonFichier(result.substr(0, result.length() - 4) + "_written.log");
    std::ofstream resultFile;
    resultFile.open(tonFichier.c_str());

    for (std::pair<std::string, std::map<int,int>> p : mapAssociationsWeight) {
        //saveFile << p.first << "(" << denominationsAssociations[p.first].first << "):";

        resultFile << p.first; // << ":";

        for (std::string s : mapAssociationsLinks[p.first]) {
            resultFile << "("+ s + "):";
            break;
        }

        for (std::pair<int, int> i : p.second) {
            //saveFile << i << "(" << associationsWeight[p.first][i] << ")" << ",";
            resultFile << i.first << "(" << i.second << ")" << ",";
        }
        //saveFile << "\n";
        resultFile << "\n";

    }

    resultFile.close();

    for (const auto elem : mapWordsByAuhtor) {
        std::string author_words;

        if (elem.first != -1)
            author_words = path + "WordsWeight/words_" + std::to_string(elem.first) + ".log";
        else
            author_words = path + WORDS_WEIGTH;

        resultFile.open(author_words.c_str());
        for (std::pair<std::string, unsigned int> p : mapWordsByAuhtor[elem.first]) {
            resultFile << p.first << ":" << p.second << "\n";
        }

        resultFile.close();
    }

    std::cout << "End build results" << std::endl;
}


void ChallengeProfiles::generateOverallStructs(std::string path)
{
    std::cout << "Starting generate Words weight " << std::endl;
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    std::string base;

    if(data == data_A ||data == data_B)
        base = path + "src/";
    else if (data == data_SOCO_2020)
        base = path + "all/";

    ThreadPool pool(NB_THREAD);
    pool.setMaxLength(filesUsed.size());
    pool.setShowProgress(true);

    std::vector<std::map<int, std::map<std::string, unsigned int>>> vectorMapWordsByAuhtor;
    std::vector<std::map<int, Style>> vectorMapStyleByAuhtor;
    std::vector<std::map<std::string, std::set<std::string>>> vectorMapAssociationsLinks;
    std::vector<std::map<std::string, std::map<int, int>>> vectorMapAssociationsWeight;

    std::map<int, std::map<std::string, unsigned int>>* mapWordsByAuhtor = &this->mapWordsByAuhtor;
    std::map<int, Style>* mapStyleByAuhtor = &this->mapStyleByAuhtor;

    std::map<std::string, std::set<std::string>>* mapAssociationsLinks = &this->mapAssociationsLinks;
    std::map<std::string, std::map<int, int>>* mapAssociationsWeight = &this->mapAssociationsWeight;

    for (int j = 0; j < filesUsed.size(); j++) {
        vectorMapWordsByAuhtor.push_back({});
        // vectorMapStyleByAuhtor.push_back({});
        vectorMapAssociationsLinks.push_back({});
        vectorMapAssociationsWeight.push_back({});
    }

    for (int j = 0; j < filesUsed.size(); j++) {
        pool.submit(std::bind(&ChallengeProfiles::createDenomsStructs, this, base, std::ref(vectorMapWordsByAuhtor), std::ref(vectorMapStyleByAuhtor), std::ref(vectorMapAssociationsLinks), std::ref(vectorMapAssociationsWeight), j));
        // createDenomsStructs( base, vectorMapWordsByAuhtor, vectorMapStyleByAuhtor, vectorMapAssociationsLinks,vectorMapAssociationsWeight, j);
    }

    pool.wait_for_tasks();

    std::cout << "Merging structures..." << std::endl;

    unsigned int size = filesUsed.size();

    int ww = -1;

    pool.resetProgress();

    pool.setMaxLength(2 * authorsList.size() + 1);

    mapWordsByAuhtor[ww];

    for (int auth : authorsList) {
        mapWordsByAuhtor[auth];
        mapStyleByAuhtor[auth];
    }

    // Passer en merge multithread car ca peut être long

    for (int i = 0; i < size; i++) {
        for (const std::pair<std::string, unsigned int>& occ : vectorMapWordsByAuhtor[i][ww])
            (*mapWordsByAuhtor)[ww][occ.first] += occ.second;
    }

    for (int auth : authorsList) {
        for (int i = 0; i < size; i++) {
            for (const std::pair<std::string, unsigned int>& occ : vectorMapWordsByAuhtor[i][auth])
                (*mapWordsByAuhtor)[auth][occ.first] += occ.second;
        }
    }

    for (int i = 0; i < size; i++) {
        for (const std::pair<std::string, std::map<int, int>> &occ: vectorMapAssociationsWeight[i])
            for (const std::pair<int, int> &occ2: occ.second)
                (*mapAssociationsWeight)[occ.first][occ2.first] += occ2.second;

        for (const std::pair<std::string, std::set<std::string>>& occ : vectorMapAssociationsLinks[i])
            for (const std::string& occ2 : occ.second)
                (*mapAssociationsLinks)[occ.first].insert(occ2);

    }

    //pool.submit([mapWordsByAuhtor, &vectorMapWordsByAuhtor, size, ww]() {
    //	for (int i = 0; i < size; i++) {
    //		for (const std::pair<std::string, unsigned int>& occ : vectorMapWordsByAuhtor[i][ww])
    //			(*mapWordsByAuhtor)[ww][occ.first] += occ.second;
    //	}
    //});

    //for (int auth : authorsList) {
    //	pool.submit([mapWordsByAuhtor, &vectorMapWordsByAuhtor, size, auth]() {
    //		for (int i = 0; i < size; i++) {
    //			for (const std::pair<std::string, unsigned int>& occ : vectorMapWordsByAuhtor[i][auth])
    //				(*mapWordsByAuhtor)[auth][occ.first] += occ.second;
    //		}
    //	});
    //}

    //for (int auth : authorsList) {
    //	pool.submit([mapStyleByAuhtor, &vectorMapStyleByAuhtor, size, auth]() {
    //		for (int i = 0; i < size; i++) {
    //			if (vectorMapStyleByAuhtor[i].find(auth) != vectorMapStyleByAuhtor[i].end())
    //				(*mapStyleByAuhtor)[auth].styleAppend(vectorMapStyleByAuhtor[i][auth]);
    //		}
    //	});
    //}


    // pool.wait_for_tasks();

    if (this->mapStyleByAuhtor.size() != 0) {
        std::cout << "\n";
        std::cout << "Style des auteurs : " << std::endl;
        for (std::pair<int, Style> p : this->mapStyleByAuhtor) {
            std::cout << p.first << std::endl;
            p.second.displayStyle();
        }
    }

    std::cout << "\n";
    std::cout << "Nombre d'auteurs concernés : " << this->mapWordsByAuhtor.size() << std::endl;

    filterReservedWords();

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::chrono::duration<double> elapsed = (end - start) / 60;

    std::cout << "elapsed time to getDenominations : " << elapsed.count() << "m\n" << std::endl;

}

void ChallengeProfiles::letsAnalyse()
{
    /*std::ifstream file;
    file.open("../../resultTreatment.txt");

    if (file) {
        std::map<int, std::vector<std::pair<double, std::string>>> denomFrequency;

        std::string ligne;
        while (getline(file, ligne))
        {
            std::vector<std::string> parse = split(ligne, " ");
            int id = stoi(parse[1]);
            int nbTotal = stoi(parse[2].substr(1, parse[2].length() - 1));
            int i = 7;
            while (i < parse.size()) {

                std::string denom;
                bool first = true;

                while (i < parse.size() && (parse[i].size() <= 2 || (parse[i].size() > 2 && (!isNumber(parse[i].substr(1, parse[i].length() - 2)) || !(parse[i][0] == '(' && parse[i][parse[i].length() - 1] == ')'))))) {

                    if (first) {
                        denom += parse[i];
                        first = false;
                    }
                    else
                        denom += " " + parse[i];

                    i++;

                }
                denomFrequency[id].push_back(std::make_pair((double)stoi(parse[i].substr(1, parse[i].length() - 2)) / (double)nbTotal, denom));
                i++;
            }
        }
        file.close();

        std::map<int, std::vector<std::pair<double, std::string>>>::iterator p;
        double seuil = 0.0;

        unsigned int nbFinalAuthors = 0;

        for (p = denomFrequency.begin(); p != denomFrequency.end(); p++) {
            int indexStop;
            boolean found = false;
            for (int i = 0; i < p->second.size(); i++) {
                if (p->second[i].first >= seuil) {
                    indexStop = i;
                    found = true;
                    break;
                }
            }
            if (found) {

                std::vector<int>::iterator it = std::find(authors.begin(), authors.end(), p->first);
                if (!(it == authors.end())) {
                    std::cout << "L'auteur " << p->first << " a pour denominations : ";

                    for (int r = indexStop; r < p->second.size(); r++) {
                        if (p->second[r].first >= seuil) {
                            std::cout << p->second[r].second << " (" << p->second[r].first << ") ";
                        }
                    }
                    std::cout << std::endl;
                    nbFinalAuthors++;
                }
            }
        }
        std::cout << "Nombre d'auteurs compris dans le dataset a trouver : " << nbFinalAuthors << " sur " << authors.size() << std::endl;
    }
    else {
        std::cout << "IMPOSSIBLE D'OUVRIR LE FICHIER\n";
    }*/
}

std::string ChallengeProfiles::ExtractLines(std::string nomFichier, int x, int y) {
    std::string extract = "";

    std::ifstream fichier;
    fichier.open("../../Codes/" + nomFichier + ".c");

    int count = 1; // Pas l'indice mais la n ème ligne

    std::string ligne;
    while (getline(fichier, ligne) && count <= y)
    {
        if (x <= count)
            extract += ligne + '\n';

        count++;
    }
    fichier.close();
    return extract;
}


void ChallengeProfiles::saveLogs() // Tjr fermer le fichier entre les écriture
{

    std::string path;

    // En faire une seule fonction
    if (data == data_A)
        path = DATA_A + LOG_A;
    else if (data == data_B)
        path = DATA_B + LOG_B;
    else if (data == data_SOCO_2020)
        path = DATA_SOCO_2020 + LOG_SOCO_2020;

    std::string const file1(path);
    saveFile.open(file1.c_str());
    if (saveFile) {
        // saveFile << _getpid();
        saveFile << "\n";
        saveFile.close();
    }
    else {
        std::cout << "IMPOSSIBLE D'OUVRIR LE FICHIER DE LOG : " << path << "\n";
    }

    if (data == data_A)
        path = DATA_A + DEBUG_A;
    else if (data == data_B)
        path = DATA_B + DEBUG_B;
    else if (data == data_SOCO_2020)
        path = DATA_SOCO_2020 + DEBUG_SOCO_2020;

    std::string const file2(path);
    debug.open(file2.c_str());
    if (debug) {
        debug.close();
    }
    else {
        std::cout << "IMPOSSIBLE D'OUVRIR LE FICHIER DE DEBUG : " << path << "\n";
    }
}

std::string ExtractLinesByFile(std::string nomFichier, std::vector<int*> lines) {

    std::string extract = "";

    std::ifstream fichier;
    fichier.open("../Codes/" + nomFichier + ".c");

    int count = 1; // Pas l'indice mais la n ème ligne

    std::string ligne;
    while (std::getline(fichier, ligne))
    {
        bool take = false;
        for (int* tab : lines)
            if (tab[0] <= count && count <= tab[1])
                take = true;

        if (take)
            extract += ligne + '\n';

        count++;
    }
    fichier.close();
    return extract;
}




void ChallengeProfiles::filter()
{
    std::cout << "starting filter" << std::endl;

    std::cout << "nombre des mots sur les chunks inconnus : " << mapWordsByAuhtor[0].size() << std::endl;
    std::cout << "nombre d'auteurs : " << mapWordsByAuhtor.size() << std::endl;


    std::map<int, std::map<std::string, unsigned int>> test = mapWordsByAuhtor;
    // std::map<unsigned int, std::map<std::string, unsigned int>> test(mapWordsByAuhtor);


    std::cout << "Nb auteurs dans test : " << test.size() << std::endl;

    mapWordsByAuhtor.clear();

    for (const auto elem : test) {
        for (const auto word : elem.second) {
            if (test[0][word.first] != 0) {
                mapWordsByAuhtor[elem.first][word.first] = word.second;
            }
        }
    }

    for (const auto elem : test) {
        std::cout << "test - author " << elem.first << " - size " << elem.second.size() << std::endl;
        std::cout << "mapAuthor - size " << mapWordsByAuhtor[elem.first].size() << std::endl;
        std::cout << std::endl;
    }
}

void ChallengeProfiles::debugChunk(std::string path)
{
    if (files.size() == 0) {
        for (int i = 0; i < filesUsed.size(); i++) {
            files.push_back(nullptr);
            debugChunkVec.push_back("");
        }
    }

    ThreadPool pool(NB_THREAD);
    pool.setMaxLength(filesUsed.size()); //filesUsed.size()

    for (unsigned int i = 0; i < filesUsed.size(); i++) // filesUsed.size()
        pool.submit(std::bind(&ChallengeProfiles::debugChunkThreaded, this, path, i));

    pool.wait_for_tasks();

    std::ofstream outputFile(path + "chunksUnknow.txt");
    if (outputFile) {
        for (int i = 0; i < debugChunkVec.size(); i++) {
            outputFile << debugChunkVec[i] << "\n";
            outputFile << "^^**---------------------------**^^\n";
        }
    }
}

void ChallengeProfiles::debugChunkThreaded(std::string path, unsigned int index)
{
    File* f = files[index];

    if (f == nullptr) {
        f = new File(path + "Codes/", filesUsed[index], chunksByFile[index]);
        f->loadBuffer();
        files[index] = f;

        if (chunksByFile.size() != 0)
            chunksByFile[index].clear();
    }

    for (const std::pair<std::pair<unsigned int, unsigned>, Chunk*>& chunk : f->getChunksUnknow()) {
        std::string buffer = chunk.second->realBuffer;
        debugChunkVec[index] = filesUsed[index] + '-' + std::to_string(chunk.first.first) + '-' + std::to_string(chunk.first.second) + '\n' + buffer;
    }

    if (f != nullptr)
        delete f;
}

void ChallengeProfiles::FillDatabase()
{
    std::cout << "Starting Fill database" << std::endl;

    std::string request;
    std::string inter;

    request = "INSERT INTO Chunk (id_file,lineBegin,lineEnd,buffer,author) VALUES ";
    unsigned int count = 0;
    for (int i = 0; i < filesUsed.size(); i++) {
        for (const auto& elem : chunksByFile[i]) {
            if ((count != 0 && count % 999 == 0) || count == filesUsed.size() - 1) {
                inter += "('" + std::to_string(i) + "', '" + std::to_string(elem.first.first) + "', '" + std::to_string(elem.first.second) + "', NULL, '" + std::to_string(elem.second) + "')";
                database->getStatement()->execute(request + inter);
                database->conn->commit();
                inter = "";
                count = 0;
            }
            else {
                inter += "('" + std::to_string(i) + "', '" + std::to_string(elem.first.first) + "', '" + std::to_string(elem.first.second) + "', NULL, '" + std::to_string(elem.second) + "'), ";
                count++;
            }
        }
    }

    std::cout << "End build database" << std::endl;
}

void ChallengeProfiles::discoverDataset(std::string basePath)
{
    std::cout << "Starting discover dataset" << std::endl;
    unsigned int id = 0;
    std::string path = basePath + "src/";
    for (const auto& entry : fs::directory_iterator(path)) {
        for (const auto& entry2 : fs::directory_iterator(entry.path().string())){
            std::string filename = entry.path().filename().string() + "/" + entry2.path().filename().string();
            fileId[filename] = id;
            id++;
        }
    }

    std::string baseRequest = "INSERT INTO File (id,nom,nb_lignes) VALUES ";
    std::string inter;

    unsigned int i = 0;
    for (std::pair<std::string,unsigned int> p : fileId) {
        if ((i != 0 && i % 999 == 0) || i == fileId.size() - 1) {
            inter += "('" + std::to_string(p.second) + "', '" + p.first + "', NULL);";
            std::string request = baseRequest + inter;
            database->getStatement()->execute(request);
            database->conn->commit();
            inter = "";
        }
        else {
            inter += "('" + std::to_string(p.second) + "', '" + p.first + "', NULL), ";
        }
        i++;
    }

    std::cout << "End discover dataset" << std::endl;
}


void ChallengeProfiles::answerChunkThreaded(std::string path, int index, unsigned int it)
{
    try {

        File* f = files[index];

        if (f == nullptr) {

            std::string nf;
            if (data == 'A' || data == 'B')
                nf = path + "src/";
            else if (data == 'C')
                nf = path + "all/";

            f = new File(nf, filesUsed[index], chunksByFile[index]);

            f->loadBuffer();
            files[index] = f;

            if (chunksByFile.size() != 0)
                chunksByFile[index].clear();
        }

        if (data == 'A' || data == 'B') {
            if (it != 0)
                f->appendChunksBuffer(it);
        }

        chunksAnswer[index] = 0;
        chunksNoAnswer[index] = 0;

        std::vector<std::string> chunksA;

        for (const std::pair<std::pair<unsigned int, unsigned>, Chunk*> chunk : f->getChunksUnknow()) {

            std::string buf = chunk.second->getBuffer();

            std::map<unsigned int, std::map<std::string, float>> answerByAuthorDebug;
            std::map<unsigned int, float> answerByAuthor;
            std::map<unsigned int, unsigned int> wordCount;

            std::string key;

            if (t == SOCCO)
                key = filesUsed[index];
            else
                key = filesUsed[index] + '-' + File::getKeyChunkByLines(chunk.second->getLines());

            for (const std::pair<std::string, unsigned int>& p : chunk.second->getWords()) {

                std::string w = p.first;

                for (const int& auth : authorsList) {

                    float valueAuthor, valueAll;

                    if(mapWordsByAuhtor[auth].find(w) == mapWordsByAuhtor[auth].end()){
                        valueAuthor = 0.0;

                        if(mapWordsByAuhtor[-1].find(w) == mapWordsByAuhtor[-1].end())
                            valueAll = 0.0;
                    }
                    else{
                        valueAuthor = mapWordsByAuhtor[auth][w];
                        valueAll = mapWordsByAuhtor[-1][w];
                    }

                    if ( mapWordsByAuhtor[auth][w] != 0) {
                        float weight = (valueAuthor / valueAll) / ((float)mapWordsByAuhtor[auth].size() / (float)mapWordsByAuhtor[-1].size());
                        //float weight = ((float)mapWordsByAuhtor[auth][w] / (float)mapWordsByAuhtor[-1][w]) * (((float)mapWordsByAuhtor[auth][TOTAL_WORD_USED] / (float)mapWordsByAuhtor[-1][TOTAL_WORD_USED]) / ((float)mapWordsByAuhtor[auth].size() / (float)mapWordsByAuhtor[-1].size()));
                        answerByAuthor[auth] += weight;
                        // answerByAuthorDebug[auth][w] = weight;
                        if (wordCount.find(auth) == wordCount.end()) {
                            wordCount[auth] = 1;
                        }
                        else
                            wordCount[auth]++;
                    }
                }
            }

            std::map<unsigned int, std::vector<unsigned int>, std::greater<unsigned int>> countDiff;

            for (const std::pair<unsigned int, unsigned int>& p : wordCount) {
                countDiff[p.second].push_back(p.first);
            }

            bool present = false;

            for (const std::pair<unsigned int, std::vector<unsigned int>>& p : countDiff) {
                std::set<std::pair<float, unsigned int>, std::greater<std::pair<float, unsigned int>>> answersSort;

                for (const int & auth : p.second) {
                    answersSort.insert(std::make_pair(answerByAuthor[auth], auth));
                }

                for (const std::pair<float, unsigned int>& an : answersSort) {
                    answers[key].push_back(an.second);
                }

                if (ACTIVE_DEBUG) {
                    if (answers[key][0] != trueAnswers[key]) {

                        std::vector<std::pair<float, std::string>> vec;
                        for (const std::pair<float, unsigned int>& an : answersSort) {
                            vec.clear();
                            if (an.second == trueAnswers[key])
                                present = true;

                            for (const std::pair<std::string, float>& p : answerByAuthorDebug[an.second]) {
                                vec.push_back(std::make_pair(p.second, p.first));
                            }
                            if (weight_debug[index][key + ':' + buf].size() < 10)
                                weight_debug[index][key + ':' + buf].push_back(std::make_pair(an.second, vec));
                            else
                                break;
                        }
                    }
                }
            }

            std::vector<std::pair<float, std::string>> vec;
            if (!present && ACTIVE_DEBUG) {
                vec.clear();
                for (const std::pair<std::string, float>& p : answerByAuthorDebug[trueAnswers[key]]) {
                    vec.push_back(std::make_pair(p.second, p.first));
                }
                weight_debug[index][key + ':' + buf].push_back(std::make_pair(trueAnswers[key], vec));
            }

            if (countDiff.size() != 0) {
                chunksAnswer[index]++;
                chunksA.push_back(File::getKeyChunkByLines(chunk.second->getLines()));
            }
            else {
                chunksNoAnswer[index]++;
            }
        }

        for (const std::string& s : chunksA) {
            f->removeChunkUnknow(s);
        }

        if (f->getChunksUnknow().size() == 0) {
            delete f;
            files[index] = nullptr;
        }

    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

void ChallengeProfiles::insertThread(SoplonDatabase* db, unsigned int index)
{
    unsigned int base = 10000;
    std::string request = "INSERT INTO file (nom)  VALUES";
    std::string inter = "";
    for (unsigned int i = 0 + base * index; i < base+index*base; i++) {

        inter = request + "(" + std::to_string(i) + ")";

        db->getStatement()->execute(inter);
        db->conn->commit();
    }
}





/*
DEBUG WORD WEIGTH CODE
                    //for (std::pair<std::string, float> p : answerByAuthorDebug[an.second])
                    //	answersWordSort[an.second].insert(std::make_pair(p.second, p.first));

                    //std::vector<std::pair<float, std::string>> v;

                    //switch (indexThread) { // éviter autant de test
                    //case 1:
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].first = buf; // Séparer en clef le buffer et la référence de chunk
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;

                    //	break;
                    //case 2:
                    //	tfidf_debug2[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //case 3:
                    //	tfidf_debug3[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //case 4:
                    //	tfidf_debug4[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //case 5:
                    //	tfidf_debug5[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //case 6:
                    //	tfidf_debug6[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //case 7:
                    //	tfidf_debug7[filesUsed[i] + '-' + chunks.first].first = buf;
                    //	v.assign(answersWordSort[an.second].begin(), answersWordSort[an.second].end());
                    //	tfidf_debug1[filesUsed[i] + '-' + chunks.first].second[an.second] = v;
                    //	break;
                    //default:
                    //	break;
                    //}

                    //if (trueAnswers[filesUsed[i] + '-' + chunks.first] == an.second) // Raccourcir le temps de débuggage
                    //	break;


*/



// THREADING

/*std::vector<std::thread> threads;

    if(it == 0 && filesUsed.size() >= NB_THREAD) {

        ReadFileSize(path);

        uint64_t filesByThread = totalSize / NB_THREAD;
        uint64_t count = 0;
        int indexFile = 0;
        int indexThread = 1;

        while (indexThread < NB_THREAD) {
            int start = indexFile;
            for (indexFile; indexFile < filesUsed.size(); indexFile++) {
                count += filesSize[indexFile];
                if (count > indexThread * filesByThread) {
                    break;
                }
            }
            threads.push_back(std::thread(&ChallengeProfiles::answerChunkThreaded, this, path, start, indexFile + 1, indexThread, it));
            indexThread++;
        }

        threads.push_back(std::thread(&ChallengeProfiles::answerChunkThreaded, this, path, indexFile + 1, filesUsed.size(), NB_THREAD, it));

        for (std::thread& t : threads)
            t.join();

        free(filesSize);

    }
    else if (it > 0 && filesUsed.size() >= NB_THREAD) {

        int filesByThread = filesUsed.size() / NB_THREAD;

        for (int i = 0; i < NB_THREAD-1; i++) {
            threads.push_back(std::thread(&ChallengeProfiles::answerChunkThreaded, this, path, i* filesByThread, (i + 1) * filesByThread, i+1, it));
        }

        threads.push_back(std::thread(&ChallengeProfiles::answerChunkThreaded, this, path, (NB_THREAD - 1) * filesByThread, filesUsed.size(), NB_THREAD, it));

        for (std::thread& t : threads)
            t.join();
    }
    else {

        for (int i = 0; i < filesUsed.size(); i++) {
            threads.push_back(std::thread(&ChallengeProfiles::answerChunkThreaded, this, path, i , i + 1, i + 1, it));
        }

        for (std::thread& t : threads)
            t.join();
    }*/
