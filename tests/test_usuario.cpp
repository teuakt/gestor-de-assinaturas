#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/usuario.h"
#include <fstream>

using namespace std;

TEST_CASE("Testando funcionalidades básicas da classe Usuario") {
    Usuario user;
    Assinatura netflix("Netflix", 39.90, 15);
    Assinatura spotify("Spotify", 19.90, 5);

    SUBCASE("Adicionar assinatura") {
        user.adicionarAssinatura(netflix);
        CHECK(user.calcularGastoMensal() == doctest::Approx(39.90));
    }

    SUBCASE("Editar assinatura") {
        user.adicionarAssinatura(netflix);
        Assinatura novaNetflix("Netflix", 49.90, 10);
        CHECK(user.editarAssinatura("Netflix", novaNetflix) == true);
        CHECK(user.calcularGastoMensal() == doctest::Approx(49.90));
    }

    SUBCASE("Remover assinatura") {
        user.adicionarAssinatura(netflix);
        CHECK(user.removerAssinatura("Netflix") == true);
        CHECK(user.calcularGastoMensal() == doctest::Approx(0.0));
    }

    SUBCASE("Salvar e carregar de arquivo") {
        user.adicionarAssinatura(netflix);
        user.adicionarAssinatura(spotify);

        string nomeArquivo = "test_userData.txt";

        CHECK(user.salvarEmArquivo(nomeArquivo) == true);

        Usuario outroUsuario;
        CHECK(outroUsuario.carregarDeArquivo(nomeArquivo) == true);
        CHECK(outroUsuario.calcularGastoMensal() == doctest::Approx(39.90 + 19.90));

        remove(nomeArquivo.c_str());
    }
}
