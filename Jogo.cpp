#include "Jogo.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

static int lerInteiro() {
    int valor;
    while (!(cin >> valor)) {
        if (cin.eof()) { cout << "\nEntrada encerrada. Fechando o jogo." << endl; exit(0); }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Digite um numero: ";
    }
    return valor;
}

Jogo::Jogo(string pastaCenas, string arquivoSave)
    : cenaAtual(1), qtdCenasVisitadas(0), pastaCenas(pastaCenas),
      arquivoSave(arquivoSave), jogoAtivo(false) {}

// =========================== LOOP PRINCIPAL ===========================
void Jogo::executar() {
    srand((unsigned) time(nullptr));
    telaAbertura();

    while (jogoAtivo) {
        Cena cena;
        if (!cena.carregarDeArquivo(cenaAtual, pastaCenas)) {
            cout << "\nErro: cena " << cenaAtual << " nao encontrada. Encerrando." << endl;
            break;
        }

        bool jaVisitada = false;
        for (int i = 0; i < qtdCenasVisitadas; i++)
            if (cenasVisitadas[i] == cenaAtual) jaVisitada = true;
        if (!jaVisitada && qtdCenasVisitadas < MAX_CENAS_VISITADAS)
            cenasVisitadas[qtdCenasVisitadas++] = cenaAtual;

        // So entrega os itens na PRIMEIRA vez que passa pela cena
        if (!jaVisitada) {
            for (int i = 0; i < cena.getQtdItensOferecidos(); i++) {
                const Item& item = cena.getItemOferecido(i);
                cout << "\n>> Voce encontrou um item: " << item.getNome() << "!" << endl;
                personagem.getInventario().adicionarItem(item);
                if (item.getTipo() == 'w') {   // arma nova: equipa automaticamente
                    personagem.getInventario().equiparArma(item.getNome());
                    cout << ">> Voce equipou " << item.getNome() << "!" << endl;
                }
            }
        }

        salvarJogo();   // salva automaticamente a cada nova cena (regra do enunciado)

        if (cena.getTipo() == NARRATIVA) {
            if (cena.getQtdOpcoes() == 0) {
                cout << "\n================================================" << endl;
                cout << cena.getTexto() << endl;
                cout << "================================================" << endl;
                jogoAtivo = false;
            } else {
                telaPadrao(cena);
            }
        } else {
            telaBatalha(cena);
        }

        if (!personagem.estaVivo()) {
            cout << "\n========================================" << endl;
            cout << "  Voce foi derrotado... Fim de jogo." << endl;
            cout << "========================================" << endl;
            jogoAtivo = false;
        }
    }
}

// =========================== TELA DE ABERTURA ===========================
void Jogo::telaAbertura() {
    int opcao = -1;
    while (opcao != 4 && !jogoAtivo) {
        cout << "\n==============================================" << endl;
        cout << "   AS CRONICAS DE ELDORVALE - Interactive eBook" << endl;
        cout << "==============================================" << endl;
        cout << "1 - Novo Jogo" << endl;
        cout << "2 - Carregar Jogo" << endl;
        cout << "3 - Exibir Creditos" << endl;
        cout << "4 - Encerrar" << endl;
        cout << "Escolha: ";
        opcao = lerInteiro();

        switch (opcao) {
            case 1: novoJogo(); break;
            case 2: carregarJogo(); break;
            case 3: exibirCreditos(); break;
            case 4: cout << "Ate a proxima aventura!" << endl; break;
            default: cout << "Opcao invalida." << endl;
        }
    }
}

void Jogo::exibirCreditos() {
    cout << "\n----- CREDITOS -----" << endl;
    cout << "Programador: Vitor Zandona" << endl;
    cout << "Trabalho Pratico Grau A - Algoritmos e Programacao: Orientacao a Objetos" << endl;
    cout << "UNISINOS - 2026/2" << endl;
    cout << "---------------------" << endl;
}

