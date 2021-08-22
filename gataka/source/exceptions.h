#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

namespace exceptions
{
	const static inline std::string message(const char* ch, std::string file,
	                                        int line)
	{
		return std::string(ch) + ". " + file + ":" + std::to_string(line);
	}
};

#endif /* EXCEPTIONS_H_INCLUDED */
