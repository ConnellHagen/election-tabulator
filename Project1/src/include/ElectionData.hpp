#ifndef ELECTION_DATA_HPP
#define ELECTION_DATA_HPP

#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "AuditLog.hpp"
#include "Party.hpp"

/**
 * @class ElectionData
 * @brief Abstract representation of an election containing parties, seats to be
 * awarded, and ballots.
 * @details
 * Contains all Parties in the election and their candidates within those
 * parties. Also includes the total available seats, the total ballots
 * submitted, the number of parties in the election, the quota necessary for a
 * Party to win a seat, and some data that is stored for creating an audit log.
 */
class ElectionData {
 protected:
  std::vector<Party*> parties;
  int num_parties;
  int total_seats;
  int total_ballots;
  int quota;
  /* allocation data schema:
     party name => (first allocation seats, remaining votes, second allocation
     seats) */
  std::map<std::string, std::tuple<int, int, int>> allocation_data;
  AuditLog audit_log;

  /**
   * @brief Calculates the amount of seats each party has won.
   * @return A map with each party's name and the amount of seats they have won.
   * @pre quota is greater than 0
   * @pre total_votes is greater than 0
   * @pre total_seats is greater than 0
   * @pre parties is not an empty vector
   * @pre num_parties is greater than 0
   */
  std::unordered_map<std::string, int> calculate_seats_per_party();

  /**
   * @brief Sorts `parties` by number of votes received.
   * @param None.
   * @details
   * Sorts `parties` in descending order by number of votes recieved, and sorts
   * their `Candidates` by a criteria specified in the implementation for
   * `Party` used.
   */
  void sort_parties();

  /**
   * @brief Adds an election-specific header to the audit log.
   * @param None.
   */
  virtual void add_audit_header() = 0;

 public:
  /**
   * @brief Randomly shuffles indices to break a tie between candidates.
   *
   * This function generates a vector of integers from 0 to (num_between - 1)
   * and then shuffles them randomly. It is intended to provide a fair and
   * unpredictable method of breaking ties between candidates in an election.
   *
   * @param num_between The number of candidates involved in the tie.
   * @return std::vector<int> A vector containing the shuffled indices
   * representing the order in which the tie is broken.
   * @pre `num_between` is greater than 0
   */
  static std::vector<int> break_tie(int num_between);

  /**
   * @brief the constructor for ElectionData
   * @param parties a vector of Party objects
   * @param total_seats the total seats available to be won
   * @param total_ballots the total ballots submitted
   * @param quota the amount of votes needed for a party to win 1 seat
   */
  ElectionData(std::vector<Party*> parties, int total_seats, int total_ballots,
               int quota);

  /**
   * @brief Destructor for `ElectionData`
   */
  virtual ~ElectionData();

  /**
   * @brief Calculates the winning candidates for each seat.
   * @param None.
   */
  virtual void calculate_winners() = 0;

  /**
   * @brief Generates an audit file with various information about the election
   * algorithm.
   * @param None.
   * @post Audit file will be output in the same directory as the executable
   * file.
   */
  void generate_audit_file();

  /**
   * @brief Displays all necessary information for an election official to the
   * terminal.
   * @param None.
   * @post All winners will be displayed with a designation.
   * @post Parties will be displayed in descending order by number of votes.
   */
  void display();
};

#endif
