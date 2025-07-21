#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <map>
#include <utility> // for std::pair
#include <variant> // for std::variant

namespace JsonParser {
  using text_it = std::string::iterator;

  // Old type unsafe method of handling JSON Values
  /* 
  union JsonValue {
     int i;
     double d;
     std::map<std::string, JsonValue>* json;
   };
  */
 
  /*
  Note: Using std::variant instead of union for type safety and better handling
  of different types in C++17. This allows us to avoid manual memory management
  */

  struct JsonValue; // forward declaration
  using JsonObject = std::map<std::string, JsonValue>;
  struct JsonValue : public std::variant<int, double, JsonObject> {
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