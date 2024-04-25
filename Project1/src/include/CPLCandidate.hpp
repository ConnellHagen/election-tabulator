#ifndef CPL_CANDIDATE_HPP
#define CPL_CANDIDATE_HPP

#include <string>

#include "Candidate.hpp"
/**
 * @class CPLCandidate
 * @brief Represents a candidate in a CPL election. Includes their name and if
 * they are a winner or not.
 */
class CPLCandidate : public Candidate {
 public:
  /**
   * @brief Constructor for `CPLCandidate`.
   * @param name A string of the candidate's name.
   * @pre `name` does not contain special characters, ex. '\\n'
   */
  CPLCandidate(std::string name);

  /**
   * @brief Destructor for `CPLCandidate`
   */
  ~CPLCandidate();

  /**
   * @brief Override for `to_string()`.
   * @param None.
   * @return The candidate's name, and a designation that they are a winner, if
   * applicable.
   */
  std::string to_string() override;
};

#endif