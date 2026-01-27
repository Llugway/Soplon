#include "Macro.h"

Macro::Macro() {

}

void Macro::setBuffer(std::string s) {
	buffer = s;
}
std::string Macro::getMacro() {
	return buffer;
}

void Macro::setUpMacro() {
	std::string tempBuffer = buffer;

	while (tempBuffer.size() > 1 && tempBuffer[0] != 'd' && tempBuffer[0] != 'D') { // Majuscule possible ?
		tempBuffer = tempBuffer.substr(1);
	}
	
	if(tempBuffer.size() > 6)
		tempBuffer = tempBuffer.substr(7);

	int i = 0;
	while (i < tempBuffer.size() && tempBuffer[i] != '\t' && tempBuffer[i] != ' ' && tempBuffer[i] != '\n' && tempBuffer[i] != '(') {
		name += tempBuffer[i];
		tempBuffer = tempBuffer.substr(1);
	}
}

std::string Macro::getName() {
	return name;
}

void Macro::setHeader(std::string s) { // Taille etc ..
	headerComment = s;
}

std::string Macro::getHeader() {
	return headerComment;
}