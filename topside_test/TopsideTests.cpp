#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>
#include "..\topside_app\Topside.h"

using namespace std;
using namespace Topside;

TEST_CASE("documents are created") {
	Document doc{};
	REQUIRE(doc.render() == "<!DOCTYPE html><html><head><script src=\"https://cdnjs.cloudflare.com/ajax/libs/uikit/2.26.3/js/uikit.min.js\"></script><link rel=\"stylsheet\" type=\"text/css\" href=\"https://cdnjs.cloudflare.com/ajax/libs/uikit/2.26.3/css/uikit.almost-flat.min.css\"></link></head><body></body></html>");
}

TEST_CASE("text elements are rendered") {
	ostringstream out;

	SECTION("basic text type") {
		Text{ "hello world" }.render(out);
		REQUIRE(out.str() == "hello world");
	}
}

TEST_CASE("tag elements are rendered") {
	ostringstream out;

	SECTION("basic tag type") {
		Tag{ "test" }.render(out);
		REQUIRE(out.str() == "<test></test>");
	}

	SECTION("heading tags") {
		Heading{ 1 }.render(out);
		REQUIRE(out.str() == "<h1></h1>");
		REQUIRE_THROWS(Heading h0{ 0 });
		REQUIRE_THROWS(Heading h7{ 7 });
	}

	SECTION("set tag attributes") {
		Tag{ "test" }.set("hello", "world")->render(out);
		REQUIRE(out.str() == "<test hello=\"world\"></test>");
	}

	SECTION("image tags") {
		Image{ "hello.png", "hello" }.render(out);
		REQUIRE(out.str() == "<img src=\"hello.png\" alt=\"hello\">");
	}

}

TEST_CASE("adding content to tags") {
	ostringstream out;
	SECTION("add text to tag") {
		Tag{ "test" }.append(new Text{ "hello" })->render(out);
		REQUIRE(out.str() == "<test>hello</test>");
	}
	SECTION("add text to heading 1") {
		Heading{ 1 }.append(new Text{ "hello" })->render(out);
		REQUIRE(out.str() == "<h1>hello</h1>");
	}
	SECTION("add text to heading 2") {
		Heading{ 2, "hello" }.render(out);
		REQUIRE(out.str() == "<h2>hello</h2>");
	}
}

TEST_CASE("unordered lists") {
	ostringstream out;

	SECTION("add itmes to list") {
		List{}.append(new ListItem{ "hello" })->append(new ListItem{ "world" })->render(out);
		REQUIRE(out.str() == "<ul><li>hello<li>world</ul>");
	}
}

