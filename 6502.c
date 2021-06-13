
// Tweak these to your liking.

// Memory size
#define MEM 0x10000
// Stack start address
#define STK 0x200
// BRK vector
#define BRKV 0xF800
// NMI vector
#define NMIV 0xF802
// Reset vector
#define RESV 0xFFFC
// IRQ vector
#define IRQV 0xFFFE

// Emulator: Procedures and variables.

#include <stdint.h>
#include <assert.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef int8_t i8;
typedef _Bool n1;
#define su8 static u8

su8*m;u16 pc;u8 a,x,y,sp;
n1 cf,zf,idf,df,bf,vf,nf;

// Emulator: Code.

#define R return
#define ZFN(r,n) static inline r n(void)
#define MFN(r,n,a1) static inline r n(a1 A)
#define DFN(r,n,a1,a2) static inline r n(a1 A, a2 B)
#define SHF(x,b)x=(A>>b)&1
#define REGO(n)MFN(void,n ## R,u8*){*A=n(*A);}
#define MEMO(n)MFN(void,n ## A,u16){u8 v=R8(A);W8(A,n(v));}
#define IH(V) ;break;case V:
MFN(u8,R8,u16){R m[A];}MFN(u16,R16,u16){R(m[A+1]<<8)|m[A];}ZFN(u8,POP8){R R8(++sp+STK);}
MFN(u16,RB16,u16){R(m[(A&0xFF00)|((A+1)&0xFF)]<<8)|m[A];}DFN(void,W8,u16,u8){m[A]=B;}
ZFN(u8,ZPG){R R8(pc++);}ZFN(u8,ZPX){R ZPG()+x;}ZFN(u8,ZPY){R ZPG()+y;}
ZFN(u16,ABS){u16 A=R16(pc);pc+=2;R A;}ZFN(u16,ABX){R ABS()+x;}ZFN(u16,ABY){R ABS()+y;}
ZFN(u16,INX){R RB16((R8(pc++)+x)&0xFF);}ZFN(u16,INY){R RB16(R8(pc++))+y;}
ZFN(i8,REL){R(i8)R8(pc++);} // XXX: Relative addressing requires signed arithmetic.
MFN(void,PSH16,u16){u16 l=STK+sp;W8(l,A>>8);W8(l-1,A&0xFF);sp-=2;}ZFN(u16,IMM){R pc++;}
ZFN(u16,POP16){R POP8()|(POP8()<<8);}MFN(void,PSH8,u8){W8(STK+sp--,A);}
MFN(void,ADJZN,u8){zf=A==0;nf=A>>7;}ZFN(u8,GFL){R nf<<7|vf<<6|32|bf<<4|df<<3|idf<<2|zf<<1|cf;}
MFN(void,SFL,u8){SHF(nf,7);SHF(vf,6);SHF(bf,4);SHF(df,3);SHF(idf,2);SHF(zf,1);SHF(cf,0);}
MFN(void,INTR,u16){PSH16(pc);PSH8(GFL());pc=R16(A);idf=1;}DFN(void,LDR,u8*,u16){*A=R8(B);ADJZN(*A);}
MFN(void,ADC,u16){u8 V=R8(A),cy,l,h;if(df){cy=cf;l=(V&0xF)+(a&0xF)+cy;if(l>9)l+=6;
h=(V>>4)+(a>>4)+(l>0xF);vf=~(a^V)&(a^(h<<4))&0x80;nf=vf=zf=cf=0;if(h>9)h+=6;
if(h>0xF)cf=1;a=(h<<4)|(l&0xF);if(!a)zf=1;if(h&0x8)nf=1;}else{u16 r=a+V+cf;
ADJZN(r&0xFF);vf=(~(a^V)&(a^r)&0x80);cf=r&0xFF00;a=r&0xFF;}}
MFN(void,SBC,u16){u8 V=R8(A),l,h;u16 r;if(df){u8 cy=!cf;r=a-V-cy;l=(a&0xF)-(V&0xF)-cy;
if(l>>7)l-=6;h=(a>>4)-(V>>4)-(l>>7);nf=vf=zf=cf=0;if((a^V)&(a^r)&0x80)vf=1;cf=!(r&0xFF00);
if(h>>7)h-=6;a=(h<<4)|(l&0xF);if(!a)zf=1;if(h&0x8)nf=1;}else{r=a-V-!cf;ADJZN(r&0xFF);
vf=(a^V)&(a^r)&0x80;cf=!(r&0xFF00);a=r&0xFF;}}
MFN(u8,INC,u8){u8 r=A+1;ADJZN(r);R r;}MFN(u8,DEC,u8){u8 r=A-1;ADJZN(r);R r;}
MFN(u8,ASL,u8){u8 r=A<<1;cf=A>>7;ADJZN(r);R r;}MFN(void,AND,u16){a&=R8(A);ADJZN(a);}
MFN(void,BIT,u16){u8 v=R8(A);vf=(v>>6)&1;zf=(v&a)==0;nf=v>>7;}
MFN(void,EOR,u16){a^=R8(A);ADJZN(a);}MFN(u8,LSR,u8){u8 r=A>>1;cf=A&1;ADJZN(r);R r;}
MFN(void,ORA,u16){a|=R8(A);ADJZN(a);}MFN(u8,ROL,u8){u8 r=A<<1;r|=cf;cf=A>>7;ADJZN(r);R r;}
MFN(u8,ROR,u8){u8 r=A>>1;r|=cf<<7;cf=A&1;ADJZN(r);R r;}DFN(void,J,i8,n1){if(B)pc+=A;}
MFN(void,U,u16){pc=A;}MFN(void,JSR,u16){PSH16(pc-1);pc=A;}ZFN(void,RTI){SFL(POP8());pc=POP16();}
ZFN(void,RTS){pc=POP16()+1;}DFN(void,CMP,u16,u8){u8 v=R8(A);u8 r=B-v;cf=B>=v;ADJZN(r);}
MEMO(INC)REGO(INC)MEMO(DEC)REGO(DEC)MEMO(ASL)MEMO(LSR)MEMO(ROR)MEMO(ROL)
ZFN(void,init){sp=0xFD;pc=a=x=y=zf=cf=idf=df=bf=vf=nf=0;}ZFN(void,nmi){bf=0;INTR(NMIV);}
ZFN(void,res){bf=0;INTR(RESV);}ZFN(void,irq){if(idf==0){bf=0;INTR(IRQV);}}

