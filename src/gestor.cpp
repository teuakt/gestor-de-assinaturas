#include "gestor.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Gestor::Gestor() {
    usuario_.carregarDeArquivo("userData.txt");
    
}

bool Gestor::carregarUsuario() {
    return usuario_.carregarDeArquivo("userData.txt");
}

Usuario& Gestor::getUsuario() {
    return usuario_;
}

void Gestor::exibirMenu() {
    int opcao = -1;

    

    while (opcao != 0) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n=== Gestor de Assinaturas de Streaming ===\n";
        cout << "1. Adicionar assinatura\n";
        cout << "2. Remover assinatura\n";
        cout << "3. Editar assinatura\n";
        cout << "4. Listar assinaturas\n";
        cout << "5. Gerar relatorio de gastos\n";
        cout << "6. Verificar lembretes de renovação" << endl;
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        this_thread::sleep_for(chrono::milliseconds(300));
        cin.ignore();
        processarComando(opcao);
    }
    cout << "Encerrando o programa. Até logo!\n";
}

void Gestor::processarComando(int opcao) {
    switch (opcao) {
        case 1: {
            string nome;
            double valor;
            int dia;

            cout << "Nome da assinatura: ";
            getline(cin, nome);

            cout << "Valor mensal (R$): ";
            cin >> valor;

            cout << "Dia de renovação (1-31): ";
            cin >> dia;
            cin.ignore();

            Assinatura nova(nome, valor, dia);
            usuario_.adicionarAssinatura(nova);
            usuario_.salvarEmArquivo("userData.txt");
            cout << "Assinatura adicionada com sucesso!\n";
            break;
        }
        case 2: {
            string nome;
            cout << "Nome da assinatura a remover: ";
            getline(cin, nome);

            if (usuario_.removerAssinatura(nome)) {
                usuario_.salvarEmArquivo("userData.txt");
                cout << "Assinatura removida com sucesso!\n";
            } else {
                cout << "Assinatura não encontrada.\n";
            }
            break;
        }
        case 3: {
            string nomeAntigo, nomeNovo;
            double valorNovo;
            int diaNovo;

            cout << "Nome da assinatura a editar: ";
            getline(cin, nomeAntigo);

            cout << "Novo nome: ";
            getline(cin, nomeNovo);

            cout << "Novo valor (R$): ";
            cin >> valorNovo;

            cout << "Novo dia de renovação: ";
            cin >> diaNovo;
            cin.ignore();

            Assinatura nova(nomeNovo, valorNovo, diaNovo);
            if (usuario_.editarAssinatura(nomeAntigo, nova)) {
                usuario_.salvarEmArquivo("userData.txt");
                cout << "Assinatura atualizada com sucesso!\n";
            } else {
                cout << "Assinatura não encontrada.\n";
            }
            break;
        }
        case 4:
            usuario_.listarAssinaturas();
            break;
        case 5:
            cout << "Gasto mensal total: R$ " << usuario_.calcularGastoMensal() << "\n";
            break;
        case 6: {
            int dias;
            cout << "Verificar lembretes de renovação nos próximos quantos dias? ";
            cin >> dias;
            Lembrete lembrete(usuario_);
            lembrete.verificarRenovacoes(dias);
            break;
}
        case 0:
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
    }
}
