#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <string>

class Assinatura {
private:
    std::string nome_;
    double valor_;
    int diaRenovacao_;

public:
    Assinatura(std::string nome, double valor, int diaRenovacao);

    std::string getNome() const;
    double getValor() const;
    int getDiaRenovacao() const;

    void setNome(const std::string& nome);
    void setValor(double valor);
    void setDiaRenovacao(int dia);
};

#endif
