#ifndef GESTOR_H
#define GESTOR_H

#include "usuario.h"
#include <string>

/**
 * Classe responsável por controlar a interface com o usuário.
 * Ela gerencia o menu principal e direciona as ações para o objeto Usuario.
 */
class Gestor {
public:
    // Construtor que inicializa o gestor.
    // Tenta carregar os dados de um arquivo, usando "userData.txt" como padrão.
    Gestor(const std::string& arquivo_dados = "userData.txt");

    Usuario& getUsuario();

    // Ponto de entrada do programa, exibe o menu e lida com a interação.
    void exibirMenu(); 

private:
    // Objeto que contém todos os dados e a lógica das assinaturas.
    Usuario usuario_;
    
    // Função interna, chamada pelo exibirMenu para executar a ação escolhida.
    void processarComando(int opcao); 
};

#endif // GESTOR_H