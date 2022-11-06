## Purpose
Some times we need to check if a class has specific member type.
## Definition
```cpp
struct nonesuch
{
nonesuch() = delete;
~nonesuch() = delete;
nonesuch(nonesuch const&) = delete;
nonesuch(nonesuch const&&) = delete;
void operator=(nonesuch const&) = delete;
void operator=(nonesuch&&) = delete;
};

/* default template */
template<class Default,
class AlwaysVoid,
template<class...> class Op,
class... Args>
struct detector
{
using value_t = std::false_type;
using type = Default;
};

/* partial specialization */
template<class Default, template<class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...>
{
using value_t = std::true_type;
using type = Op<Args...>;
};

template<template<class...> class Op, class... Args>
using is_detected = typename detector<nonesuch, void, Op, Args...>::value_t;
```
## Usage
```cpp
/* checking if type T has typename value_type */
template<typename T>
using value_type_t = typename T::value_type;

std::cout << std::boolalpha << is_detected<value_type_t, std::vector<int>>();
```

`is_detected` is trying to match the partial template specialization first. In this case, the parameter `void_t<Op<Args>>` will be deduced to be `void_t<std::string::value_type>`, which is legal because `std::string` has typename `value_type`.

If there deduction fails, `is_detected` will match the primitive one, which we got `value_t = std::false_type` and `type = nonesuch`.