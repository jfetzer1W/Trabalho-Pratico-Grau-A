# As Crônicas de Eldorvale — Interactive eBook

Trabalho Prático Grau A — Algoritmos e Programação: Orientação a Objetos (UNISINOS)

## Como compilar e jogar

```bash
make
./jogo
```

Ou sem `make`:

```bash
g++ -std=c++17 -Wall *.cpp -o jogo
./jogo
```

Não usa nenhuma biblioteca exclusiva de Windows, nem `vector` (apenas arrays
alocados dinamicamente com `new`/`delete`). O jogo salva automaticamente em
`save.txt` a cada nova cena; use "Carregar Jogo" no menu para retomar.

## Estrutura (flat — todos os arquivos na raiz)

```
Item.h / Item.cpp               -> um objeto do jogo (arma, armadura, item comum)
Inventario.h / Inventario.cpp   -> itens guardados num array dinamico (new[]/delete[])
Personagem.h / Personagem.cpp   -> atributos do heroi + tem um Inventario
Monstro.h / Monstro.cpp         -> um inimigo e para onde o jogo vai apos o combate
Cena.h / Cena.cpp               -> le e interpreta um arquivo N.txt da pasta cenas/
Jogo.h / Jogo.cpp               -> as 4 telas, o fluxo, e salvar/carregar
main.cpp                        -> ponto de entrada
cenas/                          -> 11 arquivos de texto com a historia (1.txt a 11.txt)
```

## Por que não usa `vector`

O requisito do enunciado pede "vetores alocados dinamicamente e de forma
eficiente". Em vez do `std::vector` (ainda não estudado), o array de itens do
`Inventario` é alocado manualmente com `new[]` e dobra de tamanho quando enche
— o mesmo princípio de crescimento amortizado que o `vector` usa por baixo
dos panos, só que escrito à mão com ponteiros. Veja o PDF de explicação para
o detalhe linha a linha.

## Mapa das 11 cenas

```
1 (inicio) -> 2 (esquerda) -> 4 (monstro: Goblin)
           -> 3 (direita)  -> 5 (forcar porta) -> 8
                            -> 6 (procurar)     -> 8

4 (Goblin): sucesso -> 8 | fuga -> 9
9 (beco sem saida)  -> 7 (monstro: Aranha) | 3 (recuar)
7 (Aranha): sucesso -> 8 | fuga -> 3

8 (sala do tesouro, pega a espada) -> 10 (monstro: Dragao Sombrio)
10 (Dragao): sucesso -> 11 (VITORIA) | fuga -> 9
```

## Formato dos arquivos de cena

Narrativa:
```
#<numero>
<texto>

I: nome;tipo;combate;FA;dano      (opcional)

#<destino>: <texto da opcao>
```

Monstro:
```
m
<texto>

N: <nome>
M: <S/N>
H: <habilidade>
S: <sorte>
E: <energia>
T: <tesouro>       (opcional)
P: <provisao>      (opcional)
I: <item>          (opcional)
<cenaSucesso>;<cenaDerrota>
```

## Documentação completa

Veja o PDF **Explicacao_Completa_Trabalho_Grau_A.pdf** para a explicação de
cada classe, linha por linha, e um roteiro sugerido de apresentação.
