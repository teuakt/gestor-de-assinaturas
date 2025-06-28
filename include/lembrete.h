#ifndef LEMBRETE_H
#define LEMBRETE_H

#include "usuario.h"

/**
 * Classe responsável por verificar e alertar sobre renovações de assinaturas.
 * Ela age sobre os dados de um objeto Usuario para encontrar assinaturas
 * que estão perto de vencer.
 */
class Lembrete {
public:
    // Construtor que recebe uma referência ao usuário que será verificado.
    Lembrete(Usuario& usuario);

    // Percorre as assinaturas do usuário e imprime um aviso para aquelas
    // que serão renovadas dentro do período de dias informado.
    // Lança uma exceção se o usuário não tiver nenhuma assinatura.
    void verificarRenovacoes(int diasAntecedencia) const;

private:
    // Guarda uma referência ao usuário para poder acessar suas assinaturas.
    Usuario& usuario_;
};

#endif // LEMBRETE_H