package Ω∫≈∞¿Â∫Ò∑ª≈ª;

import static org.junit.Assert.*;

import org.junit.Test;

public class RentalSkiEquipmentTest {
	PosSystem pos = new PosSystem();
	
	@Test
	public void testRentEnterGoods() {
		pos.loadDataBase();
		pos.rentEnterGoods();
		assertNotNull(pos.customer.list[1]);
	}
}
