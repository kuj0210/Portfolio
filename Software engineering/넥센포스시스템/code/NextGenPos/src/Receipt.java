
class Receipt {
	protected int num;
	int price[];
	protected int gross_price;
	protected int received_money;
	protected int change;
	protected RegisterList goods;
	protected String payment;
	protected String card;
}
class ReceiptList {
	protected Receipt list[];
	public ReceiptList() {
		list = new Receipt[256];
	}
	public void add(int _num, RegisterList _goods,int _price[], int _gross_price, int _received_money, int _change, String _payment, String _card) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				this.list[i] = new Receipt();
				this.list[i].num = _num;
				this.list[i].price = new int[100];
				this.list[i].price = _price;
				this.list[i].goods = new RegisterList();
				for(int j=0; j<list[i].goods.list.length; i++) {
					if(list[i].goods.list[j]==null) {
						this.list[i].goods.list[j] = new Register();
						this.list[i].goods = _goods;
						break;
					}
				}
				this.list[i].gross_price = _gross_price;
				this.list[i].received_money = _received_money;
				this.list[i].change = _change;
				this.list[i].payment = _payment;
				this.list[i].card = _card;
				break;
			}
		}
	};
	public void showReceipt(int num) {
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		System.out.println("영수증 번호 : " + list[num-1].num);
		for(int j=0; j<list[num-1].goods.list.length; j++) {
			if(list[num-1].goods.list[j]==null) break;
			System.out.println("상품 명 :"+list[num-1].goods.list[j].id + " / 가격 : " + list[num-1].price[j]  +"원 / 구매수량 : " + list[num-1].goods.list[j].num + "개" );
		}
		System.out.println("결제방식 : " + list[num-1].payment);
		if(list[num-1].payment.equals("현금")) {
			System.out.println("합계 : " + list[num-1].gross_price + "원");
			System.out.println("받은 돈 : " + list[num-1].received_money + "원");
			System.out.println("거스름 돈 : " + list[num-1].change+ "원");
		}
		else {
			System.out.println("결제 금액 :"+list[num-1].gross_price);
			System.out.println("카드 종류 :"+list[num-1].card);
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	}
	public void showRefundReceipt(int num) {
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		System.out.println("영수증 번호 : " + list[num-1].num);
		for(int j=0; j<list[num-1].goods.list.length; j++) {
			if(list[num-1].goods.list[j]==null) break;
			System.out.println("상품 명 :"+list[num-1].goods.list[j].id + " / 구매수량 : " + list[num-1].goods.list[j].num + "개  / 가격 : " + -list[num-1].price[j]  + "원");
		}
		System.out.println("결제방식 : " + list[num-1].payment);
		if(list[num-1].payment.equals("현금")) {
			System.out.println("환불 금액 : " + list[num-1].gross_price + "원");
		}
		else {
			System.out.println("환불 금액 :"+list[num-1].gross_price);
			System.out.println("카드 종류 :"+list[num-1].card);
			System.out.println("승인 취소 완료");
		}
		System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	}
	public void showList(){
		for(int i=1; i<list.length+1; i++) {
			if(list[i-1]==null) break;
			this.showReceipt(i);
		}		
		
	}
}
