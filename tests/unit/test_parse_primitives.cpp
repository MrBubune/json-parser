#include <gtest/gtest.h>
#include "json_parser.h"

using namespace JsonParser;

TEST(ParsePrimitiveTest, ParsesInteger) {
  std::string text = "{ \"num\": 10 }";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<int>(obj.at("num")));
  EXPECT_EQ(std::get<int>(obj.at("num")), 10);
}

TEST(ParsePrimitiveTest, ParsesDouble) {
  std::string text = "{ \"pi\": 3.14 }";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<double>(obj.at("pi")));
  EXPECT_DOUBLE_EQ(std::get<double>(obj.at("pi")), 3.14);
}
