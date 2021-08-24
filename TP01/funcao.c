#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *alocaVetor(int *RAM, int qtd){								//funcao que aloca todos os vetores inclusive a RAM
	RAM = NULL;			//alocando a RAM
	RAM =  (int*) malloc(qtd*sizeof(int));
	return RAM;
} 

int **alocaMatriz(int **matrizInstrucoes){						//alocando Matriz de instruções
   matrizInstrucoes = NULL;
   matrizInstrucoes = (int **) malloc(10 * sizeof(int*));
    
    if(matrizInstrucoes == NULL){
        printf("Memoria insuficiente.\n");
        return 0;
    }

    for (int i=0; i<10; i++){
        matrizInstrucoes[i] = (int*)  malloc(4*sizeof(int));

        if(matrizInstrucoes[i] == NULL){
            printf("Memoria insuficiente.\n");
            return 0;
        }
    }

	return matrizInstrucoes;
}

void MontarRam(int *RAM){										//preenchendo a RAM com numeros aleatorios
	srand(time(NULL));
	for(int i = 0; i < 100; i++)
		RAM[i] = rand()%1000;
}

void maquinaInterpretada(int *instrucao, int *RAM){				//maquina interpreta uma instrucao por vez e realiza as tarefas de acordo com o opcode

	// opcode = 0 salva na memória RAM
	// opcode = 1 soma
	// opcode = 2 subtrai
	// opcode = 3 trás da memória RAM  


	int opcode = instrucao[0];
	switch (opcode)
	{
		case 0:
		RAM[instrucao[2]] = instrucao[1];
		
		//printf("Salvou na RAM %d numero %d\n", instrucao[2], instrucao[1]);
			break;

		case 1:{

			int endPrimeiro, endSegundo, endTerceiro, contPrimeiro, contSegundo; 
			endPrimeiro = instrucao[1];
			endSegundo = instrucao[2];
			endTerceiro = instrucao[3];

			contPrimeiro = RAM[endPrimeiro];
			contSegundo = RAM[endSegundo];

			RAM[endTerceiro] = contPrimeiro + contSegundo; 
			//printf("1 - Somou na RAM %d numero %d\n", endPrimeiro, contPrimeiro);
			//printf("2 - Somou na RAM %d numero %d\n", endSegundo, contSegundo);
			//printf("3 - Somou na RAM %d numero %d\n", endTerceiro, RAM[endTerceiro]);

		
			break;
		}

		case 2:{
			int endPrimeiro, endSegundo, endTerceiro, contPrimeiro, contSegundo; 
			endPrimeiro = instrucao[1];
			endSegundo = instrucao[2];
			endTerceiro = instrucao[3];

			contPrimeiro = RAM[endPrimeiro];
			contSegundo = RAM[endSegundo];

			RAM[endTerceiro] = contPrimeiro - contSegundo; 
			//printf("1 - Subtraiu na RAM %d numero %d\n", endPrimeiro, contPrimeiro);
			//printf("2 - Subtraiu na RAM %d numero %d\n", endSegundo, contSegundo);
			//printf("3 - Subtraiu na RAM %dnumero %d\n", endTerceiro, RAM[endTerceiro]);

			break;

		}

		case 3: 
		instrucao[1]= RAM[instrucao[2]] ;			
			break; 		
	}
}

void maquina(int **matrizInstrucoes, int *RAM){					//maquina repassa uma série de instrucoes para a maquina interpreta 
	int indice = 0, opcode, qtd = 4;									 
	
	do{
		int* instrucao;										//caso eu não aloque dentro do while toda as instrucoes receberão o conteudo da ultima apontada 
		instrucao = alocaVetor(instrucao, qtd);		
		instrucao = matrizInstrucoes[indice];
		opcode = instrucao[0];								// a instrução é apenas mais ditatico, poderia ser repassado a matriz
		maquinaInterpretada(instrucao, RAM);
	
	
		indice++;											//faz o indice da matriz de instruções variar
	}while(opcode != -1);	
	
}

void instrucoesAleatorias(int **matrizInstrucoes, int *RAM){	//conjunto de somas e subtrações aleatorias

	//0 -> salvar na memoria
	//1 -> somar
	//2 -> subtrair
	//3 -> trazer da memória 

	srand(time(NULL));

    int* instrucao, qtd = 4;   

	for(int i=0; i<10; i++){
		instrucao = NULL;
		instrucao = alocaVetor(instrucao, qtd);

        instrucao[0]= (rand()%2) + 1;
        instrucao[1]= rand()%100;
        instrucao[2]= rand()%100;
        instrucao[3]= rand()%100;

        matrizInstrucoes[i]= instrucao;           //Aqui passamos para a nossa matriz as instruções que seram executadas na máquina
    }


    instrucao[0]= -1;
    instrucao[1]= -1;
    instrucao[2]= -1;
    instrucao[3]= -1;
    matrizInstrucoes[9] = instrucao;
	
     //Aqui iremos parar o nosso programa, pois a instrução -1 representa o Halt
	maquina(matrizInstrucoes, RAM);

	free(instrucao);

}


