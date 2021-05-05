class Processor
{
public:
    long A;
    long X;
    long Y;

    // flags
    bool GF;
    bool LF;
    bool EF;

    long PC;
    long SP;
    long mem[512];

    void brk() {
        /*
        *  we will not do anything for brk()
        *  because it is the break opcode
        *  if we dont increment the PC
        *  we will not continue execution.
        */
    }

    /*
    *   if you see:   
    *   this->PC += 2;
    *   instead of:
    *   this->PC++;
    * 
    *   the opcode is 2 bytes long (parameter)
    */

    //
    // register ops

    void lda(long v) { this->A = v; this->PC+=2; }
    void ldx(long v) { this->X = v; this->PC+=2; }
    void ldy(long v) { this->Y = v; this->PC+=2; }
    void str(long addr) { this->mem[addr] = this->A; this->PC+=2; }

    // transfer ops

    void txa() { this->A = this->X; this->X = 0; this->PC++; }
    void txy() { this->Y = this->X; this->X = 0; this->PC++; }
    void tya() { this->A = this->Y; this->Y = 0; this->PC++; }
    void tyx() { this->X = this->Y; this->Y = 0; this->PC++; }
    void tax() { this->A = this->X; this->X = 0; this->PC++; }
    void tay() { this->A = this->Y; this->Y = 0; this->PC++; }

    // jump ops

    void jmp(long addr) { this->PC = addr; }
    void jgt(long addr)
    {
        if (this->GF)
        {
            this->PC = addr;
        }
    }
    void jlt(long addr)
    {
        if (this->LF)
        {
            this->PC = addr;
        }
    }
    void jet(long addr)
    {
        if (this->EF)
        {
            this->PC = addr;
        }
    }

    // compare ops

    void cmp(long v)
    {

        this->GF = false;
        this->EF = false;
        this->LF = false;

        if (v > this->A)
        {
            this->GF = true;
        }
        if (v < this->A)
        {
            this->LF = true;
        }
        if (v == this->A)
        {
            this->EF = true;
        }
        this->PC += 2;
    }

    void add(long v) { this->A += v; this->PC+=2; }
    void sub(long v) { this->A -= v; this->PC+=2; }

    void inc(void) { this->A++; this->PC++; }
    void inx(void) { this->X++; this->PC++; }
    void iny(void) { this->Y++; this->PC++; }
};
