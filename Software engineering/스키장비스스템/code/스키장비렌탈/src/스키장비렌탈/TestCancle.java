package Ω∫≈∞¿Â∫Ò∑ª≈ª;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestCancle {
	PosSystem pos = new PosSystem();
	@Test
	public void test() {
		pos.loadDataBase();
		pos.cancle();
		assertNull(pos.customer.list[1]);
	}

}
