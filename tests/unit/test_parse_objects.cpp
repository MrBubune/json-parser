#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(ParseObjectTest, ParsesNestedObject) {
  std::string text = R"({
    \"info\": {
      \"level\": 5,
      \"score\": 99.9
    }
  })";

  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);
  const auto& obj = std::get<JsonObject>(val);
  const auto& inner = std::get<JsonObject>(obj.at("info"));

  EXPECT_EQ(std::get<int>(inner.at("level")), 5);
  EXPECT_DOUBLE_EQ(std::get<double>(inner.at("score")), 99.9);
}