#include "File.h"

std::string File::getKeyChunkByLines(unsigned int first, unsigned int second) {
	return std::to_string(first) + '-' + std::to_string(second);
}

std::string File::getKeyChunkByLines(std::pair<unsigned int, unsigned int> p) {
	return std::to_string(p.first) + '-' + std::to_string(p.second);
}

std::pair<unsigned int, unsigned int> File::getLinesChunkByKey(std::string key) {
	std::vector<std::string> lines = split(key, "-");
	return std::make_pair(stoul(lines[0]), stoul(lines[1]));
}


File::File(std::string path, std::string namefile)
{
	this->path = path;
	this->namefile = namefile;
	this->header = new Header();
}

File::File(std::string path, std::string namefile, std::set<std::pair<std::pair<unsigned int, unsigned int>, int>> chunks)
{
	this->path = path;
	this->namefile = namefile;
	this->header = new Header();

	for (const std::pair<std::pair<unsigned int, unsigned int>, int>& elem : chunks) {
		linesSet.insert(std::make_pair(elem.first.first, elem.first.second));
		this->chunks[getKeyChunkByLines(elem.first.first, elem.first.second)] = elem.second;
	}
}


File::~File()
{
	for (std::pair<std::pair<unsigned int, unsigned int>, Chunk*> p : chunksKnown)
		if (p.second != nullptr)
			delete p.second;

	for (std::pair<std::pair<unsigned int, unsigned int>, Chunk*> p : chunksUnKnown)
		if (p.second != nullptr)
			delete p.second;

	chunksUnKnown.clear();
	chunksKnown.clear();

	linesSet.clear();
	buffer.clear();
	chunks.clear();
	wordsByAuthor.clear();

	if (header != nullptr)
		delete header;
}

std::string File::getNamefile()
{
	return namefile;
}

void File::setUpHeader() {
	header->parseHeader2();
	header->freeMemories();
}

Header* File::getHeader() {
	return header;
}

std::map<std::pair<unsigned int, unsigned int>, Chunk*> File::getChunksUnknow()
{
	return chunksUnKnown;
}


void File::removeChunkUnknow(std::string cu)
{
	delete chunksUnKnown[getLinesChunkByKey(cu)];
	chunksUnKnown.erase(getLinesChunkByKey(cu));
}

void File::loadBuffer()
{
	fichier.open(path + namefile + ".c"); //
	
	if (fichier)
	{
		if (linesSet.size() != 0)
			FileToChunks();
		else
			FileToBuffer();

		fichier.close();
	}
	else
	{
		std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture : " << path +  namefile << std::endl;
	}
}

void File::linkAnonymousDenoms()
{
	/*for (std::pair<std::pair<unsigned int, unsigned int>, Chunk*> c : chunksUnKnown) {
		std::map<int, int> count;
		std::set<std::pair<int, int>, std::greater<std::pair<int, int>>> weightSort;
		std::vector<int> res;
		for (std::string s : *(header)->denom) {
			if (c.second->getBuffer().find(s) != 0xffffffffffffffff) {
				for (std::pair<int, int> p : associationsWeight[s]) {
					count[p.first] += p.second;
				}
			}
		}
		for (std::map<int, int>::iterator it = count.begin(); it != count.end(); ++it) {
			weightSort.insert(std::make_pair(it->second, it->first));
		}

		for (const std::pair<int, int> p : weightSort) {
			res.push_back(p.second);
		}

		if (res.size() != 0)
			answers[getKeyChunkByLines(c.first)] = res;
	}*/
}

std::set<int> File::getDenomLinks(std::string s)
{
	return AssociationsLinked[s];
}

int File::getDenomWeigth(std::string s, int author)
{
	return associationsWeight[s][author];
}

void File::setDenomLinks(std::string s, std::set<int> list)
{
	AssociationsLinked[s] = list;
}

void File::setDenomWeigth(std::string s, std::map<int, int> m)
{
	associationsWeight[s] = m;
}

void File::freeMemories()
{
	buffer.clear();

	for (std::pair<std::pair<unsigned int, unsigned int>, Chunk*> c : chunksKnown)
		c.second->freeMemories();

	delete header;

	linesSet.clear();

	chunks.clear();

	wordsByAuthor.clear();

	styleByAuthor.clear();

	// association clear ?
}


