#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

#include "opcodes.hpp"
#include "cpu.hpp"

int pokeaddr;
int pokeval;

std::ifstream f;
Processor *cpu = new Processor;

bool pokemode = false;
bool gomode = false;
char prompt = '@';

void execute(void)
{
    std::cout << "init" << std::endl;
    while (cpu->mem[cpu->PC] != 0)
    {
        std::cout << "CPU cycled" << std::endl;
        switch (cpu->mem[cpu->PC])
        {
        case BRK:
            std::cout << "BRK" << std::endl;
            cpu->brk();
            gomode = false;
            return;
        case LDA:
            std::cout << "LDA" << std::endl;
            cpu->lda(cpu->mem[cpu->PC + 1]);
            break;

        case LDX:
            std::cout << "LDX" << std::endl;
            cpu->ldx(cpu->mem[cpu->PC + 1]);
            break;
        case LDY:
            std::cout << "LDY" << std::endl;
            cpu->ldy(cpu->mem[cpu->PC + 1]);
            break;
        case STR:
            std::cout << "STR" << std::endl;
            cpu->str(cpu->mem[cpu->PC + 1]);
            break;

            // transfers

        case TXA:
            std::cout << "TXA" << std::endl;
            cpu->txa();
            break;
        case TXY:
            std::cout << "TXY" << std::endl;
            cpu->txy();
            break;
        case TYA:
            std::cout << "TYA" << std::endl;
            cpu->tya();
            break;
        case TYX:
            std::cout << "TYX" << std::endl;
            cpu->tyx();
            break;
        case TAX:
            std::cout << "TAX" << std::endl;
            cpu->tax();
            break;
        case TAY:
            std::cout << "TAY" << std::endl;
            cpu->tay();
            break;

            // jumps

        case JMP:
            std::cout << "JMP" << std::endl;
            cpu->jmp(cpu->mem[cpu->PC + 1]);
            break;
        case JLT:
            std::cout << "JLT" << std::endl;
            cpu->jlt(cpu->mem[cpu->PC + 1]);
            break;
        case JGT:
            std::cout << "JGT" << std::endl;
            cpu->jgt(cpu->mem[cpu->PC + 1]);
            break;
        case JET:
            std::cout << "JET" << std::endl;
            cpu->jet(cpu->mem[cpu->PC + 1]);
            break;
        case CMP:
            std::cout << "CMP" << std::endl;
            cpu->cmp(cpu->mem[cpu->PC + 1]);
            break;

            // arithmetic

        case ADD:
            std::cout << "ADD" << std::endl;
            cpu->add(cpu->mem[cpu->PC + 1]);
            break;
        case SUB:
            std::cout << "SUB" << std::endl;
            cpu->sub(cpu->mem[cpu->PC + 1]);
            break;

            // incrementation

        case INC:
            std::cout << "INC" << std::endl;
            cpu->inc();
            break;
        case INX:
            std::cout << "INX" << std::endl;
            cpu->inx();
            break;
        case INY:
            std::cout << "INY" << std::endl;
            cpu->iny();
            break;
        default:
            std::cout << "processor panic (bad opcode)" << std::endl;
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    while (1 < 2)
    {
    monstart:

        prompt = '@';

        std::cout << prompt;
        std::cin >> pokeaddr;
    monmain:
        if (!pokemode)
        {
            if (pokeaddr < 256)
            {
                if (pokeaddr > 0)
                {
                    std::cout << pokeaddr << " >-< " << cpu->mem[pokeaddr] << std::endl;
                }
                else
                {
                    if (pokeaddr == -1)
                    {
                        // enter POKE mode
                        prompt = '%';
                        pokemode = true;
                        goto monmain;
                    }
                    if (pokeaddr == -2)
                    {
                        cpu->jmp(1); // jump to address $00
                        std::cout << "JMP'd" << std::endl;
                        gomode = true;

                        execute();
                    }
                    if (pokeaddr == -3)
                    {
                        std::cout << "PC: " << cpu->PC << " SP: " << cpu->SP << std::endl;
                        std::cout << "A: " << cpu->A << " X: " << cpu->X << " Y: " << cpu->Y << std::endl;
                    }
                    if (pokeaddr == -4)
                    {
                        std::string dline;
                        f.open("out");

                        int loadctr = 0;

                        while(!f.eof()) {
                            loadctr++;
                            std::getline(f,dline);
                            cpu->mem[loadctr] = atoi(dline.c_str());
                        }
                        f.close();
                    }
                }
            }
            else
            {
                std::cout << "index out of memory bounds" << std::endl;
            }
        }
        else
        {
            while (pokemode)
            {
                std::cout << "%";
                std::cin >> pokeaddr;

                if (pokeaddr == -1)
                {
                    pokemode = false;
                    break;
                }

                std::cout << "&";
                std::cin >> pokeval;

                cpu->mem[pokeaddr] = pokeval;
            }
        }
    }
}