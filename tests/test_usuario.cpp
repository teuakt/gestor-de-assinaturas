#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/usuario.h"
#include "../include/assinatura.h"
#include "../include/erros.h"
#include <fstream>
#include <cstdio>

// Uma "Fixture" é uma estrutura que prepara um ambiente de teste comum.
// Isso garante que cada SUBCASE comece com um objeto 'usuario' limpo.
struct FixtureUsuario {
    Usuario usuario;
    Assinatura a1{"Netflix", 39.90, 10};
    Assinatura a2{"Spotify", 19.90, 5};
};

TEST_CASE_FIXTURE(FixtureUsuario, "Testes de Gerenciamento de Assinaturas (Adicionar, Remover, Editar)") {

    SUBCASE("Adicionar uma nova assinatura com sucesso") {
        usuario.adicionarAssinatura(a1);
        CHECK(usuario.getAssinaturas().size() == 1);
        CHECK(usuario.getAssinaturas()[0].getNome() == "Netflix");
    }

    SUBCASE("Lançar exceção ao tentar adicionar uma assinatura duplicada") {
        usuario.adicionarAssinatura(a1);
        CHECK_THROWS_AS(usuario.adicionarAssinatura(a1), AssinaturaJaExisteException);

        CHECK(usuario.getAssinaturas().size() == 1);
    }

    SUBCASE("Remover uma assinatura existente com sucesso") {
        usuario.adicionarAssinatura(a1);

        CHECK_NOTHROW(usuario.removerAssinatura("Netflix"));
        CHECK(usuario.getAssinaturas().empty() == true);
    }

    SUBCASE("Lançar exceção ao tentar remover uma assinatura inexistente") {
        usuario.adicionarAssinatura(a1);
        CHECK_THROWS_AS(usuario.removerAssinatura("Inexistente"), AssinaturaNaoEncontradaException);
        CHECK(usuario.getAssinaturas().size() == 1);
    }

    SUBCASE("Editar uma assinatura existente com sucesso") {
        usuario.adicionarAssinatura(a1);
        Assinatura a1_editada("Netflix", 45.90, 12);
        CHECK_NOTHROW(usuario.editarAssinatura("Netflix", a1_editada));
        
        const auto& assinaturas = usuario.getAssinaturas();
        CHECK(assinaturas.size() == 1);
        CHECK(assinaturas[0].getValor() == doctest::Approx(45.90));
        CHECK(assinaturas[0].getDiaRenovacao() == 12);
    }

    SUBCASE("Lançar exceção ao tentar editar uma assinatura inexistente") {
        Assinatura a_fantasma("Fantasma", 1.0, 1);
        CHECK_THROWS_AS(usuario.editarAssinatura("Inexistente", a_fantasma), AssinaturaNaoEncontradaException);
    }

    SUBCASE("Lançar exceção ao listar assinaturas de uma lista vazia") {
        CHECK(usuario.getAssinaturas().empty() == true);
        CHECK_THROWS_AS(usuario.listarAssinaturas(), ListaDeAssinaturasVaziaException);
    }
    
    SUBCASE("Calcular gasto mensal corretamente") {
        CHECK(usuario.calcularGastoMensal() == doctest::Approx(0.0));
        usuario.adicionarAssinatura(a1);
        usuario.adicionarAssinatura(a2);
        CHECK(usuario.calcularGastoMensal() == doctest::Approx(59.80));
    }
}

TEST_CASE("Testes de Persistência em Arquivo do Usuário") {
    const std::string NOME_ARQUIVO = "test_usuario_data.txt";
    

    remove(NOME_ARQUIVO.c_str());

    SUBCASE("Salvar e carregar um arquivo com sucesso") {
        Usuario u_salvar;
        u_salvar.adicionarAssinatura(Assinatura("HBO Max", 29.90, 20));
        u_salvar.adicionarAssinatura(Assinatura("Youtube Premium", 20.90, 25));

        CHECK_NOTHROW(u_salvar.salvarEmArquivo(NOME_ARQUIVO));

        Usuario u_carregar;
        CHECK_NOTHROW(u_carregar.carregarDeArquivo(NOME_ARQUIVO));
        CHECK(u_carregar.getAssinaturas().size() == 2);
        CHECK(u_carregar.calcularGastoMensal() == doctest::Approx(50.80));
    }

    SUBCASE("Lançar exceção ao carregar arquivo inexistente") {
        Usuario usuario;
        CHECK_THROWS_AS(usuario.carregarDeArquivo("arquivo_que_nao_existe.txt"), ErroAoAbrirArquivoException);
    }

    SUBCASE("Lançar exceção ao carregar arquivo corrompido") {

        std::ofstream arq(NOME_ARQUIVO);
        arq << "Netflix;preco_errado;10\n";
        arq.close();

        Usuario usuario;
        CHECK_THROWS_AS(usuario.carregarDeArquivo(NOME_ARQUIVO), ErroDeFormatoDeArquivoException);
    }
    
    SUBCASE("Carregar um arquivo vazio resulta em lista vazia") {

        std::ofstream arq(NOME_ARQUIVO);
        arq.close();

        Usuario usuario;
        usuario.adicionarAssinatura(Assinatura("Teste", 1.0, 1)); // Adiciona algo para garantir que será limpo
        CHECK_NOTHROW(usuario.carregarDeArquivo(NOME_ARQUIVO));
        CHECK(usuario.getAssinaturas().empty() == true);
    }

    remove(NOME_ARQUIVO.c_str());
}