#pragma once

#include <ph.h>

namespace ph {
namespace vr {

extern ovrHmd  m_hmd;

void init(int width, int height);

void init_with_shaders(int width, int height, const char** shader_paths, int num_shaders);

void draw(int* resolution);

void enable_skybox();

void disable_skybox();

void toggle_postproc();

void toggle_interlace_throttle();

void deinit();

}  // ns vr
}  // ns ph
