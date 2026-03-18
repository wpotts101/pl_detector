%{
#include <stdio.h>

#define T_TYPE        1
#define T_CONTROL     2
#define T_JUMP        3
#define T_MODIFIER    4
#define T_IDENTIFIER  5
#define T_NUMBER      6
#define T_STRING      7
#define T_CHAR        8
#define T_OPERATOR    9
#define T_REL_OP      10
#define T_ASSIGN      11
#define T_PUNCT       12
#define T_LPAREN      13
#define T_RPAREN      14
#define T_LBRACE      15
#define T_RBRACE      16
#define T_LBRACKET    17
#define T_RBRACKET    18

void emit(int tok) 
{
    printf("%03d ", tok);
}
%}

%option noyywrap
%x COMMENT

LETTER [A-Za-z_]
DIGIT [0-9]
ID {LETTER}({LETTER}|{DIGIT})*
INT {DIGIT}+
FLOAT {DIGIT}+"."{DIGIT}+([eE][+-]?{DIGIT}+)?
NUMBER {FLOAT}|{INT}
STRING \"([^\\\n]|(\\.))*\"
CHARLIT \'([^\\\n]|(\\.))\'
WS [ \t\r\n]+

%%
{WS} ;
"//".* ;

"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>\n ;
<COMMENT>. ;

"int"|"float"|"double"|"char"|"void"|"long"|"short" { emit(T_TYPE); }

"if"|"else"|"for"|"while"|"do"|"switch"|"case"|"default" { emit(T_CONTROL); }

"return"|"break"|"continue" { emit(T_JUMP); }

"unsigned"|"signed"|"const"|"static"|"typedef"|"struct" { emit(T_MODIFIER); }

{STRING} { emit(T_STRING); }
{CHARLIT} { emit(T_CHAR); }
{NUMBER} { emit(T_NUMBER); }
{ID} { emit(T_IDENTIFIER); }

"=="|"!="|"<="|">=" { emit(T_REL_OP); }
"<"|">" { emit(T_REL_OP); }
"=" { emit(T_ASSIGN); }

"++"|"--"|"+"|"-"|"*"|"/"|"%"|"&&"|"||"|"!" { emit(T_OPERATOR); }

";"|","|":" { emit(T_PUNCT); }
"(" { emit(T_LPAREN); }
")" { emit(T_RPAREN); }
"{" { emit(T_LBRACE); }
"}" { emit(T_RBRACE); }
"[" { emit(T_LBRACKET); }
"]" { emit(T_RBRACKET); }

. ;
%%
int main(void) {
    yylex();
    return 0;
}