#include "usuario.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void Usuario::adicionarAssinatura(const Assinatura& assinatura) {
    assinaturas_.push_back(assinatura);
}

bool Usuario::removerAssinatura(const string& nome) {
    for (auto it = assinaturas_.begin(); it != assinaturas_.end(); ++it) {
        if (it->getNome() == nome) {
            assinaturas_.erase(it);
            return true;
        }
    }
    return false;
}

bool Usuario::editarAssinatura(const string& nome, const Assinatura& novaAssinatura) {
    for (auto& a : assinaturas_) {
        if (a.getNome() == nome) {
            a = novaAssinatura;
            return true;
        }
    }
    return false;
}

void Usuario::listarAssinaturas() const {
    if (assinaturas_.empty()) {
        cout << "Nenhuma assinatura cadastrada.\n";
        return;
    }

    cout << "Assinaturas cadastradas:\n";
    for (const auto& a : assinaturas_) {
        a.exibir();
    }
}

double Usuario::calcularGastoMensal() const {
    double total = 0.0;
    for (const auto& a : assinaturas_) {
        total += a.getValor();
    }
    return total;
}

bool Usuario::salvarEmArquivo(const std::string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    for (const auto& a : assinaturas_) {
        arquivo << a.getNome() << ";" << a.getValor() << ";" << a.getDiaRenovacao() << "\n";
    }

    arquivo.close();
    return true;
}

bool Usuario::carregarDeArquivo(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    assinaturas_.clear();

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, valorStr, diaStr;
        
        getline(ss, nome, ';');
        getline(ss, valorStr, ';');
        getline(ss, diaStr, ';');
        
        double valor = stod(valorStr);
        int dia = stoi(diaStr);
        
        Assinatura a(nome, valor, dia);
        assinaturas_.push_back(a);
    }

    arquivo.close();
    return true;
}
