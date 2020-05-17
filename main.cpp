#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Function forward declarations
void loadInitialSymbols(map<string, int>&);
void loadCompTable(map<string, string>&);
void loadDestTable(map<string, string>&);
void loadJumpTable(map<string, string>&);
string shortToBinary(unsigned short);
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

//Loads default values per Hack assembly language specifications
void loadInitialSymbols(map<string, int> &table){
    table["R0" ] =  0;
    table["R1" ] =  1;
    table["R2" ] =  2;
    table["R3" ] =  3;
    table["R4" ] =  4;
    table["R5" ] =  5;
    table["R6" ] =  6;
    table["R7" ] =  7;
    table["R8" ] =  8;
    table["R9" ] =  9;
    table["R10"] = 10;
    table["R11"] = 11;
    table["R12"] = 12;
    table["R13"] = 13;
    table["R14"] = 14;
    table["R15"] = 15;
    table["SCREEN"] = 16384;
    table["KBD"]    = 24576;
    table["SP" ]  = 0;
    table["LCL"]  = 1;
    table["ARG"]  = 2;
    table["THIS"] = 3;
    table["THAT"] = 4;
}

//Loads C instruction conversions per Hack assembly language specifications(Comp table)
void loadCompTable(map<string, string> &table){
    table["0"]   = "0101010";
    table["1"]   = "0111111";
    table["D"]   = "0111010";
    table["A"]   = "0110000"; table["M"]   = "1110000";
    table["!D"]  = "0001101";
    table["!A"]  = "0110001"; table["!M"]  = "1110001";
    table["-D"]  = "0001111";
    table["-A"]  = "0110011"; table["-M"]  = "1110011";
    table["D+1"] = "0011111";
    table["A+1"] = "0110111"; table["M+1"] = "1110111";
    table["D-1"] = "0001110";
    table["A-1"] = "0110010"; table["M-1"] = "1110010";
    table["D+A"] = "0000010"; table["D+M"] = "1000010";
    table["D-A"] = "0010011"; table["D-M"] = "1010011";
    table["A-D"] = "0000111"; table["M-D"] = "1000111";
    table["D&A"] = "0000000"; table["D&M"] = "1000000";
    table["D|A"] = "0010101"; table["D|M"] = "1010101";
}

//Loads C instruction conversions per Hack assembly language specifications(Dest table)
void loadDestTable(map<string, string> &table){
    table["null"] = "000";
    table[   "M"] = "001";
    table[   "D"] = "010";
    table[  "MD"] = "011";
    table[   "A"] = "100";
    table[  "AM"] = "101";
    table[  "AD"] = "110";
    table[ "AMD"] = "111";
}

//Loads C instruction conversions per Hack assembly language specifications(Jump table)
void loadJumpTable(map<string, string> &table){
    table["null"] = "000";
    table[ "JGT"] = "001";
    table[ "JEQ"] = "010";
    table[ "JGE"] = "011";
    table[ "JLT"] = "100";
    table[ "JNE"] = "101";
    table[ "JLE"] = "110";
    table[ "JMP"] = "111";
}

/* Convert int into "binary" string of 0's and 1's.
 * Max result is a 15 bit string with 0 as the first bit.
 * 0-32767 */
string shortToBinary(unsigned short n){
    string result = "0000000000000000";
    if(n > 32767) return result;
    string::iterator sit = result.begin()+1;
    int term = 16384;
    while(n > 0){
        if(n >= term){
            *sit = '1';
            n -= term;
        }
        term /= 2;
        sit++;
    }
    return result;
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