std::vector<std::string> File::getBuffer()
{
	return buffer;
}

std::map<std::string, std::vector<int>> File::getAnswers()
{
	return answers;
}

std::map<unsigned int, std::map<std::string, unsigned int>> File::getWordsByAuthor()
{
	return wordsByAuthor;
}

std::map<unsigned int, Style> File::getStyleByAuthor()
{
	return styleByAuthor;
}

void File::appendChunksBuffer(unsigned int it)
{

	std::string extraBuffer;

	for (std::pair<std::pair<unsigned int, unsigned int>, Chunk*> c : chunksUnKnown) {

		int begin = (int)c.second->getLineBegin();
		int end = (int)c.second->getLineEnd();

		if (begin - 1 - (int)it >= 0)
			extraBuffer = buffer[begin - 1 - (int)it] + '\n';
		if (end - 1 + it < buffer.size())
			extraBuffer += buffer[end - 1 + (int)it] + '\n';

		c.second->appendBuffer(extraBuffer);
	}
}


bool File::isCommentLine(std::string s) {
	while (s[0] == '/t' || s[0] == ' ') {
		s = s.substr(1);
	}
	return ((s[0] == '/' && s[1] == '/'));
}

bool File::isCommentBlockB(std::string s) { // Debut bloc commentaire
	while (s[0] == '/t' || s[0] == ' ') {
		s = s.substr(1);
	}
	return ((s[0] == '/' && s[1] == '*'));
}

bool File::isCommentBlockE(std::string s) { // Fin bloc commentaire

	while (s.size() > 1 && !(s[0] == '*' && s[1] == '/')) {
		s = s.substr(1);
	}

	return ((s[0] == '*' && s[1] == '/'));
}

void File::FileToChunks() {

	std::string headerComments = "";
	std::vector<std::string> headerCommentsVector;

	bool isComments = false;
	bool begin = false;

	bool first = true;

	bool isCL;
	bool isCBB;
	bool isCBE;

	std::string ligne;
	int index = 0;

	while (getline(fichier, ligne)) {
		buffer.push_back(ligne);

		isCL = isCommentLine(ligne);
		isCBB = isCommentBlockB(ligne);
		isCBE = isCommentBlockE(ligne);

		if (ligne.size() > 0 && first && (isCL || isCBB || isComments)) {

			headerComments += ligne + '\n';
			headerCommentsVector.push_back(ligne);
			
			if (!begin) {
				begin = true;
				header->setHeaderBegin(index);
			}

			if (isCBE) {
				isComments = false;
			}
			else if (isCBB)
				isComments = true;

			index++;
		}
		else {
			if (first){
				first = false;
				header->setHeaderEnd(index);
				// break; // Traiter juste les header
			}
		}
	}

	header->setHeader(headerComments);
	header->setHeaderVector(headerCommentsVector);

	std::vector<std::pair<std::pair<unsigned int, unsigned int>, int>> headerLines;
	if (linesSet.size() > 0) {
		for (const std::pair<unsigned int, unsigned int>& lines : linesSet) {
			std::string chunk;

			if (lines.first == 0 && lines.second == 0) {
				for (int i = 0; i < buffer.size(); i++) {
					chunk += buffer[i] + '\n';
				}
			}
			else {
				for (int i = lines.first - 1; i < lines.second; i++) {
					if (i < buffer.size())
						chunk += buffer[i] + "\n";
				}
			}

			std::string key = getKeyChunkByLines(lines.first, lines.second);
			int author = chunks[key];

			if (chunks[key] == -1) {
				chunksUnKnown[std::make_pair(lines.first, lines.second)] = new Chunk(buffer, chunk, lines.first, lines.second, author);
			}
			else {
				Chunk* c = new Chunk(buffer, chunk, lines.first, lines.second, author);
				chunksKnown[std::make_pair(lines.first, lines.second)] = c;
				std::map<std::string, unsigned int> temp = c->getWords();
				for (const auto& elem : temp) {
					wordsByAuthor[author][elem.first] += elem.second;
				}

				if (lines.first < header->getHeaderBegin() && lines.second > header->getHeaderEnd()) {
					headerLines.push_back(std::make_pair(std::make_pair(header->getHeaderBegin(), header->getHeaderEnd()), author));
				}
				else if (lines.first < header->getHeaderBegin() && lines.second <= header->getHeaderEnd()) {
					headerLines.push_back(std::make_pair(std::make_pair(header->getHeaderBegin(), lines.second), author));
				}
				else if (lines.first >= header->getHeaderBegin() && lines.second <= header->getHeaderEnd()) {
					headerLines.push_back(std::make_pair(std::make_pair(lines.first, lines.second), author));
				}
				else if (lines.first >= header->getHeaderBegin() && lines.first <= header->getHeaderEnd() && lines.second > header->getHeaderEnd()) {
					headerLines.push_back(std::make_pair(std::make_pair(lines.first, header->getHeaderEnd()), author));
				}

				// styleByAuthor[author].styleAppend( c->getStyle());
			}
		}
	}

	header->setAuthorsLines(headerLines);
}

