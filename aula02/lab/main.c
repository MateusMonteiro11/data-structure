#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma célula da lista duplamente ligada
typedef struct Celula {
	int valor;					// Valor armazenado na célula
	struct Celula *proximo;		// Ponteiro para o próximo elemento
	struct Celula *anterior;	// Ponteiro para o elemento anterior
} Celula;

// Estrutura da fila com ponteiros para início e fim
typedef struct {
	Celula *head;	// Ponteiro para o primeiro elemento (início da fila)
	Celula *tail;	// Ponteiro para o último elemento (fim da fila)
	int qtde;		// Contador de elementos na fila
} Queue;

// Cria uma nova célula com o valor especificado
Celula *cria_celula(int valor){
	Celula *nova_celula = malloc(sizeof *nova_celula);
    if (!nova_celula) {
        fprintf(stderr, "Erro ao alocar memória para nova célula.\n");
        exit(EXIT_FAILURE);
    }
    nova_celula->valor = valor;
    nova_celula->proximo = NULL;
    nova_celula->anterior = NULL;
    return nova_celula;
}

// Cria uma nova fila vazia
Queue *cria_queue(){
	Queue *queue = malloc(sizeof *queue);
    if (!queue) {
        fprintf(stderr, "Erro ao alocar memória para a fila.\n");
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->qtde = 0;
    return queue;
}

// Operação ENQUEUE: insere elemento no final da fila (FIFO)
void enqueue(Queue *queue, int valor){
    Celula *nova_celula = cria_celula(valor);
    if (queue->tail) {
        queue->tail->proximo = nova_celula; // Atualiza o próximo do último elemento
        nova_celula->anterior = queue->tail; // Atualiza o anterior da nova célula
    } else {
        queue->head = nova_celula; // Se a fila estava vazia, atualiza o head
    }
    queue->tail = nova_celula; // Atualiza o tail para a nova célula
    queue->qtde++; // Incrementa a quantidade de elementos na fila
}

// Operação DEQUEUE: remove elemento do início da fila (FIFO)
int dequeue(Queue *queue, int *valor){
    if (!queue->head) {
        fprintf(stderr, "Fila vazia. Não é possível remover elementos.\n");
        return 0; // Retorna falha quando a fila está vazia
    }
    Celula *temp = queue->head; // Armazena a célula a ser removida
    *valor = temp->valor; // Armazena o valor da célula removida
    queue->head = queue->head->proximo; // Atualiza o head para o próximo elemento
    if (queue->head) {
        queue->head->anterior = NULL; // Atualiza o anterior do novo head
    } else {
        queue->tail = NULL; // Se a fila ficou vazia, atualiza o tail
    }
    free(temp); // Libera a memória da célula removida
    queue->qtde--; // Decrementa a quantidade de elementos na fila
    return 1; // Retorna sucesso na remoção
}

// Exibe todos os elementos da fila (do início ao fim)
void show(Queue *queue){
    Celula *atual = queue->head; // Começa pelo head da fila
    while (atual) {
        printf("%d", atual->valor); // Imprime o valor da célula atual
        atual = atual->proximo; // Avança para a próxima célula
        if (atual) {
            printf(" ");
        }
    }
    printf("\n"); // Nova linha após imprimir todos os elementos
}

void free_queue(Queue *queue){
    Celula *atual = queue->head;
    while (atual) {
        Celula *proxima = atual->proximo;
        free(atual);
        atual = proxima;
    }
    free(queue);
}

int main(void) {
    Queue *queue = cria_queue(); // Cria uma nova fila
    int in[] = {10, 2, 0, 4, 5, 5, 6, 2, 8, 1, 9}; // Array de valores a serem inseridos na fila
    int size = sizeof(in) / sizeof(in[0]); // Calcula o tamanho do array

    printf("=== INSERINDO ELEMENTOS ===\n");

    // Insere os elementos na fila
    for (int i = 0; i < size; i++) {
        enqueue(queue, in[i]);
        printf("Inserido %d: ", in[i]);
        show(queue);
    }

    printf("\n=== REMOVENDO ELEMENTOS ===\n");

    // Remove todos os elementos da fila
    for (int i = 0; i < size; i++) {
        int valor_removido;
        if (dequeue(queue, &valor_removido)) {
            printf("Valor removido: %d, Fila restante:", valor_removido);
            if (queue->head) {
                printf(" ");
            }
            show(queue);
        }
    }

    free_queue(queue);
    return 0; // Finaliza o programa com sucesso
}
