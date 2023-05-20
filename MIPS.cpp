#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include "Anti_assembler.cpp"
#include "Simulator.cpp"
#include "Assembler.cpp"
#include "IntFloatConverter.cpp"

/*
Anti_assembler class:
    Need to Initialize before you use it.
*/
//Anti_assembler anti_assembler;

void test_for_Assembler();
void test_for_Disassembler();
void test_for_Simulator();
void test_for_Converter();

void display()
{
    cout << "*****MIPS*****" << endl;
    cout << "1. Assembler:" << endl;
    cout << "2. Anti_assembler:" << endl;
    cout << "3. Simulator:" << endl;
    cout << "4. IntFloatConverter:" << endl;
    cout << "5. Exit" << endl;
}
void operate_assem()
{
    string input_file = "assem_input.txt";   // 输入文件名
    string output_file = "assem_output.txt"; // 输出文件名
    string line;                             // 用于存储读取的每一行数据

    // 打开输入文件
    ifstream infile(input_file);

    if (infile.is_open())
    {
        ofstream outfile(output_file);
        if (outfile.is_open())
        {
            // 逐行读取输入文件中的数据
            while (getline(infile, line))
            {
                string result = Assemble(line);
                outfile << result << "     <---" << line << endl;
            }
            outfile.close();
        }
        else
        {
            cout << "Can not open input " << output_file << endl;
        }

        infile.close();
    }
    else
    {
        cout << "Can not open output " << input_file << endl;
    }
}
void operate_disass()
{
    string input_file = "dis_assem_input.txt";   // 输入文件名
    string output_file = "dis_assem_output.txt"; // 输出文件名
    string line;                                 // 用于存储读取的每一行数据
    vector<string> input;
    vector<string> result;
    // 打开输入文件
    ifstream infile(input_file);

    if (infile.is_open())
    {
        ofstream outfile(output_file);
        if (outfile.is_open())
        {
            // 逐行读取输入文件中的数据
            while (getline(infile, line))
            {
                input.push_back(line);
            }
            Anti_assembler anti_assembler;
            anti_assembler.setBinaryfile(input);
            anti_assembler.setLinenum(input.size());
            result = anti_assembler.disassemble();
            for (int i = 0; i < result.size(); i++)
            {
                outfile << result[i] << "     <---" << input[i] << endl;
            }

            outfile.close();
        }
        else
        {
            cout << "Can not open input " << output_file << endl;
        }

        infile.close();
    }
    else
    {
        cout << "Can not open output " << input_file << endl;
    }
}
void operate_sim()
{
    string input_file = "Simulator_input.txt";   // 输入文件名
    string output_file = "Simulator_output.txt"; // 输出文件名
    string line;                                 // 用于存储读取的每一行数据
    vector<string> input;
    vector<string> result;
    MipsSimulator simulator;
    // 打开输入文件
    ifstream infile(input_file);

    if (infile.is_open())
    {
        ofstream outfile(output_file);
        if (outfile.is_open())
        {
            // 逐行读取输入文件中的数据
            while (getline(infile, line))
            {
                input.push_back(line);
            }
            simulator.load(input);
            for (int i = 0; i < input.size(); i++)
            {
                simulator.ExecuteOne();
                outfile << input[i] << endl;
                outfile << "--------------------------------" << endl;
                for (int i = 0; i < 32; i++)
                {
                    outfile << REGISTERS2.at(i) << " : " << simulator.reg[i] << endl;
                }
                outfile << "PC: " << simulator.PC << endl;
                outfile << "address: " << simulator.address[simulator.PC] << endl;
                outfile << "--------------------------------" << i << endl;
            }
            outfile.close();
        }
        else
        {
            cout << "Can not open input " << output_file << endl;
        }

        infile.close();
    }
    else
    {
        cout << "Can not open output " << input_file << endl;
    }
}
void operate_converter()
{
    cout << "1. interger" << endl
         << "2. float" << endl;
    int flag = 0;
    cin >> flag;
    if (flag == 1)
    {
        int num1, num2;
        cin >> num1 >> num2;
        std::string a = intToBin(num1);
        std::string b = intToBin(num2);
        std::string sumi = addInt(a, b);
        std::string differencei = subInt(a, b);
        std::string producti = multiplyInt(a, b);
        std::string quotienti = divideInt(a, b);

        std::cout << "Input 1: " << num1 << std::endl;
        std::cout << "Binary representation: " << a << std::endl;
        std::cout << "Input 2: " << num2 << std::endl;
        std::cout << "Binary representation: " << b << std::endl;

        std::cout << "Integer Addition: " << sumi << " " << binToInt(sumi) << std::endl;
        std::cout << "Integer Subtraction: " << differencei << " " << binToInt(differencei) << std::endl;
        std::cout << "Integer Multiplication: " << producti << " " << binToInt(producti) << std::endl;
        std::cout << "Integer Division: " << quotienti << " " << binToInt(quotienti) << std::endl;
    }
    else if (flag == 2)
    {
    float num3,num4;
            cin >> num3 >> num4;
            FloatConverter converter1 = floatToBin(num3);
            FloatConverter converter2 = floatToBin(num4);

            std::cout << "Input 3: " << num3 << std::endl;
            printFloatBin(converter1);
            std::cout << "Input 4: " << num4 << std::endl;
            printFloatBin(converter2);

            FloatConverter sum = addFloats(converter1, converter2);
            FloatConverter difference = subtractFloats(converter1, converter2);
            FloatConverter product = multiplyFloats(converter1, converter2);
            FloatConverter quotient = divideFloats(converter1, converter2);

            std::cout << "Sum: " << binToFloat(sum) << std::endl;
            printFloatBin(sum);
            std::cout << "Difference: " << binToFloat(difference) << std::endl;
            printFloatBin(difference);
            std::cout << "Product: " << binToFloat(product) << std::endl;
            printFloatBin(product);
            std::cout << "Quotient: " << binToFloat(quotient) << std::endl;
            printFloatBin(quotient);
    }
}
int main()
{
    int operation = 0;
    while (1)
    {
        display();
        cin >> operation;
        switch (operation)
        {
        case 1:
        {
            operate_assem();
            break;
        }
        case 2:
        {
            operate_disass();
            break;
        }
        case 3:
        {
            operate_sim();
            break;
        }
        case 4:
        {
            operate_converter();
            break;
        }
        case 5:
        {
            return 0;
        }
        }
    }
    // 一点测试代码
    //  test_for_Assembler();
    //  test_for_Disassembler();
    //  test_for_Simulator();
    //  test_for_Converter();
    return 0;
}

