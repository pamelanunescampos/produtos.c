# 📊 Resumo Técnico do Projeto

## Visão Geral

O projeto implementa um **sistema CRUD completo em C** para gerenciamento de produtos de uma loja, utilizando **arquivo CSV como banco de dados**. A aplicação opera via terminal com menu interativo e valida todas as entradas do usuário antes de persistir os dados.

## ✅ Pontos Fortes

### 1. Validação Robusta de Entrada

- Campos de texto rejeitam strings vazias e o caractere `;` (que quebraria o CSV)
- Preços passam por validação numérica e não aceitam valores negativos
- Conversão automática de vírgula para ponto (padrão brasileiro para decimal)

### 2. Manipulação Segura de Arquivos

- Verificação de `NULL` após `fopen()` em todas as operações
- Uso de arquivo temporário (`temp.csv`) para atualizações e remoções, prevenindo perda de dados
- `rewind()` para reutilização do arquivo após contagem de registros

### 3. Código Modular e Legível

- Funções bem nomeadas com responsabilidades únicas (`lerTexto`, `lerPreco`, `lerLinhaCSV`)
- Protótipos organizados no início do arquivo
- Separação clara entre funções auxiliares, de validação e CRUD

### 4. Cross-Platform

- Detecção automática do sistema operacional para comando de limpar tela (`cls` vs `clear`)
- Uso de `setlocale(LC_ALL, "")` para suporte a caracteres locais

### 5. UX em Terminal

- Menu claro e intuitivo
- Pausa após operações para evitar retorno imediato ao menu
- Confirmação antes de remoções (prevenção de exclusão acidental)

## 🎓 Competências Adquiridas

| Competência | Nível | Evidência no Código |
|---|---|---|
| **Manipulação de arquivos** | Intermediário | Leitura/escrita em CSV, arquivo temporário, `remove()` e `rename()` |
| **Estruturas de dados** | Intermediário | `struct Produto` com campos tipados |
| **Validação de entrada** | Avançado | Loops de validação com `while(1)` e múltiplas verificações |
| **Parsing de strings** | Intermediário | `strtok()`, `strcspn()`, `strchr()`, `sscanf()` |
| **Gerenciamento de memória** | Básico | Uso de buffers fixos (`TAM`, `250`) e `strncpy()` para segurança |
| **Fluxo de controle** | Intermediário | `switch-case`, loops aninhados, flags de controle (`encontrou`, `confirmou`) |
| **Tratamento de erros** | Intermediário | Verificação de `NULL`, `perror()`, mensagens de erro claras |

## 🔧 Desafios Superados

1. **Parsing de CSV manual** — Implementação de `lerLinhaCSV()` usando `strtok()` para dividir campos
2. **Atualização segura** — Uso de arquivo temporário para reescrever o CSV sem corromper dados
3. **Validação de preço** — Conversão de entrada do usuário (texto) para `float` com tratamento de vírgula
4. **Buffer do `scanf()`** — Função `limparBuffer()` para remover `\n` residual do buffer de entrada

## 🚀 Melhorias Futuras (Priorizadas)

### Alta Prioridade

| Melhoria | Impacto | Esforço |
|---|---|---|
| **Busca parcial por nome** | Alto (UX) | Baixo |
| **Divisão em múltiplos arquivos** | Alto (manutenibilidade) | Médio |
| **Makefile** | Médio (automação) | Baixo |
| **Suporte UTF-8 completo** | Alto (internacionalização) | Médio |

### Média Prioridade

- Ordenação de listagens (por nome, preço, categoria)
- Validação de preço com regex ou `strtod()` mais seguro
- Histórico de operações (log de alterações)

### Baixa Prioridade (Longo Prazo)

- Migração para SQLite
- Interface gráfica (ncurses ou GTK)
- API REST para integração com outros sistemas

## 📈 Evolução do Projeto

```text
Fase 1 (Atual) ✅
└── CRUD completo em terminal com CSV

Fase 2 (Próxima)
├── Busca parcial
├── Ordenação
└── Divisão em módulos (.h/.c)

Fase 3 (Futuro)
├── SQLite
├── Makefile + testes unitários
└── Documentação técnica (Doxygen)
```

## 💡 Lições Aprendidas

1. **Validação é crucial** — Entradas do usuário são a principal fonte de bugs
2. **Arquivos temporários previnem perda de dados** — Sempre usar abordagem copy-modify-replace
3. **Código modular facilita depuração** — Funções pequenas e testáveis isolam problemas
4. **UX importa mesmo em terminal** — Pausas, confirmações e mensagens claras melhoram a experiência
