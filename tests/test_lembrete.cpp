#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../include/lembrete.h"
#include "../include/usuario.h"
#include "../include/erros.h"

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

// Testes para a classe Lembrete.
// O principal desafio aqui é testar uma classe que depende da data atual
// e que imprime sua saída diretamente no console.

// Função auxiliar para calcular uma data futura.
// Usar isso em vez de `diaAtual + X` evita problemas na virada do mês
int calcularDiaFuturo(int diaAtual, int diasAMais) {
    time_t agora = time(0);
    tm* ltm = localtime(&agora);
    ltm->tm_mday += diasAMais;
    mktime(ltm); // Normaliza a data (ex: dia 32 vira dia 1 do próximo mês)
    return ltm->tm_mday;
}


TEST_CASE("Testando a classe Lembrete") {
    // Prepara um ambiente comum para os sub-casos de teste.
    Usuario usuario;
    int diaAtual = localtime(&((time_t){time(nullptr)}))->tm_mday;

    // Testa o caminho de erro: uma lista vazia deve lançar a exceção correta.
    SUBCASE("verificarRenovacoes lança exceção se a lista de assinaturas estiver vazia") {
        Lembrete lembrete(usuario);
        CHECK_THROWS_AS(lembrete.verificarRenovacoes(7), ListaDeAssinaturasVaziaException);
    }

    SUBCASE("verificarRenovacoes identifica corretamente as renovações próximas") {
        // 1. PREPARAÇÃO: Cria assinaturas com datas de renovação
        // relativas ao dia de hoje para simular diferentes cenários.
        Assinatura a_proxima("Netflix", 39.90, calcularDiaFuturo(diaAtual, 2)); // Deve aparecer
        Assinatura a_limite("Spotify", 19.90, calcularDiaFuturo(diaAtual, 7)); // Deve aparecer
        Assinatura a_distante("Disney+", 29.90, calcularDiaFuturo(diaAtual, 10)); // NÃO deve aparecer

        usuario.adicionarAssinatura(a_proxima);
        usuario.adicionarAssinatura(a_limite);
        usuario.adicionarAssinatura(a_distante);

        Lembrete lembrete(usuario);

        // 2. AÇÃO: Redireciona o `cout` para um buffer em memória para que
        // possamos capturar e analisar a saída da função.
        std::stringstream buffer_captura;
        auto* backup_cout = std::cout.rdbuf(); 
        std::cout.rdbuf(buffer_captura.rdbuf()); 

        lembrete.verificarRenovacoes(7);

        // É crucial restaurar o cout para seu estado original.
        std::cout.rdbuf(backup_cout);

        // 3. VERIFICAÇÃO: Analisa a string capturada para garantir que
        // as mensagens de lembrete corretas foram impressas.
        std::string saida_capturada = buffer_captura.str();

        CHECK(saida_capturada.find("Atenção! A assinatura \"Netflix\"") != std::string::npos);
        CHECK(saida_capturada.find("Atenção! A assinatura \"Spotify\"") != std::string::npos);
        CHECK(saida_capturada.find("Atenção! A assinatura \"Disney+\"") == std::string::npos);
    }
}