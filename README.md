## Needle :: A GitHub GameJam 2021 Submission

### Theme is BUG(s?)

### Overview

An adventurous group of friends steal a rocket spaceship and take it
from Earth out into the Cosmos. They crash land somewhere past Jupiter and before Uranus. Upon, landing safetly, they realize their commandeered spaceship engine has stalled, indefintely. Their knowledge of software development kicks in and they open a terminal into the rocket's digital console. They discover that all the code has been scrambled, with a note reading: "Congratultions on discovering this place, you're not the first and surely could be the last, so make it past with some more gas,
and you'll see the source more easily." In ASCII artform, a bee, is attached.

### Building and Playing

Install [CMake](https://cmake.org/download/) and [Git](https://git-scm.com/downloads)

Clone repo using `git clone https://github.com/zmertens/Needle --recurse-submodules`

  - Create build/ directory
  - Change to build/ directory, run `cmake ..` or `cmake CMAKE_BUILD_TYPE=Release ..`
    - By default, CMake build type is "RelWithDebInfo", causing `NEEDLE_DEBUG` mode in application
  - If Makefile is generated, run `make -j4` from build/
  - Copy glfw DLL file and assets/ folder to the build/
    - Run `Needle.exe` to play!

Update submodules using `git submodule init` or `git submodule update --init`
List of Git submodules:
```bash
git submodule add -b master https://github.com/ocornut/imgui.git dear_imgui
git submodule add -b 3.3-stable https://github.com/glfw/glfw.git glfw-3.3-stable
git submodule add -b 0.9.7 https://github.com/g-truc/glm.git glm-0.9.7
git submodule add https://github.com/erincatto/box2d.git
```

