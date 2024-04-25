#ifndef ELECTION_DATA_PARSER_HPP
#define ELECTION_DATA_PARSER_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "CPLParty.hpp"
#include "ElectionData.hpp"
#include "OPLCandidate.hpp"
#include "OPLParty.hpp"
#include "ElectionParsingStrategy.hpp"

/**
 * @class ElectionDataParser
 * @brief Parses election data from files and creates election objects.
 * @details
 * This class is responsible for reading election data from provided files,
 * parsing the information, and creating appropriate election objects based on
 * the election type (e.g., OPL or CPL). It supports creating candidate and
 * party objects and assigning votes based on the data in the files.
 */
class ElectionDataParser {    
 public:
    
  /**
   * @brief Default constructor for ElectionDataParser.
   */
  ElectionDataParser();

    /**
     * @pre All contents of `ballots` are valid file paths
     * @pre All `ballots` have the same election type, and candidate & party names.
     */
    static ElectionData* create_election(std::vector<std::string> ballots);
    
    /**
     * @pre All contents of `ballots` are valid file paths
     * @pre All `ballots` have the same election type, and candidate & party names.
     */
    static ElectionData* create_election(std::string ballot);
};

#endif
