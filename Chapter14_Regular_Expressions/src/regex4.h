#pragma once

/*

14.6 Regex Flags

- regex_constants::egrep
- regex_constants::icase

*/

#include <string>
#include <regex>
#include <iostream>
using namespace std;

void test()
{
	// case-intensitive find LaTeX index entries
	// the goal is to find LaTeX index entries that might have one or two arguments.
	string pat1 = R"(\\.*index\{([^}]*)\})";		// first capture group (take greediness into account)
	string pat2 = R"(\\.*index\{(.*)\}\{(.*)\})";	// 2nd and 3rd capture group
	// grep and egrep can search for multiple regular expressions at the same time, specified in separate lines
	regex pat(pat1 + "\n" + pat2,
			  regex_constants::egrep | regex_constants::icase);

	// initialize string with characters from standard input:
	string data((istreambuf_iterator<char>(cin)),
				istreambuf_iterator<char>());

	// search and print matching index entries:
	smatch m;
	auto pos = data.cbegin();
	auto end = data.cend();
	for (; regex_search(pos, end, m, pat); pos = m.suffix().first)
	{
		cout << "match: " << m.str() << endl;
		cout << "  val: " << m.str(1) + m.str(2) << endl;	// if no (second regex) match exists, str(2) and str(3) yield an empty string
		cout << "  see: " << m.str(3) << endl;
	}
}

/*

\chapter{The Standard Template Library}
\index{STL}%
\MAININDEX{standard template library}%
\SEEINDEX{standard template library}{STL}%
This is the basic chapter about the STL.
\section{STL Components}
\hauptindex{STL, introduction}%
The \stl{} is based on the cooperation of
^Z
match: \index{STL}
  val: STL
  see:
match: \MAININDEX{standard template library}
  val: standard template library
  see:
match: \SEEINDEX{standard template library}{STL}
  val: standard template library
  see: STL
match: \hauptindex{STL, introduction}
  val: STL, introduction
  see:
请按任意键继续. . .

*/
