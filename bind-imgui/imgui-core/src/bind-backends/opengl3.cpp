#include <imgui-core/inc/imgui-modules.h>

#include <backends/imgui_impl_opengl3.h>

// TODO not compiled atm

void init_backend_opengl3(py::module& m)
{
    m.def("Init", ImGui_ImplOpenGL3_Init, "glsl_version"_a = nullptr);
    m.def("Shutdown", ImGui_ImplOpenGL3_Shutdown);
    m.def("NewFrame", ImGui_ImplOpenGL3_NewFrame);
    m.def("RenderDrawData", ImGui_ImplOpenGL3_RenderDrawData, "draw_data"_a);
    // Optional
    m.def("CreateFontsTexture", ImGui_ImplOpenGL3_CreateFontsTexture);
    m.def("DestroyFontsTexture", ImGui_ImplOpenGL3_DestroyFontsTexture);
    m.def("CreateDeviceObjects", ImGui_ImplOpenGL3_CreateDeviceObjects);
    m.def("DestroyDeviceObjects", ImGui_ImplOpenGL3_DestroyDeviceObjects);
}