# Relatório técnico das decisões tomadas no código

## 1. Visão geral do projeto

O código implementa um sistema de gerenciamento de produtos em linguagem C, com persistência dos dados em um arquivo CSV chamado `produtos.csv`.

A aplicação permite realizar as principais operações de um sistema CRUD:

- Cadastrar produtos.
- Listar produtos.
- Buscar produtos por nome.
- Buscar produtos por categoria.
- Buscar produtos por faixa de preço.
- Atualizar produtos.
- Remover produtos.
- Encerrar o sistema.

A estrutura geral foi organizada de maneira modular, separando a função principal, o menu, as validações, a leitura do arquivo e as operações de manipulação dos produtos. O programa utiliza uma estrutura `Produto`, funções auxiliares e arquivos temporários para atualizar ou excluir registros. Essas decisões estão presentes no código analisado.

## 2. Decisões de modelagem

### Uso de uma estrutura `struct`

Foi criada a estrutura:

```c
typedef struct {
    char nome[TAM];
    char categoria[TAM];
    float preco;
} Produto;
```

Essa decisão permite representar um produto como uma única entidade lógica, agrupando seus atributos:

- `nome`: identifica o produto.
- `categoria`: classifica o produto.
- `preco`: armazena o valor do produto.

Em vez de trabalhar com variáveis independentes, a estrutura facilita a passagem dos dados entre funções e torna o código mais organizado.

Por exemplo, a função `mostrarProduto` recebe um objeto do tipo `Produto`, enquanto as funções de cadastro, atualização e remoção recebem um ponteiro para permitir a alteração dos dados.

### Definição de constantes

O código utiliza constantes simbólicas:

```c
#define ARQUIVO "produtos.csv"
#define TEMP "temp.csv"
#define TAM 100
```

Essa escolha evita a repetição de valores fixos ao longo do programa.

- `ARQUIVO` define o arquivo principal de armazenamento.
- `TEMP` define o arquivo utilizado durante atualizações e remoções.
- `TAM` define o tamanho máximo dos campos de texto.

Caso seja necessário alterar o tamanho máximo dos textos ou o nome dos arquivos, basta modificar as definições no início do programa.

### Compatibilidade entre sistemas operacionais

Foi utilizada uma diretiva condicional:

```c
#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif
```

A decisão permite que o comando usado para limpar a tela seja escolhido de acordo com o sistema operacional:

- `cls` para Windows.
- `clear` para Linux e outros sistemas semelhantes ao Unix.

Isso demonstra uma preocupação com a portabilidade do programa.

## 3. Decisões relacionadas à entrada de dados

### Separação das funções de leitura

O código criou funções específicas para diferentes tipos de entrada:

```c
void lerTexto(char *rotulo, char *destino);
float lerPreco(char *rotulo);
```

Essa decisão evita repetir as mesmas validações em várias partes do programa.

A função `lerTexto` é utilizada para ler nomes e categorias, enquanto `lerPreco` concentra as regras específicas para valores monetários.

Essa separação melhora:

- A organização.
- A reutilização.
- A manutenção.
- A legibilidade.
- A consistência das validações.

### Uso de `fgets` para textos

A função `lerTexto` utiliza:

```c
fgets(destino, TAM, stdin);
```

Essa escolha é mais segura do que utilizar `scanf("%s", ...)`, porque permite ler textos com espaços, como:

```text
Notebook Gamer
Bebidas não alcoólicas
```

Além disso, o limite `TAM` reduz o risco de exceder o tamanho do vetor de caracteres.

Depois da leitura, o caractere de quebra de linha é removido:

```c
destino[strcspn(destino, "\n")] = '\0';
```

Essa decisão é necessária porque o `fgets` normalmente armazena o `\n` digitado pelo usuário.

### Validação de campos vazios

O código verifica se o texto informado possui tamanho zero:

