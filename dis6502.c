
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Instruction tables. Copied from some online source.

enum { IMP, IMPA, MARK2, BRA, IMM, ZP, ZPX, ZPY, INDX, INDY, IND, MARK3, ABS, ABSX, ABSY, IND16, IND1X };
enum { I_ADC, I_AND, I_ASL, I_BCC, I_BCS, I_BEQ, I_BIT, I_BMI, I_BNE, I_BPL, I_BRA, I_BRK, I_BVC, I_BVS,
       I_CLC, I_CLD, I_CLI, I_CLV, I_CMP, I_CPX, I_CPY, I_DEC, I_DEX, I_DEY, I_EOR, I_INC, I_INX, I_INY,
       I_JMP, I_JSR, I_LDA, I_LDX, I_LDY, I_LSR, I_NOP, I_ORA, I_PHA, I_PHP, I_PHX, I_PHY, I_PLA, I_PLP,
       I_PLX, I_PLY, I_ROL, I_ROR, I_RTI, I_RTS, I_SBC, I_SEC, I_SED, I_SEI, I_STA, I_STP, I_STX, I_STY,
       I_STZ, I_TAX, I_TAY, I_TRB, I_TSB, I_TSX, I_TXA, I_TXS, I_TYA, I_WAI, I_XXX };

char ops[] =
      "ADCANDASLBCCBCSBEQBITBMIBNEBPLBRABRKBVCBVS"
      "CLCCLDCLICLVCMPCPXCPYDECDEXDEYEORINCINXINY"
      "JMPJSRLDALDXLDYLSRNOPORAPHAPHPPHXPHYPLAPLP"
      "PLXPLYROLRORRTIRTSSBCSECSEDSEISTASTPSTXSTY"
      "STZTAXTAYTRBTSBTSXTXATXSTYAWAI???";

char insname[256] = {
    I_BRK, I_ORA, I_XXX, I_XXX, I_TSB, I_ORA, I_ASL, I_XXX, I_PHP, I_ORA, I_ASL, I_XXX, I_TSB, I_ORA, I_ASL, I_XXX,
    I_BPL, I_ORA, I_ORA, I_XXX, I_TRB, I_ORA, I_ASL, I_XXX, I_CLC, I_ORA, I_INC, I_XXX, I_TRB, I_ORA, I_ASL, I_XXX,
    I_JSR, I_AND, I_XXX, I_XXX, I_BIT, I_AND, I_ROL, I_XXX, I_PLP, I_AND, I_ROL, I_XXX, I_BIT, I_AND, I_ROL, I_XXX,
    I_BMI, I_AND, I_AND, I_XXX, I_BIT, I_AND, I_ROL, I_XXX, I_SEC, I_AND, I_DEC, I_XXX, I_BIT, I_AND, I_ROL, I_XXX,
    I_RTI, I_EOR, I_XXX, I_XXX, I_XXX, I_EOR, I_LSR, I_XXX, I_PHA, I_EOR, I_LSR, I_XXX, I_JMP, I_EOR, I_LSR, I_XXX,
    I_BVC, I_EOR, I_EOR, I_XXX, I_XXX, I_EOR, I_LSR, I_XXX, I_CLI, I_EOR, I_PHY, I_XXX, I_XXX, I_EOR, I_LSR, I_XXX,
    I_RTS, I_ADC, I_XXX, I_XXX, I_STZ, I_ADC, I_ROR, I_XXX, I_PLA, I_ADC, I_ROR, I_XXX, I_JMP, I_ADC, I_ROR, I_XXX,
    I_BVS, I_ADC, I_ADC, I_XXX, I_STZ, I_ADC, I_ROR, I_XXX, I_SEI, I_ADC, I_PLY, I_XXX, I_JMP, I_ADC, I_ROR, I_XXX,
    I_BRA, I_STA, I_XXX, I_XXX, I_STY, I_STA, I_STX, I_XXX, I_DEY, I_BIT, I_TXA, I_XXX, I_STY, I_STA, I_STX, I_XXX,
    I_BCC, I_STA, I_STA, I_XXX, I_STY, I_STA, I_STX, I_XXX, I_TYA, I_STA, I_TXS, I_XXX, I_STZ, I_STA, I_STZ, I_XXX,
    I_LDY, I_LDA, I_LDX, I_XXX, I_LDY, I_LDA, I_LDX, I_XXX, I_TAY, I_LDA, I_TAX, I_XXX, I_LDY, I_LDA, I_LDX, I_XXX,
    I_BCS, I_LDA, I_LDA, I_XXX, I_LDY, I_LDA, I_LDX, I_XXX, I_CLV, I_LDA, I_TSX, I_XXX, I_LDY, I_LDA, I_LDX, I_XXX,
    I_CPY, I_CMP, I_XXX, I_XXX, I_CPY, I_CMP, I_DEC, I_XXX, I_INY, I_CMP, I_DEX, I_WAI, I_CPY, I_CMP, I_DEC, I_XXX,
    I_BNE, I_CMP, I_CMP, I_XXX, I_XXX, I_CMP, I_DEC, I_XXX, I_CLD, I_CMP, I_PHX, I_STP, I_XXX, I_CMP, I_DEC, I_XXX,
    I_CPX, I_SBC, I_XXX, I_XXX, I_CPX, I_SBC, I_INC, I_XXX, I_INX, I_SBC, I_NOP, I_XXX, I_CPX, I_SBC, I_INC, I_XXX,
    I_BEQ, I_SBC, I_SBC, I_XXX, I_XXX, I_SBC, I_INC, I_XXX, I_SED, I_SBC, I_PLX, I_XXX, I_XXX, I_SBC, I_INC, I_XXX
};

