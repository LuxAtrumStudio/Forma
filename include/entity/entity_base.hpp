#ifndef FORMA_ENTITY_ENTITY_BASE_HPP_
#define FORMA_ENTITY_ENTITY_BASE_HPP_

#include <memory>

#include "../shader/shader.hpp"

namespace forma {
  namespace entity {
    class EntityBase{
      public:
      private:

        std::shared_ptr<shader::Shader>shader_;
        std::vector<float> verticies_;
        std::vector<std::size_t> indicies_;

    };
  } // namespace entity
} // namespace forma

#endif  // FORMA_ENTITY_ENTITY_BASE_HPP_
