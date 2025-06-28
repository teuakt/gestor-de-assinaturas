#include "gestor.h"
#include "lembrete.h"
#include "erros.h" 
#include <iostream>

// Ponto de entrada principal do programa.
int main() {
    // A lógica principal é envolvida em um grande try-catch. Isso serve para
    // capturar erros que podem acontecer na inicialização (como um
    // arquivo de dados corrompido) e encerrar o programa.
    try {
        // 1. Cria o objeto principal do gestor.
        // O construtor do Gestor já tenta carregar os dados do arquivo "userData.txt".
        Gestor gestor;

        // 2. Bloco para verificar lembretes na inicialização.
        // Usamos um try-catch aninhado porque uma lista vazia para o lembrete
        // não é um erro fatal; o programa deve apenas avisar e continuar.
        try {
            Lembrete lembrete(gestor.getUsuario());
            lembrete.verificarRenovacoes(7); 
        } catch (const ListaDeAssinaturasVaziaException& e) {
            std::cout << "\nNenhuma assinatura cadastrada para verificar lembretes." << std::endl;
        }

        // 3. Inicia o loop do menu, onde o usuário interage.
        gestor.exibirMenu();

    } catch (const ErroDeFormatoDeArquivoException& e) {
        // Se o arquivo de dados estiver corrompido, o programa não pode continuar.
        // Este catch informa o usuário sobre o problema.
        std::cerr << "ERRO CRÍTICO NA INICIALIZAÇÃO: O arquivo de dados está corrompido na linha " << e.linha << "." << std::endl;
        std::cerr << "--> Conteúdo: \"" << e.conteudo << "\"" << std::endl;
        std::cerr << "--> O programa não pode continuar. Corrija o arquivo 'userData.txt' e tente novamente." << std::endl;
        return 1; // Retorna 1 para indicar que o programa terminou com erro.
    } catch (const std::exception& e) {
        // Bloco para capturar quaisquer outros erros inesperados.
        std::cerr << "Ocorreu um erro inesperado: " << e.what() << std::endl;
        return 1;
    }

    // Se tudo correu bem, retorna 0.
    return 0; 
}
