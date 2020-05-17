#include "Parser.h"

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

//Returns true if the given line is an A instruction
bool isAInstruction(const string &line){
    return (line.size() and line[0] == '@');
}

//Parse the given line as an A instruction
string parseAInstruction(string line){
    line.erase(line.begin());
    int value = stoi(line);
    return shortToBinary(value);
}

//Parse the given line as a C instruction
string parseCInstruction(string line,
                         const map<string, string> &destTable,
                         const map<string, string> &compTable,
                         const map<string, string> &jumpTable){
    string result = "111";
    string dest = "", comp = "", jmp = "";
    size_t equalChar = line.find('=');
    size_t semiColonChar = line.find(';');

    //Parse out each field if they exist
    if(equalChar != string::npos and semiColonChar != string::npos){
        comp = line.substr(equalChar+1, semiColonChar - equalChar - 1);
        dest = line.substr(0, equalChar);
        jmp = line.substr(semiColonChar+1);
    }
    else if(equalChar != string::npos){
        comp = line.substr(equalChar+1);
        dest = line.substr(0, equalChar);
    }
    else if(semiColonChar != string::npos){
        comp = line.substr(0, semiColonChar);
        jmp = line.substr(semiColonChar+1);
    }
    else{
        comp = line;
    }

    cout << dest << endl;
    cout << comp << endl;
    cout << jmp  << endl;
    //compile binary instruction
    result += compTable.find(comp)->second;
    result += (dest == "")? "000": destTable.find(dest)->second;
    result += (jmp  == "")? "000": jumpTable.find( jmp)->second;
    return result;
}








