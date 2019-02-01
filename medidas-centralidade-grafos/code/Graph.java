package t2;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

public class Graph {
	private int numVertices;
	private Vertice[] vertices;
	
	public Graph(int n) {
		vertices=new Vertice[n];
		for(int i=0; i<n; i++) 
			vertices[i]=new Vertice(i);
		numVertices=n;
	}
	
	public void addEdge(int v, int w) { //Não direcionado. Cria uma ponte (vai em ambas direções).		
		if(!vertices[v].jaExiste(w)) {
			vertices[v].addAdjacencia(w);
			vertices[w].addAdjacencia(v);
			vertices[v].addGrau();
			vertices[w].addGrau();
		}
	}
	
	public Stack<Integer> BFS(int s, int []sigma, int []dist, List<Integer> []pais, Stack<Integer> S) {
		Queue<Integer> Q = new PriorityQueue<>();
		Q.add(s);
		
		while(!Q.isEmpty()) {
			int v=Q.poll();
			S.push(v);
			for(Integer w : vertices[v].getAdjacencia()) { //w armazena cada um dos elementos da lista de adjacência do vértice v
				if(dist[w] < 0) {
					Q.add(w);
					dist[w] = dist[v]+1;
				}
				if(dist[w]==dist[v]+1) {
					sigma[w] += sigma[v];
					pais[w].add(v);
				}
			}
		}
		return S;
	}
	
	public void calcularCentralidades() {
		for(int i=0; i < numVertices; i++) 
			vertices[i].inicializarCentralidades(0, 0);
		
		for(int s=0; s < numVertices; s++) {
			Stack<Integer> S = new Stack<>();
			List<Integer> []pais = new LinkedList[numVertices]; //armazena os pais de menor distância de cada vértice
			for(int i=0; i<numVertices; i++) 
				pais[i] = new LinkedList<Integer>();
			int []sigma = new int[numVertices];
			int []dist = new int[numVertices];
			Arrays.fill(sigma, 0);
			Arrays.fill(dist, -1);
			sigma[s]=1;
			dist[s]=0;
			
			//Betweenness 
			S=BFS(s, sigma, dist, pais, S);
			double []delta = new double[numVertices];
			int w;
			Arrays.fill(delta, 0);
			while(!S.isEmpty()) {
				w=S.pop();
				for(Integer v : pais[w]) {
					delta[v] += (sigma[v]/sigma[w]) * (1.0+delta[w]);
				}
				if(w!=s) 
					vertices[w].setBetweenness(delta[w]);
			}

			for(int i=0; i<numVertices; i++) 
				vertices[i].edgeBetweenness();
			
			//Closeness
			double somaDistancias=0;
			for(int i=0; i<numVertices; i++) 
				somaDistancias+=dist[i];
			vertices[s].setCloseness(1/somaDistancias);
			}
	}
	
	public Vertice getVertice(int i) {
		return vertices[i];
	}

	public Vertice[] getVertices() {
		// TODO Auto-generated method stub
		return vertices;
	}
}
