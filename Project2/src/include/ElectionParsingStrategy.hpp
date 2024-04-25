#ifndef ELECTION_PARSING_STRATEGY_HPP
#define ELECTION_PARSING_STRATEGY_HPP

#include <string>
#include <vector>

#include "ElectionData.hpp"

/**
 * @class ElectionParsingStrategy
 * @brief class for the different election parsing strategies.
 */
class ElectionParsingStrategy {
 public:
     /**
     * @brief Constructor.
     */
    ElectionParsingStrategy() {}
     /**
     * @brief destructor.
     */
    virtual ~ElectionParsingStrategy();
     /**
     * @brief Create ElectionData from ballot data.
     *
     * @param ballots A vector of strings representing the file name of ballots.
     * @return ElectionData* Pointer to ElectionData
     */
    virtual ElectionData* create_election(std::vector<std::string> ballots) = 0;

    static std::vector<std::string> tokenize_lines(std::string line);
};

#endif
