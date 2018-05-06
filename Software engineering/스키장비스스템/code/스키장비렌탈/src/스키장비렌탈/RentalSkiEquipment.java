package 스키장비렌탈;

import java.util.Scanner;

class PosSystem {
	public final int ADMIN = 0;
	public final int CASHIER = 1;
	protected String adName;
	protected String adpw;
	protected int mode;
	protected int num;
	protected CashierList cashier;
	protected GoodsList goods;
	protected RegisterList register;
	protected CustomerList customer;
	protected int pos_money;
	Scanner scanner = new Scanner(System.in);
 
	public PosSystem(){
		cashier = new CashierList();
		goods = new GoodsList();
		register = new RegisterList();
		customer = new CustomerList();
		pos_money = 150000;
	};
	public void loadDataBase(){
		adName = "admin";
		adpw = "0000";
		Customer db_customer = new Customer();
		goods.add("스키",20000,30);
		goods.add("보드",20000,30);
		goods.add("고급의류",20000,30);
		goods.add("일반의류",10000,30);
		goods.add("보호대",5000,30);
		goods.add("고글",5000,30);
		goods.add("헬멧",5000,30);
		cashier.add("김우진","on_11","1111");
		cashier.add("김해빈","goqls2002","1234");
		goods.setEvent("스키",50);
		goods.setEvent("보드",50);
		RegisterList tmp_reg1 = new RegisterList();
		tmp_reg1.enterReg("스키", 5);
		tmp_reg1.enterReg("일반의류", 5);
		tmp_reg1.enterReg("보호대", 5);
		tmp_reg1.enterReg("헬멧", 5);
		int tmp_price1[] = new int[4];
		tmp_price1[0] = 100000;
		tmp_price1[1] = 50000;
		tmp_price1[2] = 25000;
		tmp_price1[3] = 25000;
		db_customer.goods = tmp_reg1;
		db_customer.price = tmp_price1;
		db_customer.name = "홍길동";
		db_customer.phone_num = "010-1234-5678";
		db_customer.day.add((float)4.1, (float)4.5,5);
		db_customer.gross_price = 200000;
		db_customer.payment_type = "카드";
		db_customer.kind_of_card = "농협";		
		goods.list[0].day.add((float)4.1, (float)4.5, 5);
		goods.list[3].day.add((float)4.1, (float)4.5, 5);
		goods.list[5].day.add((float)4.1, (float)4.5, 5);
		goods.list[6].day.add((float)4.1, (float)4.5, 5);
		customer.add(db_customer);
		int i = customer.getCustomer("010-1234-5678");
		customer.list[i].state=1;
		customer.periodUpdate_Goods(i, 5, 1);
	};
	public void saveDataBase(){
		System.out.println("데이터 저장 완료!");
	};
	public void login(){
		String id;
		String pw;
		int i=0;
		while(true) {
			System.out.println("로그인할 ID : ");
			id = scanner.next();
			System.out.println("비밀번호 : ");
			pw = scanner.next();
			if(id.equals("admin") && pw.equals("0000")) {
				System.out.println("로그인 성공! (관리자모드)");
				mode = ADMIN;
				return;
			}
			else {
				for(i=0; i<cashier.list.length; i++) {
					if(cashier.list[i]==null) break;
					if(id.equals(cashier.list[i].id) && pw.equals(cashier.list[i].pw)) {
						System.out.println("로그인 성공!");
						mode = CASHIER;
						return;
					}
				}
				System.out.println("로그인 실패");
			}
		}
	};
	public void enterGoods(){
		String name;
		int quan;
		int flag = 0;
		String o;
		while(true) {
			while(true) {
				System.out.println("물건의 이름 :");
				System.out.print(">입력:");
				name = scanner.next();
				for(int i=0; i<goods.list.length; i++) {
					if(goods.list[i]==null) break;
					if(name.equals(goods.list[i].name)) {
						flag = 1;
						break;
					}
				}
				if(flag==1)	{
					flag = 0;
					break;				
				}
				else if(flag==0) {
					System.out.println("물건의 이름을 정확히 입력해 주세요");
					goods.showList();
				}
			}
			System.out.println("수량 입력 (반드시 숫자만 입력)");
			System.out.print(">입력:");
			quan = scanner.nextInt();
			this.register.enterReg(name, quan);
			System.out.println("적용하고 나갈 시 'y'입력('y'외 입력시 물건 추가)");
			System.out.print(">입력:");
			o = scanner.next();
			if(o.equals("y")) {
				break;
			}
		}
	};
	public void setEnterGoodsEvent(){
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			goods.setEvent(register.list[i].id, register.list[i].num);
		}
	};
	public void rentEnterGoods() {
		Customer tmp_customer = new Customer();
		int gross_price=0;
		int price[] = new int[100];
		int money=0;
		String payment;
		String card="";
		int quan;
		System.out.println("스키장비를 대여할 첫번째 날짜를 입력하세요(ex)6월 1일 -> '6.1'입력)");
		System.out.println(">입력 : ");
		float first_day = scanner.nextFloat();		
		System.out.println("스키장비를 대여할 마지막 날짜를 입력하세요(ex)6월 1일 -> '6.1'입력)");
		System.out.println(">입력 : ");
		float last_day= scanner.nextFloat();	
		System.out.println("대여하실 장비 수량을 입력하세요");
		goods.showList();
		enterGoods();
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			while(true) {
				for(float j = first_day*10; j <=last_day*10; j++) {
					for(int k=0; k<goods.list.length; k++) {
						if(goods.list[k]==null) break;
						if(goods.list[k].name.equals(register.list[i].id)) {
							quan = goods.list[k].isRent(j);
							if(quan<register.list[i].num) {
								System.out.println(j/10 + "일의 " +  register.list[i].id + "의 재고가 " + (register.list[i].num-quan) + "개 만큼 재고가 부족합니다.");
								System.out.println(register.list[i].id + "의 현재 재고는 " + quan + "개입니다.");
								System.out.println(register.list[i].id + "의 대여수량을 다시 입력해주세요.");
								System.out.println(">입력 : ");	
								register.list[i].num = scanner.nextInt();
							}
						}							
					}
				}
				break;
			}
		}
		System.out.println("성함을 입력하세요");
		System.out.println(">입력 : ");	
		String name = scanner.next();
		System.out.println("휴대폰 번호를 입력하세요");
		System.out.println(">입력 : ");	
		String phone_num = scanner.next();
		while(true) {
			System.out.println("예약 하시겠습니까?(y/n)");
			System.out.print(">입력:");
			String o = scanner.next();
			if(o.equals("y")) {
				break;
			}
			else if(o.equals("n")) {
				return;
			}
			else {
				System.out.println("'y'나 'n'을 입력해주세요.");
			}
		}
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			price[i] = goods.sale(register.list[i].id, register.list[i].num);
			gross_price += price[i];
		}
		gross_price *= ((last_day*10)-(first_day*10)+1);
		System.out.println("총 가격은 " + gross_price + "입니다.");
		while(true) {
			System.out.println("어떤 방식으로 결제를 하시겠습니까? (현금/카드)");
			System.out.print(">입력:");
			payment = scanner.next();
			if(payment.equals("현금")) {
				while(true) {
					System.out.println("얼마를 내시겠습니까?(원 생략, 반드시 숫자만 입력)");
					System.out.print(">입력:");
					money = scanner.nextInt();
					if(money<gross_price) {
						System.out.println("총 가격보다 같거나 큰 금액을 주시기 바랍니다.");
					}
					else {
						break;
					}
				}
				pos_money += gross_price;
				System.out.println(money + "원 받았습니다. 거스름돈은 " + (money-gross_price) + "원입니다.");
				break;
			}
			else if(payment.equals("카드")) {
				System.out.println("카드 종류 : ");
				System.out.print(">입력:");
				card = scanner.next();
				payCredit(card);
				break;
			}
			else {
				System.out.println("'현금'이나 '카드'를 입력해주세요");
			}
		} 
		if(payment.equals("카드")) {
			tmp_customer.goods = register;
			tmp_customer.price = price;
			tmp_customer.name = name;
			tmp_customer.phone_num = phone_num;
			for(int j=0; j<register.list.length; j++) {
				if(register.list==null) break;
				tmp_customer.day.add(first_day,last_day,register.list[0].num);
			}
			tmp_customer.gross_price = gross_price;
			tmp_customer.payment_type = payment;
			tmp_customer.kind_of_card = card;
		}
		else if(payment.equals("현금")) {
			tmp_customer.goods = register;
			tmp_customer.price = price;
			tmp_customer.name = name;
			tmp_customer.phone_num = phone_num;
			for(int j=0; j<register.list.length; j++) {
				if(register.list==null) break;
				tmp_customer.day.add(first_day,last_day,register.list[0].num);
			}
			tmp_customer.received_money = money;
			tmp_customer.change = money-gross_price;
			tmp_customer.gross_price = gross_price;
			tmp_customer.payment_type = payment;
		}
		for(int i=0; i<goods.list.length; i++) {
			if(goods.list[i]==null) break;
			for(int j=0; j<register.list.length; j++) {
				if(register.list[j]==null) break;
				if(goods.list[i].name.equals(register.list[j].id)) {
					goods.list[i].day.add(first_day,last_day,register.list[j].num);
				}
			}
		}
		customer.add(tmp_customer);
		customer.getCustomer(phone_num);
		int i = customer.getCustomer(phone_num);
		customer.periodUpdate_Goods(i, register.list[0].num, 1);
		customer.list[i].state=1;
		customer.showCustomer(phone_num);
		register = new RegisterList();
	}
	public void payCredit(String card){
		System.out.println(card + "(카드) 결제중.");
		System.out.println(card + "(카드) 결제중..");
		System.out.println(card + "(카드) 결제중...");
		System.out.println("카드 결제 완료!");
	};
	public void cancle(){
		String phone_num;
		while(true) { 
			this.customer.showList();
			System.out.println("휴대폰 번호를 입력하세요");
			System.out.print(">입력: ");
			phone_num = scanner.next();
			float first_day,last_day=0;
			for(int i=0; i<customer.list.length; i++) {
				if(customer.list[i]==null) break;
				if(customer.list[i].phone_num.equals(phone_num)) {
					if(customer.list[i].payment_type.equals("현금")) {
						System.out.println("환불받으실 금액은 " + customer.list[i].gross_price +"원 입니다.");
						pos_money -= customer.list[i].gross_price;
						customer.showRefund(phone_num);
						first_day = customer.list[i].day.list[0].day;
						for(int j=0; j<customer.list[i].day.list.length; j++) {
							if(customer.list[i].day.list[j]==null) {
								last_day = customer.list[i].day.list[j-1].day;
								break;
							}
						}
						for(int j=0; j<customer.list[i].goods.list.length; j++) {
							if(customer.list[i].goods.list[j]==null) break;
							if(goods.list[i].name.equals(customer.list[i].goods.list[j].id)) {
								goods.list[i].day.delete(first_day,last_day,customer.list[i].goods.list[j].num);
							}
						}
						customer.remove(phone_num);
						return;
					}
					else {
						refundCredit(customer.list[i].kind_of_card);
						customer.showRefund(phone_num);
						first_day = customer.list[i].day.list[0].day;
						for(int j=0; j<customer.list[i].day.list.length; j++) {
							if(customer.list[i].day.list[j]==null) {
								last_day = customer.list[i].day.list[j-1].day;
								break;
							}
						}
						for(int j=0; j<customer.list[i].goods.list.length; j++) {
							if(customer.list[i].goods.list[j]==null) break;
							if(goods.list[i].name.equals(customer.list[i].goods.list[j].id)) {
								goods.list[i].day.delete(first_day,last_day,customer.list[i].goods.list[j].num);
							}
						}
						customer.remove(phone_num);
						return;
					}
				}
				else if(customer.list[i].phone_num.equals(phone_num) && customer.list[i]==null) {
					System.out.println("올바른 휴대폰 번호를 입력해 주세요.");
				}
			}
		}		
	};
	public void refundCredit(String card){
		System.out.println(card + "(카드) 승인 취소중.");
		System.out.println(card + "(카드) 승인 취소중..");
		System.out.println(card + "(카드) 승인 취소중...");
		System.out.println("승인 취소 완료!");
	};
	public void returnGoods(){
		String phone_num;
		while(true) { 
			this.customer.showList();
			System.out.println("휴대폰 번호를 입력하세요");
			System.out.print(">입력: ");
			phone_num = scanner.next();
			float first_day,last_day=0;
			for(int i=0; i<customer.list.length; i++) {
				if(customer.list[i]==null) break;
				if(customer.list[i].phone_num.equals(phone_num)) {
					customer.periodUpdate_Goods(i, customer.list[i].day.list[0].quan, -1);
					customer.list[i].state = 0;
					first_day = customer.list[i].day.list[0].day;
					for(int j=0; j<customer.list[i].day.list.length; j++) {
						if(customer.list[i].day.list[j]==null) {
							last_day = customer.list[i].day.list[j-1].day;
							break;
						}
					}
					for(int j=0; j<customer.list[i].goods.list.length; j++) {
						if(customer.list[i].goods.list[j]==null) break;
						if(goods.list[i].name.equals(customer.list[i].goods.list[j].id)) {
							goods.list[i].day.delete(first_day,last_day,customer.list[i].goods.list[j].num);
						}
					}
					return;
				}
				else if(customer.list[i].phone_num.equals(phone_num) && customer.list[i]==null) {
					System.out.println("올바른 휴대폰 번호를 입력해 주세요.");
				}
			}
		}
	};
	public void run(){
		int menu;
		login();
		while(true) {		
			System.out.println("메뉴 선택");
			System.out.println("1: 예약\n2: 취소\n3: 반납\n4: 대여가능 장비수량 정보\n5: 상품관리\n6: 직원관리\n7: 이벤트등록\n8: 사용자전환\n0: 종료");
			System.out.print(">입력:");
			menu = scanner.nextInt();
			switch(menu) {
			case 1 :
				rentEnterGoods();
				break;
			case 2 :
				cancle();
				break;
			case 3 :
				returnGoods();
				break;
			case 4 :
				System.out.println("날짜를 입력해주세요");
				System.out.print(">입력:");
				float day = scanner.nextFloat();
				goods.showList();
				System.out.println("장비명을 입력해주세요");
				System.out.print(">입력:");
				String name = scanner.next();
				for(int i=0; i<goods.list.length; i++) {
					if(goods.list[i]==null) break;
					if(goods.list[i].name.equals(name)) {
						System.out.println(day + "일에 " + name + "의 재고는" + goods.list[i].isRent(day) + "개 입니다.");
					}
				}
				break;
			case 5 :
				if(mode==CASHIER) {
					System.out.println("권한이 없습니다.");
					break;
				}
				while(true) {
					System.out.println("1 입력 : 상품등록, 2 입력 : 상품삭제");
					System.out.print(">입력:");
					int o = scanner.nextInt();
					if(o==1) {
						goods.add();
						System.out.println("상품 추가완료!");
						goods.showList();
						break;
					}
					else if (o==2) {
						goods.showList();
						goods.remove();
						System.out.println("상품 삭제완료!");
						goods.showList();
						break;
					}
					else {
						System.out.println("'1'이나 '2'를 입력해 주시기 바랍니다.");
						System.out.print(">입력:");
					}
				}
				break;
			case 6 :
				if(mode==CASHIER) {
					System.out.println("권한이 없습니다.");
					break;
				}
				while(true) {
					System.out.println("1 입력 : 직원등록, 2 입력 : 직원삭제");
					System.out.print(">입력:");
					int o = scanner.nextInt();
					if(o==1) {
						cashier.add();
						cashier.showList();
						System.out.println("직원 등록완료!");
						break;
					}
					else if (o==2) {
						cashier.showList();
						cashier.remove();
						System.out.println("직원 삭제완료!");
						cashier.showList();
						break;
					}
					else {
							System.out.println("'1'이나 '2'를 입력해 주시기 바랍니다.");
						}
				}
				break;
			case 7 :
				enterGoods();
				if(mode==CASHIER) {
					System.out.println("권한이 없습니다.");
					break;
				}
				for(int i=0; i<register.list.length; i++) {
					if(register.list[i]==null) break;
					goods.setEvent(register.list[i].id, register.list[i].num);
				}
				System.out.println("이벤트 적용 완료!");
				register = new RegisterList();
				break;
			case 8 :
				login();
				break;				
			case 0 :
				return;
			}
		}
	};
}
public class RentalSkiEquipment {
	public static void main(String[] args){
		PosSystem ps = new PosSystem();
		ps.loadDataBase();
		ps.run();
		
	}
}
