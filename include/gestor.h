#ifndef GESTOR_H
#define GESTOR_H

#include "usuario.h"
#include "lembrete.h"

class Gestor {
private:
    Usuario usuario_;
    std::vector<Assinatura> assinaturas_;

public:
    Gestor();
    bool carregarUsuario();
    Usuario& getUsuario();

    void exibirMenu(); 
    void processarComando(int opcao); 
};

#endif