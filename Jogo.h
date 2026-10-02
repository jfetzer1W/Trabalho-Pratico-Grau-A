#ifndef JOGO_H
#define JOGO_H

#include "Personagem.h"
#include "Cena.h"
#include <string>
using namespace std;

const int MAX_CENAS_VISITADAS = 50;   // nosso jogo tem 11 cenas, 50 e uma folga confortavel

// Controla o fluxo geral: as 4 telas pedidas no enunciado.
class Jogo {
private:
    Personagem personagem;
    int cenaAtual;

    int cenasVisitadas[MAX_CENAS_VISITADAS];
    int qtdCenasVisitadas;

    string pastaCenas;
    string arquivoSave;
    bool jogoAtivo;

    // ---- as 4 telas do enunciado ----
    void telaAbertura();
    void telaInventario();
    void telaPadrao(Cena& cena);
    void telaBatalha(Cena& cena);

    void criarPersonagem();
    void novoJogo();
    void carregarJogo();
    void exibirCreditos();

    // ---- Salvar/Carregar (aula de Arquivos: ofstream/ifstream) ----
    void salvarJogo();
    bool carregarDoArquivo();

public:
    Jogo(string pastaCenas, string arquivoSave);
    void executar();
};

#endif
