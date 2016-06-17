#pragma once
#include <string>
#include <sstream>

namespace Topside {
	class Element {

	public:
		virtual void render(std::ostringstream &out) const = 0;
	};
}