#include "Simulator.h"


MipsSimulator::MipsSimulator() {
    address.resize(MAX_ADDRESS_SIZE);
    reg.resize(ADDRESS_BITS);
    PC = INSTRUCTION_START;
}


MipsSimulator::~MipsSimulator() {
}

string MipsSimulator::Transform(int n) {
    //整数转化为32位二进制
    string m;
    for (int i = 31; i >= 0; i--)
    {
        m.push_back(((n >> i) & 1) + '0');//与1做位操作
    }
    return m;
}
bool MipsSimulator::load(vector<std::string> instruction) {
    //放入32位机器码，如果某个机器码不是32位则返回false并停止
    for (int i = 0; i < instruction.size(); i++) {
        if (instruction[i].size() != ADDRESS_BITS) return false;
        address[INSTRUCTION_START + i] = instruction[i];
    }
    return true;
}
void MipsSimulator::clear() {
    address.clear();
    PC = INSTRUCTION_START;
    for(int i = 0; i < reg.size(); i++) reg[i] = 0;
}
void MipsSimulator::ExecuteOne() {
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
void MipsSimulator::Execute() {
    while (PC >= 0 && PC < MAX_ADDRESS_SIZE) {
        if (address[PC].empty()) break;
        ExecuteOne();
    }
}

vector<string> MipsSimulator::TakePara(string ins) {//去除多余的字符，获取参数
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

void MipsSimulator::Showallreg() {//输出所有寄存器的状态
    for (int i = 0; i < 32; i++) {
        cout << REGISTERS2.at(i) << " : " << reg[i] << endl;
    }
}

void MipsSimulator::ShowOneReg(int i) {
    cout << REGISTERS2.at(i) << " : " << reg[i];
}
void MipsSimulator::ShowPC(){
    cout << "PC : " << PC << endl;
}
void MipsSimulator::showaddress(int i){
    if(i <= 0 || i >= MAX_ADDRESS_SIZE)
        cout << "INVALID ADDRESS!";
    cout << "address at " << i << ": " << address[i];
}
