#include <stdio.h>
#include <stdlib.h>

#include "lista_dinamica.h"

/*
   Cria uma lista vazia (inicializa o ponteiro para NULL).
   A lista estara vazia apos a execucao desta funcao.
*/
void cria(Lista *p_l) {
    *p_l = NULL;  // Inicializa a lista como vazia, apontando para NULL.
}

/*
   Verifica se a lista esta vazia.
   Retorna 1 se a lista estiver vazia, 0 caso contrario.
*/
int vazia(Lista *p_l) {
    return (*p_l == NULL);  // Retorna 1 se a lista for NULL (vazia), 0 caso contrario.
}

/*
   Insere um elemento no inicio da lista.
   A lista sera modificada para que o novo elemento seja o primeiro.
*/
void insere_inicio(Lista *p_l, elem_t e) {
    No_lista *novo;
    novo = (No_lista*)malloc(sizeof(No_lista));  // Aloca memoria para o novo no.
    novo->info = e;  // Atribui o valor do novo no.
    novo->prox = *p_l;  // O proximo do novo no sera o no que estava no inicio da lista.
    *p_l = novo;  // Atualiza a lista para apontar para o novo no.
}

/*
   Insere um elemento no final da lista.
   A lista sera modificada para que o novo elemento seja o ultimo.
*/
void insere_fim(Lista *p_l, elem_t e) {
    No_lista *novo, *aux;
    novo = (No_lista*)malloc(sizeof(No_lista));  // Aloca memoria para o novo no.
    novo->info = e;  // Atribui o valor ao novo no.
    novo->prox = NULL;  // O proximo do novo no sera NULL (final da lista).

    // Se a lista estiver vazia, o novo no sera o primeiro (e o unico) da lista.
    if (vazia(p_l)) {
        *p_l = novo;
        return;
    }

    aux = *p_l;
    // Percorre a lista ate o ultimo no.
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;  // O ultimo no agora apontara para o novo no.
}

/*
   Insere um elemento na lista de maneira ordenada.
   A lista permanece ordenada apos a insercao.
   Retorna 0 caso o elemento ja exista na lista, e 1 caso contrario.
*/
int insere_ordenado(Lista *p_l, elem_t e) {
    No_lista *novo, *aux = *p_l;
    novo = (No_lista*)malloc(sizeof(No_lista));  // Aloca memoria para o novo no.
    novo->info = e;  // Atribui o valor ao novo no.

    // Se a lista estiver vazia ou o valor do primeiro no for maior ou igual ao novo valor.
    if (vazia(p_l) || (*p_l)->info >= e) {
        novo->prox = *p_l;  // O proximo do novo no sera o antigo primeiro no.
        *p_l = novo;  // O novo no passa a ser o primeiro da lista.
        return 1;
    }

    // Encontra a posicao correta para a insercao (onde o valor atual e menor que o novo valor).
    while (aux->prox != NULL && aux->prox->info < e) {
        aux = aux->prox;
    }

    novo->prox = aux->prox;  // O proximo do novo no sera o no que estava apos o no encontrado.
    aux->prox = novo;  // O no anterior agora aponta para o novo no.

    return 1;  // Insercao realizada com sucesso.
}

/*
   Verifica se a lista esta ordenada.
   Retorna 1 se a lista estiver ordenada, 0 caso contrario.
*/
int ordenada(Lista *p_l) {
    No_lista *aux = *p_l;

    // Percorre a lista comparando cada no com o proximo.
    while (aux != NULL) {
        No_lista *verifica = aux->prox;
        while (verifica != NULL) {
            if (aux->info > verifica->info) {
                return 0;  // Se um no for maior que o proximo, a lista nao esta ordenada.
            }
            verifica = verifica->prox;  // Move para o proximo no.
        }
        aux = aux->prox;  // Move para o proximo no.
    }

    return 1;  // A lista esta ordenada.
}

/*
   Ordena a lista utilizando o algoritmo de ordenacao por selecao.
   Após a execucao, a lista estara ordenada em ordem crescente.
*/
void ordena(Lista *p_l) {
    No_lista *aux = *p_l;

    // Percorre todos os nos da lista.
    while (aux != NULL) {
        No_lista *ordena = aux->prox;
        while (ordena != NULL) {
            // Se o valor do no atual for maior que o valor do no subsequente, troca os valores.
            if (aux->info > ordena->info) {
                int min_idx = aux->info;
                aux->info = ordena->info;
                ordena->info = min_idx;
            }
            ordena = ordena->prox;  // Move para o proximo no.
        }
        aux = aux->prox;  // Move para o proximo no.
    }
}

