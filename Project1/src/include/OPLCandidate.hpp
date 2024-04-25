#ifndef OPL_CANDIDATE_HPP
#define OPL_CANDIDATE_HPP

#include <string>

#include "Candidate.hpp"

/**
 * @class OPLCandidate
 * @brief Represents a candidate in an OPL election. Includes their name, their
 * number of votes and if they are a winner or not.
 */
class OPLCandidate : public Candidate {
 public:
  /**
   * @brief Constructor for `OPLCandidate`.
   * @param name A string of the candidate's name.
   */
  OPLCandidate(std::string name);

  /**
   * @brief Destructor for `OPLCandidate`
   */
  ~OPLCandidate();

  /**
   * @brief Override for `to_string()`.
   * @param None.
   * @return The candidate's number of votes, their name, and a designation that
   * they are a winner, if applicable.
   */
  std::string to_string() override;
};

#endif