// assinatura.cpp
#include "assinatura.h"
#include "erros.h"
#include <iostream>

using namespace std;

Assinatura::Assinatura(string nome, double valor, int diaRenovacao) {
    if (nome.empty()) {
        throw NomeAssinaturaInvalidoException{};
    }
    if (valor < 0.0) {
        throw ValorAssinaturaInvalidoException{valor};
    }
    if (diaRenovacao < 1 || diaRenovacao > 31) {
        throw DiaRenovacaoInvalidoException{diaRenovacao};
    }

    nome_ = nome;
    valor_ = valor;
    diaRenovacao_ = diaRenovacao;
}

string Assinatura::getNome() const {
    return nome_;
}

double Assinatura::getValor() const {
    return valor_;
}

int Assinatura::getDiaRenovacao() const {
    return diaRenovacao_;
}

void Assinatura::setNome(const string& nome) {
    if (nome.empty()) {
        throw NomeAssinaturaInvalidoException{};
    }
    nome_ = nome;
}

void Assinatura::setValor(double valor) {
    if (valor < 0.0) {
        throw ValorAssinaturaInvalidoException{valor};
    }
    valor_ = valor;
}

void Assinatura::setDiaRenovacao(int dia) {
    if (dia < 1 || dia > 31) {
        throw DiaRenovacaoInvalidoException{dia};
    }
    diaRenovacao_ = dia;
}

void Assinatura::exibir() const {
    cout << "Assinatura: " << nome_ << endl;
    cout << "Valor: R$ " << valor_ << endl;
    cout << "Dia de Renovação: " << diaRenovacao_ << endl;
    cout << "-----------------------------" << endl;
}