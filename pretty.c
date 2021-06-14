                #define R  return
                #include<stdio.h>
                #define _ typedef
               #include <stdint.h>
               #include <assert.h>
               #include <stdlib.h>
               #include <string.h>
             #define Z(r,n)r n(void)
            #define S(x,b) x=(A>>b)&1
            #define M(r,n,x) r n(x A)
          #define Q(V) ;break; case V:
         #define D(r,n,x,y) r n(x A,y B)
     #define X(n) M(void,n##R,q*){*A=n(*A);}
#define Y(n)M(void,n##A,w){q v=_A(A);W8(A,n(v));}
_ uint8_t q;_ uint16_t w;_ int8_t e;_ _Bool r;q*m
;w p;q a,x,y,s;r n,b        ,C,E,F,G,H;M(q,_A,w){
R m[A];}M(w,_B,w){R        (m[A+1]<<8)|m[A];}Z(q,
_C){R _A(++s+0x200        );}D(void,W8,w,q){m[A]=
B;}Z(q,_E){R _A(p        ++);}Z(q,_F){R _E()+x;}Z
(q,_G){R _E()+y;        }Z(w,_H){w A=_B(p);p+=2;R
A;}Z(w,_Z){R _H        ()+x;}Z(w,_Y){R _H()+y;}Z(
w,_O){R _B((_A        (p++)+x)&255);}Z(w,_P){R _B
(_A(p++))+y;}              Z(e,REL){R(e)_A(p++);}
M(void,_J,w)                 {w l=512+s;W8(l,A>>8
);W8(l+(-1),                  A&255);s-=2;}Z(w,_V
){R p++;}Z(w       ,_N){       R _C()|(_C()<<8);}
M(void,_K,q)       { W8(       512+s--,A);}M(void
,_I,q){b=A==                   0;H=A>>7;}Z(q,GFL)
{R H<<7|G<<6|                 32|F<<4|E<<3|C<<2|b
<< 1|n;}M(void,             __,q){S(H,7);S(G,6);S
(F,4);S(E,3);S(C,         2);S(b,1);S(n,0x10-0x10
);}M(void,___,w){_J(p);_K(GFL());p=_B(A);C=1;}D(
void,_X,q*,w                  ){*A=_A(B);_I(*A);}
M(void,ADC,w                  ){q V=_A(A),cy,l,h;
w r=a+V+n;_I                  (r&0xFF);G=(~(a^V)&
(a^r)&0x80);       n=r&0xFF00;a=r&255;}M(void,SBC
,w){q V=_A(A       ),l,h;w r;r=a-V-!n;_I(r&0xFF);
G=(a^V)&(a^r       )&0x80;n=!(r&0xFF00);a=r&0xFF;
}M(q,INC,q){                q r=A+1;_I(r);R r;}M(
q,_L,q){q r=                 A+(-1);_I(r);R r;}M(
q,ASL,q){q r                  =A<<1;n=A>>7;_I(r);
R r;}M(void,AND,w){a&=_A       (A);_I(a);}M(void,
BIT,w){q v=_A(A);G=(v>>6       )&1;b=(v&a)==0;H=v
>>7;}M(void,       EOR,w       ){a^=_A(A);_I(a);}
M(q,LSR,q){q                   r=A>>1;n=A&1;_I(r)
;R r;}M(void,                 _S,w){a|=_A(A);_I(a
);}M(q,ROL,q){q             r=A<<1;r|=n;n=A>>7;_I
(r);R r;}M(q,_M,q         ){q r=A>>1;r|=n<<7;n=A&
1;_I(r);R r;}D(void,J,e,r){if(B)p+=A;}M(void,U,w)
{p=A;}M(void,JSR,         w){_J(p-1);p=A;}Z(void,
_Q){__(_C());p=             _N();}Z(void, RTS){p=
_N()+1+(0);}D                 (void,_R,w, q){q v=
_A(A);q r=B-                   v;n=B>=v;_I(r);}Y(
INC)X(INC)Y(        _L)        X(_L)Y(ASL)Y(LSR)Y
(_M)Y(ROL)Z(       void,       init){s=0xFD;p=a=x
=y=b=n=C=E=F       =G=H=       0;}Z(void,nmi){F=0
;___(0xF802)       ;   }       Z(void,rs){F=0;___
(0xFFFC);}Z(       void,       irq){if(C==0){F=0;
___(65534);}       } Z (       void,step){switch(
_A((p=p+1)-1       ) ) {       default:Q(0xA9)_X(
&a, _V()) Q(        165        )_X(&a,_E())Q(0xB5
)_X(&a,_F())                   Q(0xAD)_X(&a,_H())
Q(0xBD)_X(&a,                 _Z())Q(185)_X(&a,_Y
())Q(0xA1)_X(&a             ,_O())Q(0xB1)_X(&a,_P
())Q(162)_X(&x,_V         ())Q(0xA6)_X(&x,_E())Q(
0xB6)_X(&x,_G())Q(0xAE)_X(&x,_H())Q(0xBE)_X(&x,_Y
())Q(0xA0)_X(               &y,_V())Q(0xA4)_X(&y,
_E())Q(0xB4)                  _X(&y,_F())Q(172)_X
(&y, _H())Q(                   0xBC)_X(&y,_Z())Q(
0x85)W8(_E()       ,a)Q(       149) W8(_F(), a)Q(
141)W8(_H(),a)Q(0x9D)W8(       _Z(),a)Q(153)W8(_Y
(),a)Q(0x81)W8(_O(),a)Q(       145) W8(_P(), a)Q(
134)W8(_E(),x)Q(0x96)         W8(_G(),x)Q(0x8E)W8
(_H(),x)Q(132)W8             (_E(),y)Q(0x94)W8(_F
(),y)Q(0x8C)W8             (_H(),y)Q(0xAA)x=a;_I(
x)Q(0xA8)y=a;           _I(y)Q(186)x=s;_I(x)Q(138
)a=x;_I(a)Q(       0x9A)s=x Q(0x98)a=y;_I(a)Q(105
)ADC(_V())Q(       0x65)ADC(_E())Q(0x75)ADC(_F())
Q(109)ADC(_H       () ) Q(      125)ADC(_Z( )) Q(
121)ADC(_Y()                    )Q(0x61)ADC(_O())
Q(113)ADC(_P                    ())Q(0xC6)_LA(_E(
))Q(0xD6)_LA                    (_F())Q(0xCE)_LA(
_H())Q(0xDE)_LA(_Z())Q(0xCA)_LR(&x)Q(0x88)_LR(&y)
Q(0xE6)INCA(_E())Q(0xF6)INCA(_F())Q(0xEE)INCA(_H(
))Q(0xFE)INCA(_Z())Q(0xE8)INCR(&x)Q(0xC8)INCR(&y)
Q(0xE9)SBC(_V())Q(0xE5)SBC(_E())Q(0xF5)SBC(_F())Q
(0xED)SBC(_H())Q(0xFD)SBC(_Z())Q(0xF9)SBC(_Y())Q(
0xE1)SBC(_O())Q(0xF1)SBC(_P())Q(41)AND(_V())Q(37)
AND(_E())Q(0x35)AND(_F())Q(0x2D)AND(_H())Q(61)AND
(_Z())Q(0x39)AND(_Y())Q(0x21)AND(_O())Q(0x31)AND(
_P())Q(0x0A)a=ASL(a)Q(0x06)ASLA(_E())Q(0x16)ASLA(
_F())Q(0x0E)ASLA(_H())Q(0x1E)ASLA(_Z())Q(0x24)BIT
(_E())Q(0x2C)BIT(_H())Q(0x49)EOR(_V())Q(0x45)EOR(
_E())Q(0x55)EOR(_F())Q(0x4D)EOR(_H())Q(93)EOR(_Z(
))Q(0x59)EOR(_Y())Q(0x41)EOR(_O())Q(0x51)EOR(_P()
)Q(0x4A)a=LSR(a)Q(0x46)LSRA(_E())Q(0x56)LSRA(_F()
)Q(0x4E)LSRA(_H())Q(0x5E)LSRA(_Z())Q(0x09)_S(_V()
)Q(0x05)_S(_E())Q(0x15)_S(_F())Q(13)_S(_H())Q(29)
_S(_Z())Q(0x19)_S(_Y())Q(0x01)_S(_O())Q(17)_S(_P(
))Q(0x2A)a=ROL(a)Q(0x26)ROLA(_E())Q(0x36)ROLA(_F(
))Q(0x2E)ROLA(_H())Q(0x3E)ROLA(_Z())Q(0x6A)a=_M(a
)Q(0x66)_MA(_E())Q(0x76)_MA(_F())Q(0x6E)_MA(_H())
Q(0x7E)_MA(_Z())Q(0x90)J(REL(),!n)Q(0xB0)J(REL(),
n)Q(0xD0)J(REL(),!b)Q(0xF0)J(REL(),b)Q(0x10)J(REL
(),!H)Q(0x30)J(REL(),H)Q(0x50)J(REL(),!G)Q(0x70)J
(REL(),G)Q(0x4C)U(_H())Q(108)U(_B(_H()))Q(32)JSR(
_H())Q(0x40)_Q()Q(0x60)RTS()Q(0x38)n=1 Q(0x18)n=0
Q(0xF8)E=1 Q(0xD8)E=0 Q(0x78)C=1 Q(0x58)C=0 Q(184
)G=0 Q(0xC9)_R(_V(),a)Q(0xC5)_R(_E(),a)Q(0xD5)_R(
_F(),a)Q(0xCD)_R(_H(),a)Q(0xDD)_R(_Z(),a)Q(217)_R
(_Y(),a)Q(0xC1)_R(_O(),a)Q(0xD1)_R(_P(),a)Q(0xE0)
_R(_V(),x)Q(0xE4)_R(_E(),x)Q(0xEC)_R(_H(),x)Q(192
)_R(_V(),y)Q(0xC4)_R(_E(),y)Q(0xCC)_R(_H(),y)Q(72
)_K(a)Q(0x68)a=_C();_I(a)Q(0x08)F=1;_K(GFL())Q(40
)__(_C())Q(0x00)F=1;p+=1;___(0xF800)Q(0xEA)break;
}}

D(void,ldm,const char*,w){uint32_t s;FILE*f=fopen(A,"rb");fseek(f,0,SEEK_END);
s=ftell(f);rewind(f);fread(&m[B],sizeof(q),s,f);fclose(f);}Z(void,t1){memset(m
,0,0x10000);ldm("test1.bin",0x4000); init();rs();for(;;){step();if(p==0x45C0){
printf("%s\n",m[0x0210]==0xFF?"passed":"failed");return;}}}int main(){m=malloc
(0x10000);t1();}
