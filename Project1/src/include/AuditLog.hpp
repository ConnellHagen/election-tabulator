#ifndef AUDIT_LOG_HPP
#define AUDIT_LOG_HPP

#include <string>
#include <tuple>
#include <vector>

/**
 * @class AuditLog
 * @brief the AuditLog class is for logging election data, including allocation
 * tables class supports adding lines of text, formatted allocation tables,
 * clearing the log, and writing the log to a file
 */
class AuditLog {
 private:
  std::string log;

 public:
  /**
   * @brief Constructor for `AuditLog`
   */
  AuditLog();

  /**
   * @brief Adds a formatted allocation table to the log
   * @param table A vector of tuples for the allocation table to add to the log,
   * representing rows of the allocation table Party (string), Votes (int),
   * First Allocation Seats (int), Remaining Votes (int), Second Allocation
   * (int), Vote %/Seat % (string)
   */
  void add_allocation_table(
      const std::vector<
          std::tuple<std::string, int, int, int, int, std::string>>& table);

  /**
   * @brief Adds a line of text to the log
   * @param line The line to add to the log
   */
  void add_line(const std::string& line);

  /**
   * @brief Clears all content from the log
   */
  void clear_log();

  /**
   * @brief Writes the log content to a file with a timestamped name to the
   * specified directory
   */
  void write_to_file();

  /**
   * @brief method to write the log content to a specific file for testing
   * @param directory The directory to write the log file to
   * @param filename The name of the file to write the log to
   */
  void write_to_file(const std::string& directory, const std::string& filename);
};

#endif
