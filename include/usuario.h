#ifndef USUARIO_H
#define USUARIO_H

#include "assinatura.h"
#include <vector>
#include <string>

class Usuario {
private:
    std::vector<Assinatura> assinaturas_;

public:
    void adicionarAssinatura(const Assinatura& assinatura);
    bool removerAssinatura(const std::string& nome);
    bool editarAssinatura(const std::string& nome, const Assinatura& novaAssinatura);
    void listarAssinaturas() const;
    double calcularGastoMensal() const;

    const std::vector<Assinatura>& getAssinaturas() const;

    bool salvarEmArquivo(const std::string& nomeArquivo) const;
    bool carregarDeArquivo(const std::string& nomeArquivo);
};

#endif