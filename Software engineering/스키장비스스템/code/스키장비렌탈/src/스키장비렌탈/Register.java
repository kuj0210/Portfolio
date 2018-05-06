package Ω∫≈∞¿Â∫Ò∑ª≈ª;


class Register {
	protected String id;
	protected int num;
}
class RegisterList {
	protected Register[] list;
	public RegisterList() {		
		list = new Register[256];
	}
	protected void enterReg(String id, int num) {
		for(int i=0; i<list.length; i++) {
			if(list[i]==null) {
				list[i] = new Register();
				list[i].id = id;
				list[i].num = num;
				break;
			}
		}
	};
	protected void removeList(String id) {
		for(int i=0; i<list.length; i++) {
			if(list[i].id.equals(id)) {
				if(i==list.length-1) {
						list[i] = null;
						return;
					}
				for(int j=i+1; j<list.length+1; j++) {
					list[i] = list[j];
					return;
				}
			}
		}
		return;
	};
}