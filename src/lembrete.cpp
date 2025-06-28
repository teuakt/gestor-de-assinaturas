#include "lembrete.h"
#include "erros.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

Lembrete::Lembrete(Usuario& usuario)
    : usuario_(usuario) {}

void Lembrete::verificarRenovacoes(int diasAntecedencia) const {
    const vector<Assinatura>& assinaturas = usuario_.getAssinaturas();

    // Primeiro, trata o caso em que não há nenhuma assinatura para verificar.
    if (assinaturas.empty()) {
        throw ListaDeAssinaturasVaziaException{};
    }

    // Pega a data atual do sistema para fazer a comparação.
    time_t tempoAtual = time(nullptr);
    tm* tempoLocal = localtime(&tempoAtual);
    int diaAtual = tempoLocal->tm_mday;

    cout << "\nVerificando renovações para os próximos " << diasAntecedencia << " dias..." << endl;
    
    for (const auto& assinatura : assinaturas) {
        int diaRenovacao = assinatura.getDiaRenovacao();
        
        // Lógica para calcular os dias restantes até a próxima renovação.
        int diasRestantes = diaRenovacao - diaAtual;

        // Se o dia de renovação já passou neste mês, calcula para o próximo.
        // NOTA: Esta é uma simplificação que considera que os meses têm 30 dias.
        if (diaRenovacao < diaAtual) {
            diasRestantes += 30; 
        }

        // Pequena pausa para um efeito visual mais agradável na exibição.
        this_thread::sleep_for(chrono::milliseconds(500));
        
        // Se a renovação estiver dentro do prazo desejado, exibe o alerta.
        if (diasRestantes >= 0 && diasRestantes <= diasAntecedencia) {
            cout << "  -> Atenção! A assinatura \"" << assinatura.getNome()
                 << "\" será renovada em " << diasRestantes << " dia(s)!" << endl;
        }
    }
}