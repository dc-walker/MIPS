
#ifndef MIPS_MASTER_SIMULATOR_H
#define MIPS_MASTER_SIMULATOR_H

#include<bits/stdc++.h>
#include"Anti_assembler.h"

#define MAX_ADDRESS_SIZE 100000
#define ADDRESS_BITS 32
#define INSTRUCTION_START 10000

using namespace std;

//The name of registers and their corresponding numbers
const std::unordered_map<int, std::string> REGISTERS =
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
    MipsSimulator();
    ~MipsSimulator();
    string Transform(int n);
    bool load(vector<string> instruction);
    void clear();
    void Execute();
    void ExecuteOne();
    vector<string> TakePara(string ins);
    void Showallreg();
    void ShowOneReg(int i);
    void ShowPC();
    void showaddress(int i);

private:
    int PC;
    vector<string> address;
    vector<int> reg;
};









#endif //MIPS_MASTER_SIMULATOR_H
