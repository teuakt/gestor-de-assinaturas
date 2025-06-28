#ifndef USUARIO_H
#define USUARIO_H

#include "assinatura.h"
#include <vector>
#include <string>

/**
 * Classe principal que gerencia a coleção de assinaturas do usuário.
 * Contém toda a lógica para adicionar, remover, editar e salvar os dados.
 */
class Usuario {
private:
    // Vetor que armazena todos os objetos de Assinatura do usuário.
    std::vector<Assinatura> assinaturas_;

public:
    // Adiciona uma nova assinatura na lista.
    // Lança uma exceção se já existir uma assinatura com o mesmo nome.
    void adicionarAssinatura(const Assinatura& assinatura);

    // Remove uma assinatura da lista com base no nome.
    // Lança uma exceção se a assinatura não for encontrada.
    void removerAssinatura(const std::string& nome);

    void editarAssinatura(const std::string& nome, const Assinatura& novaAssinatura);

    // Imprime no console a lista de todas as assinaturas cadastradas.
    void listarAssinaturas() const;

    // Retorna a soma dos valores de todas as assinaturas.
    double calcularGastoMensal() const;

    // Retorna uma referência constante ao vetor de assinaturas.
    // Útil para outras classes que precisam ler os dados, como Lembrete.
    const std::vector<Assinatura>& getAssinaturas() const;

    // Salva a lista atual de assinaturas em um arquivo de texto.
    void salvarEmArquivo(const std::string& nomeArquivo) const;
    
    // Carrega as assinaturas de um arquivo, substituindo as que estão na memória.
    void carregarDeArquivo(const std::string& nomeArquivo);
};

#endif // USUARIO_H