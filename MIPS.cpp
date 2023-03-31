#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//根据指令和操作码的建立对应关系
const unordered_map<string, unsigned int> OPCODES = 
{
    // 暂时选了这10条，还没确定
    {"add", 0x20},
    {"addi", 0x8},
    {"lw", 0x23},
    {"sw", 0x2b},
    {"beq", 0x4},
    {"bne", 0x5},
    {"j", 0x2},
    {"jal", 0x3},
    // {"jr", 0x},
    // {"slt", 0x}
};

//32个寄存器


class MIPS_Simulator
{
public:
    void Load();   //将uint32位指令读入内存
    void Execute();  //执行指令
    /*
    接口也不一定长这样，怎么好写怎么来
    */
private:
    //PC等寄存器,内存
    //其它寄存器可以参考如下实现
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
};

//汇编
unsigned int Assemble(string instruction);
/*
输入形如add $t0, $t1, $t2的指令，返回32位机器码（用uint存储）
*/

//反汇编
string Disassemble(unsigned int instruction);
/*
输入uint类型的32位机器码，返回形如add $t0, $t1, $t2的指令
*/
