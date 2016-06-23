#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "Element.h"
#include "Tag.h"

namespace Topside {

	class Document {
		Tag head;
		Tag body;

	public:
		Document() : head{ "head" }, body{ "body" } {
			addStylesheet("https://cdnjs.cloudflare.com/ajax/libs/uikit/2.26.3/css/uikit.almost-flat.min.css");
			addScript("https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0/jquery.min.js");
			addScript("https://cdnjs.cloudflare.com/ajax/libs/uikit/2.26.3/js/uikit.min.js");

		}

		void add(const Element&& element) {
			body.append(std::move(element));
		}

		void addScript(const std::string& src) {
			head.append(Script{ src });
		}

		void addStylesheet(const std::string& src) {
			head.append(Stylesheet{ src });
		}

		std::string render() {
			std::ostringstream out{};
			out << "<!DOCTYPE html><html>";
			head.render(out);
			body.render(out);
			out << "</html>";
			return out.str();
		}

	};

}