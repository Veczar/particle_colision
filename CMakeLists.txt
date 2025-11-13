project(particle_collision C)
set(CMAKE_C_STANDARD 11)

# === OpenMP Support ===
find_package(OpenMP REQUIRED)

add_executable(particle_collision src/main.c src/physics.c src/draw.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 and OpenMP
target_link_libraries(particle_collision ${SDL2_LIBRARIES} OpenMP::OpenMP_C -lm)