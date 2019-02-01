package t2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Teste {
	public static void main(String[] args) {
		File path = new File("C:\\Users\\Andressa\\Documents\\t3\\dolphins.txt");
		File path2 = new File("C:\\Users\\Andressa\\Documents\\t3\\rank.txt");
		try{
			BufferedReader leitor=new BufferedReader(new FileReader(path));
			String linha;
			String elementosLinha[];
			int n;
			
			/*Lê o número de vértices*/
			linha=leitor.readLine(); 
			while(!linha.startsWith("*vertices")) linha=leitor.readLine();
			elementosLinha=linha.split(" ");
			n=Integer.parseInt(elementosLinha[1]);
			
			Graph G = new Graph(n);
			Arquivo.lerGrafo(leitor, n, G);
			G.calcularCentralidades();
			leitor.close();
			
			BufferedWriter escritor=new BufferedWriter(new FileWriter(path2));
			Arquivo.escreverRank(G, escritor);
			escritor.close();
		} catch (FileNotFoundException ex) {
			System.out.println("Não foi possível abrir o arquivo para leitura.");
		} catch (IOException ex3) {
			System.out.println("Não foi possível acessar o arquivo.");
		} 
	}
	

}
