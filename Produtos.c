#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define ARQUIVO "produtos.csv"
#define TEMP "temp.csv"
#define TAM 100

#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

typedef struct {
    char nome[TAM];
    char categoria[TAM];
    float preco;
} Produto;

// Protótipo das funções

// Funções de verificação
void lerTexto(char *rotulo, char *destino);
float lerPreco(char *rotulo);
int lerLinhaCSV(char *linha, Produto *produto);
int verificarProdutos(FILE *f, char *linha, Produto *produto);

// Funções auxiliares
void menu(void);
void limparBuffer(void);
void pausar(void);
void mostrarProduto(Produto produto);
int confirmarRemocao(void);

// Funções CRUD
void cadastrarProduto(Produto *produto);
void listarProduto(Produto *produto);
void buscarPorNome(Produto *produto);
void buscarPorCategoria(Produto *produto);
void buscarPorFaixa(Produto *produto);
void atualizarProduto(Produto *produto);
void removerProduto(Produto *produto);

// Função principal
int main() {
	setlocale(LC_ALL, "");
    int opcao;
    Produto produto;

    do {
        system(LIMPAR_TELA);
		menu();
        if (scanf("%d", &opcao) != 1) {
    		printf("Entrada invalida!\n");
    		limparBuffer();
    		continue;
		}
        limparBuffer();

        printf("\n");

        switch (opcao) {
            case 1: 
				cadastrarProduto(&produto);
				pausar();
				break;
				
            case 2: 
				listarProduto(&produto);
				pausar();
				break;
				
            case 3: 
				buscarPorNome(&produto);
				pausar();
				break;
				
            case 4: 
				buscarPorCategoria(&produto); 
				pausar();
				break;
				
            case 5: 
				buscarPorFaixa(&produto);     
				pausar();
				break;
				
            case 6: 
				atualizarProduto(&produto);            
				pausar();
				break;
				
            case 7:
				removerProduto(&produto);           
				pausar();
				break;
				
            case 0: 
				printf("Encerrando o sistema...\n"); 
				break;
				
            default:
                printf("Erro: opção inválida! Tente novamente.\n");
                pausar();
        }
    } while (opcao != 0);

    return 0;
}

// Função de menu
void menu(){
		printf("------------------------------------\n");
        printf("      SISTEMA LOJA DE PRODUTOS      \n");
        printf("------------------------------------\n");
        printf("1 - Cadastrar produto               \n");
        printf("2 - Listar produtos                 \n");
        printf("3 - Buscar por nome                 \n");
        printf("4 - Buscar por categoria            \n");
        printf("5 - Buscar por faixa de preços      \n");
        printf("6 - Atualizar produto               \n");
        printf("7 - Remover produto                 \n");
        printf("0 - Sair\n");
        printf("------------------------------------\n");
        printf("Escolha uma das opções: ");
}

// Limpa o '\n' que o scanf deixa no input
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para pausar, já que o System limpa a tela e volta pro menu
void pausar(){
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
}

// Função de verificação de um texto não aceita ';' porque daria erro no csv
void lerTexto(char *rotulo, char *destino) {

    while (1) {

        printf("%s", rotulo);
        
        fgets(destino, TAM, stdin);
        destino[strcspn(destino, "\n")] = '\0';

        if (strlen(destino) == 0) {
            printf("Erro: o campo não pode ficar vazio.\n");
            continue;
        }

        if (strchr(destino, ';') != NULL) {
            printf("Erro: não use o caractere ';'.\n");
            continue;
        }

        return;
    }
}

// Função de verificação de um preço e só aceita número válido e não negativo
float lerPreco(char *rotulo) {
    float valor;
    char entrada[50];
    int i;

    while (1) {

        printf("%s", rotulo);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        // Troca a vírgula por ponto
        for ( i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] == ',') {
                entrada[i] = '.';
            }
        }

        // Converte texto para número
        if (sscanf(entrada, "%f", &valor) != 1) {
            printf("Erro: digite um preço válido.\n");
        }
        else if (valor < 0) {
            printf("Erro: o preço não pode ser negativo.\n");
        }
        else {
            return valor;
        }
    }
}

