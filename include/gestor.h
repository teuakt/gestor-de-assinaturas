#ifndef GESTOR_H
#define GESTOR_H

#include "usuario.h"

class Gestor {
private:
    Usuario usuario_;

public:
    Gestor();
    
    void exibirMenu(); 
    void processarComando(int opcao); 
};

#endif