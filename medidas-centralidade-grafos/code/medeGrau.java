package t2;

import java.util.Comparator;

public class medeGrau implements Comparator<Vertice> {
	public int compare(Vertice c1, Vertice c2) {
		if(c1.getGrau() > c2.getGrau()) return -1;
		if(c1.getGrau() < c2.getGrau()) return 1;
		return 0;
	}
}
