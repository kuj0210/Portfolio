import java.util.Scanner;

class Goods {
	protected String name;
	protected int price;
	protected int quan;
	protected int salequan;
	protected int event;
}
class GoodsList {
	protected Goods[] list;
	Scanner scanner = new Scanner(System.in);
	public GoodsList() {		
		list = new Goods[256];	
	}
	public void add(){
		System.out.println("�߰��� ��ǰ�� �̸��� �Է��ϼ���");
		System.out.print(">�Է�:");
		String name = scanner.next();
		System.out.println("�߰��� ��ǰ�� ������ �Է��ϼ���");
		System.out.print(">�Է�:");
		int price  = scanner.nextInt();
		System.out.println("�߰��� ��ǰ�� ���� �Է��ϼ���");
		System.out.print(">�Է�:");
		int quan = scanner.nextInt();
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i]=new Goods();
				list[i].name = name;
				list[i].price = price;
				list[i].quan = quan;
				return;
			}
		}
	};
	public void add(String name, int price, int quan){
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i]=new Goods();
				list[i].name = name;
				list[i].price = price;
				list[i].quan = quan;
				return;
			}
		}
	};
	public void remove(){
		System.out.println("������ ��ǰ�� �̸��� �Է��ϼ���");
		System.out.print(">�Է�:");
		String remove_name = scanner.next();
		for(int i=0; i<list.length; i++) {
			if(list[i].name.equals(remove_name)) {
				for(int j=i; j<list.length; j++) {
					list[j] = list[j+1];
					if(list[j+2]==null) {
						list[j+1]=null;
						return;
					}
				}
			}
		}
		return;
	};
	public void showList(){
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		System.out.println("��ǰ ���");
		System.out.println("��ǰ�� / ���� / ���� / ���ο���");
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].quan<=0) continue;
			if(list[i].event>0) {
				System.out.println(list[i].name + " / " + list[i].price + " / " + list[i].quan + " / ������ " + list[i].event + "%����");
			}
			else {
				System.out.println(list[i].name + " / " + list[i].price + " / " + list[i].quan);
			}
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	};
	public int sale(String name, int salequan) {
		int price=0;
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].name.equals(name)) {
				list[i].quan -= salequan;
				list[i].salequan += salequan;
				if(list[i].event>0) {
					price = list[i].price*salequan*(100-list[i].event)/100;
					break;
				}
				else {
					price = list[i].price*salequan;
				}
			}
		}
		return price;
	};
	public void setEvent(String name,int event){
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].name.equals(name)) {
				list[i].event = event;
			}
		}
	};
	public int check(String name, int quan){
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].name.equals(name) && list[i].quan<quan) {
				return quan-list[i].quan;
			}
		}
		return 0;
	}
}