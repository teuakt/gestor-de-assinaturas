// erros.h
#ifndef ERROS_H
#define ERROS_H

#include <string>

// Lançada ao tentar adicionar uma assinatura que já está na lista.
struct AssinaturaJaExisteException {
    const std::string nome;
};

// Lançada ao tentar remover ou editar uma assinatura que não existe.
struct AssinaturaNaoEncontradaException {
    const std::string nome;
};

// Usada quando uma operação (como listar) é tentada em uma lista vazia.
struct ListaDeAssinaturasVaziaException {};

// --- Erros de Arquivo ---

// Ocorre se o arquivo de dados não puder ser aberto para leitura ou escrita.
struct ErroAoAbrirArquivoException {
    const std::string nomeArquivo;
};

// Lançada quando uma linha no arquivo de dados está mal formatada.
struct ErroDeFormatoDeArquivoException {
    const int linha;
    const std::string conteudo;
};

// --- Erros de Validação de Dados da Assinatura ---

// Lançada pelo construtor de Assinatura se o nome for inválido (ex: vazio).
struct NomeAssinaturaInvalidoException {};

// Lançada se o valor da assinatura for inválido (ex: negativo).
struct ValorAssinaturaInvalidoException {
    const double valor;
};

// Lançada se o dia de renovação estiver fora do intervalo válido (1-31).
struct DiaRenovacaoInvalidoException {
    const int dia;
};

#endif // ERROS_H