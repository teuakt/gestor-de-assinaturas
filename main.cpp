#include "gestor.h"
#include "lembrete.h"
#include "erros.h" 
#include <iostream>

int main() {
    try {
        Gestor gestor;

        try {
            Lembrete lembrete(gestor.getUsuario());
            lembrete.verificarRenovacoes(7); 
        } catch (const ListaDeAssinaturasVaziaException& e) {
            std::cout << "\nNenhuma assinatura cadastrada para verificar lembretes." << std::endl;
        }

        gestor.exibirMenu();

    } catch (const ErroDeFormatoDeArquivoException& e) {
        std::cerr << "ERRO CRÍTICO NA INICIALIZAÇÃO: O arquivo de dados está corrompido na linha " << e.linha << "." << std::endl;
        std::cerr << "--> Conteúdo: \"" << e.conteudo << "\"" << std::endl;
        std::cerr << "--> O programa não pode continuar. Corrija o arquivo 'userData.txt' e tente novamente." << std::endl;
        return 1;
    } catch (const std::exception& e) {

        std::cerr << "Ocorreu um erro inesperado: " << e.what() << std::endl;
        return 1;
    }

    return 0; 
}