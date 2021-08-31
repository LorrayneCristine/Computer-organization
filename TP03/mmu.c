#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"
#include "constantes.h"

BlocoMemoria buscarNasMemorias(Endereco e, Memoria *memoria) {
	int posicaoCache1 = e.endBloco % TAMANHO_CACHE1;
	int posicaoCache2 = e.endBloco % TAMANHO_CACHE2;
	int posicaoCache3 = e.endBloco % TAMANHO_CACHE3;
	int custo = 0;

	custo += CUSTO_CACHE1;
	if (memoria->cache1[posicaoCache1].endBloco == e.endBloco) {
		memoria->cache1[posicaoCache1].custo = custo;
		memoria->cache1[posicaoCache1].cacheHit = CACHE1;

		return memoria->cache1[posicaoCache1];
	} else {
		custo += CUSTO_CACHE2;
		if (memoria->cache2[posicaoCache2].endBloco == e.endBloco) {
			memoria->cache2[posicaoCache2].cacheHit = CACHE2;

			return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);
		} else {
			custo += CUSTO_CACHE3;
			if (memoria->cache3[posicaoCache3].endBloco == e.endBloco) {
				memoria->cache3[posicaoCache3].cacheHit = CACHE3;

				testaMemoria1Memoria2(posicaoCache2, posicaoCache3, memoria->cache2, memoria->cache3, custo);
				return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);
			} else {
				custo += CUSTO_RAM;

				memoria->RAM[e.endBloco].cacheHit = CRAM;

				if (memoria->cache3[posicaoCache3].atualizado) {
					memoria->cache3[posicaoCache3].atualizado = 0;
					testaMemoria1Memoria2(posicaoCache3, e.endBloco, memoria->cache3, memoria->RAM, custo);
				} else {
					memoria->cache3[posicaoCache3] = memoria->RAM[e.endBloco];
				}
				testaMemoria1Memoria2(posicaoCache2, posicaoCache3, memoria->cache2, memoria->cache3, custo);
				return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);
			}
		}
	}
}

BlocoMemoria buscarNasMemoriasAssociativo(Endereco e, Memoria *memoria) {
	int posicaoCache1, posicaoCache2, posicaoCache3, posicaoRAM;
	int i;
	int custo = 0;

	custo += CUSTO_CACHE1;
	for (i = 0; i < TAMANHO_CACHE1; i++) {
		if (memoria->cache1[i].endBloco == e.endBloco) {
			memoria->cache1[i].custo = custo;
			memoria->cache1[i].cacheHit = CACHE1;

			return memoria->cache1[i];
		}
	}

	posicaoCache1 = buscaLRU(memoria->cache1, TAMANHO_CACHE1);

	custo += CUSTO_CACHE2;
	for (i = 0; i < TAMANHO_CACHE2; i++) {
		if (memoria->cache2[i].endBloco == e.endBloco) {
			memoria->cache2[i].cacheHit = CACHE2;

			//posicaoCache1 = buscaLRU(memoria->cache1, TAMANHO_CACHE1);
			return testaMemoria1Memoria2(posicaoCache1, i, memoria->cache1, memoria->cache2, custo);
		}
	}

	posicaoCache2 = buscaLRU(memoria->cache2, TAMANHO_CACHE2);

	custo += CUSTO_CACHE3;
	for (i = 0; i < TAMANHO_CACHE3; i++) {
		if (memoria->cache3[i].endBloco == e.endBloco) {
			memoria->cache3[i].cacheHit = CACHE3;

			//posicaoCache1 = buscaLRU(memoria->cache1, TAMANHO_CACHE1);
			//posicaoCache2 = buscaLRU(memoria->cache2, TAMANHO_CACHE2);
			testaMemoria1Memoria2(posicaoCache2, i, memoria->cache2, memoria->cache3, custo);
			return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);
		}
	}

	posicaoCache3 = buscaLRU(memoria->cache3, TAMANHO_CACHE3);

	custo += CUSTO_RAM;
	for (i = 0; i < TAMANHO_RAM; i++) {
		if (memoria->RAM[i].endBloco == e.endBloco) {
			memoria->RAM[i].cacheHit = CRAM;

			//posicaoCache1 = buscaLRU(memoria->cache1, TAMANHO_CACHE1);
			//posicaoCache2 = buscaLRU(memoria->cache2, TAMANHO_CACHE2);
			//posicaoCache3 = buscaLRU(memoria->cache3, TAMANHO_CACHE3);

			if (memoria->cache3[posicaoCache3].atualizado) {
				for(int j = 0; j < TAMANHO_RAM; j++){
					if(memoria->cache3[posicaoCache3].endBloco == memoria->RAM[j].endBloco){
							//memoria->cache3[posicaoCache3].atualizado = 0;
							memoria->RAM[j] = memoria->cache3[posicaoCache3];
					}
				}
			
			}
			memoria->cache3[posicaoCache3] = memoria->RAM[i];

			//testaMemoria1Memoria2(posicaoCache3, i, memoria->cache3, memoria->RAM, custo);
			testaMemoria1Memoria2(posicaoCache2, posicaoCache3, memoria->cache2, memoria->cache3, custo);
			return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);
		}
	}
	
	BlocoMemoria aux;
	FILE *arquivo;
	int posicaoHD = e.endBloco * sizeof(BlocoMemoria);

	posicaoRAM = buscaLRU(memoria->RAM, TAMANHO_RAM);
	custo += CUSTO_HD;

	arquivo = fopen("hd.bin", "r+b");

	if (arquivo != NULL) {
		fseek(arquivo, posicaoHD, SEEK_SET);
		fread(&aux, sizeof(BlocoMemoria), 1, arquivo);
		//fclose(arquivo);

		if (memoria->RAM[posicaoRAM].atualizado) {
			memoria->RAM[posicaoRAM].atualizado = 0;

			fseek(arquivo, memoria->RAM[posicaoRAM].endBloco * sizeof(BlocoMemoria), SEEK_SET);
			fwrite(&(memoria->RAM[posicaoRAM]), sizeof(BlocoMemoria), 1, arquivo);

		}
		fclose(arquivo);
		memoria->RAM[posicaoRAM] = aux;

		if (memoria->cache3[posicaoCache3].atualizado) {
			for(int j = 0; j < TAMANHO_RAM; j++){
				if(memoria->cache3[posicaoCache3].endBloco == memoria->RAM[j].endBloco){
						//memoria->cache3[posicaoCache3].atualizado = 0;
						memoria->RAM[j] = memoria->cache3[posicaoCache3];
				}
			}	
		}
		memoria->cache3[posicaoCache3] = memoria->RAM[posicaoRAM];


		testaMemoria1Memoria2(posicaoCache2, posicaoCache3, memoria->cache2, memoria->cache3, custo);
		return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, memoria->cache1, memoria->cache2, custo);



	} else {
		printf("\n\n\n\t\t\tERRO CRITICO: CAD� O HD, CARA????????????????????????????????");
		exit(1);
	}
}

