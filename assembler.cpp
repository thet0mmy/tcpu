#include <iostream>
#include <string>
#include <locale>
#include <fstream>

#include "opcodes.hpp"
#include "cpu.hpp"

/*
*   Tommy Wilson 5.5.2021
*   Assembler for Tommy's CPU
*/

std::ifstream f;
std::ofstream o("out");

std::string asmline;

std::string asmop;
std::string asmp;

int opcode;
int opparam;

std::string asmdict[] = {
    "brk", "lda", "ldx", "ldy", "str",
    "txa", "txy", "tya", "tyx", "tax", "tay",
    "jmp", "jgt", "jlt", "jet", "cmp",
    "add", "sub", "inc", "inx", "iny"};

int findspace(std::string s)
{
    for (int sp = 1; sp < s.length() + 1; sp++)
    {
        if (s.c_str()[sp] == ' ')
        {
            return sp++;
        }
    }
    return -1;
}

int isDicted(std::string op)
{
    for (int oit = 0; oit < (sizeof(asmdict) / sizeof(asmdict[1])) + 1; oit++)
    {
        if (asmdict[oit] == op)
        {
            return oit;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Not enough files to assemble" << std::endl;
        return 0;
    }

    f.open(argv[1]);
    std::cout << "Tommy's CPU assembler" << std::endl;
    while (!f.eof())
    {
        std::getline(f, asmline);

        if (asmline.length() > 2)
        {
            asmop = asmline.substr(0, findspace(asmline));
            asmp = asmline.substr(findspace(asmline) + 1, asmline.length());
            int dictval = isDicted(asmop);
            if (dictval > 0)
            {
                opcode = dictval;
                opparam = atoi(asmp.c_str());
                if (opcode != 0)
                {
                    o << opcode << std::endl;
                    if (opparam != 0)
                    {
                        o << opparam << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "^";
            }
        }
        else
        {
            std::cout << "^";
        }
    }
    f.close();

    std::cout << std::endl;
    return 0;
}