#include "Header.h"


Header::Header() {
	headerComment = "";
	// denom = new std::unordered_set<std::string>();
	// denom = new std::map<std::string, std::pair<unsigned int, unsigned int>>();
	// denom = new std::map<std::string, std::set<unsigned int>>();
}

std::string Header::getHeader() {
	return headerComment;
}
void Header::setHeader(std::string h) {
	headerComment = h;
	nbChars = headerComment.size();
	withHeader = nbChars > 0;
}

void Header::setHeaderVector(std::vector<std::string> v)
{
	headerCommentVector = v;
}

void Header::setHeaderBegin(unsigned int i)
{
	begin = i;
}

unsigned int Header::getHeaderBegin()
{
	return begin;
}

void Header::setHeaderEnd(unsigned int i)
{
	end = i;
}

unsigned int Header::getHeaderEnd()
{
	return end;
}

void Header::setAuthorsLines(std::vector<std::pair<std::pair<unsigned int, unsigned int>, int>> s)
{
	authorsLines = s;
}

int Header::getNbChars() {
	return nbChars;
}
bool Header::getWithHeader() {
	return withHeader;
}
void Header::parseHeader() {

	// std::cout << headerComment << std::endl;

	// std::string tempHeader = headerComment;
	//std::string tempHeader2;

	//std::vector<char> chs;
	//std::vector<std::string> copyrights;
	//std::string copyright;
	//std::string author;
	//std::string by;

	//std::vector<std::string> possibilities;

	////chs.push_back('.');
	////chs.push_back('-');
	//chs.push_back('\n');
	//chs.push_back(':');
	//chs.push_back('©');
	//// chs.push_back('/');
	////chs.push_back(';');
	////chs.push_back(',');

	//std::vector<char> chsAddress;

	//chsAddress.push_back('<');
	//chsAddress.push_back('>');
	//chsAddress.push_back('(');
	//chsAddress.push_back(')');
	//chsAddress.push_back('[');
	//chsAddress.push_back(']');
	//chsAddress.push_back('*');
	//// chsAddress.push_back('=');
	//// chsAddress.push_back('-');
	//// chsAddress.push_back('/');


	//for (auto& c : tempHeader)
	//	if (c == '\t')
	//		c = ' ';

	//tempHeader2 = tempHeader;
	//tempHeader2 = replaceWord(tempHeader2, "\n", " ");

	//std::vector<std::string> words = split(tempHeader2, " ");

	//for (int i = 0; i < words.size(); i++) {

	//	std::string s = words.at(i);
	//	s = deleteWord(s, "*/");
	//	s = deleteChars(s, chsAddress);
	//	while (s.size() > 0 && (s[0] == '/' || s[0] == '=' || s[0] == '-' || s[0] == ' ' || s[0] == '"'))
	//		s = s.substr(1);

	//	if (s.size() > 0) {
	//		std::vector<std::string> spli = split(s, "@");

	//		if (spli.size() == 2 && isAlphaWord(spli[0]) && isAlphaWord(spli[1])) { // ATTENTION SPLIT WORDS.AT NOT S
	//			int pos = s.find(" ");
	//			if (pos != 0xffffffffffffffff)
	//				s = s.substr(0, pos);
	//			if (s[s.length() - 1] == '.' || s[s.length() - 1] == ',' || s[s.length() - 1] == ';' || s[s.length() - 1] == ':' || s[s.length() - 1] == ' ' || s[s.length() - 1] == ',') // Caractère collé
	//				s = s.substr(0, s.length() - 1);
	//			while (s[s.length() - 1] == '/' || s[s.length() - 1] == '=' || s[s.length() - 1] == '-' || s[s.length() - 1] == ' ' || s[s.length() - 1] == '.' || s[s.length() - 1] == ',' || s[s.length() - 1] == '>')
	//				s = s.substr(0, s.length() - 1);
	//			s = deleteWord(s, "mailto:");
	//			if (std::find(mailAddress.begin(), mailAddress.end(), s) == mailAddress.end()) {
	//				std::vector<std::string>::iterator it = std::find(mailAddress.begin(), mailAddress.end(), s);
	//				if (it == mailAddress.end()) {
	//					mailAddress.push_back(s);
	//					denom->insert(s);
	//				}
	//			}
	//		}
	//		else if ((s.find("http") != 0xffffffffffffffff) || (s.find("www.") != 0xffffffffffffffff)) {
	//			if (s[s.length() - 1] == '.' || s[s.length() - 1] == ',' || s[s.length() - 1] == ';' || s[s.length() - 1] == ':' || s[s.length() - 1] == ' ')
	//				s = s.substr(0, s.length() - 1);
	//			while (s[s.length() - 1] == '/' || s[s.length() - 1] == '=' || s[s.length() - 1] == '-' || s[s.length() - 1] == ' ')
	//				s = s.substr(0, s.length() - 1);
	//			if (std::find(webAddress.begin(), webAddress.end(), s) == webAddress.end()) {
	//				std::vector<std::string>::iterator it = std::find(webAddress.begin(), webAddress.end(), s);
	//				if (it == webAddress.end()) {
	//					webAddress.push_back(s);
	//					denom->insert(s);
	//				}
	//			}
	//		}
	//	}

	//}
	//std::vector<std::string> parse;

	//int posCopy, posAuthor, posBy, posName;
	//int posCompare;


	//std::vector<std::string> copyrightAnnouncers = { "©" , "(C)" , "(c)", "COPYRIGHT", "Copyright" };
	//std::vector<std::string> authorAnnouncers = { "Author(s):","Authors:", "Author:", "AUTHOR(S):","AUTHORS:", "AUTHOR:" };
	//std::vector<std::string> writtenByAnnouncers = { "by:", "By:", "BY:", "Written by","Written By" }; // Pas obligatoire car char : enlevé

	//std::vector<std::string> copyrightNoises = { "ALL RIGHTS RESERVED", "All rights reserved","All Rights Reserved","All right reserved","All rights rsvd","All rights","*/" }; // INC INCORPORATION ???

	//posCopy = tempHeader.find(copyrightAnnouncers[0]);

	//for (int i = 1; i < copyrightAnnouncers.size(); i++) {
	//	posCompare = tempHeader.find(copyrightAnnouncers[i]);
	//	if (posCopy == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posCopy))
	//		posCopy = posCompare;
	//}

	//posAuthor = tempHeader.find(authorAnnouncers[0]);

	//for (int i = 1; i < authorAnnouncers.size(); i++) {
	//	posCompare = tempHeader.find(authorAnnouncers[i]);
	//	if (posAuthor == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posAuthor))
	//		posAuthor = posCompare;
	//}

	//posBy = tempHeader.find(writtenByAnnouncers[0]);

	//for (int i = 1; i < writtenByAnnouncers.size(); i++) {
	//	posCompare = tempHeader.find(writtenByAnnouncers[i]);
	//	if (posBy == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posBy))
	//		posBy = posCompare;
	//}

	//tempHeader2 = tempHeader;

	//bool soloAnouncer = true;

	//while (posCopy != 0xffffffffffffffff) { // Va chercher le mot copyright dans un bloc de texte

	//	bool niceCopy = false;

	//	copyright = tempHeader2.substr(posCopy);
	//	copyright = copyright.substr(0, copyright.find('\n') + 1);

	//	for (int i = 0; i < copyrightAnnouncers.size(); i++) {
	//		int pos = copyright.find(copyrightAnnouncers[i]);
	//		if (pos != 0xffffffffffffffff) {
	//			// copyright = deleteWord(copyright, copyrightAnnouncers[i]);

	//			if (copyrightAnnouncers[i] == "(C)" || copyrightAnnouncers[i] == "(c)" || copyrightAnnouncers[i] == "©" || copyright.find(copyrightAnnouncers[i] + ':') != 0xffffffffffffffff)
	//				niceCopy = true;

	//			copyright = copyright.substr(pos + copyrightAnnouncers[i].length());

	//		}
	//	}

	//	for (int i = 0; i < copyrightNoises.size(); i++) {
	//		int pos = copyright.find(copyrightNoises[i]);
	//		if (pos != 0xffffffffffffffff){
	//			copyright = copyright.substr(0, pos);
	//		}
	//		//copyright = deleteWord(copyright, copyrightNoises[i]);
	//	}

	//	copyright = replaceWord(copyright, " by", " "); // Avant ou apres les deleteWords

	//	copyright = deleteChars(copyright, { '*' , '|' , '?' });

	//	for (std::string s : webAddress) {
	//		copyright = deleteWord(copyright, s);
	//	}

	//	copyright = deleteBetweenDelimiters(copyright);

	//	for (std::string s : mailAddress) {      // A rétablir si pas d'addresse mail entre délimiteur
	//		copyright = deleteWord(copyright, s);
	//	}

	//	possibilities = split(copyright, ";");
	//	if (possibilities.size() == 1)
	//		possibilities = split(copyright, ",");
	//	if (possibilities.size() == 1)
	//		possibilities = split(copyright, " - ");

	//	for (std::string poss : possibilities) {
	//		poss = deleteChars(poss, chs);

	//		parse = split(poss, " ");
	//		for (int i = 0; i < parse.size(); i++) {
	//			if (numberMorePresent(parse.at(i), 0.80) && parse.at(i).size() > 2) { // Fait le choix de ne pas prendre les copyrights sans date pour ne pas récupérer des pavets de texte
	//				niceCopy = true;
	//				break;
	//			}
	//		}
	//		if (niceCopy)
	//			break;
	//	}

	//	for (int index = 0; index < possibilities.size(); index++) {
	//		std::string poss = possibilities[index];

	//		poss = deleteChars(poss, chs);

	//		while (poss.length() != 0 && (poss[poss.length() - 1] == '=' || poss[poss.length() - 1] == '-' || poss[poss.length() - 1] == '/' || poss[poss.length() - 1] == ' ' || poss[poss.length() - 1] == '.'))
	//			poss = poss.substr(0, poss.length() - 1);

	//		while (poss.length() != 0 && (poss[0] == '-' || poss[0] == ' ' || poss[0] == ','))
	//			poss = poss.substr(1);


	//		if (poss.substr(0, 5) == "Inc. ")
	//			poss = poss.substr(5);
	//		else if (poss.substr(0, 4) == "Inc ")
	//			poss = poss.substr(4);

	//		// A voir si rewhile pour clean

	//		parse = split(poss, " ");
	//
	//		poss = "";
	//		int length = 0;
	//		for (int i = 0; i < parse.size(); i++) {
	//			if (!numberMorePresent(parse.at(i), 0.80)) { // Changer pour letter 
	//				if ((parse.at(i) == "&" || parse.at(i) == "@" || parse.at(i) == "for" || parse.at(i) == "of" || parse.at(i) == "-" || parse.at(i) == "--" || parse.at(i) == "and") && niceCopy) {
	//					if (poss.length() != 0) {
	//						poss = poss.substr(0, poss.length() - 1);
	//						// std::cout << "COPYRIGHT : " << poss << std::endl;
	//						denom->insert(poss);
	//						copyrights.push_back(poss);
	//					}
	//					
	//					poss = "";
	//				}
	//				else {
	//					length++;					// contributors
	//					if (length > 8 || (parse.at(i) == "BE" || parse.at(i) == "be" || parse.at(i) == "GPL" || parse.at(i) == "Distributed" || parse.at(i) == "adapted" || parse.at(i) == "COPYING" || parse.at(i) == "version" || parse.at(i) == "distributed" || parse.at(i).find("licens") != 0xffffffffffffffff || parse.at(i).find("term") != 0xffffffffffffffff)) { // "AS IS" ; "DISCLAIM" || parse.at(i) == "Based"
	//						if (niceCopy)
	//							niceCopy = false;
	//						break;
	//					}
	//					if (parse.at(i) == "who" || parse.at(i) == "based") {
	//						break;
	//					}
	//					poss += parse.at(i) + ' ';

	//				}
	//			}
	//		}

	//		if (niceCopy && poss.length() != 0) {
	//			poss = poss.substr(0, poss.length() - 1);

	//			if (atLeastOneUpper(poss)) { // Gérer ce qui n'est pas un nom

	//				poss = cleanDenom(poss);
	//				if (poss[0] != '@' && poss.length() != 0) {
	//					// std::cout << "COPYRIGHT : " << poss << std::endl;
	//					denom->insert(poss);
	//					copyrights.push_back(poss);
	//				}
	//			}
	//		}
	//	}

	//	tempHeader2 = tempHeader2.substr(posCopy);
	//	tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);

	//	posCopy = tempHeader2.find(copyrightAnnouncers[0]);

	//	for (int i = 1; i < copyrightAnnouncers.size(); i++) {
	//		posCompare = tempHeader2.find(copyrightAnnouncers[i]);
	//		if (posCopy == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posCopy))
	//			posCopy = posCompare;
	//	}

	//	if (soloAnouncer && posCopy != 0xffffffffffffffff) // On part du principe que si 2 occurences d'annonceur il n'y aura pas de déclaration sans
	//		soloAnouncer = false;

	//	if (soloAnouncer) {

	//		std::string nextLine = tempHeader2.substr(0, tempHeader2.find('\n') + 1); // Doit enlever la ligne dans tempHeader2
	//		int posAnouncer;
	//		bool anouncer = false;
	//		if (nextLine.size() > 1) {
	//			if (!anouncer && isAlphaWord(nextLine)) {
	//				for (int i = 0; i < copyrightAnnouncers.size(); i++) {
	//					posAnouncer = nextLine.find(copyrightAnnouncers[i]);
	//					if (posAnouncer != 0xffffffffffffffff) {
	//						anouncer = true;
	//						break; // Ne pas refaire un tour
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < authorAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(authorAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < writtenByAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(writtenByAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					posAnouncer = nextLine.find(": ");
	//					int posAnouncer2 = nextLine.find(":\n");
	//					if (posAnouncer != 0xffffffffffffffff || posAnouncer2 != 0xffffffffffffffff) {
	//						anouncer = true;
	//						break; // Ne pas refaire un tour
	//					}
	//				}

	//				if (!anouncer) {

	//					int pos = nextLine.find("by ");
	//					if (pos == 0xffffffffffffffff) {
	//						pos = nextLine.find("from ");
	//						if (pos == 0xffffffffffffffff) {
	//							int i = 0;
	//							while (!iswalpha(nextLine[i]) && !iswdigit((nextLine[i])) && nextLine[i] != '(' && nextLine[i] != '<' && nextLine[i] != '[') // Obligé de laisser les chiffres pour copyright comme manière de les dissocier des mots copyrights dans un texte
	//								i++;
	//							posCopy = i;
	//						}
	//						else
	//							posCopy = pos + 5;
	//					}
	//					else
	//						posCopy = pos + 3;
	//				}
	//			}
	//		}
	//		else {
	//			posCopy = 0xffffffffffffffff;
	//		}

	//	}
	//}

	//tempHeader2 = tempHeader;

	//if (!soloAnouncer)
	//	soloAnouncer = true;

	//while (posAuthor != 0xffffffffffffffff) {
	//	author = tempHeader2.substr(posAuthor);
	//	author = author.substr(0, author.find('\n') + 1);

	//	for (int i = 0; i < authorAnnouncers.size(); i++) {
	//		//author = deleteWord(author, authorAnnouncers[i]);
	//		int pos = author.find(authorAnnouncers[i]);
	//		if (pos != 0xffffffffffffffff) {
	//			// copyright = deleteWord(copyright, copyrightAnnouncers[i]);
	//			author = author.substr(pos + authorAnnouncers[i].length());
	//		}
	//	}

	//	author = deleteWord(author, "*/");
	//	// author = replaceWord(author, " by "," ");
	//	//author = deleteChars(author, chsAddress);

	//	author = deleteChars(author, { '*', '|','?' });
	//	author = deleteBetweenDelimiters(author);

	//	//for (std::string s : mailAddress) {
	//	//	author = deleteWord(author, s);		
	//	//}

	//	for (std::string s : webAddress) {
	//		author = deleteWord(author, s);
	//	}

	//	for (std::string s : copyrights) {
	//		author = deleteWord(author, s);
	//	}

	//	possibilities = split(author, ";");
	//	if (possibilities.size() == 1)
	//		possibilities = split(author, ",");
	//	if (possibilities.size() == 1)
	//		possibilities = split(author, " - ");


	//	for (int index = 0; index < possibilities.size(); index++) {
	//		std::string poss = possibilities[index];

	//		poss = deleteChars(poss, chs);

	//		while (poss.length() != 0 && (poss[poss.length() - 1] == '=' || poss[poss.length() - 1] == '-' || poss[poss.length() - 1] == '/' || poss[poss.length() - 1] == ' ' || poss[poss.length() - 1] == '.'))
	//			poss = poss.substr(0, poss.length() - 1);

	//		while (poss.length() != 0 && (poss[0] == '-' || poss[0] == ' ' || poss[0] == ','))
	//			poss = poss.substr(1);

	//		parse = split(poss, " ");

	//		poss = "";
	//		bool niceAuthor = true;
	//		for (int i = 0; i < parse.size(); i++) {
	//			if (!numberMorePresent(parse.at(i), 0.80)) {
	//				if ((parse.at(i) == "&" || parse.at(i) == "@" || parse.at(i) == "for" || parse.at(i) == "of"  || parse.at(i) == "-" ||  parse.at(i) == "and") && poss.length() != 0) { 
	//					poss = poss.substr(0, poss.length() - 1);
	//					//std::cout << "author : " << poss << std::endl;
	//					denom->insert(poss);
	//					poss = "";
	//				}
	//				else {
	//					
	//					if ((parse.at(i) == "BE" || parse.at(i) == "be" || parse.at(i) == "Distributed" || parse.at(i) == "version"  || parse.at(i) == "distributed" || parse.at(i).find("licens") != 0xffffffffffffffff || parse.at(i).find("term") != 0xffffffffffffffff)) { // "AS IS" ; "DISCLAIM" || parse.at(i) == "Based"
	//						if (niceAuthor)
	//							niceAuthor = false;
	//						break;
	//					}
	//					if (parse.at(i) == "who" || parse.at(i) == "based") {
	//						break;
	//					}
	//					poss += parse.at(i) + ' ';
	//				}
	//			}
	//		}

	//		if (poss.length() != 0 && niceAuthor) {
	//			int pos = poss.find(" by ");
	//			if (pos == 0xffffffffffffffff)
	//				poss = poss.substr(0, poss.length() - 1);
	//			else
	//				poss = poss.substr(pos + 4);

	//			poss = cleanDenom(poss);
	//			if (poss[0] != '@' &&  poss.length() != 0) {
	//				//std::cout << "Author : " << poss << std::endl;
	//				denom->insert(poss);
	//			}

	//		}
	//	}

	//	tempHeader2 = tempHeader2.substr(posAuthor);
	//	tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);

	//	posAuthor = tempHeader2.find(authorAnnouncers[0]);

	//	for (int i = 1; i < authorAnnouncers.size(); i++) {
	//		posCompare = tempHeader2.find(authorAnnouncers[i]);
	//		if (posAuthor == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posAuthor))
	//			posAuthor = posCompare;
	//	}

	//	if (soloAnouncer && posAuthor != 0xffffffffffffffff) // On part du principe que si 2 occurences d'annonceur il n'y aura pas de déclaration sans
	//		soloAnouncer = false;

	//	if (soloAnouncer) {

	//		std::string nextLine = tempHeader2.substr(0, tempHeader2.find('\n') + 1); // Doit enlever la ligne dans tempHeader2

	//		if (nextLine.size() > 1) {
	//			int posAnouncer;
	//			bool anouncer = false;

	//			if (!anouncer && isAlphaWord(nextLine)) {
	//				for (int i = 0; i < copyrightAnnouncers.size(); i++) {
	//					posAnouncer = nextLine.find(copyrightAnnouncers[i]);
	//					if (posAnouncer != 0xffffffffffffffff) {
	//						anouncer = true;
	//						break; // Ne pas refaire un tour
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < authorAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(authorAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < writtenByAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(writtenByAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					posAnouncer = nextLine.find(": ");
	//					int posAnouncer2 = nextLine.find(":\n");
	//					if (posAnouncer != 0xffffffffffffffff || posAnouncer2 != 0xffffffffffffffff) {
	//						anouncer = true;
	//						break; // Ne pas refaire un tour
	//					}
	//				}

	//				if (!anouncer) {
	//					int pos = nextLine.find("by ");
	//					if (pos == 0xffffffffffffffff){
	//						pos = nextLine.find("from ");
	//						if (pos != 0xffffffffffffffff)
	//							posBy = pos + 5;
	//					}
	//					else
	//						posAuthor = pos + 3;

	//					if (pos == 0xffffffffffffffff) {
	//						int i = 0;
	//						bool bl = true;
	//						/*	while (!iswalpha(nextLine[i]) && nextLine[i] != '(' && nextLine[i] != '<' && nextLine[i] != '[')
	//								i++;
	//								posBy = i;
	//								*/
	//						for (int j = 0; j < posBy; j++) {
	//							if (nextLine[j] != ' ') {
	//								bl = false;
	//								break;
	//							}
	//						}
	//						if (!bl)
	//							pos = 0xffffffffffffffff;
	//					}
	//				}

	//			}
	//		}
	//		else {
	//			posAuthor = 0xffffffffffffffff;
	//		}

	//	}
	//}

	//tempHeader2 = tempHeader;

	//if (!soloAnouncer)
	//	soloAnouncer = true;

	//while (posBy != 0xffffffffffffffff) {
	//	by = tempHeader2.substr(posBy);
	//	by = by.substr(0, by.find('\n') + 1);

	//	for (int i = 0; i < writtenByAnnouncers.size(); i++) {
	//		// by = deleteWord(by, writtenByAnnouncers[i]);
	//		int pos = by.find(writtenByAnnouncers[i]);
	//		if (pos != 0xffffffffffffffff) {
	//			// copyright = deleteWord(copyright, copyrightAnnouncers[i]);
	//			by = by.substr(pos + writtenByAnnouncers[i].length());
	//		}
	//	}

	//	by = deleteWord(by, "*/");
	//	//by = deleteChars(by, chsAddress);

	//	by = deleteChars(by, { '*', '?' });
	//	by = deleteBetweenDelimiters(by);

	//	for (std::string s : mailAddress) {
	//		by = deleteWord(by, s);
	//	}

	//	for (std::string s : webAddress) {
	//		by = deleteWord(by, s);
	//	}

	//	for (std::string s : copyrights) {
	//		by = deleteWord(by, s);
	//	}

	//	possibilities = split(by, ";");
	//	if (possibilities.size() == 1)
	//		possibilities = split(by, ",");
	//	if (possibilities.size() == 1)
	//		possibilities = split(by, " - ");


	//	for (int index = 0; index < possibilities.size(); index++) {

	//		std::string poss = possibilities[index];

	//		poss = deleteChars(poss, chs);

	//		while (poss.length() != 0 && (poss[poss.length() - 1] == '=' || poss[poss.length() - 1] == '-' || poss[poss.length() - 1] == '/' || poss[poss.length() - 1] == ' ' || poss[poss.length() - 1] == '.'))
	//			poss = poss.substr(0, poss.length() - 1);

	//		while (poss.length() != 0 && (poss[0] == '-' || poss[0] == ' ' || poss[0] == ','))
	//			poss = poss.substr(1);

	//		parse = split(poss, " ");

	//		poss = "";
	//		bool niceBy = true;
	//		for (int i = 0; i < parse.size(); i++) {
	//			if (!numberMorePresent(parse.at(i), 0.80)) {
	//				if (((parse.at(i) == "&" || parse.at(i) == "@") || parse.at(i) == "for" || parse.at(i) == "-" || parse.at(i) == "of" || parse.at(i) == "and") && poss.length() != 0) {
	//					poss = poss.substr(0, poss.length() - 1);
	//					//std::cout << "By : " << poss << std::endl;
	//					denom->insert(poss);
	//					poss = "";
	//				}
	//				else {					
	//					if ((parse.at(i) == "BE" || parse.at(i) == "be" || parse.at(i) == "Distributed" || parse.at(i) == "version" || parse.at(i) == "distributed"  || parse.at(i).find("licens") != 0xffffffffffffffff || parse.at(i).find("term") != 0xffffffffffffffff)) { // "AS IS" ; "DISCLAIM" || parse.at(i) == "Based"
	//						if (niceBy)
	//							niceBy = false;
	//						break;
	//					}
	//					if (parse.at(i) == "who" || parse.at(i) == "based") {
	//						break;
	//					}
	//					poss += parse.at(i) + ' ';
	//				}
	//			}
	//		}

	//		if (poss.length() != 0 && niceBy) { // Cas ou ca ne cut pas à by

	//			int pos = poss.find(" by ");
	//			if (pos == 0xffffffffffffffff)
	//				poss = poss.substr(0, poss.length() - 1);
	//			else
	//				poss = poss.substr(pos + 4);

	//			poss = cleanDenom(poss);
	//			if (poss[0] != '@' && poss.length() != 0) {
	//				
	//				//std::cout << "By : " << poss << std::endl;
	//				denom->insert(poss);
	//			}
	//		}
	//	}

	//	tempHeader2 = tempHeader2.substr(posBy);
	//	tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);

	//	posBy = tempHeader2.find(writtenByAnnouncers[0]);

	//	for (int i = 1; i < writtenByAnnouncers.size(); i++) {
	//		posCompare = tempHeader2.find(writtenByAnnouncers[i]);
	//		if (posBy == 0xffffffffffffffff || (posCompare != 0xffffffffffffffff && posCompare < posBy))
	//			posBy = posCompare;
	//	}

	//	if (soloAnouncer && posBy != 0xffffffffffffffff) // On part du principe que si 2 occurences d'annonceur il n'y aura pas de déclaration sans
	//		soloAnouncer = false;

	//	if (soloAnouncer) {

	//		std::string nextLine = tempHeader2.substr(0, tempHeader2.find('\n') + 1); // Doit enlever la ligne dans tempHeader2

	//		if (nextLine.size() > 1) {
	//			int posAnouncer;
	//			bool anouncer = false;

	//			if (!anouncer && isAlphaWord(nextLine)) {
	//				for (int i = 0; i < copyrightAnnouncers.size(); i++) {
	//					posAnouncer = nextLine.find(copyrightAnnouncers[i]);
	//					if (posAnouncer != 0xffffffffffffffff) {
	//						anouncer = true;
	//						break; // Ne pas refaire un tour
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < authorAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(authorAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					for (int i = 0; i < writtenByAnnouncers.size(); i++) {
	//						posAnouncer = nextLine.find(writtenByAnnouncers[i]);
	//						if (posAnouncer != 0xffffffffffffffff) {
	//							anouncer = true;
	//							break; // Ne pas refaire un tour
	//						}
	//					}
	//				}

	//				if (!anouncer) {
	//					int pos = nextLine.find("by ");
	//					if (pos == 0xffffffffffffffff){
	//						pos = nextLine.find("from ");
	//						if (pos != 0xffffffffffffffff)
	//							posBy = pos + 5;
	//					}
	//					else
	//						posBy = pos + 3;

	//					if (pos == 0xffffffffffffffff) {
	//						int i = 0;
	//						bool bl = true;
	//						/*	while (!iswalpha(nextLine[i]) && nextLine[i] != '(' && nextLine[i] != '<' && nextLine[i] != '[')
	//								i++;
	//								posBy = i;
	//								*/
	//						for (int j = 0; j < posBy; j++) {
	//							if (nextLine[j] != ' ') {
	//								bl = false;
	//								break;
	//							}
	//						}
	//						if (!bl)
	//							pos = 0xffffffffffffffff;
	//					}						
	//				}
	//			}
	//		}
	//		else {
	//			posBy = 0xffffffffffffffff;
	//		}
	//	}
	//}


	//denom->erase("Inc");
	//denom->erase("inc");
	//denom->erase("Ltd");
	//denom->erase("and");

	//std::cout << std::endl;
	//for (const auto& deno : *denom)
	//	std::cout << deno << std::endl;
	//std::cout << std::endl;
}

void Header::parseHeader2()
{
	// std::cout << headerComment << std::endl;

	std::vector<char> chs;

	std::vector<char> chsDelimiter;

	chs.push_back('.');
	chs.push_back('-');
	chs.push_back(':');
	chs.push_back('©');
	chs.push_back('/');
	chs.push_back('|');

	// chs.push_back('*');
	chs.push_back('=');
	chs.push_back('"');
	chs.push_back('\'');
	chs.push_back('`');
	chs.push_back('?');

	chs.push_back('<');
	chs.push_back('>');
	chs.push_back(')');
	chs.push_back('(');
	chs.push_back('[');
	chs.push_back(']');

	chsDelimiter.push_back(';');
	chsDelimiter.push_back(',');
	chsDelimiter.push_back('&');

	unsigned int indexLine = 0;
	std::string line;
	unsigned int indexLinesKnown = 0;
	int author;

	unsigned int lastPos = 0;

	bool anouncer = false;
	bool soloAnouncer = false;

	while (indexLine < headerCommentVector.size()) {
		line = headerCommentVector[indexLine];

		if (indexLinesKnown < authorsLines.size() && indexLine - begin + 1 >= authorsLines[indexLinesKnown].first.first && indexLine - begin + 1 <= authorsLines[indexLinesKnown].first.second)
			author = authorsLines[indexLinesKnown].second;
		else if (indexLinesKnown < authorsLines.size() && indexLine - begin + 1> authorsLines[indexLinesKnown].first.first && indexLine - begin + 1 > authorsLines[indexLinesKnown].first.second) {
			while (indexLinesKnown < authorsLines.size() && authorsLines[indexLinesKnown].first.first < indexLine - begin)
				indexLinesKnown++;

			if (indexLinesKnown < authorsLines.size() && indexLine - begin + 1 >= authorsLines[indexLinesKnown].first.first && indexLine - begin + 1 <= authorsLines[indexLinesKnown].first.second)
				author = authorsLines[indexLinesKnown].second;
			else
				author = -1;
		}
		else
			author = -1;

		std::string tempLine;
		for (char& c : line) {
			if (c == '\t')
				tempLine += "    ";
			else if (c == '\n' || c == '*')
				tempLine += " ";
			else
				tempLine += c;
		}

		line = tempLine;
		headerCommentVector[indexLine] = tempLine;

		std::vector<char> tempDelim = chsDelimiter;
		tempDelim.push_back(' ');

		std::vector<std::string> words = split(line, tempDelim);

		for (int i = 0; i < words.size(); i++) {

			std::string s = words.at(i);

			std::vector<std::string> spli = split(s, "@");

			if (spli.size() == 2) {

				unsigned int ind = 0;

				bool firstPart = true;

				while (ind < s.size() && s[ind] != '@') {

					if (!((s[ind] > 47 && s[ind] < 58) || (s[ind] > 64 && s[ind] < 90) || (s[ind] > 96 && s[ind] < 123) || s[ind] == 46 || s[ind] == 45 || s[ind] == 95)) {
						s = s.substr(ind + 1);
						ind = 0;
					}
					else
						ind++;
				}

				std::vector<std::string> premPart;

				if (ind == 0) {
					firstPart = false;
					std::vector<char> delims = { '|','{','}' }; // '(',')' ,'[',']'
					premPart = split(words.at(i).substr(0, words.at(i).find("@") - 1), delims);
				}

				ind++;

				while (ind < s.size() && ((s[ind] > 47 && s[ind] < 58) || (s[ind] > 64 && s[ind] < 90) || (s[ind] > 96 && s[ind] < 123) || s[ind] == 46 || s[ind] == 45 || s[ind] == 95)) {
					ind++;
				}

				if (ind != s.size())
					s = s.substr(0, ind);


				if (author != -1) {
					if (premPart.size() > 1) {
						for (std::string p : premPart) {
							mailAddress[p + s].insert(author);
							denom[p + s].insert(author);
						}
					}
					else if(firstPart){
						mailAddress[s].insert(author);
						denom[s].insert(author);
					}
				}
				else {
					if (premPart.size() > 1) {
						for (std::string p : premPart) {
							mailAddress[p + s];
							denom[p + s];
						}
					}
					else if (firstPart) {
						mailAddress[s];
						denom[s];
					}
				}

				if (premPart.size() > 1)
					line = deleteWord(line, words.at(i).substr(0, words.at(i).find("@") - 1));
				else
					line = deleteWord(line, s);

			}

			if ((s.find("http") != -1) || (s.find("www.") != -1)) {
				for (char& c : chsDelimiter) {
					while (s.size() > 0 && s[0] == c) {
						s = s.substr(1);
					}
					while (s.size() > 0 && s[s.size() - 1] == c) {
						s = s.substr(0, s.size() - 1);
					}
				}
				for (char& c : chs) {
					while (s.size() > 0 && s[0] == c) {
						s = s.substr(1);
					}
					while (s.size() > 0 && s[s.size() - 1] == c) {
						s = s.substr(0, s.size() - 1);
					}
				}

				if (author != -1) {
					webAddress[s].insert(author);
					denom[s].insert(author);
				}
				else {
					webAddress[s];
					denom[s];
				}

				line = deleteWord(line, s);
			}
		}

		int posCopy = -1, pos = -1;

		unsigned int i = 0;

		while (i < copyrightAnnouncers.size() && posCopy == -1) {
			posCopy = line.find(copyrightAnnouncers[i]);
			if (posCopy != -1)
				posCopy += copyrightAnnouncers[i].size();
			i++;
		}

		i = 0;

		while (i < authorAnnouncers.size() && pos == -1) {
			pos = line.find(authorAnnouncers[i]);
			if (pos != -1)
				pos += authorAnnouncers[i].size();
			i++;
		}

		if (pos == -1) {

			i = 0;

			while (i < writtenByAnnouncers.size() && pos == -1) {
				pos = line.find(writtenByAnnouncers[i]);
				if (pos != -1)
					pos += writtenByAnnouncers[i].size();
				i++;
			}
		}

		if (posCopy != -1) {

			bool niceCopy = false;

			line = line.substr(posCopy);

			for (int i = 0; i < copyrightNoises.size(); i++) {
				int pos = line.find(copyrightNoises[i]);
				if (pos != -1) {
					line = deleteWord(line, copyrightNoises[i]);
				}
			}

			for (int i = 0; i < noises.size(); i++) {
				int pos = line.find(noises[i]);
				if (pos != -1) {
					line = deleteWord(line, noises[i]);
				}
			}

			std::vector<std::string> groups = isolateParenth(line);

			for (std::string& s : groups) {
				for (char& c : chs)
					s = replaceChar(s, c, ' ');
			}

			for (char& c : chs)
				line = replaceChar(line, c, ' ');

			std::vector<std::string> tempPossibilities, possibilities;

			tempPossibilities = split(line, chsDelimiter);

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " for "))

					if (s2.find("source code") != -1)
						break;
					else
						possibilities.push_back(s2);
			}

			tempPossibilities = possibilities;
			possibilities.clear();

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " on behalf of "))
					possibilities.push_back(s2);
			}

			tempPossibilities = possibilities;
			possibilities.clear();

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " and "))
					possibilities.push_back(s2);
			}


			if (possibilities.size() == 1)
				possibilities = split(possibilities[0], " - ");


			for (std::string& s : groups) {
				for (std::string s2 : split(s, chsDelimiter))
					possibilities.push_back(s2);
			}

			for (std::string& poss : possibilities) {

				std::vector<std::string> parse;
				parse = split(poss, " ");
				
				poss = "";

				if (parse.size() > 0 && parse[0] == "Inc") { // Parfois dénomination dans copyright commence par Inc
					parse.erase(parse.begin());
				}

				for (int i = 0; i < parse.size(); i++) {
					if (parse[i] != "author") {
						if (parse[i] != "as" && parse[i] != "from" && parse[i] != "Modified" && parse[i] != "This" && parse[i] != "or" && parse[i] != "with" && parse[i] != "Based") {
							if (!numberMorePresent(parse[i], 0.80)) { // Fait le choix de ne pas prendre les copyrights sans date pour ne pas récupérer des pavets de texte
								if (poss == "")
									poss = parse[i];
								else
									poss += " " + parse[i];
							}
							else
								niceCopy = true;
						}
						else
							break;
					}
				}

				if (poss.size() > 2 && niceCopy && poss != "Inc"  && poss != "Ltd" && poss != "All" && poss != "others") {
					if (author != -1)
						denom[poss].insert(author);
					else
						denom[poss];

				}
			}
		}
		else if (pos != -1) {

			line = line.substr(pos);
			lastPos = pos;
			anouncer = true;

			if (line == "")
				soloAnouncer = true;

			for (int i = 0; i < noises.size(); i++) {
				int pos = line.find(noises[i]);
				if (pos != -1) {
					line = deleteWord(line, noises[i]);
				}
			}

			std::vector<std::string> groups = isolateParenth(line);

			for (std::string& s : groups) {
				for (char& c : chs)
					s = replaceChar(s, c, ' ');
			}

			for (char& c : chs)
				line = replaceChar(line, c, ' ');

			std::vector<std::string> tempPossibilities, possibilities;

			tempPossibilities = split(line, chsDelimiter);

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " for "))

					if (s2.find("source code") != -1)
						break;
					else
						possibilities.push_back(s2);
			}

			tempPossibilities = possibilities;
			possibilities.clear();

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " on behalf of "))
					possibilities.push_back(s2);
			}

			tempPossibilities = possibilities;
			possibilities.clear();

			for (std::string s : tempPossibilities) {
				for (std::string s2 : split(s, " and "))
					possibilities.push_back(s2);
			}

			if (possibilities.size() == 1)
				possibilities = split(possibilities[0], " - ");

			for (std::string& s : groups) {
				for (std::string s2 : split(s, chsDelimiter))
					possibilities.push_back(s2);
			}

			for (std::string& poss : possibilities) {

				std::vector<std::string> parse;
				parse = split(poss, " ");
				poss = "";

				for (int i = 0; i < parse.size(); i++) {
					if (parse[i] != "author") {
						if (parse[i] != "as" && parse[i] != "from" && parse[i] != "Modified" && parse[i] != "This" && parse[i] != "or" && parse[i] != "with") {
							if (!numberMorePresent(parse[i], 0.80)) { // Fait le choix de ne pas prendre les copyrights sans date pour ne pas récupérer des pavets de texte
								if (poss == "")
									poss = parse[i];
								else
									poss += " " + parse[i];
							}
						}
						else
							break;
					}
				}

				if (poss.size() > 2 && poss != "Inc" && poss != "Ltd" && poss != "others") {
					if (author != -1)
						denom[poss].insert(author);
					else
						denom[poss];

				}
			}
		}
		else if (anouncer && posCopy == -1 && pos == -1) {
			std::string tempLine = line;
			for (char& c : chs)
				tempLine = replaceChar(tempLine, c, ' ');
			bool ok = true;
			for (int i = 0; i < lastPos; i++) {
				if (tempLine[i] != ' ') {
					ok = false;
					break;
				}
			}
			if (ok || soloAnouncer) {

				std::vector<std::string> groups = isolateParenth(line);

				for (std::string& s : groups) {
					for (char& c : chs)
						s = replaceChar(s, c, ' ');
				}

				for (char& c : chs)
					line = replaceChar(line, c, ' ');

				std::vector<std::string> tempPossibilities, possibilities;

				tempPossibilities = split(line, chsDelimiter);

				for (std::string s : tempPossibilities) {
					for (std::string s2 : split(s, " for "))

						if (s2.find("source code") != -1)
							break;
						else
							possibilities.push_back(s2);
				}

				tempPossibilities = possibilities;
				possibilities.clear();

				for (std::string s : tempPossibilities) {
					for (std::string s2 : split(s, " on behalf of "))
						possibilities.push_back(s2);
				}

				tempPossibilities = possibilities;
				possibilities.clear();

				for (std::string s : tempPossibilities) {
					for (std::string s2 : split(s, " and "))
						possibilities.push_back(s2);
				}

				if (possibilities.size() == 1)
					possibilities = split(possibilities[0], " - ");

				for (std::string& s : groups) {
					for (std::string s2 : split(s, chsDelimiter))
						possibilities.push_back(s2);
				}

				for (std::string& poss : possibilities) {

					std::vector<std::string> parse;
					parse = split(poss, " ");
					poss = "";

					for (int i = 0; i < parse.size(); i++) {
						if (parse[i] != "author") {
							if (parse[i] != "as" && parse[i] != "from" && parse[i] != "Modified" && parse[i] != "This" && parse[i] != "or" && parse[i] != "with") {
								if (!numberMorePresent(parse[i], 0.80)) { // Fait le choix de ne pas prendre les copyrights sans date pour ne pas récupérer des pavets de texte
									if (poss == "")
										poss = parse[i];
									else
										poss += " " + parse[i];
								}
							}
							else
								break;
						}
					}

					if (poss.size() > 2 && poss != "Inc" && poss != "Ltd" && poss != "others") {
						if (author != -1)
							denom[poss].insert(author);
						else
							denom[poss];

					}
				}
				soloAnouncer = false;
			}
			else
				anouncer = false;
		}


		indexLine++;
	}

	//denom->erase("Inc");
	//denom->erase("inc");
	//denom->erase("Ltd");
	//denom->erase("and");

	//for (std::pair<std::string, std::set<unsigned int>> s : denom) {
	//	std::cout << s.first << " : ";
	//	if(s.second.size() > 0)
	//		for (unsigned int i : s.second)
	//			std::cout << i << ", ";
	//	std::cout << "\n";
	//}

	//std::cout << "" << std::endl;
}

