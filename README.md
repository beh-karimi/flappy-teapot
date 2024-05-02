# Flappy Teapot
A shameless flappy bird clone using deprecated OpenGL APIs and GLUT.

The camera has 3 position presets: side (default), behind, first person, and can be moved and rotated freely.

You can also switch between perspective and orthographic rendering.

## Controls
<kbd>Space</kbd>: jump.
<kbd>m</kbd> : cycle through camera position presets.
<kbd>c</kbd> : switch between perspective and orthographic rendering.
<kbd>w</kbd> / <kbd>s</kbd> : move the camera forward/backward.
<kbd>a</kbd> / <kbd>d</kbd> : move the camera to left/right.
<kbd>z</kbd> / <kbd>x</kbd> : move the camera down/up.
<kbd>g</kbd> / <kbd>t</kbd> : rotate the camera down/up.
<kbd>f</kbd> / <kbd>h</kbd> : rotate the camera towards left/right.

## Building
To compile on linux, make sure you have freeglut or any other glut library and make.

Simply run `make` to build or `make run` to build and run the program.
