#include "Cena.h"
#include <fstream>
#include <iostream>
using namespace std;

Cena::Cena() : tipo(NARRATIVA), qtdItensOferecidos(0), qtdOpcoes(0) {}

bool Cena::carregarDeArquivo(int numeroCena, const string& caminhoPasta) {
    string caminho = caminhoPasta + "/" + to_string(numeroCena) + ".txt";
    ifstream arq(caminho);
    if (!arq.is_open()) {
        cout << "ERRO: nao foi possivel abrir a cena " << caminho << endl;
        return false;
    }
    string primeiraLinha;
    getline(arq, primeiraLinha);
    tipo = (trim(primeiraLinha) == "m") ? CENA_MONSTRO : NARRATIVA;

    string linha;
    texto = "";
    while (getline(arq, linha)) {
        if (trim(linha).empty()) break;
        if (!texto.empty()) texto += " ";
        texto += trim(linha);
    }

    if (tipo == NARRATIVA) {
        while (getline(arq, linha)) {
            string l = trim(linha);
            if (l.empty()) continue;

            if (l.rfind("I:", 0) == 0) {
                if (qtdItensOferecidos < MAX_ITENS_OFERECIDOS) {
                    itensOferecidos[qtdItensOferecidos] = Item::fromString(trim(l.substr(2)));
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
        string nomeMonstro;
        int hab = 0, srt = 0, en = 0, tes = -1, prov = -1;
        bool temItemMonstro = false;
        Item itemMonstro;

        while (getline(arq, linha)) {
            string l = trim(linha);
            if (l.empty()) continue;
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
            else if (chave == "M") {}
            else if (chave == "H") hab = stoi(valor);
            else if (chave == "S") srt = stoi(valor);
            else if (chave == "E") en = stoi(valor);
            else if (chave == "T") tes = stoi(valor);
            else if (chave == "P") prov = stoi(valor);
            else if (chave == "I") {
                temItemMonstro = true;
                itemMonstro = Item::fromString(valor);
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
