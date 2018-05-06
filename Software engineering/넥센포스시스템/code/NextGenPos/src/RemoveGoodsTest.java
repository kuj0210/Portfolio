import static org.junit.Assert.*;

import org.junit.Test;

public class RemoveGoodsTest {
	GoodsList goods = new GoodsList();
	
	@Test
	public void testRemovetest() {
		goods.add("»§",1000,30);
		goods.remove();
		assertNull(goods.list[0]);
	}
}
