#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

void quickSort(char items[][50], int left, int right);

void quickSort(char items[][50], int left, int right)
{
  int i, j;
  char *x;
  char temp[60];
  int aux;
  i = left;
  j = right;
  x = items[(left+right)/2];

  do {
    while((strcmp(items[i],x) < 0) && (i < right)) {
       i++;
    }
    while((strcmp(items[j],x) > 0) && (j > left)) {
        j--;
    }
    if(i <= j) {
      strcpy(temp, items[i]);
      strcpy(items[i], items[j]);
      strcpy(items[j], temp);
      i++;
      j--;
   }
  } while(i <= j);

  if(left < j) {
     quickSort(items, left, j);
  }
  if(i < right) {
     quickSort(items, i, right);
  }
}

/*** problema 1.1 ***/
lista* filtra_titulos(lista *lista1, lista *lista2)
{
	int inserir;
	lista* lista_filtrada = lista_nova();
	for(int i=0;i<lista1->tamanho;i++){
		inserir=1;
		l_elemento* elem1= lista_elemento(lista1,i);
		for(int j=0;j<lista2->tamanho;j++){
			l_elemento* elem2= lista_elemento(lista2,j);
			if(strcmp(elem1->str,elem2->str)==0){
				inserir=0;
			}
		}
		if(inserir==1){
			elem1= lista_insere(lista_filtrada,elem1->str,NULL);
		}

	}

	if(lista_filtrada->tamanho==0)
		return NULL;
	else
		return lista_filtrada;
	
	

}

/*** problema 1.2 ***/
int retira_comecados_por(lista *lst, char *inicio)
{
	int retirados=0;
	for(int i=0;i<lst->tamanho;i++){
		l_elemento *elem = lista_elemento(lst,i);
		if(strncmp(inicio,elem->str,1) == 0) {
			elem= lista_remove(lst,elem);
			retirados++;
			i--; //quando se remove o elemento na posicao i+1 passa para i!
		}
	}
	if(retirados==0)
		return 0;
	else
		return retirados;
}

/*** problema 1.3 ***/
int insere_na_pilha(pilha *p, char *titulo)
{
	int tamanho_pilha= p->tamanho;
	char str[32][40];
	pilhaItem *item;
	for(int i=0;i<tamanho_pilha;i++){
		item->elemento = pilha_top(p);
		strcpy(str[i],item->elemento);
		pilha_pop(p);
	 		
	}
	for(int i=0;i<tamanho_pilha;i++){
		printf("\nstr[%d]= %s",i,str[i]);
	}


	return 0;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}

	return l;
}

pilha* lerParaPilha(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	pilha* p;

	if (ficheiro == NULL)
		return NULL;

	p = pilha_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		pilha_push(p,buffer);
	}
	return p;
}

void imprimeLista(lista *l, unsigned int n) {
	if (l->tamanho<n)
		printf("ERRO... Lista possui menos de %d elementos\n",n);
	unsigned int i;
	l_elemento *aux = l->inicio;
	for (i=0; i<n; i++) {
		printf("%dº Livro: %s\n", i+1,aux->str);
		aux = aux->proximo;
	}
}

int main()
{
	FILE *f;
	lista *l1=NULL, *l2=NULL, *l=NULL;
	pilha *p;
	int nmov, res;
	char *tit1;

	/* testes */
	f = fopen("livros1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l1 = lerParaLista(f);
	fclose(f);

	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lerParaLista(f);
	fclose(f);

	/* inicio teste prob1.1 */
	l = filtra_titulos(l1, l2);
	if(l) {
		printf("\nLista resultante contem %d livros.\n", lista_tamanho(l));
		if(lista_tamanho(l) != 12)
			printf("ERRO.. Tamanho da lista incorreto(tamanho: %d; esperado: 12)\n", lista_tamanho(l));
		else
			imprimeLista(l,lista_tamanho(l));
	}
	else
		printf("\nERRO.. filtra_titulos retornou NULL\n");
	/* fim teste prob1.1 */


	/* inicio teste prob1.2 */
	f = fopen("livros.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	lista_apaga(l);
	l = lerParaLista(f);
	fclose(f);

	nmov = retira_comecados_por(l, "A");
	printf("\nForam retirados %d livros\n", nmov);
	printf("A lista contém %d livros\n", lista_tamanho(l));
	if (nmov!=146)
		printf("ERRO.. Numero de livros removidos incorreto (removidos: %d; esperado: 146\n",nmov);
	else if(lista_tamanho(l) != 389)
		printf("ERRO.. Lista incorreta (tamanho: %d; esperado: 389)\n", lista_tamanho(l));
	else
		printf("9º livro da lista: %s\n", lista_elemento(l,8)->str);
	/* fim teste prob1.2 */


	/* inicio teste prob1.3 */
	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	p = lerParaPilha(f);
	fclose(f);

	tit1="Fora de Horas";
	res = insere_na_pilha(p, tit1);

	if (res==0) {
		printf("\n'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("\nERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n",pilha_tamanho(p));
	else {
		printf("\n'%s' foi inserido na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}

	tit1="Mundo incompleto";
	res = insere_na_pilha(p, tit1);

	if (res==0) {
		printf("'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("ERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n",pilha_tamanho(p));
	else {
			printf("'%s' foi inserido na pilha\n", tit1);
			printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
		}
	puts("");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	pilha_apaga(p);

	return 0;
}
