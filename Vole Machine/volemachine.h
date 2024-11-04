
#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H
#include <bits/stdc++.h>
using namespace std;

class Alu {
protected:
    string hexToBinary(const string &hex);
    string binaryToHex(const string &binary);
    string signExtend(const string &binary, int length);
    string addBinaryTwosComplement(const string &bin1, const string &bin2);
    int hexToDecimal(const string &hex);
    string ORing(string binary1, string binary2);
    string ANDing(string binary1, string binary2);
    string XORing(string binary1, string binary2);
    void rotateRight(string &binary, int steps);
};

class Register {
    vector<string> bits;
public:
    Register();
    void setbit(string memvalue, int operand);
    string getbit(int operand);
    void printRegister();
};

class Memory {
protected:
    vector<string> cell;
public:
    Memory();
    void setcellinput(const string& input, int i2);
    void setcelladdress(int address, string operand_value);
    string getcell(int address);
    void printMemory();
};

class Instructions : public Alu {
public:
    void readInput(Memory& memory, vector<string>& commands, int i3);
    void executeStep(Memory& memory, Register& reg, int& index, vector<string>& commands, bool& isRunning, int& pc);
};

class Machine : public Memory , public Register {
    Memory memory;
    Register reg;
    Instructions instructions;
    vector<string> commands;
    bool isRunning;
    int index;

public:
    Machine();
    void setInput(string input, int i1);
    void execute(int i1);
    void printState();
};



#endif //VOLE_MACHINE_VOLEMACHINE_H
