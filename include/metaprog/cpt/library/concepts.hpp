#pragma once

#ifndef METAPROG_CPT_LIBRARY_CONCEPTS_HPP_
#define METAPROG_CPT_LIBRARY_CONCEPTS_HPP_

/**
 *
 * EqualityComparable : operator== is an equivalence relation
 *
 * LessThanComparable : operator< is a strict weak ordering relation
 *
 * Swappable : can be swapped with an unqualified non-member function call
 * swap()
 *
 * ValueSwappable : an Iterator that dereferences to a Swappable type
 *
 * NullablePointer : a pointer-like type supporting a null value
 *
 * Hash : a FunctionObject that for inputs with different values has a low
 * probability of giving the same output
 *
 * FunctionObject : an object that can be called with the function call syntax Callable : a type for which the invoke
 * operation is defined
 *
 * Predicate : a FunctionObject that returns a value convertible to bool
 * for one argument without modifying it
 *
 * BinaryPredicate : a FunctionObject that returns a value convertible to bool for two arguments without modifying them
 *
 * Compare : a BinaryPredicate that establishes an ordering relation
 *
 */

namespace cpt { namespace concepts { namespace library {


}}} // namespace cpt::concepts::library

#endif // METAPROG_CPT_LIBRARY_CONCEPTS_HPP_
