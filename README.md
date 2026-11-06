# 📦 Sistema Loja de Produtos

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Tecnologias Utilizadas](#️-tecnologias-utilizadas)
- [Pré-requisitos](#-pré-requisitos)
- [Como Usar](#-como-usar)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Competências Desenvolvidas](#-competências-desenvolvidas)
- [Melhorias Futuras](#-melhorias-futuras)
- [Autor](#-autor)

## 📖 Sobre o Projeto

O Sistema Loja de Produtos é uma aplicação de linha de comando que permite o cadastro, listagem, busca, atualização e remoção de produtos. Os dados são persistidos em um arquivo CSV (`produtos.csv`), garantindo que as informações permaneçam disponíveis entre execuções do programa.

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

| Tecnologia       | Versão | Descrição                                   |
|------------------|--------|---------------------------------------------|
| C (ISO C99)      | —      | Linguagem de programação principal          |
| GCC / Clang      | —      | Compilador recomendado                      |
| File I/O         | —      | Manipulação de arquivos texto (CSV)         |
| Standard Library | —      | `stdio.h`, `stdlib.h`, `string.h`, `locale.h` |

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

O sistema apresentará um menu interativo. Digite o número da opção desejada e pressione Enter.

## 📁 Estrutura do Projeto

```
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
- **Fluxo de controle** — Loops, condicionais e switch-case
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

Este projeto está sob a licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.
