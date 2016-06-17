#pragma once
#pragma once

#include <string>
#include <sstream>

#include "Element.h"

namespace Topside {
	class Text : public Element {
		std::string content;
	public:
		Text(const std::string& content) : content{ content } {}

		virtual void render(std::ostringstream &out) const override {
			out << content;
		}
	};
}