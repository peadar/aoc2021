%{

#include <iostream>

int horiz, depth, aim;
int yyerror(const char *p) { throw p; }
int yylex();
int yyparse();

extern "C" { int yywrap() { return true; } }

int main() {
   yyparse();
   std::cout
            << "depth: " << depth
            << ", horizontal: " << horiz
            << ", product:" << depth * horiz
            << std::endl;
}

%}

%token UP DOWN FORWARD NUMBER
%union { int number; }
%type<number> NUMBER;
%%
stmts:
     | stmt stmts
     ;

stmt : DOWN NUMBER { aim += $2; }
     | UP NUMBER { aim -= $2; }
     | FORWARD NUMBER { horiz += $2;  depth += aim * $2; }
     ;
