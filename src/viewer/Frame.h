//
// Created by valdemar on 22.10.17.
//

#pragma once

#include <cstdint>

#include <glm/glm.hpp>
#include <json.hpp>

namespace pod {
struct Circle;
struct Rectangle;
struct Line;
struct Unit;
}

/**
 * Represent one game frame.
 *  - contains all primitives to be drawn
 *  - contains user message to draw in message window
 */
struct Frame {
    enum class UnitType {
        undefined = 0,
        helicopter = 1,
        tank = 2,
        fighter = 3,
        count
    };

    enum class AreaType {
        unknown = 0,
        forest,
        swamp,
        rain,
        cloud,
        count
    };

    std::vector<pod::Circle> circles;
    std::vector<pod::Rectangle> rectangles;
    std::vector<pod::Line> lines;
    std::vector<pod::Unit> units;
    std::string user_message;
};


namespace pod {

struct Colored {
    glm::vec3 color;
};

struct Line : Colored {
    float x1;
    float y1;
    glm::vec3 surprise; //TODO: Need to use geometric shader, to avoid that
    float x2;
    float y2;
};

struct Circle : Colored {
    glm::vec2 center;
    float radius;
};

struct Rectangle : Colored {
    glm::vec2 center;
    float w;
    float h;
};

struct Unit : Circle {
    int hp;
    int max_hp;
    Frame::UnitType utype = Frame::UnitType::undefined;
    float course = 0;
};

struct AreaDesc {
    //Cell coordinates
    int x;
    int y;
    Frame::AreaType type;
};

} // namespace pod