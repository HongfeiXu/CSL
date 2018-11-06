#pragma once

/*

14.7 Regex Exceptions

*/

#include <regex>
#include <iostream>
#include "regexexception.h"
using namespace std;

void test()
{
	try {
		// initialize regular expression with invlid syntax:
		regex pat(R"(\\.index\{([^}]*)\})",
				  regex_constants::grep | regex_constants::icase);
	}
	catch (const regex_error& e)
	{
		cerr << "regex_error: \n"
			<< " what(): " << e.what() << "\n"
			<< " code(): " << regexCode(e.code()) << endl;
	}
}

/*

regex_error:
 what(): regex_error(error_badbrace): The expression contained an invalid range in a { expression }.
 code(): error_badbrace: regex has invalid range in {} expression
请按任意键继续. . .

*/
