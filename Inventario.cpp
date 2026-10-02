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
    copiarDe(outro);
}

Inventario& Inventario::operator=(const Inventario& outro) {
    if (this == &outro) return *this;   // protege contra "obj = obj;"
    delete[] itens;                      // libera o array antigo
    copiarDe(outro);
    return *this;
}
