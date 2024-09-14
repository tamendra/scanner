#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int string_to_int(string s);
string int_to_string(int i);

// pad_s is a single char, padded to the left
string lpad(string s, unsigned int str_len, string pad_s);
