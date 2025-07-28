#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include <string>
#include "json_parser/json_parser.h"

namespace JsonLoader {
  std::string LoadFromFile(const std::string& filepath);
}

#endif
