#include "CPLElectionData.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

#include "CPLParty.hpp"
#include "ElectionData.hpp"
#include "Party.hpp"

void CPLElectionData::calculate_winners() {
  // find how many seats each party will be assigned
  std::unordered_map<std::string, int> seats_per_party =
      calculate_seats_per_party();
  std::unordered_map<std::string, int>::iterator it = seats_per_party.begin();

  // // iterate through all parties, and have them assign the proper number of
  // winners
  while (it != seats_per_party.end()) {
    std::string name = it->first;
    // linear search through the parties vector to find the corresponding party
    for (Party* party : parties) {
      if (party->get_name() == name) {
        party->assign_seat_winners(it->second);
        break;
      }
    }
    it++;
  }
}

void CPLElectionData::add_audit_header() {
  audit_log.add_line("Election Type: CPL");
  audit_log.add_line("Total Votes: " + std::to_string(total_ballots));
  audit_log.add_line("Seats Up for Election: " + std::to_string(total_seats));
  audit_log.add_line("Votes per Guaranteed Seat: " + std::to_string(quota));
  audit_log.add_line("");
}

CPLElectionData::CPLElectionData(std::vector<Party*> parties, int total_seats,
                                 int total_ballots)
    : ElectionData(parties, total_seats, total_ballots,
                   std::ceil(static_cast<double>(total_ballots) /
                             static_cast<double>(total_seats))) {
  add_audit_header();
  calculate_winners();
  sort_parties();
}

CPLElectionData::~CPLElectionData() {
  for (Party* party : parties) {
    delete party;
  }
}