void multiplicacao(int **matrizInstrucoes, int multiplicando, int multiplicador, int *RAM){

	int* instrucao, qtd = 4;    
	instrucao = NULL;  

	if ( multiplicador > multiplicando){
		int aux = 0; 
		aux = multiplicando; 
		multiplicando = multiplicador;
		multiplicador = aux;
	}

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = multiplicando;
	instrucao[2] = 4;
	instrucao[3] = -1; 
	matrizInstrucoes[0] = instrucao;

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 5;
	instrucao[3] = -1; 
	matrizInstrucoes[1] = instrucao;

	for(int i = 0; i < multiplicador; i++){
		instrucao = alocaVetor(instrucao, qtd);
		instrucao[0] = 1; // somando 
		instrucao[1] = 5;
		instrucao[2] = 4;
		instrucao[3] = 5; 

		matrizInstrucoes[i + 2] = instrucao;

	}

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0]= -1;
    instrucao[1]= -1;							//parar o programa
    instrucao[2]= -1;
    instrucao[3]= -1;
    matrizInstrucoes[multiplicador+2] = instrucao;


	maquina(matrizInstrucoes, RAM);
	free(instrucao);

}
void divisao(int **matrizInstrucoes, int dividendo, int divisor, int *RAM){
	int *instrucao, qtd = 4; 
	instrucao = NULL;

	instrucao = alocaVetor(instrucao, qtd);			//salvando o dividendo na ram 
	instrucao[0] = 0;
	instrucao[1] = dividendo; 						//valor sendo levado
	instrucao[2] = 0;								//posição que esta sendo levado
	instrucao[3] = -1; 
	matrizInstrucoes[0] = instrucao;


	instrucao = alocaVetor(instrucao, qtd); 		//salvando o o divisor na ram
	instrucao[0] = 0;
	instrucao[1] = divisor; 						//valor sendo levado
	instrucao[2] = 1;								//posição que esta sendo levado
	instrucao[3] = -1; 
	matrizInstrucoes[1] = instrucao;



	instrucao = alocaVetor(instrucao, qtd); 		//criando um contador para saber quanto deu a divisao
	instrucao[0] = 0;								
	instrucao[1] = 0;								//valor sendo levado de 0
	instrucao[2] = 2; 								//posição que esta sendo levado
	instrucao[3] = -1; 
	matrizInstrucoes[2] = instrucao;


	instrucao = alocaVetor(instrucao, qtd); 		//criando segunda parte do contador para a soma
	instrucao[0] = 0;
	instrucao[1] = 1;								//valor de 1 sendo levado para a soma
	instrucao[2] = 3;								//casinnha para onde ele esta sendo levado		
	instrucao[3] = -1; 						
	matrizInstrucoes[3] = instrucao;

	instrucao = alocaVetor(instrucao, qtd); 		//finalizando o trem
	instrucao[0] = -1;								
	instrucao[2] = -1;							
	instrucao[1] = -1; 								
	instrucao[3] = -1; 
	matrizInstrucoes[4] = instrucao;

	maquina(matrizInstrucoes, RAM); 				//passando a maquina para ter certeza que foram salvas as alteracoes

	//[0][1] = dividendo divisor
	//[2][3] = contador 0 e contador 1


	instrucao = alocaVetor(instrucao, qtd); 		//buscando o dividendo na memoria
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 0;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);
	int ram0 = instrucao[1];


	instrucao = alocaVetor(instrucao, qtd); 		//buscando o divisor na memoria
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 1;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);
	int ram1 = instrucao[1];

	while(ram0 >= ram1){

		instrucao = alocaVetor(instrucao, qtd); 	//divindo oque ta na ram 0 pelo oque esta na ram 1	
		instrucao[0] = 2;
		instrucao[1] = 0;
		instrucao[2] = 1;
		instrucao[3] = 0;
		maquinaInterpretada(instrucao, RAM);

		instrucao = alocaVetor(instrucao, qtd); 	//somando o contador
		instrucao[0] = 1;
		instrucao[1] = 2;
		instrucao[2] = 3;
		instrucao[3] = 2;
		maquinaInterpretada(instrucao, RAM);

		instrucao = alocaVetor(instrucao, qtd); 		//buscando o dividendo na memoria e atualizando
		instrucao[0] = 3;
		instrucao[1] = -1;
		instrucao[2] = 0;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);
		ram0 = instrucao[1];

	}


	free(instrucao);
}
void soma(int **matrizInstrucoes, int soma1, int soma2, int *RAM){

	int *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = soma1;
	instrucao[2] = 6;
	instrucao[3] = -1; 
	matrizInstrucoes[0] = instrucao;

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = soma2;
	instrucao[2] = 7;
	instrucao[3] = -1; 
	matrizInstrucoes[1] = instrucao;


	instrucao = alocaVetor(instrucao, qtd); 		//finalizando o trem
	instrucao[0] = -1;								
	instrucao[2] = -1;							
	instrucao[1] = -1; 								
	instrucao[3] = -1; 
	matrizInstrucoes[2] = instrucao;

	maquina(matrizInstrucoes, RAM);

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 6;
	instrucao[3] = -1; 
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 7;
	instrucao[3] = -1; 
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 1;
	instrucao[1] = 6;
	instrucao[2] = 7;
	instrucao[3] = 8; 
	maquinaInterpretada(instrucao, RAM);

	free(instrucao);
}
void subtracao(int **matrizInstrucoes, int num1, int num2, int *RAM){

	int *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = num1;
	instrucao[2] = 9;
	instrucao[3] = -1; 
	matrizInstrucoes[0] = instrucao;

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = num2;
	instrucao[2] = 10;
	instrucao[3] = -1; 
	matrizInstrucoes[1] = instrucao;


	instrucao = alocaVetor(instrucao, qtd); 		//finalizando o trem
	instrucao[0] = -1;								
	instrucao[2] = -1;							
	instrucao[1] = -1; 								
	instrucao[3] = -1; 
	matrizInstrucoes[2] = instrucao;

	maquina(matrizInstrucoes, RAM);

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 9;
	instrucao[3] = -1; 
	maquinaInterpretada(instrucao, RAM);


	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 3;
	instrucao[1] = -1;
	instrucao[2] = 10;
	instrucao[3] = -1; 
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 2;
	instrucao[1] = 9;
	instrucao[2] = 10;
	instrucao[3] = 11; 
	maquinaInterpretada(instrucao, RAM);

	free(instrucao);
}
void exponenciacao(int **matrizInstrucoes, int base, int potencia, int *RAM){
	RAM[12] = base;
	int* instrucao, qtd = 4;
	instrucao = NULL; 

	while((potencia-1) != 0){

		multiplicacao(matrizInstrucoes, RAM[12], base, RAM );
		instrucao = alocaVetor(instrucao, qtd);
		instrucao[0]= 0;
		instrucao[1]= RAM[5];
		instrucao[2]= 12;
		instrucao[3]= -1;
		maquinaInterpretada(instrucao, RAM);

		potencia--;
	}

	free(instrucao);
}


