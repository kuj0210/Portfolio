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
		System.out.println("추가할 상품의 이름을 입력하세요");
		System.out.print(">입력:");
		String name = scanner.next();
		System.out.println("추가할 상품의 가격을 입력하세요");
		System.out.print(">입력:");
		int price  = scanner.nextInt();
		System.out.println("추가할 상품의 양을 입력하세요");
		System.out.print(">입력:");
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
		System.out.println("삭제할 상품의 이름을 입력하세요");
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
		System.out.println("제품 목록");
		System.out.println("제품명 / 가격 / 수량 / 할인여부");
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) break;
			if(list[i].quan<=0) continue;
			if(list[i].event>0) {
				System.out.println(list[i].name + " / " + list[i].price + " / " + list[i].quan + " / 결제시 " + list[i].event + "%할인");
			}
			else {
				System.out.println(list[i].name + " / " + list[i].price + " / " + list[i].quan);
			}
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
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