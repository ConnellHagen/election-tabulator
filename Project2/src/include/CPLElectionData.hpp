#include <vector>

#include "CPLParty.hpp"
#include "ElectionData.hpp"

/**
 * @class CPLElectionData
 * @brief Represents A Closed Party List (CPL) Election.
 * @details
 * Contains all Parties within the election, and by extension, their candidates.
 * Also contains data relating to the number of votes required to win a seat,
 * and for logging information about the winner calculation process.
 */
class CPLElectionData : public ElectionData {
 protected:
  /**
   * @brief Calculates the winning candidates for all seats to be won.
   * @param None.
   * @details
   * Sets the `winner` variable to true for all aggregated `CPLCandidate`s who
   * won a seat.
   */
  void calculate_winners() override;

  /**
   * @brief Adds a CPL-specific header to the audit log.
   * @param None.
   * @details
   * Adds lines including the election type, number of votes cast, number of
   * seats being awarded, and the number of votes for a guaranteed seat.
   */
  void add_audit_header();

 public:
  /**
   * @brief Constructor for `CPLElectionData`.
   * @param parties A list of all parties in the election represented by
   * `CPLParty` objects.
   * @param total_seats Total number of seats to be won during the election.
   * @param total_ballots Total number of votes cast in the election.
   * @pre `parties` is not empty.
   * @pre `parties` does not contain any `nullptr` or `NULL` values.
   * @pre `total_seats` is at least 1 and less than the number of total
   * candidates.
   * @pre `total_ballots` is at least 1.
   * @post Winner calculation algorithm will be completely finished running;
   * `display()` will give correct winners.
   */
  CPLElectionData(std::vector<Party*> parties, int total_seats,
                  int total_ballots);

  /**
   * @brief Destructor for `CPLElectionData`.
   */
  ~CPLElectionData() override;
};
