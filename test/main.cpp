#include <gtest/gtest.h>

#include "levenshtein.h"

TEST(SpellChecker, SuggestionList) {
    std::vector<std::string> corrected = list_suggestions("goood");
    std::vector<std::string> suggestion{"good",  "drood", "flood", "food",
                                        "pood",  "mood",  "mooed", "agood",
                                        "looed", "loord"};

    ASSERT_EQ(corrected, suggestion);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}