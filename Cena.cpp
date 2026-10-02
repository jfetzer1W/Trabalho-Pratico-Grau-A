#include "Cena.h"
#include <fstream>
#include <iostream>
using namespace std;

static string trim(const string& s) {
    size_t inicio = s.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fim = s.find_last_not_of(" \t\r\n");
    return s.substr(inicio, fim - inicio + 1);
}

// Interpreta uma linha "nome;tipo;combate;FA;dano" e monta um Item.
// Feito "na mao" com find/substr (sem vector) porque o numero de campos e sempre 5, fixo.
static Item parseItem(const string& linha) {
    size_t p1 = linha.find(';');
    size_t p2 = linha.find(';', p1 + 1);
    size_t p3 = linha.find(';', p2 + 1);
    size_t p4 = linha.find(';', p3 + 1);

    string nome = trim(linha.substr(0, p1));
    char tipo = trim(linha.substr(p1 + 1, p2 - p1 - 1))[0];
    bool combate = trim(linha.substr(p2 + 1, p3 - p2 - 1)) == "1";
    int fa = stoi(trim(linha.substr(p3 + 1, p4 - p3 - 1)));
    int dano = stoi(trim(linha.substr(p4 + 1)));

    return Item(nome, tipo, combate, fa, dano);
}

Cena::Cena() : tipo(NARRATIVA), qtdItensOferecidos(0), qtdOpcoes(0) {}

bool Cena::carregarDeArquivo(int numeroCena, const string& caminhoPasta) {
    string caminho = caminhoPasta + "/" + to_string(numeroCena) + ".txt";
    ifstream arq(caminho);
    if (!arq.is_open()) {
        cout << "ERRO: nao foi possivel abrir a cena " << caminho << endl;
        return false;
    }

    // 1) Primeira linha: "m" = cena de monstro; qualquer outra coisa = narrativa
    string primeiraLinha;
    getline(arq, primeiraLinha);
    tipo = (trim(primeiraLinha) == "m") ? CENA_MONSTRO : NARRATIVA;

    // 2) Texto da cena: le ate achar uma linha em branco
    string linha;
    texto = "";
    while (getline(arq, linha)) {
        if (trim(linha).empty()) break;
        if (!texto.empty()) texto += " ";
        texto += trim(linha);
    }

    if (tipo == NARRATIVA) {
        // 3a) Le "I: ..." (item oferecido) e "#N: texto" (opcoes)
        while (getline(arq, linha)) {
            string l = trim(linha);
            if (l.empty()) continue;

            if (l.rfind("I:", 0) == 0) {
                if (qtdItensOferecidos < MAX_ITENS_OFERECIDOS) {
                    itensOferecidos[qtdItensOferecidos] = parseItem(trim(l.substr(2)));
                    qtdItensOferecidos++;
                }
            } else if (l[0] == '#') {
                if (qtdOpcoes < MAX_OPCOES) {
                    size_t doisPontos = l.find(':');
                    opcoes[qtdOpcoes].destino = stoi(trim(l.substr(1, doisPontos - 1)));
                    opcoes[qtdOpcoes].texto = trim(l.substr(doisPontos + 1));
                    qtdOpcoes++;
                }
            }
        }
    } else {
        // 3b) Cena de monstro: campos "CHAVE: valor" e, por ultimo, "sucesso;derrota"
        string nomeMonstro;
        int hab = 0, srt = 0, en = 0, tes = -1, prov = -1;
        bool temItemMonstro = false;
        Item itemMonstro;

        while (getline(arq, linha)) {
            string l = trim(linha);
            if (l.empty()) continue;

            // A ultima linha ("sucesso;derrota") tem ';' mas NAO tem ':'
            if (l.find(':') == string::npos && l.find(';') != string::npos) {
                size_t p = l.find(';');
                int cenaSucesso = stoi(trim(l.substr(0, p)));
                int cenaDerrota = stoi(trim(l.substr(p + 1)));
                monstro.configurar(nomeMonstro, hab, srt, en, tes, prov,
                                    temItemMonstro, itemMonstro, cenaSucesso, cenaDerrota);
                continue;
            }

            size_t doisPontos = l.find(':');
            if (doisPontos == string::npos) continue;
            string chave = trim(l.substr(0, doisPontos));
            string valor = trim(l.substr(doisPontos + 1));

            if (chave == "N") nomeMonstro = valor;
            else if (chave == "M") { /* S/N arcano -- nao usado nesta versao simplificada */ }
            else if (chave == "H") hab = stoi(valor);
            else if (chave == "S") srt = stoi(valor);
            else if (chave == "E") en = stoi(valor);
            else if (chave == "T") tes = stoi(valor);
            else if (chave == "P") prov = stoi(valor);
            else if (chave == "I") {
                temItemMonstro = true;
                itemMonstro = parseItem(valor);
            }
        }
    }

    arq.close();
    return true;
}

TipoCena Cena::getTipo() const { return tipo; }
string Cena::getTexto() const { return texto; }

int Cena::getQtdItensOferecidos() const { return qtdItensOferecidos; }
const Item& Cena::getItemOferecido(int indice) const { return itensOferecidos[indice]; }

int Cena::getQtdOpcoes() const { return qtdOpcoes; }
const Opcao& Cena::getOpcao(int indice) const { return opcoes[indice]; }

Monstro& Cena::getMonstro() { return monstro; }
