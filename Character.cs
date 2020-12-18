
public class Character {
	private const float b = 1.35f;
	private const float ATTR_MULTIPLIER = 1.2f;
	private string name;
	private int gold = 100;
	private int level = 1;
	private int experience = 0;
	private CharacterClass characterClass;
	private Inventory inventory;
	private int attackDamage;
	private float criticalChance;
	private int criticalModifier;
	private int maxHealth;
	private int currentHealth;
	private Equipment[] equipment = new Equipment[3]; //0 = helmet, 1 = armor, 2 = weapon
	
	public string Name { get { return name; } }
	public int Gold { get { return gold; } }
	public int Level { get { return level; } }
	public int Experience { get { return experience; } }
	public CharacterClass PlayerClass { get { return characterClass; } }
	public Inventory PlayerInventory { get { return inventory; } }
	public int PlayerHealth { get { return currentHealth; } }
	public int MaxHealth { get { return maxHealth; } }
	public int ExperienceToNextLevel { get { return (int)(100*((1 - Math.Pow(b, level))/(1 - b)) - 100*((1 - Math.Pow(b, level - 1))/(1 - b))); } }
	public int Defense { 
		get {
			int defense;
			for( int i = 0; i < 3; i++) {
				defense += equipment[i].armor;
			}
			return defense;
		}
	}
	
	public Character(string name, CharacterClass characterClass) {
		this.name = name;
		this.characterClass = characterClass;
		
		
		switch(characterClass) {
			case characterClass.warrior:
				this.attackDamage = 10;
				this.criticalChance = 0;
				this.criticalModifier = 0;
				this.maxHealth = 100;
				break;
			case characterClass.mage:
				this.attackDamage = 15;
				this.criticalChance = 0;
				this.criticalModifier = 0;
				this.maxHealth = 50;
				break;
			case characterClass.thief:
				this.attackDamage = 10;
				this.criticalChance = 0.15f;
				this.criticalModifier = 3;
				this.maxHealth = 75;
				break;
			default:
				this.attackDamage = 10;
				this.criticalChance = 0;
				this.criticalModifier = 0;
				this.maxHealth = 100;
				break;
		}
		this.currentHealth = this.maxHealth;
	}
	
	public void TakeDamage(int amount) {
		amount -= Defense;
		currentHealth -= amount;
	}
	
	public int CalculateDamage() {
		Random random = new Random();
		return random.NextDouble() <= criticalChance ? attackDamage * criticalModifier : attackDamage;
	}
	
	public void GainExperience(int amount) {
		experience += amount;
		if (experience >= ExperienceToNextLevel) {
			experience = experience - ExperienceToNextLevel;
			level++;
			maxHealth = (int)(maxHealth * ATTR_MULTIPLIER);
			attackDamage = (int)(attackDamage * ATTR_MULTIPLIER);
		}
	}
	
	public void Heal(int amount) {
		health += amount;
		if (health > maxHealth)
			health = maxHealth;
	}
	
	public void AddGold(int amount) {
		gold += amount;
	}
	
	public bool RemoveGold(int amount) {
		if (amount > gold)
			return false;
		gold -= amount;
		return true;
	}
	
	public string WriteToJSON
}

public enum CharacterClass {
	warrior,
	mage,
	thief
}