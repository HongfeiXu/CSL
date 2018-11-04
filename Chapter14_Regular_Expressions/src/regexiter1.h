#pragma once

/*

14.3 Regex Iterators

To iterate over all matches of a regular search, we can also use regex iterators.

- sregex_iterator, regex_iterator<>

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
	regex reg("<(.*)>(.*)</(\\1)>");

	// iterate over all matches (using a regex_iterator)
	sregex_iterator pos(data.cbegin(), data.cend(), reg);
	sregex_iterator end;
	for (; pos != end; ++pos)
	{
		cout << "match:   " << pos->str() << endl;
		cout << " tag:    " << pos->str(1) << endl;
		cout << " value:  " << pos->str(2) << endl;
	}
	cout << endl;

	// use a regex_iterator to process each matched substring as element in an algorithm:
	sregex_iterator beg(data.cbegin(), data.cend(), reg);
	for_each(beg, end, [](const smatch& m) {
		cout << "match:   " << m.str() << endl;
		cout << " tag:    " << m.str(1) << endl;
		cout << " value:  " << m.str(2) << endl;
	});
}

/*

match:   <first>Nico</first>
 tag:    first
 value:  Nico
match:   <last>Josuttis</last>
 tag:    last
 value:  Josuttis

match:   <first>Nico</first>
 tag:    first
 value:  Nico
match:   <last>Josuttis</last>
 tag:    last
 value:  Josuttis
请按任意键继续. . .

*/
