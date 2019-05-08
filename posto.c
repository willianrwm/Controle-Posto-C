#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//FUNÇÕES ==================================

void MENU();

void FORNECEDOR();
void CADASTRARFORNECEDOR();
void EDITARFORNECEDOR();
void EXCLUIRFORNECEDOR();
void LISTARFORNECEDOR();
bool CODFORNECEDOR(cod);

void TIPOSPRODUTO();
void CADASTRARTIPOSPRODUTO();
void EDITARTIPOSPRODUTO();
void EXCLUIRTIPOSPRODUTO();
void LISTARTIPO();
bool CODTIPO(cod);

void PRODUTOS();
void CADASTRARPRODUTO();
void EDITARPRODUTO();
void EXCLUIRPRODUTO();
void LISTARPRODUTO();
bool CODPRODUTO(cod);

void REALIZARPEDIDO(Pedidos);
void FINALIZARPEDIDO(Pedidos);
void CANCELARPEDIDO(Pedidos);
void ADICIONARITEM(Pedidos);
void LISTARITENS(Pedidos);

//STRUCTS ==================================

struct Login{
    char usuario[15];
    char senha[10];
};

struct Fornecedor{
    char codigo[4];
    char razao[100];
    int cnpj;
    char inscricao[100];
    int telefone;
    char email[100];
    char rua[100];
	int numero;
	char bairro[50];
    char cidade[50];
    char estado[30];
    int cep;
    bool status;
    int cont; //utilizado para pesquisa
};

struct TipoProduto{
    char codigo[4];
    char descricao[100];
    bool status;
	int cont; //utilizado para pesquisa
};

struct Produto{
    char codigo[4];
    char tipo[4];
    char nome[100];
    char unidade[10];
    float valor;
    bool status;
	int cont; //utilizado para pesquisa
};

typedef struct ItemPedido{
    char item[100];
    float quantidade;
    float valor;
    char unidade[10];
    float qtd;
}Item;

typedef struct Pedido{
	int primeiro;
	int ultimo;
	Item item[10];
}Pedidos;




//FUNÇÕES IMPLEMENTADAS ==================================

//ESVAZIA O VETOR
void EsvaziaVetor(Pedidos *p){
    p->primeiro = p->ultimo = 0;
}

//VERIFICA SE O VETOR ESTÁ VAZIO
bool EstaVazio (Pedidos *p){
	return p -> primeiro == p -> ultimo;
}

//PESQUISAR FORNECEDOR
//==========================================================================
struct Fornecedor PESQUISAFORNECEDOR(pesquisa){
	struct Fornecedor fornecedor;
    FILE *arquivo;
    int cont=0;

    if((arquivo = fopen("fornecedor.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&fornecedor, sizeof(struct Fornecedor),1,arquivo) == 1){
            if(strcmp(pesquisa,fornecedor.codigo)==0 && fornecedor.status){
				fornecedor.cont = cont;
                return fornecedor;
                break;
            }
        }
        cont++;
    }
	fclose(arquivo);
}

//PESQUISAR TIPO DE PRODUTO
//==========================================================================
struct TipoProduto PESQUISATIPO(pesquisa){
	struct TipoProduto tipo;
    FILE *arquivo;
    int cont=0;

    if((arquivo = fopen("tipoproduto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&tipo, sizeof(struct TipoProduto),1,arquivo) == 1){
            if(strcmp(pesquisa,tipo.codigo)==0 && tipo.status){
				tipo.cont = cont;
                return tipo;
                break;
            }
        }
        cont++;
    }
	fclose(arquivo);
}

//PESQUISAR PRODUTO
//==========================================================================
struct Produto PESQUISAPRODUTO(pesquisa){
	struct Produto prod;
    FILE *arquivo;
    int cont=0;

