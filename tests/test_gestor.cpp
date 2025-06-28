#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/gestor.h"
#include "../include/erros.h"
#include <fstream>
#include <cstdio> // Para a função remove()

// Testes para a classe Gestor, lidando com diferentes
// cenários de arquivos de dados.

const std::string NOME_ARQUIVO_TESTE = "test_gestor_data.txt";

// --- Funções Auxiliares para Manipulação de Arquivos de Teste ---
// Estas funções criam e removem arquivos temporários para que os testes
// possam rodar em um ambiente controlado e previsível, sem usar o "userData.txt" real.

void criarArquivoTesteValido() {
    std::ofstream arq(NOME_ARQUIVO_TESTE);
    arq << "Netflix;39.90;10\n";
    arq << "Spotify;19.90;5\n";
    arq.close();
}

void criarArquivoTesteCorrompido() {
    std::ofstream arq(NOME_ARQUIVO_TESTE);
    arq << "Netflix;valor_invalido;10\n";
    arq.close();
}

void removerArquivoTeste() {
    remove(NOME_ARQUIVO_TESTE.c_str());
}

TEST_CASE("Testando a Classe Gestor") {
    
    // Verifica se o construtor do Gestor consegue ler um arquivo bem formatado
    // e carregar os dados para o objeto Usuario.
    SUBCASE("Construtor carrega dados de um arquivo válido") {
        criarArquivoTesteValido();
        
        Gestor gestor(NOME_ARQUIVO_TESTE);
        Usuario& usuario = gestor.getUsuario();

        CHECK(usuario.getAssinaturas().size() == 2);
        CHECK(usuario.getAssinaturas()[0].getNome() == "Netflix");
        CHECK(usuario.getAssinaturas()[1].getValor() == doctest::Approx(19.90));
        
        removerArquivoTeste();
    }

    // Testa o comportamento quando o arquivo de dados não existe (ex: primeira execução).
    // O esperado é que o programa inicie normalmente com uma lista vazia.
    SUBCASE("Construtor lida com arquivo inexistente") {
        removerArquivoTeste(); // Garante que o arquivo não existe antes do teste
        
        Gestor gestor(NOME_ARQUIVO_TESTE);
        Usuario& usuario = gestor.getUsuario();

        CHECK(usuario.getAssinaturas().empty() == true);
    }

    // Testa o cenário de um arquivo com dados corrompidos.
    SUBCASE("Construtor propaga exceção de arquivo corrompido") {
        criarArquivoTesteCorrompido();
        
        Usuario u_teste;
        CHECK_THROWS_AS(u_teste.carregarDeArquivo(NOME_ARQUIVO_TESTE), ErroDeFormatoDeArquivoException);
        
        removerArquivoTeste();
    }
}