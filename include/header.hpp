// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <any>
#include <map>
#include <vector>

using namespace std;

class Json {
public:

Json(const std::string& s)

bool is_array() const

bool is_object() const

std::any& operator[](const std::string& key)

std::any& operator[](int index)

private:
string findKey(const string& s)

any findMean(const string& s)

public:
static Json parse(const std::string& s)

static Json parseFile(const std::string& path_to_file)

int position;
std::string str;
std::map <std::string, std::any> parsed;

}
#endif // INCLUDE_HEADER_HPP_

