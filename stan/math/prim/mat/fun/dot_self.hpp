#ifndef STAN_MATH_PRIM_MAT_FUN_DOT_SELF_HPP
#define STAN_MATH_PRIM_MAT_FUN_DOT_SELF_HPP

#include <stan/math/prim/err.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>

namespace stan {
namespace math {

/**
 * Returns the dot product of the specified vector with itself.
 *
 * @tparam R number of rows, can be Eigen::Dynamic
 * @tparam C number of columns, can be Eigen::Dynamic
 * @param v Vector.
 * @throw std::domain_error If v is not vector dimensioned.
 */
template <int R, int C>
inline double dot_self(const Eigen::Matrix<double, R, C>& v) {
  check_vector("dot_self", "v", v);
  return v.squaredNorm();
}

}  // namespace math
}  // namespace stan

#endif
