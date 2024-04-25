#include <gtest/gtest.h>

#include "../src/include/AuditLog.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// Reading file content into a string to verify the the test's expected results
std::string readFileContent(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in);
    if (!file) return ""; 

     std::stringstream buffer;
     buffer << file.rdbuf(); 
     return buffer.str(); 
}

class AuditLogTest : public ::testing::Test {
protected:
    std::string testDirectory = "./testAuditLogs";// Tests Directory
    AuditLog auditLog;

    // SetUp ensuring there is testDirectory
    void SetUp() override {
        fs::create_directory(testDirectory);
    }

    // TearDown removing the test directory and content
    void TearDown() override {
        fs::remove_all(testDirectory);
    }
};

TEST(AuditLogUnitTest, HelloWorldTest) {
}

// Constructor test verifies Audit Log constructor initializes the log with an empty string
TEST_F(AuditLogTest, ConstructorTest) {
    std::string filename = "ConstructorTest.txt";
    auditLog.write_to_file(testDirectory, filename); // Write initilized log to file ConstructorTest.txt

    std::string fullPath = fs::path(testDirectory) / filename;
    std::string fileContent = readFileContent(fullPath);
    EXPECT_EQ("", fileContent); // Expect the log to be empty
}

// Clear log test verifies clear_log method correctly clears the log's content to an empty string
TEST_F(AuditLogTest, ClearLogTest) {
    auditLog.add_line("Test line for ClearLogTest"); // adding a test line
    auditLog.clear_log(); // Clear the log after adding a line

    std::string filename = "clearLogTest.txt";
    auditLog.write_to_file(testDirectory, filename); // Write the cleared log to file clearLogTest.txt

    std::string fullPath = fs::path(testDirectory) / filename;
    std::string fileContent = readFileContent(fullPath);
    EXPECT_EQ("", fileContent); // Expect the file to be empty if the log was cleared
}

// Add line test verifies add_line method correctly adds a line to the log
TEST_F(AuditLogTest, AddLineTest) {
    std::string testLine = "Test line for AddLineTest";
    auditLog.add_line(testLine); // creating and adding a test line
    std::string filename = "AddLineTest.txt";
    auditLog.write_to_file(testDirectory, filename); // Write the log to file AddLineTest.txt

    std::string fullPath = fs::path(testDirectory) / filename;
    std::string fileContent = readFileContent(fullPath);
    EXPECT_EQ(testLine + "\n", fileContent); // Expect the file to have the added test line
}

TEST_F(AuditLogTest, WriteToFileTest) {
    std::string testLine = "Test line for WritetoFileTest";
    auditLog.add_line(testLine); // Add a test line for content to write

    std::string filename = "writeToFileTest.txt";
    auditLog.write_to_file(testDirectory, filename); // Write the log to file writeToFileTest.txt

    std::string fullPath = fs::path(testDirectory) / filename;
    std::string fileContent = readFileContent(fullPath);
    EXPECT_EQ(testLine + "\n", fileContent); // Expect the file to contain the test line added
}
