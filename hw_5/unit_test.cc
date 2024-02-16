#include "gtest/gtest.h"
#include "utilities.h"
#include <map>

// Test fixture for occurrence_map function
class OccurrenceMapTest : public ::testing::Test {
protected:
    // Path to test file
    std::string file_path;

    // Constructor, called before each test
    OccurrenceMapTest() {
        // Initialize the file path to the test file
        file_path = "test.txt";
    }
};

// Test case for occurrence_map function
TEST_F(OccurrenceMapTest, BasicTest) {
    // Expected word occurrences
    std::map<std::string, int> expected_occurrences = {
            {"this", 1},
            {"is", 1},
            {"a", 1},
            {"test", 2},
            {"file", 1}
    };

    // Call the occurrence_map function
    std::map<std::string, int> actual_occurrences = occurrence_map(file_path);

    // Compare actual and expected results
    ASSERT_EQ(expected_occurrences.size(), actual_occurrences.size());
    for (const auto& pair : expected_occurrences) {
        ASSERT_EQ(pair.second, actual_occurrences[pair.first]);
    }
}

// More test cases can be added as needed

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
