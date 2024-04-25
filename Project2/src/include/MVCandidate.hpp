#ifndef MV_CANDIDATE_HPP
#define MV_CANDIDATE_HPP

#include <string>

#include "Candidate.hpp"

/**
 * @class MVCandidate
 * @brief Represents a candidate in an MV election. Includes their name, their
 * number of votes and if they are a winner or not.
 */
class MVCandidate : public Candidate {
 public:
  /**
   * @brief Constructor for `MVCandidate`.
   * @param name A string of the candidate's name.
   */
  MVCandidate(std::string name);

  /**
   * @brief Destructor for `MVCandidate`
   */
  ~MVCandidate();

  /**
   * @brief Override for `to_string()`.
   * @param None.
   * @return The candidate's number of votes, their name, and a designation that
   * they are a winner, if applicable.
   */
  std::string to_string() override;
};

#endif