char addrmode[256] = {
    IMP, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMPA,  IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZP,   ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMPA,  IMP,  ABS,	  ABSX,	 ABSX, IMP,
    ABS, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMPA,  IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZPX,  ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMPA,  IMP,  ABSX,	  ABSX,	 ABSX, IMP,
    IMP, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMPA,  IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZP,   ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMP,   IMP,  ABS,	  ABSX,	 ABSX, IMP,
    IMP, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMPA,  IMP,  IND16,  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZPX,  ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMP,   IMP,  IND1X,  ABSX,	 ABSX, IMP,
    BRA, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMP,   IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZPX,  ZPX,   ZPY,	 IMP,	IMP,  ABSY,  IMP,   IMP,  ABS,	  ABSX,	 ABSX, IMP,
    IMM, INDX,  IMM, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMP,   IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZPX,  ZPX,   ZPY,	 IMP,	IMP,  ABSY,  IMP,   IMP,  ABSX,	  ABSX,	 ABSY, IMP,
    IMM, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMP,   IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZP,   ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMP,   IMP,  ABS,	  ABSX,	 ABSX, IMP,
    IMM, INDX,  IMP, IMP,  ZP,   ZP,	   ZP,	 IMP,	IMP,  IMM,   IMP,   IMP,  ABS,	  ABS,	 ABS,  IMP,
    BRA, INDY,  IND, IMP,  ZP,   ZPX,   ZPX,	 IMP,	IMP,  ABSY,  IMP,   IMP,  ABS,	  ABSX,	 ABSX, IMP
};

// The disassembler part.

uint16_t disassemble(uint16_t addr) {
    uint16_t temp, mode, ind;
    uint8_t p1, p2;
    uint8_t op = getchar();
    mode = addrmode[op];
    p1 = (mode > MARK2) ? getchar() : 0;
    p2 = (mode > MARK3) ? getchar() : 0;
    ind = insname[op] * 3;
    printf("%04X   ", addr);
    if(mode > MARK3)
        printf("%02X %02X %02X   ", op, p1, p2);
    else if(mode > MARK2)
        printf("%02X %02X      ", op, p1);
    else
        printf("%02X         ", op);
    for(temp = 0; temp < 3; temp++)
        putchar(ops[ind + temp]);
    putchar(' ');
    switch (mode) {
        case IMPA: putchar('A'); break;
        case BRA: temp = addr + 2 + (signed char) p1; printf("%04X", temp); addr++; break;
        case IMM: printf("#$%02X", p1); addr++; break;
        case ZP: printf("$%02X", p1); addr++; break;
        case ZPX: printf("$%02X,X", p1); addr++; break;
        case ZPY: printf("$%02X,Y", p1); addr++; break;
        case IND: printf("($%02X)", p1); addr++; break;
        case INDX: printf("($%02X,X)", p1); addr++; break;
        case INDY: printf("($%02X),Y", p1); addr++; break;
        case ABS: printf("$%02X%02X", p2, p1); addr += 2; break;
        case ABSX: printf("$%02X%02X,X", p2, p1); addr += 2; break;
        case ABSY: printf("$%02X%02X,Y", p2, p1); addr += 2; break;
        case IND16: printf("($%02X%02X)", p2, p1); addr += 2; break;
        case IND1X: printf("($%02X%02X,X)", p2, p1); addr += 2; break;
    }
    putchar('\n');
    addr++;
    return addr;
}

// Converting a string to a number in a smart way (detecting the base)

static int smart_cvt(char * number) {
    int base = 10;
    if(!strncmp(number, "0x", 2)) base = 16;
    else if(!strncmp(number, "0b", 2)) base = 2;
    else if(!strncmp(number, "0o", 2)) base = 8;
    return strtol((base != 10) * 2 + number, NULL, base);
}

int main(int argc, char * argv[]) {
    uint16_t addr = argc == 2 ? smart_cvt(argv[1]) : 0;
    printf("                  * = $%04X\n", addr);
    while(!feof(stdin))
        addr = disassemble(addr);
}
