#include "Variable.h"

std::string Variable::getCode() {
	return code;
}
void Variable::setCode(std::string s) {
	code = s;
}

std::string Variable::getName() {
	return name;
}

void Variable::setUpName() {

	for (int i = 0; i < code.size(); i++) {
		if (code[i] != '=' && code[i] != ';'){
			if (code[i] != '\t')
				name += code[i];
			else
				name += ' ';
		}
		else
			break;
	}

}

void Variable::setUpVariable() {
	setUpName();
}

void Variable::setHeader(std::string h) {
	headerComment = h;
}

std::string Variable::getHeader() {
	return headerComment;
}