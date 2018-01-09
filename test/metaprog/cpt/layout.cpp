#include <metaprog/cpt/cpt.hpp>

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

struct trivial_full {
  trivial_full()                    = default;
  trivial_full(const trivial_full&) = default;
  trivial_full(trivial_full&&)      = default;
  trivial_full& operator=(const trivial_full&) = default;
  trivial_full& operator=(trivial_full&&) = default;
};

struct non_trivial_virtual_destructor {
  virtual ~non_trivial_virtual_destructor(){};
};

struct trivial_on_copy_constructor {
  trivial_on_copy_constructor()                                   = default;
  trivial_on_copy_constructor(const trivial_on_copy_constructor&) = default;
  trivial_on_copy_constructor(trivial_on_copy_constructor&&)      = delete;
  trivial_on_copy_constructor& operator=(const trivial_on_copy_constructor&) = delete;
  trivial_on_copy_constructor& operator=(trivial_on_copy_constructor&&) = delete;
};

struct trivial_on_move_constructor {
  trivial_on_move_constructor()                                   = default;
  trivial_on_move_constructor(const trivial_on_move_constructor&) = delete;
  trivial_on_move_constructor(trivial_on_move_constructor&&)      = default;
  trivial_on_move_constructor& operator=(const trivial_on_move_constructor&) = delete;
  trivial_on_move_constructor& operator=(trivial_on_move_constructor&&) = delete;
};

struct trivial_on_copy_assignement {
  trivial_on_copy_assignement()                                   = default;
  trivial_on_copy_assignement(const trivial_on_copy_assignement&) = delete;
  trivial_on_copy_assignement(trivial_on_copy_assignement&&)      = delete;
  trivial_on_copy_assignement& operator=(const trivial_on_copy_assignement&) = default;
  trivial_on_copy_assignement& operator=(trivial_on_copy_assignement&&) = delete;
};

struct trivial_on_move_assignement {
  trivial_on_move_assignement()                                   = default;
  trivial_on_move_assignement(const trivial_on_move_assignement&) = delete;
  trivial_on_move_assignement(trivial_on_move_assignement&&)      = delete;
  trivial_on_move_assignement& operator=(const trivial_on_move_assignement&) = delete;
  trivial_on_move_assignement& operator=(trivial_on_move_assignement&&) = default;
};

TEST(Cpt_Layout, trivially_copyable)
{
  ASSERT_TRUE((cpt::check<trivial_full>(concepts::trivially_copyable)));
#ifndef _MSC_VER
  ASSERT_TRUE((cpt::check<trivial_on_copy_constructor>(concepts::trivially_copyable)));
  ASSERT_TRUE((cpt::check<trivial_on_move_constructor>(concepts::trivially_copyable)));
  ASSERT_TRUE((cpt::check<trivial_on_copy_assignement>(concepts::trivially_copyable)));
  ASSERT_TRUE((cpt::check<trivial_on_move_assignement>(concepts::trivially_copyable)));
#endif
  ASSERT_FALSE((cpt::check<non_trivial_virtual_destructor>(concepts::trivially_copyable)));
}

struct non_trivial {
  non_trivial()
  {
  }
};

TEST(Cpt_Layout, trivial)
{
  ASSERT_TRUE((cpt::check<trivial_full>(concepts::trivial)));
#ifndef _MSC_VER
  ASSERT_TRUE((cpt::check<trivial_on_copy_constructor>(concepts::trivial)));
  ASSERT_TRUE((cpt::check<trivial_on_move_constructor>(concepts::trivial)));
  ASSERT_TRUE((cpt::check<trivial_on_copy_assignement>(concepts::trivial)));
  ASSERT_TRUE((cpt::check<trivial_on_move_assignement>(concepts::trivial)));
#endif
  ASSERT_FALSE((cpt::check<non_trivial_virtual_destructor>(concepts::trivial)));
  ASSERT_FALSE((cpt::check<non_trivial>(concepts::trivial)));
}

struct standard_layout {
  void* v;
};

struct non_standard_layout_ref {
  int& v;
};

struct non_standard_layout_virtual {
  virtual void foo()
  {
  }
};

struct standard_layout_private {
private:
  int i_;
};

struct non_standard_layout_private {
  int j;

private:
  int i_;
};

struct standard_layout_protected {
protected:
  double d_;
};

struct non_standard_layout_protected {
private:
  double f_;

protected:
  double d_;
};

struct non_standard_layout_inherited : non_standard_layout_private {
};

struct standard_layout_bis : standard_layout {
};

struct standard_layout_ter : standard_layout {
};

struct non_standard_layout_diamond_inheritance
  : standard_layout_bis
  , standard_layout_ter {
};

struct non_standard_layout_composition {
  non_standard_layout_diamond_inheritance component_;
};

TEST(Cpt_Layout, standard_layout)
{
  ASSERT_TRUE((cpt::check<standard_layout>(concepts::standard_layout)));
  ASSERT_TRUE((cpt::check<standard_layout_bis>(concepts::standard_layout)));
  ASSERT_TRUE((cpt::check<standard_layout_private>(concepts::standard_layout)));
  ASSERT_TRUE((cpt::check<standard_layout_protected>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_ref>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_virtual>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_private>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_protected>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_inherited>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_diamond_inheritance>(concepts::standard_layout)));
  ASSERT_FALSE((cpt::check<non_standard_layout_composition>(concepts::standard_layout)));
}