BlocoMemoria testaMemoria1Memoria2(int posicaoBloco1, int posicaoBloco2, BlocoMemoria *bloco1, BlocoMemoria *bloco2, int custo) {
	BlocoMemoria aux = bloco1[posicaoBloco1];
	bloco1[posicaoBloco1] = bloco2[posicaoBloco2];
	bloco2[posicaoBloco2] = aux;

	bloco1[posicaoBloco1].custo = custo;

	return bloco1[posicaoBloco1];
}

int buscaLRU(BlocoMemoria *bloco, int tamanho) {
	int i, LRU = 0;
	
	for (i = 1; i < tamanho; i++) {
		if (bloco[i].tempoChamado < bloco[LRU].tempoChamado) {
			LRU = i;
		}
	}

	return LRU;
}

/*void atualizarRAM(Memoria *memoria) {
	int i;

	for (i = 0; i < TAMANHO_CACHE1; i++) {
		if (memoria->cache1[i].atualizado) {
			memoria->RAM[memoria->cache1[i].endBloco] = memoria->cache1[i];
		}
	}

	for (i = 0; i < TAMANHO_CACHE2; i++) {
		if (memoria->cache2[i].atualizado) {
			memoria->RAM[memoria->cache2[i].endBloco] = memoria->cache2[i];
		}
	}

	for (i = 0; i < TAMANHO_CACHE3; i++) {
		if (memoria->cache3[i].atualizado) {
			memoria->RAM[memoria->cache3[i].endBloco] = memoria-> cache3[i];
		}
	}

}*/


void atualizarHD(Memoria *memoria) {
	int i;
	FILE *arquivo;
	int aux;

	arquivo = fopen("hd.bin", "r+b");
	
	if(arquivo != NULL){
		for (i = 0; i < TAMANHO_CACHE1; i++) {
			if (memoria->cache1[i].atualizado) {
				aux = memoria->cache1[i].endBloco * sizeof(BlocoMemoria);
				fseek(arquivo, aux, SEEK_SET);
				fwrite(&(memoria->cache1[i]), sizeof(BlocoMemoria), 1, arquivo);

			}
		}

		for (i = 0; i < TAMANHO_CACHE2; i++) {
			if (memoria->cache2[i].atualizado) {
				aux = memoria->cache2[i].endBloco * sizeof(BlocoMemoria);
				fseek(arquivo, aux, SEEK_SET);
				fwrite(&(memoria->cache2[i]), sizeof(BlocoMemoria), 1, arquivo);			
			}
		}

		for (i = 0; i < TAMANHO_CACHE3; i++) {
			if (memoria->cache3[i].atualizado) {
				aux = memoria->cache3[i].endBloco * sizeof(BlocoMemoria);
				fseek(arquivo, aux, SEEK_SET);
				fwrite(&(memoria->cache3[i]), sizeof(BlocoMemoria), 1, arquivo);			
			}
		}

		for (i = 0; i < TAMANHO_RAM; i++) {
			if (memoria->RAM[i].atualizado) {
				aux = memoria->RAM[i].endBloco * sizeof(BlocoMemoria);
				fseek(arquivo, aux, SEEK_SET);
				fwrite(&(memoria->RAM[i]), sizeof(BlocoMemoria), 1, arquivo);			
			}
		}

		fclose(arquivo);
	}else{
		printf("Favor comprar um HD irmão\n");
		exit(1);

	}

}