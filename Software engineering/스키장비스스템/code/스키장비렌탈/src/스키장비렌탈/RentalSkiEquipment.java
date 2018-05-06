package ��Ű���Ż;

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
		goods.add("��Ű",20000,30);
		goods.add("����",20000,30);
		goods.add("����Ƿ�",20000,30);
		goods.add("�Ϲ��Ƿ�",10000,30);
		goods.add("��ȣ��",5000,30);
		goods.add("���",5000,30);
		goods.add("���",5000,30);
		cashier.add("�����","on_11","1111");
		cashier.add("���غ�","goqls2002","1234");
		goods.setEvent("��Ű",50);
		goods.setEvent("����",50);
		RegisterList tmp_reg1 = new RegisterList();
		tmp_reg1.enterReg("��Ű", 5);
		tmp_reg1.enterReg("�Ϲ��Ƿ�", 5);
		tmp_reg1.enterReg("��ȣ��", 5);
		tmp_reg1.enterReg("���", 5);
		int tmp_price1[] = new int[4];
		tmp_price1[0] = 100000;
		tmp_price1[1] = 50000;
		tmp_price1[2] = 25000;
		tmp_price1[3] = 25000;
		db_customer.goods = tmp_reg1;
		db_customer.price = tmp_price1;
		db_customer.name = "ȫ�浿";
		db_customer.phone_num = "010-1234-5678";
		db_customer.day.add((float)4.1, (float)4.5,5);
		db_customer.gross_price = 200000;
		db_customer.payment_type = "ī��";
		db_customer.kind_of_card = "����";		
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
			System.out.println("���� �Է� (�ݵ�� ���ڸ� �Է�)");
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
	public void rentEnterGoods() {
		Customer tmp_customer = new Customer();
		int gross_price=0;
		int price[] = new int[100];
		int money=0;
		String payment;
		String card="";
		int quan;
		System.out.println("��Ű��� �뿩�� ù��° ��¥�� �Է��ϼ���(ex)6�� 1�� -> '6.1'�Է�)");
		System.out.println(">�Է� : ");
		float first_day = scanner.nextFloat();		
		System.out.println("��Ű��� �뿩�� ������ ��¥�� �Է��ϼ���(ex)6�� 1�� -> '6.1'�Է�)");
		System.out.println(">�Է� : ");
		float last_day= scanner.nextFloat();	
		System.out.println("�뿩�Ͻ� ��� ������ �Է��ϼ���");
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
								System.out.println(j/10 + "���� " +  register.list[i].id + "�� ��� " + (register.list[i].num-quan) + "�� ��ŭ ��� �����մϴ�.");
								System.out.println(register.list[i].id + "�� ���� ���� " + quan + "���Դϴ�.");
								System.out.println(register.list[i].id + "�� �뿩������ �ٽ� �Է����ּ���.");
								System.out.println(">�Է� : ");	
								register.list[i].num = scanner.nextInt();
							}
						}							
					}
				}
				break;
			}
		}
		System.out.println("������ �Է��ϼ���");
		System.out.println(">�Է� : ");	
		String name = scanner.next();
		System.out.println("�޴��� ��ȣ�� �Է��ϼ���");
		System.out.println(">�Է� : ");	
		String phone_num = scanner.next();
		while(true) {
			System.out.println("���� �Ͻðڽ��ϱ�?(y/n)");
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
		gross_price *= ((last_day*10)-(first_day*10)+1);
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
		if(payment.equals("ī��")) {
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
		else if(payment.equals("����")) {
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
		System.out.println(card + "(ī��) ������.");
		System.out.println(card + "(ī��) ������..");
		System.out.println(card + "(ī��) ������...");
		System.out.println("ī�� ���� �Ϸ�!");
	};
	public void cancle(){
		String phone_num;
		while(true) { 
			this.customer.showList();
			System.out.println("�޴��� ��ȣ�� �Է��ϼ���");
			System.out.print(">�Է�: ");
			phone_num = scanner.next();
			float first_day,last_day=0;
			for(int i=0; i<customer.list.length; i++) {
				if(customer.list[i]==null) break;
				if(customer.list[i].phone_num.equals(phone_num)) {
					if(customer.list[i].payment_type.equals("����")) {
						System.out.println("ȯ�ҹ����� �ݾ��� " + customer.list[i].gross_price +"�� �Դϴ�.");
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
					System.out.println("�ùٸ� �޴��� ��ȣ�� �Է��� �ּ���.");
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
	public void returnGoods(){
		String phone_num;
		while(true) { 
			this.customer.showList();
			System.out.println("�޴��� ��ȣ�� �Է��ϼ���");
			System.out.print(">�Է�: ");
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
					System.out.println("�ùٸ� �޴��� ��ȣ�� �Է��� �ּ���.");
				}
			}
		}
	};
	public void run(){
		int menu;
		login();
		while(true) {		
			System.out.println("�޴� ����");
			System.out.println("1: ����\n2: ���\n3: �ݳ�\n4: �뿩���� ������ ����\n5: ��ǰ����\n6: ��������\n7: �̺�Ʈ���\n8: �������ȯ\n0: ����");
			System.out.print(">�Է�:");
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
				System.out.println("��¥�� �Է����ּ���");
				System.out.print(">�Է�:");
				float day = scanner.nextFloat();
				goods.showList();
				System.out.println("������ �Է����ּ���");
				System.out.print(">�Է�:");
				String name = scanner.next();
				for(int i=0; i<goods.list.length; i++) {
					if(goods.list[i]==null) break;
					if(goods.list[i].name.equals(name)) {
						System.out.println(day + "�Ͽ� " + name + "�� ����" + goods.list[i].isRent(day) + "�� �Դϴ�.");
					}
				}
				break;
			case 5 :
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
			case 6 :
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
			case 7 :
				enterGoods();
				if(mode==CASHIER) {
					System.out.println("������ �����ϴ�.");
					break;
				}
				for(int i=0; i<register.list.length; i++) {
					if(register.list[i]==null) break;
					goods.setEvent(register.list[i].id, register.list[i].num);
				}
				System.out.println("�̺�Ʈ ���� �Ϸ�!");
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
