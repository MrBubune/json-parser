#include "json_loader/json_loader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string JsonLoader::LoadFromFile(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filepath);
  }

  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
