#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mmu.h"
#include "constantes.h"

//cahce 1  /cahce 2  /cahce 3 
// cache 1 end 5558
// cache 2 end 225

// 20 RAM
// 
//hit 0 miss 400// hit 1 miss 1

void montarBlocoMemoriaCheio(BlocoMemoria *bloco, int tamanho, int tipo);
void montarBlocoMemoriaVazio(BlocoMemoria *bloco, int tamanho);

void maquina(Instrucao *memoriaInstrucoes, Memoria *memoria);
void montarInstrucoesProgramaAleatorio(Instrucao *memoriaInstrucoes);
void montarProgramaGerador(Instrucao *memoriaInstrucoes);

void montarHD();

int main() {
	//Instrucao memoriaInstrucoes[TAMANHO_PROGRAMA];
	//Memoria memoria;
	//BlocoMemoria RAM[TAMANHO_RAM], cache1[TAMANHO_CACHE1], cache2[TAMANHO_CACHE2], cache3[TAMANHO_CACHE3];

	/*montarBlocoMemoriaCheio(memoria.RAM, TAMANHO_RAM, CRAM);
	montarBlocoMemoriaVazio(memoria.cache1, TAMANHO_CACHE1);
	montarBlocoMemoriaVazio(memoria.cache2, TAMANHO_CACHE2);
	montarBlocoMemoriaVazio(memoria.cache3, TAMANHO_CACHE3);

	//montarInstrucoesProgramaAleatorio(memoriaInstrucoes);
	montarProgramaGerador(memoriaInstrucoes);*/

	/*for (int i = 0; i < TAMANHO_PROGRAMA; i++) {
		printf("%d", memoriaInstrucoes[i].opcode);
		printf(" | %d %d", memoriaInstrucoes[i].end1.endBloco, memoriaInstrucoes[i].end1.endPalavra);
		printf(" | %d %d", memoriaInstrucoes[i].end2.endBloco, memoriaInstrucoes[i].end2.endPalavra);
		printf(" | %d %d\n", memoriaInstrucoes[i].end3.endBloco, memoriaInstrucoes[i].end3.endPalavra);
	}*/

	//maquina(memoriaInstrucoes, &memoria);

	montarHD();

	return 0;
}

void montarBlocoMemoriaCheio(BlocoMemoria *bloco, int tamanho, int tipo) {
	srand(time(NULL));
	for (int i = 0; i < tamanho; i++) {
		bloco[i].tempoChamado = 0;
		bloco[i].atualizado = 0;
		bloco[i].cacheHit = CRAM;
		if (tipo == CRAM) {
			bloco[i].endBloco = i;	
		} else {
			bloco[i].endBloco = -1;
		}
		for (int j = 0; j < QDE_PALAVRAS_BLOCO; j++) {
			bloco[i].palavra[j] = rand() % 1000000;
		}
	}
}

void montarBlocoMemoriaVazio(BlocoMemoria *bloco, int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		bloco[i].endBloco = -1;
		bloco[i].tempoChamado = 0;
		bloco[i].atualizado = 0;
		bloco[i].cacheHit = 0;
	}
}

