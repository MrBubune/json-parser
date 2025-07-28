#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(ParseArrayTest, ParsesSimpleArray) {
  std::string text = R"({ "nums": [1, 2, 3] })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  const auto& arr = std::get<JsonArray>(obj.at("nums"));

  ASSERT_EQ(arr.size(), 3);
  EXPECT_EQ(std::get<int>(arr[0]), 1);
  EXPECT_EQ(std::get<int>(arr[1]), 2);
  EXPECT_EQ(std::get<int>(arr[2]), 3);
}

TEST(ParseArrayTest, ParsesNestedArray) {
  std::string text = R"({ "nested": [10, {"a": 1}, [20]] })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  const auto& arr = std::get<JsonArray>(obj.at("nested"));

  EXPECT_EQ(std::get<int>(arr[0]), 10);
  const auto& innerObj = std::get<JsonObject>(arr[1]);
  EXPECT_EQ(std::get<int>(innerObj.at("a")), 1);

  const auto& innerArr = std::get<JsonArray>(arr[2]);
  EXPECT_EQ(std::get<int>(innerArr[0]), 20);
}
