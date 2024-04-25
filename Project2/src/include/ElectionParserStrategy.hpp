#ifndef ELECTION_PARSER_STRATEGY_HPP
#define ELECTION_PARSER_STRATEGY_HPP

#include <string>
#include <vector>

#include "ElectionData.hpp"

class ElectionParserStrategy {
public:
    ElectionParserStrategy() {}

    virtual ~ElectionParserStrategy() {}

    virtual ElectionData* createElection(std::vector<std::string> data) = 0;

    static std::vector<std::string> tokenize_lines(std::string line);
};

#endif
