#include <metaprog/cpt/cpt.hpp>

#include <string_view>
#include <type_traits>

namespace concepts = cpt::concepts;

template <typename>
struct Image {
};

template <typename>
struct image_traits {
  using accessible = void;
  using category   = void;
  using concrete   = void;
  using indexable  = void;
  using extension  = void;
};

namespace image_concept_traits {
template <typename I>
using accessible = typename image_traits<I>::accessible;
template <typename I>
using category = typename image_traits<I>::category;
template <typename I>
using concrete = typename image_traits<I>::concrete;
template <typename I>
using indexable = typename image_traits<I>::indexable;
template <typename I>
using extension = typename image_traits<I>::extension;

template <typename I>
using value = typename I::value_type;
template <typename I>
using reference = typename I::reference;
template <typename I>
using const_reference = typename I::const_reference;
template <typename I>
using pixel = typename I::pixel_type;
template <typename I>
using const_pixel = typename I::const_pixel_type;


template <typename I>
using site_type = typename I::site_type;
template <typename I>
using point_type = typename I::point_type;
template <typename I>
using domain_type = typename I::domain_type;

template <typename I>
using is_base_of_image = std::is_base_of<Image<I>, I>;

template <typename I>
using domain_matching =
std::is_convertible<std::remove_reference_t<decltype(std::declval<I>().domain())>, domain_type<I>>;

template <typename I>
using pixel_value_type_matching = std::is_convertible<typename pixel<I>::value_type, value<I>>();
template <typename I>
using pixel_reference_matching = std::is_same<typename pixel<I>::reference, reference<I>>();
template <typename I>
using const_pixel_value_type_matching = std::is_convertible<typename const_pixel<I>::value_type, value<I>>();
template <typename I>
using const_pixel_reference_matching = std::is_same<typename const_pixel<I>::reference, const_reference<I>>();
template <typename I>
using pixel_convert_to_const_pixel = std::is_convertible<pixel<I>, const_pixel<I>>();
} // namespace image_concept_traits

int main() {
  return 0;
}
