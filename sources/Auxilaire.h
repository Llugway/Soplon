#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <math.h>
#include<set>


static bool sortC(int i, int j) { return (i < j); }

static bool isNumber(const std::string& str)
{
    for (char const& c : str) {
        //std::cout << c << std::endl;
        //std::cout << (int)c << std::endl;
        try {
            //if (c < -1 || c > 255) return false;
            if (std::isdigit(c) == 0) return false;
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            return false;
        }

    }
    return true;
}

static std::string cleanDenom(std::string s) {
    while (s.size() >= 1 && (s[0] == '"' || s[0] == '/' || s[0] == ' ' || s[0] == '.' || s[0] == ')' || s[0] == '=' || s[0] == '$')) {
        s = s.substr(1);
    }
    while (s.size() >= 1 && (s[s.length()-1] == '"' || s[s.length() - 1] == '/' || s[s.length() - 1] == ' ' || s[s.length() - 1] == '.' || s[s.length() - 1] == ')' || s[s.length() - 1] == '$')) {
        s = s.substr(0,s.size()-1);
    }
    return s;
}


static uint64_t calculHash(std::string s, int length) {
    uint64_t res = 0;

    for (int m = 0; m < length; m++) {
        res += pow(s[m],m);
    }

    return res;
}

static uint64_t newCalculHash(std::string s,int index, int prime, uint64_t hash) {
    hash = hash - s[index];
    hash = hash / prime;
    int m = 4;
    hash = hash + pow(s[index+m], m - 1);
    return hash;

}

static std::set<uint64_t> getPatternHash(std::string s,int prime,int length) {
    std::set<uint64_t> ret;
    if (s.size() > 3) {
        uint64_t p = calculHash(s, 4);
        int index = 0;
        while (index + 4 < s.size()) {
            ret.insert(p);
            p = newCalculHash(s, index, prime, p);
            index++;
        }
    }
    
    return ret;
}

static std::vector<std::string> split(const std::string& str, const std::string& delim) // func auxiliaire
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

static std::vector<std::string> split(const std::string& str, const std::vector<char>& delim) // func auxiliaire
{
    std::vector<std::string> tokens;
    std::string current = "";
    unsigned int i = 0;
    while (i < str.size()) {
        bool isDelim = false;
        for (const char &c : delim) {
            if (c == str[i]){
                isDelim = true;
                break;
            }
        }

        if (!isDelim)
            current += str[i];
        else {
            if(current != "")
                tokens.push_back(current);
            current = "";
        }

        i++;
    }

    if(current != "")
        tokens.push_back(current);

    return tokens;
}

static std::string deleteChar(std::string s, char c) {
    std::string res = "";

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != c)
            res += s[i];
    }

    return res;
}

static bool isAlphaWord(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        if (iswalpha(s[i]))
            return true;
    }
    return false;
}

static std::vector<std::string> isolateParenth(std::string & s) {

    std::vector<std::string> tokens;

    unsigned int i = 0;

    char previousDelim;
    unsigned int startDelim = 0;
    bool delimiter = false;

    while (i < s.size()) {

        if (s[i] == '(' || s[i] == '{' || s[i] == '[' || s[i] == '<'){
            previousDelim = s[i];
            startDelim = i;
            delimiter = true;
        }
        else if (delimiter && ((s[i] == ')' && previousDelim == '(') || (s[i] == '}' && previousDelim == '{') ||( s[i] == ']' && previousDelim == '[') || (s[i] == '>' && previousDelim == '<'))) {
            std::string token;
            
            if (startDelim + 1 < i - 1){

                for (unsigned int ind = startDelim + 1; ind < i; ind++)
                    token += s[ind];
            }
            else
                token = "";   

            if (token != "") {
                s = s.substr(0, startDelim) + s.substr(i+1);
                tokens.push_back(token);
                previousDelim = ' ';
                startDelim = 0;
                i = 0;
                delimiter = false;
            }
                   
        }

        i++;
    }

    return tokens;
}

