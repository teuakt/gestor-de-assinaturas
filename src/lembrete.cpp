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

    if (assinaturas.empty()) {
        throw ListaDeAssinaturasVaziaException{};
    }

    time_t tempoAtual = time(nullptr);
    tm* tempoLocal = localtime(&tempoAtual);
    int diaAtual = tempoLocal->tm_mday;

    cout << "\nVerificando renovações para os próximos " << diasAntecedencia << " dias..." << endl;
    
    for (const auto& assinatura : assinaturas) {
        int diaRenovacao = assinatura.getDiaRenovacao();
        
        int diasRestantes = diaRenovacao - diaAtual;
        if (diaRenovacao < diaAtual) {
            diasRestantes += 30; 
        }

        this_thread::sleep_for(chrono::milliseconds(500));
        if (diasRestantes >= 0 && diasRestantes <= diasAntecedencia) {
            cout << "  -> Atenção! A assinatura \"" << assinatura.getNome()
                 << "\" será renovada em " << diasRestantes << " dia(s)!" << endl;
        }
    }
}