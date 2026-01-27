#include "Enum.h"

void Enum::setCode(std::string s) {
	code = s;
}
std::string Enum::getCode() {
	return code;
}

void Enum::setHeader(std::string h) {
	headerComment = h;
}

std::string Enum::getHeader() {
	return headerComment;
}