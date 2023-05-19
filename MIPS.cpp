#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include "Anti_assembler.cpp"
#include "Assembler.cpp"

using namespace std;

//根据指令和操作码的建立对应关系
// const unordered_map<string, unsigned int> OPCODES = 
// {
//     // 暂时选了这10条，还没确定,opcode我没仔细看
//     {"add", 0x20},
//     {"sub", 0x111},
//     {"addi", 0x8},
//     {"lw", 0x23},
//     {"sw", 0x2b},
//     {"beq", 0x4},
//     {"bne", 0x5},
//     {"jal", 0x3},
//     {"jr", 0x111},
//     {"slt", 0x}
// };

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
    //PC等寄存器,内存（可用数组实现）
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
string Assemble(string instr);
/*
输入形如add $t0, $t1, $t2的指令，返回32位机器码（用32位string存储）
*/


/*
Anti_assembler class:
    Need to Initialize before you use it.
*/
Anti_assembler anti_assembler;

/*
Test for Disassembler:
    Author: Squarehuang
    Last Modified: 2023.5.18
    Description: test for Disassembler
*/
void test_for_Disassembler()
{
    using namespace std;
    vector<string> output;
    vector<string> input = {
        "00000001001010100100000000100000",
        "00000001001010100100000000100010",
        "00100001001010000000000000000001",
        "10001101001010000000000000000100",
        "10101101001010001111111111111100",
        "00010001000010010000000111110100",
        "00010101000010010000000111110100",
        "00001100000000000000111110100000",
        "00000011111000000000000000000100",
        "00000001001010100100000000101010"
    };
    vector<string> instruction = {
        "add $t0, $t1, $t2",
        "sub $t0, $t1, $t2",
        "addi $t0, $t1, 1",
        "lw $t0, 4($t1)",
        "sw $t0, -4($t1)",
        "beq $t0, $t1, 500",
        "bne $t0, $t1, 500",
        "jal 4000",
        "jr $ra",
        "slt $t0, $t1, $t2"
    };
    Anti_assembler anti_assembler_test(input);

    try{
        output = anti_assembler_test.disassemble();
    }
    catch(Myexception &e){
        e.Display();
    }
    assert(output.size() == instruction.size());
    for(int i=0; i<input.size(); i++){
        assert(output[i] == instruction[i]);
    }
    printf("\nTest Successfully!\n");
}


int main()
{

    //一点测试代码
     string instr_add = Assemble("add $t0, $t1, $t2");
     cout<<instr_add<<endl;
    string instr_sub = Assemble("sub $t0, $t1, $t2");
    cout<<instr_sub<<endl;
    string instr_addi = Assemble("addi $t0, $t1, 1");
    cout<<instr_addi<<endl; 
    string instr_lw = Assemble("lw $t0, 4($t1)");
    cout<<instr_lw<<endl;
    string instr_sw = Assemble("sw $t0, -4($t1)");
    cout<<instr_sw<<endl;
    string instr_beq = Assemble("beq $t0, $t1, 500");
    cout<<instr_beq<<endl;
    string instr_bne = Assemble("bne $t0, $t1, 500");
    cout<<instr_bne<<endl;
    string instr_jal = Assemble("jal 4000");
    cout<<instr_jal<<endl;
    string instr_jr = Assemble("jr $ra");
    cout<<instr_jr<<endl;
    string instr_slt = Assemble("slt $t0, $t1, $t2");
    cout<<instr_slt<<endl;
    test_for_Disassembler();
    return 0;
}