#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <sstream>

#include "Element.h"
#include "Text.h"

namespace Topside {
	class Tag : public Element {
		std::list<Element*> contents;
		std::string tag;
		bool close;
		std::unordered_map<std::string, std::string> attributes;
	public:
		Tag(const std::string& tag, bool close = true) : tag{ tag }, close{ close } {}
		
		template <typename T>
		Tag(const std::string& tag, T* element) :
			tag{ tag }, attributes{} {
			append(std::move(element));
		}

		template <typename T, typename... Ts>
		Tag(const std::string& tag, T* element, Ts*... elements) :
			Tag(tag, elements...) {
			prepend(element);
		}

		virtual void render(std::ostringstream &out) const override {
			out << '<' << tag;
			for (auto a : attributes)
				out << ' ' << a.first << "=\"" << a.second << "\"";
			out << '>';
			for (auto e : contents)
				e->render(out);
			if(close)
				out << "</" << tag << '>';
		}
		
		Tag* append(Element* element) {
			contents.push_back(element);
			return this;
		}
		
		Tag* prepend(Element* element) {
			contents.push_front(element);
			return this;
		}

		Tag* set(const std::string& key, const std::string& value) {
			attributes[key] = value;
			return this;
		}

		std::string get(const std::string& key) const{
			auto attribute = attributes.find(key);
			if (attribute != attributes.end())
				return attribute->second;
			return "";
		}

		Tag* addClass(const std::string& name) {
			auto existing = get("class");
			if (existing != "")
				set("class", existing + " " + name);
			else
				set("class", name);
			return this;
		}

	};

	class Image : public Tag {
	public:
		Image(const std::string& src, const std::string& alt = "") : Tag{ "img", false } {
			set("src", src);
			set("alt", alt);
		}
	};

	class Script : public Tag {
	public:
		Script(const std::string& src) : Tag{ "script" } {
			set("src", src);
		}
	};


	class Link : public Tag {
	public:
		Link(const std::string& rel, const std::string& type, const std::string& href) : Tag{ "link", false } {
			set("rel", rel);
			set("type", type);
			set("href", href);
		}
	};

	class Stylesheet : public Link {
	public:
		Stylesheet(const std::string& src) : Link{ "stylesheet", "text/css", src } {}
	};

	class Paragraph : public Tag {
	public:
		Paragraph() : Tag{ "p" } {}
		Paragraph(const std::string& text) : Paragraph{} {
			append(new Text{ text });
		}
	};

	class Heading : public Tag {
	public:
		Heading(int level) : Tag{ "h" + std::to_string(level) } {
			if (level < 1 || level > 6)
				throw(std::invalid_argument("only 1-6 are valid"));
		}
		Heading(int level, const std::string& text) : Heading{ level } {
			append(new Text{ text });
		}
	};

	class ListItem : public Tag {
	public:
		ListItem() : Tag{ "li", false } {}
		ListItem(const std::string& text) : ListItem{} {
			append(new Text{ text });
		}
	};

	class Anchor : public Tag {
	public:
		Anchor(const std::string& href) : Tag{ "a" } {
			set("href", href);
		}
	};

	class Division : public Tag {
	public:
		template <typename... Ts>
		Division(Ts*... elements) : Tag{ "div", elements... } {}
	};

	class List : public Tag {
	public:
		List() : Tag{ "ul" } {}
		template <typename... Ts>
		List(Ts*... elements) : Tag{ "ul", elements... } {}
	};

	class NavList : public List {
	public:
		NavList() {}
		template <typename... Ts>
		NavList(Ts*... elements) : List{ elements... } {
			addClass("uk-navbar-nav uk-hidden-small");
		}
	};

	class NavItem : public ListItem {
	public:
		NavItem(const std::string& text, const std::string& href) {
			append((new Anchor{ href })->append(new Text{ text }));
		}
	};

	class Container : public Division {
	public:
		Container() {}
		template <typename... Ts>
		Container(Ts*... elements) : Division{ elements... } {
			addClass("uk-container uk-container-center uk-margin-top uk-margin-bottom");
		}
	};

	class Panel : public Division {
	public:
		Panel() {}
		template <typename... Ts>
		Panel(Ts*... elements) : Division{ elements... } {
			addClass("uk-panel uk-panel-box");
		}
	};

	class NavBar : public Tag {
	public:
		NavBar(const std::string& text, NavList* navlist) : Tag{ "nav" } {
			addClass("uk-navbar uk-margin-bottom");
			append((new Anchor{ "#" })->addClass("uk-navbar-brand uk-hidden-small")->append(new Text{ text }));
			append(navlist);
		}
	};

	class Button : public Anchor {
	public:
		Button(const std::string& text, const std::string& href = "#") : Anchor{href} {
			addClass("uk-button");
			append(new Text{ text });
		}
	};

}