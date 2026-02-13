# Particle System in C

A real-time interactive particle simulation built in C using raylib.
Features four unique emitter types with realistic physics and 
optimised memory management through object pooling.

## Features
- **Object Pooling** - Pre-allocated particle pool for fast, 
  efficient memory management
- **Four Emitter Types** - Explosion, Fountain, Smoke and Sparks
- **Realistic Physics** - Gravity, velocity, and friction per particle
- **Visual Effects** - Particles fade and shrink as they die
- **Interactive** - Mouse-driven particle spawning

## Requirements
- MSYS2 with MinGW64
- raylib installed via pacman:
```bash
pacman -S mingw-w64-x86_64-raylib
```
- Copy `libraylib.dll` and `glfw3.dll` from `C:/msys64/mingw64/bin` 
  to project folder

## How to Build
1. Open MINGW64 terminal
2. Navigate to project folder
3. Run:
```bash
./build.sh
```

## Controls
| Key | Emitter |
|-----|---------|
| Left Click | Explosion |
| E | Sparks |
| S | Smoke |
| F | Fountain |

## Technical Details

### Object Pooling
Instead of calling `malloc()` and `free()` for every particle 
(which is slow and causes memory fragmentation), we pre-allocate 
a fixed pool of 5000 particles at startup.

Each particle has an `active` flag:
- `active = true` → particle is alive and updating
- `active = false` → particle is back in the pool, ready for reuse

When a particle's `life` reaches 0, it's simply marked inactive - 
no memory is freed. When a new particle is needed, we find the 
first inactive slot and reuse it. Zero malloc, zero free, 
thousands of particles at 60 FPS.

### Particle Lifecycle
Each particle has a `life` value starting at 1.0, decreasing 
every frame. This single value drives both the visual fading 
(`Fade(color, life)`) and shrinking (`radius * life`), 
creating a natural death animation.

### Physics
Each particle has its own `gravity` value, allowing different 
emitter types to feel unique - smoke barely falls while sparks 
drop quickly.