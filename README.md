<div align="center">

# JParse

A fast, minimal, and beginner-friendly C++ JSON parser with file support and unit testing.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](#)
[![C++ Standard](https://img.shields.io/badge/C++-17-blue.svg)](#)

</div>

---

## Why JParse?

Tired of bloated or hard-to-understand C++ JSON libraries?
**JParse** was built with simplicity in mind — readable code, full control, and just enough power to get the job done.
Parse JSON from strings or files, and run clean unit tests with GoogleTest.

---

## Features

* 📜 Supports parsing of:

  * Objects `{ }`
  * Arrays `[ ]`
  * Strings `"text"`
  * Numbers (`int`, `double`)
  * Booleans (`true`, `false`)
  * `null`
* 📁 Load from files
* 🧪 Unit tests with GoogleTest
* 📦 Modular structure (parser vs loader)
* 🛠️ Written in modern C++17

---

## Installation

Clone the repo and build it using CMake:

```sh
git clone https://github.com/MrBubune/json-parser.git
cd json-parser
mkdir build && cd build
cmake ..
cmake --build .
```

To run tests:

```sh
ctest
```

Or on Windows:

```sh
.\build.bat
```

---

## Usage

### From Code (String Parsing)

```cpp
#include "json_parser/json_parser.h"

int main() {
    std::string json = R"({ "name": "Daryl", "age": 21 })";
    auto it = json.begin();
    JsonParser::JsonValue root = JsonParser::ParseJsonHelper(json, it);
}
```

### From File

```cpp
#include "json_parser/json_parser.h"

int main() {
    JsonParser::JsonValue root = JsonParser::ParseJson("tests/data/nested_object.json");
}
```

---

## Project Structure

```
json-parser/
├── include/
│   ├── json_parser/
│   │   └── json_parser.h
│   └── json_loader/
│       └── json_loader.h
├── src/
│   ├── json_parser/
│   │   └── json_parser.cpp
│   └── json_loader/
│       └── json_loader.cpp
├── tests/
│   ├── unit/
│   │   ├── test_parse_primitives.cpp
│   │   ├── test_parse_objects.cpp
│   │   └── test_key_value_parsing.cpp
│   ├── data/
│   │   ├── numbers.json
│   │   ├── nested_object.json
│   │   └── malformed.json
│   └── test_main.cpp
├── CMakeLists.txt
├── LICENSE
├── README.md
└── .gitignore
```

---

## Example Test

```cpp
TEST(ParsePrimitiveTest, ParsesInteger) {
    std::string text = "{ \"num\": 10 }";
    auto it = text.begin();
    JsonParser::JsonValue val = JsonParser::ParseJsonHelper(text, it);
    const auto& obj = std::get<JsonParser::JsonObject>(val);
    EXPECT_EQ(std::get<int>(obj.at("num")), 10);
}
```

---

## Contributing

1. Fork this repo
2. Create your feature branch: `git checkout -b feature/new-feature`
3. Commit your changes: `git commit -am 'Add something'`
4. Push to the branch: `git push origin feature/new-feature`
5. Create a new Pull Request

---

## License

Distributed under the MIT License.
See `LICENSE` for more information.
