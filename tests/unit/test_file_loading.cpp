#include <gtest/gtest.h>
#include "json_loader/json_loader.h"
#include <string>

using namespace JsonLoader;
using namespace JsonParser;

TEST(FileLoadingTest, LoadsNumbersJsonCorrectly) {
  JsonValue result = LoadFromFile("../tests/data/numbers.json");
  const auto& obj = std::get<JsonObject>(result);

  ASSERT_TRUE(std::holds_alternative<int>(obj.at("int")));
  EXPECT_EQ(std::get<int>(obj.at("int")), 42);

  ASSERT_TRUE(std::holds_alternative<double>(obj.at("float")));
  EXPECT_DOUBLE_EQ(std::get<double>(obj.at("float")), 3.1415);
}

TEST(FileLoadingTest, LoadsNestedObjectJsonCorrectly) {
  JsonValue result = LoadFromFile("../tests/data/nested_object.json");
  const auto& obj = std::get<JsonObject>(result);
  const auto& user = std::get<JsonObject>(obj.at("user"));
  const auto& profile = std::get<JsonObject>(user.at("profile"));

  EXPECT_EQ(std::get<int>(user.at("id")), 101);
  EXPECT_DOUBLE_EQ(std::get<double>(profile.at("score")), 87.5);
  EXPECT_EQ(std::get<int>(profile.at("active")), 1);
}
