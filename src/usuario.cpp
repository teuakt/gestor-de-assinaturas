#include "usuario.h"
#include "erros.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

using namespace std;

void Usuario::adicionarAssinatura(const Assinatura& assinatura) {
    for (const auto& a : assinaturas_) {
        if (a.getNome() == assinatura.getNome()) {
            throw AssinaturaJaExisteException{assinatura.getNome()};
        }
    }
    assinaturas_.push_back(assinatura);
}

void Usuario::removerAssinatura(const string& nome) {
    for (auto it = assinaturas_.begin(); it != assinaturas_.end(); ++it) {
        if (it->getNome() == nome) {
            assinaturas_.erase(it);
            return; 
        }
    }

    throw AssinaturaNaoEncontradaException{nome};
}


void Usuario::editarAssinatura(const string& nome, const Assinatura& novaAssinatura) {
    for (auto& a : assinaturas_) {
        if (a.getNome() == nome) {
            a = novaAssinatura;
            return; 
        }
    }

    throw AssinaturaNaoEncontradaException{nome};
}

void Usuario::listarAssinaturas() const {
    if (assinaturas_.empty()) {
        throw ListaDeAssinaturasVaziaException{};
    }

    cout << "Assinaturas cadastradas:\n";
    for (const auto& a : assinaturas_) {
        a.exibir();
    }
}

double Usuario::calcularGastoMensal() const {
    double total = 0.0;
    for (const auto& a : assinaturas_) {
        total += a.getValor();
    }
    return total;
}

const vector<Assinatura>& Usuario::getAssinaturas() const {
    return assinaturas_;
}

void Usuario::salvarEmArquivo(const string& nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        throw ErroAoAbrirArquivoException{nomeArquivo};
    }

    for (const auto& a : assinaturas_) {
        arquivo << a.getNome() << ";" << a.getValor() << ";" << a.getDiaRenovacao() << "\n";
    }

    arquivo.close();
}

void Usuario::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        throw ErroAoAbrirArquivoException{nomeArquivo};
    }

    assinaturas_.clear();

    string linha;
    int numeroLinha = 0;
    while (getline(arquivo, linha)) {
        numeroLinha++;
        if (linha.empty()) {
            continue;
        }
        stringstream ss(linha);
        string nome, valorStr, diaStr;

        if (getline(ss, nome, ';') && getline(ss, valorStr, ';') && getline(ss, diaStr, ';')) {
            try {
                double valor = stod(valorStr);
                int dia = stoi(diaStr);
                
                Assinatura a(nome, valor, dia);

                assinaturas_.push_back(a); 
            } catch (const std::invalid_argument& e) {
                throw ErroDeFormatoDeArquivoException{numeroLinha, linha};
            } catch (const std::out_of_range& e) {
                throw ErroDeFormatoDeArquivoException{numeroLinha, linha};
            }
        } else {
            throw ErroDeFormatoDeArquivoException{numeroLinha, linha};
        }
    }

    arquivo.close();
}