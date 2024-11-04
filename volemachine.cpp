#include "volemachine.h"
// Alu Class Implementation
string Alu::hexToBinary(const string &hex) { string binary = "";
    for (char c: hex) {
        switch (toupper(c)) {
            case '0':
                binary += "0000";
                break;
            case '1':
                binary += "0001";
                break;
            case '2':
                binary += "0010";
                break;
            case '3':
                binary += "0011";
                break;
            case '4':
                binary += "0100";
                break;
            case '5':
                binary += "0101";
                break;
            case '6':
                binary += "0110";
                break;
            case '7':
                binary += "0111";
                break;
            case '8':
                binary += "1000";
                break;
            case '9':
                binary += "1001";
                break;
            case 'A':
                binary += "1010";
                break;
            case 'B':
                binary += "1011";
                break;
            case 'C':
                binary += "1100";
                break;
            case 'D':
                binary += "1101";
                break;
            case 'E':
                binary += "1110";
                break;
            case 'F':
                binary += "1111";
                break;
            default:
                cout << "Invalid hexadecimal digit: " << c << endl;
                return "";
        }
    }
    return binary; }
string Alu::binaryToHex(const string &binary) { string hex = "";
    int len = binary.length();

    // Ensure the binary string length is a multiple of 4
    int padLength = (4 - (len % 4)) % 4;
    string paddedBinary = string(padLength, '0') + binary;

    for (size_t i = 0; i < paddedBinary.length(); i += 4) {
        string fourBits = paddedBinary.substr(i, 4);
        if (fourBits == "0000") hex += '0';
        else if (fourBits == "0001") hex += '1';
        else if (fourBits == "0010") hex += '2';
        else if (fourBits == "0011") hex += '3';
        else if (fourBits == "0100") hex += '4';
        else if (fourBits == "0101") hex += '5';
        else if (fourBits == "0110") hex += '6';
        else if (fourBits == "0111") hex += '7';
        else if (fourBits == "1000") hex += '8';
        else if (fourBits == "1001") hex += '9';
        else if (fourBits == "1010") hex += 'A';
        else if (fourBits == "1011") hex += 'B';
        else if (fourBits == "1100") hex += 'C';
        else if (fourBits == "1101") hex += 'D';
        else if (fourBits == "1110") hex += 'E';
        else if (fourBits == "1111") hex += 'F';
    }
    return hex; }
string Alu::signExtend(const string &binary, int length) { if (binary.size() >= length) return binary; // No need to extend if already the correct size
    char signBit = binary[0];
    return string(length - binary.size(), signBit) + binary; }
string Alu::addBinaryTwosComplement(const string &bin1, const string &bin2) { int maxLength = max(bin1.size(), bin2.size());

    // Sign-extend both binary strings to the same length
    string paddedBin1 = signExtend(bin1, maxLength + 1); // Add extra bit for overflow detection
    string paddedBin2 = signExtend(bin2, maxLength + 1);

    string result = "";
    int carry = 0;

    // Perform the binary addition from the rightmost bit
    for (int i = maxLength; i >= 0; i--) {
        int bit1 = paddedBin1[i] - '0';
        int bit2 = paddedBin2[i] - '0';
        int sum = bit1 + bit2 + carry;

        carry = sum / 2;  // Determine the carry (1 if sum is 2 or 3)
        result += (sum % 2) + '0';  // Add the resulting bit
    }

    // Reverse the result to get the final sum
    reverse(result.begin(), result.end());

    // Remove the leading bit if there was no overflow
    if (result.size() > maxLength) {
        result = result.substr(1);
    }

    return result; }
int Alu::hexToDecimal(const string &hex) { int decimalValue = 0;
    int base = 1; // 16^0

    for (int i = hex.length() - 1; i >= 0; i--) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            decimalValue += (hex[i] - '0') * base;
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            decimalValue += (hex[i] - 'A' + 10) * base;
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            decimalValue += (hex[i] - 'a' + 10) * base;
        } else {
            cout << "Invalid hexadecimal digit: " << hex[i] << endl;
            return -1; // Error code for invalid input
        }
        base *= 16; // Move to the next power of 16
    }

    return decimalValue; }
string Alu::ORing(string binary1, string binary2) { // Ensure both strings are of equal length
    if (binary1.length() < binary2.length()) {
        binary1.insert(0, binary2.length() - binary1.length(), '0');
    } else {
        binary2.insert(0, binary1.length() - binary2.length(), '0');
    }

    string result;
    for (size_t i = 0; i < binary1.length(); ++i) {
        result += (binary1[i] == '1' || binary2[i] == '1') ? '1' : '0';
    }
    return result; }
