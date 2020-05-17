#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>

using namespace std;

void loadInitialSymbols(map<string, int>&);
void loadCompTable(map<string, string>&);
void loadDestTable(map<string, string>&);
void loadJumpTable(map<string, string>&);
string shortToBinary(unsigned short);
bool isAInstruction(string);
string parseAInstruction(string);


#endif // PARSER_H
