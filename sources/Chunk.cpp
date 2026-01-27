#include "Chunk.h"

/*
*  Return 0 for no structure, 1 for if, 2 for for, 3 for while
*/
int getControlStructure(const std::string s) {
	unsigned int pos = 0;
	while (pos < s.size() && (s[pos] == ' ' || s[pos] == '\t'))
		pos++;
	if (pos + 5 < s.size() && s[pos] == 'w' && s[pos+1] == 'h' && s[pos + 2] == 'i' && s[pos + 3] == 'l' && s[pos + 4] == 'e' && (s[pos+5] == ' ' || s[pos+5] == '(')) {
		return 3;
	}
	else if (pos + 3 < s.size() && s[pos] == 'f' && s[pos + 1] == 'o' && s[pos + 2] == 'r' && (s[pos + 3] == ' ' || s[pos + 3] == '(')) {
		return 2;
	}
	else if (pos + 2 < s.size() && s[pos] == 'i' && s[pos + 1] == 'f' && (s[pos + 2] == ' ' || s[pos + 2] == '(')) {
		return 1;
	}
	else {
		return 0;
	}
}

Chunk::Chunk(std::vector<std::string> & fileBuffer, std::string buffer, unsigned int begin, unsigned int end, int author) { // Verifier la complexite

	this->realBuffer = buffer;
	this->buffer = buffer;
	this->begin = begin;
	this->end = end;
	this->author = author;
	
	for (auto& c : this->buffer) // Il y a des \n non remplacés - '.'
		if (specialChar.find(c) != specialChar.end() || c < 0 ||c > 254) // ->
			c = ' ';

	this->buffer = replaceWord(this->buffer, "->", " ");// !
	this->buffer = replaceWord(this->buffer, "\n", " "); // Etrange que tous les \n pas traité avant
	this->buffer = replaceWord(this->buffer, "\t", " ");

	std::vector<std::string> words = split(this->buffer, " ");

	for (std::string & s : words) {

		while (s.size() > 0 && (!iswalpha(s[0]) && !iswdigit(s[0])/* && s[0] != '_'*/))
			s = s.substr(1);

		while (s.size() > 0 && (!iswalpha(s[s.length()-1]) && !iswdigit(s[s.length() - 1])))
			s = s.substr(0, s.length() - 1);
		
		if (s.size() > 2) { 		
			if(!iswdigit(s[0]) && /*((s[0] > 64 && s[0] < 91) || (s[0] > 96 && s[0] < 123))*/ (s[0] >=0  && s[0] <= 254))
				this->words[s]++;
		}
	}
	
	// vérifier les pos + x < realBuffer , sans doute inutile autant

	// std::cout << begin << ";" << end << std::endl;	
//	std::cout << author << std::endl;
// 	std::cout << realBuffer << std::endl;

	//if (begin == 3817 && end == 3820)
	//	std::cout << "here" << std::endl;

	//if (begin == 637 && end == 638)
	//	std::cout << "here" << std::endl;

	//int pos = 0;
	//while (pos < realBuffer.size()) {
	//	if (pos + 2 < realBuffer.size() && realBuffer[pos] == '/' && realBuffer[pos + 1] == '/') {
	//		pos = pos + 2;
	//		while (pos < realBuffer.size() && realBuffer[pos] != '\n'  ) {
	//			pos++;
	//		}
	//	}
	//	else if (pos + 2 < realBuffer.size() && realBuffer[pos] == '/' && realBuffer[pos + 1] == '*') {
	//		pos = pos + 2;
	//		while (pos < realBuffer.size() && !(realBuffer[pos] == '*' && realBuffer[pos + 1] == '/')) {
	//			pos++;
	//		}
	//		pos++;
	//	}
	//	else if (realBuffer[pos] == '"') {
	//		pos++;
	//		while (pos < realBuffer.size() && !(realBuffer[pos] == '"' && realBuffer[pos-1] != '\\')) {
	//			pos++;
	//		}
	//	}
	//	else if ((pos == 0 || realBuffer[pos -1] == '\n') && realBuffer[pos] == '#') {
	//		pos++;
	//		chunkStyle.macro_s.nb++;
	//		while (pos +1 < realBuffer.size() && realBuffer[pos] != '\n') {
	//			if (realBuffer[pos] == '(' && realBuffer[pos + 1] == ' ') {
	//				chunkStyle.macro_s.space_after_parenth++;
	//			}
	//			else if (realBuffer[pos] == ')' && pos -1 >= 0 && realBuffer[pos - 1] == ' ') {
	//				chunkStyle.macro_s.space_before_parenth++;
	//			}
	//			else if (realBuffer[pos] == ',') {
	//				if (pos - 1 >= 0 && realBuffer[pos - 1] == ' ')
	//					chunkStyle.macro_s.space_before_virgule++;
	//				if (pos + 1  < realBuffer.size() && realBuffer[pos + 1] == ' ')
	//					chunkStyle.macro_s.space_after_virgule++;
	//			}

	//			pos++;
	//		}
	//	}
	//	else if (realBuffer[pos] == 'f' && ((pos - 1 >= 0 && (realBuffer[pos-1] == ' ' || realBuffer[pos-1] == '\n' || realBuffer[pos-1] == '\t')) || pos == 0 ) && pos + 4 < realBuffer.size() && realBuffer[pos+1] == 'o' && realBuffer[pos+2] == 'r' && (realBuffer[pos + 3] == '(' || (realBuffer[pos + 4] == '(' && (realBuffer[pos + 3] == ' ' || realBuffer[pos + 3] == '\t')))) {
	//		pos = pos + 3;
	//		chunkStyle.for_s.nb++;
	//		while (pos < realBuffer.size() && realBuffer[pos] != '(') {
	//			pos++;
	//		}

	//		if (pos + 1 < realBuffer.size() && realBuffer[pos + 1] == ' ') { // pas de tab ?
	//			chunkStyle.for_s.space_after_parenth++;
	//			pos++;
	//		}
	//		
	//		while (pos < realBuffer.size() && realBuffer[pos] != '=' && realBuffer[pos] != ';') {
	//			pos++;
	//		}
	//		if (pos >= realBuffer.size())
	//			break;
	//		else if (realBuffer[pos] == ';')
	//			chunkStyle.for_s.point_virgule++;

	//		if (pos < realBuffer.size() && realBuffer[pos] == '=') {
	//			chunkStyle.for_s.affectation++;
	//			if (pos + 1 < realBuffer.size() && realBuffer[pos + 1] == ' ')
	//				chunkStyle.for_s.space_after_affectation++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.for_s.space_before_affectation++;

	//			while (pos < realBuffer.size() && realBuffer[pos] != ';')
	//				pos++;

	//			if (pos >= realBuffer.size())
	//				break;
	//			else if (realBuffer[pos] == ';')
	//				chunkStyle.for_s.point_virgule++;

	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.for_s.space_before_point_virgule++;
	//			else if (realBuffer[pos + 1] == ' ')
	//				chunkStyle.for_s.space_after_point_virgule++;
	//		}
	//		else if (pos < realBuffer.size())
	//			pos++;

	//		while (pos < realBuffer.size() && compareSymbols.find(realBuffer[pos]) != compareSymbols.end() && realBuffer[pos] != ';')
	//			pos++;

	//		if (pos >= realBuffer.size())
	//			break;
	//		else if (realBuffer[pos] == ';')
	//			chunkStyle.for_s.point_virgule++;

	//		if (realBuffer[pos] != ';' && pos + 2 < realBuffer.size() && realBuffer[pos + 1] == '=') {
	//			chunkStyle.for_s.comparaison++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.for_s.space_before_comparaison++;
	//			if (realBuffer[pos + 2 ] == ' ')
	//				chunkStyle.for_s.space_after_comparaison++;
	//		}
	//		else if (realBuffer[pos] != ';' && pos + 1 < realBuffer.size()) {
	//			chunkStyle.for_s.comparaison++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.for_s.space_before_comparaison++;
	//			if (realBuffer[pos + 1] == ' ')
	//				chunkStyle.for_s.space_after_comparaison++;
	//		}

	//		while (pos < realBuffer.size() && realBuffer[pos] != ';')
	//			pos++;

	//		if (pos >= realBuffer.size())
	//			break;
	//		else if (realBuffer[pos] == ';')
	//			chunkStyle.for_s.point_virgule++;

	//		if(realBuffer[pos-1] == ' ')
	//			chunkStyle.for_s.space_before_point_virgule++;
	//		else if (realBuffer[pos + 1] == ' ')
	//			chunkStyle.for_s.space_after_point_virgule++;

	//		if(pos+1 < realBuffer.size())
	//			pos++;

	//		
	//		while (pos < realBuffer.size() && realBuffer[pos] != '=' && realBuffer[pos] != ')') 
	//			pos++;
	//		
	//		if (pos >= realBuffer.size())
	//			break;

	//		if (realBuffer[pos] == '=') {
	//			chunkStyle.for_s.affectation++;
	//			if (pos + 1 < realBuffer.size() && realBuffer[pos + 1] == ' ')
	//				chunkStyle.for_s.space_after_affectation++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.for_s.space_before_affectation++;
	//		}
	//		
	//		while (pos < realBuffer.size() && realBuffer[pos] != ')')
	//			pos++;

	//		if (pos - 1 < realBuffer.size() && realBuffer[pos - 1] == ' ') { // pas de tab ?
	//			chunkStyle.for_s.space_before_parenth++;

	//			if(pos < realBuffer.size())
	//				pos++;
	//		}

	//		while (pos < realBuffer.size() && realBuffer[pos] != '\n' && realBuffer[pos] != '{')
	//			pos++;

	//		if (pos >= realBuffer.size())
	//			break;

	//		if (realBuffer[pos] == '\n') {
	//			while (pos < realBuffer.size() && (realBuffer[pos] == ' ' || realBuffer[pos] == '\t')) {
	//				pos++;
	//			}
	//			if (realBuffer[pos] == '{') {
	//				chunkStyle.for_s.accolade++;
	//				chunkStyle.for_s.accolade_solo++;
	//			}
	//		}
	//		else if (realBuffer[pos] == '{') {
	//			chunkStyle.for_s.accolade++;
	//		}

	//	}
	//	else if (realBuffer[pos] == 'i' && ((pos - 1 >= 0 && (realBuffer[pos - 1] == ' ' || realBuffer[pos - 1] == '\n' || realBuffer[pos - 1] == '\t')) || pos == 0) && pos + 2 < realBuffer.size() && realBuffer[pos + 1] == 'f' && (realBuffer[pos + 2] == '(' || (realBuffer[pos + 3] == '(' && (realBuffer[pos + 2] == ' ' || realBuffer[pos + 2] == '\t')))) {
	//		pos = pos + 2;
	//		chunkStyle.if_s.nb++;
	//		while (pos < realBuffer.size() && realBuffer[pos] != '(') {
	//			pos++;
	//		}
	//		unsigned int nb_parent = 1;

	//		if (pos + 1 < realBuffer.size())
	//			pos++;

	//		if (realBuffer[pos] == ' ') { 
	//			chunkStyle.if_s.space_after_parenth++;
	//			pos++;
	//		}
	//		
	//		while (pos < realBuffer.size() && !(realBuffer[pos] == '>' && realBuffer[pos-1] != '-') && realBuffer[pos] != '<' && realBuffer[pos] != '=' && !(realBuffer[pos] == '!' && realBuffer[pos + 1] == '=') && !(nb_parent == 0) ) {
	//			if (realBuffer[pos] == '(')
	//				nb_parent++;
	//			else if (realBuffer[pos] == ')')
	//				nb_parent--;
	//			if(nb_parent != 0)
	//				pos++;
	//		}

	//		if (nb_parent != 0 && pos + 2 < realBuffer.size() && realBuffer[pos + 1] == '=') {
	//			chunkStyle.if_s.comparaison++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.if_s.space_before_comparaison++;
	//			if (realBuffer[pos + 2] == ' ')
	//				chunkStyle.if_s.space_after_comparaison++;
	//		}
	//		else if (nb_parent != 0 && pos + 1 < realBuffer.size()) {
	//			chunkStyle.if_s.comparaison++;
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.if_s.space_before_comparaison++;
	//			if (realBuffer[pos + 1] == ' ')
	//				chunkStyle.if_s.space_after_comparaison++;
	//		}

	//		while (pos < realBuffer.size() && !(nb_parent == 0)){
	//			if (realBuffer[pos] == '(')
	//				nb_parent++;
	//			else if (realBuffer[pos] == ')')
	//				nb_parent--;
	//			if (nb_parent != 0)
	//				pos++;
	//		}

	//		if (realBuffer[pos - 1] == ' ') { // pas de tab ?
	//			chunkStyle.if_s.space_before_parenth++;
	//		}

	//		while (pos < realBuffer.size() && realBuffer[pos] != '\n' && realBuffer[pos] != '{')
	//			pos++;

	//		if (realBuffer[pos] == '\n') {

	//			if (pos + 1 < realBuffer.size())
	//				pos++;

	//			while (pos < realBuffer.size() && (realBuffer[pos] == ' ' || realBuffer[pos] == '\t')) {
	//				pos++;
	//			}

	//			if (realBuffer[pos] == '{') {
	//				chunkStyle.if_s.accolade++;
	//				chunkStyle.if_s.accolade_solo++;
	//			}
	//		}
	//		else if (realBuffer[pos] == '{') {
	//			chunkStyle.if_s.accolade++;
	//		}
	//	}
	//	//else if (realBuffer[pos] == '(') {
	//	//	chunkStyle.parenth++;
	//	//	if(pos+1 < realBuffer.size() && realBuffer[pos+1] == ' '){
	//	//		chunkStyle.space_after_parenth++;
	//	//		pos++;
	//	//	}
	//	//}
	//	//else if (realBuffer[pos] == ')') {
	//	//	chunkStyle.parenth++;
	//	//	if (pos - 1 >= 0 && realBuffer[pos - 1] == ' ')
	//	//		chunkStyle.space_before_parenth++;
	//	//}
	//	//else if (realBuffer[pos] == '{' ) {
	//
	//	//	int dif = 1;
	//	//	while (pos - dif >= 0 && (realBuffer[pos - dif] == ' ' || realBuffer[pos - dif] == '\t')){
	//	//		dif++;
	//	//	}
	//	//	if ((pos - dif < 0 || realBuffer[pos - dif] == '\n')){
	//	//		chunkStyle.accolade_function++;
	//	//		chunkStyle.accolade_open_function_solo++;
	//	//		
	//	//		//if (pos - dif < 0 && begin - 2 > 0) {
	//	//		//	int ret = getControlStructure(fileBuffer[begin - 2]);

	//	//		//}
	//	//	}

	//	//	else
	//	//		chunkStyle.accolade_function++;
	//	//}
	//	////else if (realBuffer[pos] == '}') {
	//	////	chunkStyle.accolade_function++;
	//	////	int dif = 1;
	//	////	while (pos + dif < realBuffer.size() && (realBuffer[pos + dif] == ' ' || realBuffer[pos + dif] == '\t' || realBuffer[pos + dif] == ';')) {
	//	////		dif++;
	//	////	}
	//	////	if (pos + dif + 3 < realBuffer.size() && realBuffer[pos + dif] == 'e' && realBuffer[pos + dif+1] == 'l' && realBuffer[pos + dif+2] == 's' && realBuffer[pos + dif+3] == 'e') {
	//	////		pos = pos + dif + 3;
	//	////	}
	//	////	else if(realBuffer[pos + dif] == '\n'){
	//	////		chunkStyle.accolade_close_function_solo++;
	//	////		pos = pos + dif;
	//	////	}		
	//	////}
	//	else if (realBuffer[pos] == ';') {
	//		chunkStyle.point_virgule++;
	//		if (pos - 1 > 0) {
	//			if (realBuffer[pos - 1] == ' ')
	//				chunkStyle.space_before_point_virgule++;
	//		}
	//	}
	//	else if (realBuffer[pos] == '=') {
	//		if (pos-1 > 0 && compareSymbols.find(realBuffer[pos-1]) != compareSymbols.end()) {
	//			chunkStyle.comparaison++;
	//			if (pos - 2 > 0) {
	//				if (realBuffer[pos - 2] == ' ')
	//					chunkStyle.space_before_comparaison++;
	//			}
	//			if (pos + 1 < realBuffer.size()) {
	//				if (realBuffer[pos + 1] == ' ') {
	//					chunkStyle.space_after_comparaison++;
	//					pos++;
	//				}
	//			}
	//		}
	//		else if (pos + 1 < realBuffer.size() && realBuffer[pos + 1] == '=') { // comparaison aussi
	//			chunkStyle.comparaison++;
	//			if (pos - 1 > 0) {
	//				if (realBuffer[pos - 1] == ' ' || realBuffer[pos - 1] == '\t')
	//					chunkStyle.space_before_comparaison++;
	//			}
	//			if (pos + 2 < realBuffer.size()) {
	//				if (realBuffer[pos + 2] == ' ') {
	//					chunkStyle.space_after_comparaison++;
	//					pos = pos + 2;
	//				}
	//			}
	//		}
	//		else if (pos - 1 > 0 && affectationSymbols.find(realBuffer[pos - 1]) != affectationSymbols.end()){
	//			chunkStyle.affectation++;
	//			if (pos - 2 > 0) {
	//				if (realBuffer[pos - 2] == ' ')
	//					chunkStyle.space_before_affectation++;
	//				else if(realBuffer[pos - 2] == '\t')
	//					chunkStyle.tab_before_affectation++;
	//			}
	//			if (pos + 1 < realBuffer.size()) {
	//				if (realBuffer[pos + 1] == ' ') {
	//					chunkStyle.space_after_affectation++;
	//					pos++;
	//				}
	//			}
	//		}	
	//		else {
	//			chunkStyle.affectation++;
	//			if (pos - 1 > 0 && (realBuffer[pos - 1] == ' ' ))
	//				chunkStyle.space_before_affectation++;
	//			else if (pos - 1 > 0 && realBuffer[pos - 1] == '\t')
	//				chunkStyle.tab_before_affectation++;
	//			
	//			if (pos + 1 < realBuffer.size() && (realBuffer[pos +1] == ' ' )) { // realBuffer[pos + 1] == '\t'
	//				chunkStyle.space_after_affectation++;
	//				pos++;	
	//			}
	//			else if (pos + 1 < realBuffer.size() && (realBuffer[pos + 1] == '\t')) {
	//				chunkStyle.tab_after_affectation++;
	//				pos++;
	//			}
	//		}
	//	}
	//	else if (realBuffer[pos] == ',') {
	//	chunkStyle.virgule++;
	//		if (pos - 1 > 0) {
	//			if (realBuffer[pos - 1] == ' ' || realBuffer[pos - 1] == '\t')
	//				chunkStyle.space_before_virgule++;
	//		}
	//		if (pos + 1 < realBuffer.size()) {
	//			if (realBuffer[pos + 1] == ' ' || realBuffer[pos + 1] == '\t' || realBuffer[pos + 1] == '\n') {
	//				chunkStyle.space_after_virgule++;
	//				pos++;
	//			}
	//		}
	//	}
	//	////else if (realBuffer[pos] == '*') { // Doit reconnaitre pointeur et multiplication
	//	////	int dif = 1;
	//	////	while (pos - dif > 0 && (realBuffer[pos - dif] == '\t' || realBuffer[pos - dif] == ' ')) {
	//	////		dif++;
	//	////	}
	//	////	if (realBuffer[pos - dif] > 0 && realBuffer[pos - dif] != '\n') {
	//	////		style.pointer++;

	//	////		if (pos + 1 < realBuffer.size()) {
	//	////			if (realBuffer[pos + 1] == ' ') {
	//	////				style.space_after_pointer++;
	//	////				pos++;
	//	////			}
	//	////		}
	//	////	}
	//	////	
	//	////}
	//	pos++;
	//}

	// chunkStyle.displayStyle();
	
}
Chunk::Chunk(unsigned int begin, unsigned int end, int author) {
	this->begin = begin;
	this->end = end;
	this->author = author;
}
std::string Chunk::getBuffer()
{
	return buffer;
}

