#ifndef ERROS_H
#define ERROS_H

#include <string>

struct ErroAssinatura {
    std::string mensagem;

    ErroAssinatura(const std::string& msg) : mensagem(msg) {}
};

#endif
