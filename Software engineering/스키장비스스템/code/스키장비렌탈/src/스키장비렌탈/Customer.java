package 스키장비렌탈;

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
				System.out.println("해당 번호로 예약된 내역이 없습니다.");
				break;
			}
			if(list[i].phone_num.equals(_phone_num)) {
				index = i;
				break;
			}
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		System.out.println("고객명 : " + list[index].name);
		System.out.println("폰 번호 : " + list[index].phone_num);
		System.out.print("대여기간 : " + list[index].day.list[0].day + " ~ ");
		for(int i=0; i<list[index].day.list.length; i++) {
			if(list[index].day.list[i]==null) {
				System.out.println(list[index].day.list[i-1].day);
				break;
			}
		}
		for(int j=0; j<list[index].goods.list.length; j++) {
			if(list[index].goods.list[j]==null) break;
			System.out.println("장비 명 :"+list[index].goods.list[j].id + " / 개당 대여료 : " + list[index].price[j]/list[index].goods.list[j].num  +"원 / 대여수량 : " + list[index].goods.list[j].num + "개" );
		}
		System.out.println("결제방식 : " + list[index].payment_type);
		if(list[index].payment_type.equals("현금")) {
			System.out.println("합계 : " + list[index].gross_price + "원");
			System.out.println("받은 돈 : " + list[index].received_money + "원");
			System.out.println("거스름 돈 : " + list[index].change+ "원");
		}
		else {
			System.out.println("결제 금액 :"+list[index].gross_price);
			System.out.println("카드 종류 :"+list[index].kind_of_card);
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
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
				System.out.println("해당 번호로 예약된 내역이 없습니다.");
				break;
			}
			if(list[i].phone_num.equals(_phone_num)) {
				index = i;
				break;
			}
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		System.out.println("고객명 : " + list[index].name);
		System.out.println("폰 번호 : " + list[index].phone_num);
		System.out.print("대여기간 : " + list[index].day.list[0].day + " ~ ");
		for(int i=0; i<list[index].day.list.length; i++) {
			if(list[index].day.list[i]==null) {
				System.out.println(list[index].day.list[i-1].day);
				break;
			}
		}
		for(int j=0; j<list[index].goods.list.length; j++) {
			if(list[index].goods.list[j]==null) break;
			System.out.println("장비 명 :"+list[index].goods.list[j].id + " / 대여료 : " + list[index].price[j]  +"원 / 대여수량 : " + list[index].goods.list[j].num + "개" );
		}
		System.out.println("결제방식 : " + list[index].payment_type);
		if(list[index].payment_type.equals("현금")) {
			System.out.println("환불 금액 : " + list[index].gross_price + "원");
		}
		else {
			System.out.println("환불 금액 : "+list[index].gross_price + "원");
			System.out.println("카드 종류 : "+list[index].kind_of_card);
			System.out.println("승인 취소 완료");
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	}
	public void showList(){
		for(int index=0; index<list.length; index++) {
			if(list[index]==null) break;
			System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
			System.out.println("고객명 : " + list[index].name);
			System.out.println("폰 번호 : " + list[index].phone_num);
			System.out.print("대여기간 : " + list[index].day.list[0].day + " ~ ");
			for(int i=0; i<list[index].day.list.length; i++) {
				if(list[index].day.list[i]==null) {
					System.out.println(list[index].day.list[i-1].day);
					break;
				}
			}
			for(int j=0; j<list[index].goods.list.length; j++) {
				if(list[index].goods.list[j]==null) break;
				System.out.println("장비 명 :"+list[index].goods.list[j].id + " / 대여료 : " + list[index].price[j]  +"원 / 대여수량 : " + list[index].goods.list[j].num + "개" );
			}
			System.out.println("결제방식 : " + list[index].payment_type);
			if(list[index].payment_type.equals("현금")) {
				System.out.println("합계 : " + list[index].gross_price + "원");
				System.out.println("받은 돈 : " + list[index].received_money + "원");
				System.out.println("거스름 돈 : " + list[index].change+ "원");
			}
			else {
				System.out.println("결제 금액 :"+list[index].gross_price);
				System.out.println("카드 종류 :"+list[index].kind_of_card);
			}
			System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
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
