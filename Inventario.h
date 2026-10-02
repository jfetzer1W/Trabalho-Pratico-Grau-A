#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Item.h"
#include <string>
using namespace std;

const int MAX_MAGIAS = 10;   // um personagem nao vai conhecer mais que 10 magias

// Guarda tudo que o personagem carrega. Os itens ficam num array ALOCADO
// DINAMICAMENTE (com new[]), que dobra de tamanho quando enche -- exatamente
// o que a aula de Ponteiros ensinou, sem usar vector.
class Inventario {
private:
    Item* itens;          // ponteiro para o primeiro elemento do array
    int capacidade;        // quantos espacos o array tem no momento
    int quantidade;        // quantos espacos estao ocupados

    int tesouro;
    int provisoes;

    string magias[MAX_MAGIAS];   // lista pequena e fixa, nao precisa ser dinamica
    int qtdMagias;

    int indiceArmaEquipada;       // -1 = nenhuma equipada
    int indiceArmaduraEquipada;

    void garantirCapacidade();    // dobra o array quando ele enche

public:
    Inventario();
    ~Inventario();                                  // libera a memoria do array (delete[])
    Inventario(const Inventario& outro);             // construtor de copia (deep copy)
    Inventario& operator=(const Inventario& outro);  // operador de atribuicao (deep copy)

    void adicionarItem(const Item& item);
    bool temItem(const string& nome) const;

    void equiparArma(const string& nome);
    void equiparArmadura(const string& nome);
    const Item* getArmaEquipada() const;
    const Item* getArmaduraEquipada() const;

    void adicionarTesouro(int valor);
    int getTesouro() const;

    void adicionarProvisoes(int qtd);
    bool usarProvisao();
    int getProvisoes() const;

    void adicionarMagia(const string& nome);
    bool temMagia() const;
    int getQtdMagias() const;
    string getMagia(int indice) const;

    int getQuantidadeItens() const;
    const Item& getItem(int indice) const;

    void imprimir() const;
};

#endif
