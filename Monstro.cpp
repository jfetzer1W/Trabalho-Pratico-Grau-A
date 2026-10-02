#include "Monstro.h"

Monstro::Monstro()
    : nome(""), habilidade(0), sorte(0), energia(0),
      tesouro(-1), provisao(-1), possuiItem(false), cenaSucesso(-1), cenaDerrota(-1) {}

void Monstro::configurar(string nome, int habilidade, int sorte, int energia,
                          int tesouro, int provisao, bool possuiItem, Item item,
                          int cenaSucesso, int cenaDerrota) {
    this->nome = nome;
    this->habilidade = habilidade;
    this->sorte = sorte;
    this->energia = energia;
    this->tesouro = tesouro;
    this->provisao = provisao;
    this->possuiItem = possuiItem;
    this->item = item;
    this->cenaSucesso = cenaSucesso;
    this->cenaDerrota = cenaDerrota;
}

string Monstro::getNome() const { return nome; }
int Monstro::getHabilidade() const { return habilidade; }
int Monstro::getEnergia() const { return energia; }

void Monstro::receberDano(int dano) {
    energia -= dano;
    if (energia < 0) energia = 0;
}
bool Monstro::estaVivo() const { return energia > 0; }

int Monstro::getTesouro() const { return tesouro; }
int Monstro::getProvisao() const { return provisao; }
bool Monstro::temItem() const { return possuiItem; }
Item Monstro::getItem() const { return item; }

int Monstro::getCenaSucesso() const { return cenaSucesso; }
int Monstro::getCenaDerrota() const { return cenaDerrota; }
