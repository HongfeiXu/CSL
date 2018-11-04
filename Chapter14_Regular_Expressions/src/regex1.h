#pragma once

/*

14.1 The Regex Match and Search Interface

- regex
- regex_match
- regex_search

“.” stands for “any character except new line”
“*” stands for “zero or more times”
use “(...)” to define a so-called capture group, to which we refer later on with the regular expression “\1”
“(.|\n)” stands for any number of any character

*/

#include <regex>
#include <iostream>
#include <string>
using namespace std;

void out(bool b)
{
	cout << (b ? "found" : "not found") << endl;
}

void test()
{
	// find XML/HTML-tagged value (using default syntax):
	regex reg1("<.*>.*</.*>");
	bool found = regex_match("<tag>value</tag>",	// data
							 reg1);					// regular expression
	out(found);

	// find XML/HTML-tagged value (tags before and after the value must match):
	regex reg2("<(.*)>.*</\\1>");
	regex reg22(R"(<(.*)>.*</\1>)");
	found = regex_match("<tag>value</tag>",
						reg2);
	out(found);

	// find XML/HTML-tagged value (using grep syntax):
	regex reg3("<\\(.*\\)>.*</\\1>", regex_constants::grep);
	regex reg32(R"(<\(.*\)>.*</\1>)", regex_constants::grep);
	found = regex_match("<tag>value</tag>",
						reg32);
	out(found);

	// using C-string as regular expression (needs explicit cast to regex)
	found = regex_match("<tag>value</tag>",
						regex("<(.*)>.*</\\1>"));
	out(found);
	cout << endl;

	// regex_match() versus regex_search()
	string pat = "<(.*)>.*</\\2>";
	found = regex_match("XML tag: <tag>value</tag>",
						regex("(.|\n)*" + pat + "(.|n)*"));
	out(found);
	found = regex_match("XML tag: <tag>value</tag>",
						regex(".*<(.*)>.*</\\1>"));
	out(found);
	found = regex_search("XML tag: <tag>value</tag>",
						 regex("<(.*)>.*</\\1>"));
	out(found);
	found = regex_search("XML tag: <tag>value</tag>",
						 regex(".*<(.*)>.*</\\1>"));
	out(found);
}

/*

found
found
found
found

found
found
found
found
请按任意键继续. . .

*/
