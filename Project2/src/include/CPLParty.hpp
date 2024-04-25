#ifndef CPL_PARTY_HPP
#define CPL_PARTY_HPP

#include <vector>

#include "CPLCandidate.hpp"
#include "Party.hpp"
#include "AuditLog.hpp"

/**
 * @class CPLParty
 * @brief Represents a political party in a Closed Party List (CPL) system.
 * @details
 * This class extends the generic Party class to implement functionality
 * specific to parties in a CPL electoral system, where candidates are
 * pre-listed by the party and seats are assigned to parties based on the total
 * votes they receive, to be filled by their listed candidates.
 */
class CPLParty : public Party {
 public:
  /**
   * @brief Constructor for `CPLParty`
   * @param candidates A vector of pointers to `CPLCandidate` objects
   * representing the candidates of the party.
   * @param name The name of the party.
   * @pre `candidates` is not empty.
   * @pre `candidates` does not contain `NULL` or `nullptr`.
   * @pre `candidates` are listed in the order of their priority of winning a
   * seat.
   * @pre `name` does not contain special characters, ex. '\\n'.
   */
  CPLParty(std::vector<Candidate*> candidates, std::string name);

  /**
   * @brief Destructor for `CPLParty`.
   */
  ~CPLParty() override;

  /**
   * @brief Assigns winners based on the number of seats won by the party.
   * @param seats The number of seats won by the party to be assigned to candidates.
   * @param log An audit log to output information to; nothing is output for a `CPLParty`.
   * @details
   * Marks the top 'seats' candidates as winners, where 'seats' is the number
   * of seats won by the party. It assumes that the candidates are listed in
   * order of their priority for seat allocation.
   */
  void assign_seat_winners(int seats, AuditLog* log = nullptr) override;
};

#endif
