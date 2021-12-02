%{
#include "parser.h"
%}
DIGIT [0-9]
EOL \n
SPACE [ ]
%%
forward         { return FORWARD; }
down            { return DOWN; }
up              { return UP; }
{DIGIT}+        { yylval.number = strtoul(yytext, 0, 0); return NUMBER; }
{EOL}           { return EOL; }
{SPACE}         {}
