package ��Ű���Ż;

import java.util.Scanner;

class Cashier {
	protected String name;
	protected String id;
	protected String pw;
}

class CashierList {
	protected Cashier[] list;
	Scanner scanner = new Scanner(System.in);
	
	public CashierList() {		
		list = new Cashier[100];
	}
	public void add(){
		System.out.println("����� �ⳳ���� �̸��� �Է��ϼ���");
		System.out.print(">�Է�:");
		String name = scanner.next();
		System.out.println("����� �ⳳ���� ID�� �Է��ϼ���");
		System.out.print(">�Է�:");
		String id = scanner.next();
		System.out.println("����� �ⳳ���� ��й�ȣ�� �Է��ϼ���");
		System.out.print(">�Է�:");
		String pw = scanner.next();
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i]=new Cashier();
				list[i].name = name;
				list[i].id = id;
				list[i].pw = pw;
				return;
			}
		}
	};
	public void add(String name, String id, String pw){
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i]=new Cashier();
				list[i].name = name;
				list[i].id = id;
				list[i].pw = pw;
				return;
			}
		}
	};
	public void remove(){
		System.out.println("������ �ⳳ���� �̸��� �Է��ϼ���");
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
		System.out.println("���� ���");
		System.out.println("������ / id ");
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
				System.out.println(list[i].name + " / " + list[i].id);
		}		
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	};

}