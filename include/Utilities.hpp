
namespace args {
namespace libs {

using std::decay_t;

template <class T>
auto defaultValueOf() -> T {
  return decay_t<T>{};
}

}  // namespace libs
}  // namespace args
