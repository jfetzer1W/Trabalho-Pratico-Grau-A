#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include "Inventario.h"
using namespace std;

// O personagem do jogador. "Tem um" Inventario (composicao).
class Personagem {
private:
    string nome;
    int habilidade;
    int energia;
    int energiaMaxima;
    int sorte;
    bool arcano;
    Inventario inventario;

public:
    Personagem();

    void configurar(string nome, int habilidade, int energiaMaxima, int sorte, bool arcano);

    string getNome() const;
    int getHabilidade() const;
    int getEnergia() const;
    int getEnergiaMaxima() const;
    int getSorte() const;
    bool isArcano() const;

    void setEnergiaAtual(int e);
    void setSorteAtual(int s);

    void receberDano(int dano);
    void curar(int qtd);
    bool estaVivo() const;

    bool testarSorte();   // sorteia 1-10 contra a sorte; sempre decrementa a sorte

    Inventario& getInventario();

    void imprimir() const;
};

#endif
