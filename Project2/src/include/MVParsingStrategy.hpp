#ifndef MV_PARSING_STRATEGY_HPP
#define MV_PARSING_STRATEGY_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "ElectionParsingStrategy.hpp" // Include the base class header file
#include "MVCandidate.hpp"
#include "MVParty.hpp"

/**
 * @class MVParsingStrategy
 * @brief Implements the ElectionParsingStrategy for the MV election format.
 * @details
 * This class is specialized to handle the parsing and creation of election data
 * objects specifically tailored for MV (Mixed Party Output) elections. It
 * involves reading data about candidates and their party affiliations from files,
 * assigning votes, and organizing these into coherent party and election data structures.
 */
class MVParsingStrategy : public ElectionParsingStrategy {
 public:
    /**
     * @brief Constructor for MVParsingStrategy.
     */
    MVParsingStrategy();
     
     /**
     * @brief Destructor for MVParsingStrategy, overriding virtual destructor from the base class.
     */
    ~MVParsingStrategy() override;
    
    /**
     * @brief Creates an ElectionData object for an MV election.
     * @param ballots Vector of strings representing the ballots.
     * @return Pointer to the ElectionData object constructed from the ballots.
     * @pre if multiple files are used, the header data is identical accross files
     * @details
     * Processes a list of ballots to create a fully populated ElectionData object
     * suitable for MV elections, organizing the data into appropriate structures.
     */
    ElectionData* create_election(std::vector<std::string> ballots) override;

 private:
     /**
     * @brief Creates MV candidates from a file.
     * @param file Reference to an input file stream.
     * @param numCands The number of candidates to be read.
     * @return A vector of tuples, each containing a party name and a pointer to a Candidate object.
     * @pre 'numCands' > 0
     * @pre if multiple files are used, the header data is identical accross files
     * @details
     * Reads candidate information for MV elections from the file and creates
     * a vector of tuples containing candidate objects and their associated party.
     */
    static std::vector<std::tuple<std::string, Candidate*>> create_MV_candidates(std::ifstream& file, int numCands);

    /**
     * @brief Assigns votes to MV candidates based on file data.
     * @param file Reference to the input file stream.
     * @param candidates Vector of pointers to Candidate objects.
     * @pre there are votes in the file
     * @pre candidate vector is not empty
     * @pre if multiple files are used, the header data is identical accross files
     * @details
     * Reads vote counts from the file and applies them to the corresponding
     * candidates in the provided vector.
     */  
    static void assign_votes_to_candidates(std::ifstream& file, std::vector<Candidate*> candidates);

     /**
     * @brief Creates MV party objects from a vector of MV candidates.
     * @param candidates A vector of tuples containing party names and Candidate pointers.
     * @return A vector of Party pointers.
     * @pre input vector not empty
     * @pre if multiple files are used, the header data is identical accross files
     * @details
     * Organizes candidates into parties based on their party affiliation and
     * creates a vector of Party objects.
     */
    static std::vector<Party*> create_MV_parties(std::vector<std::tuple<std::string, Candidate*>> candidates);
};

#endif
