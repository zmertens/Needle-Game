## Needle :: A GitHub GameJam 2021 Submission
Game jam theme is "BUG"

### Overview

An adventurous group of friends steal a rocket spaceship and take it
from Earth out into the Cosmos. They crash land somewhere past Jupiter and before Uranus. Upon, landing safetly, they realize their commandeered spaceship engine has stalled, indefintely. Their knowledge of software development kicks in and they open a terminal into the rocket's digital console. They discover that all the code has been scrambled, with a note reading: "Congratultions on discovering this place, you're not the first and surely could be the last, so make it past with some more gas,
and you'll see the source more easily." In ASCII artform, a bee, is attached.

### Playing

 - Command Line Arguments: `--message=MESSAGE_HERE, --no-sound, --fly`

Use VIM-like keyboard commands to delete *bugs* and gain power-ups. Enjoy the sci-fi-like setting. Play with the console for information about the game and the like of keyboard commands.

 - ESCAPE change modes
 - h move cursor left
 - j move cursor down
 - k move cursor up
 - l move cursor right
 - del delete text
 - v highlight text
 - d delete highlighted text
 - c copy highlighted text
 - p paste highlighted text

### Building

Install [CMake](https://cmake.org/download/) and [Git](https://git-scm.com/downloads), and a C++14 compiler

Clone repo using `git clone https://github.com/zmertens/Needle --recurse-submodules`

  1. Create build/ directory
  2. Change to build/ directory, run `cmake ..` or `cmake CMAKE_BUILD_TYPE=Release ..`
    - By default, CMake build type is "RelWithDebInfo", activating `NEEDLE_DEBUG` mode in application
  3. If Makefile is generated, run `make -j4` from build/
  4. Copy glfw and zep DLL filef, and assets/ folder, to the build/
  5. Run `Needle.exe` to play!

Update submodules using `git submodule init` or `git submodule update --init`
```bash
git submodule add -b master https://github.com/ocornut/imgui.git dear_imgui
git submodule add -b 3.3-stable https://github.com/glfw/glfw.git glfw-3.3-stable
git submodule add -b 0.9.7 https://github.com/g-truc/glm.git glm-0.9.7
git submodule add https://github.com/erincatto/box2d.git
git submodule add https://github.com/RameshAditya/asciify.git
git submodule add https://github.com/reedacartwright/dawg.git
```

