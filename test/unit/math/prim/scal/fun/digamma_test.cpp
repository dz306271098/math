#include <stan/math/prim/scal.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <gtest/gtest.h>
#include <limits>

TEST(MathFunctions, digamma) {
  EXPECT_FLOAT_EQ(boost::math::digamma(0.5), stan::math::digamma(0.5));
  EXPECT_FLOAT_EQ(boost::math::digamma(-1.5), stan::math::digamma(-1.5));
}

TEST(MathFunctions, digamma_nan) {
  double nan = std::numeric_limits<double>::quiet_NaN();

  EXPECT_PRED1(boost::math::isnan<double>, stan::math::digamma(nan));

  EXPECT_PRED1(boost::math::isnan<double>, stan::math::digamma(-1));

  // see comments in test/unit/math/prim/scal/fun/lgamma_test.cpp
  EXPECT_PRED1(boost::math::isnormal<double>,
               boost::math::digamma(1.0E50, stan::math::boost_policy_t()));
}
