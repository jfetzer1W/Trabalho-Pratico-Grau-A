#include "Jogo.h"
#include <iostream>

using namespace std;

Jogo::Jogo() {
    opcao = 0;
}

void Jogo::Cabecalho(){

    cout << "\n==================================\n";
    cout << "          FETZDONA GAME\n";
    cout << "      Projeto Pratico Grau A\n";
    cout << "==================================\n";
}

void Jogo::mostrarMenu(){

    cout << "\n========= MENU DO JOGO =========\n\n";
    cout << "[1] Novo Jogo\n";
    cout << "[2] Carregar Jogo\n";
    cout << "[3] Creditos\n ";
    cout << "[4] Fechar Jogo ";
}

void Jogo::executar(){
    Cabecalho();
    mostrarMenu();
    cin >> opcao;
}


