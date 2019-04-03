#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{

	 vetor *nomes = vetor_novo();
	 //int num_cartas[43]= {1};
	 v_elemento *elemento;
	 v_elemento *elemento_nomes;
		for(int i=0;i<vrem->tamanho;i++){
		    elemento->str = vetor_elemento(vrem,i);
			//printf("\n%s",elemento->str);
			vetor_insere(nomes,elemento->str,-1);
			}
		for(int i=0;i<vdest->tamanho;i++){
		    elemento->str = vetor_elemento(vdest,i);
			//printf("\n%s",elemento->str);
			vetor_insere(nomes,elemento->str,-1);
			}

		for(int i=0;i<nomes->tamanho;i++){
			elemento_nomes->str= vetor_elemento(nomes,i);
			for(int j=0;j<nomes->tamanho;j++){
				 elemento->str = vetor_elemento(vrem,j);
				 if(strcmp(elemento->str,elemento_nomes->str)==0){
					 vetor_remove(nomes,j);
					 j--;
				 }
				//printf("\n%s",elemento_nomes->str);
			}
		

		return nomes;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor* vrem;
	vetor* vdest;
	vetor *vcp_dest;
	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_remetente_destinatario(vrem, vdest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else {
		printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);

	return 0;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}
