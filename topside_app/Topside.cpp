#include <iostream>
#include "Topside.h"
#include <vector>
using namespace std;
using namespace Topside;

int main() {
	Document doc;
	
	doc.add(
		Container(
			NavBar("TestSite",
				NavList(
					NavItem("home", "#"),
					NavItem("about", "#"),
					NavItem("contact", "#"),
					NavItem("help", "#")
			)),
			Panel(
				Heading(1, "Hello World!!"),
				Paragraph("Lorem ipsum dolor sit amet, nibh tractatos no nec, ut per nobis inermis pericula, has ne suscipit sapientem." ),
				Button("Buy now!").addClass("uk-button-large")->addClass("uk-button-primary"),
				Paragraph("you won't regret it!")),
			Panel(
				Heading(2, "fruits of the world"),
				List(
					ListItem("cherry"),
					ListItem("banana"),
					ListItem("orange")
	))));

	std::cout << doc.render();
}