```c
if (strlen(destino) == 0) {
    printf("Erro: o campo não pode ficar vazio.\n");
    continue;
}
```

Com isso, o programa impede o cadastro de produtos sem nome ou sem categoria.

A validação é repetida por meio de um laço infinito controlado por `return`. Enquanto a entrada for inválida, o usuário continua sendo solicitado a informar um valor.

### Restrição do caractere `;`

Como os registros são armazenados no formato CSV usando ponto e vírgula como separador, o código rejeita esse caractere nos textos:

```c
if (strchr(destino, ';') != NULL) {
    printf("Erro: não use o caractere ';'.\n");
    continue;
}
```

Essa é uma decisão importante para preservar a estrutura dos registros.

Um produto é gravado assim:

```text
nome;categoria;preco
```

Se o nome contivesse outro ponto e vírgula, o programa poderia interpretar o texto como várias colunas, comprometendo a leitura posterior.

### Tratamento do preço

A função `lerPreco` lê inicialmente o valor como texto:

```c
char entrada[50];
fgets(entrada, sizeof(entrada), stdin);
```

Depois, a vírgula é convertida para ponto:

```c
if (entrada[i] == ',') {
    entrada[i] = '.';
}
```

Essa escolha facilita a entrada no padrão brasileiro, permitindo valores como:

```text
19,90
```

que são convertidos internamente para:

```text
19.90
```

Em seguida, o texto é convertido para `float` utilizando:

```c
sscanf(entrada, "%f", &valor);
```

Também foi implementada a rejeição de preços negativos:

```c
else if (valor < 0) {
    printf("Erro: o preço não pode ser negativo.\n");
}
```

Assim, o sistema garante que o preço seja numérico e não negativo.

## 4. Decisões de controle do fluxo

### Menu baseado em `do...while`

A função `main` utiliza:

```c
do {
    ...
} while (opcao != 0);
```

Essa escolha garante que o menu seja exibido pelo menos uma vez antes da verificação da condição de saída.

O sistema só termina quando o usuário escolhe a opção `0`.

### Uso de `switch`

As opções do menu são processadas com `switch`:

```c
switch (opcao) {
    case 1:
        cadastrarProduto(&produto);
        break;
    ...
    case 0:
        printf("Encerrando o sistema...\n");
        break;
    default:
        printf("Erro: opção inválida! Tente novamente.\n");
}
```

O `switch` é adequado nesse caso porque existe uma quantidade fixa de alternativas numéricas.

Cada opção do menu é associada diretamente a uma função específica, evitando concentrar toda a lógica dentro da `main`.

### Tratamento de opção inválida

A entrada da opção é validada com:

```c
if (scanf("%d", &opcao) != 1) {
    printf("Entrada invalida!\n");
    limparBuffer();
    continue;
}
```

Essa decisão impede que valores não numéricos causem comportamento inesperado.

Além disso, o bloco `default` trata números que não correspondem às opções existentes.

### Limpeza do buffer de entrada

Foi criada a função:

```c
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

Essa função remove caracteres restantes no buffer de entrada, principalmente o `\n` deixado pelo `scanf`.

A decisão é importante porque o código mistura `scanf` e `fgets`. Sem limpar o buffer, o `fgets` poderia capturar imediatamente a quebra de linha restante, fazendo parecer que o usuário forneceu uma entrada vazia.

## 5. Decisões de armazenamento

### Utilização de arquivo CSV

Os produtos são armazenados no arquivo:

```c
#define ARQUIVO "produtos.csv"
```

O formato escolhido é:

```text
nome;categoria;preco
```

Essa decisão oferece uma persistência simples, sem necessidade de banco de dados.

As vantagens dessa abordagem são:

- Fácil implementação.
- Arquivo legível por humanos.
- Facilidade para abrir em editores de texto ou planilhas.
- Baixa complexidade para um projeto acadêmico.

Por outro lado, o formato exige restrições, como a proibição do caractere `;` nos textos.

### Cadastro utilizando modo append

No cadastro, o arquivo é aberto com:

```c
FILE *f = fopen(ARQUIVO, "a");
```

O modo `"a"` significa append, ou seja, os novos registros são adicionados ao final do arquivo sem apagar os dados existentes.

Essa decisão é apropriada para a operação de cadastro, pois cada novo produto deve ser incluído preservando os produtos já armazenados.

O registro é gravado com:

```c
fprintf(f, "%s;%s;%.2f\n",
        produto->nome,
        produto->categoria,
        produto->preco);
