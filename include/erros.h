// erros.h
#ifndef ERROS_H
#define ERROS_H

#include <string>

// ---------------------------------- usuario --------------------------------- //
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
// ---------------------------------- assinatura --------------------------------- //
struct NomeAssinaturaInvalidoException {};

struct ValorAssinaturaInvalidoException {
    const double valor;
};

struct DiaRenovacaoInvalidoException {
    const int dia;
};
// ---------------------------------- assinatura --------------------------------- //
#endif // ERROS_H