void Chunk::setBuffer(std::string s)
{
	buffer = s;
}

int Chunk::getAuthor()
{
	return author;
}

std::map<std::string, unsigned int> Chunk::getWords()
{
	return words;
}

void Chunk::freeMemories()
{
	buffer.clear();
	words.clear();
}

unsigned int Chunk::getItResolve()
{
	return nb_resolve;
}

void Chunk::appendBuffer(std::string extraBuffer) // Creer des fonctions utilisées par le constructeur et cette fonction
{	 
	for (auto& c : extraBuffer) // Il y a des \n non remplacés - '.'
		if (specialChar.find(c) != specialChar.end()) // ->
			c = ' ';

	extraBuffer = replaceWord(extraBuffer, "->", " "); // !
	extraBuffer = replaceWord(extraBuffer, "\n", " "); // Etrange que tous les \n pas traité avant
	extraBuffer = replaceWord(extraBuffer, "\t", " ");

	this->buffer += " " + extraBuffer;

	std::vector<std::string> words = split(extraBuffer, " ");

	for (std::string s : words) {

		while (s.size() > 0 && (!iswalpha(s[0]) && !iswdigit(s[0])/* && s[0] != '_'*/))
			s = s.substr(1);

		while (s.size() > 0 && (!iswalpha(s[s.length() - 1]) && !iswdigit(s[s.length() - 1])))
			s = s.substr(0, s.length() - 1);

		if (s.size() > 2) {
			if (!iswdigit(s[0]) && /*((s[0] > 64 && s[0] < 91) || (s[0] > 96 && s[0] < 123))*/ (s[0] >= 0 && s[0] <= 254))
				this->words[s]++;
		}
	}
}

unsigned int Chunk::getLineBegin() {
	return begin;
}
unsigned int Chunk::getLineEnd() {
	return end;
}

std::pair<unsigned int, unsigned int> Chunk::getLines()
{
	return std::make_pair(begin,end);
}

Style Chunk::getStyle()
{
	return chunkStyle;
}

Chunk::~Chunk() {
	freeMemories();
}