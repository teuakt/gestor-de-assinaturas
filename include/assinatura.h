#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <string>

class Assinatura {
private:
    std::string nome;
    double valor;
    int diaRenovacao;

public:
    Assinatura(std::string nome, double valor, int diaRenovacao);

    std::string getNome() const;
    double getValor() const;
    int getDiaRenovacao() const;

    void setNome(std::string novoNome);
    void setValor(double novoValor);
    void setDiaRenovacao(int novoDia);

    void exibir() const;
};

#endif
