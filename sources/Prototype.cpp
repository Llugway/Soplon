#include "Prototype.h"

Prototype::Prototype() {

}

bool isUpperCase(char c) { // Peut ne pas etre la
    return (65 <= c && 90 >= c);
}

void Prototype::setUp() {

    bool recordName = false;
    std::string name = "";

    for (int i = 0; i < proto.size(); i++) {
        if (proto[i] == ' ') 
            recordName = true;
        else if (proto[i] == '(') 
            break;
        else if (recordName) 
            name += proto[i];
        else 
            type += proto[i];
    }

    firstCharUpperCase = isUpperCase(name[0]);

    countUpper = 0;
    countUnderscore = 0;

    for (int i = 0; i < name.size(); i++) {
        if (name[i] == '_')
            countUnderscore++;
        else if (isUpperCase(name[i]))
            countUpper++;
    }

    underscoreIsPresent = (countUnderscore > 0);
    upperIsPresent = (countUpper > 0);
    fullUpper = (countUpper == name.size());

    /* DETERMINER LES MODELES */
     

    // ************************ AVEC UNDERSCORE *************************************** // 
    /*

    vector<string> parseUnderscore = split(name, "_");

    string prefixe;
    string suffixe;

    bool* Uppers = (bool*)malloc(parseUnderscore.size());
    for (int i = 0; i < parseUnderscore.size(); i++) {
        *(Uppers+i) = true;
    }

    for (int i = 0; i < parseUnderscore.size();i++) {;
        string s = parseUnderscore.at(i);
        for (int j = 0; j < s.size(); j++) {
            if (!isUpperCase(s[j])) {
                Uppers[i] = false;
                break;
            }
        }

        if (fullUpper && i == 0) {
            prefixe 
        }

    }

    */

    /* *********************************** Parse MAJUSCULE ***********************************************/

  /*  bool* uppers = (bool*)malloc(name.size());

    for (int i = 0; i < name.size(); i++) {
        uppers[i] = isUpperCase(name[i]);
    }

    vector<string> stringUpper;

    int i = 0;
    string s = "";
    while (i < name.size()) {
        if (uppers[i])
            s += name[i];
        else{
            if (s.size() > 0)
                stringUpper.push_back(s);
            s = "";
        }
    }*/

    // Si mot de 1 caractère : sans doute majuscule au debut chaque mot
    // si mot de 2 char+ : prefixe, suffixe, accronime
}

std::string Prototype::getPrototype() {
    return proto;
}

void Prototype::setPrototype(std::string p) {
    this->proto = p;
}


void Prototype::setType(std::string t) {
    type = t;
}

std::string Prototype::getType() {
    return type;
}

bool Prototype::getFirstCharUpperCase() {
    return firstCharUpperCase;
}

void Prototype::setFirstCharUpperCase(bool b) {
    firstCharUpperCase = b;
}

bool Prototype::getUpperIsPresent() {
    return upperIsPresent;
}

void Prototype::setUpperIsPresent(bool b) {
    upperIsPresent = b;
}
