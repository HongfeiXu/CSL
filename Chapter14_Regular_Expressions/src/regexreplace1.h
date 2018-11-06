#pragma once

/*

14.5 Replacing Regular Expressions

- regex_replace

*/

#include <string>
#include <regex>
#include <iostream>
#include <iterator>
using namespace std;

void test()
{
	string data =
		"<person>\n"
		" <first>Nico</first>\n"
		" <last>Josuttis</last>\n"
		"</person>\n";

	regex reg("<(.*)>(.*)</\\1>");

	// print data with replacement for matched patterns
	cout << regex_replace(data,					// data
						  reg,					// regular expression
						  //"<$1 value=\"$2\"/>")	// replacement using default syntax
						  R"(<$1 value = "$2"/>)")	// replacement using default syntax specified as a raw string
		<< endl;

	// same using sed syntax
	cout << regex_replace(data,							// data
						  reg,							// regular expression
						  //"<\\1 value=\"\\2\"/>",		// replacement using sed syntax
						  R"(<\1 value="\2"/>)",		// replacement using sed syntax specified as raw string
						  regex_constants::format_sed)	// format flag
		<< endl;

	// use iterator interface, and
	// -format_no_copy:		don't copy characters that don't match
	// -format_first_only:	replace only the first match found
	string res2;
	regex_replace(back_inserter(res2),
				  data.begin(), data.end(),
				  reg,
				  "<$1 value=\"$2\">",
				  regex_constants::format_no_copy | regex_constants::format_first_only);
	cout << res2 << endl;

	cout << endl;

	// example 
	// Ref: https://zh.cppreference.com/w/cpp/regex/regex_replace
	string text = "Quick brown fox";
	regex vowel_re("a|e|i|o|u");

	// 写结果到输出迭代器
	regex_replace(ostreambuf_iterator<char>(cout),
				  text.begin(), text.end(), 
				  vowel_re, 
				  "*");

	// 构造保有结果的字符串
	cout << '\n' << regex_replace(text, 
								  vowel_re, 
								  "[$&]") 
		<< '\n';
}

/*

<person>
 <first value = "Nico"/>
 <last value = "Josuttis"/>
</person>

<person>
 <first value="Nico"/>
 <last value="Josuttis"/>
</person>

<first value="Nico">

Q**ck br*wn f*x
Q[u][i]ck br[o]wn f[o]x
请按任意键继续. . .


*/