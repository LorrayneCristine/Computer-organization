#ifndef mmu_h
#define mmu_h

#include "constantes.h"

typedef struct {
	int endBloco;
	int endPalavra;
} Endereco;

typedef struct {
	int palavra[QDE_PALAVRAS_BLOCO];
	int endBloco, atualizado;
	int custo, cacheHit;
	int tempoChamado;
} BlocoMemoria;

typedef struct {
	Endereco end1, end2, end3;
	int opcode;
} Instrucao;

BlocoMemoria buscarNasMemorias(Endereco e, BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3);

BlocoMemoria buscarNasMemoriasAssociativo(Endereco e, BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3);
	
BlocoMemoria testaMemoria1Memoria2(int posicaoBloco1, int posicaoBloco2, BlocoMemoria *bloco1, BlocoMemoria *bloco2, int custo);

int buscaLRU(BlocoMemoria *bloco, int tamanho);

void atualizarRAM(BlocoMemoria *RAM, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3);

#endif