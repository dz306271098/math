#ifndef STAN_MATH_PRIM_SCAL_PROB_BERNOULLI_CDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_BERNOULLI_CDF_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/bernoulli_lcdf.hpp>

namespace stan {
namespace math {

/** \ingroup prob_dists
 * @deprecated use <code>bernoulli_lcdf</code>
 */
template <typename T_n, typename T_prob>
return_type_t<T_prob> bernoulli_cdf_log(const T_n& n, const T_prob& theta) {
  return bernoulli_lcdf<T_n, T_prob>(n, theta);
}

}  // namespace math
}  // namespace stan
#endif
