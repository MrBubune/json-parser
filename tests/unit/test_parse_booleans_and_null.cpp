#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(ParseLiteralTest, ParsesTrueBoolean) {
  std::string text = R"({ "flag": true })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<bool>(obj.at("flag")));
  EXPECT_EQ(std::get<bool>(obj.at("flag")), true);
}

TEST(ParseLiteralTest, ParsesFalseBoolean) {
  std::string text = R"({ "flag": false })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_EQ(std::get<bool>(obj.at("flag")), false);
}

TEST(ParseLiteralTest, ParsesNull) {
  std::string text = R"({ "something": null })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<std::nullptr_t>(obj.at("something")));
}
