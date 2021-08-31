#include "mmu.h"
#include "constantes.h"

BlocoMemoria buscarNasMemorias(Endereco e, BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3) {
	int posicaoCache1 = e.endBloco % TAMANHO_CACHE1;
	int posicaoCache2 = e.endBloco % TAMANHO_CACHE2;
	int posicaoCache3 = e.endBloco % TAMANHO_CACHE3;
	int custo = 0;

	custo += CUSTO_CACHE1;
	if (cache1[posicaoCache1].endBloco == e.endBloco) {
		cache1[posicaoCache1].custo = custo;
		cache1[posicaoCache1].cacheHit = CACHE1;

		return cache1[posicaoCache1];
	} else {
		custo += CUSTO_CACHE2;
		if (cache2[posicaoCache2].endBloco == e.endBloco) {
			cache2[posicaoCache2].cacheHit = CACHE2;

			return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, cache1, cache2, custo);
		} else {
			custo += CUSTO_CACHE3;
			if (cache3[posicaoCache3].endBloco == e.endBloco) {
				cache3[posicaoCache3].cacheHit = CACHE3;

				testaMemoria1Memoria2(posicaoCache2, posicaoCache3, cache2, cache3, custo);
				return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, cache1, cache2, custo);
			} else {
				custo += CUSTO_RAM;

				RAM[e.endBloco].cacheHit = CRAM;

				if (cache3[posicaoCache3].atualizado) {
					cache3[posicaoCache3].atualizado = 0;
					testaMemoria1Memoria2(posicaoCache3, e.endBloco, cache3, RAM, custo);
				} else {
					cache3[posicaoCache3] = RAM[e.endBloco];
				}
				testaMemoria1Memoria2(posicaoCache2, posicaoCache3, cache2, cache3, custo);
				return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, cache1, cache2, custo);
			}
		}
	}
}

BlocoMemoria buscarNasMemoriasAssociativo(Endereco e, BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3) {
	int posicaoCache1, posicaoCache2, posicaoCache3;
	int i;
	int custo = 0;

	custo += CUSTO_CACHE1;
	for (i = 0; i < TAMANHO_CACHE1; i++) {
		if (cache1[i].endBloco == e.endBloco) {
			cache1[i].custo = custo;
			cache1[i].cacheHit = CACHE1;

			return cache1[i];
		}
	}

	custo += CUSTO_CACHE2;
	for (i = 0; i < TAMANHO_CACHE2; i++) {
		if (cache2[i].endBloco == e.endBloco) {
			cache2[i].cacheHit = CACHE2;

			posicaoCache1 = buscaLRU(cache1, TAMANHO_CACHE1);
			return testaMemoria1Memoria2(posicaoCache1, i, cache1, cache2, custo);
		}
	}

	custo += CUSTO_CACHE3;
	for (i = 0; i < TAMANHO_CACHE3; i++) {
		if (cache3[i].endBloco == e.endBloco) {
			cache3[i].cacheHit = CACHE3;

			posicaoCache1 = buscaLRU(cache1, TAMANHO_CACHE1);
			posicaoCache2 = buscaLRU(cache2, TAMANHO_CACHE2);
			testaMemoria1Memoria2(posicaoCache2, i, cache2, cache3, custo);
			return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, cache1, cache2, custo);
		}
	}

	custo += CUSTO_RAM;
	
	RAM[e.endBloco].cacheHit = CRAM;

	posicaoCache1 = buscaLRU(cache1, TAMANHO_CACHE1);
	posicaoCache2 = buscaLRU(cache2, TAMANHO_CACHE2);
	posicaoCache3 = buscaLRU(cache3, TAMANHO_CACHE3);

	if (cache3[posicaoCache3].atualizado) {
		cache3[posicaoCache3].atualizado = 0;
		RAM[cache3[posicaoCache3].endBloco] = cache3[posicaoCache3];
		//testaMemoria1Memoria2(posicaoCache3, e.endBloco, cache3, RAM, custo);
	}// else {
		cache3[posicaoCache3] = RAM[e.endBloco];
	//}
	testaMemoria1Memoria2(posicaoCache2, posicaoCache3, cache2, cache3, custo);
	return testaMemoria1Memoria2(posicaoCache1, posicaoCache2, cache1, cache2, custo);
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

void atualizarRAM(BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3) {
	int i;

	for (i = 0; i < TAMANHO_CACHE1; i++) {
		if (cache1[i].atualizado) {
			RAM[cache1[i].endBloco] = cache1[i];
		}
	}

	for (i = 0; i < TAMANHO_CACHE2; i++) {
		if (cache2[i].atualizado) {
			RAM[cache2[i].endBloco] = cache2[i];
		}
	}

	for (i = 0; i < TAMANHO_CACHE3; i++) {
		if (cache3[i].atualizado) {
			RAM[cache3[i].endBloco] = cache3[i];
		}
	}

}