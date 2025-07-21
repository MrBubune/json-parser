#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(KeyValueParsingTest, ParsesSingleKeyValue) {
  std::string text = "{ \"key\": 123 }";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<int>(obj.at("key")));
  EXPECT_EQ(std::get<int>(obj.at("key")), 123);
}

TEST(KeyValueParsingTest, IgnoresWhitespaceAndNewlines) {
  std::string text = "{\n  \"num\":\n 42\n}";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_EQ(std::get<int>(obj.at("num")), 42);
}