/*
   Remove o elemento que esta no inicio da lista.
   Retorna 0 caso a lista esteja vazia, e 1 caso a remocao seja bem-sucedida.
*/
int remove_inicio(Lista *p_l, elem_t *p_e) {
    No_lista *aux = *p_l;

    if (vazia(p_l))  // Se a lista estiver vazia, nao ha nada para remover.
        return 0;

    *p_e = aux->info;  // Armazena o valor a ser removido.
    *p_l = aux->prox;  // O primeiro no agora sera o proximo no da lista.
    free(aux);  // Libera a memoria do no removido.

    return 1;  // Remocao realizada com sucesso.
}

/*
   Remove o elemento que esta no final da lista.
   Retorna 0 caso a lista esteja vazia, e 1 caso a remocao seja bem-sucedida.
*/
int remove_fim(Lista *p_l, elem_t *p_e) {
    No_lista *no, *aux = *p_l;

    if (vazia(p_l)) {  // Se a lista estiver vazia, nao ha nada para remover.
        return 0;
    }

    // Se houver apenas um elemento, ele sera removido diretamente.
    if (aux->prox == NULL) {
        no = aux;
        *p_l = NULL;  // A lista agora ficara vazia.
    }
    else {
        // Percorre ate o penultimo no.
        while (aux->prox->prox != NULL) {
            aux = aux->prox;
        }
        *p_e = aux->prox->info;  // Armazena o valor a ser removido.
        no = aux->prox;  // O ultimo no sera removido.
        aux->prox = NULL;  // O penultimo no agora aponta para NULL.
    }
    free(no);  // Libera a memoria do no removido.

    return 1;  // Remocao realizada com sucesso.
}

/*
   Remove o no com o valor especificado.
   Retorna 0 caso o valor nao seja encontrado, e 1 caso a remocao seja bem-sucedida.
*/
int remove_valor(Lista *p_l, elem_t e) {
    No_lista *no, *aux = *p_l;

    if (vazia(p_l)) {  // Se a lista estiver vazia, nao ha nada para remover.
        return 0;
    }

    // Se o valor a ser removido for o primeiro no.
    if (aux->info == e) {
        no = aux;
        *p_l = aux->prox;  // O primeiro no sera o proximo no da lista.
    }
    else {
        // Percorre a lista para encontrar o valor.
        while (aux->prox != NULL && aux->prox->info != e) {
            aux = aux->prox;
        }
        // Se o valor for encontrado.
        if (aux->prox != NULL) {
            no = aux->prox;  // O no a ser removido.
            aux->prox = no->prox;  // O no anterior agora aponta para o proximo do no removido.
        } else {
            return 0;  // O valor nao foi encontrado.
        }
    }
    free(no);  // Libera a memoria do no removido.
    return 1;  // Remocao realizada com sucesso.
}

/*
   Inverte os elementos da lista.
   Após a execucao, a lista estara invertida.
*/
void inverte(Lista *p_l) {
    No_lista *aux = *p_l, *ant = NULL, *prox = NULL;

    if (vazia(p_l))  // Se a lista estiver vazia, nao ha nada para inverter.
        return;

    // Percorre a lista invertendo as ligacoes entre os nos.
    while (aux != NULL) {
        prox = aux->prox;  // Armazena o proximo no.
        aux->prox = ant;  // Inverte a direcao do ponteiro.
        ant = aux;  // O no atual se torna o anterior.
        aux = prox;  // Move para o proximo no.
    }

    *p_l = ant;  // O ultimo no (agora o primeiro) sera o novo inicio da lista.
}

/*
   Libera todos os nos da lista, tornando a lista vazia.
   A memoria de cada no sera liberada.
*/
void libera(Lista *p_l) {
    *p_l = NULL;  // Simplesmente define o ponteiro da lista como NULL, "apagando" a lista.
}

/*
   Exibe o conteudo da lista, imprimindo os valores dos nos.
   A funcao percorre a lista e imprime cada elemento.
*/
void exibe(Lista *p_l) {
    No_lista *aux = *p_l;

    // Percorre a lista e imprime cada valor.
    while (aux != NULL) {
        printf("%d ", aux->info);  // Imprime o valor do no.
        aux = aux->prox;  // Move para o proximo no.
    }
}
