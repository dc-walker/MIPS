#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <bitset>
#include <unordered_map>
using namespace std;
map<string, unsigned int> opcodes = {
        {"add", 0x20},
        {"jr", 0x08},
        {"slt", 0x2A},
        {"j", 0x02},
        {"jal", 0x03},
        {"beq", 0x04},
        {"bne", 0x05},
        {"addi", 0x08},
        {"lw", 0x23},
        {"sw", 0x2B},
        {"sub", 0x22}
};

const unordered_map<string, unsigned int> REGISTERS =
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
string Assemble(string instruction);