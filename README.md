# osciGL
osciGL is a small wrapper utility that shall help visualizing and analyzing sampled data in realtime. Using Nvidias Cuda technology together with OpenGL to process data input streams shall never be more simple than with osciGl. Therefore predefined interfaces help easily adding new applications to the osciGL runtime. 

## Vision and Idea
Imagine you get a new device that just tells you raw data. With normal circumstances you'd first just catch a sample of the data, and write a small Matlab or Python script to get known to formats, required transformations or further different imaging alorithms. Now imagine you'd have a realitime environment for getting known to unknown data. You open your IDE, tell some class your first idea of how your input looks alike and your machine just starts drawing. 

With osciGL this problem shall become simple and convenient to solve. osciGL makes direct use of the GPU to analyze any available input stream in reliant and performant prototypic applications.

Nowadays this means that increddible amounts of samples can be added, moved, transformed, etc. within the split of a second. You don't even need the newest GPUs for it. Even if you want to deal with either big amounts of data or high resolution data.

[comment]: <> (add calculation about memory consumption here)

The facing principle of osciGL beside the heavy use of GPU is memory management. Therefore written partly in C but mostly in C++ osciGL tries to tie down memory duplication to its lowest level. 

osciGL shall make applied science more simple by taking infrastuctural and technical issues away from the user. When finished, maybe there can also be a binding for Python, Rust or Go available.

## Current State
osciGL is still in its most early development stages. 

To be able to reach a wide amount of users osciGL is tried to be implemented as optional and modular as possible. A simple API together with small cut interfaces and highly extendible abstract classes shall provide an readable and conclusive environment for digital data processing. 

## Currently in Work

### Improved Zooming & Scales and Metrics
- get familiar with the non existing camera concept
see: https://learnopengl.com/Getting-started/Camera

### Evaluate Window Toolkits
- done! GLFW it is!

## Features In Development

- Data Processing Pipe
    - Fast Fourier Transformation
    - Realtime Operation Interpreter
- Rendering Choices
    - Imaging Support
        - Camera as Example Input Source
        - Image Renderer  
    - 2nd View (almost done not yet tested)
- Context Menu support
    - Switching between Pipes