// Emulator: Instruction stepping.

ZFN(void,step){switch(R8(pc++)){
    default:
    IH(0xA9)LDR(&a,IMM()) /* LDA IMM */ IH(0xA5)LDR(&a,ZPG()) /* LDA ZPG */
    IH(0xB5)LDR(&a,ZPX()) /* LDA ZPX */ IH(0xAD)LDR(&a,ABS()) /* LDA ABS */
    IH(0xBD)LDR(&a,ABX()) /* LDA ABX */ IH(0xB9)LDR(&a,ABY()) /* LDA ABY */
    IH(0xA1)LDR(&a,INX()) /* LDA INX */ IH(0xB1)LDR(&a,INY()) /* LDA INY */
    IH(0xA2)LDR(&x,IMM()) /* LDX IMM */ IH(0xA6)LDR(&x,ZPG()) /* LDX ZPG */
    IH(0xB6)LDR(&x,ZPY()) /* LDX ZPY */ IH(0xAE)LDR(&x,ABS()) /* LDX ABS */
    IH(0xBE)LDR(&x,ABY()) /* LDX ABY */ IH(0xA0)LDR(&y,IMM()) /* LDY IMM */
    IH(0xA4)LDR(&y,ZPG()) /* LDY ZPG */ IH(0xB4)LDR(&y,ZPX()) /* LDY ZPX */
    IH(0xAC)LDR(&y,ABS()) /* LDY ABS */ IH(0xBC)LDR(&y,ABX()) /* LDY ABX */
    IH(0x85)W8(ZPG(),a)   /* STA ZPG */ IH(0x95)W8(ZPX(),a)   /* STA ZPX */
    IH(0x8D)W8(ABS(),a)   /* STA ABS */ IH(0x9D)W8(ABX(),a)   /* STA ABX */
    IH(0x99)W8(ABY(),a)   /* STA ABY */ IH(0x81)W8(INX(),a)   /* STA INX */
    IH(0x91)W8(INY(),a)   /* STA INY */ IH(0x86)W8(ZPG(),x)   /* STX ZPG */
    IH(0x96)W8(ZPY(),x)   /* STX ZPY */ IH(0x8E)W8(ABS(),x)   /* STX ABS */
    IH(0x84)W8(ZPG(),y)   /* STY ZPG */ IH(0x94)W8(ZPX(),y)   /* STY ZPX */
    IH(0x8C)W8(ABS(),y)   /* STY ABS */
    IH(0xAA)x=a;ADJZN(x)  /* TAX */     IH(0xA8)y=a;ADJZN(y)  /* TAY */
    IH(0xBA)x=sp;ADJZN(x) /* TSX */     IH(0x8A)a=x;ADJZN(a)  /* TXA */
    IH(0x9A)sp=x          /* TXS */     IH(0x98)a=y;ADJZN(a)  /* TYA */
    IH(0x69)ADC(IMM())    /* ADC IMM */ IH(0x65)ADC(ZPG())    /* ADC ZPG */
    IH(0x75)ADC(ZPX())    /* ADC ZPX */ IH(0x6D)ADC(ABS())    /* ADC ABS */
    IH(0x7D)ADC(ABX())    /* ADC ABX */ IH(0x79)ADC(ABY())    /* ADC ABY */
    IH(0x61)ADC(INX())    /* ADC INX */ IH(0x71)ADC(INY())    /* ADC INY */
    IH(0xC6)DECA(ZPG())   /* DEC ZPG */ IH(0xD6)DECA(ZPX())   /* DEC ZPX */
    IH(0xCE)DECA(ABS())   /* DEC ABS */ IH(0xDE)DECA(ABX())   /* DEC ABX */
    IH(0xCA)DECR(&x)      /* DEX */     IH(0x88)DECR(&y)      /* DEY */
    IH(0xE6)INCA(ZPG())   /* INC ZPG */ IH(0xF6)INCA(ZPX())   /* INC ZPX */
    IH(0xEE)INCA(ABS())   /* INC ABS */ IH(0xFE)INCA(ABX())   /* INC ABX */
    IH(0xE8)INCR(&x)      /* INX */     IH(0xC8)INCR(&y)      /* INY */
    IH(0xE9)SBC(IMM())    /* SBC IMM */ IH(0xE5)SBC(ZPG())    /* SBC ZPG */
    IH(0xF5)SBC(ZPX())    /* SBC ZPX */ IH(0xED)SBC(ABS())    /* SBC ABS */
    IH(0xFD)SBC(ABX())    /* SBC ABX */ IH(0xF9)SBC(ABY())    /* SBC ABY */
    IH(0xE1)SBC(INX())    /* SBC INX */ IH(0xF1)SBC(INY())    /* SBC INY */
    IH(0x29)AND(IMM())    /* AND IMM */ IH(0x25)AND(ZPG())    /* AND ZPG */
    IH(0x35)AND(ZPX())    /* AND ZPX */ IH(0x2D)AND(ABS())    /* AND ABS */
    IH(0x3D)AND(ABX())    /* AND ABX */ IH(0x39)AND(ABY())    /* AND ABY */
    IH(0x21)AND(INX())    /* AND INX */ IH(0x31)AND(INY())    /* AND INY */
    IH(0x0A)a=ASL(a)      /* ASL ACC */ IH(0x06)ASLA(ZPG())   /* ASL ZPG */
    IH(0x16)ASLA(ZPX())   /* ASL ZPX */ IH(0x0E)ASLA(ABS())   /* ASL ABS */
    IH(0x1E)ASLA(ABX())   /* ASL ABX */
    IH(0x24)BIT(ZPG())    /* BIT ZPG */ IH(0x2C)BIT(ABS())    /* BIT ABS */
    IH(0x49)EOR(IMM())    /* EOR IMM */ IH(0x45)EOR(ZPG())    /* EOR ZPG */
    IH(0x55)EOR(ZPX())    /* EOR ZPX */ IH(0x4D)EOR(ABS())    /* EOR ABS */
    IH(0x5D)EOR(ABX())    /* EOR ABX */ IH(0x59)EOR(ABY())    /* EOR ABY */
    IH(0x41)EOR(INX())    /* EOR INX */ IH(0x51)EOR(INY())    /* EOR INY */
    IH(0x4A)a=LSR(a)      /* LSR ACC */ IH(0x46)LSRA(ZPG())   /* LSR ZPG */
    IH(0x56)LSRA(ZPX())   /* LSR ZPX */ IH(0x4E)LSRA(ABS())   /* LSR ABS */
    IH(0x5E)LSRA(ABX())   /* LSR ABX */ IH(0x09)ORA(IMM())    /* ORA IMM */
    IH(0x05)ORA(ZPG())    /* ORA ZPG */ IH(0x15)ORA(ZPX())    /* ORA ZPX */
    IH(0x0D)ORA(ABS())    /* ORA ABS */ IH(0x1D)ORA(ABX())    /* ORA ABX */
    IH(0x19)ORA(ABY())    /* ORA ABY */ IH(0x01)ORA(INX())    /* ORA IMM */
    IH(0x11)ORA(INY())    /* ORA IMM */ IH(0x2A)a=ROL(a)      /* ROL ACC */
    IH(0x26)ROLA(ZPG())   /* ROL ZPG */ IH(0x36)ROLA(ZPX())   /* ROL ZPX */
    IH(0x2E)ROLA(ABS())   /* ROL ABS */ IH(0x3E)ROLA(ABX())   /* ROL ABX */
    IH(0x6A)a=ROR(a)      /* ROR ACC */ IH(0x66)RORA(ZPG())   /* ROR ZPG */
    IH(0x76)RORA(ZPX())   /* ROR ZPX */ IH(0x6E)RORA(ABS())   /* ROR ABS */
    IH(0x7E)RORA(ABX())   /* ROR ABX */ IH(0x90)J(REL(),!cf)  /* BCC REL */
    IH(0xB0)J(REL(),cf)   /* BCS REL */ IH(0xD0)J(REL(),!zf)  /* BNE REL */
    IH(0xF0)J(REL(),zf)   /* BEQ REL */ IH(0x10)J(REL(),!nf)  /* BPL REL */
    IH(0x30)J(REL(),nf)   /* BMI REL */ IH(0x50)J(REL(),!vf)  /* BVC REL */
    IH(0x70)J(REL(),vf)   /* BVS REL */ IH(0x4C)U(ABS())      /* JMP */
    IH(0x6C)U(RB16(ABS()))/* JMP */     IH(0x20)JSR(ABS())    /* JSR */
    IH(0x40)RTI()         /* RTI */     IH(0x60)RTS()         /* RTS */
    IH(0x38)cf=1          /* SEC */     IH(0x18)cf=0          /* CLC */
    IH(0xF8)df=1          /* SED */     IH(0xD8)df=0          /* CLD */
    IH(0x78)idf=1         /* SEI */     IH(0x58)idf=0         /* CLI */
    IH(0xB8)vf=0          /* CLV */
    IH(0xC9)CMP(IMM(),a)  /* CMP IMM */ IH(0xC5)CMP(ZPG(),a)  /* CMP ZPG */
    IH(0xD5)CMP(ZPX(),a)  /* CMP ZPX */ IH(0xCD)CMP(ABS(),a)  /* CMP ABS */
    IH(0xDD)CMP(ABX(),a)  /* CMP ABX */ IH(0xD9)CMP(ABY(),a)  /* CMP ABY */
    IH(0xC1)CMP(INX(),a)  /* CMP INX */ IH(0xD1)CMP(INY(),a)  /* CMP INY */
    IH(0xE0)CMP(IMM(),x)  /* CPX IMM */ IH(0xE4)CMP(ZPG(),x)  /* CPX ZPG */
    IH(0xEC)CMP(ABS(),x)  /* CPX ABS */ IH(0xC0)CMP(IMM(),y)  /* CPY IMM */
    IH(0xC4)CMP(ZPG(),y)  /* CPY ZPG */ IH(0xCC)CMP(ABS(),y)  /* CPY ABS */

    IH(0x48)PSH8(a)       /* PHA */     IH(0x68)a=POP8();ADJZN(a) /* PLA */
    IH(0x08)bf=1;PSH8(GFL()) /* PHP */  IH(0x28)SFL(POP8())   /* PLP */
    IH(0x00)bf=1;pc+=1;INTR(BRKV) /* BRK */
    IH(0xEA)break; /* NOP */
    }
}

// Test code for the emulator.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;

DFN(void, loadmem, const char *, u16) {
    u32 size;
    FILE * f = fopen(A, "rb"); assert(f);
    fseek(f, 0, SEEK_END); size = ftell(f); rewind(f);
    assert(size + B <= MEM);
    assert(fread(&m[B], sizeof(u8), size, f) == size);
    fclose(f);
}

ZFN(void, test1) {
    memset(m, 0, MEM);
    loadmem("test1.bin", 0x4000);
    init(); res();

    for(;;) {
        step();

        if (pc == 0x45C0) {
            printf("%s\n", m[0x0210] == 0xFF ? "passed" : "failed");
            return;
        }
    }
}

int main(void) {
    m = malloc(MEM);
    test1();
}
