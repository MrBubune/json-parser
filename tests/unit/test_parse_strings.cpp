#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(ParseStringTest, ParsesSimpleString) {
  std::string text = R"({ "greeting": "hello" })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_TRUE(std::holds_alternative<std::string>(obj.at("greeting")));
  EXPECT_EQ(std::get<std::string>(obj.at("greeting")), "hello");
}

TEST(ParseStringTest, ParsesEscapedCharacters) {
  std::string text = R"({ "path": "C:\\Users\\Daryl" })";
  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  const auto& obj = std::get<JsonObject>(val);
  EXPECT_EQ(std::get<std::string>(obj.at("path")), "C:\\Users\\Daryl");
}
