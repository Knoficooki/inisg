#pragma once

#include <string>
#include <exception>

std::string help_STR__ = "\t\tHelp\nSYNTAX:\n\tinisg load -f [file]\n\tinisg save ([-f [file])\n\tinisg set (-s [section]) -k [key] -v [value]\n\tinisg get (-s [section]) -k [key] (-v [default value])\n\tinisg new (-f [file])\n\tinisg clear\n\n\0";

void help(std::string&& e = "") {
	throw std::logic_error((
		help_STR__
		 + e.c_str()).c_str());
}

std::string helpInside_STR__ = "\t\tHelp\nSYNTAX:\n\tinisg inside set -f [file] (-s [section]) -k [key] -v [value]\n\tinisg inside get -f [file] (-s [section]) -k [key] (-v [default value]) (--out (-f [output file]) (--trunc))\n\tinisg inside del -f [file] (-s [section] &// -k [key])\n\tinisg inside new -f [file] (--from -f [from file])\n\n\0";

void helpInside(std::string&& e = "") {
	throw std::logic_error((
		helpInside_STR__
		 + e.c_str()).c_str());
}