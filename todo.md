# FRAMEWORK

- Graphics
  - Window Creation
  - Texture Rendering
  - Text Rendering
  - Texture Manipulation
- Audio

# WORLD

- World creation
- Entity Manager
- Component Manager
- System Manager
- Message Bus

# ENTITY

- Entity Creation
- Entity Component Addition
- Entity Handler
- DATA ONLY

# COMPONENT

- Default component
- Easily extendable components
- Component Handler
- Allow component to be a listener for event types.
- PRIMARILY DATA, CAN HAVE FUNCTIONS?

# SYSTEMS

- Easily extendible systems
- Each system is called every frame/update
- SYSTEMS ARE FUNCTIONS ONLY
- Systems cannot be a listener to events, as they are already called every game
  update.

# EVENT SYSTEM

- General event/message class
- Create a function to disspatch a new message
- Create a function to poll for messages of a given type
- Create a function to clear messages at the end of a display from
- Create a list of listener components, which will be called when an even
  occurs.