// void test_for_Disassembler()
// {
//     using namespace std;
//     vector<string> output;
//     vector<string> input = {
//         "00000001001010100100000000100000",
//         "00000001001010100100000000100010",
//         "00100001001010000000000000000001",
//         "10001101001010000000000000000100",
//         "10101101001010001111111111111100",
//         "00010001000010010000000111110100",
//         "00010101000010010000000111110100",
//         "00001100000000000000111110100000",
//         "00000011111000000000000000001000",
//         "00000001001010100100000000101010"
//     };
//     vector<string> instruction = {
//         "add $t0, $t1, $t2",
//         "sub $t0, $t1, $t2",
//         "addi $t0, $t1, 1",
//         "lw $t0, 4($t1)",
//         "sw $t0, -4($t1)",
//         "beq $t0, $t1, 500",
//         "bne $t0, $t1, 500",
//         "jal 4000",
//         "jr $ra",
//         "slt $t0, $t1, $t2"
//     };
//     Anti_assembler anti_assembler_test(input);

//     try{
//         output = anti_assembler_test.disassemble();
//     }
//     catch(Myexception &e){
//         e.Display();
//     }
//     assert(output.size() == instruction.size());
//     for(int i=0; i<input.size(); i++){
//         assert(output[i] == instruction[i]);
//     }
//     printf("\nTest Successfully!\n");
// }


// void test_for_Simulator(){

//     vector<string> input = {
//             "00100001000010000000000000000010",
//             "00000001010010000100100000100000",
//             "00000001001010000101000000100010",
//             "00000001001010100101100000101010",
//             "00010001001010000000000000000000",
//             "00010101001010000000000000000000",
//             "00100001101111110010011100011000",
//             "00000011111000000000000000001000",
//             "10001101001011000010011100010000",
//             "10101101001011010000000000000100",
//             "00001100000000000000001111101000"

