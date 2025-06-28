#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <string>

/**
 * Classe que representa uma única assinatura de serviço.
 * Guarda informações como nome, valor da mensalidade e o dia da renovação.
 */
class Assinatura {
private:
    std::string nome_;
    double valor_;
    int diaRenovacao_;

public:
    // Construtor que cria uma nova assinatura e valida os dados de entrada.
    Assinatura(std::string nome, double valor, int diaRenovacao);

    // Funções para obter os dados da assinatura.
    std::string getNome() const;
    double getValor() const;
    int getDiaRenovacao() const;

    // Funções para alterar os dados da assinatura.
    void setNome(const std::string& nome);

    // Altera o valor da mensalidade, validando para não ser negativo.
    void setValor(double valor);
    
    void setDiaRenovacao(int dia);

    // Imprime os detalhes da assinatura de forma organizada no console.
    void exibir() const;
};

#endif // ASSINATURA_H