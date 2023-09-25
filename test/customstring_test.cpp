// File: customstring_test.cpp

#include "../3rdpart/gtest/gtest.h"
#include "../inc/datastructure/customstring.h"

using namespace custom;

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter
// Assert: Check if the returned list contains the expected substrings
TEST(StringSplitTest, SplitWithDelimiter) {
  string str("Hello,World!");
  list<string> result = str.split(L",");
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result.front(), "Hello");
  ASSERT_EQ(result.back(), "World!");
}

// Arrange: Create a string object with a given string
// Act: Call the split function without a delimiter
// Assert: Check if the returned list contains the whole string as a single
// substring
TEST(StringSplitTest, SplitWithoutDelimiter) {
  string str("Hello World!");
  list<string> result = str.split();
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), "Hello World!");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with an empty delimiter
// Assert: Check if the returned list contains each character as a separate
// substring
TEST(StringSplitTest, SplitWithEmptyDelimiter) {
  string str("Hello");
  list<string> result = str.split(L"");
  ASSERT_EQ(result.size(), 5);
  ASSERT_EQ(result.front(), "H");
  ASSERT_EQ(result.back(), "o");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is not present in the
// string Assert: Check if the returned list contains the whole string as a
// single substring
TEST(StringSplitTest, SplitWithNonexistentDelimiter) {
  string str("Hello World!");
  list<string> result = str.split(L",");
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), "Hello World!");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a null delimiter
// Assert: Check if the returned list contains the whole string as a single
// substring
TEST(StringSplitTest, SplitWithNullDelimiter) {
  string str("Hello World!");
  list<string> result = str.split(nullptr);
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), "Hello World!");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is longer than the string
// Assert: Check if the returned list contains the whole string as a single
// substring
TEST(StringSplitTest, SplitWithLongDelimiter) {
  string str("Hello");
  list<string> result = str.split(L"Hello World!");
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), "Hello");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is a space character
// Assert: Check if the returned list contains each word as a separate substring
TEST(StringSplitTest, SplitWithSpaceDelimiter) {
  string str("Hello World!");
  list<string> result = str.split(L" ");
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result.front(), "Hello");
  ASSERT_EQ(result.back(), "World!");
}

// Arrange: Create a string object with an empty string
// Act: Call the split function with a delimiter
// Assert: Check if the returned list is empty
TEST(StringSplitTest, SplitEmptyString) {
  string str("");
  list<string> result = str.split(L",");
  ASSERT_TRUE(result.empty());
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is a null character
// Assert: Check if the returned list contains each character as a separate
// substring
TEST(StringSplitTest, SplitWithNullCharacterDelimiter) {
  string str("Hello");
  list<string> result = str.split(L"\0");
  ASSERT_EQ(result.size(), 5);
  ASSERT_EQ(result.front(), "H");
  ASSERT_EQ(result.back(), "o");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is a wide character string
// Assert: Check if the returned list contains each substring separated by the
// delimiter
TEST(StringSplitTest, SplitWithWideDelimiter) {
  string str("Hello,World!");
  list<string> result = str.split(L",");
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result.front(), "Hello");
  ASSERT_EQ(result.back(), "World!");
}

// Arrange: Create a string object with a given string
// Act: Call the split function with a delimiter that is a wide character string
// with multiple characters Assert: Check if the returned list contains each
// substring separated by the delimiter
TEST(StringSplitTest, SplitWithWideDelimiterMultipleCharacters) {
  string str("Hello,World!");
  list<string> result = str.split(L"lo,");
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result.front(), "Hel");
  ASSERT_EQ(result.back(), "World!");
}
