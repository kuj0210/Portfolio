
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
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		System.out.println("������ ��ȣ : " + list[num-1].num);
		for(int j=0; j<list[num-1].goods.list.length; j++) {
			if(list[num-1].goods.list[j]==null) break;
			System.out.println("��ǰ �� :"+list[num-1].goods.list[j].id + " / ���� : " + list[num-1].price[j]  +"�� / ���ż��� : " + list[num-1].goods.list[j].num + "��" );
		}
		System.out.println("������� : " + list[num-1].payment);
		if(list[num-1].payment.equals("����")) {
			System.out.println("�հ� : " + list[num-1].gross_price + "��");
			System.out.println("���� �� : " + list[num-1].received_money + "��");
			System.out.println("�Ž��� �� : " + list[num-1].change+ "��");
		}
		else {
			System.out.println("���� �ݾ� :"+list[num-1].gross_price);
			System.out.println("ī�� ���� :"+list[num-1].card);
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	}
	public void showRefundReceipt(int num) {
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
		System.out.println("������ ��ȣ : " + list[num-1].num);
		for(int j=0; j<list[num-1].goods.list.length; j++) {
			if(list[num-1].goods.list[j]==null) break;
			System.out.println("��ǰ �� :"+list[num-1].goods.list[j].id + " / ���ż��� : " + list[num-1].goods.list[j].num + "��  / ���� : " + -list[num-1].price[j]  + "��");
		}
		System.out.println("������� : " + list[num-1].payment);
		if(list[num-1].payment.equals("����")) {
			System.out.println("ȯ�� �ݾ� : " + list[num-1].gross_price + "��");
		}
		else {
			System.out.println("ȯ�� �ݾ� :"+list[num-1].gross_price);
			System.out.println("ī�� ���� :"+list[num-1].card);
			System.out.println("���� ��� �Ϸ�");
		}
		System.out.println("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�");
	}
	public void showList(){
		for(int i=1; i<list.length+1; i++) {
			if(list[i-1]==null) break;
			this.showReceipt(i);
		}		
		
	}
}
