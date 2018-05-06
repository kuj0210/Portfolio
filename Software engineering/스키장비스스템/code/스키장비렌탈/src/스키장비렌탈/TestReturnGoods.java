package Ω∫≈∞¿Â∫Ò∑ª≈ª;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestReturnGoods {
	PosSystem pos = new PosSystem();
	@Test
	public void test() {
		pos.loadDataBase();
		int result;
		pos.returnGoods();
		result = pos.goods.list[0].isRent((float) 4.1);
		assertEquals(30,result);

	}

}