void termoPA(int **matrizInstrucoes, int a1, int n, int r, int *RAM){
	//an = a1 + (n - 1)*r
	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	subtracao(matrizInstrucoes,  n, RAM[13], RAM); 		//RAM[13] = onde ficou armazenado -1
	multiplicacao(matrizInstrucoes,  r, RAM[11], RAM);	//RAM[08] = onde ficou salvo o resultado da subtracao
	soma(matrizInstrucoes,  a1, RAM[5], RAM);			//RAM[11] = onde ficou armazenado o resultado da multiplicacao


	free(instrucao);
}
void nPA(int **matrizInstrucoes, int a1, int ai, int r, int *RAM){
	//n = (((An-A1)+r)/r)*r

	subtracao(matrizInstrucoes, ai, a1, RAM);		//o resultado fica na RAM[11]
	soma(matrizInstrucoes, RAM[11], r, RAM); 		//o resultado vai pra RAM[8]
	divisao(matrizInstrucoes, RAM[8], r, RAM);		// o resultado vai pra RAM[2]
	multiplicacao(matrizInstrucoes, RAM[2], r, RAM);//o resultado vai pra RAM[5]
}
void razaoPA(int **matrizInstrucoes, int a1, int a2, int *RAM){
	//r = an - an-1
	subtracao(matrizInstrucoes, a2, a1, RAM);//o resultado fica na RAM[11]
}
void somaPA(int **matrizInstrucoes, int a1, int an, int n, int *RAM){
	//s = ((a1 + an)*n)/2

	soma(matrizInstrucoes, a1, an, RAM);//o resultado fica na RAM[8]
	multiplicacao(matrizInstrucoes, RAM[8], n, RAM);//o resultado fica na RAM[5]

	int* instrucao, qtd = 4;
		instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 2 na memoria RAM
	instrucao[0] = 0;
	instrucao[1] = 2;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	

	divisao(matrizInstrucoes, RAM[5], RAM[13], RAM);//o resultado é substituido na ram 2
	soma(matrizInstrucoes, RAM[8], RAM[7], RAM);

	free(instrucao);
}
void PG(int **matrizInstrucoes, int a1, int n, int r, int *RAM){
		//An=A1*q^(n-1)
		//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
		instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 1 na memoria RAM
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	

	subtracao(matrizInstrucoes, n, RAM[13], RAM);
	exponenciacao(matrizInstrucoes, r, RAM[11], RAM);	//salva na RAM[12]
	multiplicacao(matrizInstrucoes, a1, RAM[12], RAM);

	free(instrucao);

}
void somaPG(int **matrizInstrucoes, int a1, int n, int q, int *RAM){
		//An=A1*q^(n-1)
		//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
		instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 1 na memoria RAM[13]
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	

	exponenciacao(matrizInstrucoes, q, n, RAM);			//salva na RAM[12]
	subtracao(matrizInstrucoes, RAM[12], RAM[13], RAM);
	multiplicacao(matrizInstrucoes, a1, RAM[11], RAM);
	subtracao(matrizInstrucoes, q, RAM[13], RAM);
	divisao(matrizInstrucoes, RAM[5], RAM[11], RAM);	

	free(instrucao);

}


