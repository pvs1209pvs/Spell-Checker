#pragma once

#include <string>
#include <vector>

std::vector<std::string> list_suggestions(const std::string & input_word);

void lev(const std::string &a, const std::string &b, int itr, int * cost_mtx);

int lev(const std::string &a, const std::string &b);

std::vector<std::string> read_words();

bool isalpha(const std::string &a);