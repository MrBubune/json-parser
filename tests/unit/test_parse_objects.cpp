#include <gtest/gtest.h>
#include "json_parser/json_parser.h"

using namespace JsonParser;

TEST(ParseObjectTest, ParsesNestedObject) {
  // Fixed: JSON string is now complete and valid
  std::string text = R"({
    "info": {
      "level": 5,
      "score": 99.9
    }
  })";

  auto it = text.begin();
  JsonValue val = ParseJsonHelper(text, it);

  // Ensure it's an object
  ASSERT_TRUE(std::holds_alternative<JsonObject>(val));
  const auto& obj = std::get<JsonObject>(val);

  // Ensure "info" key is present and is an object
  ASSERT_TRUE(obj.find("info") != obj.end());
  ASSERT_TRUE(std::holds_alternative<JsonObject>(obj.at("info")));

  const auto& inner = std::get<JsonObject>(obj.at("info"));

  // Validate values inside nested object
  ASSERT_TRUE(inner.find("level") != inner.end());
  ASSERT_TRUE(inner.find("score") != inner.end());

  EXPECT_TRUE(std::holds_alternative<int>(inner.at("level")));
  EXPECT_EQ(std::get<int>(inner.at("level")), 5);

  EXPECT_TRUE(std::holds_alternative<double>(inner.at("score")));
  EXPECT_DOUBLE_EQ(std::get<double>(inner.at("score")), 99.9);
}
