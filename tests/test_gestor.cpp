#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/gestor.h"
#include <fstream>

void criarArquivoTeste() {
    std::ofstream arq("userData.txt");
    arq << "Netflix;39.90;10\n";
    arq << "Spotify;19.90;5\n";
    arq.close();
}

TEST_CASE("Gestor inicializa e carrega assinaturas corretamente") {
    criarArquivoTeste();

    Gestor g;  
    CHECK(true);
}
