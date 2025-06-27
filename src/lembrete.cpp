#include "lembrete.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

Lembrete::Lembrete(Usuario& usuario)
    : usuario_(usuario) {}

void Lembrete::verificarRenovacoes(int diasAntecedencia) const {
    time_t tempoAtual = time(nullptr);
    tm* tempoLocal = localtime(&tempoAtual);
    int diaAtual = tempoLocal->tm_mday;

    cout << "\nVerificando renovações para os próximos " << diasAntecedencia << " dias..." << endl;
    bool encontrou = false;

    const vector<Assinatura>& assinaturas = usuario_.getAssinaturas();

    for (const auto& assinatura : assinaturas) {
        int diaRenovacao = assinatura.getDiaRenovacao();
        int diasRestantes = diaRenovacao - diaAtual;
        this_thread::sleep_for(chrono::milliseconds(500));
        if (diasRestantes >= 0 && diasRestantes <= diasAntecedencia) {
            cout << "\nAtenção! A assinatura \"" << assinatura.getNome()
                 << "\" será renovada em " << diasRestantes << " dia(s)!" << endl;
            encontrou = true;
        }
    }

    if (!encontrou) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Nenhuma renovação prevista para os próximos dias." << endl;
    }
}
