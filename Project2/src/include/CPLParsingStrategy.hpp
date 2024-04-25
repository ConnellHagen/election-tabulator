#ifndef CPL_PARSING_STRATEGY_HPP
#define CPL_PARSING_STRATEGY_HPP

#include <vector>
#include <string>
#include <fstream>

#include "ElectionParsingStrategy.hpp"
#include "ElectionData.hpp"
#include "CPLParty.hpp"

/**
 * @class CPLParsingStrategy
 * @brief Implements parsing strategy for Closed Party List (CPL) election systems.
 * Inherits from ElectionParsingStrategy
 */
class CPLParsingStrategy : public ElectionParsingStrategy {
 public:
     /**
     * @brief Constructor for CPLParsingStrategy.
     */
    CPLParsingStrategy();
     /**
     * @brief Destructor for CPLParsingStrategy.
     */
    ~CPLParsingStrategy() override;
     /**
     * @brief Generates ElectionData from a list of ballot file names reflecting votes across multiple files. 
     * @param ballots A vector of strings representing the file name of ballots.
     * @return ElectionData* Pointer to ElectionData
     */
    ElectionData* create_election(std::vector<std::string> ballots) override;

 private:
     /**
     * @brief Method creates a vector Party objects.
     * @param file Reference to read party data.
     * @param numParties Number of parties
     * @return <Party*> A vector of pointers to Party objects
     */
    static std::vector<Party*> create_CPL_parties(std::ifstream& file, int numParties);
     /**
     * @brief Method assigns votes to CPL parties from file. 
     * @param file Reference from which to read ballot data.
     * @param parties Vector of pointers to Party objects
     */
    static void assign_votes_to_parties(std::ifstream& file, std::vector<Party*> parties);
};

#endif
