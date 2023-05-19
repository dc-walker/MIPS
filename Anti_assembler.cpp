#include"Anti_assembler.h"
#include<assert.h>
#include<sstream>

std::string process1(std::string line);
std::string process2(std::string line);
std::string process3(std::string line);
std::string process4(std::string line);
std::string process5(std::string line);
std::string process6(std::string line);
std::string process7(std::string line);

//Implementation of class Myexception
Myexception::Myexception(){
}

Myexception::Myexception(std::string type, std::string message){
    this->type = type;
    this->message = message;
}

Myexception::~Myexception(){
}

std::string Myexception::getMessage(){
    return message;
}

std::string Myexception::getType(){
    return type;
}

void Myexception::setMessage(std::string message){
    this->message = message;
}

void Myexception::setType(std::string type){
    this->type = type;
}

void Myexception::Display(){
    std::cout << "Error type: " << type << std::endl;
    std::cout << "Error message: " << message << std::endl;
}

//Implementation of class Anti_assembler
Anti_assembler::Anti_assembler(){
    this->linenum = 0;
    this->binaryfile.clear();
    this->binaryfile.resize(0);
    this->binaryfile.reserve(0);
}

Anti_assembler::Anti_assembler(std::vector<std::string> binaryfile) throw (Myexception){
    this->linenum = binaryfile.size();
    if(!this->binaryfile.empty()){
        throw Myexception("NOT_NULL_BEFORE_INITIALIZATION", "The binaryfile is not empty before you initialize!");
    }
    this->binaryfile.swap(binaryfile);
}

Anti_assembler::~Anti_assembler(){
}

void Anti_assembler::setLinenum(int linenum){
    this->linenum = linenum;
}

int Anti_assembler::getLinenum(){
    return linenum;
}

void Anti_assembler::setBinaryfile(std::vector<std::string> binaryfile){
    this->binaryfile.swap(binaryfile);
}

std::vector<std::string> Anti_assembler::getBinaryfile(){
    return binaryfile;
}

std::vector<std::string> Anti_assembler::disassemble() throw(Myexception){
    std::string line;
    std::vector<std::string> mipscode;
    for(int i=0; i<this->linenum; i++){
        std::string temp = "";
        line = this->binaryfile.at(i);
        //add, sub, jr, slt
        if(line.substr(0, 6) == "000000"){
            assert((temp = process1(line)) != "");
            mipscode.push_back(temp);
        }
        //addi
        else if(line.substr(0, 6) =="001000"){
            assert((temp = process2(line)) != "");
            mipscode.push_back(temp);
        }   
        //lw
        else if(line.substr(0, 6) == "100011"){
            assert((temp = process3(line))!= "");
            mipscode.push_back(temp);
        }
        //sw
        else if(line.substr(0, 6) == "101011"){
            assert((temp = process4(line))!= "");
            mipscode.push_back(temp);
        }
        //beq
        else if(line.substr(0, 6) == "000100"){
            assert((temp = process5(line))!= "");
            mipscode.push_back(temp);
        }
        //bne
        else if(line.substr(0, 6) == "000101"){
            assert((temp = process6(line))!= "");
            mipscode.push_back(temp);
        }
        //jal
        else if(line.substr(0, 6) == "000011"){
            assert((temp = process7(line))!= "");
            mipscode.push_back(temp);
        }
    }   
    return mipscode;
}

int binary_to_int(std::string binary){
    int number = 0;
    for(int i=0; i<binary.length(); i++)
        number = number * 2 + (binary[i] - '0');
    return number;
}

int imm_binary_to_int(std::string binary){
    int number = 0;
    //for 10..00->00..00
    if(binary[0] == '1' and binary[1] == '0')
        return 0;
    if(binary[0] == '1'){
        for(int i=binary.length()-1; i>=1; i--)
            if(binary[i] == '1'){
                binary[i] = '0';
                for(int j = i+1; j < binary.length(); j++){
                    binary[j] = '1';
                }
                break;  
            }
        for(int i=0; i<binary.length(); i++)
            if(binary[i] == '0')
                binary[i] = '1';
            else
                binary[i] = '0';    }
    for(int i=1; i<binary.length(); i++)
        number = number * 2 + (binary[i] - '0');
    
    return number;
}

//Process for some/a instructions
//add, sub, jr, slt
std::string process1(std::string line){
    std::string outcome;
    std::string imm;
    int len = line.length();
    //add:000000 00000 00000 00000 00000 100000
    if(line.substr(len-6,6) == "100000"){
        outcome += "add ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(16, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));

    }
    // sub:000000 00000 00000 00000 00000 100010
    else if(line.substr(len-6,6) == "100010"){
        outcome += "sub ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(16, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    }
    // jr:000000 00000 00000 00000 00000 001000
    else if(line.substr(len-6,6) == "001000"){
        outcome += "jr ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    }
    //slt:000000 00000 00000 00000 00000 101010
    else if(line.substr(len-6,6) == "101010"){
        outcome += "slt ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(16, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
        outcome += ", ";
        outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    }
    return outcome;
}   

//addi
std::string process2(std::string line){
    std::string outcome;
    outcome += "addi ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    outcome += ", ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    outcome += ", ";
    if(line[16] == '1')
        outcome += "-";
    outcome += std::to_string(imm_binary_to_int(line.substr(16, 16)));
    return outcome;
}

//lw
std::string process3(std::string line){
    std::string outcome;
    outcome += "lw ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    outcome += ", ";
    outcome += std::to_string(imm_binary_to_int(line.substr(16, 16)));
    outcome += "(";
    outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    outcome += ")";
    return outcome;
}

//sw
std::string process4(std::string line){
    std::string outcome;
    outcome += "sw ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    outcome += ", ";
    if(line[16] == '1')
        outcome += "-";
    outcome += std::to_string(imm_binary_to_int(line.substr(16, 16)));
    outcome += "(";
    outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    outcome += ")";
    return outcome;
}

//beq
std::string process5(std::string line){
    std::string outcome;
    outcome += "beq ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    outcome += ", ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    outcome += ", ";
    if(line[16] == '1')
        outcome += "-";
    outcome += std::to_string(imm_binary_to_int(line.substr(16, 16)));
    return outcome;
}

//bne
std::string process6(std::string line){
    std::string outcome;
    outcome += "bne ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(6, 5)));
    outcome += ", ";
    outcome += REGISTERS2.at(binary_to_int(line.substr(11, 5)));
    outcome += ", ";
    if(line[16] == '1')
        outcome += "-";
    outcome += std::to_string(imm_binary_to_int(line.substr(16, 16)));
    return outcome;
}


//jal Pseudodirect addressing
std::string process7(std::string line){
    std::string outcome;
    outcome += "jal ";
    outcome += std::to_string(binary_to_int(line.substr(6, 26)));
    return outcome;
}
