#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

// Um item do jogo. Segue o formato do enunciado: nome;tipo;combate;FA;dano
class Item {
private:
    string nome;
    char tipo;      // 'c' = comum, 'r' = armadura, 'w' = arma
    bool combate;   // pode ser usado em combate?
    int FA;         // bonus/penalidade na Forca de Ataque
    int dano;       // bonus/penalidade no dano

public:
    Item();
    Item(string nome, char tipo, bool combate, int FA, int dano);

    string getNome() const;
    char getTipo() const;
    bool podeUsarEmCombate() const;
    int getFA() const;
    int getDano() const;

    void imprimir() const;
};

#endif
