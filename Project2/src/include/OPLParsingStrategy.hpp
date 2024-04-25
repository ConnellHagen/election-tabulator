#ifndef OPL_PARSING_STRATEGY_HPP
#define OPL_PARSING_STRATEGY_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "ElectionParsingStrategy.hpp" // Include the base class header file
#include "OPLCandidate.hpp"
#include "OPLParty.hpp"

/**
 * @class OPLParsingStrategy
 * @brief Implements parsing strategy for Open Party List (OPL) election systems.
 *
 * Inherits from ElectionParsingStrategy
 */
class OPLParsingStrategy : public ElectionParsingStrategy {
 public:
     /**
     * @brief Constructor for OPLParsingStrategy.
     */
    OPLParsingStrategy();
     /**
     * @brief Destructor for OPLParsingStrategy.
     */
    ~OPLParsingStrategy() override;
     /**
     * @brief Generates ElectionData from a list of ballot file names reflecting votes across multiple files.
     * 
     * @param ballots A vector of strings representing the file name of ballots.
     * @return ElectionData* Pointer to ElectionData
     */
    ElectionData* create_election(std::vector<std::string> ballots) override;

 private:
    /**
     * @brief Static method to create OPL candidates from file, creating tuples of party name and candidate.
     *
     * @param file Reference from which to read candidate data.
     * @param numCands Number of candidates
     * @return std::vector<std::tuple<std::string, Candidate*>> List of tuples containing party names and Candidate pointers.
     */
    static std::vector<std::tuple<std::string, Candidate*>> create_OPL_candidates(std::ifstream& file, int numCands);

    /**
     * @brief Static method to assign votes to OPL candidates from file
     *
     * @param file Reference from which to read ballot data.
     * @param candidates Vector of candidate pointers
     */
    static void assign_votes_to_candidates(std::ifstream& file, std::vector<Candidate*> candidates);

    /**
     * @brief Static method to create OPL parties from OPL candidates
     *
     * @param candidates Vector of tuples containing a party name and a Candidate pointer.
     * @return std::vector<Party*> Vector of Party pointers, each representing a party with its respective candidates.
     */
    static std::vector<Party*> create_OPL_parties(std::vector<std::tuple<std::string, Candidate*>> candidates);
};

#endif