void maquina(Instrucao *memoriaInstrucoes, Memoria *memoria) {
	int PC = 0, opcode = 0, custo = 0, tempoExecucao = 1;
	int hitC1 = 0, missC1 = 0, hitC2 = 0, missC2 = 0, hitC3 = 0, missC3 = 0, hitR = 0;

	while (opcode != HALT) {
		Instrucao umaInstrucao = memoriaInstrucoes[PC];
		opcode = umaInstrucao.opcode;

		if (opcode != -1) {
			//BlocoMemoria dadoMemoriaEnd1 = buscarNasMemorias(umaInstrucao.end1, RAM, cache1, cache2, cache3);
			BlocoMemoria dadoMemoriaEnd1 = buscarNasMemoriasAssociativo(umaInstrucao.end1, memoria);
			dadoMemoriaEnd1.tempoChamado = tempoExecucao;
			for (int i = 0; i < TAMANHO_CACHE1; i++) {
				if (dadoMemoriaEnd1.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd1;
					//printf("\t\t1 t:%d i:%d", memoria->cache1[i].tempoChamado, i);
					break;
				}
			}

			//BlocoMemoria dadoMemoriaEnd2 = buscarNasMemorias(umaInstrucao.end2, RAM, cache1, cache2, cache3);
			BlocoMemoria dadoMemoriaEnd2 = buscarNasMemoriasAssociativo(umaInstrucao.end2, memoria);
			dadoMemoriaEnd2.tempoChamado = tempoExecucao;
			for (int i = 0; i < TAMANHO_CACHE1; i++) {
				if (dadoMemoriaEnd2.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd2;
					//printf("\t\t2 t:%d i:%d", cache1[i].tempoChamado, i);
					break;
				}
			}

			//BlocoMemoria dadoMemoriaEnd3 = buscarNasMemorias(umaInstrucao.end3, RAM, cache1, cache2, cache3);
			BlocoMemoria dadoMemoriaEnd3 = buscarNasMemoriasAssociativo(umaInstrucao.end3, memoria);
			dadoMemoriaEnd3.tempoChamado = tempoExecucao;
			for (int i = 0; i < TAMANHO_CACHE1; i++) {
				if (dadoMemoriaEnd3.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd3;
					//printf("\t\t3 t:%d i:%d", cache1[i].tempoChamado, i);
					break;
				}
			}

			custo += dadoMemoriaEnd1.custo;
			custo += dadoMemoriaEnd2.custo;
			custo += dadoMemoriaEnd3.custo;

			switch (dadoMemoriaEnd1.cacheHit) {
				case CACHE1:
					hitC1++;
					break;
				case CACHE2:
					missC1++;
					hitC2++;
					break;
				case CACHE3:
					missC1++;
					missC2++;
					hitC3++;
					break;
				case CRAM:
					missC1++;
					missC2++;
					missC3++;
					hitR++;
					break;
			}

			switch (dadoMemoriaEnd2.cacheHit) {
				case CACHE1:
					hitC1++;
					break;
				case CACHE2:
					missC1++;
					hitC2++;
					break;
				case CACHE3:
					missC1++;
					missC2++;
					hitC3++;
					break;
				case CRAM:
					missC1++;
					missC2++;
					missC3++;
					hitR++;
					break;
			}

			switch (dadoMemoriaEnd3.cacheHit) {
				case CACHE1:
					hitC1++;
					break;
				case CACHE2:
					missC1++;
					hitC2++;
					break;
				case CACHE3:
					missC1++;
					missC2++;
					hitC3++;
					break;
				case CRAM:
					missC1++;
					missC2++;
					missC3++;
					hitR++;
					break;
			}

			printf("\n\nCusto ate o momento do programa em execucao: %d\n", custo);
			printf("\tHits e Misses ate o momento:\n");
			printf("\tHit C1 | Miss C1 | Hit C2 | Miss C2 | Hit C3 | Miss C3 | Hit RAM\n");
			printf("\t%6d | %7d | %6d | %7d | %6d | %7d | %7d\n\n", hitC1, missC1, hitC2, missC2, hitC3, missC3, hitR);

			int conteudo1, conteudo2, resul;
			switch (opcode) {
				case SOMA:
					conteudo1 = dadoMemoriaEnd1.palavra[umaInstrucao.end1.endPalavra];
					conteudo2 = dadoMemoriaEnd2.palavra[umaInstrucao.end2.endPalavra];
					resul = conteudo1 + conteudo2;

					dadoMemoriaEnd3.palavra[umaInstrucao.end3.endPalavra] = resul;
					dadoMemoriaEnd3.atualizado = 1;

					printf("\t\tSomando %d + %d = %d\n", conteudo1, conteudo2, resul);
					break;
				case SUBTRACAO:
					conteudo1 = dadoMemoriaEnd1.palavra[umaInstrucao.end1.endPalavra];
					conteudo2 = dadoMemoriaEnd2.palavra[umaInstrucao.end2.endPalavra];
					resul = conteudo1 - conteudo2;

					dadoMemoriaEnd3.palavra[umaInstrucao.end3.endPalavra] = resul;
					dadoMemoriaEnd3.atualizado = 1;

					printf("\t\tSubtraindo %d - %d = %d\n", conteudo1, conteudo2, resul);
					break;
				case ESCREVER:
					printf("\n\t\tImpossivel realizar a acao de escrita na memoria.\n");
					break;
				case LER:
					printf("\n\t\tImpossivel realizar a acao de leitura da memoria.\n");
					break;
			}

			for (int i = 0; i < TAMANHO_CACHE1; i++) {
				if (dadoMemoriaEnd1.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd1;
					//printf("\t\t1 t:%d i:%d", cache1[i].tempoChamado, i);
				}

				if (dadoMemoriaEnd2.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd2;
					//printf("\t\t2 t:%d i:%d", cache1[i].tempoChamado, i);
				}

				if (dadoMemoriaEnd3.endBloco == memoria->cache1[i].endBloco) {
					memoria->cache1[i] = dadoMemoriaEnd3;
					//printf("\t\t3 t:%d i:%d", cache1[i].tempoChamado, i);
				}
			}
			//printf("\n");
		}

		PC++;
		tempoExecucao++;
	}

	atualizarRAM(memoria);

	printf("\n\nCusto total do programa: %d\n", custo);
	printf("\tHits e Misses do programa:\n");
	printf("\tHit C1 | Miss C1 | Hit C2 | Miss C2 | Hit C3 | Miss C3 | Hit RAM\n");
	printf("\t%6d | %7d | %6d | %7d | %6d | %7d | %7d\n", hitC1, missC1, hitC2, missC2, hitC3, missC3, hitR);
}

