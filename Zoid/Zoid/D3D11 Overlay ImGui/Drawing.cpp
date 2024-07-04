#include "Drawing.h"
#include "ImGui/imgui_internal.h"
#include "main.h"
#include <D3DX11tex.h>
#include "ImGui/imgui_settings.h"

LPCSTR Drawing::lpWindowName = "Vex";
ImVec2 Drawing::vWindowSize = { 350, 75 };
ImGuiWindowFlags Drawing::WindowFlags = 0;
bool Drawing::bDraw = false;
UI::WindowItem Drawing::lpSelectedWindow = { nullptr, "", "" };

bool Drawing::isActive()
{
    return bDraw == false;

}

void Drawing::Draw()
{
    if (isActive())
    {
        
    }
};