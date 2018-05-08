#pragma once

/*
////////////////////////////////////////////////////////////////////////////////////////////
// Object concepts
////////////////////////////////////////////////////////////////////////////////////////////

struct Destructible
{
  template<typename T>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::is_true(std::is_nothrow_destructible<T>())
  ));
};

struct Constructible
  : refines<Destructible(_1)>
{
  template<typename T, typename... Args>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::is_true(std::is_constructible<T, Args...>{})
  ));
};

struct DefaultConstructible
  : refines<Constructible>
{
  template<typename T>
  void requires_();
};

struct MoveConstructible
{
  template<typename T>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::model_of<Constructible, T, T>(),
    concepts::model_of<ConvertibleTo, T, T>()
  ));
};

struct CopyConstructible
  : refines<MoveConstructible>
{
  template<typename T>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::model_of<Constructible, T, T &>(),
    concepts::model_of<Constructible, T, T const &>(),
  concepts::model_of<Constructible, T, T const>(),
    concepts::model_of<ConvertibleTo, T &, T>(),
    concepts::model_of<ConvertibleTo, T const &, T>(),
    concepts::model_of<ConvertibleTo, T const, T>()
  ));
};

struct Movable
  : refines<MoveConstructible>
{
  template<typename T>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::is_true(std::is_object<T>{}),
    concepts::model_of<Assignable, T &, T>(),
    concepts::model_of<Swappable, T &>()
  ));
};

struct Copyable
  : refines<Movable, CopyConstructible>
{
  template<typename T>
  auto requires_() -> decltype(
  concepts::valid_expr(
    // Spec requires this to be validated
    concepts::model_of<Assignable, T &, T const &>(),
    // Spec does not require these to be validated
    concepts::model_of<Assignable, T &, T &>(),
    concepts::model_of<Assignable, T &, T const>()
  ));
};

struct SemiRegular
  : refines<Copyable, DefaultConstructible>
{
  // Axiom: copies are independent. See Fundamentals of Generic Programming
  // http://www.stepanovpapers.com/DeSt98.pdf
};

struct Regular
  : refines<SemiRegular, EqualityComparable>
{};
 */