static std::string deleteBetweenDelimiters(std::string s) { // () [] <> ; Pk pas {} ?
    int i = 0;
    char delimiter;
    bool skip = false;
    std::string result = "";
    while (i < s.size()){
        if ((s[i] == '(' || s[i] == '[' || s[i] == '<') && !skip) {
            skip = true;
            delimiter = s[i];
        }
        else if (!skip)
            result += s[i];
        else if ((delimiter == '(' && s[i] == ')') || (delimiter == '[' && s[i] == ']') || (delimiter == '<' && s[i] == '>'))
            skip = false; 

        i++;
    }
    return result;
}

static bool atLeastOneUpper(const std::string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 65 && s[i] <= 90)
            return true;
    }
    return false;
}

static std::string deleteChars(std::string s, std::vector<char> chars) {
    std::string res = "";
    bool isAvailable = true;

    for (int i = 0; i < s.size(); i++) {
        if (!isAvailable)
            isAvailable = true;
        for(char c : chars)
            if (c == s[i]) {
                isAvailable = false;
                break;
            }

        if (isAvailable)
            res += s[i];
    }

    return res;
}


static std::string replaceChar(std::string s, char oldChar, char newChar) {
    std::string result = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != oldChar)
            result += s[i];
        else
            result += newChar;
    }
    return result;
}

static std::string deleteWord(std::string s, std::string word) {

    int i = 0;
    int indexW = 0;

    int size = word.length();

    std::string mem = "";
    std::string result = "";

    while (i < s.size()) {

        if (s[i+indexW] == word[indexW]) {
            mem += s[i + indexW];
            indexW++;
        }
        else {
            result += mem;
            if(i+indexW != s.size())
                result += s[i + indexW];
            i += indexW + 1;
            mem = "";
            if (indexW != 0)
                indexW = 0;
        }

        if (indexW == word.length()) {
            i = i + indexW;
            mem = "";
            indexW = 0;
        }
    }
    return result;
}

static std::string replaceWord(std::string s, std::string word, std::string replace) {

    int i = 0;
    int indexW = 0;

    std::string mem = "";
    std::string result = "";

    while (i < s.size()) {

        if (s[i + indexW] == word[indexW]) {
            mem += s[i + indexW];
            indexW++;
        }
        else if (mem.length() != 0){
            result += mem;         
            i += indexW;
            mem = "";     
            indexW = 0;
        }
        else {

            if (i + indexW != s.size())
                result += s[i + indexW];

            i += 1;
        }

        if (indexW == word.size()) {
            i = i + indexW;
            mem = "";
            indexW = 0;
            result += replace;
        }
    }
    return result;
}

static bool stringInString(std::string s, std::string word) {

    int i = 0;
    int indexW = 0;

    while (i < s.size()) {

        if (s[i + indexW] == word[indexW]) {
            indexW++;
        }
        else {
            i += indexW + 1;
            if (indexW != 0)
                indexW = 0;
        }

        if (indexW == word.size()) {
            return true;
        }
    }

    return false;

}

static bool numberMorePresent(std::string s, float seuil) {
    int nbNumbers = 0;
    int nbChars = s.size();

    for (int i = 0; i < nbChars; i++) {
        if ((47 < s[i] && s[i] < 58))
            nbNumbers++;
    }

    return ((float)nbNumbers / (float)nbChars) >= seuil;
}
static bool letterMorePresent(std::string s, float seuil) {
    int nbLetters = 0;
    int nbChars = s.size();

    for (int i = 0; i < nbChars; i++) {
        if (65 <= s[i] && s[i] < 91)
            nbLetters++;
    }

    return ((float)nbLetters / (float)nbChars) >= seuil;
}

static bool charInString(std::string s, char c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c)
            return true;
    }
    return false;
}