// Função para manipular o arquivo produtos e temp(temporario)
// Transforma uma linha "nome;categoria;preco" em um Produto usando strtok.
// Devolve 1 se deu certo e 0 se a linha estiver incompleta
int lerLinhaCSV(char *linha, Produto *produto) {
    char *nome = strtok(linha, ";");        // tudo antes do primeiro ;
    char *categoria = strtok(NULL, ";");    // NULL = continua na mesma string
    char *preco = strtok(NULL, ";\n");

    if (nome == NULL || categoria == NULL || preco == NULL) {
        return 0;
    }

    strncpy(produto->nome, nome, TAM - 1);
    produto->nome[TAM - 1] = '\0';
    strncpy(produto->categoria, categoria, TAM - 1);
    produto->categoria[TAM - 1] = '\0';
    produto->preco = (float) atof(preco);         // texto vira numero numero
    return 1;
}

// Função para confirmar se o usuario quer remover o produto
int confirmarRemocao() {
    char resposta;

    printf("\nTem certeza que deseja remover este produto? (S/N): ");
    scanf(" %c", &resposta);
    limparBuffer();

    if (resposta == 'S' || resposta == 's') {
        return 1;
    }

    return 0;
}

// Função para verificar se tem produtos
int verificarProdutos(FILE *f, char *linha, Produto *produto) {

    int total = 0;

    while (fgets(linha, 250, f) != NULL) {
        if (lerLinhaCSV(linha, produto)) {
            total++;
        }
    }

    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return 0;
    }

    rewind(f);

    return 1;
}

// Função de cadastrar produtos
void cadastrarProduto(Produto *produto) {
	
    printf("----- CADASTRAR PRODUTO -----\n");
    lerTexto("Nome do produto: ", produto->nome);
    lerTexto("Categoria: ", produto->categoria);
    produto->preco = lerPreco("Preço: ");

    // "a" (append) acrescenta no final sem apagar os produtos existentes
    FILE *f = fopen(ARQUIVO, "a");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo!");
        return;
    }

    fprintf(f, "%s;%s;%.2f\n", produto->nome, produto->categoria, produto->preco);
    fclose(f);
    printf("\nProduto cadastrado com sucesso!\n");
}

// Função de mostrar os produtos
void mostrarProduto(Produto produto) {
	printf("===============================\n");
    printf("Nome do Produto: %s\n", produto.nome);
    printf("\n");
    printf("Categoria: %s\n", produto.categoria);
    printf("\n");
	printf("Preço: R$ %.2f\n", produto.preco);
	printf("===============================\n");
}

// Função de listar os produto
void listarProduto(Produto *produto) {
    
    char linha[250];
    int total = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("----- PRODUTOS CADASTRADOS -----\n");

    // fgets() le uma linha do arquivo por vez, ate chegar ao fim (NULL)
    while (fgets(linha, 250, f) != NULL) {
        if (lerLinhaCSV(linha, produto)) {
            total++;
            printf("\nProduto %d\n", total);
            mostrarProduto(*produto);
        }
    }
    fclose(f);

    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
    else {
        printf("\nTotal: %d produto(s).\n", total);
    }
}

// Função de buscar produto pelo nome
void buscarPorNome(Produto *produto) {
    
    char linha[250];
    char nomeBusca[TAM];
    int encontrou = 0;
    int total = 0;
    
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }
    
    if (!verificarProdutos(f, linha, produto)) {
    	fclose(f);
    	return;
	}

    printf("----- BUSCAR POR NOME -----\n");
    lerTexto("Digite o nome do produto que deseja buscar: ", nomeBusca);

    while (fgets(linha, 250, f) != NULL && encontrou == 0) {
        if (lerLinhaCSV(linha, produto) && strcmp(produto->nome, nomeBusca) == 0) {
            printf("\nProduto encontrado!\n");
            mostrarProduto(*produto);
            encontrou = 1;
        }
    }
    fclose(f);

    if (encontrou == 0) {
        printf("Produto não encontrado.\n");
    }
    
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
}

// Função de buscar produto pela categoria
void buscarPorCategoria(Produto *produto) {
    
    char linha[250];
    char categoriaBusca[TAM];
    int encontrou = 0;
    int total = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }
    
    if (!verificarProdutos(f, linha, produto)) {
    	fclose(f);
    	return;
	}
    
    printf("----- BUSCAR POR CATEGORIA -----\n");
    lerTexto("Digite a categoria desejada: ", categoriaBusca);

    while (fgets(linha, 250, f) != NULL) {
        if (lerLinhaCSV(linha, produto) && strcmp(produto->categoria, categoriaBusca) == 0) {
            if (encontrou == 0) {
                printf("\nProdutos encontrados:\n");
            }
            printf("%s - R$ %.2f\n", produto->nome, produto->preco);
            encontrou = 1;
        }
    }
    fclose(f);

    if (encontrou == 0) {
        printf("Nenhum produto encontrado na categoria \"%s\".\n", categoriaBusca);
    }
}

