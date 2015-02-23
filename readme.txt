== A simple Matrix text rain effect demo for the c64 computer ==

The main reason to start this project was desire to learn some C-language and the cc65 development tools and of course to have fun with the legendary 8 bit hardware.

Authors: 
  - Matti Kuonanoja

Project:
  - written with C-language using cc65 compiler
  - effect properties can be set in a header file
  - a python script for creating background images

Features:
  - streams flows from top to bottom
  - streams writes random characters to screen
  - streams have random speeds
  - streams have random lengths
  - streams have random columns
  - streams tries to find an empty column when restarted
  - streams uses 4 colours each to simulate fade effect
  - background image is revealed column by column, after a stream have run over it
  - background image pixel colours are changed by random every time a stream runs over it
  - FPS counter can be enabled and disabled by pressing space bar

Build dependencies:
  - cc65 build environment
  - python module: PIL, if you want to generate a different background image

Build instructions (Windows):
  - build.cmd
  - the executable file (demo.prg) is created in build\ directory

Run instructions (c64):
  - load "demo.prg",8,1
  - run

Changing the background image:
  - create 40x25 pixels image using black (#000000) as the background colour
  - run: tools\background.py <image_file> <output_text_file>
  - use the code in the generated text file in the src\backgroundimage.c file