//     };
//     /*
//      * 对应指令为：
//      *  "addi $t0, $t0, 2",
//             "add $t1, $t2, $t0",
//             "sub $t2, $t1, $t0",
//             "slt $t3, $t1, $t2",
//             "beq $t0, $t1, 0",
//             "bne $t0, $t1, 0",
//             "addi $ra, $t5, 10008",
//             "jr $ra",
//             "lw $t4, 10000($t1)",
//             "sw $t5, 4($t1)",
//             "jal 1000"
//      *
//      */
//     MipsSimulator mips;
//     mips.load(input);
//     mips.Execute();
//     mips.Showallreg();
// }

// void test_for_Converter()
// {
//     // std::string a = "00000000000000000000000000001011"; // 11
//     // std::string b = "00000000000000000000000000001101"; // 13

//     int num1, num2;
//     std::cout << "Input two test integers" << std::endl;
//     std::cin >> num1 >> num2;
//     std::string a = intToBin(num1);
//     std::string b = intToBin(num2);
//     std::string sumi = addInt(a, b);
//     std::string differencei = subInt(a, b);
//     std::string producti = multiplyInt(a, b);
//     std::string quotienti = divideInt(a, b);

//     std::cout << "Input 1: " << num1 << std::endl;
//     std::cout << "Binary representation: " << a << std::endl;
//     std::cout << "Input 2: " << num2 << std::endl;
//     std::cout << "Binary representation: " << b << std::endl;

//     std::cout << "Integer Addition: " << sumi << " " << binToInt(sumi) << std::endl;
//     std::cout << "Integer Subtraction: " << differencei << " " << binToInt(differencei) << std::endl;
//     std::cout << "Integer Multiplication: " << producti << " " << binToInt(producti) << std::endl;
//     std::cout << "Integer Division: " << quotienti << " " << binToInt(quotienti) << std::endl;

//     float num3, num4;
//     std::cout << "Input two test floats" << std::endl;
//     std::cin >> num3 >> num4;
//     FloatConverter converter1 = floatToBin(num3);
//     FloatConverter converter2 = floatToBin(num4);

//     std::cout << "Input 3: " << num3 << std::endl;
//     printFloatBin(converter1);
//     std::cout << "Input 4: " << num4 << std::endl;
//     printFloatBin(converter2);

//     FloatConverter sum = addFloats(converter1, converter2);
//     FloatConverter difference = subtractFloats(converter1, converter2);
//     FloatConverter product = multiplyFloats(converter1, converter2);
//     FloatConverter quotient = divideFloats(converter1, converter2);

//     std::cout << "Sum: " << binToFloat(sum) << std::endl;
//     printFloatBin(sum);
//     std::cout << "Difference: " << binToFloat(difference) << std::endl;
//     printFloatBin(difference);
//     std::cout << "Product: " << binToFloat(product) << std::endl;
//     printFloatBin(product);
//     std::cout << "Quotient: " << binToFloat(quotient) << std::endl;
//     printFloatBin(quotient);
// }

// void test_for_Assembler()
// {
//     string instr_add = Assemble("add $t0, $t1, $t2");
//     cout<<instr_add<<endl;
//     string instr_sub = Assemble("sub $t0, $t1, $t2");
//     cout<<instr_sub<<endl;
//     string instr_addi = Assemble("addi $t0, $t1, 1");
//     cout<<instr_addi<<endl; 
//     string instr_lw = Assemble("lw $t0, 4($t1)");
//     cout<<instr_lw<<endl;
//     string instr_sw = Assemble("sw $t0, -4($t1)");
//     cout<<instr_sw<<endl;
//     string instr_beq = Assemble("beq $t0, $t1, 500");
//     cout<<instr_beq<<endl;
//     string instr_bne = Assemble("bne $t0, $t1, 500");
//     cout<<instr_bne<<endl;
//     string instr_jal = Assemble("jal 4000");
//     cout<<instr_jal<<endl;
//     string instr_jr = Assemble("jr $ra");
//     cout<<instr_jr<<endl;
//     string instr_slt = Assemble("slt $t0, $t1, $t2");
//     cout<<instr_slt<<endl;
// }
