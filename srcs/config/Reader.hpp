#ifndef READER_HPP
#define READER_HPP

#include <string>

#define ISSPACE		"\t\n\v\f\r "
#define SEMICOLON	";"

class Reader {
	private:
		std::string _parser;

	public:
		Reader(void);
		Reader(const std::string& source);
		Reader(const Reader& other);
		virtual ~Reader(void);

		Reader& operator=(const Reader &other);

	public:
		std::string
		read(void);

	public:
		static Reader from(const std::string& path);
};

#endif
