import static org.junit.Assert.*;

import org.junit.Test;

public class AddGoodsTest {
	GoodsList goods = new GoodsList();
	@Test
	public void testAddGoods() {
		
		goods.add("»§",1000,30);
		assertNotNull(goods.list[0]);
	}
	
}
