# Squiggle

## Introduction

Squiggle is vector, matrix and quaternion library. It is heavily inspired by the awesome [boost library qvm](https://github.com/boostorg/qvm).

Like boost qvm this library allows compatibility with user types via non-intrusive trait specification. This is very useful if you are working with several other libraries each with their own vector type for more see the [concepts](./concepts.md) page.

The primary motivation for this additional library was to create a modern vector, matrix and quaternion library which makes use of concepts for faster build times and reduced code complexity.

This library is aimed around game-developement and general mathematics. As such only 2,3,4 dimension vectors and square matricies are implemented, along with quaternions.

## Other Libraries

- [boost qvm](https://github.com/boostorg/qvm)
- [GLM](https://github.com/icaven/glm)
- [Eigen](https://github.com/PX4/eigen/tree/3.4) for heavier linear algebra requirements
