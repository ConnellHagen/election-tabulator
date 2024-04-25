#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

#include <string>
/**
 * @class Candidate
 * @brief Abstract representation of candidate, including a name, number of
 * votes, and whether or not they won a seat.
 */
class Candidate {
 protected:
  int num_votes;
  std::string name;
  bool winner;

 public:
  /**
   * @brief Constructor for `Candidate`.
   * @param name The candidate's name.
   */
  Candidate(std::string name);

  /**
   * @brief Destructor for `Candidate`
   */
  virtual ~Candidate();

  /**
   * @brief Getter for `num_votes`.
   * @param None.
   * @return Value of `num_votes`.
   */
  inline int get_num_votes() const { return num_votes; }

  /**
   * @brief Setter for `num_votes`.
   * @param p_num_votes The new value for `num_votes`.
   * @pre p_num_votes is non-negative.
   */
  inline void set_num_votes(int p_num_votes) { num_votes = p_num_votes; }

  /**
   * @brief Getter for the candidate's `name`.
   * @param None.
   * @return Value of `name`.
   */
  inline std::string get_name() const { return name; }

  /**
   * @brief Getter for `winner`.
   * @param None.
   * @return Value of `winner`.
   */
  inline bool get_winner() const { return winner; }

  /**
   * @brief Setter for `winner`.
   * @param p_winner The new value for `winner`.
   */
  inline void set_winner(bool p_winner) { winner = p_winner; }

  /**
   * @brief `to_string()` for the candidate.
   * @param None.
   * @return A string representation of the candidate.
   */
  virtual std::string to_string() = 0;

  /**
   * @brief Comparision helper used for sorting pointers of `Candidates`s.
   * @param c1 First `Candidates` pointer being compared
   * @param c2 Second `Candidates` pointer being compared
   * @details
   * Compares the 2 `Candidates`s by the number of votes they have received.
   */
  inline static bool compare_ptr_to_Candidate(Candidate* c1, Candidate* c2) {
    return c1->get_num_votes() > c2->get_num_votes();
  }
};

#endif