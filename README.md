# emui - embedded ui

`emui` is a library for creating fast and responsive user interfaces for embedded systems.
It is designed with low-end microcontrollers in mind, and can function in places where
higher-level UI toolkits cannot.

`emui` is renderer-agnostic, it simply outputs to a user-provided frame buffer. This means
it can be run bare-metal (try writing to `/dev/fb0`!). In addition to not depending on a 
specific rendering API, `emui` also does not depend on:

- A filesystem
- Dynamic memory
- A keyboard or mouse for input
	- Buttons can be configured for navigation, with optional pointer support
- Any external libraries
- `libc` (except in debug mode for printing)