void areaQuadrado(int **matrizInstrucoes, int lado,  int *RAM){

	multiplicacao(matrizInstrucoes, lado, lado , RAM); //salva na RAM[5]

}
void areaRetangulo(int **matrizInstrucoes, int lado1, int lado2,  int *RAM){
	multiplicacao(matrizInstrucoes, lado1, lado2 , RAM); //salva na RAM[5]
}
void areaTriangulo(int **matrizInstrucoes, int base, int altura,  int *RAM){
	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 2 na memoria RAM[13]
	instrucao[0] = 0;
	instrucao[1] = 2;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, base, altura , RAM); //salva na RAM[5]
	divisao(matrizInstrucoes, RAM[5], RAM[13], RAM);

	free(instrucao);
}


void fibonacci(int **matrizInstrucoes, int termo,  int *RAM){
	//F(n)=F(n-1)+F(n-2)
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 0 na memoria RAM[13]
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizInstrucoes[0] = instrucao;

 	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 0 na memoria RAM[14]
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizInstrucoes[1] = instrucao;

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 0 na memoria RAM[14]
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 8;
	instrucao[3] = -1;
	matrizInstrucoes[2] = instrucao;

	instrucao = alocaVetor(instrucao, qtd);		///colocando o numero 0 na memoria RAM[8] que é a soma
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizInstrucoes[3] = instrucao;
	maquina(matrizInstrucoes, RAM);

	printf("0, 1");


	for(int i = 0; i < termo; i++){
		soma(matrizInstrucoes, RAM[6], RAM[7], RAM);

		instrucao = alocaVetor(instrucao, qtd); 
		instrucao[0] = 0;
		instrucao[1] = RAM[7];
		instrucao[2] = 6;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		instrucao = alocaVetor(instrucao, qtd); 
		instrucao[0] = 0;
		instrucao[1] = RAM[8];
		instrucao[2] = 7;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		printf(", %d", RAM[8]);
	}

	free(instrucao);
}
void fatorial(int **matrizInstrucoes, int n,  int *RAM){
		//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
	int *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd); 
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd); 
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 5;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd); //subtracao
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 11;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	int aux = n;

	for(int i = 0; i < aux-1; i ++){
		subtracao(matrizInstrucoes, RAM[11], RAM[13], RAM);
		multiplicacao(matrizInstrucoes, RAM[5], RAM[11], RAM );

	}

	free(instrucao);
}
void delta(int **matrizInstrucoes, int a, int b, int c,  int *RAM){
		// delta = b^2 - 4*a*c
		int *instrucao, qtd = 4;
			instrucao = NULL; 

		instrucao = alocaVetor(instrucao, qtd); 
		instrucao[0] = 0;
		instrucao[1] = 2;
		instrucao[2] = 13;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		instrucao = alocaVetor(instrucao, qtd); 
		instrucao[0] = 0;
		instrucao[1] = 4;
		instrucao[2] = 14;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		exponenciacao(matrizInstrucoes, b, RAM[13], RAM);
		multiplicacao(matrizInstrucoes, a, c, RAM);
		multiplicacao(matrizInstrucoes, RAM[14], RAM[5], RAM);

		subtracao(matrizInstrucoes, RAM[12], RAM[5], RAM);

		free(instrucao);
}
void raiz(int **matrizInstrucoes, int n,  int *RAM){

	int *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd); //colocando o valor 0 na RAM 8 que é onde sai o resultado da soma
	instrucao[0] = 0;
	instrucao[1] = 0;							
	instrucao[2] = 8;
	instrucao[3] = -1;
	matrizInstrucoes[0] = instrucao;

	instrucao = alocaVetor(instrucao, qtd); //salvando o valor 1 para usar de acrescimo no contador
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 14;
	instrucao[3] = -1;
	matrizInstrucoes[1] = instrucao;

	instrucao = alocaVetor(instrucao, qtd); //salvando o valor 2 para usar na divisao
	instrucao[0] = 0;
	instrucao[1] = 2;
	instrucao[2] = 15;
	instrucao[3] = -1;
	matrizInstrucoes[2] = instrucao;

	instrucao = alocaVetor(instrucao, qtd); //salvando 0 para o contador
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 16;
	instrucao[3] = -1;
	matrizInstrucoes[3] = instrucao;

	instrucao = alocaVetor(instrucao, qtd); //salvando 0 para o contador
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizInstrucoes[4] = instrucao;

	maquina(matrizInstrucoes, RAM);


	divisao(matrizInstrucoes, n, RAM[15], RAM);

	
	do{
		multiplicacao(matrizInstrucoes, RAM[8], RAM[8], RAM);

		instrucao = alocaVetor(instrucao, qtd); //somando contador
		instrucao[0] = 1;
		instrucao[1] = 16;
		instrucao[2] = 14;
		instrucao[3] = 16;
		maquinaInterpretada(instrucao, RAM);

		if(RAM[5]==n){										//resultado da multiplicacao == o numero escolhido
			printf("\tO valor da raiz é: %d\n", RAM[8]);
			break;
		}
		else if(RAM[16] == RAM[2]){									//ultima vez que o for entra e não encontra o numero
			printf("\tNão foi encontrado uma raiz inteira\n");
		}
		else{												//somo o numero que usei na soma + 1 para entrar novamente no for
			soma(matrizInstrucoes, RAM[8], RAM[14], RAM);
		}
	}while (RAM[16] <= RAM[2]);

	free(instrucao);
	
}


