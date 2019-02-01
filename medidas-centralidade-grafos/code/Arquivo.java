package t2;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Arrays;


public class Arquivo {
	
	public static void lerGrafo(BufferedReader leitor, int n, Graph G) throws IOException {
		String linha;
		String elementosLinha[];
		int i=0, j;
		
		linha=leitor.readLine();
		do { //Lê os nomes referentes a cada vértice.
			elementosLinha=linha.split("\"");
			G.getVertice(i).setNome(elementosLinha[1]);
			i++;
			linha=leitor.readLine();
		} while(!linha.startsWith("*edges") );
		
		System.out.println("--------------------------");
		
		
		/*linha=leitor.readLine();
		do { //Cria arcos (i.e, direcionados) entre dois vértices.
			elementosLinha=linha.split(" ");

			for(i=0; i<elementosLinha.length; i++) 
				if(!elementosLinha[i].isEmpty()) break;
			for(j=i+1; j<elementosLinha.length; j++)
				if(!elementosLinha[j].isEmpty()) break;

			G.addArc(Integer.parseInt(elementosLinha[i])-1, Integer.parseInt(elementosLinha[j])-1);
			linha=leitor.readLine();
		} while(linha!=null); */
	
		while( (linha=leitor.readLine()) != null) { //Cria edges (i.e, não direcionados) entre dois vértices.
				elementosLinha=linha.split(" ");

				/* Os for's abaixo percorrem o vetor elementosLinha até encontrar alguma posição que não esteja vazia. 
				 * Isso é necessário pois a quantidade de espaços entre os números não é a mesma em todas as linhas. 
				 * i: primeiro vértice, j: segundo vértice. */
				for(i=0; i<elementosLinha.length; i++) 
					if(!elementosLinha[i].isEmpty()) break;
				for(j=i+1; j<elementosLinha.length; j++)
					if(!elementosLinha[j].isEmpty()) break;

				G.addEdge(Integer.parseInt(elementosLinha[i])-1, Integer.parseInt(elementosLinha[j])-1);
		}
	}
	
	public static void escreverRank(Graph G, BufferedWriter escritor) throws IOException {
		escritor.write("---------- TOP 10, BETWEENNESS");
		escritor.newLine();
		Arrays.sort(G.getVertices());
		for(int i=0; i<10; i++) { //rank betweenness
			escritor.write("Vértice " + G.getVertice(i).exibirV() + " \"" + G.getVertice(i).getNome() + "\" -> Betweenness " + G.getVertice(i).getBetweenness());
			escritor.newLine();
		}
		
		escritor.newLine();
		Arrays.sort(G.getVertices(), new medeCloseness());
		escritor.write("---------- TOP 10, CLOSENESS:\n");
		escritor.newLine();
		for(int i=0; i<10; i++) {  //rank closeness
			escritor.write("Vértice " + G.getVertice(i).exibirV() + " \"" + G.getVertice(i).getNome() + "\" -> Closeness " + G.getVertice(i).getCloseness());
			escritor.newLine();
		}

		escritor.newLine();
		Arrays.sort(G.getVertices(), new medeGrau());
		escritor.write("---------- TOP 10, GRAUS:\n");
		escritor.newLine();
		for(int i=0; i<10; i++) {  //rank closeness
			escritor.write("Vértice " + G.getVertice(i).exibirV() + " \"" + G.getVertice(i).getNome() + "\" -> Grau " + G.getVertice(i).getGrau());
			escritor.newLine();
		}
	}
	
}
