#pragma once
#include "ImGui/imgui_internal.h"
#include "Vectorr.hpp"
#include <vector>
#include <d3d11.h>

inline ImFont* Lexend_Medium = nullptr;
inline ImFont* Mainfont = nullptr;
inline char input[64] = { "" };
inline char input1[64] = { "" };

inline int tabs = 0;
inline int sub_tabs = 0;

class dot
{
public:
    dot(SourceEngine::Vector p, SourceEngine::Vector v) {
        m_vel = v;
        m_pos = p;
    }

    inline void update();
    inline void draw();

    SourceEngine::Vector m_pos, m_vel;
};

inline std::vector<dot*> dots = { };

inline void dot::update() {
    auto opacity = 200 / 105.0f;

    m_pos += m_vel * (opacity);
}

inline void dot::draw() {
    int opacity = 55.0f * (240 / 255.0f);

    ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x, m_pos.y }, { m_pos.x + 6, m_pos.y + 6 }, ImColor(15, 70, 255, 210), 10.f, 0);


    auto t = std::find(dots.begin(), dots.end(), this);
    if (t == dots.end()) {
        return;
    }
}

inline void dot_draw() {
    struct screen_size {
        int x, y;
    }; screen_size sc;

    sc.x = ImGui::GetIO().DisplaySize.x, sc.y = ImGui::GetIO().DisplaySize.y;

    int s = rand() % 1;

    if (s == 0) {
        dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, -16, 0), SourceEngine::Vector((0) - 0, rand() % 3 + 1, 0)));
    }



    auto alph = 135.0f * (240 / 255.0f);
    auto a_int = (int)(alph);

    ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

    for (auto i = dots.begin(); i < dots.end();) {
        if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
            delete (*i);
            i = dots.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }

    for (auto i = dots.begin(); i < dots.end(); i++) {
        (*i)->draw();
    }
}

inline void dot_destroy() {
    for (auto i = dots.begin(); i < dots.end(); i++) {
        delete (*i);
    }

    dots.clear();
}
