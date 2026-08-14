#include <stdio.h>
#include <stdlib.h>

// Ponteiro aponta diretamente pra key (valor).
// Prõximo aponta diretamente para o ponteiro de direção.
// New é o valor da key nova que será realocada conforme a ordem.
// Primeiro é a referencia inicial que sempre inicializa a lista (Válido incrementar nas condições)

typedef struct Celula{
	struct Celula *anterior;
	struct Celula *proximo;
	int valor;
}Celula;

typedef struct LDDE{
	Celula *primeiro;
	int qtde;
}LDDE;

LDDE *inicializa_lista(){
	LDDE *lista = malloc(sizeof(LDDE));
	lista->primeiro = NULL;
	lista->qtde = 0;
	return lista;
}

Celula *inicializa_celula(int valor){ // Inicializador da célula
	Celula *celula = malloc(sizeof(Celula));
	celula->anterior = NULL;
	celula->proximo = NULL;
	celula->valor = valor;
	return celula;
}

void inserir(LDDE *lista, int valor) {
    // implementar

	Celula *ptr = lista->primeiro; // Inicializa o ponteiro na primeira referencia.
	Celula *new = inicializa_celula(valor); // Inicializa a celula (key que irá entrar em vigor) feito através da função.

	// -------------- Conditions --------------
	if (!ptr) lista->primeiro = new; // Se o ponteiro na primeira referencia não existir, a lista retorna o primeiro item como o new

	else if (valor < ptr->valor){ // Se o valor da celula no ponteiro for maior que na posição inicial/atual 
		ptr->anterior = new; // Anterior retorna como o novo valor da key
		new->proximo = ptr; // O proximo valor referenciado será o valor do ponteiro na referencia atual
		lista->primeiro = new; // Novo valor da primeira referencia será atualizado.

	} else {
		do { // ------------------- Conditions do looping ---------------------
			if (!ptr->proximo){ // Se a proxima referencia não estiver contida no ponteiro
				ptr->proximo = new; // O novo valor da key será o valor do ponteiro na referencia atual
				new->anterior = ptr; // O valor anterior da key será o valor do ponteiro na referencia atual
				break; // Quebra o looping
			}
			if (valor < ptr->proximo->valor){
				ptr->proximo->anterior = new; // O valor anterior da proxima referencia será o valor do ponteiro na referencia atual
				new->proximo = ptr->proximo; // O valor da proxima referencia será o valor do ponteiro na referencia atual
				ptr->proximo = new; // O valor da proxima referencia será o valor do ponteiro na referencia atual
				new->anterior = ptr; // O valor anterior da key será o valor do ponteiro na referencia atual
				break; // Quebra o looping
			}
		}
		while(ptr = ptr->proximo); // Enquanto o ponteiro for igual a proxima referencia, o looping continua
	}
	lista ->qtde++; // Incrementa a quantidade de elementos na lista
}


void imprimir_crescente(LDDE *lista){
	Celula *atual = lista->primeiro;
	while(atual != NULL){
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
}

void imprimir_decrescente(LDDE *lista){
	Celula *atual = lista->primeiro;
	Celula *anterior = NULL;
	while(atual != NULL){
		anterior = atual;
		atual = atual->proximo;
	}
	atual = anterior;
	while(atual != NULL){
		printf("%d ", atual->valor);
		atual = atual->anterior;
	}
	printf("\n");
}

Celula *buscar(LDDE *lista, int valor){
	Celula *atual = lista->primeiro;
	while(atual != NULL && atual->valor != valor){
		atual = atual->proximo;
	}
	return atual;
}

void remover(LDDE *lista, int valor) {
    // Implementar remoção de elemento da lista

    Celula *ptr = buscar(lista, valor); // Inicializa a referencia no primiro item da lista
    if (!ptr) return; // Se o ponteiro não existir, a função retorna

    if (ptr == lista->primeiro) { // Se o ponteiro for igual a primeira referencia, a primeira referencia será atualizada para o proximo item da lista
        lista->primeiro = ptr->proximo;
    } else { // Se o ponteiro não for igual a primeira referencia, o proximo item da lista será atualizado para o proximo item do ponteiro
        ptr->anterior->proximo = ptr->proximo;
    }

    if (ptr->proximo) { // Se o proximo item do ponteiro existir, o anterior do proximo item será atualizado para o anterior do ponteiro
        ptr->proximo->anterior = ptr->anterior;
    }

    free(ptr); // Libera a memória
    lista->qtde--; // Decrementa a quantidade de elementos na lista
}


int main(void) {
  LDDE *lista = inicializa_lista();
	int in[] = {2, 3, 9, 6, 7, 4, 1, 8, 0, 5};
	int out[] = {0, 9, 1, 8, 5, 5, 6, 2, 3, 4, 7};
	int len_in = sizeof(in) / sizeof(int);
	int len_out = sizeof(out) / sizeof(int);
	for(int i = 0; i < len_in; i ++){
		inserir(lista, in[i]);
		imprimir_crescente(lista);
		imprimir_decrescente(lista);
	}
	for(int j = 0; j < len_out; j++){
		remover(lista, out[j]);
		imprimir_crescente(lista);
		imprimir_decrescente(lista);
	}
  return 0;
}