void montarProgramaGerador(Instrucao *memoriaInstrucoes) {
	FILE *arquivo;
	char aux[100], *token;

	arquivo = fopen("programa.txt", "r");
	if (arquivo != NULL) {
		for (int i = 0; i < TAMANHO_PROGRAMA-1; i++) {
			fgets(aux, 100, arquivo);

			token = strtok(aux, ":");
			memoriaInstrucoes[i].opcode = atoi(token);

			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end1.endBloco = atoi(token);
			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end1.endPalavra = atoi(token) % QDE_PALAVRAS_BLOCO;

			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end2.endBloco = atoi(token);
			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end2.endPalavra = atoi(token) % QDE_PALAVRAS_BLOCO;

			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end3.endBloco = atoi(token);
			token = strtok(NULL, ":");
			memoriaInstrucoes[i].end3.endPalavra = atoi(token) % QDE_PALAVRAS_BLOCO;
		}

		memoriaInstrucoes[TAMANHO_PROGRAMA-1].opcode = HALT;

		fclose(arquivo);
	} else {
		printf("Falha ao abrir arquivo");
		exit(1);
	}
}

void montarInstrucoesProgramaAleatorio(Instrucao *memoriaInstrucoes) {
	srand(time(NULL));
	for (int i = 0; i < TAMANHO_PROGRAMA-1; i++) {
		memoriaInstrucoes[i].opcode = rand() % 4;

		memoriaInstrucoes[i].end1.endBloco = rand() % TAMANHO_RAM;
		memoriaInstrucoes[i].end1.endPalavra = rand() % QDE_PALAVRAS_BLOCO;

		memoriaInstrucoes[i].end2.endBloco = rand() % TAMANHO_RAM;
		memoriaInstrucoes[i].end2.endPalavra = rand() % QDE_PALAVRAS_BLOCO;

		memoriaInstrucoes[i].end3.endBloco = rand() % TAMANHO_RAM;
		memoriaInstrucoes[i].end3.endPalavra = rand() % QDE_PALAVRAS_BLOCO;
	}

	memoriaInstrucoes[TAMANHO_PROGRAMA-1].opcode = HALT;
}

void montarHD(){
	FILE *arq;
	BlocoMemoria aux;

	arq = fopen("HD.txt", "rb");

	if(arq == NULL){

		arq = fopen("HD.txt", "wb");

		for(int i = 0; i < TAMANHO_HD; i++){

			aux.endBloco = i;	
			aux.tempoChamado = 0;
			aux.atualizado = 0;
			aux.cacheHit = HD;

			srand(time(NULL));
			for (int j = 0; j < QDE_PALAVRAS_BLOCO; j++) {
				aux.palavra[j] = rand() % 1000000;
			}


     		fwrite (&aux, sizeof(BlocoMemoria), 1, arq);		
		}

		fclose(arq);

	}



}