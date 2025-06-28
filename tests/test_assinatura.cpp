#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/assinatura.h"
#include "../include/erros.h"

// Teste - Sucesso: verifica se o construtor e os getters funcionam
// corretamente com dados válidos.
TEST_CASE("Testando construtor e getters de Assinatura") {
    Assinatura a("Netflix", 29.90, 10);

    CHECK(a.getNome() == "Netflix");
    CHECK(a.getValor() == doctest::Approx(29.90));
    CHECK(a.getDiaRenovacao() == 10);
}

// Teste - Sucesso para os setters: garante que os dados podem ser
// alterados corretamente com novos valores válidos.
TEST_CASE("Testando alteração de valores válidos na Assinatura") {
    Assinatura a("Spotify", 19.90, 15);
    
    a.setNome("Spotify Premium");
    a.setValor(24.90);
    a.setDiaRenovacao(5);

    CHECK(a.getNome() == "Spotify Premium");
    CHECK(a.getValor() == doctest::Approx(24.90));
    CHECK(a.getDiaRenovacao() == 5);
}

// Conjunto de testes para os Testes - Falha, para garantir que a classe
// lida corretamente com dados inválidos, lançando as exceções.
TEST_CASE("Testando validações e exceções da Assinatura") {
    
    // Testa se o construtor barra a criação de objetos com dados inválidos.
    SUBCASE("Construtor com dados inválidos") {
        CHECK_THROWS_AS(Assinatura("", 39.90, 10), NomeAssinaturaInvalidoException);
        CHECK_THROWS_AS(Assinatura("Netflix", -1.0, 10), ValorAssinaturaInvalidoException);
        CHECK_THROWS_AS(Assinatura("Spotify", 19.90, 0), DiaRenovacaoInvalidoException);
        CHECK_THROWS_AS(Assinatura("HBO Max", 29.90, 32), DiaRenovacaoInvalidoException);
    }

    // Testa se os setters lançam exceções com dados inválidos.
    // Mais importante: verifica se o estado do objeto permanece o mesmo
    // após a falha.
    SUBCASE("Setters com dados inválidos não devem alterar o estado") {
        Assinatura a("Valida", 10.0, 15);

        CHECK_THROWS_AS(a.setNome(""), NomeAssinaturaInvalidoException);
        CHECK(a.getNome() == "Valida"); // Verifica se o nome não mudou

        CHECK_THROWS_AS(a.setValor(-5.0), ValorAssinaturaInvalidoException);
        CHECK(a.getValor() == doctest::Approx(10.0)); // Verifica se o valor não mudou

        CHECK_THROWS_AS(a.setDiaRenovacao(0), DiaRenovacaoInvalidoException);
        CHECK(a.getDiaRenovacao() == 15); // Verifica se o dia não mudou

        CHECK_THROWS_AS(a.setDiaRenovacao(35), DiaRenovacaoInvalidoException);
        CHECK(a.getDiaRenovacao() == 15);
    }
}