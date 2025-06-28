#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/assinatura.h"
#include "../include/erros.h"

TEST_CASE("Testando construtor e getters de Assinatura") {
    Assinatura a("Netflix", 29.90, 10);

    CHECK(a.getNome() == "Netflix");
    CHECK(a.getValor() == doctest::Approx(29.90));
    CHECK(a.getDiaRenovacao() == 10);
}

TEST_CASE("Testando alteração de valores válidos na Assinatura") {
    Assinatura a("Spotify", 19.90, 15);
    
    a.setNome("Spotify Premium");
    a.setValor(24.90);
    a.setDiaRenovacao(5);

    CHECK(a.getNome() == "Spotify Premium");
    CHECK(a.getValor() == doctest::Approx(24.90));
    CHECK(a.getDiaRenovacao() == 5);
}

TEST_CASE("Testando validações e exceções da Assinatura") {
    
    SUBCASE("Construtor com dados inválidos") {
        CHECK_THROWS_AS(Assinatura("", 39.90, 10), NomeAssinaturaInvalidoException);
        CHECK_THROWS_AS(Assinatura("Netflix", -1.0, 10), ValorAssinaturaInvalidoException);
        CHECK_THROWS_AS(Assinatura("Spotify", 19.90, 0), DiaRenovacaoInvalidoException);
        CHECK_THROWS_AS(Assinatura("HBO Max", 29.90, 32), DiaRenovacaoInvalidoException);
    }

    SUBCASE("Setters com dados inválidos não devem alterar o estado") {
        Assinatura a("Valida", 10.0, 15);

        CHECK_THROWS_AS(a.setNome(""), NomeAssinaturaInvalidoException);
        CHECK(a.getNome() == "Valida");

        CHECK_THROWS_AS(a.setValor(-5.0), ValorAssinaturaInvalidoException);
        CHECK(a.getValor() == doctest::Approx(10.0));

        CHECK_THROWS_AS(a.setDiaRenovacao(0), DiaRenovacaoInvalidoException);
        CHECK(a.getDiaRenovacao() == 15);

        CHECK_THROWS_AS(a.setDiaRenovacao(35), DiaRenovacaoInvalidoException);
        CHECK(a.getDiaRenovacao() == 15);
    }
}