// =========================== CRIACAO DE PERSONAGEM ===========================
void Jogo::criarPersonagem() {
    cout << "\n===== CRIACAO DE PERSONAGEM =====" << endl;
    string nome;
    cout << "Nome do seu personagem: ";
    cin.ignore();
    getline(cin, nome);

    cout << "\nVoce tem 12 pontos para distribuir entre Habilidade, Sorte e Energia." << endl;
    cout << "Habilidade: cada ponto vale +1 (base 6, maximo 12)" << endl;
    cout << "Sorte:      cada ponto vale +1 (base 6, maximo 12)" << endl;
    cout << "Energia:    cada ponto vale +2 (base 12, maximo 24)" << endl;

    int pontosRestantes = 12;
    cout << "\nPontos para Habilidade (0 a 6): ";
    int pH = lerInteiro();
    while (pH < 0 || pH > 6) { cout << "Valor invalido (0 a 6): "; pH = lerInteiro(); }
    pontosRestantes -= pH;

    cout << "Pontos restantes: " << pontosRestantes << ". Pontos para Sorte (0 a " << min(6, pontosRestantes) << "): ";
    int pS = lerInteiro();
    // Energia aceita no maximo 6 pontos, entao a Sorte precisa usar o que sobrar acima disso
    while (pS < 0 || pS > 6 || pS > pontosRestantes || pontosRestantes - pS > 6) {
        cout << "Valor invalido (sobrariam mais de 6 pontos para Energia): ";
        pS = lerInteiro();
    }
    pontosRestantes -= pS;

    int pE = pontosRestantes;
    cout << "Pontos restantes (" << pontosRestantes << ") atribuidos a Energia." << endl;

    int habilidade = 6 + pH;
    int sorte = 6 + pS;
    int energia = 12 + (pE * 2);

    cout << "\nSeu personagem usa magia diretamente (e Arcano)? (1-Sim / 0-Nao): ";
    bool arcano = (lerInteiro() == 1);

    personagem.configurar(nome, habilidade, energia, sorte, arcano);
    personagem.getInventario().adicionarItem(Item("Adaga", 'w', true, 0, 0));
    personagem.getInventario().equiparArma("Adaga");
    personagem.getInventario().adicionarProvisoes(5);
    if (arcano) personagem.getInventario().adicionarMagia("Bola de Fogo");

    cout << "\nPersonagem criado com sucesso!" << endl;
    telaInventario();
}

