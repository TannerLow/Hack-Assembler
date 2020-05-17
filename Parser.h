#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

void loadInitialSymbols(map<string, int>&);
void loadCompTable(map<string, string>&);
void loadDestTable(map<string, string>&);
void loadJumpTable(map<string, string>&);
string shortToBinary(unsigned short);
bool isAInstruction(string);
string parseAInstruction(string);
string parseCInstruction(string,
                         const map<string, string>&,
                         const map<string, string>&,
                         const map<string, string>&);
vector<string> parseLines(vector<string>&,
                         const map<string, string>&,
                         const map<string, string>&,
                         const map<string, string>&);


#endif // PARSER_H
