#include "Personagem.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Personagem::Personagem()
    : nome(""), habilidade(0), energia(0), energiaMaxima(0), sorte(0), arcano(false) {}

void Personagem::configurar(string nome, int habilidade, int energiaMaxima, int sorte, bool arcano) {
    this->nome = nome;
    this->habilidade = habilidade;
    this->energiaMaxima = energiaMaxima;
    this->energia = energiaMaxima;
    this->sorte = sorte;
    this->arcano = arcano;
}

string Personagem::getNome() const { return nome; }
int Personagem::getHabilidade() const { return habilidade; }
int Personagem::getEnergia() const { return energia; }
int Personagem::getEnergiaMaxima() const { return energiaMaxima; }
int Personagem::getSorte() const { return sorte; }
bool Personagem::isArcano() const { return arcano; }

void Personagem::setEnergiaAtual(int e) { energia = e; }

void Personagem::receberDano(int dano) {
    energia -= dano;
    if (energia < 0) energia = 0;
}

void Personagem::curar(int qtd) {
    energia += qtd;
    if (energia > energiaMaxima) energia = energiaMaxima;
}

bool Personagem::estaVivo() const { return energia > 0; }

bool Personagem::testarSorte() {
    int sorteado = (rand() % 10) + 1;
    bool sucesso = sorteado <= sorte;
    if (sorte > 0) sorte--;
    return sucesso;
}

Inventario& Personagem::getInventario() { return inventario; }

void Personagem::imprimir() const {
    cout << "Nome: " << nome << (arcano ? " (Arcano)" : "") << endl;
    cout << "Habilidade: " << habilidade << endl;
    cout << "Energia: " << energia << "/" << energiaMaxima << endl;
    cout << "Sorte: " << sorte << endl;
}
