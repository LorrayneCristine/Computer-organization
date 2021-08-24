//basico maquina
void menu(int *escolha);
void chamaFuncao(int **matrizInstrucoes, int *RAM, int escolha);
void MontarRam(int *RAM);
int *alocaVetor(int *RAM, int qtd);
int **alocaMatriz(int **matrizInstrucoes);
void maquinaInterpretada(int *instrucao, int *RAM);
void maquina(int **matrizInstrucoes, int *RAM);
void instrucoesAleatorias(int **matrizInstrucoes, int *RAM);

//instrucoes basicas
void soma(int **matrizInstrucoes, int soma1, int soma2, int *RAM);
void subtracao(int **matrizInstrucoes, int num1, int num2, int *RAM);
void multiplicacao(int **matrizInstrucoes, int multiplicando, int multiplicador, int *RAM);
void divisao(int **matrizInstrucoes, int dividendo, int divisor, int *RAM);
void exponenciacao(int **matrizInstrucoes, int base, int potencia, int *RAM);

//PA & PG
void termoPA(int **matrizInstrucoes, int a1, int n, int r, int *RAM);
void nPA(int **matrizInstrucoes, int a1, int ai, int r, int *RAM);
void razaoPA(int **matrizInstrucoes, int a1, int a2, int *RAM);
void somaPA(int **matrizInstrucoes, int a1, int an, int n, int *RAM);
void PG(int **matrizInstrucoes, int a1, int n, int r, int *RAM);
void somaPG(int **matrizInstrucoes, int a1, int n, int q, int *RAM);

//area de figuras
void areaQuadrado(int **matrizInstrucoes, int lado,  int *RAM);
void areaRetangulo(int **matrizInstrucoes, int lado1, int lado2,  int *RAM);
void areaTriangulo(int **matrizInstrucoes, int base, int altura,  int *RAM);

//calculo
void fibonacci(int **matrizInstrucoes, int termo,  int *RAM);
void fatorial(int **matrizInstrucoes, int n,  int *RAM);
void delta(int **matrizInstrucoes, int a, int b, int c,  int *RAM);
void raiz(int **matrizInstrucoes, int n,  int *RAM);

//temperatura 
void celsiusToFahrenheit(int **matrizInstrucoes, int n,  int *RAM);
void celsiusToKelvin(int **matrizInstrucoes, int c,  int *RAM);

//meses e anos
void anosMeses(int **matrizInstrucoes, int n,  int *RAM); 
void anoDia(int **matrizInstrucoes, int n,  int *RAM);
void anoHora(int **matrizInstrucoes, int n,  int *RAM);
void semanaMes(int **matrizInstrucoes, int n,  int *RAM);

//velocidade
void velocidadeMedia(int **matrizInstrucoes, int s, int t,  int *RAM);
void distancia(int **matrizInstrucoes, int s, int v, int t,  int *RAM);
void aceleracao(int **matrizInstrucoes, int v, int t,  int *RAM);
void velocidadeAceleracao(int **matrizInstrucoes, int v, int a, int t,  int *RAM);

//aleatorios
void beberAgua(int **matrizInstrucoes, int n,  int *RAM);
void aguaBreja(int **matrizInstrucoes, int n,  int *RAM);
void sonic(int **matrizInstrucoes, int n,  int *RAM);
void pedraPapelTesoura(int **matrizInstrucoes, int *RAM);
void imparPar(int **matrizInstrucoes, int escolha, int *RAM);

