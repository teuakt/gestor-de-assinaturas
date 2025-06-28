#ifndef GESTOR_H
#define GESTOR_H

#include "usuario.h"
#include <string>

class Gestor {
public:
    Gestor(const std::string& arquivo_dados = "userData.txt");

    Usuario& getUsuario();

    void exibirMenu(); 

private:
    Usuario usuario_;
    void processarComando(int opcao); 
};

#endif // GESTOR_H