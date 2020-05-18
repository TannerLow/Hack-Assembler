#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void loadInitialSymbols(map<string, int>&);
void loadCompTable(map<string, string>&);
void loadDestTable(map<string, string>&);
void loadJumpTable(map<string, string>&);
string shortToBinary(unsigned short);
bool isAInstruction(string);
string parseAInstruction(string, const map<string, int>&);
string parseAInstruction(string, map<string, int>&, int&);
string parseCInstruction(string,
                         const map<string, string>&,
                         const map<string, string>&,
                         const map<string, string>&);
vector<string> parseLines(vector<string>&,
                         const map<string, string>&,
                         const map<string, string>&,
                         const map<string, string>&,
                         map<string, int>&);
void firstPass(vector<string>&, map<string, int>&);


#endif // PARSER_H
