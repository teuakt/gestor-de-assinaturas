#ifndef LEMBRETE_H
#define LEMBRETE_H

#include "usuario.h"

class Lembrete {
public:

    Lembrete(Usuario& usuario);

    void verificarRenovacoes(int diasAntecedencia) const;

private:
    Usuario& usuario_;
};

#endif
