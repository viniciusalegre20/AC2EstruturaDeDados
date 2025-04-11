/*
 * Programa para testar as operações de lista
 */

#include<stdio.h>
#include "lista_dinamica.h"

int main(){
  int num, opcao;
  Lista l;

  cria(&l);
  
  opcao = 1;  
  while(opcao <= 10 && opcao > 0){
    
    printf("\n 1 - insere um numero no inicio da lista");
    printf("\n 2 - insere um numero no fim da lista");
    printf("\n 3 - insere um numero de maneira ordenada");
    printf("\n 4 - verifica se a lista está ordenada");
    printf("\n 5 - ordena a lista");
    printf("\n 6 - remove o elemento que esta no inicio da lista");
    printf("\n 7 - remove o elemento que esta no fim da lista");
    printf("\n 8 - remove um valor determinado");
    printf("\n 9 - inverte");
    printf("\n 10 - exibe a lista");
    printf("\n qualquer outro numero para sair");
    printf("\n\nEntre com uma das opcoes acima: ");
    
    scanf("%d", &opcao);
    
    switch (opcao){
    case 1:
      //printf("\n\nEntre com o numero a ser inserido: ");
      scanf("%d", &num);
      insere_inicio(&l, num);
      break;
    case 2:
      //printf("\n\nEntre com o numero a ser inserido: ");
      scanf("%d", &num);
      insere_fim(&l, num);
      break;
    case 3:
      //printf("\n\nEntre com o numero a ser inserido: ");
      scanf("%d", &num);
      if (!ordenada(&l))
	ordena(&l);
      insere_ordenado(&l, num);
      break;
    case 4: 
      if (ordenada(&l))
	       printf("\nlista ordenada");
      else 
	       printf("\nlista NAO ordenada");
      break;
    case 5: 
      if (!ordenada(&l))
	       ordena(&l);
      break;
    case 6:
      if (remove_inicio(&l, &num))
	       printf("\nNumero removido: %d\n", num);
      else
	       printf("\nLista vazia");
      break;
    case 7:
      if (remove_fim(&l, &num))
	       printf("\nNumero removido: %d\n", num);
      else
	       printf("\nLista vazia");
      break;
    case 8:
      //printf("\n\nEntre com o numero a ser removido: ");
      scanf("%d", &num);
      if (!remove_valor(&l, num))
	       printf("Numero nao encontrado");
      break;      
    case 9:
      inverte(&l);
      break;            
    case 10: exibe(&l); break;
    }
    
    exibe(&l);
    printf("\n\n");    
  }    
  libera(&l);
  return 0;
}
