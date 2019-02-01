package t2;

import java.util.LinkedList;
import java.util.List;

public class Vertice implements Comparable<Vertice> {
	private int v;
	private String nome;
	private List<Integer> adjacencia;
	private double closeness;
	private double betweenness;
	private int grau;	
	
	public Vertice(int v) {
		this.v=v;
		adjacencia=new LinkedList<Integer>();
	}
	
	public void addGrau() {
		this.grau++;
	}
	
	public void addAdjacencia(int v) {
		adjacencia.add(v);
	}
	
	public boolean jaExiste(int v) {
		for(Integer it : adjacencia){
			if(it==v) return true;
		} 
		return false;
	}
	
	public List<Integer> getAdjacencia(){
		return adjacencia;
	}
	
	public void inicializarCentralidades(double b, double c) {
		betweenness=c;
		closeness=c;
	}
	
	public void setBetweenness(double b) {
		betweenness+=b;
	}
	
	public void setCloseness(double c) {
		closeness+=c;
	}
	
	public double getBetweenness() {
		return betweenness;
	}
	
	public void setNome(String n) {
		nome=n;
	}
	
	public String getNome() {
		return nome;
	}
	
	public double getCloseness() {
		return closeness;
	}
	
	public int getGrau() {
		return grau;
	}
	
	public int compareTo(Vertice v) {
		if(this.betweenness < v.betweenness) 
			return 1;
		if(this.betweenness > v.betweenness) 
			return -1;
		return 0;
	}
	
	public int exibirV() {
		return v;
	}

	public void edgeBetweenness() { //em casos onde o grafo é não direcionado é necessário dividir as centralidades bet. por 2
		// TODO Auto-generated method stub
		betweenness/=2;
	}
}