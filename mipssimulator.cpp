#include<bits/stdc++.h>
#include"Anti_assembler.h"

#define MAX_ADDRESS_SIZE 100000
#define ADDRESS_BITS 32
#define INSTRUCTION_START 10000

using namespace std;

//The name of registers and their corresponding numbers
const std::unordered_map<int, std::string> REGISTERS2 =
{
    {0, "$zero"},{1, "$at"},{2, "$v0"},{3, "$v1"},
    {4, "$a0"},{5, "$a1"},{6, "$a2"},{7, "$a3"},
    {8, "$t0"},{9, "$t1"},{10,"$t2"},{11, "$t3"},
    {12, "$t4"},{13, "$t5"},{14, "$t6"},{15, "$t7"},
    {16, "$s0"},{17, "$s1"},{18, "$s2"},{19, "$s3"},
    {20, "$s4"},{21, "$s5"},{22, "$s6"},{23, "$s7"},
    {24, "$t8"},{25, "$t9"},{26, "$k0"},{27, "$k1"},
    {28, "$gp"},{29, "$sp"},{30, "$fp"},{31, "$ra"},
};

const   unordered_map<string, int> RegToNum =
{
    {"$zero", 0},{"$at", 1},{"$v0", 2},{"$v1", 3},
    {"$a0", 4},{"$a1", 5},{"$a2", 6},{"$a3", 7},
    {"$t0", 8},{"$t1", 9},{"$t2", 10},{"$t3", 11},
    {"$t4", 12},{"$t5", 13},{"$t6", 14},{"$t7", 15},
    {"$s0", 16},{"$s1", 17},{"$s2", 18},{"$s3", 19},
    {"$s4", 20},{"$s5", 21},{"$s6", 22},{"$s7", 23},
    {"$t8", 24}, {"$t9", 25},{"$k0", 26},{"$k1", 27},
    {"$gp", 28},{"$sp", 29},{"$fp", 30},{"$ra", 31}
};

class MipsSimulator {
public:
    MipsSimulator() {
        address.resize(MAX_ADDRESS_SIZE);
        reg.resize(ADDRESS_BITS);
        PC = INSTRUCTION_START;
    }
    ~MipsSimulator() {

    }
    string Transform(int n) {//整数转化为32位二进制
        string m;
        for (int i = 31; i >= 0; i--)
        {
            m.push_back(((n >> i) & 1) + '0');//与1做位操作
        }
        return m;
    }
    bool load(vector<string> instruction) {//放入32位机器码，如果某个机器码不是32位则返回false并停止

        for (int i = 0; i < instruction.size(); i++) {
            if (instruction[i].size() != ADDRESS_BITS) return false;
            address[INSTRUCTION_START + i] = instruction[i];
        }
        return true;
    }
    void clear(){
        address.clear();
        PC = INSTRUCTION_START;
        for(int i = 0; i < reg.size(); i++) reg[i] = 0;
    }
    void Execute() {
        while (PC >= 0 && PC < MAX_ADDRESS_SIZE) {
            if (address[PC].empty()) break;
            ExecuteOne();
        }

    }
    void ExecuteOne() {
        string ins;
        Anti_assembler a;
        vector<string> binary;
        vector<string> instruction;
        binary.push_back(address[PC]);
        a.setBinaryfile(binary);
        a.setLinenum(1);
        instruction = a.disassemble();
        ins = instruction[0];
        vector<string> parameter = TakePara(ins);
        PC += 1;
        if (parameter[0] == "add" || parameter[0] == "sub" || parameter[0] == "slt") {
            int res, op1, op2;
            res = RegToNum.at(parameter[1]);
            op1 = RegToNum.at(parameter[2]);
            op2 = RegToNum.at(parameter[3]);
            if (parameter[0] == "add") reg[res] = reg[op1] + reg[op2];
            if (parameter[0] == "sub") reg[res] = reg[op1] - reg[op2];
            if (parameter[0] == "slt") reg[res] = (reg[op1] < reg[op2]);

        }
        else if (parameter[0] == "jr") {
            int r1 = RegToNum.at(parameter[1]);
            PC = reg[r1];
        }
        else if (parameter[0] == "addi" || parameter[0] == "beq" || parameter[0] == "bne") {
            int op1, op2, imm;
            op1 = RegToNum.at(parameter[1]);
            op2 = RegToNum.at(parameter[2]);
            imm = stoi(parameter[3]);
            if (parameter[0] == "addi") reg[op1] = reg[op2] + imm;
            if (parameter[0] == "beq")
                if (reg[op1] == reg[op2]) PC += imm;
            if (parameter[0] == "bne") if (reg[op1] != reg[op2]) PC += imm;
        }
        else if (parameter[0] == "lw" || parameter[0] == "sw") {
            int op1, op2, imm;
            op1 = RegToNum.at(parameter[1]);
            imm = stoi(parameter[2]);
            op2 = RegToNum.at(parameter[3]);
            if (parameter[0] == "lw") {
                if (address[reg[op2] + imm].empty()) {
                    reg[op1] = 0;
                    return;
                }
                bitset<32> bits(address[reg[op2] + imm]);
                reg[op1] = bits.to_ulong();
            }
            if (parameter[0] == "sw") {
                address[reg[op2] + imm] = Transform(reg[op1]);
            }
        }
        else if (parameter[0] == "jal") {
            int imm = stoi(parameter[1]);
            reg[31] = PC;
            PC = imm;
        }


    }
    vector<string> TakePara(string ins) {//去除多余的字符，获取参数
        vector<string> res;
        for (int i = 0; i < ins.size(); i++) {
            if (ins[i] == ',' || ins[i] == '(' || ins[i] == ')')
                ins[i] = ' ';
        }
        stringstream sstream;
        string temp;
        sstream << ins;
        while (sstream) {
            sstream >> temp;
            res.push_back(temp);
        }
        return res;
    }
    void Showallreg() {//输出所有寄存器的状态
        for (int i = 0; i < 32; i++) {
            cout << REGISTERS2.at(i) << " : " << reg[i] << endl;
        }
    }
    void ShowOneReg(int i) {
        cout << REGISTERS2.at(i) << " : " << reg[i];
    }
    void ShowPC(){
        cout << "PC : " << PC << endl;
    }
    void showaddress(int i){
        if(i <= 0 || i >= MAX_ADDRESS_SIZE)
            cout << "INVALID ADDRESS!";
        cout << "address at " << i << ": " << address[i];
    }

private:
    int PC;
    vector<string> address;
    vector<int> reg;
};




