#include <iostream>
#include "Topside.h"
#include <vector>
using namespace std;
using namespace Topside;

int main() {
	Document doc;
	
	doc.add(
		new Container(
			new NavBar("TestSite",
				new NavList(
					new NavItem("home", "#"),
					new NavItem("about", "#"),
					new NavItem("contact", "#"),
					new NavItem("help", "#")
			)),
			new Panel(
				new Heading(1, "Hello World!!"),
				new Paragraph("Lorem ipsum dolor sit amet, nibh tractatos no nec, ut per nobis inermis pericula, has ne suscipit sapientem." ),
				(new Button("Buy now!"))->addClass("uk-button-large")->addClass("uk-button-primary"),
				new Paragraph("you won't regret it!")),
			new Panel(
				new Heading(2, "fruits of the world"),
				new List(
					new ListItem("cherry"),
					new ListItem("banana"),
					new ListItem("orange")
	))));

	std::cout << doc.render();
}