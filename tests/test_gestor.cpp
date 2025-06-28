#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/gestor.h"
#include "../include/erros.h"
#include <fstream>
#include <cstdio>

const std::string NOME_ARQUIVO_TESTE = "test_gestor_data.txt";

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
    
    SUBCASE("Construtor carrega dados de um arquivo válido") {
        criarArquivoTesteValido();
        
        Gestor gestor(NOME_ARQUIVO_TESTE);
        Usuario& usuario = gestor.getUsuario();

        CHECK(usuario.getAssinaturas().size() == 2);
        CHECK(usuario.getAssinaturas()[0].getNome() == "Netflix");
        CHECK(usuario.getAssinaturas()[1].getValor() == doctest::Approx(19.90));
        
        removerArquivoTeste();
    }

    SUBCASE("Construtor lida com arquivo inexistente") {
        removerArquivoTeste(); 
        Gestor gestor(NOME_ARQUIVO_TESTE);
        Usuario& usuario = gestor.getUsuario();

        CHECK(usuario.getAssinaturas().empty() == true);
    }

    SUBCASE("Construtor propaga exceção de arquivo corrompido") {
        criarArquivoTesteCorrompido();
        
        Usuario u_teste;
        CHECK_THROWS_AS(u_teste.carregarDeArquivo(NOME_ARQUIVO_TESTE), ErroDeFormatoDeArquivoException);
        
        removerArquivoTeste();
    }
}