void File::FileToBuffer()
{
	std::string headerComments = "";

	bool isComments = false;

	bool isCL;
	bool isCBB;
	bool isCBE;

	std::string ligne;
	while (getline(fichier, ligne)) {
		buffer.push_back(ligne);

		isCL = isCommentLine(ligne);
		isCBB = isCommentBlockB(ligne);
		isCBE = isCommentBlockE(ligne);

		if (ligne.size() > 0 && (isCL || isCBB || isComments)) {

			headerComments += ligne + '\n';

			if (isCBE) {
				isComments = false;
			}
			else if (isCBB)
				isComments = true;

		}
		else {
			break;
		}
	}
	header->setHeader(headerComments);
}


void File::SaveResult()
{
	/* // Il faut creer le repertoire si pas fait - FAIRE ATTENTION AVEC la var fichier de la classe

	vector<string> parse = split(namefile, "/");
	string name;
	int a = 1;
	if (parse.at(0) == "..")
		a = 2;

	for (int i = a; i < parse.size(); i++) {
		name += parse.at(i);
	}

	ofstream fichier;
	// string const tonFichier(PATH + name + ".log");
	string const tonFichier(PATH + "header" + ".log");
	fichier.open(tonFichier.c_str(), ios::app);

	if (fichier) {

		/*     for (int i = 0; i < NBPARAMFUNCTIONS; i++) {
				 fichier << countFunctions[i];
				 if(i != NBPARAMFUNCTIONS -1 ) fichier << "-";
			 }
			 fichier << "\n";

			 for (int i = 0; i < NBPARAMPERCENTS; i++) {
				 fichier << commentsPercentages[i];
				 if (i != NBPARAMPERCENTS - 1) fichier << "-";
			 }
			 fichier << "\n\n";
		result += header->getHeader() + '\n';
		result += "COPYRIGHT : " + header->copyright + '\n';
		result += "AUTHOR : " + header->author + '\n';
		result += '\n' + "**********************************************";
		fichier << result;
	}
	else {
		cout << "IMPOSSIBLE D'OUVRIR LE FICHIER RESULTAT \n";
	}
	fichier.close();
	*/
}

