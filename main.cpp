#include <iostream>
#include "include/gestor.h"
#include "include/assinatura.h"

using namespace std;

int main() {
    Gestor gestor;

    Assinatura netflix("Netflix", 39.90, 15);
    Assinatura spotify("Spotify", 19.90, 10);

    gestor.adicionarAssinatura(netflix);
    gestor.adicionarAssinatura(spotify);

    cout << "Assinaturas cadastradas:" << endl;
    gestor.listarAssinaturas();

    gestor.removerAssinatura("Spotify");

    cout << "\nApós remover Spotify:" << endl;
    gestor.listarAssinaturas();

    return 0;
}
