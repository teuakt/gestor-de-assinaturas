#include "assinatura.h"
#include <iostream>

using namespace std;

Assinatura::Assinatura(string nome, double valor, int diaRenovacao)
    : nome_(nome), valor_(valor), diaRenovacao_(diaRenovacao) {}

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
    nome_ = nome;
}

void Assinatura::setValor(double valor) {
    valor_ = valor;
}

void Assinatura::setDiaRenovacao(int dia) {
    diaRenovacao_ = dia;
}

void Assinatura::exibir() const {
    cout << "Assinatura: " << nome_ << endl;
    cout << "Valor: R$ " << valor_ << endl;
    cout << "Dia de Renovação: " << diaRenovacao_ << endl;
    cout << "-----------------------------" << endl;
}