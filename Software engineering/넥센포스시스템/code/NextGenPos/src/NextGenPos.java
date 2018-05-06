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
		goods.add("��",1000,30);
		goods.add("���",1500,30);
		goods.add("����",1000,30);
		cashier.add("�����","on_11","1111");
		cashier.add("���غ�","goqls2002","1234");	
		RegisterList tmp_reg1 = new RegisterList();
		tmp_reg1.enterReg("��", 5);
		int tmp_price1[] = new int[1];
		tmp_price1[0] = 5000;		
		receipt.add(1, tmp_reg1, tmp_price1, 5000, 10000, (10000-5000), "����", "");
		RegisterList tmp_reg2 = new RegisterList();
		tmp_reg2.enterReg("���", 3);
		tmp_reg2.enterReg("����", 2);
		int tmp_price2[] = new int[2];
		tmp_price2[0] = 4500;
		tmp_price2[1] = 2000;
		receipt.add(2, tmp_reg2, tmp_price2, 6500, 6500, 4500, "ī��", "BC");
		num = 2;
	};
	public void saveDataBase(){
		System.out.println("������ ���� �Ϸ�!");
	};
	public void login(){
		String id;
		String pw;
		int i=0;
		while(true) {
			System.out.println("�α����� ID : ");
			id = scanner.next();
			System.out.println("��й�ȣ : ");
			pw = scanner.next();
			if(id.equals("admin") && pw.equals("0000")) {
				System.out.println("�α��� ����! (�����ڸ��)");
				mode = ADMIN;
				return;
			}
			else {
				for(i=0; i<cashier.list.length; i++) {
					if(cashier.list[i]==null) break;
					if(id.equals(cashier.list[i].id) && pw.equals(cashier.list[i].pw)) {
						System.out.println("�α��� ����!");
						mode = CASHIER;
						return;
					}
				}
				System.out.println("�α��� ����");
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
				System.out.println("������ �̸� :");
				System.out.print(">�Է�:");
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
					System.out.println("������ �̸��� ��Ȯ�� �Է��� �ּ���");
					goods.showList();
				}
			}
			System.out.println("������ ���Է� (�ݵ�� ���ڸ� �Է�)");
			System.out.print(">�Է�:");
			quan = scanner.nextInt();
			this.register.enterReg(name, quan);
			System.out.println("�����ϰ� ���� �� 'y'�Է�('y'�� �Է½� ���� �߰�)");
			System.out.print(">�Է�:");
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
		
		System.out.println("�����Ͻ� ���ǰ� ������ �Է��ϼ���");
		goods.showList();
		enterGoods();
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			while(true) {
				if((quan = goods.check(register.list[i].id, register.list[i].num))>0) {
					System.out.println(register.list[i].id + "�� ��� " + quan + "�� ��ŭ ��� �����մϴ�.");
					System.out.println(register.list[i].id + "�� ���� ���� " + (register.list[i].num-quan) + "���Դϴ�.");
					System.out.println(register.list[i].id + "�� ���ż����� �ٽ� �Է����ּ���.");
					register.list[i].num = scanner.nextInt();
				}
				else {
					break;
				}
			}
		}
		while(true) {
			System.out.println("�����Ͻðڽ��ϱ�?(y/n)");
			System.out.print(">�Է�:");
			String o = scanner.next();
			if(o.equals("y")) {
				break;
			}
			else if(o.equals("n")) {
				return;
			}
			else {
				System.out.println("'y'�� 'n'�� �Է����ּ���.");
			}
		}
		for(int i=0; i<register.list.length; i++) {
			if(register.list[i]==null) break;
			price[i] = goods.sale(register.list[i].id, register.list[i].num);
			gross_price += price[i];
		}
		System.out.println("�� ������ " + gross_price + "�Դϴ�.");
		while(true) {
			System.out.println("� ������� ������ �Ͻðڽ��ϱ�? (����/ī��)");
			System.out.print(">�Է�:");
			payment = scanner.next();
			if(payment.equals("����")) {
				while(true) {
					System.out.println("�󸶸� ���ðڽ��ϱ�?(�� ����, �ݵ�� ���ڸ� �Է�)");
					System.out.print(">�Է�:");
					money = scanner.nextInt();
					if(money<gross_price) {
						System.out.println("�� ���ݺ��� ���ų� ū �ݾ��� �ֽñ� �ٶ��ϴ�.");
					}
					else {
						break;
					}
				}
				pos_money += gross_price;
				System.out.println(money + "�� �޾ҽ��ϴ�. �Ž������� " + (money-gross_price) + "���Դϴ�.");
				break;
			}
			else if(payment.equals("ī��")) {
				System.out.println("ī�� ���� : ");
				System.out.print(">�Է�:");
				card = scanner.next();
				payCredit(card);
				break;
			}
			else {
				
				System.out.println("'����'�̳� 'ī��'�� �Է����ּ���");
			}
		}
		num++;
		receipt.add(num, register, price, gross_price, money, (money-gross_price), payment, card);
		receipt.showReceipt(num);
		register = new RegisterList();
	};
	public void payCredit(String card){
		System.out.println(card + "(ī��) ������.");
		System.out.println(card + "(ī��) ������..");
		System.out.println(card + "(ī��) ������...");
		System.out.println("ī�� ���� �Ϸ�!");
	};
	public void refundEnterGoods(){
		int num;
		while(true) { 
			this.receipt.showList();
			System.out.println(">ȯ���� ������ ��ȣ �Է� : ");
			num = scanner.nextInt();
			for(int i=0; i<receipt.list.length; i++) {
				if(receipt.list[i]==null) break;
				if(receipt.list[i].num==num) {
					if(receipt.list[i].payment.equals("����")) {
						System.out.println("ȯ�ҹ����� �ݾ��� " + receipt.list[i].gross_price +"�� �Դϴ�.");
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
					System.out.println("�ùٸ� ������ ��ȣ�� �Է��� �ּ���.");
				}
			}
		}
	};
	public void refundCredit(String card){
		System.out.println(card + "(ī��) ���� �����.");
		System.out.println(card + "(ī��) ���� �����..");
		System.out.println(card + "(ī��) ���� �����...");
		System.out.println("���� ��� �Ϸ�!");
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
		System.out.println("�Ǹŷ�����(�Ǹŷ� ������)");
		System.out.println("  ��ǰ�� / �Ǹŷ�");
		for(int i=0; i<agoods.list.length; i++) {
			if(agoods.list[i]==null) break;
			System.out.println(agoods.list[i].name + " / " + agoods.list[i].salequan + "��");
		}
		System.out.println("���� ������ ���� �Ѿ� : " + pos_money + "��");
	};
	public void run(){
		int menu;
		login();
		while(true) {		
			System.out.println("�޴� ����");
			System.out.println("1: ����\n2: ȯ��\n3: ��ǰ����\n4: ��������\n5: �̺�Ʈ���\n6: �Ǹŷ�����\n7: �������ȯ\n0: ����");
			System.out.print(">�Է�:");
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
					System.out.println("������ �����ϴ�.");
					break;
				}
				while(true) {
					System.out.println("1 �Է� : ��ǰ���, 2 �Է� : ��ǰ����");
					System.out.print(">�Է�:");
					int o = scanner.nextInt();
					if(o==1) {
						goods.add();
						System.out.println("��ǰ �߰��Ϸ�!");
						goods.showList();
						break;
					}
					else if (o==2) {
						goods.showList();
						goods.remove();
						System.out.println("��ǰ �����Ϸ�!");
						goods.showList();
						break;
					}
					else {
						System.out.println("'1'�̳� '2'�� �Է��� �ֽñ� �ٶ��ϴ�.");
						System.out.print(">�Է�:");
					}
				}
				break;
			case 4 :
				if(mode==CASHIER) {
					System.out.println("������ �����ϴ�.");
					break;
				}
				while(true) {
					System.out.println("1 �Է� : �������, 2 �Է� : ��������");
					System.out.print(">�Է�:");
					int o = scanner.nextInt();
					if(o==1) {
						cashier.add();
						cashier.showList();
						System.out.println("���� ��ϿϷ�!");
						break;
					}
					else if (o==2) {
						cashier.showList();
						cashier.remove();
						System.out.println("���� �����Ϸ�!");
						cashier.showList();
						break;
					}
					else {
							System.out.println("'1'�̳� '2'�� �Է��� �ֽñ� �ٶ��ϴ�.");
						}
				}
				break;
			case 5 :
				enterGoods();
				for(int i=0; i<register.list.length; i++) {
					if(register.list[i]==null) break;
					goods.setEvent(register.list[i].id, register.list[i].num);
				}
				System.out.println("�̺�Ʈ ���� �Ϸ�!");
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

