#include "ElectionData.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "AuditLog.hpp"
#include "Party.hpp"

void ElectionData::sort_parties() {
  std::sort(parties.begin(), parties.end(), Party::compare_ptr_to_Party);

  for (Party* party : parties) {
    party->sort_candidates();
  }
}

ElectionData::ElectionData(std::vector<Party*> parties, int total_seats,
                           int total_ballots, int quota)
    : parties(parties),
      num_parties(parties.size()),
      total_seats(total_seats),
      total_ballots(total_ballots),
      quota(quota) {}

ElectionData::~ElectionData() {}

std::vector<int> ElectionData::break_tie(int num_between) {
  std::vector<int> indices(num_between);
  for (int i = 0; i < num_between; ++i) {
    indices.at(i) = i;
  }

  // Shuffle the indices randomly
  for (int i = 0; i < 1001; i++) {
    std::random_shuffle(indices.begin(), indices.end());
  }

  return indices;
}

std::unordered_map<std::string, int> ElectionData::calculate_seats_per_party() {
  int remaining_seats = total_seats;
  std::unordered_map<std::string, int> seat_map;
  std::vector<std::tuple<std::string, int, int>> tracker;

  srand(time(0));  // Seeds rand() based on the current time

  // Generate temporary data structure for tracking votes and max seats allowed
  for (int i = 0; i < num_parties; i++) {
    std::string temp_name = parties.at(i)->get_name();
    int temp_total_votes = parties.at(i)->get_total_votes();
    int temp_max_seats = parties.at(i)->get_candidates().size();
    std::tuple<std::string, int, int> party_data(temp_name, temp_total_votes,
                                                 temp_max_seats);
    tracker.push_back(party_data);
  }

  // tracker key
  // std::get<0>(tracker[i]) = name
  // std::get<1>(tracker[i]) = votes
  // std::get<2>(tracker[i]) = max_seats (i.e. # candidates)
  int tempSeats = 0;
  int i = 0;
  while (remaining_seats > 0 && i < num_parties) {  // First allocation

    if (quota != 0) {
      tempSeats = std::get<1>(tracker.at(i)) / quota;  // seats / quota
    }

    // if temp seats > max_seats, set to max
    if (tempSeats > std::get<2>(tracker.at(i))) {
      tempSeats = std::get<2>(tracker.at(i));
    }

    seat_map[std::get<0>(tracker.at(i))] += tempSeats;  // allocate seats
    std::get<1>(tracker.at(i)) =
        std::get<1>(tracker.at(i)) - (quota * tempSeats);  // decrement votes
    std::get<2>(tracker.at(i)) =
        std::get<2>(tracker.at(i)) - tempSeats;  // decrement max_seats allowed
    remaining_seats -= tempSeats;                // reduce remaining seats
    allocation_data.insert(
        {std::get<0>(tracker.at(i)),
         std::make_tuple(tempSeats, std::get<1>(tracker.at(i)), 0)});
    i++;
  }

  // Sort by remaining votes after first allocation
  std::sort(tracker.begin(), tracker.end(),
            [](const std::tuple<std::string, int, int>& a,
               const std::tuple<std::string, int, int>& b) {
              return std::get<1>(a) > std::get<1>(b);
            });

  i = 0;
  while (remaining_seats > 0 && i < num_parties) {  // Second allocation
    int num_ties = 1;

    while (i + num_ties < num_parties &&
           std::get<1>(tracker.at(i)) ==
               std::get<1>(tracker.at(i + num_ties))) {  // Check for tied votes
      num_ties++;
    }

    int seats_to_assign = std::min(remaining_seats, num_ties);

    // Break ties if needed and assign seats to tied candidates
    std::vector<int> tie_indices = ElectionData::break_tie(num_ties);

    if (num_ties > 1) {  // Prepare tie-breaker logging information

      std::stringstream parties_involved;
      for (int ti = 0; ti < num_ties; ++ti) {
        if (ti > 0) parties_involved << ", ";
        parties_involved << std::get<0>(tracker[i + ti]);
      }

      std::string array_produced = "";
      for (unsigned long int j = 0; j < tie_indices.size(); j++) {
        array_produced += std::to_string(tie_indices.at(j));
        if (j != tie_indices.size() - 1)
            array_produced += ", ";
      }

      int random_seed = rand();
      // Log tie-breaker details
      audit_log.add_line("TIE BREAKER INFO | PARTY SEAT ALLOCATION");
      audit_log.add_line("Tie breaker between [" + parties_involved.str() +
                         "] for " + std::to_string(seats_to_assign) + " seats");
      audit_log.add_line(
          "Random seed generated: " + std::to_string(random_seed) +
          ", Results from sample #1001...");
      audit_log.add_line("Randomized array produced: [" + array_produced +
                         "]");
    }

    std::stringstream winners;
    for (int j = 0; j < seats_to_assign; ++j) {
      int winner_index = tie_indices.at(j);
      if (std::get<2>(tracker.at(i + winner_index)) > 0) {
        std::string winner_name = std::get<0>(tracker.at(i + winner_index));
        seat_map[winner_name] += 1;  // Allocate seats

        if (j > 0) winners << ", ";
        winners << winner_name;

        allocation_data[winner_name] =
            std::make_tuple(std::get<0>(allocation_data[winner_name]),
                            std::get<1>(allocation_data[winner_name]),
                            std::get<2>(allocation_data[winner_name]) + 1);

        std::get<1>(tracker.at(i + winner_index)) =
            std::get<1>(tracker.at(i + winner_index)) -
            (quota * 1);  // Decrement votes
        std::get<2>(tracker.at(i + winner_index)) =
            std::get<2>(tracker.at(i + winner_index)) -
            1;  // Decrement max_seats allowed

        remaining_seats -= 1;  // Reduce remaining seats
      }
    }

    if (num_ties > 1) {
      audit_log.add_line("Winner(s) of the tie breaker: [" + winners.str() +
                         "]" + "\n");
    }

    i += num_ties;
  }

  return seat_map;
}

void ElectionData::display() {
  for (Party* party : parties) {
    std::cout << party->to_string();
  }
}

void ElectionData::generate_audit_file() {
  std::vector<std::tuple<std::string, int, int, int, int, std::string>> rows;

  // iterate through `allocation_data` and fill `rows` with the properly
  // calculated data
  std::map<std::string, std::tuple<int, int, int>>::iterator it =
      allocation_data.begin();
  while (it != allocation_data.end()) {
    // (first seats, remaining votes, second allocation seats)
    std::tuple pre_row = it->second;

    // quota * number of first-round seats + the remaining number of votes
    int total_votes = quota * std::get<0>(pre_row) + std::get<1>(pre_row);

    int percent_votes = 100 * total_votes / total_ballots;
    int percent_seats =
        100 * (std::get<0>(pre_row) + std::get<2>(pre_row)) / total_seats;
    std::string percentage_display = std::to_string(percent_votes) + "%/" +
                                     std::to_string(percent_seats) + "%";

    rows.push_back(std::make_tuple(it->first, total_votes, std::get<0>(pre_row),
                                   std::get<1>(pre_row), std::get<2>(pre_row),
                                   percentage_display));
    it++;
  }

  audit_log.add_allocation_table(rows);
  audit_log.add_line("");

  // add to one variable to avoid newline issues
  std::string party_to_strings = "";
  for (Party* party : parties) {
    party_to_strings += party->to_string();
  }
  audit_log.add_line(party_to_strings);

  audit_log.write_to_file();
}
