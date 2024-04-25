#ifndef MPO_CANDIDATE_HPP
#define MPO_CANDIDATE_HPP

#include <string>

#include "Candidate.hpp"

/**
 * @class MPOCandidate
 * @brief Represents a candidate in an MPO election. Includes their name, their
 * number of votes and if they are a winner or not.
 */
class MPOCandidate : public Candidate {
 public:
  /**
   * @brief Constructor for `MPOCandidate`.
   * @param name A string of the candidate's name.
   */
  MPOCandidate(std::string name);

  /**
   * @brief Destructor for `MPOCandidate`
   */
  ~MPOCandidate();

  /**
   * @brief Override for `to_string()`.
   * @param None.
   * @return The candidate's number of votes, their name, and a designation that
   * they are a winner, if applicable.
   */
  std::string to_string() override;
};

#endif