static std::string deleteCommentBlock(std::string s) { // Doit prendre ne compte les commentaire sur une ligne
                                                       // Peut etre source de bug si commentaire sur 2 lignes
    std::string result = "";
    bool writte = true;
    bool begin = false;
    bool end = false;
    for (int i = 0;  i < s.size(); i++) {

        if (begin && s[i] == '*') {
            writte = false;
            begin = false;
        }

        else if (s[i] == '/' && end) {
            writte = true;
            end = false;
        }
        else if (s[i] == '/' && !begin && !end) {
            begin = true;
        }
        else if (s[i] == '*' && !begin && !end) {
            end = true;
        }
        else if (writte){ // N'écrit pas le premier caractère si /[DeuxièmeChar]
            result += s[i];
        }
        else {
            if (begin)
                begin = false;
            if (end)
                end = false;
        }
    }
    return result;
}

static std::string deleteTab(std::string s) { // Doit prendre ne compte les commentaire sur une ligne
                                                       // Peut etre source de bug si commentaire sur 2 lignes
    std::string result = "";

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '\t') {
            result += s[i];
        }

    }
    return result;
}

static std::string execute(std::string sentence)
{
    std::string file_name = "result.txt";
    sentence = replaceChar(sentence, '\n', ' ');
    sentence = replaceChar(sentence, '\t', ' ');
    sentence = replaceChar(sentence, ')', ' ');
    sentence = replaceChar(sentence, '(', ' ');
    sentence = replaceChar(sentence, ',', ' ');

    std::vector<char> del;
    del.push_back('+');
    del.push_back('{');
    del.push_back('}');
    del.push_back(';');
    del.push_back('=');
    del.push_back('!');
    del.push_back('<');
    del.push_back('+');
    del.push_back('>');
    del.push_back('|');
    del.push_back('-');
    del.push_back('&');
    del.push_back('*');

    sentence = deleteChars(sentence, del);
 

    std::vector<std::string>parse = split(sentence," ");
    sentence = "";
    for (std::string s : parse) {
        sentence += s + '+';
    }
    sentence = sentence.substr(0, sentence.size() - 1);
    std::cout << sentence << std::endl;
    std::string command = "curl -s https://ws.detectlanguage.com/0.2/detect -H \"Authorization: Bearer a4c8a5a58b27ee0710c8c7a1f53248f2\" -d q=" + sentence + " > " + file_name;
    std::system((command).c_str()); // redirect output to file
    // open file for input, return string containing characters in the file
    std::ifstream file(file_name);

    std::string ligne; //Une variable pour stocker les lignes lues
    std::string ret;
    while (getline(file, ligne)) //Tant qu'on n'est pas à la fin, on lit
    {
        ret += ligne + ' ' ;
    }
    //std::string  ret = { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() }; // Ne récupérer que la première occurrence
    // remove(file_name.c_str());
    return ret;
}

static std::vector<std::string> parseJSONToLanguage(std::string json) {

    std::vector<std::string> languages;

    int pos = json.find("language") + 11;

    while (pos != 0xffffffff && json.size() > pos) {
        json = json.substr(pos);
        std::string language = json.substr(0, json.find('"'));
        languages.push_back(language);
        pos = json.find("language");
        if(pos != 0xffffffff)
            pos += 11;
    }

    return languages;
}

static std::string languageEquivalent(std::string l) {
    if (l == "en")
        return "English";
    else if (l == "ru")
        return "Russian";
    else if (l == "th")
        return "Thai";
    else if (l == "el")
        return "Greek";
    else if (l == "de")
        return "German";
    else if (l == "ga")
        return "Irish";
    else if (l == "lb")
        return "Luxembourgish";
    else if (l == "nl")
        return "Dutch";
    else if (l == "wo")
        return "Wolof";
    else if (l == "eg")
        return "Egyptian";
    else if (l == "ko")
        return "Korean";
    else if (l == "fr")
        return "French";
    else if (l == "la")
        return "Latin";
    else if (l == "pt")
        return "Portuguese";
    else
        return "Unknow";
}