    if((arquivo = fopen("produto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&prod, sizeof(struct Produto),1,arquivo) == 1){
            if(strcmp(pesquisa,prod.codigo)==0 && prod.status){
				prod.cont = cont;
                return prod;
                break;
            }
        }
        cont++;
    }
	fclose(arquivo);
}

//VERIFICA CODIGO FORNECEDOR EXISTENTE
//==========================================================================
bool CODFORNECEDOR(cod){
    struct Fornecedor fornecedor;
    FILE *arquivo;
    bool teste = true;

    if((arquivo = fopen("fornecedor.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&fornecedor, sizeof(struct Fornecedor),1,arquivo) == 1){
            if(strcmp(cod,fornecedor.codigo)==0 && fornecedor.status){
                printf("\nCodigo ja existe!\n\n");
                teste = false;
                break;
            }
        }
    }
    fclose(arquivo);
    return teste;
}

//VERIFICA CODIGO TIPO EXISTENTE
//==========================================================================
bool CODTIPO(cod){
    struct TipoProduto tipo;
    FILE *arquivo;
    bool teste = true;

    if((arquivo = fopen("tipoproduto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&tipo, sizeof(struct TipoProduto),1,arquivo) == 1){
            if(strcmp(cod,tipo.codigo)==0 && tipo.status){
                printf("\nCodigo ja existe!\n\n");
                teste = false;
                break;
            }
        }
    }
    fclose(arquivo);
    return teste;
}

//VERIFICA CODIGO PRODUTO EXISTENTE
//==========================================================================
bool CODPRODUTO(cod){
    struct Produto prod;
    FILE *arquivo;
    bool teste = true;

    if((arquivo = fopen("produto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&prod, sizeof(struct Produto),1,arquivo) == 1){
            if(strcmp(cod,prod.codigo)==0 && prod.status){
                printf("\nCodigo ja existe!\n\n");
                teste = false;
                break;
            }
        }
    }
    fclose(arquivo);
    return teste;
}

//LISTAR FORNECEDORES
//==========================================================================
void LISTARFORNECEDOR(){
    struct Fornecedor fornecedor;
    FILE *arquivo;

    if((arquivo = fopen("fornecedor.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	printf("\tCODIGO\t|\tRAZAO SOCIAL\t|\tCNPJ\t\t|\tTELEFONE\t|\tEMAIL\n");
	printf("=========================================================================================================================\n");
    while (!feof(arquivo)){
        if(fread(&fornecedor, sizeof(struct Fornecedor),1,arquivo) == 1){
            if(fornecedor.status){
                printf("\t%s \t|\t %s \t|\t %d \t|\t %d \t|\t %s\n", fornecedor.codigo, fornecedor.razao, fornecedor.cnpj, fornecedor.telefone, fornecedor.email);
            }
        }
    }
    fclose(arquivo);
}

//CADASTRAR FORNECEDOR
//==========================================================================
void CADASTRARFORNECEDOR(){
    struct Fornecedor fornecedor;
    FILE *arquivo;
    bool teste = false;

	printf("============= CADASTRO DE FORNECEDOR =============\n\n\n");
	printf("Insira a razao social:\n");
    fflush(stdin);
    gets(fornecedor.razao);

    while(!teste){
		printf("Insira um codigo com 3 letras:\n");
		fflush(stdin);
		gets(fornecedor.codigo);
		teste = CODFORNECEDOR(fornecedor.codigo);
    }
    printf("Informe o CNPJ:\n");
    fflush(stdin);
    scanf("%d", &fornecedor.cnpj);
    printf("Informe a inscricao estadual:\n");
    fflush(stdin);
    gets(fornecedor.inscricao);
    printf("Informe o telefone:\n");
    fflush(stdin);
    scanf("%d", &fornecedor.telefone);
    printf("Informe o email:\n");
    fflush(stdin);
    gets(fornecedor.email);
    printf("Informe a rua:\n");
    fflush(stdin);
    gets(fornecedor.rua);
    printf("Informe o numero:\n");
    fflush(stdin);
    scanf("%d", &fornecedor.numero);
    printf("Informe o bairro:\n");
    fflush(stdin);
    gets(fornecedor.bairro);
    printf("Informe a cidade:\n");
    fflush(stdin);
    gets(fornecedor.cidade);
    printf("Informe o estado:\n");
    fflush(stdin);
    gets(fornecedor.estado);
    printf("Informe o CEP:\n");
    fflush(stdin);
    scanf("%d", &fornecedor.cep);
    fornecedor.status = true;

	if((arquivo = fopen("fornecedor.txt","ab")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	if(fwrite(&fornecedor,sizeof(struct Fornecedor),1, arquivo) == 1){
        printf("\n\nCadastro realizado com sucesso!\n\n");
	} else{
        printf("\n\nErro ao efetuar cadastro\n\n");
	}

	fclose(arquivo);
	system("pause");
}

//EDITAR FORNECEDOR
//==========================================================================
void EDITARFORNECEDOR(){
    struct Fornecedor fornecedor;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;
	bool teste = false;

    printf("============= ATUALIZACAO DE FORNECEDOR =============\n\n\n");
    LISTARFORNECEDOR();
    printf("\n\nInforme o codigo do fornecedor que deseja editar:\n");
    fflush(stdin);
    gets(pesquisa);

	fornecedor = PESQUISAFORNECEDOR(pesquisa);
	printf("\n\n\tCodigo: %s\n", fornecedor.codigo);
    printf("\tRazao Social: %s\n", fornecedor.razao);

	if((arquivo = fopen("fornecedor.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(fornecedor.codigo == NULL){
        printf("\n\nCadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja atualizar o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
            system("cls");
            printf("============= ATUALIZACAO DE FORNECEDOR =============\n\n\n");
            printf("Atualizar fornecedor\n\n");
            printf("Insira a razao social:\n");
            fflush(stdin);
            gets(fornecedor.razao);
            while(!teste){
                printf("Insira um codigo com 3 letras:\n");
                fflush(stdin);
                gets(fornecedor.codigo);
                teste = CODFORNECEDOR(fornecedor.codigo);
            }
            printf("Informe o CNPJ:\n");
            fflush(stdin);
            scanf("%d", &fornecedor.cnpj);
            printf("Informe a inscricao estadual:\n");
            fflush(stdin);
            gets(fornecedor.inscricao);
            printf("Informe o telefone:\n");
            fflush(stdin);
            scanf("%d", &fornecedor.telefone);
            printf("Informe o email:\n");
            fflush(stdin);
            gets(fornecedor.email);
            printf("Informe a rua:\n");
            fflush(stdin);
            gets(fornecedor.rua);
            printf("Informe o numero:\n");
            fflush(stdin);
            scanf("%d", &fornecedor.numero);
            printf("Informe o bairro:\n");
            fflush(stdin);
            gets(fornecedor.bairro);
            printf("Informe a cidade:\n");
            fflush(stdin);
            gets(fornecedor.cidade);
            printf("Informe o estado:\n");
            fflush(stdin);
            gets(fornecedor.estado);
            printf("Informe o CEP:\n");
            fflush(stdin);
            scanf("%d", &fornecedor.cep);

            fseek(arquivo, sizeof(struct Fornecedor) * fornecedor.cont, SEEK_SET);
            fwrite(&fornecedor,sizeof(struct Fornecedor),1, arquivo);
            printf("\n\nRegistro atualizado com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//EXCLUIR FORNECEDOR
//==========================================================================
void EXCLUIRFORNECEDOR(){
    struct Fornecedor fornecedor;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;

    printf("============= EXCLUIR FORNECEDOR =============\n\n\n");
    LISTARFORNECEDOR();
    printf("\n\nInforme o codigo do fornecedor que deseja excluir:\n");
    fflush(stdin);
    gets(pesquisa);

	fornecedor = PESQUISAFORNECEDOR(pesquisa);
	printf("\n\n\tCodigo: %s\n", fornecedor.codigo);
    printf("\tRazao Social: %s\n", fornecedor.razao);

    if((arquivo = fopen("fornecedor.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(fornecedor.codigo == NULL){
        printf("Cadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja excluir o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
			system("cls");
            printf("============= EXCLUIR FORNECEDOR =============\n\n\n");
            fornecedor.status = false;
            fseek(arquivo, sizeof(struct Fornecedor) * fornecedor.cont, SEEK_SET);
            fwrite(&fornecedor,sizeof(struct Fornecedor),1, arquivo);
            printf("Registro excluido com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//MENU FORNECEDOR
//==========================================================================
void FORNECEDOR(){
    int opcao;
	system("cls");
	printf("============= FORNECEDORES =============\n\n\n");
	printf("Informe a opcao desejada: \n\n\t1- CADASTRAR FORNECEDOR\n\t2- EDITAR FORNECEDOR \n\t3- EXCLUIR FORNECEDOR \n\t4- LISTAR FORNECEDORES \n\t5- VOLTAR\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 CADASTRARFORNECEDOR();
			 FORNECEDOR();
			 break;
		case 2:
			 system("cls");
			 EDITARFORNECEDOR();
			 FORNECEDOR();
			 break;
		case 3:
			 system("cls");
			 EXCLUIRFORNECEDOR();
			 FORNECEDOR();
			 break;
        case 4:
			 system("cls");
			 LISTARFORNECEDOR();
			 system("pause");
			 FORNECEDOR();
			 break;
		case 5:
			 system("cls");
			 MENU();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida!");
			FORNECEDOR();
	}
}

//LISTAR TIPOS DE PRODUTOS
//==========================================================================
void LISTARTIPO(){
    struct TipoProduto tipo;
    FILE *arquivo;

    if((arquivo = fopen("tipoproduto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	printf("\tCODIGO\t|\tDESCRICAO\n");
	printf("===============================================\n");
    while (!feof(arquivo)){
        if(fread(&tipo, sizeof(struct TipoProduto),1,arquivo) == 1){
            if(tipo.status){
                printf("\t%s \t|\t %s\n", tipo.codigo, tipo.descricao);
            }
        }
    }
    fclose(arquivo);
}

//CADASTRAR TIPOS DE PRODUTOS
//==========================================================================
void CADASTRARTIPOSPRODUTO(){
    struct TipoProduto tipo;
    FILE *arquivo;
    bool teste = false;

	printf("============= CADASTRO DE TIPO DE PRODUTO =============\n\n\n");
	printf("Descreva o tipo de produto:\n");
    fflush(stdin);
    gets(tipo.descricao);

    while(!teste){
		printf("Insira um codigo com 3 letras:\n");
		fflush(stdin);
		gets(tipo.codigo);
		teste = CODTIPO(tipo.codigo);
    }
    tipo.status = true;

	if((arquivo = fopen("tipoproduto.txt","ab")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	if(fwrite(&tipo,sizeof(struct TipoProduto),1, arquivo) == 1){
        printf("\n\nCadastro realizado com sucesso!\n\n");
	} else{
        printf("\n\nErro ao efetuar cadastro\n\n");
	}

	fclose(arquivo);
	system("pause");
}

//EDITAR TIPOS DE PRODUTOS
//==========================================================================
void EDITARTIPOSPRODUTO(){
    struct TipoProduto tipo;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;
	bool teste = false;

    printf("============= ATUALIZACAO DE TIPO DE PRODUTO =============\n\n\n");
    LISTARTIPO();
    printf("\n\nInforme o codigo do tipo de produto que deseja editar:\n");
    fflush(stdin);
    gets(pesquisa);

	tipo = PESQUISATIPO(pesquisa);
	printf("\n\n\tCodigo: %s\n", tipo.codigo);
    printf("\tDescricao: %s\n", tipo.descricao);

	if((arquivo = fopen("tipoproduto.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(tipo.codigo == NULL){
        printf("\n\nCadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja atualizar o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
            system("cls");
            printf("============= ATUALIZACAO DE TIPO DE PRODUTO =============\n\n\n");
            printf("Atualizar produto\n\n");
            printf("Descreva o tipo de produto:\n");
            fflush(stdin);
            gets(tipo.descricao);
			while(!teste){
				printf("Insira um codigo com 3 letras:\n");
				fflush(stdin);
				gets(tipo.codigo);
				teste = CODTIPO(tipo.codigo);
			}
            fseek(arquivo, sizeof(struct TipoProduto) * tipo.cont, SEEK_SET);
            fwrite(&tipo,sizeof(struct TipoProduto),1, arquivo);
            printf("\n\nRegistro atualizado com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//EXCLUIR TIPOS DE PRODUTOS
//==========================================================================
void EXCLUIRTIPOSPRODUTO(){
    struct TipoProduto tipo;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;

    printf("============= EXCLUIR TIPO DE PRODUTO =============\n\n\n");
    LISTARTIPO();
    printf("\n\nInforme o codigo do tipo de produto que deseja excluir:\n");
    fflush(stdin);
    gets(pesquisa);

	tipo = PESQUISATIPO(pesquisa);
	printf("\n\n\tCodigo: %s\n", tipo.codigo);
    printf("\tDescricao: %s\n", tipo.descricao);

    if((arquivo = fopen("tipoproduto.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(tipo.codigo == NULL){
        printf("Cadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja excluir o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
			system("cls");
            printf("============= EXCLUIR TIPO DE PRODUTO =============\n\n\n");
            tipo.status = false;
            fseek(arquivo, sizeof(struct TipoProduto) * tipo.cont, SEEK_SET);
            fwrite(&tipo,sizeof(struct TipoProduto),1, arquivo);
            printf("Registro excluido com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//MENU TIPOS DE PRODUTOS
//==========================================================================
void TIPOSPRODUTO(){
    int opcao;
	system("cls");
	printf("============= TIPO DE PRODUTO =============\n\n\n");
	printf("Informe a opcao desejada: \n\n\t1- CADASTRAR TIPOS DE PRODUTO\n\t2- EDITAR TIPOS DE PRODUTO \n\t3- EXCLUIR TIPOS DE PRODUTO \n\t4- LISTAR TIPOS DE PRODUTO \n\t5- VOLTAR\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 CADASTRARTIPOSPRODUTO();
			 TIPOSPRODUTO();
			 break;
		case 2:
			 system("cls");
			 EDITARTIPOSPRODUTO();
			 TIPOSPRODUTO();
			 break;
		case 3:
			 system("cls");
			 EXCLUIRTIPOSPRODUTO();
			 TIPOSPRODUTO();
			 break;
        case 4:
			 system("cls");
			 LISTARTIPO();
			 system("pause");
			 TIPOSPRODUTO();
			 break;
		case 5:
			 system("cls");
			 MENU();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida!");
			TIPOSPRODUTO();
	}
}



//LISTAR PRODUTOS
//==========================================================================
void LISTARPRODUTO(){
    struct Produto prod;
    FILE *arquivo;

    if((arquivo = fopen("produto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	printf("\tCODIGO\t|\tNOME\t\t|\tVALOR\t|\tUNIDADE\n");
	printf("============================================================================\n");
    while (!feof(arquivo)){
        if(fread(&prod, sizeof(struct Produto),1,arquivo) == 1){
            if(prod.status){
                printf("\t%s \t|\t %s \t|\t %.2f \t|\t %s\n", prod.codigo, prod.nome, prod.valor, prod.unidade);
            }
        }
    }
    fclose(arquivo);
}

//CADASTRAR PRODUTOS
//==========================================================================
void CADASTRARPRODUTO(){
    struct Produto produto;
    FILE *arquivo;
    bool teste = false;

	printf("============= CADASTRO DE PRODUTO =============\n\n\n");
	LISTARTIPO();
	printf("\n\nInforme o codigo do tipo de produto que deseja cadastrar:\n");
    fflush(stdin);
    gets(produto.tipo);
    printf("Informe o nome do produto:\n");
    fflush(stdin);
    gets(produto.nome);

    while(!teste){
		printf("Insira um codigo com 3 letras:\n");
		fflush(stdin);
		gets(produto.codigo);
		teste = CODPRODUTO(produto.codigo);
    }
    printf("Informe a unidade de medida:\n");
    fflush(stdin);
    gets(produto.unidade);
    printf("Informe o valor do produto:\n");
    fflush(stdin);
    scanf("%f", &produto.valor);
    produto.status = true;

    if((arquivo = fopen("produto.txt","ab")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	if(fwrite(&produto,sizeof(struct Produto),1, arquivo) == 1){
        printf("\n\nCadastro realizado com sucesso!\n\n");
	} else{
        printf("\n\nErro ao efetuar cadastro\n\n");
	}

	fclose(arquivo);
	system("pause");
}

//EDITAR PRODUTOS
//==========================================================================
void EDITARPRODUTO(){
    struct Produto prod;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;
	bool teste = false;

    printf("============= ATUALIZACAO DE PRODUTO =============\n\n\n");
	LISTARPRODUTO();
    printf("\n\nInforme o codigo do produto que deseja editar:\n");
    fflush(stdin);
    gets(pesquisa);

	prod = PESQUISAPRODUTO(pesquisa);
	printf("\n\n\tCodigo: %s\n", prod.codigo);
	printf("\tNome: %s\n", prod.nome);
	printf("\tValor: %.2f\n", prod.valor);
	printf("\tUnidade: %s\n", prod.unidade);

    if((arquivo = fopen("produto.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(prod.codigo == NULL){
        printf("\n\nCadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja atualizar o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
            system("cls");
            printf("============= ATUALIZACAO DE PRODUTO =============\n\n\n");
            printf("Atualizar produto\n\n");
            LISTARTIPO();
            printf("\n\nInforme o codigo do tipo do produto:\n");
            fflush(stdin);
            gets(prod.tipo);
            printf("Informe o nome do produto:\n");
            fflush(stdin);
            gets(prod.nome);
			while(!teste){
				printf("Insira um codigo com 3 letras:\n");
				fflush(stdin);
				gets(prod.codigo);
				teste = CODPRODUTO(prod.codigo);
			}
            printf("Informe a unidade de medida:\n");
            fflush(stdin);
            gets(prod.unidade);
            printf("Informe o valor do produto:\n");
            fflush(stdin);
            scanf("%f", &prod.valor);
            fseek(arquivo, sizeof(struct Produto) * prod.cont, SEEK_SET);
            fwrite(&prod,sizeof(struct Produto),1, arquivo);
            printf("\n\nRegistro atualizado com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//EXCLUIR PRODUTOS
//==========================================================================
void EXCLUIRPRODUTO(){
    struct Produto prod;
    FILE *arquivo;
    char pesquisa[4];
    char opcao;

    printf("============= EXCLUIR PRODUTO =============\n\n\n");
	LISTARPRODUTO();
    printf("\n\nInforme o codigo do produto que deseja excluir:\n");
    fflush(stdin);
    gets(pesquisa);

	prod = PESQUISAPRODUTO(pesquisa);
	printf("\n\n\tCodigo: %s\n", prod.codigo);
	printf("\tNome: %s\n", prod.nome);
	printf("\tValor: %.2f\n", prod.valor);
	printf("\tUnidade: %s\n", prod.unidade);

	if((arquivo = fopen("produto.txt","rb+")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    if(prod.codigo == NULL){
        printf("Cadastro inexistente!\n\n");
    }else{
        printf("\n\nDeseja excluir o cadastro? [s/n]\n\n");
        opcao = getche();
        if(opcao == 's'){
            system("cls");
            printf("============= EXCLUIR PRODUTO =============\n\n\n");
            prod.status = false;
            fseek(arquivo, sizeof(struct Produto) * prod.cont, SEEK_SET);
            fwrite(&prod,sizeof(struct Produto),1, arquivo);
            printf("Registro excluido com sucesso!\n\n");
        }
    }
    fclose(arquivo);
    system("pause");
}

//MENU PRODUTOS
//==========================================================================
void PRODUTOS(){
    int opcao;
	system("cls");
	printf("============= PRODUTO =============\n\n\n");
	printf("Informe a opcao desejada: \n\n\t1- CADASTRAR PRODUTO\n\t2- EDITAR PRODUTO \n\t3- EXCLUIR PRODUTO \n\t4- LISTAR PRODUTO \n\t5- VOLTAR\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 CADASTRARPRODUTO();
			 PRODUTOS();
			 break;
		case 2:
			 system("cls");
			 EDITARPRODUTO();
			 PRODUTOS();
			 break;
		case 3:
			 system("cls");
			 EXCLUIRPRODUTO();
			 PRODUTOS();
			 break;
        case 4:
			 system("cls");
			 LISTARPRODUTO();
			 system("pause");
			 PRODUTOS();
			 break;
		case 5:
			 system("cls");
			 MENU();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida!");
			PRODUTOS();
	}
}



//ADICIONAR ITEM AO PEDIDO
//==========================================================================
void ADICIONARITEM(Pedidos *p){
    FILE *arquivo2;
    struct Produto produto;
    char pesquisa[4];

    printf("============= REALIZAR PEDIDO =============\n\n\n");
    //lista os tipos de produto
    LISTARTIPO();
	printf("\n\nInforme o codigo do tipo de produto:\n");
    fflush(stdin);
    gets(pesquisa);
    system("cls");

    printf("============= REALIZAR PEDIDO =============\n\n\n");
    //lista os produtos de acordo com o tipo escolhido
	if((arquivo2 = fopen("produto.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo2)){
        if(fread(&produto, sizeof(struct Produto),1,arquivo2) == 1){
            if(strcmp(pesquisa,produto.tipo)==0 && produto.status){
                printf("\t%s \t|\t %s \t|\t %.2f\n", produto.codigo, produto.nome, produto.valor);
            }
        }
    }
    fclose(arquivo2);

    printf("\nInforme o codigo do produto:\n");
    gets(pesquisa);
	produto = PESQUISAPRODUTO(pesquisa);

	strcpy(p -> item[p->ultimo].item, produto.nome);
	strcpy(p -> item[p->ultimo].unidade, produto.unidade);
    printf("Informe a quantidade desejada:\n");
    scanf("%f",&p -> item[p->ultimo].qtd);
    p -> item[p->ultimo].valor = (p -> item[p->ultimo].qtd* produto.valor); //multiplica a quantidade pelo valor do produto
    p -> ultimo ++;

    REALIZARPEDIDO(p);
}

//FINALIZAR PEDIDO
//==========================================================================
void FINALIZARPEDIDO(Pedidos *p){
	int i;
	float valorTotal = 0;

	system("cls");
	LISTARITENS(p);

	for (i=0; i< p->ultimo; i++){
		valorTotal = valorTotal + p -> item[i].valor;
	}
    printf("VALOR TOTAL DO PEDIDO: %.2f", valorTotal);
    printf("\n\n*********** Pedido finalizado! ***********\n\n");
    system("pause");
}

//CANCELAR PEDIDO
//==========================================================================
void CANCELARPEDIDO(Pedidos *p){
    EsvaziaVetor(p);
    printf("\n\nPedido cancelado.\n\n");
    system("pause");
}

//LISTAR ITENS DO PEDIDO
//==========================================================================
void LISTARITENS(Pedidos *p){
	int i;

    if (EstaVazio(p)){
		return;
	}
	else{
        printf("============= ITENS DO PEDIDO =============\n\n");
        for (i=0; i< p->ultimo; i++){
            printf("%s\t%.f %s\t%.2f\n", p -> item[i].item, p -> item[i].qtd, p -> item[i].unidade, p -> item[i].valor);
        }
        printf("\n===========================================\n\n");
	}
}

//MENU DO PEDIDO
//==========================================================================
void REALIZARPEDIDO(Pedidos *p){
	int i;
	int op;

    system("cls");
    printf("============= REALIZAR PEDIDO =============\n\n\n");

    LISTARITENS(p);

    printf("Informe a opcao desejada: \n\n\t1- ADICIONAR ITEM\n\t2- FINALIZAR PEDIDO \n\t3- CANCELAR PEDIDO \n");
    scanf("%i",&op);
    switch(op){
        case 1:
             system("cls");
             ADICIONARITEM(p);
             break;
        case 2:
             FINALIZARPEDIDO(p);
             MENU();
             break;
        case 3:
             system("cls");
             CANCELARPEDIDO(p);
             MENU();
             break;
        default:
            system("cls");
            printf("Opcao Invalida!");
            MENU();
    }
}



//MENU PRINCIPAL
//============================================
void MENU(){
	int opcao;
	Pedidos *p;

	system("cls");
	printf("============= MENU PRINCIPAL =============\n\n\n");
	printf("Informe a opcao desejada: \n\n\t1- FORNECEDOR\n\t2- TIPOS DE PRODUTO\n\t3- PRODUTOS \n\t4- REALIZAR PEDIDO \n\t5- SAIR \n");
	scanf("%i",&opcao);
	switch(opcao){
	    case 1:
			 system("cls");
			 FORNECEDOR();
			 break;
		case 2:
			 system("cls");
			 TIPOSPRODUTO();
			 break;
		case 3:
			 system("cls");
			 PRODUTOS();
			 break;
		case 4:
			 system("cls");
			 EsvaziaVetor(&p);
			 REALIZARPEDIDO(&p);
			 break;
        case 5:
			 exit(0);
		default:
			system("cls");
			printf("Opcao Invalida!");
			MENU();
	}
}

struct Login LOGIN(){
	struct Login login;
    FILE *arquivo;
    int cont=0;
    char user[15];
    char sen[10];

    printf("Informe o usuario:\n");
    fflush(stdin);
    gets(user);
    printf("Informe a senha:\n");
    fflush(stdin);
    gets(sen);


    if((arquivo = fopen("login.txt","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

    while (!feof(arquivo)){
        if(fread(&login, sizeof(struct Login),1,arquivo) == 1){
            if(strcmp(user,login.usuario)==0 && strcmp(sen,login.senha)==0){
				MENU();
                break;
            }
        }
    }
    printf("Login invalido!");
	fclose(arquivo);
	system("pause");
	main();
}

void CADASTRO(){
    struct Login login;
    FILE *arquivo;

	printf("============= CADASTRO DE USUARIO =============\n\n\n");
	printf("Insira um usuario:\n");
    fflush(stdin);
    gets(login.usuario);
    printf("Insira uma senha:\n");
    fflush(stdin);
    gets(login.senha);

	if((arquivo = fopen("login.txt","ab")) == NULL){
		printf("Erro ao abrir o arquivo\n");
		system("pause");
		exit(1);
	}

	if(fwrite(&login,sizeof(struct Login),1, arquivo) == 1){
        printf("\n\nCadastro realizado com sucesso!\n\n");
	} else{
        printf("\n\nErro ao efetuar cadastro\n\n");
	}

	fclose(arquivo);
	main();
}

//==========================================================================
int main(){
    int opcao;

	system("cls");
	printf("============= LOGIN =============\n\n\n");
	printf("Informe a opcao desejada: \n\n\t1- REALIZAR LOGIN\n\t2- CADASTRAR USUARIO\n");
	scanf("%i",&opcao);
	switch(opcao){
	    case 1:
			 system("cls");
			 LOGIN();
			 break;
		case 2:
			 system("cls");
			 CADASTRO();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida!");
			main();
	}
}
