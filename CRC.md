# Cartões CRC - Gestor de Assinaturas de Streaming

## Classe: Assinatura
- **Responsabilidades:**
  - Armazenar dados de uma assinatura (nome, valor, data de renovação).
- **Colaborações:**
  - Usada por `Usuario` para compor a lista de assinaturas.

---

## Classe: Usuario
- **Responsabilidades:**
  - Gerenciar lista de assinaturas.
  - Adicionar e remover assinaturas.
  - Listar todas as assinaturas.
  - Gerar relatório de gastos mensais.
- **Colaborações:**
  - Usa `Assinatura` para armazenar dados.
  - Utilizada por `GestorAssinaturas` para realizar operações.

---

## Classe: GestorAssinaturas
- **Responsabilidades:**
  - Controlar a interface de interação com o usuário.
  - Exibir menu e encaminhar comandos.
- **Colaborações:**
  - Usa `Usuario` para executar as ações.

---

## Classe: Lembrete
- **Responsabilidades:**
  - Enviar alertas sobre próximas renovações.
- **Colaborações:**
  - Pode ser usada por `Usuario` ou `GestorAssinaturas` para notificação.
