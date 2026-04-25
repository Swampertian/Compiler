# Compiler

Projeto de analisador léxico, sintático e semântico para declarações simples.

#### Requisitos Minimos:
- `gcc`
- `flex`
- `bison`

#### Compilacao:
```bash
./run_parser.sh
```

#### Execucao:
```bash
./run_parser.sh "int a = 1 + 2;"
./run_parser.sh examples/input.txt
echo "float b = 1 - 2.5;" | ./run_parser.sh
```

Na execucao valida, o parser imprime:
- a confirmacao sintatica e semantica;
- a AST gerada;
- a tabela de simbolos.

#### **Autores**:

[Joao vitor](https://github.com/joaovitro99)

[Pedro Lucas](https://github.com/Swampertian)
