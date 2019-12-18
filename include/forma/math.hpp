#ifndef MATH_HPP_OUV8ONJC
#define MATH_HPP_OUV8ONJC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ALIAS(highLevelF, lowLevelF)                       \
  template <typename... Args>                              \
  inline auto highLevelF(Args&&... args)                   \
      ->decltype(lowLevelF(std::forward<Args>(args)...)) { \
    return lowLevelF(std::forward<Args>(args)...);         \
  }

namespace forma {
  // Types
  typedef glm::vec2 vec2;
  typedef glm::vec3 vec3;
  typedef glm::vec4 vec4;
  typedef glm::uvec2 uvec2;
  typedef glm::uvec3 uvec3;
  typedef glm::uvec4 uvec4;
  typedef glm::mat2 mat2;
  typedef glm::mat3 mat3;
  typedef glm::mat4 mat4;

  // Common Functions
  ALIAS(abs, glm::abs);
  ALIAS(ceil, glm::ceil);
  ALIAS(clamp, glm::clamp);
  ALIAS(floor, glm::floor);
  ALIAS(fma, glm::fma);
  ALIAS(fract, glm::fract);
  ALIAS(frexp, glm::frexp);
  ALIAS(isinf, glm::isinf);
  ALIAS(isnan, glm::isnan);
  ALIAS(ldexp, glm::ldexp);
  ALIAS(max, glm::max);
  ALIAS(min, glm::min);
  ALIAS(mix, glm::mix);
  ALIAS(mod, glm::mod);
  ALIAS(modf, glm::modf);
  ALIAS(round, glm::round);
  ALIAS(round_even, glm::roundEven);
  ALIAS(sign, glm::sign);
  ALIAS(smoothstep, glm::smoothstep);
  ALIAS(step, glm::step);
  ALIAS(trunc, glm::trunc);

  // Exponential Functions
  ALIAS(exp, glm::exp);
  ALIAS(exp2, glm::exp2);
  ALIAS(invertsqrt, glm::inversesqrt);
  ALIAS(log, glm::log);
  ALIAS(log2, glm::log2);
  ALIAS(pow, glm::pow);
  ALIAS(sqrt, glm::sqrt);

  // Geometric Functions
  ALIAS(cross, glm::cross);
  ALIAS(distance, glm::distance);
  ALIAS(dot, glm::dot);
  ALIAS(faceforward, glm::faceforward);
  ALIAS(length, glm::length);
  ALIAS(normalize, glm::normalize);
  ALIAS(reflect, glm::reflect);
  ALIAS(refract, glm::refract);

  // Matrix Functions
  ALIAS(determinant, glm::determinant);
  ALIAS(inverse, glm::inverse);
  ALIAS(matrix_comp_mult, glm::matrixCompMult);
  ALIAS(outer_product, glm::outerProduct);
  ALIAS(transpose, glm::transpose);

  // type_ptr
  ALIAS(make_vec2, glm::make_vec2);
  ALIAS(make_vec3, glm::make_vec3);
  ALIAS(make_vec4, glm::make_vec4);
  ALIAS(make_mat2, glm::make_mat2);
  ALIAS(make_mat3, glm::make_mat3);
  ALIAS(make_mat4, glm::make_mat4);
  ALIAS(value_ptr, glm::value_ptr);

  // random
  ALIAS(ball_rand, glm::ballRand);
  ALIAS(circular_rand, glm::circularRand);
  ALIAS(disk_rand, glm::diskRand);
  ALIAS(gauss_rand, glm::gaussRand);
  ALIAS(linear_rand, glm::linearRand);
  ALIAS(spherical_rand, glm::sphericalRand);

  // matrix_transform
  ALIAS(frustum, glm::frustum);
  ALIAS(infinite_perspective, glm::infinitePerspective);
  ALIAS(look_at, glm::lookAt);
  ALIAS(ortho, glm::ortho);
  ALIAS(perspective, glm::perspective);
  ALIAS(perspective_fov, glm::perspectiveFov);
  ALIAS(pick_matrix, glm::pickMatrix);
  ALIAS(project, glm::project);
  ALIAS(rotate, glm::rotate);
  ALIAS(scale, glm::scale);
  ALIAS(translate, glm::translate);
  ALIAS(tweaked_infinite_perspective, glm::tweakedInfinitePerspective);
  ALIAS(unproject, glm::unProject);

  // noise
  ALIAS(perlin, glm::perlin);
  ALIAS(simplex, glm::simplex);
}  // namespace forma

#endif /* end of include guard: MATH_HPP_OUV8ONJC */
