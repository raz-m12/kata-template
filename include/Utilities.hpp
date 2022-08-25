
namespace args::libs {

#include <type_traits>

using std::decay_t;

template <class T>
auto defaultValueOf() -> T {
  return decay_t<T>{};
}

}  // namespace args::libs
