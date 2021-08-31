import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Random;

public class Gerador {

	static int QTD_INS = 100; // Quantidade de instru��es geradas
	static int TAM_FOR = 10; // Tamanho do For
	static int TAM_MEM = 1000000; // Tamanho da Memoria (Quantidade de Endere�os
									// Possiveis)
	static int PROB_FOR = 50; // Probabilidade de Ocorrencia do For (%)

	public static void main(String args[]) throws IOException {
		int aleatorio;
		// Define seu separador (entre os parametros da sua instru��o
		String separador = ":";
		Random r = new Random();
		ArrayList<String> ins = new ArrayList<>();

		// N � a quantidade de Opcodes disponiveis
		int N = 8;
		// instruc � o vetor que conta quantos endere�os tem cada Opcode
		int instruc[] = { 1, 1, 1, 1, 0, 3, 4, 5 };// Instru��es numeradas de 0
													// a N-1

		// Gerando o for (la�o de repeti��o) do programa;
		ArrayList<String> repeticao = new ArrayList<>();
		for (int i = 0; i < TAM_FOR; i++) {
			aleatorio = r.nextInt(N) + 1;
			String s = "";
			for (int j = 0; j < instruc[aleatorio - 1]; j++) {
				s += separador + r.nextInt(TAM_MEM);
			}
			repeticao.add(aleatorio + s);
		}

		for (int i = 0; i < QTD_INS;) {
			aleatorio = r.nextInt(100) + 1;
			if (aleatorio <= PROB_FOR && i + TAM_FOR < QTD_INS) {
				i = i + TAM_FOR;
				ins.addAll(repeticao);
			} else {
				i++;
				aleatorio = r.nextInt(N) + 1;
				String s = "";
				for (int j = 0; j < instruc[aleatorio - 1]; j++) {
					s += separador + r.nextInt(TAM_MEM);
				}
				ins.add(aleatorio + s);
			}
		}
		OutputStream os = new FileOutputStream("instru��es.txt");
		OutputStreamWriter osw = new OutputStreamWriter(os);
		BufferedWriter bw = new BufferedWriter(osw);
		for (int i = 0; i < ins.size(); i++) {
			bw.write(ins.get(i));
			bw.newLine();
		}
		bw.close();
	}
}
