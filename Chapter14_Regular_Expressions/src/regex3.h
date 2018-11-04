#pragma once

/*

14.2 Dealing with Subexpressions

find all matches of a regular expression

*/

#include <string>
#include <regex>
#include <iostream>
using namespace std;

void test()
{
	string data = 
		"<person>\n"
		" <first>Nico</first>\n"
		" <last>Josuttis</last>\n"
		"</person>\n";

	regex reg("<(.*)>(.*)</(\\1)>");

	// iterate over all matches
	auto pos = data.cbegin();
	auto end = data.cend();
	smatch m;
	// after each match, we continue the search with the beginning of the remainning characters
	//for (; regex_search(pos, end, m, reg); pos = m[0].second)	
	for (; regex_search(pos, end, m, reg); pos = m.suffix().first)	// equal to above
	{
		cout << "match:   " << m.str() << endl;
		cout << " tag:    " << m.str(1) << endl;
		cout << " value:  " << m.str(2) << endl;
	}
	cout << endl;

	// note that the output will be different if the tags in data were not separeted by a newline character
	// the reason is that regex functions try to operate in a greedy manner, the longest match possible is returned
	string data2 =
		"<person><first>Nico</first><last>Josuttis</last></person>";

	pos = data2.cbegin();
	end = data2.cend();
	for (; regex_search(pos, end, m, reg); pos = m.suffix().first)	// equal to above
	{
		cout << "match:   " << m.str() << endl;
		cout << " tag:    " << m.str(1) << endl;
		cout << " value:  " << m.str(2) << endl;
	}
	cout << endl;

	// to ensure that we still find the inner tags, we'd have to change the regular expressions
	// “[^>]*” stands for “all but character > any times”
	regex reg2("<(.*)>([^>]*)</(\\1)>");
	pos = data2.cbegin();
	end = data2.cend();
	for (; regex_search(pos, end, m, reg2); pos = m.suffix().first)	// equal to above
	{
		cout << "match:   " << m.str() << endl;
		cout << " tag:    " << m.str(1) << endl;
		cout << " value:  " << m.str(2) << endl;
	}
}

/*

match:   <first>Nico</first>
 tag:    first
 value:  Nico
match:   <last>Josuttis</last>
 tag:    last
 value:  Josuttis

match:   <person><first>Nico</first><last>Josuttis</last></person>
 tag:    person
 value:  <first>Nico</first><last>Josuttis</last>

match:   <first>Nico</first>
 tag:    first
 value:  Nico
match:   <last>Josuttis</last>
 tag:    last
 value:  Josuttis
请按任意键继续. . .

*/
