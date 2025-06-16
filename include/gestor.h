#ifndef GESTOR_H
#define GESTOR_H

#include "assinatura.h"
#include <vector>
#include <string>

class Gestor {
private:
    std::vector<Assinatura> assinaturas_;

public:
    void adicionarAssinatura(const Assinatura& assinatura);

    bool removerAssinatura(const std::string& nome);

    bool editarAssinatura(const std::string& nome, const Assinatura& novaAssinatura);

    void listarAssinaturas() const;
};

#endif
