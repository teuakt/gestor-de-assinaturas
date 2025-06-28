#include "gestor.h"
#include "assinatura.h"
#include "lembrete.h"
#include "erros.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <stdexcept> 

using namespace std;

Gestor::Gestor(const std::string& arquivo_dados) {
    try {
        usuario_.carregarDeArquivo(arquivo_dados);
    } catch (const ErroAoAbrirArquivoException& e) {}
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
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        
        cin >> opcao;

        if (cin.fail()) {
            cerr << "ERRO: Por favor, digite um número válido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (opcao != 0) {
            processarComando(opcao);
        }
    }
    cout << "Encerrando o programa. Até logo!\n";
}

void Gestor::processarComando(int opcao) {
    switch (opcao) {
        case 1: {
            try {
                string nome;
                double valor;
                int dia;

                cout << "Nome da assinatura: ";
                getline(cin, nome);

                cout << "Valor mensal (R$): ";
                cin >> valor;
                if (cin.fail()) throw runtime_error("Entrada de valor inválida.");

                cout << "Dia de renovação (1-31): ";
                cin >> dia;
                if (cin.fail()) throw runtime_error("Entrada de dia inválida.");

                Assinatura nova(nome, valor, dia);
                usuario_.adicionarAssinatura(nova);
                usuario_.salvarEmArquivo("userData.txt");
                cout << "Assinatura '" << nome << "' adicionada com sucesso!\n";

            } catch (const runtime_error& e) {
                cerr << "ERRO: " << e.what() << " Por favor, insira um número.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } catch (const NomeAssinaturaInvalidoException& e) {
                cerr << "ERRO: O nome da assinatura não pode ser vazio.\n";
            } catch (const ValorAssinaturaInvalidoException& e) {
                cerr << "ERRO: Valor inválido (R$ " << e.valor << "). O valor não pode ser negativo.\n";
            } catch (const DiaRenovacaoInvalidoException& e) {
                cerr << "ERRO: Dia de renovação inválido (" << e.dia << "). O dia deve ser entre 1 e 31.\n";
            } catch (const AssinaturaJaExisteException& e) {
                cerr << "ERRO: A assinatura '" << e.nome << "' já está cadastrada.\n";
            } catch (const ErroAoAbrirArquivoException& e) {
                cerr << "ERRO: Não foi possível salvar as alterações no arquivo '" << e.nomeArquivo << "'.\n";
            }
            break;
        }
        case 2: {
            try {
                string nome;
                cout << "Nome da assinatura a remover: ";
                getline(cin, nome);
                
                usuario_.removerAssinatura(nome);
                usuario_.salvarEmArquivo("userData.txt");
                cout << "Assinatura '" << nome << "' removida com sucesso!\n";

            } catch (const AssinaturaNaoEncontradaException& e) {
                cerr << "ERRO: A assinatura '" << e.nome << "' não foi encontrada.\n";
            } catch (const ErroAoAbrirArquivoException& e) {
                cerr << "ERRO: Não foi possível salvar as alterações no arquivo '" << e.nomeArquivo << "'.\n";
            }
            break;
        }
        case 3: {
            try {
                string nomeAntigo, nomeNovo;
                double valorNovo;
                int diaNovo;

                cout << "Nome da assinatura a editar: ";
                getline(cin, nomeAntigo);

                cout << "Novo nome: ";
                getline(cin, nomeNovo);

                cout << "Novo valor (R$): ";
                cin >> valorNovo;
                 if (cin.fail()) throw runtime_error("Entrada de valor inválida.");

                cout << "Novo dia de renovação: ";
                cin >> diaNovo;
                if (cin.fail()) throw runtime_error("Entrada de dia inválida.");

                Assinatura nova(nomeNovo, valorNovo, diaNovo);
                usuario_.editarAssinatura(nomeAntigo, nova);
                usuario_.salvarEmArquivo("userData.txt");
                cout << "Assinatura '" << nomeAntigo << "' atualizada com sucesso!\n";

            } catch (const runtime_error& e) {
                cerr << "ERRO: " << e.what() << " Por favor, insira um número.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } catch (const AssinaturaNaoEncontradaException& e) {
                cerr << "ERRO: A assinatura original '" << e.nome << "' não foi encontrada.\n";
            } catch (const NomeAssinaturaInvalidoException& e) {
                cerr << "ERRO: O novo nome da assinatura não pode ser vazio.\n";
            } catch (const ValorAssinaturaInvalidoException& e) {
                cerr << "ERRO: Novo valor inválido (R$ " << e.valor << ").\n";
            } catch (const DiaRenovacaoInvalidoException& e) {
                cerr << "ERRO: Novo dia de renovação inválido (" << e.dia << ").\n";
            } catch (const ErroAoAbrirArquivoException& e) {
                cerr << "ERRO: Não foi possível salvar as alterações no arquivo '" << e.nomeArquivo << "'.\n";
            }
            break;
        }
        case 4: {
            try {
                usuario_.listarAssinaturas();
            } catch (const ListaDeAssinaturasVaziaException& e) {
                cout << "Nenhuma assinatura cadastrada para listar.\n";
            }
            break;
        }
        case 5: {
            cout << "Gasto mensal total: R$ " << usuario_.calcularGastoMensal() << "\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
    }
}
