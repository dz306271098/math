#ifndef STAN_MATH_PRIM_SCAL_PROB_UNIFORM_CDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_UNIFORM_CDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/err.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>

namespace stan {
namespace math {

template <typename T_y, typename T_low, typename T_high>
return_type_t<T_y, T_low, T_high> uniform_cdf(const T_y& y, const T_low& alpha,
                                              const T_high& beta) {
  static const char* function = "uniform_cdf";
  using T_partials_return = partials_return_t<T_y, T_low, T_high>;

  if (size_zero(y, alpha, beta)) {
    return 1.0;
  }

  T_partials_return cdf(1.0);
  check_not_nan(function, "Random variable", y);
  check_finite(function, "Lower bound parameter", alpha);
  check_finite(function, "Upper bound parameter", beta);
  check_greater(function, "Upper bound parameter", beta, alpha);
  check_consistent_sizes(function, "Random variable", y,
                         "Lower bound parameter", alpha,
                         "Upper bound parameter", beta);

  scalar_seq_view<T_y> y_vec(y);
  scalar_seq_view<T_low> alpha_vec(alpha);
  scalar_seq_view<T_high> beta_vec(beta);
  size_t N = max_size(y, alpha, beta);

  for (size_t n = 0; n < N; n++) {
    const T_partials_return y_dbl = value_of(y_vec[n]);
    if (y_dbl < value_of(alpha_vec[n]) || y_dbl > value_of(beta_vec[n])) {
      return 0.0;
    }
  }

  operands_and_partials<T_y, T_low, T_high> ops_partials(y, alpha, beta);
  for (size_t n = 0; n < N; n++) {
    const T_partials_return y_dbl = value_of(y_vec[n]);
    const T_partials_return alpha_dbl = value_of(alpha_vec[n]);
    const T_partials_return beta_dbl = value_of(beta_vec[n]);
    const T_partials_return b_min_a = beta_dbl - alpha_dbl;
    const T_partials_return cdf_ = (y_dbl - alpha_dbl) / b_min_a;

    cdf *= cdf_;

    if (!is_constant_all<T_y>::value) {
      ops_partials.edge1_.partials_[n] += 1.0 / b_min_a / cdf_;
    }
    if (!is_constant_all<T_low>::value) {
      ops_partials.edge2_.partials_[n]
          += (y_dbl - beta_dbl) / b_min_a / b_min_a / cdf_;
    }
    if (!is_constant_all<T_high>::value) {
      ops_partials.edge3_.partials_[n] -= 1.0 / b_min_a;
    }
  }

  if (!is_constant_all<T_y>::value) {
    for (size_t n = 0; n < stan::length(y); ++n) {
      ops_partials.edge1_.partials_[n] *= cdf;
    }
  }
  if (!is_constant_all<T_low>::value) {
    for (size_t n = 0; n < stan::length(alpha); ++n) {
      ops_partials.edge2_.partials_[n] *= cdf;
    }
  }
  if (!is_constant_all<T_high>::value) {
    for (size_t n = 0; n < stan::length(beta); ++n) {
      ops_partials.edge3_.partials_[n] *= cdf;
    }
  }

  return ops_partials.build(cdf);
}

}  // namespace math
}  // namespace stan
#endif
