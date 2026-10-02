#include "Item.h"
#include <iostream>

Item::Item() : nome(""), tipo('c'), combate(false), FA(0), dano(0) {}

Item::Item(string nome, char tipo, bool combate, int FA, int dano)
    : nome(nome), tipo(tipo), combate(combate), FA(FA), dano(dano) {}

string Item::getNome() const { return nome; }
char Item::getTipo() const { return tipo; }
bool Item::podeUsarEmCombate() const { return combate; }
int Item::getFA() const { return FA; }
int Item::getDano() const { return dano; }

void Item::imprimir() const {
    string tipoTexto = (tipo == 'r') ? "Armadura" : (tipo == 'w') ? "Arma" : "Item comum";
    cout << "  - " << nome << " [" << tipoTexto << "]";
    if (combate) {
        cout << " (FA: " << (FA >= 0 ? "+" : "") << FA
             << ", Dano: " << (dano >= 0 ? "+" : "") << dano << ")";
    }
    cout << endl;
}

string trim(const string& s) {
    size_t inicio = s.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fim = s.find_last_not_of(" \t\r\n");
    return s.substr(inicio, fim - inicio + 1);
}

Item Item::fromString(const string& linha) {
    size_t p1 = linha.find(';');
    size_t p2 = linha.find(';', p1 + 1);
    size_t p3 = linha.find(';', p2 + 1);
    size_t p4 = linha.find(';', p3 + 1);

    string nome = trim(linha.substr(0, p1));
    char tipo = trim(linha.substr(p1 + 1, p2 - p1 - 1))[0];
    bool combate = trim(linha.substr(p2 + 1, p3 - p2 - 1)) == "1";
    int fa = stoi(linha.substr(p3 + 1, p4 - p3 - 1));
    int dano = stoi(linha.substr(p4 + 1));

    return Item(nome, tipo, combate, fa, dano);
}

string Item::toString() const {
    return nome + ";" + tipo + ";" + (combate ? "1" : "0") + ";"
         + to_string(FA) + ";" + to_string(dano);
}