void Header::countChars() {
	std::map<char, int> chars;
	char c;
	for (int i = 0; i < headerComment.size(); i++) {
		c = headerComment[i];
		if (chars.find(c) != chars.end())
			chars[c]++;
		else
			chars.insert({ c,1 });
	}

	std::map<char, int>::iterator p;
	char morePresentChar;
	int count = 0;
	for (p = chars.begin(); p != chars.end(); p++) {
		if (p->first != ' ' && p->first != '\n' && p->first != '\t' && p->second > count) {
			morePresentChar = p->first;
			count = p->second;
		}
	}

	if (morePresentChar == '*' || morePresentChar == '-' || morePresentChar == '_')
		std::cout << "Il y a sans doute la presence de separateurs : " << morePresentChar << "." << std::endl;
	else
		std::cout << "Pas de separateur ou caractere pas pris en compte : " << morePresentChar << std::endl;
}

void Header::freeMemories()
{
	headerComment = "";
	mailAddress.clear();
	webAddress.clear();
}

void Header::findCustomMailAddress() {

	//int i = 0;
	//bool between = false;
	//std::string mem;

	//std::string code = headerComment;
	//for (auto& c : code) c = toupper(c);

	//while (i < code.size()) {

	//	if (code[i] == '<') {
	//		between = true;
	//	}
	//	else if (code[i] == '>' && between) { // Vérifier que jamais d'infos autre que mail address dans <....>

	//		if (std::find(mailAddress.begin(), mailAddress.end(), mem) == mailAddress.end() && (stringInString(mem, "@") || stringInString(mem, "AT")))
	//			mailAddress.push_back(mem);

	//		mem = "";
	//		between = false;
	//	}
	//	else if (between) {
	//		mem += code[i];
	//	}
	//	else {
	//		if (mem.size() > 0)
	//			mem = "";
	//	}

	//	i++;
	//}
}

