#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/assinatura.h"

TEST_CASE("Testando construtor e getters de Assinatura") {
    Assinatura a("Netflix", 29.90, 10);

    CHECK(a.getNome() == "Netflix");
    CHECK(a.getValor() == doctest::Approx(29.90));
    CHECK(a.getDiaRenovacao() == 10);
}

TEST_CASE("Testando alteração de valores na Assinatura (se existir)") {
    Assinatura a("Spotify", 19.90, 15);
    
    a.setNome("Spotify Premium");
    a.setValor(24.90);
    a.setDiaRenovacao(5);

    CHECK(a.getNome() == "Spotify Premium");
    CHECK(a.getValor() == doctest::Approx(24.90));
    CHECK(a.getDiaRenovacao() == 5);
}
