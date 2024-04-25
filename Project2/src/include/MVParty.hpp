#ifndef MV_PARTY_HPP
#define MV_PARTY_HPP

#include <vector>

#include "MVCandidate.hpp"
#include "Party.hpp"
#include "AuditLog.hpp"

/**
 * @class MVParty
 * @brief Represents a party in an Multiple Popularity Only (MV) electoral system.
 * @details
 * Extends the Party class to implement functionality specific to MV electoral
 * systems, where voters vote for candidates within parties and seats are
 * allocated to parties based on total votes, which are then distributed to
 * individual candidates within the party based on vote counts.
 */
class MVParty : public Party {
 private:
  /**
   * @brief Calculates the total number of votes received by all candidates in the party.
   * @details
   * Iterates through each candidate in the party and sums up their votes,
   * updating the `total_votes` attribute from the base class `Party`.
   */
  void calculate_total_votes();

 public:
  /**
   * @brief Constructor for `MVParty`.
   * @param candidates A vector of pointers to `MVCandidate` objects representing the candidates of the party.
   * @param name The name of the party.
   * @pre `candidates` is not empty.
   * @pre `candidates` does not contain `NULL` or `nullptr`.
   * @pre `name` does not contain special characters, ex. '\\n'.
   */
  MVParty(std::vector<Candidate*> candidates, std::string name);

  /**
   * @brief Destructor for `MVParty`.
   */
  ~MVParty() override;

  /**
   * @brief Sorts `Candidate`s within the party in descending order by number of
   * votes received.
   * @param None.
   */
  void sort_candidates() override;

  /**
  * @brief not necessary for how MVParty is set up but necessary for proper compilation*/
  void assign_seat_winners(int seats, AuditLog* log){};
};

#endif