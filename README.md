# fract'ol

A 42 School project for rendering beautiful fractals using the MiniLibX graphics library.

## Description

**fract'ol** is a computer graphics project that explores complex numbers, computer graphics optimization, event handling. The term fractal, coined by mathematician Benoit Mandelbrot in 1974, comes from the Latin word *fractus* meaning "broken" or "fractured". A fractal is an abstract mathematical object the internal consistencies of which are observeable at every scale.

This program renders fractals in real-time, allowing interactive exploration through zooming and navigation.

## Installation

### Prerequisites

- GCC compiler
- MiniLibX graphics library
- X11

### Basic Syntax

```bash
./fractol <fractal_type> [parameters]
```

### Examples

```bash
# Display Mandelbrot set
./fractol mandelbrot

# Display Julia set with default parameters
./fractol julia

# Display Julia set with custom parameters
./fractol julia -0.7 0.27015

# Display help/usage information
./fractol
```

### Controls

| Key/Action | Function |
|------------|----------|
| **Mouse Wheel Up** | Zoom in |
| **Mouse Wheel Down** | Zoom out |
| **Arrow Keys** | Move view (bonus) |
| **ESC** | Exit program |
| **Window Close (X)** | Exit program |

## Fractal Types

### Mandelbrot Set

The Mandelbrot set is defined by the iterative formula:

```
z(n+1) = z(n)^2 + c
```

where `z` starts at 0 and `c` is the complex number representing each pixel.

### Julia Set

The Julia set uses the same formula but with a fixed `c` value and varying starting points:

```
z(n+1) = z(n)^2 + c
```

Different `c` values produce dramatically different Julia sets.


## Resources

- [Complex Numbers - MathIsFun](https://www.mathsisfun.com/algebra/complex-number-multiply.html)
- ["The Mandelbrot Set - Numberphile" - youtube](https://www.youtube.com/watch?v=NGMRB4O922I&list=PLt5AfwLFPxWJ8GCgpFo5_OSyfl7j0nOiu)
- [The Mandelbrot Set - povusers.org](http://warp.povusers.org/Mandelbrot/)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [The Mandelbrot Set - complex-analysis.com](https://complex-analysis.com/content/mandelbrot_set.html)