void celsiusToFahrenheit(int **matrizInstrucoes, int c,  int *RAM){
// F = C * 1.8 + 32
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 2;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 32;
	instrucao[2] = 14;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	


	multiplicacao(matrizInstrucoes, c, RAM[13],  RAM);
	soma(matrizInstrucoes, RAM[5], RAM[14],  RAM);

	free(instrucao);
}
void celsiusToKelvin(int **matrizInstrucoes, int c,  int *RAM){
// K = c + 273
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 273;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);	

	soma(matrizInstrucoes, c, RAM[13],  RAM);
	free(instrucao);
}


void anosMeses(int **matrizInstrucoes, int n,  int *RAM){

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 12;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, n, RAM[13],  RAM);

	free(instrucao);
}
void anoDia(int **matrizInstrucoes, int n,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 365;
	instrucao[2] = 14;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, n, RAM[14],  RAM);

	free(instrucao);
}
void anoHora(int **matrizInstrucoes, int n,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 365;
	instrucao[2] = 14;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 24;
	instrucao[2] = 15;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, n, RAM[14],  RAM);
	multiplicacao(matrizInstrucoes, RAM[5], RAM[15],  RAM);


	free(instrucao);
}	
void semanaMes(int **matrizInstrucoes, int n,  int *RAM){
	int *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);
	instrucao[0] = 0;
	instrucao[1] = 4;
	instrucao[2] = 13;
	instrucao[4] = -1;
	maquinaInterpretada(instrucao, RAM);

	divisao(matrizInstrucoes, n, RAM[13], RAM);

}


void velocidadeMedia(int **matrizInstrucoes, int s, int t,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
// V = s/t
	divisao(matrizInstrucoes, s, t, RAM);

}
void distancia(int **matrizInstrucoes, int s, int v, int t,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
// S = S0 + vt
	multiplicacao(matrizInstrucoes, v, t, RAM);
	soma(matrizInstrucoes, s, RAM[5], RAM);

}
void aceleracao(int **matrizInstrucoes, int v, int t,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
//Am = V/T	
	divisao(matrizInstrucoes, v, t, RAM);

}
void velocidadeAceleracao(int **matrizInstrucoes, int v, int a, int t,  int *RAM){
//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
//V = v0 + a . t 
	multiplicacao(matrizInstrucoes, a, t, RAM);
	soma(matrizInstrucoes, v, RAM[5], RAM);

}


