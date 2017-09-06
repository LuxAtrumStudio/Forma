#ifndef FORMA_ENTITY_ENTITY_HPP
#define FORMA_ENTITY_ENTITY_HPP

namespace forma {
  namespace entity {
    class Entity {
     public:
      Entity();
      Entity(const Entity& copy);
      ~Entity();

      void Display();

     private:
    };
  }  // namespace entity
}  // namespace forma

#endif /* ifndef FORMA_ENTITY_ENTITY_HPP */
