#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "Fireball.hpp"
#include "SpellBook.hpp"
#include "TargetGenerator.hpp"
#include "Polymorph.hpp"
#include "BrickWall.hpp"

int main()
{
  Warlock richard("Richard", "foo");
  richard.setTitle("Hello, I'm Richard the Warlock!");
  BrickWall model1;

  Polymorph* polymorph = new Polymorph();
  TargetGenerator tarGen;

  tarGen.learnTargetType(&model1);
  richard.learnSpell(polymorph);

  Fireball* fireball = new Fireball();

  richard.learnSpell(fireball);

  ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

  richard.introduce();
  richard.launchSpell("Polymorph", *wall);
  richard.launchSpell("Fireball", *wall);
  delete polymorph;
  delete fireball;
}

// int main(void)
// {
// 	std::cout << "--- Constructors:\n";
// 	Warlock richard("Aang", "The Avatar");

// 	std::cout << "--- Spells:\n";
// 	Polymorph *water = new Polymorph();
// 	Fireball *fire = new Fireball();
// 	Fwoosh *air = new Fwoosh();
// 	richard.learnSpell(water);
// 	richard.learnSpell(fire);
// 	richard.forgetSpell("Fwoosh");
// 	richard.learnSpell(air);
// 	richard.forgetSpell("Fwoosh");
// 	richard.forgetSpell("Fwoosh");
// 	richard.learnSpell(air);

// 	std::cout << "--- Targets:\n";
// 	Dummy *hay = new Dummy();
// 	BrickWall *earth = new BrickWall();

// 	TargetGenerator tarGen;
// 	tarGen.learnTargetType(hay);
// 	tarGen.learnTargetType(earth);

// 	std::cout << "--- Spells (all):\n";

// 	richard.launchSpell("Fwoosh", *tarGen.createTarget("Dummy Practice"));
// 	richard.launchSpell("Fireball", *tarGen.createTarget("BrickWall Practice"));
// 	richard.launchSpell("Polymorph", *tarGen.createTarget("Dummy Practice"));

// 	std::cout << "--- Forgotten \"Fwoosh\":\n";

// 	richard.forgetSpell("Fwoosh");
// 	richard.launchSpell("Fwoosh", *tarGen.createTarget("Dummy Practice"));
// 	richard.launchSpell("Fireball", *tarGen.createTarget("BrickWall Practice"));
// 	richard.launchSpell("Polymorph", *tarGen.createTarget("Dummy Practice"));

// 	std::cout << "--- Spells (all):\n";

// 	richard.learnSpell(air);
// 	richard.launchSpell("Fwoosh", *tarGen.createTarget("Dummy Practice"));
// 	richard.launchSpell("Fireball", *tarGen.createTarget("BrickWall Practice"));
// 	richard.launchSpell("Polymorph", *tarGen.createTarget("Dummy Practice"));

// 	std::cout << "--- Non-existant spell:\n";

// 	richard.launchSpell("ACID", *tarGen.createTarget("BrickWall Practice"));
// 	richard.forgetSpell("ACID");
// 	richard.launchSpell("ACID", *tarGen.createTarget("Dummy Practice"));

// 	std::cout << "--- Destructors:\n";
// 	return (0);
// }
