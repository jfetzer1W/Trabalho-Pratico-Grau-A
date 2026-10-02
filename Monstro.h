#ifndef MONSTRO_H
#define MONSTRO_H

#include <string>
#include "Item.h"
using namespace std;

// Um inimigo. E "configurado" pela classe Cena, que le seus dados do arquivo .txt.
class Monstro {
private:
    string nome;
    int habilidade;
    int sorte;
    int energia;

    int tesouro;      // -1 = nao possui
    int provisao;     // -1 = nao possui
    bool possuiItem;
    Item item;

    int cenaSucesso;
    int cenaDerrota;

public:
    Monstro();
    void configurar(string nome, int habilidade, int sorte, int energia,
                     int tesouro, int provisao, bool possuiItem, Item item,
                     int cenaSucesso, int cenaDerrota);

    string getNome() const;
    int getHabilidade() const;
    int getEnergia() const;
    void receberDano(int dano);
    bool estaVivo() const;

    int getTesouro() const;
    int getProvisao() const;
    bool temItem() const;
    Item getItem() const;

    int getCenaSucesso() const;
    int getCenaDerrota() const;
};

#endif
