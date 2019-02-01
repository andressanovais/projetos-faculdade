package t2;

import java.util.Comparator;

public class medeCloseness implements Comparator<Vertice> {
	public int compare(Vertice c1, Vertice c2) {
		if(c1.getCloseness() > c2.getCloseness()) return -1;
		if(c1.getCloseness() < c2.getCloseness()) return 1;
		return 0;
	}
}

