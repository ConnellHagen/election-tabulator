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
   * @brief Tokenizes a string into a vector of strings based on comma
   * delimiters.
   * @param line The string to tokenize.
   * @return A vector of tokenized strings.
   */
  static std::vector<std::string> tokenize_lines(std::string line);

  /**
   * @brief Creates vector CPLCandidates
   * @param file Reference to the input file stream.
   * @param numCands The number of candidates to read.
   * @return A vector of tuples with party names and OPLCandidate pointers.
   * @pre 'numCands' > 0
   * Reads candidate information for CPL elections from the file and creates
   * a vector of tuples containing candidate objects and their associated party.
   */
  static std::vector<std::tuple<std::string, Candidate*>> create_OPL_candidates(
      std::ifstream& file, int numCands);

  /**
   * @brief Assigns votes to OPL candidates based on file data.
   *
   * Applies vote counts from the file to the corresponding
   * candidates in the provided vector.
   * @param file Reference to the input file stream.
   * @param candidates Vector of pointers to OPLCandidate objects.
   * @pre there are votes in the file
   * @pre candidate vector is not empty
   * @details
   * Applies vote counts from the file to the corresponding
   * candidates in the provided vector.
   */
  static void assign_votes_to_candidates(std::ifstream& file,
                                         std::vector<Candidate*> candidates);

  /**
   * @brief Creates OPLParty objects from a vector of candidates.
   * @param candidates A vector of tuples containing party names and
   * OPLCandidate pointers.
   * @return A vector of OPLParty pointers.
   * @pre input vector not empty
   * @details
   * Organizes candidates into parties based on their party affiliation and
   * creates a vector of OPLParty objects.
   */
  static std::vector<Party*> create_OPL_parties(
      std::vector<std::tuple<std::string, Candidate*>> candidates);

  /**
   * @brief Creates CPLParty objects based on input file data.
   * @param file Reference to the input file stream.
   * @param numParties The number of parties to read.
   * @return A vector of CPLParty pointers.
   * @pre 'numParties' > 0
   * @details
   * Reads party and candidate information for CPL elections from the file and
   * creates a vector of CPLParty objects.
   */
  static std::vector<Party*> create_CPL_parties(std::ifstream& file,
                                                int num_parties);

  /**
   * @brief Assigns votes to CPL parties based on file data.
   * @pre input vector is not empty
   * @param file Reference to the input file stream.
   * @param parties Vector of pointers to CPLParty objects.
   * @details
   * Applies vote counts from the file to the corresponding
   * parties in the provided vector.
   */
  static void assign_votes_to_parties(std::ifstream& file,
                                      std::vector<Party*> parties);

  /**
   * @brief Creates an ElectionData object based on the data from a given file.
   * @param filename Path to the election data file.
   * @pre `filename` leads to file that exists and has read permissions
   * @pre `filename` is a properly-formatted representation of an OPL or CPL
   * election
   * @pre `filename` contains data for at least 1 party
   * @pre `filename` contains data for at least 1 candidate
   * @pre `filename` contains fata for at least 1 vote
   * @return A pointer to an ElectionData object containing the parsed data, or
   * nullptr on failure.
   * @details
   * This function reads an election file, determines the type of election,
   * and then creates and returns an appropriate election object populated with
   * candidates, parties, and vote counts.
   */
  static ElectionData* create_election(std::string filename);
};

#endif
