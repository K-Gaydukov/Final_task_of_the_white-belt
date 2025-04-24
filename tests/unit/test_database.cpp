#include <gtest/gtest.h>
#include "CommonHeaders.h"
#include "DateBase.h"

// Тесты для Date
TEST(DateTest, ParseValidDate) {
    Date date("2023-01-01");
    EXPECT_EQ(date.GetYear(), 2023);
    EXPECT_EQ(date.GetMonth(), 1);
    EXPECT_EQ(date.GetDay(), 1);

    Date date2("-1-12-31");
    EXPECT_EQ(date2.GetYear(), -1);
    EXPECT_EQ(date2.GetMonth(), 12);
    EXPECT_EQ(date2.GetDay(), 31);

    Date date3("1-+1-+1");
    EXPECT_EQ(date3.GetYear(), 1);
    EXPECT_EQ(date3.GetMonth(), 1);
    EXPECT_EQ(date3.GetDay(), 1);
}

TEST(DateTest, ParseInvalidFormat) {
    EXPECT_THROW(Date("2023/01/01"), std::invalid_argument);
    EXPECT_THROW(Date("2023-1"), std::invalid_argument);
    EXPECT_THROW(Date("1---1-1"), std::invalid_argument);
    EXPECT_THROW(Date("abc"), std::invalid_argument);
}

TEST(DateTest, ParseInvalidMonth) {
    EXPECT_THROW(Date("2023-13-01"), std::invalid_argument);
    EXPECT_THROW(Date("2023--1-01"), std::invalid_argument);
}

TEST(DateTest, ParseInvalidDay) {
    EXPECT_THROW(Date("2023-01-32"), std::invalid_argument);
    EXPECT_THROW(Date("2023-01-00"), std::invalid_argument);
}

TEST(DateTest, ToString) {
    Date date("2023-1-1");
    EXPECT_EQ(date.ToString(), "2023-01-01");
    Date date2("1-12-31");
    EXPECT_EQ(date2.ToString(), "0001-12-31");
    Date date3("1-1-1");
    EXPECT_EQ(date3.ToString(), "0001-01-01");
}

TEST(DateTest, Comparison) {
    Date date1("2023-01-01");
    Date date2("2023-01-02");
    Date date3("2022-12-31");
    EXPECT_TRUE(date1 < date2);
    EXPECT_FALSE(date2 < date1);
    EXPECT_TRUE(date3 < date1);
}

// Тесты для Database
TEST(DatabaseTest, AddEvent) {
    Database db;
    Date date("2023-01-01");
    db.AddEvent(date, "event1");
    auto events = db.Find(date);
    EXPECT_EQ(events.size(), 1);
    EXPECT_TRUE(events.count("event1"));

    db.AddEvent(date, "event2");
    events = db.Find(date);
    EXPECT_EQ(events.size(), 2);
    EXPECT_TRUE(events.count("event2"));
}

TEST(DatabaseTest, AddDuplicateEvent) {
    Database db;
    Date date("2023-01-01");
    db.AddEvent(date, "event1");
    db.AddEvent(date, "event1");
    auto events = db.Find(date);
    EXPECT_EQ(events.size(), 1);
}

TEST(DatabaseTest, DeleteEvent) {
    Database db;
    Date date("2023-01-01");
    db.AddEvent(date, "event1");
    EXPECT_TRUE(db.DeleteEvent(date, "event1"));
    EXPECT_FALSE(db.DeleteEvent(date, "event1"));
    EXPECT_EQ(db.Find(date).size(), 0);
}

TEST(DatabaseTest, DeleteNonExistentEvent) {
    Database db;
    Date date("2023-01-01");
    EXPECT_FALSE(db.DeleteEvent(date, "event1"));
}

TEST(DatabaseTest, DeleteDate) {
    Database db;
    Date date("2023-01-01");
    db.AddEvent(date, "event1");
    db.AddEvent(date, "event2");
    EXPECT_EQ(db.DeleteDate(date), 2);
    EXPECT_EQ(db.Find(date).size(), 0);
}

TEST(DatabaseTest, DeleteEmptyDate) {
    Database db;
    Date date("2023-01-01");
    EXPECT_EQ(db.DeleteDate(date), 0);
}

TEST(DatabaseTest, FindEvents) {
    Database db;
    Date date("2023-01-01");
    db.AddEvent(date, "event2");
    db.AddEvent(date, "event1");
    auto events = db.Find(date);
    EXPECT_EQ(events.size(), 2);
    auto it = events.begin();
    EXPECT_EQ(*it++, "event1");
    EXPECT_EQ(*it, "event2");
}

TEST(DatabaseTest, FindNonExistentDate) {
    Database db;
    Date date("2023-01-01");
    EXPECT_EQ(db.Find(date).size(), 0);
}

TEST(DatabaseTest, PrintEvents) {
    Database db;
    db.AddEvent(Date("2023-01-01"), "event1");
    db.AddEvent(Date("2022-12-31"), "event2");
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    db.Print();
    std::cout.rdbuf(old_cout);
    EXPECT_EQ(oss.str(), "2022-12-31 event2\n2023-01-01 event1\n");
}

TEST(DatabaseTest, PrintEmpty) {
    Database db;
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    db.Print();
    std::cout.rdbuf(old_cout);
    EXPECT_EQ(oss.str(), "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}