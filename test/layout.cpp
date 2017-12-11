#include <concepts/concepts.hpp>

#include <gtest/gtest.h>

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

TEST(Layout, trivially_copyable)
{
  ASSERT_TRUE(concepts::trivially_copyable<trivial_full>);
  ASSERT_TRUE(concepts::trivially_copyable<trivial_on_copy_constructor>);
  ASSERT_TRUE(concepts::trivially_copyable<trivial_on_move_constructor>);
  ASSERT_TRUE(concepts::trivially_copyable<trivial_on_copy_assignement>);
  ASSERT_TRUE(concepts::trivially_copyable<trivial_on_move_assignement>);

  ASSERT_FALSE(traits::is_trivially_copyable_v<non_trivial_virtual_destructor>);
}

struct non_trivial {
  non_trivial()
  {
  }
};

TEST(Layout, trivial)
{
  ASSERT_TRUE(concepts::trivial<trivial_full>);
  ASSERT_TRUE(concepts::trivial<trivial_on_copy_constructor>);
  ASSERT_TRUE(concepts::trivial<trivial_on_move_constructor>);
  ASSERT_TRUE(concepts::trivial<trivial_on_copy_assignement>);
  ASSERT_TRUE(concepts::trivial<trivial_on_move_assignement>);

  ASSERT_FALSE(traits::is_trivial_v<non_trivial_virtual_destructor>);
  ASSERT_FALSE(traits::is_trivial_v<non_trivial>);
}

struct standard_layout {
  void* v_;
};

struct non_standard_layout_ref {
  int& v_;
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
public:
  int j_;

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

TEST(Layout, standard_layout)
{
  ASSERT_TRUE(concepts::standard_layout<standard_layout>);
  ASSERT_TRUE(concepts::standard_layout<standard_layout_bis>);
  ASSERT_TRUE(concepts::standard_layout<standard_layout_private>);
  ASSERT_TRUE(concepts::standard_layout<standard_layout_protected>);

  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_ref>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_virtual>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_private>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_protected>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_inherited>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_diamond_inheritance>);
  ASSERT_FALSE(traits::is_standard_layout_v<non_standard_layout_composition>);
}
