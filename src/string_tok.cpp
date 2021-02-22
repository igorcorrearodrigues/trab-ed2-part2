#include "utils.hpp"

std::string string_tok(const std::string& s, char delim, size_t *position)
{
	size_t pos = (position) ? (*position) : 0;

	if (pos == s.length())
		return "";

	std::string tok;

	if (delim == '\0') {
		tok = s.substr(pos);
		if (position)
			*position = s.length();

		return tok;
	}

	while (s.at(pos) == delim)
		++pos;

	size_t end = s.find(delim, pos);

	/* Se não encontrou 'delim' */
	if (end == std::string::npos) {
		tok = s.substr(pos);
		if (position)
			*position = s.length();
	} else {
		tok = s.substr(pos, end - pos);
		if (position)
			*position = end + 1;
	}
	return tok;
}
