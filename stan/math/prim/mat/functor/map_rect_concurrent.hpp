#ifndef STAN_MATH_PRIM_MAT_FUNCTOR_MAP_RECT_CONCURRENT_HPP
#define STAN_MATH_PRIM_MAT_FUNCTOR_MAP_RECT_CONCURRENT_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/mat/fun/typedefs.hpp>

#include <vector>

namespace stan {
namespace math {
namespace internal {

template <int call_id, typename F, typename T_shared_param,
          typename T_job_param>
Eigen::Matrix<return_type_t<T_shared_param, T_job_param>, Eigen::Dynamic, 1>
map_rect_concurrent(
    const Eigen::Matrix<T_shared_param, Eigen::Dynamic, 1>& shared_params,
    const std::vector<Eigen::Matrix<T_job_param, Eigen::Dynamic, 1>>&
        job_params,
    const std::vector<std::vector<double>>& x_r,
    const std::vector<std::vector<int>>& x_i, std::ostream* msgs = nullptr);

}  // namespace internal
}  // namespace math
}  // namespace stan

#endif
