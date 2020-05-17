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
    cout << parseAInstruction("@7948") << endl;

    //Load data into all the look up tables
    map<string, int> symbolTable;
    map<string, string> CompTable;
    map<string, string> DestTable;
    map<string, string> JumpTable;
    loadInitialSymbols(symbolTable);
    loadCompTable(CompTable);
    loadDestTable(DestTable);
    loadJumpTable(JumpTable);
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
