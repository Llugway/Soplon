#include "Structure.h"

std::string Structure::getStructure() {
	return buffer;
}
void Structure::setBuffer(std::string s) {
	buffer = s;
}

void Structure::setUpStruct() {

	std::string tempBuffer = buffer;

	/*while (tempBuffer.size() > 0 && (tempBuffer[0] == ' ' || tempBuffer[0] == '\t') ) {
		tempBuffer.substr(1);
	}*/

	while (tempBuffer.size() > 6 && !(tempBuffer[0] == 's' && tempBuffer[1] == 't' && tempBuffer[2] == 'r' && tempBuffer[3] == 'u' && tempBuffer[4] == 'c' && tempBuffer[5] == 't')) {
		tempBuffer = tempBuffer.substr(1);
	}
	if(tempBuffer.size() > 6)
		tempBuffer = tempBuffer.substr(7);

	while (tempBuffer.size() > 0 && tempBuffer[0] != '{' && tempBuffer[0] != '=') { // Egale pour une variable pas définition de structs
		if(tempBuffer[0] != '\n' && tempBuffer[0] != '\t')
			name += tempBuffer[0];
		tempBuffer = tempBuffer.substr(1);
	}
	if (name.size() == 0)
		name = "UNKNOW";
}
std::string Structure::getName() {
	return name;
}

std::string Structure::getHeader() {
	return header;
}

void Structure::setHeader(std::string s) {
	header = s;
	if (s.size() > 0)
		withHeader = true;
}