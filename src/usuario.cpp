#include "gestor.h"
#include <iostream>

using namespace std;

void Gestor::adicionarAssinatura(const Assinatura& assinatura) {
    assinaturas_.push_back(assinatura);
}

bool Gestor::removerAssinatura(const string& nome) {
    for (auto it = assinaturas_.begin(); it != assinaturas_.end(); ++it) {
        if (it->getNome() == nome) {
            assinaturas_.erase(it);
            return true;
        }
    }
    return false;
}

bool Gestor::editarAssinatura(const string& nome, const Assinatura& novaAssinatura) {
    for (auto& a : assinaturas_) {
        if (a.getNome() == nome) {
            a = novaAssinatura;
            return true;
        }
    }
    return false;
}

void Gestor::listarAssinaturas() const {
    if (assinaturas_.empty()) {
        cout << "Nenhuma assinatura cadastrada.\n";
        return;
    }

    cout << "Assinaturas cadastradas:\n";
    for (const auto& a : assinaturas_) {
        a.exibir();
    }
}
