#pragma once

/*

14.4 Regex Token Iterators

- sregex_token_iterator, regex_token_iterator<>

*/

#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
using namespace std;

void test()
{
	string data =
		"<person>\n"
		" <first>Nico</first>\n"
		" <last>Josuttis</last>\n"
		"</person>\n";

	regex reg("<(.*)>(.*)</\\1>");

	// iterate over all matches (using a regex_token_iterator):
	sregex_token_iterator pos(data.cbegin(), data.cend(),	// sequence
							  reg,							// token separator
							  { 0, 2 });					// 0:full match, 2:second substring

	sregex_token_iterator end;
	for (; pos != end; ++pos)
	{
		cout << "match: " << pos->str() << endl;
	}
	cout << endl;

	string name = "nico, jim helmut, paul, tim, john paul, rita";
	regex sep("[ \t\n]*[,;.][ \t\n]*");	// sperated by ,; or . and spaces
	regex sep2("[[:space:]]*[,;.][[:space:]]*");
	sregex_token_iterator p(name.cbegin(), name.cend(),		// sequence
							sep,							// separator
							-1);							// -1:values between separators
	sregex_token_iterator e;
	for (; p != e; ++p)
	{
		cout << "match: " << p->str() << endl;
	}
	cout << endl;
}

/*

match: <first>Nico</first>
match: Nico
match: <last>Josuttis</last>
match: Josuttis

match: nico
match: jim helmut
match: paul
match: tim
match: john paul
match: rita

请按任意键继续. . .

*/
