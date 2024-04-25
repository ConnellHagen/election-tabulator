#include "AuditLog.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <ctime>
#include <random>

using namespace std::chrono;

// Constructor initializes log as an empty string.
AuditLog::AuditLog() : log("") {}

// Adds an allocation table to the log and each row of the table is formatted
// and appended
void AuditLog::add_allocation_table(
    const std::vector<std::tuple<std::string, int, int, int, int, std::string>>&
        table) {
  std::ostringstream stream;

  // Column widths
  const int party_width = 15;
  const int votes_width = 10;
  const int seats_width = 25;
  const int votes_remaining_width = 20;
  const int second_allocation_width = 20;
  const int vote_seat_percent_width = 15;

  // Header for the allocation table
  stream << std::left << std::setw(party_width) << "Party"
         << std::setw(votes_width) << "Votes" << std::setw(seats_width)
         << "First Allocation Seats" << std::setw(votes_remaining_width)
         << "Remaining Votes" << std::setw(second_allocation_width)
         << "Second Allocation" << std::setw(vote_seat_percent_width)
         << "Vote %/Seat %"
         << "\n";

  // Iterate rows of the table and append it to the stream
  for (const auto& row : table) {
    stream << std::left << std::setw(party_width) << get<0>(row) << " "
           << std::setw(votes_width + 10) << get<1>(row) << " "
           << std::setw(seats_width - 7) << get<2>(row) << " "
           << std::setw(votes_remaining_width) << get<3>(row) << " "
           << std::setw(second_allocation_width - 5) << get<4>(row) << " "
           << std::setw(vote_seat_percent_width) << get<5>(row) << "\n";
  }

  // Append the formatted table string to the log
  log += stream.str();
}

// Adds a line of text to the log
void AuditLog::add_line(const std::string& line) { log += line + "\n"; }

// Clears the logs content, log returns to empty string
void AuditLog::clear_log() { log.clear(); }

// Writes the log content to a file
void AuditLog::write_to_file() {
    // Records the current time with high-resolution
    auto now = high_resolution_clock::now();
    auto time_point = duration_cast<microseconds>(now.time_since_epoch());
    auto time = system_clock::to_time_t(system_clock::now());
    tm* ptm = localtime(&time);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;


    // Generate a random number between 1 and 1 million
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    int random_number = dis(gen);

    // Construct the file name
    std::ostringstream filename;
    filename << "audit_" << std::put_time(ptm, "%Y-%m-%d_%H-%M-%S") << "_" << std::setw(6) << std::setfill('0') << microseconds.count() << random_number << ".txt";

    std::ofstream file(filename.str());
    if (file) {
        file << log; // Write the log to the file
        file.close(); // Close the file
    }
}

// Overloaded version of write_to_file for testing, allows specifying filename
void AuditLog::write_to_file(const std::string& directory,
                             const std::string& filename) {
  std::string fullPath = directory + "/" + filename;
  std::ofstream file(fullPath);  // open the file for writing
  if (file) {
    file << log;   // Write the log to the file
    file.close();  // Close the file after writing
  }
}
