#ifndef PARTY_HPP
#define PARTY_HPP

#include <string>
#include <vector>

#include "Candidate.hpp"
#include "AuditLog.hpp"

/**
 * @class Party
 * @brief Abstract representation of a political party.
 * @details
 * Defines common attributes and functionalities for a political party
 * participating in an election. This class serves as a base for specific types
 * of party classes tailored to different electoral systems. All will contain a
 * list of `Candidates`, a name, the number of seats they won, and a number of
 * votes they received.
 */
class Party {
 protected:
  std::vector<Candidate*> candidates;
  std::string name;
  int total_votes;

 public:
  int seats_allocated;

  /**
   * @brief Constructs a Party object with a specified name.
   * @param candidates A vector of all Candidates being run by the party in this
   * election.
   * @param name The name of the party.
   */
  Party(std::vector<Candidate*> candidates, std::string name);

  /**
   * @brief Virtual destructor for the Party class.
   */
  virtual ~Party();

  /**
   * @brief Getter for `candidates`.
   * @param None.
   * @return A vector of all aggregated `Candidate`s.
   */
  inline std::vector<Candidate*> get_candidates() const { return candidates; }

  /**
   * @brief Retrieves the name of the party.
   * @param None.
   * @return A string representing the name of the party.
   */
  inline std::string get_name() const { return name; }

  /**
   * @brief Retrieves the total number of votes received by the party.
   * @param None.
   * @return An integer representing the total votes received.
   */
  inline int get_total_votes() const { return total_votes; }

  /**
   * @brief Setter for `total_votes`.
   * @param votes The new total votes to be set for the party.
   */
  inline void set_total_votes(int votes) { total_votes = votes; }

  /**
   * @brief Assigns seats to winning candidates.
   * @param seats The number of seats to be allocated.
   * @param log An audit log to which relevant information, like ties, can be logged.
   */
  virtual void assign_seat_winners(int seats, AuditLog* log) = 0;

  /**
   * @brief `to_string` for `Party`
   * @return String representation of the party
   * @details
   * Includes the number of votes that the party received, its name, and
   * the `to_string` representation of all of its `Candidate`s.
   */
  std::string to_string();

  /**
   * @brief Sorts the candidates of the `Party` to prepare for display.
   * @param None.
   * @details
   * By default, this method will do nothing. If an election type has a
   * way that candidates are ranked / ordered that is not pre-determined
   * before the election starts, then this method will be overriden.
   */
  virtual void sort_candidates();

  /**
   * @brief Comparision helper used for sorting pointers of `Party`s.
   * @param p1 First `Party` pointer being compared
   * @param p2 Second `Party` pointer being compared
   * @details
   * Compares the 2 `Party`s by the number of votes they have received.
   */
  inline static bool compare_ptr_to_Party(Party* p1, Party* p2) {
    return p1->get_total_votes() > p2->get_total_votes();
  }
};

#endif
