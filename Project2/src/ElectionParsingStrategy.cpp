#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "ElectionParsingStrategy.hpp"

ElectionParsingStrategy::~ElectionParsingStrategy()
{}

std::vector<std::string> ElectionParsingStrategy::tokenize_lines(std::string line) {
  std::vector<std::string> tokens;
  std::istringstream stream(line);
  std::string token;

  while (std::getline(stream, token, ',')) {
    // Remove leading and trailing white spaces
    token.erase(0, token.find_first_not_of(" \t\r\n"));
    token.erase(token.find_last_not_of(" \t\r\n") + 1);
    tokens.push_back(token);
  }

  // gets the value after the final comma
  if (!line.empty() && line.back() == ',') {
    tokens.push_back("");
  }

  return tokens;
}