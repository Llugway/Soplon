#include "Function.h"

Function::Function()
{
    header = "";
    prototype = new Prototype();
}

Function::~Function()
{

}

float Function::getCommentsPercentages()
{
	return commentsPercentages;
}

bool Function::getWithHeader()
{
	return withHeader;
}

std::string Function::getCode()
{
	return code;
}

void Function::setCommentsPercentages(float per)
{
	this->commentsPercentages = per;
}
void Function::setWithHeader(bool header)
{
	this->withHeader = header;
}
void Function::setCode(std::string code)
{
    this->code = code;
}

void Function::setPrototype(std::string s) {
    this->prototype->setPrototype(s);
}

void Function::setHeader(std::string h)
{
    header = h;

    int i = 0;
    int nbLine = 1;
    while (i < h.size()) {
        if (h[i] == '\n')
            nbLine++;
        i++;
    }
    nbLineHeader = nbLine;
}

std::string Function::getPrototype() {
    return prototype->getPrototype();
}

std::string Function::getHeader()
{
    return header;
}

int Function::getNbLineHeader() {
    return nbLineHeader;
}


void Function::calculatePercentages() {

    int NbChar = code.size(); // Compte les retours à la ligne
    int nbCharComment = 0;

    bool skip = false;
    bool charSpecial = false;
    char skipChar;

    int i = 0;
    while (i < code.size() - 1) {


        if (i - 1 >= 0 && code[i - 1] == '\\') {
            charSpecial = true;
            /*if (i - 2 >= 0)
                if (ligne[i - 2] == '\\')
                    charSpecial = false;*/
            int d = 2;
            while (i - d >= 0 && code[i - d] == '\\') {
                charSpecial = !charSpecial;
                d++;
            }
        }

        if (!skip && (code[i] == '"' ) && !charSpecial) {
            skip = true;
            skipChar = '"';
        }

        else if (!skip && (code[i] == 39) && !charSpecial ) {
            skip = true;
            skipChar = 39;
        }

        else if (skip && (code[i] == 39) && skipChar == 39 && !charSpecial ) {
            skip = false;
        }

        else if (skip && (code[i] == '"') && skipChar == '"' && !charSpecial) {
            skip = false;
        }

         if (code[i] == '/' && code[i + 1] == '/' && !skip) {
             nbCharComment += 2;
             i = i + 2;
             while (code[i] != '\n') {
                 nbCharComment++;
                 i++;
             }
         }
         else if (code[i] == '/' && code[i + 1] == '*' && !skip) {
             char c1, c2;
             nbCharComment += 2;
             i = i + 2;
             while (code[i] != '*' && code[i + 1] != '/') {
                 c1 = code[i];
                 c2 = code[i + 1];
                 nbCharComment++;
                 i++;
             }
             nbCharComment += 2;
             i += 2;
         }
         i++;
     }

    commentsPercentages = ((float)nbCharComment / (float)NbChar)*100.0;
}


void Function::analysePrototype() {
    prototype->setUp();
}

void Function::setUpFunction() {
    calculatePercentages();
    analysePrototype();
    setComments();
    findLanguage();
}

void Function::setComments() {
    bool skip = false;
    bool commentBlock = false;
    bool commentLine = false;
    bool charSpecial = false;
    char skipChar= ' ';

    for (int i = 0; i < code.size(); i++) {
        char c = code[i];

        if (i - 1 >= 0 && code[i - 1] == '\\') {
            charSpecial = true;
            int d = 2;
            while (i - d >= 0 && code[i - d] == '\\') {
                charSpecial = !charSpecial;
                d++;
            }
        }

        if (code[i] == '\n' && commentLine) {
            commentLine = false;
            comments += '\n';
        }
        else if ((code[i] == '"' || code[i] == '\'') && !skip && !commentBlock && !charSpecial) {
            skip = true;
            skipChar = code[i];
        }
        else if (code[i] == skipChar && skip && !commentBlock && !charSpecial) { // Doit prendre en compte les caractères spéciaux
            skip = false;
            skipChar = ' ';
        }
        else if (code.size() > i +1 && code[i] == '/' && code[i+1] == '/' && !skip && !charSpecial) {
            commentLine = true;
            i++;
        }
        else if (code.size() > i + 1 && code[i] == '/' && code[i + 1] == '*' && !skip && !charSpecial) {
            commentBlock = true;
            i++;
        }
        else if (code.size() > i + 1 && code[i] == '*' && code[i + 1] == '/' && !skip && !charSpecial) {
            commentBlock = false;
            comments += '\n';
            i++;
        }
        else if(commentBlock || commentLine) {
            if((code[i] != '*' && code[i] != '\t' && !skip))
                comments += code[i];
        }

        if (charSpecial)
            charSpecial = false;
    }
}

std::string Function::getComments() {
    return comments;
}

void Function::findLanguage() {
   /* std::cout << "Prototype : " << prototype->getPrototype() << endl;
    if(comments.size()>0){
        commentsLanguages =  parseJSONToLanguage(execute(comments));

        std::cout << "Langages des commentaires : ";
        for (std::string s : commentsLanguages)
            std::cout << s << "   ";
        std::cout << endl;
    }
    std::cout << endl;
    codeLanguages = parseJSONToLanguage(execute(code));
    std::cout << endl;

    std::cout << "Langages du code : ";
    for (std::string s : codeLanguages)
        std::cout << s + "   ";
    std::cout << endl;*/
}

std::vector<std::string> Function::getCommentsLanguages() {
    return commentsLanguages;
}
std::vector<std::string> Function::getCodeLanguages() {
    return codeLanguages;
}