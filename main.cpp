#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "Parser.h"

using namespace std;

//Function forward declarations
void removeWhitespace(vector<string>&);
void removeBlankLines(vector<string>&);
void saveToFile(const string, const vector<string>&);
string getFileNameNoExt(const string);

int main(int argc, char **argv){
    //Read source code file and clean it of whitespace/comments
    if(argc != 2) return 0;
    ifstream sourceCode(argv[1]);
    vector<string> lines;
    string buffer;
    while(getline(sourceCode, buffer)){
        lines.push_back(buffer);
    }
    sourceCode.close();
    removeWhitespace(lines);
    removeBlankLines(lines);

    //Load data into all the look up tables
    map<string, int> symbolTable;
    map<string, string> CompTable;
    map<string, string> DestTable;
    map<string, string> JumpTable;
    loadInitialSymbols(symbolTable);
    loadCompTable(CompTable);
    loadDestTable(DestTable);
    loadJumpTable(JumpTable);

    //First pass to find and mark labels
    firstPass(lines, symbolTable);

    //Parse assembly file
    vector<string> parsed = parseLines(lines, DestTable, CompTable, JumpTable, symbolTable);

    //save parsed result as <filename.hack>
    saveToFile(getFileNameNoExt(argv[1]) + ".hack", parsed);
    return 0;
}

//Removes tabs, spaces, and ignores comments by modifying the given reference
void removeWhitespace(vector<string> &lines){
    for(int i = 0; i < lines.size(); i++){
        string cleanedString = "";
        for(int j = 0; j < lines[i].size(); j++){
            char c = lines[i][j];
            //Ignore comments and move to next line
            if(c == '/' and j < lines[i].size()-1 and lines[i][j+1] == '/')
                break;
            //Pass over tabs and spaces
            if(c != '\t' and c != ' ')
                cleanedString += c;
        }
        lines[i] = cleanedString;
    }
}

//Remove blank lines by modifying the given reference
void removeBlankLines(vector<string> &lines){
    typedef vector<string>::iterator iter;
    for(iter it = lines.begin(); it < lines.end(); it++){
        if(*it == "")
            lines.erase(it--);
    }
}

//Save contents of lines to a file with the specified filename
void saveToFile(const string filename, const vector<string> &lines){
    ofstream file(filename);
    for(const string line : lines){
        file << line << '\n';
    }
    file.close();
}

//Gets files base name (Ex. Max.asm -> Max)
string getFileNameNoExt(const string fullName){
    return fullName.substr(0, fullName.size()-4);
}