void beberAgua(int **matrizInstrucoes, int n,  int *RAM){
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 35;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, n, RAM[13],  RAM);

	free(instrucao);
}
void aguaBreja(int **matrizInstrucoes, int n,  int *RAM){
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 100;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	multiplicacao(matrizInstrucoes, n, RAM[13],  RAM);

	free(instrucao);
}
void sonic(int **matrizInstrucoes, int n,  int *RAM){
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int* instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = 0;
	instrucao[1] = 343;						//sonic faz 342,7 m/s
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);

	divisao(matrizInstrucoes, n, RAM[13],  RAM);

	free(instrucao);
}
void pedraPapelTesoura(int **matrizInstrucoes, int *RAM){
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]
	int escolha, pc, *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		//RAM 6 para pontuar o jogador
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizInstrucoes[0] = instrucao; 

	instrucao = alocaVetor(instrucao, qtd);		//RAM 7 para pontuar o maquina
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizInstrucoes[1] = instrucao; 

	instrucao = alocaVetor(instrucao, qtd);		//RAM [9] para somar o contador
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 9;
	instrucao[3] = -1;
	matrizInstrucoes[2] = instrucao; 

	instrucao = alocaVetor(instrucao, qtd);		// RAM[8] para somar 1 no placar
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 8;
	instrucao[3] = -1;
	matrizInstrucoes[3] = instrucao; 

	instrucao = alocaVetor(instrucao, qtd);		
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizInstrucoes[4] = instrucao; 

	maquina(matrizInstrucoes, RAM);


	do{
		printf("\tEscolha 1-pedra, 2-papel, 3-tesoura: ");
		scanf("%d", &escolha);

		instrucao = alocaVetor(instrucao, qtd);		
		instrucao[0] = 0;
		instrucao[1] = escolha;
		instrucao[2] = 13;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		srand(time(NULL));
		pc = (rand()%3) +1;

		instrucao = alocaVetor(instrucao, qtd);		
		instrucao[0] = 0;
		instrucao[1] = pc;
		instrucao[2] = 14;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);

		if(RAM[13] == RAM[14]){
			printf("\tEMPATE\n\n");
		}
		else if((RAM[13] == 1 && RAM[14] == 2) || (RAM[13] == 2 && RAM[14] == 3) || (RAM[13] == 3 && RAM[14] == 1)){
			printf("\tPonto para o adversário\n\n");

			instrucao = alocaVetor(instrucao, qtd);		//RAM [7] pontua o adversario
			instrucao[0] = 1;
			instrucao[1] = 7;
			instrucao[2] = 8;
			instrucao[3] = 7;
			maquinaInterpretada(instrucao, RAM);
		}else{
			printf("\tPonto seu\n\n");

			instrucao = alocaVetor(instrucao, qtd);		//RAM 6 para pontuar o jogador
			instrucao[0] = 1;
			instrucao[1] = 6;
			instrucao[2] = 8;
			instrucao[3] = 6;
			maquinaInterpretada(instrucao, RAM);
		}

		instrucao = alocaVetor(instrucao, qtd);		//RAM [9] para somar o contador
		instrucao[0] = 1;
		instrucao[1] = 9;
		instrucao[2] = 8;
		instrucao[3] = 9;
		maquinaInterpretada(instrucao, RAM);


	}while( RAM[9] < 3);
}
void imparPar(int **matrizInstrucoes, int escolha, int *RAM){
	//subtracao RAM[11], divisao RAM[2], soma RAM[8], multiplicacao RAM[5]

	int n, pc, *instrucao, qtd = 4;
	instrucao = NULL; 

	instrucao = alocaVetor(instrucao, qtd);		// RAM[13] para dividir 
	instrucao[0] = 0;
	instrucao[1] = 2;
	instrucao[2] = 13;
	instrucao[3] = -1;
	maquinaInterpretada(instrucao, RAM);


	printf("\tEscolha um número: ");
	scanf("%d", &n);

	srand(time(NULL));
	pc = rand()%100;

	soma(matrizInstrucoes, pc, n, RAM);
	divisao(matrizInstrucoes, RAM[8], RAM[13], RAM);

	printf("\n\tO adversário jogou %d e você %d\n", pc, n);

	if(escolha == 1){
		if(RAM[0] == 0)
			printf("\tVocê perdeu :(\n");
		else
			printf("\tVocê ganhou :)\n");		
	}
	else if(escolha == 2){
		if(RAM[0] == 0)
			printf("\tVocê ganhou :)\n");			
		else
			printf("\tVocê perdeu :(\n");	
	}

}


