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
