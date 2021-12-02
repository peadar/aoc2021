%top{
#include "parser.h"
}

DIGIT [0-9]
NUMBER {DIGIT}+
WHITESPACE [ \n]

%%
forward { return FORWARD; }
down    { return DOWN; }
up      { return UP; }
{DIGIT}+ { yylval.number = strtoul(yytext, 0, 0); return NUMBER; }
{WHITESPACE}+
