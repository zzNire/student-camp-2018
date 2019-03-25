
bison -d parser.y
flex lexer.l
mv parser.tab.c parser.cpp
mv lex.yy.c lexer.cpp
g++ lexer.cpp parser.cpp table.cpp node.cpp -I.
./a.out

