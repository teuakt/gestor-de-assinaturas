#include "gestor.h"
#include "lembrete.h"
#include <iostream>

int main() {
    Gestor gestor;

    if (!gestor.carregarUsuario()) {
        std::cout << "Erro ao carregar dados do usuário." << std::endl;
    }

    Lembrete lembrete(gestor.getUsuario());
    lembrete.verificarRenovacoes(7);

    gestor.exibirMenu();

    return 0;
}
