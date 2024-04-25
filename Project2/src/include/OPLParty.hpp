#ifndef OPL_PARTY_HPP
#define OPL_PARTY_HPP

#include <vector>

#include "OPLCandidate.hpp"
#include "Party.hpp"
#include "AuditLog.hpp"

/**
 * @class OPLParty
 * @brief Represents a party in an Open Party List (OPL) electoral system.
 * @details
 * Extends the Party class to implement functionality specific to OPL electoral
 * systems, where voters vote for candidates within parties and seats are
 * allocated to parties based on total votes, which are then distributed to
 * individual candidates within the party based on vote counts.
 */
class OPLParty : public Party {
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
   * @brief Constructor for `OPLParty`.
   * @param candidates A vector of pointers to `OPLCandidate` objects representing the candidates of the party.
   * @param name The name of the party.
   * @pre `candidates` is not empty.
   * @pre `candidates` does not contain `NULL` or `nullptr`.
   * @pre `name` does not contain special characters, ex. '\\n'.
   */
  OPLParty(std::vector<Candidate*> candidates, std::string name);

  /**
   * @brief Destructor for `OPLParty`.
   */
  ~OPLParty() override;

  /**
   * @brief Assigns winning seats to candidates based on the number of seats won by the party.
   * @param seats The number of seats won by the party to be assigned to candidates.
   * @param log An audit log to which tie-breaking information is to be output to.
   * @pre seats is non-negative.
   * @details
   * Sorts the candidates within the party by their number of votes in
   * descending order, and then assigns seats to the top candidates based on the
   * number of seats won. The 'winner' flag in the OPLCandidate class is set to
   * true for the winning candidates. Ties are handled by the
   * `ElectionData::break_tie(int)` function.
   */
  void assign_seat_winners(int seats, AuditLog* log) override;

  /**
   * @brief Sorts `Candidate`s within the party in descending order by number of
   * votes received.
   * @param None.
   */
  void sort_candidates() override;
};

#endif