// Função de buscar produto pela faixa de preçon entre o minimo e o máximo
void buscarPorFaixa(Produto *produto) {

    char linha[250];
    float minimo, maximo;
    int encontrou = 0;
    int total = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }
    
    if (!verificarProdutos(f, linha, produto)) {
    	fclose(f);
    	return;
	}
    
    printf("----- BUSCAR POR FAIXA DE PRECOS -----\n");
    minimo = lerPreco("Preco minimo: ");   // ja recusa valores negativos
    maximo = lerPreco("Preco maximo: ");

    if (minimo > maximo) {
        printf("Erro: o preço minimo não pode ser maior que o preço máximo.\n");
        return;
    }

    while (fgets(linha, 250, f) != NULL) {
        
        if (lerLinhaCSV(linha, produto) && produto->preco >= minimo && produto->preco <= maximo) {
            if (encontrou == 0) {
                printf("\nProdutos encontrados na faixa:\n");
            }
            printf("%s - R$ %.2f\n", produto->nome, produto->preco);
            encontrou = 1;
        }
    }
    fclose(f);

    if (encontrou == 0) {
        printf("Nenhum produto encontrado na faixa informada.\n");
    }
}

// Função de atualizar os dados de um produto
void atualizarProduto(Produto *produto) {
    Produto novo;
    char linha[250], copia[250];
    char nomeBusca[TAM];
    int encontrou = 0;
    int total = 0;

	FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }
	
	FILE *temp = fopen(TEMP, "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }
	    
    if (!verificarProdutos(f, linha, produto)) {
    	fclose(f);
    	return;
	}
	
    printf("----- ATUALIZAR PRODUTO -----\n");
    lerTexto("Digite o produto que deseja atualizar: ", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {
        strcpy(copia, linha);

        if (encontrou == 0 && lerLinhaCSV(copia, produto) && strcmp(produto->nome, nomeBusca) == 0) {
            encontrou = 1;

            printf("\nProduto atual:\n");
            mostrarProduto(*produto);
            printf("\n");

            lerTexto("Novo nome: ", novo.nome);
            lerTexto("Nova categoria: ", novo.categoria);
            novo.preco = lerPreco("Novo preço: ");

            // grava os dados novos no lugar da linha antiga
            fprintf(temp, "%s;%s;%.2f\n", novo.nome, novo.categoria, novo.preco);
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    if (encontrou == 1) {
        remove(ARQUIVO);
        rename(TEMP, ARQUIVO);
        printf("\nProduto atualizado com sucesso!\n");
    }
    else {
        remove(TEMP);
        printf("Produto não encontrado.\n");
    }
}

// Função de remover produto
void removerProduto(Produto *produto) {

    char linha[250], copia[250];
    char nomeBusca[TAM];
    int encontrou = 0;
    int confirmou = 0;
    int total = 0;

	FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Produto não encontrado.\n");
        return;
    }
    
	FILE *temp = fopen(TEMP, "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }
    
	if (!verificarProdutos(f, linha, produto)) {
    	fclose(f);
    	return;
	}
    
	printf("----- REMOVER PRODUTO -----\n");
    lerTexto("Digite o nome do produto que deseja remover: ", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {

        strcpy(copia, linha);

        if (encontrou == 0 &&
            lerLinhaCSV(copia, produto) &&
            strcmp(produto->nome, nomeBusca) == 0) {

            encontrou = 1;

            printf("\nProduto encontrado:\n");
            mostrarProduto(*produto);

            confirmou = confirmarRemocao();

            if (!confirmou) {
                fprintf(temp, "%s", linha);
            }

        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    if (encontrou == 1 && confirmou == 1) {

        remove(ARQUIVO);
        rename(TEMP, ARQUIVO);

        printf("\nProduto removido com sucesso!\n");
    }
    else {
		if (encontrou == 1 && confirmou == 0) {

        remove(TEMP);

        printf("\nRemoção cancelada.\n");
    	}
    	
    	else {

        remove(TEMP);

        printf("\nProduto não encontrado.\n");
    	}
    }    
}

