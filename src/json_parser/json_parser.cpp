#include <algorithm> // for std::find
#include <fstream> // for std::ifstream
#include <cassert> // for assert()
#include <cctype> // for isdigit()

#include "json_parser/json_parser.h"
#include "json_loader/json_loader.h"

using namespace JsonParser;

JsonValue JsonParser::ParseJson(const std::string& filepath) {
  std::string text = JsonLoader::LoadFromFile(filepath);
  text_it it = text.begin();
  return ParseJsonHelper(text, it);
}

JsonValue JsonParser::ParsePrimitive(const std::string& text, text_it start, text_it end) {
  std::string substr = text.substr(start - text.begin(), end - start);

  // String
  if (*start == '"' && *(end - 1) == '"') {
    std::string result;
    for (text_it it = start + 1; it < end - 1; ++it) {
      if (*it == '\\') {
        ++it;
        if (it == end - 1) break;
        switch (*it) {
          case 'n': result += '\n'; break;
          case 't': result += '\t'; break;
          case 'r': result += '\r'; break;
          case '\\': result += '\\'; break;
          case '"': result += '"'; break;
          default: result += *it; break;
        }
      } else {
        result += *it;
      }
    }
    return JsonValue(result);
  }

  // Boolean or null
  if (substr == "true") return JsonValue(true);
  if (substr == "false") return JsonValue(false);
  if (substr == "null") return JsonValue(nullptr);

  // Number
  size_t float_point_index = substr.find(".");
  if (float_point_index == std::string::npos) {
    return JsonValue(std::stoi(substr));
  } else {
    return JsonValue(std::stod(substr));
  }
}

JsonValue ParseArray(const std::string& text, text_it& it) {
  assert(*it == '[');
  ++it; // skip '['

  JsonArray array;

  while (*it != ']') {
    // Skip whitespace
    while (*it == ' ' || *it == '\n') ++it;

    // Parse the next value
    if (*it == '{') {
      array.push_back(ParseJsonHelper(text, it));
    } else if (*it == '[') {
      array.push_back(ParseArray(text, it));
    } else if (*it == '"') {
      text_it start = ++it;
      while (*it != '"') ++it;
      std::string str = text.substr(start - text.begin(), it - start);
      ++it;
      array.push_back(str);
    } else {
      text_it start = it;
      while (*it != ',' && *it != ']' && *it != '\n' && *it != ' ') ++it;
      array.push_back(ParsePrimitive(text, start, it));
    }

    // Skip whitespace and comma
    while (*it == ' ' || *it == '\n') ++it;
    if (*it == ',') ++it;
  }

  ++it; // skip ']'
  return JsonValue(array);
}

std::pair<std::string, JsonValue> JsonParser::RetriveKeyValuePair(
  const std::string& text,
  text_it& it
) {
  assert(it != text.end());

  // Ignore white spaces & line breaks
  while (*it == ' ' || *it == '\n') {
    ++it;
  }

  text_it curr_it;
  std::string key;
  JsonValue value;

  // Parse the key (string between quotes)
  if (*it == '\"') {
    curr_it = ++it;
    while (*it != '\"') {
      ++it;
    }

    key = text.substr(curr_it - text.begin(), it - curr_it);
    assert(*(++it) == ':'); // move past closing quote and expect a colon
    ++it; // move past ':'
  }

  // Skip whitespace before the value
  while (*it == ' ' || *it == '\n') {
    ++it;
  }

  // Parse the value
  if (*it == '{') {
    value = ParseJsonHelper(text, it); // Object
  } else if (*it == '[') {
    value = ParseArray(text, it);
  } else if (*it == '"') {
    // String literal
    curr_it = it;
    ++it;
    while (*it != '"' || *(it - 1) == '\\') {
      ++it;
    }
    ++it;
    value = ParsePrimitive(text, curr_it, it);
  } else {
    // Primitive (number, boolean, null)
    curr_it = it;
    while (std::isalnum(*it) || *it == '.' || *it == '-') {
      ++it;
    }
    value = ParsePrimitive(text, curr_it, it);
  }

  // Skip optional trailing comma
  if (*it == ',') {
    ++it;
  }

  return std::make_pair(key, value);
}


JsonValue JsonParser::ParseJsonHelper(const std::string& text, text_it& it) {
  assert(*it == '{'); // must start with the left curly bracket
  it++;

  JsonObject json_map;

  do {
    const auto [key, value] = RetriveKeyValuePair(text, it);
    json_map[key] = value;

    while (*it == ' ' || *it == '\n') {
      it++;
    }
  } while (*it != '}');

  it++; // after '}'

  return JsonValue(json_map);
}