/*
struct+Scsi_Host+aha152x_probe_one+struct+aha152x_setup+setup+struct+Scsi_Host+shpnt+shpnt+scsi_host_alloc+aha152x_driver_template+sizeof+struct+aha152x_hostdata+if+shpnt+printk+KERN_ERR
+"aha152x:+scsi_host_alloc+failed\n"+return+NULL+memset+HOSTDATA+shpnt+0+sizeof+HOSTDATA+shpnt+INIT_LIST_HEAD+HOSTDATA+shpnt+host_list+/+need+to+have+host+registered+before+triggering+any+interrupt+
/+list_add_tail+HOSTDATA+shpnt+host_list+aha152x_host_list+shpntio_port+setupio_port+shpntn_io_port+IO_RANGE+shpntirq+setupirq+if+setuptc1550+HOSTIOPORT0+setupio_port+HOSTIOPORT1+setupio_port+else+HOSTIOPORT0+
setupio_port0x10+HOSTIOPORT1+setupio_port0x10+spin_lock_init+QLOCK+RECONNECT+setupreconnect+SYNCHRONOUS+setupsynchronous+PARITY+setupparity+DELAY+setupdelay+EXT_TRANS+setupext_trans+SETPORT+SCSIID+setupscsiid+4
+shpntthis_id+setupscsiid+if+setupreconnect+shpntcan_queue+AHA152X_MAXQUEUE+/+RESET+OUT+/+printk+"aha152x:+resetting+bus...\n"+SETPORT+SCSISEQ+SCSIRSTO+mdelay+256+SETPORT+SCSISEQ+0+mdelay+DELAY+reset_ports
+shpnt+printk+KERN_INFO+"aha152x%d%s:+"+"vital+data:+rev%x+"+"io0x%03lx+0x%03lx/0x%03lx+"+"irq%d+"+"scsiid%d+"+"reconnect%s+"+"parity%s+"+"synchronous%s+"+"delay%d+"+"extended+translation%s\n"+shpnthost_no+setuptc1550+?+"
+tc1550+mode+"+:+""+GETPORT+REV+0x7+shpntio_port+HOSTIOPORT0+HOSTIOPORT1+shpntirq+shpntthis_id+RECONNECT+?+"enabled"+:+"disabled"+PARITY+?+"enabled"+:+"disabled"+SYNCHRONOUS+?+"enabled"+:+"disabled"+DELAY+EXT_TRANS+?+"enabled"+:+"disabled"
+/+not+expecting+any+interrupts+/+SETPORT+SIMODE0+0+SETPORT+SIMODE1+0+if+request_irq+shpntirq+swintr+IRQF_SHARED+"aha152x"+shpnt+printk+KERN_ERR+"aha152x%d:+irq+%d+busy.\n"+shpnthost_no+shpntirq+goto+out_host_put+HOSTDATA+shpnt+swint+0+printk
+KERN_INFO+"aha152x%d:+trying+software+interrupt+"+shpnthost_no+mb+SETPORT+DMACNTRL0+SWINTINTEN+mdelay+1000+free_irq+shpntirq+shpnt+if+HOSTDATA+shpnt+swint+if+TESTHI+DMASTAT+INTSTAT+printk+"lost.\n"+else+printk+"failed.\n"+SETPORT+DMACNTRL0
+INTEN+printk+KERN_ERR+"aha152x%d:+irq+%d+possibly+wrong.+"+"Please+verify.\n"+shpnthost_no+shpntirq+goto+out_host_put+printk+"ok.\n"+/+clear+interrupts+/+SETPORT+SSTAT0+0x7f+SETPORT+SSTAT1+0xef+if+request_irq+shpntirq+intr+IRQF_SHARED+"aha152x"
+shpnt+printk+KERN_ERR+"aha152x%d:+failed+to+reassign+irq+%d.\n"+shpnthost_no+shpntirq+goto+out_host_put+if+scsi_add_host+shpnt+NULL+free_irq+shpntirq+shpnt+printk+KERN_ERR+"aha152x%d:+failed+to+add+host.\n"+shpnthost_no+goto+out_host_put
+scsi_scan_host+shpnt+return+shpnt+out_host_put:+list_del+HOSTDATA+shpnt+host_list+scsi_host_put+shpnt+return+NULL
*/