void menu(int *escolha){

	    printf("\n\n\t\t\t𝕀 ℕ 𝕀 ℂ 𝕀 𝕆\n");//menu para escolha da dimensão
        printf("\n\t---------------------------------------------------------------\n");
        printf("\t 01 - Operações aleatórias \n");
        printf("\t 02 - Soma \n");
		printf("\t 03 - Subtração \n");
        printf("\t 04 - Multiplicação\n");
        printf("\t 05 - Divisão\n");
        printf("\t 06 - Exponenciação\n");
        printf("\t 07 - Encontre o termo PA\n");
        printf("\t 08 - Encontre o numero de termos da PA\n");
        printf("\t 09 - Encontre a razão PA\n");
        printf("\t 10 - Somatório dos termos de PA(finita)\n");
        printf("\t 11 - Encontre o termo da PG\n");
        printf("\t 12 - Soma de PG finita\n");
		printf("\t 13 - Area de quadrado\n");
		printf("\t 14 - Area de retângulo \n");
		printf("\t 15 - Area de triângulo \n");
		printf("\t 16 - Sequencia de Fibonacci\n");
		printf("\t 17 - Fatorial\n");
		printf("\t 18 - Calculo delta\n");
		printf("\t 19 - Raiz quadrada\n");
		printf("\t 20 - Temperatura em Celsius para Fahrenheit\n");
		printf("\t 21 - Temperatura em Celsius para Kelvin\n");
		printf("\t 22 - Conversão de ano para meses\n");
		printf("\t 23 - Conversão de ano para dias\n");
		printf("\t 24 - Conversão de ano para horas\n");
		printf("\t 25 - Conversão de semanas para meses\n");
		printf("\t 26 - Calculo da velocidade média \n"); // V = s/t
		printf("\t 27 - Calculo da distância \n"); // S = S0 + vt
		printf("\t 28 - Calculo da aceleração \n"); // Am = V/T
		printf("\t 29 - Calculo da velocidade com aceleração\n"); // V = v0 + a . t 
		printf("\t 30 - Quanto de água devo beber por peso\n");
		printf("\t 31 - Quanto de água devo beber por cerveja\n");
		printf("\t 32 - Distância percorrida do Sonic\n");
		printf("\t 33 - Pedra, papel e tesoura (melhor de três) \n");
		printf("\t 34 - Ímpar ou par\n");






        printf("\t                                                              \n");
        printf("\t Escolha a opção: ");	scanf("%d", escolha); 
        printf("\n\t---------------------------------------------------------------\n\n");

}
void chamaFuncao(int **matrizInstrucoes, int *RAM, int escolha){

	switch (escolha)
	{

		case 1:{
			instrucoesAleatorias(matrizInstrucoes, RAM);
			break;
		}
		case 2:{
			int num1, num2;
			printf("\tDigite dois numeros inteiros para realizar a soma: ");
			scanf("%d %d", &num1, &num2); 
			soma(matrizInstrucoes, num1, num2, RAM);
			printf("\tO resultado da soma é = %d\n", RAM[8]);
			break;
		}
		case 3:{
			int num1, num2;
			printf("\tDigite dois numeros inteiros para realizar a subtração: ");
			scanf("%d %d", &num1, &num2); 
			subtracao(matrizInstrucoes, num1, num2, RAM);
			printf("\tO resultado da subtração é = %d\n", RAM[11]);

			break;
		}
			case 4:{
			int num1, num2;
			printf("\tDigite dois numeros inteiros para realizar a multiplicacao: ");
			scanf("%d %d", &num1, &num2); 
			multiplicacao(matrizInstrucoes, num1, num2, RAM);
			printf("\tO resultado da multiplicação é = %d\n", RAM[5]);

			break;
		}

			case 5:{
			int num1, num2;
			printf("\tDigite respectivamente o dividendo e o divisor: ");
			scanf("%d %d", &num1, &num2); 
			divisao(matrizInstrucoes, num1, num2, RAM);
			printf("\tO resultado da divisao é = %d\n", RAM[2]);

			break;
		}
			case 6:{
			int num1, num2;
			printf("\tDigite respectivamente a base e o expoente: ");
			scanf("%d %d", &num1, &num2); 
			exponenciacao(matrizInstrucoes, num1, num2, RAM);
			printf("\tO resultado da exponenciação é = %d\n", RAM[12]);

			break;
		}
			case 7:{

			int a1, n, r;			
			printf("\tDigite respectivamente o primeiro termo da progressão, o ultimo termo e a razão: ");
			scanf("%d %d %d", &a1, &n, &r); 
			termoPA(matrizInstrucoes, a1, n,r, RAM);
			printf("\tO termo procurado é = %d\n", RAM[8]);

			break;
		}

		case 8:{

			int a1, ai, r;			
			printf("\tInforme o primeiro termo da progressao, o ultimo termo e a razao, respectivamente: ");
			scanf("%d %d %d", &a1, &ai, &r); 
			nPA(matrizInstrucoes, a1, ai,r, RAM);
			printf("\tNumero de termos é = %d\n", RAM[5]);

			break;
		}

		case 9:{

			int a1, a2;			
			printf("\tInforme um termo da progressao e o seu sucessor: ");
			scanf("%d %d", &a1, &a2); 
			razaoPA(matrizInstrucoes, a1, a2, RAM);
			printf("\tA razão da PA é = %d\n", RAM[11]);

			break;
		}

		case 10:{

			int a1, an, n;			
			printf("\tInforme o primeiro termo da progressao, o ultimo e a quantidade de termos, respectivamente: ");
			scanf("%d %d %d", &a1, &an, &n); 
			somaPA(matrizInstrucoes, a1, an, n, RAM);
			printf("\tA soma da PA é = %d\n", RAM[2]);

			break;
		}
		case 11:{

			int a1, an, r;			
			printf("\tInforme o primeiro termo da progressao, a posicao do termo que deseja achar e a razao, respectivamente: ");
			scanf("%d %d %d", &a1, &an, &r); 
			PG(matrizInstrucoes, a1, an, r, RAM);
			printf("\tO resultado da PG é = %d\n", RAM[12]);

			break;
		}
		case 12:{

			int a1, n, q;			
			printf("\tInforme o primeiro termo da progressao, a quantidade de termos e a razao, respectivamente: ");
			scanf("%d %d %d", &a1, &n, &q); 
			somaPG(matrizInstrucoes, a1, n, q, RAM);
			printf("\tO resultado da soma da PG é = %d\n", RAM[2]);

			break;
		}

		case 13:{

			int lado;			
			printf("\tInforme o lado do quadrado: ");
			scanf("%d", &lado); 
			areaQuadrado(matrizInstrucoes, lado, RAM);
			printf("\tA area do quadrado é = %d\n", RAM[5]);

			break;
		}
		case 14:{

			int lado1, lado2;			
			printf("\tInforme as medidas dos lados do retangulo: ");
			scanf("%d %d", &lado1, &lado2); 
			areaRetangulo(matrizInstrucoes, lado1, lado2, RAM);
			printf("\tA area do retângulo é = %d\n", RAM[5]);

			break;
		}
			case 15:{

			int base, altura;			
			printf("\tInforme as medidas da base e altura do triângulo: ");
			scanf("%d %d", &base, &altura); 
			areaTriangulo(matrizInstrucoes, base, altura, RAM);
			printf("\tA area do triângulo é = %d\n", RAM[2]);

			break;
		}
		case 16:{
			int termos;
			printf("\tInforme a quantidade de termos: ");
			scanf("%d", &termos); 
			printf("\tFibonacci: (");
			fibonacci(matrizInstrucoes, termos, RAM);
			printf(")\n");

			break;
		}
		case 17:{
			int n;
			printf("\tInforme o numero para o fatorial: ");
			scanf("%d", &n); 
			fatorial(matrizInstrucoes, n, RAM);
			printf("\t!= %d\n", RAM[5]);

			break;
		}
		case 18:{
			int a, b, c;
			printf("\tInforme a, b, c, respectivamente para calcular delta: ");
			scanf("%d %d %d", &a, &b, &c); 
			delta(matrizInstrucoes, a, b, c, RAM);
			printf("\tO resultado do delta é = %d\n", RAM[11]);

			break;
		}
		case 19:{
			int n;
			printf("\tInforme o numero para achar a raiz inteira: ");
			scanf("%d", &n); 
			raiz(matrizInstrucoes, n, RAM);
			break;
		} 
		case 20:{
			int c;
			printf("\tInforme o valor da temperatura em Celsius: ");
			scanf("%d", &c); 
			celsiusToFahrenheit(matrizInstrucoes, c, RAM);
			printf("\t%d Celsius é aproximadamente a %d Fahrenheit\n", c, RAM[8]);
			break;
		} 
		case 21:{
			int c;
			printf("\tInforme o valor da temperatura em Celsius: ");
			scanf("%d", &c); 
			celsiusToKelvin(matrizInstrucoes, c, RAM);
			printf("\t%d Celsius é equivalente a %d Kelvin\n", c, RAM[8]);
			break;
		} 
		case 22:{
			int c;
			printf("\tInforme a quantidade de ano: ");
			scanf("%d", &c); 
			anosMeses(matrizInstrucoes, c, RAM);
			printf("\t%d meses\n",RAM[5]);
			break;
		} 
		case 23:{
			int c;
			printf("\tInforme a quantidade de ano: ");
			scanf("%d", &c); 
			anoDia(matrizInstrucoes, c, RAM);
			printf("\t%d dias (considerando 1 ano 365 dias)\n",RAM[5]);
			break;
		} 
		case 24:{
			int c;
			printf("\tInforme a quantidade de ano: ");
			scanf("%d", &c); 
			anoHora(matrizInstrucoes, c, RAM);
			printf("\t%d horas (considerando 1 ano 365 dias)\n",RAM[5]);
			break;
		} 
		case 25:{
			int c;
			printf("\tInforme a quantidade de semanas: ");
			scanf("%d", &c); 
			semanaMes(matrizInstrucoes, c, RAM);
			printf("\t%d mes(es) e %d semana(s)\n",RAM[2], RAM[0]);
			break;
		} 
		case 26:{
			int t, s;
			printf("\tInforme a distância percorrida e tempo gasto: ");
			scanf("%d %d", &s, &t); 
			velocidadeMedia(matrizInstrucoes, s, t, RAM);
			printf("\tA velocidade media aproximada é = %d",RAM[2]);
			break;
		} 
		case 27:{
			int v, s, t;
			printf("\tInforme a posição inicial, a velocidade e tempo gasto, respectivamente: ");
			scanf("%d %d %d", &s, &v, &t); 
			distancia(matrizInstrucoes, s, v, t, RAM);
			printf("\tA distância percorrida é = %d",RAM[8]);
			break;
		} 
		case 28:{
			int v, t;
			printf("\tInforme a variaçã da velocidade pelo tempo, respectivamente: ");
			scanf("%d %d", &v, &t); 
			aceleracao(matrizInstrucoes, v, t, RAM);
			printf("\tA aceleração é aproximadamente = %d",RAM[2]);
			break;
		} 
		case 29:{
			int v, t, a;
			printf("\tInforme a velocidade inicial a aceleração e o tempo, respectivamente: ");
			scanf("%d %d %d", &v, &a, &t); 
			velocidadeAceleracao(matrizInstrucoes, v, a, t, RAM);
			printf("\tA velocidade média é aproximadamente = %d",RAM[8]);
			break;
		} 
		case 30:{
			int c;
			printf("\tInforme o seu peso em kg: ");
			scanf("%d", &c); 
			beberAgua(matrizInstrucoes, c, RAM);
			printf("\tVocê deverá beber %d ml de água por dia\n",RAM[5]);
			break;
		} 
		case 31:{
			int c;
			printf("\tQuantas latas de cerveja você bebeu: ");
			scanf("%d", &c); 
			aguaBreja(matrizInstrucoes, c, RAM);
			printf("\tVocê deverá beber %d ml de água \n",RAM[5]);
			break;
		}
		case 32:{
			int c;
			printf("\tDigite uma distância em metros: ");
			scanf("%d", &c); 
			sonic(matrizInstrucoes, c, RAM);
			printf("\tConsiderando a velocidade do Sonic aproximadamente 343 m/s ele demoraria %d segundos\n",RAM[2]);
			break;
		}
		case 33:{
			pedraPapelTesoura(matrizInstrucoes, RAM);
			printf("\tVocê %d X %d Adversário\n",RAM[6], RAM[7]);
			break;
		}
		case 34:{
			printf("\tEscolha ímpar 1 ou par 2: ");
			scanf("%d", &escolha);
			imparPar(matrizInstrucoes, escolha, RAM);
			break;
		}
		

	}

 	printf("\n\t---------------------------------------------------------------\n\n");


}