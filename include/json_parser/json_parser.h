#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <map> // for std::map
#include <utility> // for std::pair
#include <variant> // for std::variant
#include <vector> // for std::vector

namespace JsonParser {
  using text_it = std::string::iterator;

  struct JsonValue; // forward declaration
  using JsonObject = std::map<std::string, JsonValue>;
  using JsonArray = std::vector<JsonValue>;

  struct JsonValue : public std::variant<int, double, std::string, bool, std::nullptr_t, JsonObject, JsonArray> {
    using variant::variant; // inherit constructors
  };

  void ReadFile(const std::string& filepath, std::string& output);

  JsonValue ParsePrimitive(const std::string& text, text_it start, text_it end);

  std::pair<std::string, JsonValue> RetriveKeyValuePair(
    const std::string& text,
    text_it& it
  );

  JsonValue ParseJsonHelper(const std::string& text, text_it& it);

  JsonValue ParseJson(const std::string& filepath);
}

#endif