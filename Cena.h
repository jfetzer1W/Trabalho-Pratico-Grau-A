#ifndef CENA_H
#define CENA_H

#include <string>
#include "Item.h"
#include "Monstro.h"
using namespace std;

const int MAX_OPCOES = 8;
const int MAX_ITENS_OFERECIDOS = 3;

struct Opcao {
    int destino;
    string texto;
};

enum TipoCena { NARRATIVA, CENA_MONSTRO };

class Cena {
private:
    TipoCena tipo;
    string texto;

    Item itensOferecidos[MAX_ITENS_OFERECIDOS];
    int qtdItensOferecidos;

    Opcao opcoes[MAX_OPCOES];
    int qtdOpcoes;

    Monstro monstro;

public:
    Cena();
    bool carregarDeArquivo(int numeroCena, const string& caminhoPasta);

    TipoCena getTipo() const;
    string getTexto() const;

    int getQtdItensOferecidos() const;
    const Item& getItemOferecido(int indice) const;

    int getQtdOpcoes() const;
    const Opcao& getOpcao(int indice) const;

    Monstro& getMonstro();
};

#endif