void File::DisplayInfos() {

	//std::string res;

	//nbFunctions = func.size();
	//nbCommentedFunctions = 0;
	//nbFunctionWithHeader = 0;

	//for (int i = 0; i < nbFunctions; i++) { // Peut etre for auto
	//	//cout << func.at(i)->getCode() << endl;
	//	//cout << "FIN FONCTION" << endl;
	//	res = "Function " + std::to_string(i + 1);
	//	res += " : Le pourcentage de commentaires est de " + to_string(func.at(i)->getCommentsPercentages()) + " %." + '\n';
	//	//cout << res;
	//}
	//std::cout << endl;

	//countFunctions[NBFUNCTIONS] = nbFunctions;

	//res = '\n' + std::to_string(nbFunctions) + " fonction(s) ont ete trouvees.\n";
	//std::cout << res;
	//result += res;

	//for (int i = 0; i < nbFunctions; i++) {
	//	float per = func.at(i)->getCommentsPercentages();

	//	if (per != 0.00) {
	//		nbCommentedFunctions++;
	//		mean += per;
	//	}

	//	std::string s;
	//	if (func.at(i)->getWithHeader()) {
	//		s = "avec";
	//		nbFunctionWithHeader++;
	//	}
	//	else
	//		s = "sans";

	//	res = "Fonction " + std::to_string(i + 1) + " " + s + " header (" + to_string(func.at(i)->getNbLineHeader()) + ") : " + to_string(per) + " % de commentaires - " + deleteChar(deleteChar(func.at(i)->getPrototype(), '\n'), '\t') + "\n";

	//	std::cout << res;
	//	result += res;
	//}

	//std::cout << endl;
	//std::cout << macros.size() << " macros trouvees" << endl;

	//for (int i = 0; i < macros.size(); i++) {
	//	res = "Macro " + std::to_string(i + 1) + " : " + macros.at(i)->getName();
	//	std::cout << res << endl;
	//	result += res;
	//}

	//std::cout << endl;
	//cout << structs.size() << " structures trouvees" << endl;

	//for (int i = 0; i < structs.size(); i++) {
	//	res = "Struct " + to_string(i + 1) + " : " + structs.at(i)->getName();
	//	cout << res << endl;
	//	result += res;
	//}

	//countFunctions[NBCOMMENTFUNC] = nbCommentedFunctions;
	//countFunctions[NBFUNCWITHHEADER] = nbFunctionWithHeader;

	//mean /= nbCommentedFunctions;

	//commentsPercentages[MEAN] = mean;

	//for (int i = 0; i < nbFunctions; i++) {

	//	if (func.at(i)->getCommentsPercentages() != 0.00)
	//		standardDeviation += pow(abs(func.at(i)->getCommentsPercentages() - mean), 2) / nbCommentedFunctions;
	//}

	//standardDeviation = sqrt(standardDeviation);

	//commentsPercentages[STANDARDDEVIATION] = standardDeviation;


	//float min1s, max1s, min2s, max2s;

	//min1s = mean - standardDeviation;
	//max1s = mean + standardDeviation;
	//min2s = mean - 2 * standardDeviation;
	//max2s = mean + 2 * standardDeviation;

	//int nb1Sigma = 0;
	//int nb2Sigma = 0;

	//for (int i = 0; i < nbFunctions; i++) {
	//	if (func.at(i)->getCommentsPercentages() != 0.00) {
	//		if (min1s <= func.at(i)->getCommentsPercentages() && func.at(i)->getCommentsPercentages() <= max1s)
	//			nb1Sigma++;
	//		if (min2s <= func.at(i)->getCommentsPercentages() && func.at(i)->getCommentsPercentages() <= max2s)
	//			nb2Sigma++;
	//	}
	//}

	//res = "\nMoyenne de commentaires par fonction commentee = " + to_string(mean) + "% et ecart type = " + to_string(standardDeviation) + "%\n";
	//cout << res;
	//result += res;
	//res = "Intervalle de confiance [" + to_string(min1s) + ";" + to_string(max1s) + "] a 1*ec : " + to_string(((float)nb1Sigma / (float)nbCommentedFunctions) * 100.0) + "% des fonctions.\n";
	//cout << res;
	//result += res;
	//res = "Intervalle de confiance [" + to_string(min2s) + ";" + to_string(max2s) + "] a 2*ec : " + to_string(((float)nb2Sigma / (float)nbCommentedFunctions) * 100.0) + "% des fonctions.\n";
	//cout << res;
	//result += res;

	//PercentagesFunctionCommented = ((float)nbCommentedFunctions / (float)nbFunctions) * 100.0;
	//commentsPercentages[PERCENTFUNCCOMMENT] = PercentagesFunctionCommented;
	//res = "Pourcentages de fonctions commentes = " + to_string(PercentagesFunctionCommented) + " %.\n";
	//cout << res;
	//result += res;
	//PercentagesFunctionWithHeader = ((float)nbFunctionWithHeader / (float)nbFunctions) * 100.0;
	//commentsPercentages[PERCENTFUNCWITHHEADER] = PercentagesFunctionWithHeader;
	//res = "Pourcentages de fonctions avec header de commentaires = " + to_string(PercentagesFunctionWithHeader) + " %.\n";
	//cout << res;
	//result += res;

	//if (header->getWithHeader() > 0) {
	//	res = "Commentaire en tete de fichier trouve : " + to_string(header->getNbChars()) + " caracteres.\n";
	//	cout << res << endl;;
	//	result += res;
	//	cout << header->getHeader() << endl;
	//}
	//else {
	//	res = "Pas de commentaire d'en tete de fichier trouve.\n";
	//	cout << res << endl;
	//	result += res;
	//}

	// SaveResult();
}