package Ω∫≈∞¿Â∫Ò∑ª≈ª;
class Day {
	float day;
	int quan;
}
public class Period {
	protected Day[] list;
	protected int[] num;
	public Period() {
		list = new Day[256];
		num = new int[256];
	};
	public void add(float s, float l, int n) {
		for(float i=s*10; i<=l*10; i++) {
			if(isInDay(i/10)>0) {
			list[getDay(i/10)].quan += n;
			}
			else if(isInDay(i/10)==-1) {
				add(i/10,n);
			}
		}
	};
	public void add(float _day, int n) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i] = new Day();
				list[i].day = _day;
				list[i].quan = n;
				break;
			}
		}
	};
	public int isInDay(float _day) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].day==_day) return 1;
		}
		return -1;
	};
	public int getDiff(float _day, int _quan) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].day==_day) { 
				return(_quan - list[i].quan);
			}
		}
		return _quan;
	};
	public int getDay(float _day) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].day==_day) return i;
		}
		return -1;
	};
	public void delete(float s, float l,int quan) {
		for(float j=s*10; j<=l*10; j++) {
			for(int i=0; i<list.length; i++) {
				if(list[i]==null) break;
				if(list[i].day==j/10) {
					list[i].quan -= quan;
					return;
				}
			}
		}
	};
}
