#include "funcao.h"
#include <stdio.h>

int main(){

	int *RAM, qtd = 100;
	int **matrizInstrucoes, escolha;

	RAM = NULL;
	RAM = alocaVetor(RAM, qtd);

	matrizInstrucoes = NULL;
	matrizInstrucoes = alocaMatriz(matrizInstrucoes);

	MontarRam(RAM);
	menu(&escolha);
	chamaFuncao(matrizInstrucoes, RAM, escolha);



	return 0;
}
    
