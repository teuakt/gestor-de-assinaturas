#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"

#include "lembrete.h"
#include "usuario.h"
#include "assinatura.h"

#include <vector>

TEST_CASE("Teste básico de Lembrete::verificarRenovacoes") {
    Usuario usuario;

    time_t tempoAtual = time(nullptr);
    tm* tempoLocal = localtime(&tempoAtual);
    int diaAtual = tempoLocal->tm_mday;

    Assinatura a1("Netflix", 29.90, diaAtual + 1);
    Assinatura a2("Spotify", 19.90, diaAtual + 5);
    Assinatura a3("Amazon Prime", 14.90, diaAtual + 10);

    usuario.adicionarAssinatura(a1);
    usuario.adicionarAssinatura(a2);
    usuario.adicionarAssinatura(a3);

    Lembrete lembrete(usuario);

    lembrete.verificarRenovacoes(7);

}
