#pragma once

/*

14.2 Dealing with Subexpressions

- smatch, match_results<>
- sub_match<>

*/

#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
using namespace std;

void test()
{
	string data = "XML tag: <tag-name>the value</tag-name>.<fuck>the value</fuck>";
	cout << "data:             " << data << "\n\n";

	// smatch : std::match_results<std::string::const_iterator>
	smatch m;	// for returned details of the match
	bool found = regex_search(data,
							  m,
							  regex("<(.*)>(.*)</(\\1)>"));
	// print match details:
	cout << "m.empty():        " << boolalpha << m.empty() << endl;
	cout << "m.size():         " << m.size() << endl;	// size() yields the number of sub_match objects (including m[0])
	if (found)
	{
		cout << "m.str():          " << m.str() << endl;
		cout << "m.length():       " << m.length() << endl;
		cout << "m.position():     " << m.position() << endl;
		cout << "m.prefix().str(): " << m.prefix() << endl;
		cout << "m.suffix().str(): " << m.suffix() << endl;
		cout << endl;

		// iterating over all matches (using the match index):
		// m[0] -- all the matched characters
		// m[1~3] -- sub_match object for each capture group
		for (unsigned i = 0; i < m.size(); ++i)
		{
			cout << "m[" << i << "].str():        " << m[i].str() << endl;
			cout << "m.str(" << i << "):          " << m.str(i) << endl;
			cout << "m.position(" << i << "):     " << m.position(i) << endl;
		}
		cout << endl;

		// iterating over all matches (using iterators):
		cout << "matches:" << endl;
		for (auto pos = m.begin(); pos != m.end(); ++pos)
		{
			cout << " " << *pos << " ";
			cout << "(length: " << pos->length() << ")" << endl;
		}
		cout << endl;

		// 4 ways to yield the whole matched string in a match_result<> m
		cout << m.str() << endl;
		cout << m.str(0) << endl;
		cout << m[0].str() << endl;
		cout << *(m.begin()) << endl;
		cout << endl;

		// 3 ways to yield the nth matches substring, if any:
		cout << m.str(1) << endl;
		cout << m[1].str() << endl;
		cout << *(m.begin() + 1) << endl;
	}
}

/*

data:             XML tag: <tag-name>the value</tag-name>.<fuck>the value</fuck>

m.empty():        false
m.size():         4
m.str():          <tag-name>the value</tag-name>
m.length():       30
m.position():     9
m.prefix().str(): XML tag:
m.suffix().str(): .<fuck>the value</fuck>

m[0].str():        <tag-name>the value</tag-name>
m.str(0):          <tag-name>the value</tag-name>
m.position(0):     9
m[1].str():        tag-name
m.str(1):          tag-name
m.position(1):     10
m[2].str():        the value
m.str(2):          the value
m.position(2):     19
m[3].str():        tag-name
m.str(3):          tag-name
m.position(3):     30

matches:
 <tag-name>the value</tag-name> (length: 30)
 tag-name (length: 8)
 the value (length: 9)
 tag-name (length: 8)

<tag-name>the value</tag-name>
<tag-name>the value</tag-name>
<tag-name>the value</tag-name>
<tag-name>the value</tag-name>

tag-name
tag-name
tag-name
请按任意键继续. . .

*/
