#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"
#include "memory"
#include "include/ISchema.hpp"

namespace args {
namespace libs {
using std::string;
using std::shared_ptr;

class ArgumentParser {
 public:
  explicit ArgumentParser(shared_ptr<ISchema> schema);
  virtual ~ArgumentParser() = default;

  ArgumentParser(ArgumentParser const &) = delete;
  ArgumentParser(ArgumentParser &&) = delete;
  auto operator=(ArgumentParser const &) -> ArgumentParser & = delete;
  auto operator=(ArgumentParser &&) -> ArgumentParser & = delete;

  static auto getParserGivenSchema(const string& input) -> ArgumentParser;
  auto getSchema() -> shared_ptr<ISchema>;

  auto getBooleanValue(const string& arg) -> bool;
  virtual auto setBooleanValue(const string& arg) -> void;

 private:
  shared_ptr<ISchema> _schema;
};
}  // namespace libs
}  // namespace args

#endif
