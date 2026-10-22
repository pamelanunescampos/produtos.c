# 📦 Sistema Loja de Produtos

Um sistema de gerenciamento de produtos desenvolvido em **C** com operações CRUD completas, persistência de dados em arquivo CSV e interface via terminal.

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [Pré-requisitos](#-pré-requisitos)
- [Como Usar](#-como-usar)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Competências Desenvolvidas](#-competências-desenvolvidas)
- [Melhorias Futuras](#-melhorias-futuras)
- [Autor](#-autor)

## 📖 Sobre o Projeto

O **Sistema Loja de Produtos** é uma aplicação de linha de comando que permite o cadastro, listagem, busca, atualização e remoção de produtos. Os dados são persistidos em um arquivo CSV (`produtos.csv`), garantindo que as informações permaneçam disponíveis entre execuções do programa.

Este projeto foi desenvolvido como exercício acadêmico para consolidar conceitos fundamentais de programação em C, incluindo manipulação de arquivos, estruturas de dados, validação de entrada e operações CRUD.

## ✨ Funcionalidades

- **Cadastrar produto** — Adiciona novos produtos com nome, categoria e preço
- **Listar produtos** — Exibe todos os produtos cadastrados com formatação
- **Buscar por nome** — Localiza um produto específico pelo nome exato
- **Buscar por categoria** — Filtra produtos por categoria
- **Buscar por faixa de preços** — Encontra produtos dentro de um intervalo de valores
- **Atualizar produto** — Modifica nome, categoria e preço de um produto existente
- **Remover produto** — Exclui produtos com confirmação do usuário
- **Validação de entrada** — Previne dados inválidos (campos vazios, caracteres proibidos, preços negativos)
- **Persistência em CSV** — Armazenamento leve e portátil dos dados

## 🛠️ Tecnologias Utilizadas

| Tecnologia | Versão | Descrição |
|---|---|---|
| C (ISO C99) | — | Linguagem de programação principal |
| GCC / Clang | — | Compilador recomendado |
| File I/O | — | Manipulação de arquivos texto (CSV) |
| Standard Library | — | `stdio.h`, `stdlib.h`, `string.h`, `locale.h` |

## 📦 Pré-requisitos

- Compilador C instalado (GCC, Clang ou MSVC)
- Terminal ou prompt de comando

### Verificando o compilador

```bash
gcc --version
```

## 🚀 Como Usar

### 1. Clone ou baixe o projeto

```bash
git clone https://github.com/seu-usuario/sistema-loja-produtos.git
cd sistema-loja-produtos
```

### 2. Compile o código

```bash
gcc -o sistema loja.c -std=c99
```

### 3. Execute o programa

```bash
./sistema        # Linux/macOS
sistema.exe      # Windows
```

### 4. Interaja com o menu

O sistema apresentará um menu interativo. Digite o número da opção desejada e pressione **Enter**.

## 📁 Estrutura do Projeto

```text
sistema-loja-produtos/
├── loja.c              # Código-fonte principal
├── produtos.csv        # Arquivo de dados (gerado automaticamente)
├── README.md           # Documentação do projeto
└── .gitignore          # Arquivos ignorados pelo Git
```

## 🎯 Competências Desenvolvidas

### Técnicas

- **Manipulação de arquivos** — Leitura, escrita e atualização de arquivos CSV
- **Estruturas de dados** — Uso de `struct` para modelagem de entidades
- **Validação de entrada** — Tratamento robusto de dados do usuário
- **Gerenciamento de memória** — Uso consciente de buffers e strings
- **Fluxo de controle** — Loops, condicionais e `switch-case`
- **Funções modulares** — Código organizado em funções com responsabilidades únicas

### Conceitos de Engenharia de Software

- **Separação de responsabilidades** — Funções auxiliares, de validação e CRUD separadas
- **Tratamento de erros** — Verificação de `NULL` em arquivos e validação de entrada
- **Persistência de dados** — Implementação de storage simples sem banco de dados
- **UX em terminal** — Menu claro, pausas e feedback ao usuário

## 🔮 Melhorias Futuras

### Funcionais

- **Busca parcial por nome** — Permitir busca por substring (ex: "note" encontra "Notebook")
- **Ordenação** — Listar produtos por nome, categoria ou preço (crescente/decrescente)
- **Relatórios** — Exportar listagens formatadas para PDF ou TXT
- **Histórico de operações** — Log de alterações realizadas no sistema

### Técnicas

- **Tratamento de acentos** — Melhor suporte a UTF-8 para evitar problemas de encoding
- **Validação de preço mais rigorosa** — Regex ou parsing mais seguro que `sscanf`
- **Separação em múltiplos arquivos** — Dividir em `main.c`, `crud.c`, `utils.c`, `produto.h`
- **Makefile** — Automatizar compilação e limpeza do projeto
- **Testes unitários** — Implementar testes com `assert.h` ou framework como CMockery

### Arquiteturais

- **Banco de dados** — Migrar para SQLite para consultas mais eficientes
- **Interface gráfica** — Criar versão com ncurses (terminal) ou GTK/Qt (GUI)
- **API REST** — Expor operações via HTTP usando libmicrohttpd ou similar

## 📄 Licença

Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes.

## 👤 Autor

**Vanessa Batista de Freitas**
Estudante de Ciência da Computação \| Mogi das Cruzes, SP 🇧🇷

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
