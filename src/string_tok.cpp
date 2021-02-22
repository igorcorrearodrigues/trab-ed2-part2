#include "utils.hpp"

std::string string_tok(const std::string& s, char delim, size_t *posptr)
{
	size_t pos = (posptr) ? (*posptr) : 0;

	if (pos == s.length())
		return "";

	std::string tok;

	if (delim == '\0') {
		tok = s.substr(pos);
		if (posptr)
			*posptr = s.length();

		return tok;
	}

	while (s.at(pos) == delim)
		++pos;

	size_t end = s.find(delim, pos);

	/* Se não encontrou 'delim' */
	if (end == std::string::npos) {
		tok = s.substr(pos);
		if (posptr)
			*posptr = s.length();
	} else {
		tok = s.substr(pos, end - pos);
		if (posptr)
			*posptr = end + 1;
	}
	return tok;
}
