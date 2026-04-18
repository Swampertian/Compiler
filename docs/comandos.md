#### Gravar Dicionario
nano contador.l
flex contador.l

#### Compilar Dicionario Sintatico
gcc lex
gcc lex.yy.c -o contador

#### Roda Echo pelo executavel contador
##### Exemplo: Pode ser **QUALQUER** Codigo em C 
echo "if(a+b)" | ./contador

##### Parser

bison -d parser.y
gcc -o parser.y parser.tab.c lex.yy.c -lfl # Compila parser e executa usando o lex

##### Execucao do parser
./parser.y < input.txt