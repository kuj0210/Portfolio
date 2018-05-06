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
	protected ReceiptList receipt;
	protected int pos_money;
	Scanner scanner = new Scanner(System.in);
 
	public PosSystem(){
		cashier = new CashierList();
		goods = new GoodsList();
		register = new RegisterList();
		receipt = new ReceiptList();
		pos_money = 150000;
	};
	public void loadDataBase(){
		adName = "admin";
		adpw = "0000";
		goods.add("빵",1000,30);
		goods.add("라면",1500,30);
		goods.add("과자",1000,30);
		cashier.add("김우진","on_11","1111");
		cashier.add("김해빈","goqls2002","1234");	
		RegisterList tmp_reg1 = new RegisterList();
		tmp_reg1.enterReg("빵", 5);
		int tmp_price1[] = new int[1];
		tmp_price1[0] = 5000;		
		receipt.add(1, tmp_reg1, tmp_price1, 5000, 10000, (10000-5000), "현금", "");
		RegisterList tmp_reg2 = new RegisterList();
		tmp_reg2.enterReg("라면", 3);
		tmp_reg2.enterReg("과자", 2);
		int tmp_price2[] = new int[2];
		tmp_price2[0] = 4500;
		tmp_price2[1] = 2000;
		receipt.add(2, tmp_reg2, tmp_price2, 6500, 6500, 4500, "카드", "BC");
		num = 2;
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
			System.out.println("적용할 값입력 (반드시 숫자만 입력)");
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
	public void saleEnterGoods(){
		int gross_price=0;
		int price[] = new int[100];
		int money=0;
		String payment;
		String card="";
		int quan;
		
		System.out.println("구매하실 물건과 수량을 입력하세요");
		goods.showList();
		enterGoods();
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			while(true) {
				if((quan = goods.check(register.list[i].id, register.list[i].num))>0) {
					System.out.println(register.list[i].id + "의 재고가 " + quan + "개 만큼 재고가 부족합니다.");
					System.out.println(register.list[i].id + "의 현재 재고는 " + (register.list[i].num-quan) + "개입니다.");
					System.out.println(register.list[i].id + "의 구매수량을 다시 입력해주세요.");
					register.list[i].num = scanner.nextInt();
				}
				else {
					break;
				}
			}
		}
		while(true) {
			System.out.println("구매하시겠습니까?(y/n)");
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
		num++;
		receipt.add(num, register, price, gross_price, money, (money-gross_price), payment, card);
		receipt.showReceipt(num);
		register = new RegisterList();
	};
	public void payCredit(String card){
		System.out.println(card + "(카드) 결제중.");
		System.out.println(card + "(카드) 결제중..");
		System.out.println(card + "(카드) 결제중...");
		System.out.println("카드 결제 완료!");
	};
	public void refundEnterGoods(){
		int num;
		while(true) { 
			this.receipt.showList();
			System.out.println(">환불할 영수증 번호 입력 : ");
			num = scanner.nextInt();
			for(int i=0; i<receipt.list.length; i++) {
				if(receipt.list[i]==null) break;
				if(receipt.list[i].num==num) {
					if(receipt.list[i].payment.equals("현금")) {
						System.out.println("환불받으실 금액은 " + receipt.list[i].gross_price +"원 입니다.");
						pos_money -= receipt.list[i].gross_price;
						receipt.showRefundReceipt(num);
						return;
					}
					else {
						refundCredit(receipt.list[i].card);
						receipt.showRefundReceipt(num);	
						return;
					}
				}
				else if(receipt.list[i].num!=num && receipt.list[i]==null) {
					System.out.println("올바른 영수증 번호를 입력해 주세요.");
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
	public void analisysGoods(){
		GoodsList agoods = new GoodsList();
		agoods = goods;
		for(int i=0; i<agoods.list.length; i++){
			if(agoods.list[i]==null) break;
			for(int j=i+1; j<agoods.list.length; j++){
				if(agoods.list[j]==null) break;
				if(agoods.list[i].salequan<agoods.list[j].salequan) {                     
					Goods temp = agoods.list[i];                 
					agoods.list[i] = agoods.list[j];                     
					agoods.list[j] = temp;
				}
			}
		}
		System.out.println("판매량정보(판매량 높은순)");
		System.out.println("  상품명 / 판매량");
		for(int i=0; i<agoods.list.length; i++) {
			if(agoods.list[i]==null) break;
			System.out.println(agoods.list[i].name + " / " + agoods.list[i].salequan + "개");
		}
		System.out.println("현재 포스기 현금 총액 : " + pos_money + "원");
	};
	public void run(){
		int menu;
		login();
		while(true) {		
			System.out.println("메뉴 선택");
			System.out.println("1: 구매\n2: 환불\n3: 상품관리\n4: 직원관리\n5: 이벤트등록\n6: 판매량정보\n7: 사용자전환\n0: 종료");
			System.out.print(">입력:");
			menu = scanner.nextInt();
			switch(menu) {
			case 1 :
				saleEnterGoods();
				break;
			case 2 :
				refundEnterGoods();
				break;
			case 3 :
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
			case 4 :
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
			case 5 :
				enterGoods();
				for(int i=0; i<register.list.length; i++) {
					if(register.list[i]==null) break;
					goods.setEvent(register.list[i].id, register.list[i].num);
				}
				System.out.println("이벤트 적용 완료!");
				register = new RegisterList();
				break;
			case 6 :
				analisysGoods();
				break;
			case 7 :
				login();
				break;				
			case 0 :
				return;
			}
		}
	};
}
public class NextGenPos {
	public static void main(String[] args){
		PosSystem ps = new PosSystem();
		ps.loadDataBase();
		ps.run();
		
	}
}

