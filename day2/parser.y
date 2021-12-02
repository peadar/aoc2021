%{
#include <iostream>

int horiz, depth, aim;
int yyerror(const char *p) {
   std::clog << p << std::endl;
   exit(1);
}

int yylex();
int yyparse();

%}

%token UP DOWN FORWARD NUMBER EOL
%union { int number; }
%type<number> NUMBER;

%%
stmts:
     | stmt EOL stmts
     ;

stmt : DOWN NUMBER { aim += $2; }
     | UP NUMBER { aim -= $2; }
     | FORWARD NUMBER { horiz += $2;  depth += aim * $2; }
     ;
%%

extern "C" { int yywrap() { return true; } }

int main() {
   yyparse();
   std::cout
            << "depth: " << depth
            << ", horizontal: " << horiz
            << ", product:" << depth * horiz
            << std::endl;
   return 0;
}