```

O preço é salvo com duas casas decimais, o que padroniza o formato do arquivo.

### Leitura sequencial dos registros

As funções de listagem e busca utilizam:

```c
while (fgets(linha, 250, f) != NULL) {
    ...
}
```

Essa decisão faz com que os registros sejam processados um por vez, evitando a necessidade de carregar todo o arquivo na memória.

O fluxo é:

1. Ler uma linha.
2. Converter a linha em um objeto `Produto`.
3. Aplicar a operação necessária.
4. Ler a próxima linha.

Essa abordagem é simples e adequada para arquivos pequenos ou médios.

### Conversão de linha CSV para `Produto`

A função `lerLinhaCSV` utiliza `strtok`:

```c
char *nome = strtok(linha, ";");
char *categoria = strtok(NULL, ";");
char *preco = strtok(NULL, ";\n");
```

A decisão permite dividir a linha com base no ponto e vírgula.

Depois, os textos são copiados para a estrutura com `strncpy`:

```c
strncpy(produto->nome, nome, TAM - 1);
produto->nome[TAM - 1] = '\0';
```

A posição final é explicitamente preenchida com `'\0'` para garantir que a string seja terminada corretamente.

O preço é convertido com:

```c
produto->preco = (float) atof(preco);
```

A função retorna `1` quando a linha possui os três campos esperados e `0` quando está incompleta.

## 6. Decisões nas operações CRUD

### Cadastro

A função `cadastrarProduto` segue esta sequência:

1. Solicita o nome.
2. Solicita a categoria.
3. Solicita o preço.
4. Abre o arquivo em modo append.
5. Grava o registro.
6. Fecha o arquivo.
7. Informa o sucesso da operação.

A abertura do arquivo é validada:

```c
if (f == NULL) {
    perror("Erro ao abrir o arquivo!");
    return;
}
```

Essa decisão evita que o programa tente escrever em um ponteiro de arquivo inválido.

### Listagem

A função `listarProduto` abre o arquivo no modo leitura:

```c
FILE *f = fopen(ARQUIVO, "r");
```

Caso o arquivo não exista, o programa interpreta que não existem produtos cadastrados:

```c
if (f == NULL) {
    printf("Nenhum produto cadastrado.\n");
    return;
}
```

Cada produto válido é exibido por meio da função:

```c
mostrarProduto(*produto);
```

A criação de uma função exclusiva para exibição evita duplicação da formatação.

Ao final, o sistema mostra a quantidade total de produtos encontrados.

### Busca por nome

A busca por nome utiliza:

```c
strcmp(produto->nome, nomeBusca) == 0
```

Isso significa que a comparação precisa ser exatamente igual, incluindo:

- Letras maiúsculas e minúsculas.
- Espaços.
- Acentos.
- Ortografia.

A busca encerra o laço quando encontra o primeiro produto correspondente:

```c
while (fgets(linha, 250, f) != NULL && encontrou == 0)
```

Essa decisão indica que o programa considera o nome como identificador único ou pretende retornar apenas o primeiro resultado.

### Busca por categoria

Diferentemente da busca por nome, a busca por categoria continua até o fim do arquivo.

Isso ocorre porque vários produtos podem pertencer à mesma categoria:

```c
while (fgets(linha, 250, f) != NULL) {
    if (lerLinhaCSV(linha, produto) &&
        strcmp(produto->categoria, categoriaBusca) == 0) {
        ...
    }
}
```

Cada produto correspondente é apresentado resumidamente com nome e preço.

### Busca por faixa de preço

A busca por faixa utiliza dois limites:

```c
minimo = lerPreco("Preco minimo: ");
maximo = lerPreco("Preco maximo: ");
```

Depois, o preço é comparado usando limites inclusivos:

```c
produto->preco >= minimo &&
produto->preco <= maximo
```

Portanto, produtos cujo preço seja exatamente igual ao mínimo ou ao máximo também são encontrados.

O código também valida a coerência da faixa:

```c
if (minimo > maximo) {
    printf("Erro: o preço minimo não pode ser maior que o preço máximo.\n");
    return;
}
```

Essa decisão evita realizar uma busca logicamente inválida.

### Atualização de produto

Como o arquivo CSV não permite alterar diretamente uma linha com facilidade, foi adotada a estratégia de arquivo temporário.

O arquivo original é aberto para leitura:

```c
FILE *f = fopen(ARQUIVO, "r");
```

E um arquivo temporário é criado para escrita:

```c
FILE *temp = fopen(TEMP, "w");
```

Durante a leitura:

- As linhas não correspondentes são copiadas para o arquivo temporário.
- A linha do produto encontrado é substituída pelos novos dados.

Depois, se o produto for encontrado:

```c
remove(ARQUIVO);
rename(TEMP, ARQUIVO);
```

Essa decisão permite simular uma alteração de registro recriando o arquivo completo.

A cópia da linha original para `copia` também é uma decisão técnica importante:

```c
strcpy(copia, linha);
```

Isso ocorre porque `strtok` modifica a string recebida. Ao utilizar uma cópia para interpretar os dados, a linha original permanece disponível para ser gravada no arquivo temporário.

### Remoção de produto

A remoção utiliza a mesma estratégia de arquivo temporário.

A diferença é que, quando o produto correspondente é encontrado, ele só deixa de ser copiado caso o usuário confirme:

```c
confirmou = confirmarRemocao();
```

A confirmação aceita:

```text
S
s
```

Qualquer outro caractere é tratado como negativa.

Se o usuário confirmar, a linha correspondente não é gravada no arquivo temporário. Se cancelar, a linha original é preservada.

Essa decisão reduz o risco de exclusões acidentais e torna a operação destrutiva mais segura.

## 7. Organização e modularização

O código possui protótipos de funções no início:

```c
void lerTexto(char *rotulo, char *destino);
float lerPreco(char *rotulo);
int lerLinhaCSV(char *linha, Produto *produto);
```

Essa escolha permite que a função `main` seja declarada antes das implementações das demais funções.

A divisão das funções foi feita por responsabilidade:

| Grupo | Responsabilidade |
|---|---|
| Funções de verificação | Validar textos, preços e linhas do CSV |
| Funções auxiliares | Menu, buffer, pausa e exibição |
| Funções CRUD | Cadastrar, listar, buscar, atualizar e remover |
| Função principal | Controlar o fluxo geral do programa |

Essa organização segue o princípio de separar responsabilidades. Cada função possui uma tarefa relativamente específica, facilitando a leitura e a manutenção.

## 8. Tratamento de situações especiais

O programa trata diversas situações de erro:

- Entrada não numérica no menu.
- Nome vazio.
- Categoria vazia.
- Uso do delimitador `;`.
- Preço inválido.
- Preço negativo.
- Arquivo inexistente.
- Falha na abertura do arquivo.
- Falha na criação do arquivo temporário.
- Linha CSV incompleta.
- Faixa de preço invertida.
- Produto não encontrado.
- Cancelamento da remoção.

A função `verificarProdutos` foi criada para evitar a repetição da lógica de verificar se o arquivo contém produtos válidos:

```c
int verificarProdutos(FILE *f, char *linha, Produto *produto)
```

Ela percorre o arquivo, conta os registros válidos e reposiciona o cursor com:

```c
rewind(f);
```

Assim, após a verificação, a função de busca ou alteração pode reler o arquivo desde o início.

## 9. Pontos técnicos que precisam de atenção

Apesar de o código apresentar uma boa estrutura geral, existem alguns pontos que podem ser melhorados.

### Variável `total` sem utilização efetiva

Nas funções `buscarPorNome`, `buscarPorCategoria`, `buscarPorFaixa`, `atualizarProduto` e `removerProduto`, há declarações como:

```c
int total = 0;
```

Em algumas delas, essa variável nunca é incrementada ou usada de forma necessária.

Na função `buscarPorNome`, por exemplo, existe:

```c
if (total == 0) {
    printf("Nenhum produto cadastrado.\n");
}
```

Como `total` permanece sempre igual a zero, essa mensagem poderá ser exibida mesmo depois de uma busca concluída. O ideal seria remover essa variável ou utilizá-la corretamente.

### Validação incompleta do preço

O uso de:

```c
sscanf(entrada, "%f", &valor)
```

aceita o início numérico da entrada, mas pode não rejeitar corretamente textos adicionais em algumas situações.

Por exemplo, uma entrada como:

```text
10abc
```

pode ser interpretada parcialmente como `10`.

Uma validação mais rigorosa deveria verificar se toda a entrada corresponde a um número válido.

### Conversão com `atof`

A função:

```c
atof(preco)
```

não informa claramente se ocorreu um erro de conversão.

Uma alternativa mais segura seria utilizar `strtof`, que permite identificar o ponto em que a conversão falhou.

### Limite das linhas do arquivo

O código utiliza:

```c
char linha[250];
```

Esse tamanho é superior ao tamanho individual dos campos, mas não há uma validação explícita para garantir que o registro completo nunca ultrapasse 249 caracteres.

Como o nome e a categoria possuem até 99 caracteres cada, o limite atual tende a ser suficiente para o formato usado, mas uma validação adicional poderia tornar o comportamento mais robusto.

### Falta de verificação de `remove` e `rename`

Nas operações de atualização e remoção, o código executa:

```c
remove(ARQUIVO);
rename(TEMP, ARQUIVO);
```

Entretanto, os retornos dessas funções não são verificados.

Uma falha no sistema de arquivos poderia fazer com que o arquivo não fosse removido ou renomeado corretamente. O ideal seria validar o resultado e informar o usuário em caso de erro.

### Comparação sensível a maiúsculas e minúsculas

As buscas usam `strcmp`, portanto:

```text
Notebook
```

é diferente de:

```text
notebook
```

Essa é uma decisão válida, mas deve ser compreendida como uma limitação da experiência de uso. Uma melhoria seria normalizar as entradas para comparar sem diferenciação entre maiúsculas e minúsculas.

### Uso de `system`

O comando:

```c
system(LIMPAR_TELA);
```

é simples e funciona em muitos ambientes, mas depende do sistema operacional e executa um comando externo.

Para um projeto acadêmico, essa decisão é aceitável. Em aplicações mais robustas, seria preferível evitar `system` ou encapsular esse comportamento de forma mais controlada.

## 10. Avaliação final

O código demonstra decisões coerentes com um projeto introdutório ou intermediário em C:

- Modelagem de dados com `struct`.
- Organização em funções.
- Validação de entradas.
- Uso de ponteiros.
- Manipulação de arquivos.
- Persistência em CSV.
- Implementação completa de operações CRUD.
- Uso de arquivo temporário para atualização e remoção.
- Tratamento de diferentes sistemas operacionais.
- Confirmação antes de excluir dados.

A principal estratégia adotada foi priorizar simplicidade, legibilidade e funcionamento sem utilizar um banco de dados externo. O arquivo CSV atende ao objetivo do projeto, enquanto a divisão em funções deixa o programa mais fácil de compreender e modificar.
