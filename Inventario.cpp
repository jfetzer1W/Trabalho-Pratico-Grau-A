#include "Inventario.h"
#include <iostream>

Inventario::Inventario() {
    capacidade = 4;
    quantidade = 0;
    itens = new Item[capacidade];     // aloca o array dinamicamente
    tesouro = 0;
    provisoes = 0;
    qtdMagias = 0;
    indiceArmaEquipada = -1;
    indiceArmaduraEquipada = -1;
}

// Destrutor: devolve a memoria do array ao sistema. Obrigatorio sempre que
// o construtor usa "new[]" (senao vazaria memoria a cada Inventario destruido).
Inventario::~Inventario() {
    delete[] itens;
}

// Construtor de copia: necessario porque a classe tem um PONTEIRO.
// Sem isso, copiar um Inventario copiaria so o ENDERECO do array, e dois
// inventarios diferentes ficariam apontando para a MESMA memoria -- um bug grave.
Inventario::Inventario(const Inventario& outro) {
    capacidade = outro.capacidade;
    quantidade = outro.quantidade;
    itens = new Item[capacidade];           // array NOVO, so para este objeto
    for (int i = 0; i < quantidade; i++)
        itens[i] = outro.itens[i];

    tesouro = outro.tesouro;
    provisoes = outro.provisoes;
    qtdMagias = outro.qtdMagias;
    for (int i = 0; i < qtdMagias; i++)
        magias[i] = outro.magias[i];

    indiceArmaEquipada = outro.indiceArmaEquipada;
    indiceArmaduraEquipada = outro.indiceArmaduraEquipada;
}

Inventario& Inventario::operator=(const Inventario& outro) {
    if (this == &outro) return *this;   // protege contra "obj = obj;"

    delete[] itens;                      // libera o array antigo
    capacidade = outro.capacidade;
    quantidade = outro.quantidade;
    itens = new Item[capacidade];
    for (int i = 0; i < quantidade; i++)
        itens[i] = outro.itens[i];

    tesouro = outro.tesouro;
    provisoes = outro.provisoes;
    qtdMagias = outro.qtdMagias;
    for (int i = 0; i < qtdMagias; i++)
        magias[i] = outro.magias[i];

    indiceArmaEquipada = outro.indiceArmaEquipada;
    indiceArmaduraEquipada = outro.indiceArmaduraEquipada;
    return *this;
}

// Dobra a capacidade do array quando ele enche. Crescer "dobrando" (em vez de
// 1 em 1) e o que torna isso EFICIENTE: a maioria das insercoes nao precisa
// realocar nada (crescimento amortizado).
void Inventario::garantirCapacidade() {
    if (quantidade < capacidade) return;

    int novaCapacidade = capacidade * 2;
    Item* novoArray = new Item[novaCapacidade];
    for (int i = 0; i < quantidade; i++)
        novoArray[i] = itens[i];

    delete[] itens;
    itens = novoArray;
    capacidade = novaCapacidade;
}

void Inventario::adicionarItem(const Item& item) {
    garantirCapacidade();
    itens[quantidade] = item;
    quantidade++;
}

bool Inventario::temItem(const string& nome) const {
    for (int i = 0; i < quantidade; i++)
        if (itens[i].getNome() == nome) return true;
    return false;
}

void Inventario::equiparArma(const string& nome) {
    for (int i = 0; i < quantidade; i++) {
        if (itens[i].getNome() == nome && itens[i].getTipo() == 'w') {
            indiceArmaEquipada = i;
            return;
        }
    }
}
void Inventario::equiparArmadura(const string& nome) {
    for (int i = 0; i < quantidade; i++) {
        if (itens[i].getNome() == nome && itens[i].getTipo() == 'r') {
            indiceArmaduraEquipada = i;
            return;
        }
    }
}
const Item* Inventario::getArmaEquipada() const {
    if (indiceArmaEquipada == -1) return nullptr;
    return &itens[indiceArmaEquipada];
}
const Item* Inventario::getArmaduraEquipada() const {
    if (indiceArmaduraEquipada == -1) return nullptr;
    return &itens[indiceArmaduraEquipada];
}

void Inventario::adicionarTesouro(int valor) { tesouro += valor; }
int Inventario::getTesouro() const { return tesouro; }

void Inventario::adicionarProvisoes(int qtd) { provisoes += qtd; }
bool Inventario::usarProvisao() {
    if (provisoes <= 0) return false;
    provisoes--;
    return true;
}
int Inventario::getProvisoes() const { return provisoes; }

void Inventario::adicionarMagia(const string& nome) {
    if (qtdMagias < MAX_MAGIAS) {
        magias[qtdMagias] = nome;
        qtdMagias++;
    }
}
bool Inventario::temMagia() const { return qtdMagias > 0; }
int Inventario::getQtdMagias() const { return qtdMagias; }
string Inventario::getMagia(int indice) const { return magias[indice]; }

int Inventario::getQuantidadeItens() const { return quantidade; }
const Item& Inventario::getItem(int indice) const { return itens[indice]; }

void Inventario::imprimir() const {
    cout << "INVENTARIO" << endl;
    cout << "Tesouro: " << tesouro << " moedas de ouro" << endl;
    cout << "Provisoes: " << provisoes << endl;
    cout << "Itens:" << endl;
    if (quantidade == 0) cout << "  (nenhum item)" << endl;
    for (int i = 0; i < quantidade; i++) {
        itens[i].imprimir();
        if (i == indiceArmaEquipada) cout << "     (equipada como arma)" << endl;
        if (i == indiceArmaduraEquipada) cout << "     (equipada como armadura)" << endl;
    }
    cout << "Magias conhecidas:" << endl;
    if (qtdMagias == 0) cout << "  (nenhuma)" << endl;
    for (int i = 0; i < qtdMagias; i++)
        cout << "  - " << magias[i] << endl;
}
