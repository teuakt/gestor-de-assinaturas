#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/lembrete.h"
#include "../include/usuario.h"
#include "../include/erros.h"

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

int calcularDiaFuturo(int diaAtual, int diasAMais) {

    time_t agora = time(0);
    tm* ltm = localtime(&agora);
    ltm->tm_mday += diasAMais;
    mktime(ltm);
    return ltm->tm_mday;
}


TEST_CASE("Testando a classe Lembrete") {
    Usuario usuario;

    time_t tempoAtual = time(nullptr);
    tm* tempoLocal = localtime(&tempoAtual);
    int diaAtual = tempoLocal->tm_mday;

    SUBCASE("verificarRenovacoes lança exceção se a lista de assinaturas estiver vazia") {
        Lembrete lembrete(usuario);
        CHECK_THROWS_AS(lembrete.verificarRenovacoes(7), ListaDeAssinaturasVaziaException);
    }

    SUBCASE("verificarRenovacoes identifica corretamente as renovações próximas") {

        Assinatura a_proxima("Netflix", 39.90, calcularDiaFuturo(diaAtual, 2)); 
        Assinatura a_limite("Spotify", 19.90, calcularDiaFuturo(diaAtual, 7)); 
        Assinatura a_distante("Disney+", 29.90, calcularDiaFuturo(diaAtual, 10)); 

        usuario.adicionarAssinatura(a_proxima);
        usuario.adicionarAssinatura(a_limite);
        usuario.adicionarAssinatura(a_distante);

        Lembrete lembrete(usuario);

        std::stringstream buffer_captura;
        auto* backup_cout = std::cout.rdbuf(); 
        std::cout.rdbuf(buffer_captura.rdbuf()); 

        lembrete.verificarRenovacoes(7);

        std::cout.rdbuf(backup_cout);

        std::string saida_capturada = buffer_captura.str();

        CHECK(saida_capturada.find("Atenção! A assinatura \"Netflix\"") != std::string::npos);
        CHECK(saida_capturada.find("Atenção! A assinatura \"Spotify\"") != std::string::npos);
        
        CHECK(saida_capturada.find("Atenção! A assinatura \"Disney+\"") == std::string::npos);
    }
}