/*	if (posName != 0xffffffffffffffff) {
		name = tempHeader.substr(posName);
		name = name.substr(0, name.find('\n') + 1);
		std::cout << "NAME : " <<  name << std::endl;
	}

	withStars = true;
	int pos = 0;


	tempHeader2 = tempHeader;

	if (posLicense != 0xffffffffffffffff) {
		tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);
	}

	tempHeader2 = tempHeader;
	pos = tempHeader2.find('/*');

	if (pos != 0xffffffffffffffff) {

		tempHeader2 = tempHeader2.substr(tempHeader2.find('/*'));

		while (tempHeader2.size() > 0 && withStars) {
			std::string ligne = tempHeader2.substr(0, tempHeader2.find('\n'));

			int i = 0;
			while (i < ligne.size()) {
				char c = ligne[i];
				if (ligne.size() > i + 1 && ligne[i] == '/' && ligne[i + 1] == '*') {
					break;
				}
				else if (ligne[i] == '*') {
					break;
				}
				else if (ligne[i] != ' ' && ligne[i] != '\t' && ligne[i] != '\n') {
					withStars = false;
					break;
				}

				i++;
			}

			tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);
		}
	}
	else
		withStars = false;

	tempHeader2 = tempHeader;

	if (posLicense != 0xffffffffffffffff) {
		tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);
	}

	withSimpleCommentLine = true;

	while (tempHeader2.size() > 0 && withSimpleCommentLine) {
		std::string ligne = tempHeader2.substr(0, tempHeader2.find('\n'));

		int i = 0;
		while (i < ligne.size()) {

			if (ligne.size() > i + 1 && ligne[i] == '/' && ligne[i+1] == '/') {
				break;
			}
			else if (ligne[i] != ' ' && ligne[i] != '\t') {
				withSimpleCommentLine = false;
				break;
			}
			i++;
		}

		tempHeader2 = tempHeader2.substr(tempHeader2.find('\n') + 1);
	}

	if (withStars)
		std::cout << "Header written with full star at the beginning of the lines" << std::endl;
	else if (withSimpleCommentLine)
		std::cout << "Header written with full simpleCommentLine at the beginning of the lines" << std::endl;
	else
		std::cout << "Header haven't specific format" << std::endl;

	tempHeader2 = tempHeader;

	while (tempHeader2.size() > 0) {

		std::string line = tempHeader2.substr(0, tempHeader2.find('\n'));

		for (std::string ad : mailAddress) { // Il y a les doublons d'adresse mail
			if (stringInString(line, ad))
			{

				int pos = line.find(" BY");

				if(pos != 0xffffffffffffffff)
					line = line.substr(pos+3);

				parse = split(line, " ");
				line = "";

				for (int i = 0; i < parse.size(); i++) {
					std::string temp = deleteChar(deleteChar(deleteChar(deleteChar(parse.at(i),'<'),'>'),'('),')');
					temp = deleteChar(deleteChar(temp, '('),')');
					if (!numberMorePresent(parse.at(i), 0.75) || ad == temp) {
						line += parse.at(i) + ' ';
						// tempMailAddress.erase(tempMailAddress.begin());
					}
				}

				line = deleteWord(line, "AUTHOR");
				line = deleteWord(line, "COPYRIGHT");
				line = deleteWord(line, "(S)");
				line = deleteWord(line, ":");
				line = deleteWord(line, "(C)");
				line = deleteWord(line, "*");
				line = deleteWord(line, ",");
				line = deleteWord(line, "\t");
				line = deleteWord(line, "//");

				std::cout << "ADDRESS LINE : " <<  line << std::endl;

			}
		}

		tempHeader2 = tempHeader2.substr(tempHeader2.find('\n')+1);
	}

	for (std::string s : mailAddress)
		std::cout << "Address Email : " << s << std::endl;

	// countChars();*/