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
	BlocoMemoria RAM[TAMANHO_RAM];
	BlocoMemoria cache1[TAMANHO_CACHE1];
	BlocoMemoria cache2[TAMANHO_CACHE2];
	BlocoMemoria cache3[TAMANHO_CACHE3];
} Memoria;

typedef struct {
	Endereco end1, end2, end3;
	int opcode;
} Instrucao;

typedef struct {
	int hitC1, missC1, hitC2, missC2, hitC3, missC3, hitR, missR, hitHD;
	long long custo;
} CustoPrograma;

BlocoMemoria buscarNasMemorias(Endereco e, Memoria *memoria);

BlocoMemoria buscarNasMemoriasAssociativo(Endereco e, Memoria *memoria);
	
BlocoMemoria testaMemoria1Memoria2(int posicaoBloco1, int posicaoBloco2, BlocoMemoria *bloco1, BlocoMemoria *bloco2, int custo);

int buscaLRU(BlocoMemoria *bloco, int tamanho);

void atualizarHD(Memoria *memoria);

#endif