string Alu::ANDing(string binary1, string binary2) { string ANDingresult;
    if (binary1.length() >= binary2.length()) { //for adding zeros for empty indexes
        for (int i = 0; i < (binary1.length()-binary2.length()); ++i) {
            binary2.insert(0,"0");
        }
    }
    else {
        for (int i = 0; i < (binary2.length()-binary1.length()); ++i) {
            binary2.insert(0,"0");
        }
    }
    for (int i = 0; i < binary1.length(); ++i) {
        if (binary1[i] == '1' && binary2[i] == '1'){
            ANDingresult += "1";
        }
        else if (binary1[i] == '1' && binary2[i] == '0'){
            ANDingresult += "0";
        }
        else if (binary1[i] == '0' && binary2[i] == '1'){
            ANDingresult += "0";
        }
        if (binary1[i] == '0' && binary2[i] == '0'){
            ANDingresult += "0";
        }
    }
    return ANDingresult; }
string Alu::XORing(string binary1, string binary2) {
    if (binary1.length() >= binary2.length()) { //for adding zeros for empty indexes
        for (int i = 0; i < (binary1.length()-binary2.length()); ++i) {
            binary2.insert(0,"0");
        }
    }
    else {
        for (int i = 0; i < (binary2.length()-binary1.length()); ++i) {
            binary2.insert(0,"0");
        }
    }
    string XORingresult;
    for (int i = 0; i < binary1.length(); ++i) {
        if (binary1[i] == '1' && binary2[i] == '1'){
            XORingresult += "0";
        }
        else if (binary1[i] == '1' && binary2[i] == '0'){
            XORingresult += "1";
        }
        else if (binary1[i] == '0' && binary2[i] == '1'){
            XORingresult += "1";
        }
        if (binary1[i] == '0' && binary2[i] == '0'){
            XORingresult += "0";
        }
    }
    return XORingresult; }
void Alu::rotateRight(string &binary, int steps) { int length = binary.length();
    steps %= length; // Ensure steps are within bounds
    string rotated = binary.substr(length - steps) + binary.substr(0, length - steps);
    binary = rotated; }

// Register Class Implementation
Register::Register() { bits.resize(16, "0"); }
void Register::setbit(string memvalue, int operand) {
    if (operand >= 0 && operand < 16) {
        bits[operand] = memvalue;
    } else {
        cout << "Invalid register index: " << operand << endl;
    }
}
string Register::getbit(int operand) {
    if (operand >= 0 && operand < 16) {
        return bits[operand];
    } else {
        return "0";
    }
}
void Register::printRegister() {
    cout << "Register: \n";
    for (int i = 0; i < 16; i++) {
        cout << bits[i] << endl;
    }
}

// Memory Class Implementation
Memory::Memory() { cell.resize(256, "00"); }
void Memory::setcellinput(const string& input, int i2) {
    stringstream ss(input);
    string command;
    int index = i2;
    while (ss >> command) {
        if (command.length() == 4 && index + 1 < cell.size()) { // Ensure there is room in memory
            cell[index++] = command.substr(0, 2);
            cell[index++] = command.substr(2, 2);
        } else {
            cout << "Invalid command or insufficient memory space." << endl;
            break;
        }
    }
}
void Memory::setcelladdress(int address, string operand_value) {
    if (address >= 0 && address < 256) {
        cell[address] = operand_value;
    } else {
        cout << "Invalid register index: " << address << endl;
    }
}
string Memory::getcell(int address) {
    if (address >= 0 && address < 256) {
        return cell[address];
    } else {
        return "00";
    }
}
void Memory::printMemory() {
    cout << "Memory: \n";
    for (int i = 0; i < 256; i++) {
        cout << cell[i] << endl;
    }
}


