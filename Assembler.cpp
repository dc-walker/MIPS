
#include "Assembler.h"



string Assemble(string instr) {
    stringstream ss(instr);
    string op, rd, rs, rt,tmp,num;
    uint32_t imm;
    ss >> op;
    if (op == "add" || op == "slt"|| op == "sub") {
        //ss >> rd >> rs >> rt;
         regex reg("(\\$[a-zA-Z0-9]+),\\s*(\\$[a-zA-Z0-9]+),\\s*(\\$[a-zA-Z0-9]+)");
        smatch match;
        if (regex_search(instr, match, reg)) {
             rd = match[1];
             rs = match[2];
             rt = match[3];
        }
        uint32_t opcode = 0x0;
        uint32_t funct = opcodes[op];
        // rd.pop_back();
        // rs.pop_back();
        uint32_t rd_code = REGISTERS3.at(rd) << 11;
        uint32_t rs_code = REGISTERS3.at(rs) << 21;
        uint32_t rt_code = REGISTERS3.at(rt) << 16;
        uint32_t machine_code = opcode | rs_code | rt_code | rd_code | funct;
        return bitset<32>(machine_code).to_string();
    }
    else if (op == "jr") {
        ss >> rs;
        uint32_t opcode = 0x0 ;
        uint32_t funct = 8;
        uint32_t rs_code = REGISTERS3.at(rs) << 21;
        uint32_t machine_code = opcode | rs_code|funct;
        return bitset<32>(machine_code).to_string();
    } else if (op == "j" || op == "jal") {
        ss>>num;
        if(num[0]=='0'&&num[1]=='x')  imm = stoi(num, nullptr,16);
        else imm = stoi(num);
        uint32_t opcode = opcodes[op] << 26;
        uint32_t machine_code = opcode | (imm & 0x03FFFFFF);
        return bitset<32>(machine_code).to_string();
    }

    else if (op == "beq" || op == "bne"|| op =="addi") {
        // ss >> rt >> rs >> num;
        // rs.pop_back();
        // rt.pop_back();
        regex reg("(\\$[a-zA-Z0-9]+),\\s*(\\$[a-zA-Z0-9]+),\\s*(-?(?:0x)?[0-9a-fA-F]+)");
        smatch match;
        if (regex_search(instr, match, reg)) {
            rt = match[1];
            rs = match[2];
            num = match[3];
        }
        if(num[0]=='0'&&num[1]=='x')  imm = stoi(num, nullptr,16);
        else imm = stoi(num);
        uint32_t opcode = opcodes[op] << 26;
        uint32_t rs_code = REGISTERS3.at(rs) << 21;
        uint32_t rt_code = REGISTERS3.at(rt) << 16;
        uint32_t imm_code = imm & 0xFFFF;
        uint32_t machine_code = opcode | rs_code | rt_code | imm_code;
        return bitset<32>(machine_code).to_string();
    }
    else if ( op == "lw" || op == "sw") {
        ss >> rt >>imm;
        getline(ss,rs,')');
        rt.pop_back();
        rs.erase(0,1);
        REGISTERS3.at("$ra");
        uint32_t opcode = opcodes[op] << 26;
        uint32_t rs_code = REGISTERS3.at(rs) << 21;
        uint32_t rt_code = REGISTERS3.at(rt) << 16;
        uint32_t imm_code = imm & 0xFFFF;
        uint32_t machine_code = opcode | rs_code | rt_code | imm_code;
        return bitset<32>(machine_code).to_string();
    }// 如果没有匹配到指令，抛出异常
    throw invalid_argument("Invalid instruction.");
}
