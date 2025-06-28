// erros.h
#ifndef ERROS_H
#define ERROS_H

#include <string>

struct AssinaturaJaExisteException {
    const std::string nome;
};

struct AssinaturaNaoEncontradaException {
    const std::string nome;
};

struct ListaDeAssinaturasVaziaException {};

struct ErroAoAbrirArquivoException {
    const std::string nomeArquivo;
};

struct ErroDeFormatoDeArquivoException {
    const int linha;
    const std::string conteudo;
};

struct NomeAssinaturaInvalidoException {};

struct ValorAssinaturaInvalidoException {
    const double valor;
};

struct DiaRenovacaoInvalidoException {
    const int dia;
};

#endif // ERROS_H