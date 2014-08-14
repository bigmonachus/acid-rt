// 2014 Sergio Gonzalez

#include <ph.h>
#include <scene.h>

using namespace ph;

static GLuint g_program;
static int g_resolution[] = {1920, 1080};  // DK2 res

// Note 2: Workgroup size should be a multiple of workgroup size.
static int g_warpsize[] = {16, 8};

void draw() {
    glUseProgram(g_program);
    vr::draw(g_resolution, g_warpsize);
}

using namespace ph;
int main() {
    ph::init();

    window::init("Cube grid", g_resolution[0], g_resolution[1],
            window::InitFlag(
                window::InitFlag_NoDecoration | window::InitFlag_OverrideKeyCallback));


    io::set_wasd_step(0.03f);

    glfwSetKeyCallback(ph::window::m_window, ph::io::wasd_callback);

    const char* paths[] = {
        "pham/tracing.glsl",
    };

    g_program = cs::init(g_resolution[0], g_resolution[1], paths, 1);

    vr::init(g_program);

    scene::init();

    // Create test grid of cubes
    scene::Cube thing;
    {
        int x = 2;
        int y = 2;
        int z = 2;
        for (int i = 0; i < z; ++i) {
            for (int j = 0; j < y; ++j) {
                for (int k = 0; k < x; ++k) {
                    thing = {{i * 1.1, j * 1.1, -2 - k * 1.1}, {0.5, 0.5, 0.5}, -1};
                    scene::submit_primitive(&thing);
                }
            }
        }
        printf("INFO: Submitted %d polygons.\n", x * y * z * 12);
    }

    scene::update_structure();
    scene::upload_everything();

    init();

    window::main_loop(draw);

    window::deinit();

    vr::deinit();
    return 0;
}
