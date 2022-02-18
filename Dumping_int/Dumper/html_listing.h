#ifndef HTML_LISTING
#define HTML_LISTING

#include <cstring>
#include "../Int/my_int.h"

const char DUMP_FILE[] = "dump.html";
const char HTML_HEAD_FILE[] = "<!DOCTYPE html><pre>";
const int MAX_FORMAT_SIZE = 128;
const int MAX_SIZE = 16;

extern const char* html_colours[];

struct Format {
	char font[MAX_SIZE];
	char colour[MAX_SIZE];
	size_t size;

	Format() {
		strcpy(font, "Arial");
		strcpy(colour, "black");
		size = 3;
	}

	Format(char* arg_colour) {
		strcpy(colour, arg_colour);
		size = 3;
	}
};

class Html_listing {
public:
	FILE* html_file;

	Html_listing() {
		html_file = fopen(DUMP_FILE, "w");
		fprintf(html_file,  "%s"
							"\n<style>p.std_indent {\n"
    						"\tline-height: 1.5;\n"
   							"}\n"
   							"P {\n"
    						"\tline-height: 0.9em;\n"
   							"}\n"
  							"</style>\n\n"
  							"<p>", HTML_HEAD_FILE);
		fclose(html_file);
	}

	void dump(std::string message) {
		html_file = fopen(DUMP_FILE, "a");

		fprintf(html_file, "%s\n", message.c_str());
		fclose(html_file);
	}

	void dump(std::string message, Format &format) {
		html_file = fopen(DUMP_FILE, "a");

		fprintf(html_file, "<font size=\"%ld\" color=\"%s\">%s</font>\n",
								format.size, format.colour, message.c_str());
		fclose(html_file);
	}

	void dump(std::string message, Console_colours colour) {
		html_file = fopen(DUMP_FILE, "a");



		fprintf(html_file, "<font size=\"%d\" color=\"%s\">%s</font>\n",
								3, html_colours[get_number_colour(colour)], message.c_str());
		fclose(html_file);
	}

	void dump_indents(int count_tabs) {
		html_file = fopen(DUMP_FILE, "a");

		for(int i = 0; i < count_tabs; ++i)
			fprintf(html_file, "\t");
		fclose(html_file);
	}

	int get_number_colour(Console_colours &colour) {
		switch(colour) {
			case DEFAULT_COLOUR:
				return 0;
			case CONSTRUCTOR_COLOUR:
				return 1;
			case ARGUMENTS_COLOUR:
				return 2;
			case DESTRUCTOR_COLOUR:
				return 3;
			case COPY_COLOUR:
				return 4;
			case OPERATOR_COLOUR:
				return 5;
			default:
				return 0;

		}

		return 0;
	}



	~Html_listing() {
		html_file = fopen(DUMP_FILE, "a");
		fprintf(html_file, "</p>");
		fclose(html_file);		
	}
};

#endif