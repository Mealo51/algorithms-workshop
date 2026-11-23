// Challenge 9: Collapse consecutive collision reports in a debug log
//
// Within a simulation tick, several colliders can report the same projectile
// and target pair in a row. For the debug log, keep the first report of
// each consecutive run, including its sample ID. Keep the original order.
// A later report after a different contact stays visible in the log.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

struct ContactReport {
    int projectileId;
    int targetId;
    int sampleId;

    bool operator==(const ContactReport&) const = default;
};

void collapse_contact_runs(std::vector<ContactReport>& reports) {
    // TODO: Use std::unique with a predicate that compares the contact pair.
    // Then erase the tail at the returned logical end. Keep the log order.
    // https://en.cppreference.com/cpp/algorithm/unique
    // https://en.cppreference.com/cpp/container/vector/erase
    if (reports.empty()) {
        return;
    }

    std::size_t kept = 1;
    for (std::size_t i = 1; i < reports.size(); ++i) {
        const ContactReport& last = reports[kept - 1];
        if (reports[i].projectileId != last.projectileId ||
            reports[i].targetId != last.targetId) {
            reports[kept] = reports[i];
            ++kept;
        }
    }
    reports.resize(kept);
}

TEST(CollapseContactRunsTest, KeepsFirstReportOfEachUnsortedRun) {
    std::vector<ContactReport> reports{
        {7, 4, 10}, {7, 4, 11}, {7, 2, 12},
        {7, 4, 13}, {7, 4, 14}, {6, 4, 15}
    };
    const std::vector<ContactReport> expected{
        {7, 4, 10}, {7, 2, 12}, {7, 4, 13}, {6, 4, 15}
    };

    collapse_contact_runs(reports);
    EXPECT_EQ(reports, expected);
}

TEST(CollapseContactRunsTest, EmptyAndSingleRun) {
    std::vector<ContactReport> reports;
    collapse_contact_runs(reports);
    EXPECT_TRUE(reports.empty());

    reports = {{3, 5, 10}, {3, 5, 11}};
    collapse_contact_runs(reports);
    const std::vector<ContactReport> expected{{3, 5, 10}};
    EXPECT_EQ(reports, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
