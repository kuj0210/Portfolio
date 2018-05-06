package 스키장비렌탈;

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
		System.out.println("등록할 출납원의 이름을 입력하세요");
		System.out.print(">입력:");
		String name = scanner.next();
		System.out.println("등록할 출납원의 ID를 입력하세요");
		System.out.print(">입력:");
		String id = scanner.next();
		System.out.println("등록할 출납원의 비밀번호을 입력하세요");
		System.out.print(">입력:");
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
		System.out.println("삭제할 출납원의 이름을 입력하세요");
		System.out.print(">입력:");
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
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		System.out.println("직원 목록");
		System.out.println("직원명 / id ");
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
				System.out.println(list[i].name + " / " + list[i].id);
		}		
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	};

}