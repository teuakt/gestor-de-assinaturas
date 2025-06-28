# Gestor de Assinaturas de Streaming

## 1. Apresentação do Problema

Com a popularização dos serviços de streaming, tornou-se cada vez mais comum que usuários acumulem múltiplas assinaturas simultâneas. Isso pode dificultar o controle financeiro e gerar esquecimentos na renovação dos serviços. Este projeto busca resolver esse problema ao oferecer uma ferramenta simples, via linha de comando, para o gerenciamento centralizado de assinaturas.

## 2. Visão Geral da Solução

### Este sistema, desenvolvido em C++, permite:

- Cadastrar, editar e remover assinaturas de forma persistente (salvas em arquivo).

- Visualizar lembretes de renovação na inicialização do programa.

- Gerar relatórios de gastos mensais.

- Lidar com erros de forma robusta, informando o usuário sobre dados inválidos, arquivos corrompidos ou operações mal-sucedidas.

### Arquitetura do Sistema
A aplicação é modular e baseada em orientação a objetos, utilizando as seguintes classes principais:

- **Assinatura**: Classe de modelo que representa uma assinatura individual, contendo seus dados (nome, valor, dia de renovação).

- **Usuario**: Classe de negócio que gerencia a coleção de assinaturas, contendo toda a lógica de adicionar, remover, editar e calcular gastos.

- **Gestor**: Classe controladora, responsável por toda a interação com o usuário, como exibir o menu e processar os comandos.

- **Lembrete**: Classe de serviço que verifica e informa sobre assinaturas com renovação próxima.

> **Veja mais detalhes das funcionalidades no arquivo docs/UserStories.md.**

### Arquitetura do Sistema

O projeto foi refatorado para incorporar práticas modernas de desenvolvimento em C++, incluindo:

 - Tratamento de Exceções: Utilização de um sistema de exceções customizadas para garantir a robustez e a integrabilidade dos dados, tratando desde entradas inválidas até erros de formatação de arquivos.

 - Testes de Unidade: Implementação de uma suíte de testes completa com o framework Doctest para validar o comportamento de cada classe, cobrindo tanto os cenários de sucesso quanto os de erro.

## 3. Estrutura do Projeto
```
gestor-de-assinaturas/
├── include/          # Arquivos de cabeçalho (.h)
├── src/              # Implementações das classes (.cpp)
├── tests/            # Arquivos de teste de unidade (_test.cpp)
├── build/            # Arquivos objeto e executáveis gerados pelo Makefile
├── docs/             # Documentação auxiliar (User Stories, CRC)
├── external/         # Bibliotecas de terceiros (Doctest)
├── main.cpp          # Função principal que inicializa o programa
├── Makefile          # Script de build, execução e teste
├── userData.txt      # Arquivo de dados gerado pela aplicação
└── README.md         # Este documento
```

## 4. Instruções de Instalação
### Pré-requisitos:
- Compilador C++ com suporte ao padrão C++17 (ex: g++)
- Utilitário make

### Passo a passo

1. **Clone o repositório:**
```bash
git clone https://github.com/teuakt/gestor-de-assinaturas
```
2. **Acesse o diretório do projeto:**
```bash
cd gestor-de-assinaturas
```
3. **Compile o projeto utilizando o Makefile:**
```bash
make
```
4. **Execute o programa:**
```bash
make run
```
5. **(Opcional) Execute a suíte de testes:**
```bash
make test
```
6. **(Opcional) Limpe os arquivos de compilação:**
```bash
make clean
```

## 5. Instruções de Uso
- Ao executar o programa, um menu interativo será exibido.
- As opções permitem adicionar, remover, editar e listar suas assinaturas. Os dados são salvos automaticamente no arquivo userData.txt após cada alteração bem-sucedida.
- O programa verifica automaticamente por lembretes de renovação ao ser iniciado.


## 6. Principais Dificuldades Encontradas
Durante o desenvolvimento, alguns desafios foram cruciais para o amadurecimento do projeto:

- Implementação de um Sistema de Erros Robusto: A transição de um modelo simples com retornos de true/false para um sistema de tratamento de exceções foi o maior desafio. Foi necessário definir erros customizados, refatorar todas as classes para lançar (throw) exceções em cenários específicos.

- Testes de Unidade em Código com Interação Externa: Testar classes que dependem de fatores externos, como a data do sistema (Lembrete) ou a entrada e saída do console (Gestor), apresentou uma dificuldade significativa.

- Separação de Responsabilidades (Design): No início, havia uma indefinição sobre qual classe deveria gerenciar a lista de assinaturas (Gestor ou Usuario). A decisão de centralizar toda a lógica de negócio em Usuario e designar Gestor como um mero controlador de interface foi um passo importante para um design mais limpo.

## Como contribuir

1. Crie uma branch para suas alterações:
```bash
git checkout -b minha-contribuicao
```
2. Faça commits claros e objetivos.
3. Envie suas alterações para o repositório remoto:
```bash
git push origin minha-contribuicao
```
4. Abra um Pull Request com a descrição das mudanças propostas.