// Instructions Class Implementation
void Instructions::readInput(Memory& memory, vector<string>& commands, int i3) {
    for (; i3 < 256; i3 += 2) {
        commands.push_back(memory.getcell(i3) + memory.getcell(i3 + 1));
    }
}
void Instructions::executeStep(Memory& memory, Register& reg, int& index, vector<string>& commands, bool& isRunning, int& pc) {
    if (index < 0 || index >= commands.size()) {
        cout << "Invalid execution index." << endl;
        isRunning = false;
        return;
    }

    string command = commands[index];
    if (command.length() < 4) {
        cout << "Invalid command format." << endl;
        isRunning = false;
        return;
    }
    int pcounter = pc;
    cout<<"pc: "<<pcounter <<"->"<<command<<endl;
    pc += 2;
    // Extract the opcode, operand, and address/value components
    int op = stoi(command.substr(0, 1), nullptr, 16);
    int operand = stoi(command.substr(1, 1), nullptr, 16);
    string v_a = command.substr(2, 2);  // Last 2 characters as value or address

    switch (op) {
        case 1: {  // Example: Load from Memory to Register
            int address = hexToDecimal(v_a);
            if (address != -1) {
                string memvalue = memory.getcell(address);
                reg.setbit(memvalue, operand);
            }
            index++; // Move to next instruction
            break;
        }

        case 2: {  // Example: Directly set value to Register
            reg.setbit(v_a, operand);
            index++; // Move to next instruction
            break;
        }

        case 3: {  // Example: Store from Register to Memory
            int address = hexToDecimal(v_a);
            string bitvalue = reg.getbit(operand);
            memory.setcelladdress(address, bitvalue);
            if (address == 0) {
                cout<<"This is Memory (00)\n";
                cout << "Output to screen: " << bitvalue << endl;
            }
            index++; // Move to next instruction
            break;
        }

        case 4: {  // Example: Copy value between registers
            int operand1 = stoi(command.substr(2, 1));
            int operand2 = stoi(command.substr(3, 1));
            reg.setbit(reg.getbit(operand1), operand2);
            index++; // Move to next instruction
            break;
        }

        case 5: {  // Example: Arithmetic Addition using Registers using 2's complement
            int operand1 = stoi(command.substr(1, 1));
            int operand2 = stoi(command.substr(2, 1));
            int operand3 = stoi(command.substr(3, 1));
            string binOp2 = hexToBinary(reg.getbit(operand2));
            string binOp3 = hexToBinary(reg.getbit(operand3));
            string resultBin = addBinaryTwosComplement(binOp2, binOp3);
            string resultHex = binaryToHex(resultBin);
            reg.setbit(resultHex, operand1);
            index++; // Move to next instruction
            break;
        }
        case 7 :{
            int operand1 = stoi(command.substr(1, 1));
            int operand2 = stoi(command.substr(2, 1));
            int operand3 = stoi(command.substr(3, 1));
            string binOp2 = hexToBinary(reg.getbit(operand2));
            string binOp3 = hexToBinary(reg.getbit(operand3));
            string resultBin = ORing(binOp2,binOp3);
            string resultHex = binaryToHex(resultBin);
            reg.setbit(resultHex, operand1);
            index++; // Move to next instruction
            break;
        }
        case 8:{
            int operand1 = stoi(command.substr(1, 1));
            int operand2 = stoi(command.substr(2, 1));
            int operand3 = stoi(command.substr(3, 1));
            string binOp2 = hexToBinary(reg.getbit(operand2));
            string binOp3 = hexToBinary(reg.getbit(operand3));
            string resultBin = ANDing(binOp2,binOp3);
            string resultHex = binaryToHex(resultBin);
            reg.setbit(resultHex, operand1);
            index++; // Move to next instruction
            break;

        }
        case 9:{
            int operand1 = stoi(command.substr(1, 1));
            int operand2 = stoi(command.substr(2, 1));
            int operand3 = stoi(command.substr(3, 1));
            string binOp2 = hexToBinary(reg.getbit(operand2));
            string binOp3 = hexToBinary(reg.getbit(operand3));
            string resultBin = XORing(binOp2,binOp3);
            string resultHex = binaryToHex(resultBin);
            reg.setbit(resultHex, operand1);
            index++; // Move to next instruction
            break;

        }
        case 10: {  // Rotate right the content of register R by X steps
            int registerNum = stoi(command.substr(1, 1)); // R
            int rotateSteps = stoi(command.substr(2, 1));  // X

            string regContent = reg.getbit(registerNum);
            rotateRight(regContent, rotateSteps);
            reg.setbit(regContent, registerNum); // Update the register content
            index++; // Move to next instruction
            break;
        }



        case 11: {  // Conditional Branch (BRXY equivalent)
            if (reg.getbit(operand) == reg.getbit(0)) {
                int address = hexToDecimal(v_a);
                index = address / 2; // Jump to the specified address
            } else {
                index++; // Continue to the next instruction if condition is not met
            }
            break;
        }

        case 12: {  // Halt Operation
            isRunning = false; // Stop further execution
            cout << "Halt execution." << endl;
            break;
        }
        
        case 13: {  // Conditional Branch (DRXY equivalent)
            if (reg.getbit(operand) > reg.getbit(0)) {
                int address = hexToDecimal(v_a);
                index = address / 2; // Jump to the specified address
            } else {
                index++; // Continue to the next instruction if condition is not met
            }
            break;
        }


        default: {
            cout << "Invalid operation code: " << op << endl;
            isRunning = false; // Stop execution on invalid opcode
            break;
        }
    }

}

// Machine Class Implementation
Machine::Machine() : isRunning(true), index(0) {}
void Machine::setInput(string input,int i1) {
    memory.setcellinput(input, i1); instructions.readInput(memory, commands, i1);
}
void Machine::execute(int i1) {
    while (isRunning && index < commands.size()) {
        instructions.executeStep(memory, reg, index, commands, isRunning, i1);
    }
}
void Machine::printState() {
    cout << "\t\t\tMemory \t\t\t\t\t  Registers" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            int index = row * 16 + col;
            cout << memory.getcell(index) << "  ";
        }

        if (row < 16) {
            cout << "  " << reg.getbit(row);
        }

        cout << endl; 
    }
}


