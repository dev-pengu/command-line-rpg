using System.Collections.Generic;

public class Inventory {
	private Dictionary<Item, int> items = new Dictionary<Item, int>();
	
	public Dictionary<Item, int> Items { get { return items; } }
	
	public Inventory() {
		if (!items)
			items = new Dictionary<Item, int>();
	}
	
	public Inventory(Inventory inv) {
		items = new Dictionary<Item, int>();
		foreach (Item item in items.Keys()) {
			items.Add(item, inv[item]);
		}
	}
	
	public void AddItem(Item item, int count) {
		if(items.ContainsKey(item)) {
			items[item] += count;
		} else {
			items.Add(item, count);
		}
	}
	
	public bool RemoveItem(Item item, int count) {
		if (!items.ContainsKey(item)) {
			return false;
		} else {
			if(items[item] < count)
				return false;
			else if(items[item] == count) {
				items.Remove(item);
				return true;
			} else {
				items[item] -= count;
				return true;
			}
		}
	}
}