// =========================== TELA DE INVENTARIO ===========================
void Jogo::telaInventario() {
    cout << "\n===== FICHA DO PERSONAGEM =====" << endl;
    personagem.imprimir();
    personagem.getInventario().imprimir();
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// =========================== NOVO JOGO / CARREGAR ===========================
void Jogo::novoJogo() {
    criarPersonagem();
    cenaAtual = 1;
    qtdCenasVisitadas = 0;
    jogoAtivo = true;
}

void Jogo::carregarJogo() {
    if (carregarDoArquivo()) {
        cout << "\nJogo carregado! Retomando na cena " << cenaAtual << "." << endl;
        jogoAtivo = true;
    } else {
        cout << "\nNao foi encontrado nenhum jogo salvo." << endl;
    }
}

// =========================== TELA PADRAO ===========================
void Jogo::telaPadrao(Cena& cena) {
    cout << "\n------------------------------------------------" << endl;
    cout << cena.getTexto() << endl;
    cout << "------------------------------------------------" << endl;

    int qtdOpcoes = cena.getQtdOpcoes();
    cout << "\nO que voce deseja fazer?" << endl;
    for (int i = 0; i < qtdOpcoes; i++)
        cout << (i + 1) << " - " << cena.getOpcao(i).texto << endl;
    cout << (qtdOpcoes + 1) << " - Ver Inventario" << endl;

    int escolha = -1;
    while (true) {
        cout << "Escolha: ";
        escolha = lerInteiro();
        if (escolha == qtdOpcoes + 1) {
            telaInventario();
            continue;
        }
        if (escolha >= 1 && escolha <= qtdOpcoes) break;
        cout << "Opcao invalida." << endl;
    }

    cenaAtual = cena.getOpcao(escolha - 1).destino;
}

// =========================== TELA DE BATALHA ===========================
void Jogo::telaBatalha(Cena& cena) {
    Monstro& monstro = cena.getMonstro();
    cout << "\n################################################" << endl;
    cout << cena.getTexto() << endl;
    cout << "Um " << monstro.getNome() << " aparece!" << endl;
    cout << "################################################" << endl;

    while (personagem.estaVivo() && monstro.estaVivo()) {
        cout << "\n--- Seu turno ---" << endl;
        cout << "Sua energia: " << personagem.getEnergia() << "/" << personagem.getEnergiaMaxima()
             << " | Energia do " << monstro.getNome() << ": " << monstro.getEnergia() << endl;

        bool podeUsarMagia = personagem.isArcano() || personagem.getInventario().temMagia();
        cout << "1 - Atacar" << endl;
        if (podeUsarMagia) cout << "2 - Usar Magia (+3 na Forca de Ataque)" << endl;
        cout << "3 - Testar Sorte" << endl;
        cout << "4 - Fugir" << endl;
        cout << "Escolha: ";
        int acao = lerInteiro();
        while (acao < 1 || acao > 4 || (acao == 2 && !podeUsarMagia)) {
            cout << "Opcao invalida. Escolha: ";
            acao = lerInteiro();
        }

        if (acao == 4) {
            cout << "\nVoce foge, mas leva um golpe (2 de dano)." << endl;
            personagem.receberDano(2);
            cenaAtual = monstro.getCenaDerrota();
            return;
        }

        bool testouSorte = false, sorteBoa = false;
        if (acao == 3) {
            testouSorte = true;
            sorteBoa = personagem.testarSorte();
            cout << (sorteBoa ? "Sorte grande! " : "Que azar! ") << "Sorte restante: " << personagem.getSorte() << endl;
        }

        int bonusFA = 0, bonusDano = 0;
        if (personagem.getInventario().getArmaEquipada() != nullptr) {
            bonusFA += personagem.getInventario().getArmaEquipada()->getFA();
            bonusDano += personagem.getInventario().getArmaEquipada()->getDano();
        }
        if (acao == 2) {
            cout << ">> Voce conjura uma magia!" << endl;
            bonusFA += 3;
        }

        int faPersonagem = (rand() % 10) + 1 + personagem.getHabilidade() + bonusFA;
        int faMonstro = (rand() % 10) + 1 + monstro.getHabilidade();
        cout << "\nForca de Ataque -> Voce: " << faPersonagem << " | " << monstro.getNome() << ": " << faMonstro << endl;

        if (faPersonagem > faMonstro) {
            int dano = 2 + bonusDano;
            if (testouSorte) dano += sorteBoa ? 2 : -1;
            if (dano < 0) dano = 0;
            monstro.receberDano(dano);
            cout << "Voce acertou! " << monstro.getNome() << " perde " << dano << " pontos de energia." << endl;
        } else if (faMonstro > faPersonagem) {
            int reducaoArmadura = 0;
            if (personagem.getInventario().getArmaduraEquipada() != nullptr)
                reducaoArmadura = personagem.getInventario().getArmaduraEquipada()->getDano();
            int dano = 2 - reducaoArmadura;
            if (testouSorte) dano += sorteBoa ? -2 : 1;
            if (dano < 0) dano = 0;
            personagem.receberDano(dano);
            cout << "Voce foi atingido! Voce perde " << dano << " pontos de energia." << endl;
        } else {
            cout << "Empate! Ninguem se machucou neste round." << endl;
        }
    }

    if (!personagem.estaVivo()) return;

    cout << "\nVoce derrotou " << monstro.getNome() << "!" << endl;
    if (monstro.getTesouro() > 0) {
        cout << "Voce encontrou " << monstro.getTesouro() << " moedas de ouro!" << endl;
        personagem.getInventario().adicionarTesouro(monstro.getTesouro());
    }
    if (monstro.getProvisao() > 0) {
        cout << "Voce encontrou " << monstro.getProvisao() << " provisao(oes)!" << endl;
        personagem.getInventario().adicionarProvisoes(monstro.getProvisao());
    }
    if (monstro.temItem()) {
        cout << "Voce encontrou um item: " << monstro.getItem().getNome() << "!" << endl;
        personagem.getInventario().adicionarItem(monstro.getItem());
    }
    cenaAtual = monstro.getCenaSucesso();
}

// =========================== SALVAR / CARREGAR (ofstream / ifstream) ===========================
void Jogo::salvarJogo() {
    ofstream arq(arquivoSave);
    if (!arq.is_open()) return;

    Inventario& inv = personagem.getInventario();

    arq << "NOME:" << personagem.getNome() << endl;
    arq << "HABILIDADE:" << personagem.getHabilidade() << endl;
    arq << "ENERGIA:" << personagem.getEnergia() << endl;
    arq << "ENERGIAMAX:" << personagem.getEnergiaMaxima() << endl;
    arq << "SORTE:" << personagem.getSorte() << endl;
    arq << "ARCANO:" << (personagem.isArcano() ? 1 : 0) << endl;
    arq << "TESOURO:" << inv.getTesouro() << endl;
    arq << "PROVISOES:" << inv.getProvisoes() << endl;
    arq << "CENAATUAL:" << cenaAtual << endl;

    arq << "VISITADAS:";
    for (int i = 0; i < qtdCenasVisitadas; i++)
        arq << (i > 0 ? ";" : "") << cenasVisitadas[i];
    arq << endl;

    arq << "MAGIAS:";
    for (int i = 0; i < inv.getQtdMagias(); i++)
        arq << (i > 0 ? ";" : "") << inv.getMagia(i);
    arq << endl;

    arq << "ITENS:" << inv.getQuantidadeItens() << endl;
    for (int i = 0; i < inv.getQuantidadeItens(); i++) {
        arq << inv.getItem(i).toString() << endl;
    }

    arq << "ARMAEQUIPADA:" << (inv.getArmaEquipada() ? inv.getArmaEquipada()->getNome() : "") << endl;
    arq << "ARMADURAEQUIPADA:" << (inv.getArmaduraEquipada() ? inv.getArmaduraEquipada()->getNome() : "") << endl;

    arq.close();
}

bool Jogo::carregarDoArquivo() {
    ifstream arq(arquivoSave);
    if (!arq.is_open()) return false;

    string nome, armaNome, armaduraNome;
    int habilidade = 0, energia = 0, energiaMax = 0, sorte = 0;
    bool arcano = false;
    int tesouro = 0, provisoes = 0, qtdItens = 0;

    string linha;
    while (getline(arq, linha)) {
        size_t dp = linha.find(':');
        if (dp == string::npos) continue;
        string chave = linha.substr(0, dp);
        string valor = linha.substr(dp + 1);

        if (chave == "NOME") nome = valor;
        else if (chave == "HABILIDADE") habilidade = stoi(valor);
        else if (chave == "ENERGIA") energia = stoi(valor);
        else if (chave == "ENERGIAMAX") energiaMax = stoi(valor);
        else if (chave == "SORTE") sorte = stoi(valor);
        else if (chave == "ARCANO") arcano = (valor == "1");
        else if (chave == "TESOURO") tesouro = stoi(valor);
        else if (chave == "PROVISOES") provisoes = stoi(valor);
        else if (chave == "CENAATUAL") cenaAtual = stoi(valor);
        else if (chave == "VISITADAS") {
            qtdCenasVisitadas = 0;
            size_t pos = 0;
            while (pos < valor.size() && qtdCenasVisitadas < MAX_CENAS_VISITADAS) {
                size_t prox = valor.find(';', pos);
                string numStr = (prox == string::npos) ? valor.substr(pos) : valor.substr(pos, prox - pos);
                if (!numStr.empty()) cenasVisitadas[qtdCenasVisitadas++] = stoi(numStr);
                if (prox == string::npos) break;
                pos = prox + 1;
            }
        }
        else if (chave == "MAGIAS") {
            size_t pos = 0;
            while (pos < valor.size()) {
                size_t prox = valor.find(';', pos);
                string nomeMagia = (prox == string::npos) ? valor.substr(pos) : valor.substr(pos, prox - pos);
                if (!nomeMagia.empty()) personagem.getInventario().adicionarMagia(nomeMagia);
                if (prox == string::npos) break;
                pos = prox + 1;
            }
        }
        else if (chave == "ITENS") {
            qtdItens = stoi(valor);
            for (int i = 0; i < qtdItens; i++) {
                string linhaItem;
                getline(arq, linhaItem);
                personagem.getInventario().adicionarItem(Item::fromString(linhaItem));
            }
        }
        else if (chave == "ARMAEQUIPADA") armaNome = valor;
        else if (chave == "ARMADURAEQUIPADA") armaduraNome = valor;
    }

    // Depois de ler o arquivo inteiro, monta o personagem com os valores lidos
    personagem.configurar(nome, habilidade, energiaMax, sorte, arcano);
    personagem.setEnergiaAtual(energia);
    personagem.getInventario().adicionarTesouro(tesouro);
    personagem.getInventario().adicionarProvisoes(provisoes);

    if (!armaNome.empty()) personagem.getInventario().equiparArma(armaNome);
    if (!armaduraNome.empty()) personagem.getInventario().equiparArmadura(armaduraNome);

    arq.close();
    return true;
}
