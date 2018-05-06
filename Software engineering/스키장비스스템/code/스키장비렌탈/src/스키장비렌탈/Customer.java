package ��Ű���Ż;

import java.util.Scanner;

class Customer {
	protected int state;
	//protected int num;
	protected String name;
	protected String phone_num;
	protected int gross_price;
	int price[];
	protected int received_money;
	protected int change;
	protected RegisterList goods;
	protected String payment_type;
	protected Period day;
	protected String kind_of_card;
	public Customer(){
		day = new Period();
	}
}
class CustomerList {
	public final int NOTRENT = 0;
	public final int RENTING = 1;
	protected Customer list[];
	public CustomerList() {
		list = new Customer[256];
	}
	public void add(Customer cus){
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i] = new Customer();
				list[i] = cus;
				break;
			}
		}
	};
	public void remove(String _phone_num){
		for(int i=0; i<list.length; i++) {
			if(list[i].phone_num.equals(_phone_num)) {
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
	public int getCustomer(String _phone_num) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null)	break;
			if(list[i].phone_num ==_phone_num) {
				return i;
			}
		}
		return -1;
	};
	public void showCustomer(String _phone_num) {
		int index=0;
		for(int i=0; i<list.length; i++) {
			if(list[i]==null)	{
				System.out.println("�ش� ��ȣ�� ����� ������ �����ϴ�.");
				break;
			}
			if(list[i].phone_num.equals(_phone_num)) {
				index = i;
				break;
			}
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		System.out.println("���� : " + list[index].name);
		System.out.println("�� ��ȣ : " + list[index].phone_num);
		System.out.print("�뿩�Ⱓ : " + list[index].day.list[0].day + " ~ ");
		for(int i=0; i<list[index].day.list.length; i++) {
			if(list[index].day.list[i]==null) {
				System.out.println(list[index].day.list[i-1].day);
				break;
			}
		}
		for(int j=0; j<list[index].goods.list.length; j++) {
			if(list[index].goods.list[j]==null) break;
			System.out.println("��� �� :"+list[index].goods.list[j].id + " / ���� �뿩�� : " + list[index].price[j]/list[index].goods.list[j].num  +"�� / �뿩���� : " + list[index].goods.list[j].num + "��" );
		}
		System.out.println("������� : " + list[index].payment_type);
		if(list[index].payment_type.equals("����")) {
			System.out.println("�հ� : " + list[index].gross_price + "��");
			System.out.println("���� �� : " + list[index].received_money + "��");
			System.out.println("�Ž��� �� : " + list[index].change+ "��");
		}
		else {
			System.out.println("���� �ݾ� :"+list[index].gross_price);
			System.out.println("ī�� ���� :"+list[index].kind_of_card);
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	}
	public void showRetalList() {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null)	break;
			if(list[i].state ==	RENTING) {
				showCustomer(list[i].phone_num);
			}
		}
	}; 
	public void showPayedlList() {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null)	break;
			if(list[i].state ==	NOTRENT) {
				showCustomer(list[i].phone_num);
			}
		}	
	}; 
	public void showRefund(String _phone_num) {
		int index=0;
		for(int i=0; i<list.length; i++) {
			if(list[i]==null)	{
				System.out.println("�ش� ��ȣ�� ����� ������ �����ϴ�.");
				break;
			}
			if(list[i].phone_num.equals(_phone_num)) {
				index = i;
				break;
			}
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		System.out.println("���� : " + list[index].name);
		System.out.println("�� ��ȣ : " + list[index].phone_num);
		System.out.print("�뿩�Ⱓ : " + list[index].day.list[0].day + " ~ ");
		for(int i=0; i<list[index].day.list.length; i++) {
			if(list[index].day.list[i]==null) {
				System.out.println(list[index].day.list[i-1].day);
				break;
			}
		}
		for(int j=0; j<list[index].goods.list.length; j++) {
			if(list[index].goods.list[j]==null) break;
			System.out.println("��� �� :"+list[index].goods.list[j].id + " / �뿩�� : " + list[index].price[j]  +"�� / �뿩���� : " + list[index].goods.list[j].num + "��" );
		}
		System.out.println("������� : " + list[index].payment_type);
		if(list[index].payment_type.equals("����")) {
			System.out.println("ȯ�� �ݾ� : " + list[index].gross_price + "��");
		}
		else {
			System.out.println("ȯ�� �ݾ� : "+list[index].gross_price + "��");
			System.out.println("ī�� ���� : "+list[index].kind_of_card);
			System.out.println("���� ��� �Ϸ�");
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	}
	public void showList(){
		for(int index=0; index<list.length; index++) {
			if(list[index]==null) break;
			System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
			System.out.println("���� : " + list[index].name);
			System.out.println("�� ��ȣ : " + list[index].phone_num);
			System.out.print("�뿩�Ⱓ : " + list[index].day.list[0].day + " ~ ");
			for(int i=0; i<list[index].day.list.length; i++) {
				if(list[index].day.list[i]==null) {
					System.out.println(list[index].day.list[i-1].day);
					break;
				}
			}
			for(int j=0; j<list[index].goods.list.length; j++) {
				if(list[index].goods.list[j]==null) break;
				System.out.println("��� �� :"+list[index].goods.list[j].id + " / �뿩�� : " + list[index].price[j]  +"�� / �뿩���� : " + list[index].goods.list[j].num + "��" );
			}
			System.out.println("������� : " + list[index].payment_type);
			if(list[index].payment_type.equals("����")) {
				System.out.println("�հ� : " + list[index].gross_price + "��");
				System.out.println("���� �� : " + list[index].received_money + "��");
				System.out.println("�Ž��� �� : " + list[index].change+ "��");
			}
			else {
				System.out.println("���� �ݾ� :"+list[index].gross_price);
				System.out.println("ī�� ���� :"+list[index].kind_of_card);
			}
			System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		}		
		
	}
	public void periodUpdate_Goods(int i,int n, int flag) {
		if(flag==1) {
			for(int j=0; j<list[i].day.list.length; j++) {
				if(list[i].day.list[j]==null) break;
				list[i].day.list[j].quan += n;
			}
		}
		else if(flag==-1) {
			for(int j=0; j<list[i].day.list.length; j++) {
				if(list[i].day.list[j]==null) break;
				list[i].day.list[j].quan -= n;
			}
		}
	}
}
