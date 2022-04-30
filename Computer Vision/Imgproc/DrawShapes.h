﻿#pragma once

#include "Image.h"
#include <iostream>
#include <array>
#include <cmath>

namespace cv
{
    /**
     * \brief Draws a line from a point to another
     * \param img Input Image
     * \param p1 The first point/coordinate in the form (x,y)
     * \param p2 The second point/coordinate in the form (x,y)
     * \param color Color of the line specified in the form (r,g,b)
     */
    void line(Image& img, const std::array<int, 2> p1, const std::array<int, 2> p2, const std::array<uint8_t, 3> color)
    {
        // p1[0] = x1, p1[1] = y1
        // p2[0] = x2, p2[1] = y2

        uint32_t max_y = std::max(p1[1], p2[1]);
        uint32_t min_y = std::min(p1[1], p2[1]);

        uint32_t max_x = std::max(p1[0], p2[0]);
        uint32_t min_x = std::min(p1[0], p2[0]);
        
        if(p1[0] == p2[0])
        {
            while(min_y <= max_y)
            {
                img.at((min_y * img.width() + p1[0]) * img.channels())     = color[0];
                img.at((min_y * img.width() + p1[0]) * img.channels() + 1) = color[1];
                img.at((min_y * img.width() + p1[0]) * img.channels() + 2) = color[2];
                min_y++;
            }
        }
        if(p1[1] == p2[1])
        {
            while(min_x <= max_x)
            {
                img.at((p1[1] * img.width() + min_x) * img.channels()    ) = color[0];
                img.at((p1[1] * img.width() + min_x) * img.channels() + 1) = color[1];
                img.at((p1[1] * img.width() + min_x) * img.channels() + 2) = color[2];
                min_x++;
            }
        }
        else
        {
            float m = static_cast<float>(max_y - min_y) / static_cast<float>((max_x - min_x));

            int c = 0;
            if(p1[0] > p2[0])
                c = static_cast<int>(p1[1] + m * p1[0]);
            else
                c = static_cast<int>(p1[1] - m * p1[0]);

            while(min_y <= max_y)
            {
                uint32_t x = 0;
                if(p1[0] > p2[0])
                    x = static_cast<uint32_t>(static_cast<float>(c - min_y) / m);
                else
                    x = static_cast<uint32_t>(static_cast<float>(min_y - c) / m);
                img.at((min_y * img.width() + x) * img.channels()    ) = color[0];
                img.at((min_y * img.width() + x) * img.channels() + 1) = color[1];
                img.at((min_y * img.width() + x) * img.channels() + 2) = color[2];
                min_y++;
            }
        }
    }

    // Helper function to draw the circle points 
    void draw_circle_point(Image& img, std::array<int, 2> center, int x, int y, std::array<uint8_t, 3> color);

    /**
    * \brief Draws circle on the input image of given radius and given coordinates
    * \param img Input Image
    * \param center Coordinates of the center of the image in the form (x,y)
    * \param radius Length of the radius of circle
    * \param color Color of the outline of the circle drawn in the form (r,g,b)
    */
    void circle_test(Image& img, std::array<int, 2> center, int radius, std::array<uint8_t, 3> color)
    {
        // center[0] = h, center[1] = k
        constexpr double pi = 3.14159265;
        int x = 0, y = radius, p = 1-radius;

        draw_circle_point(img, center, x, y, color);

        while(x < y)
        {
            if(p < 0)
            {
                x ++;
                p += 2*x + 1;
            }
            else
            {
                x++;
                y--;
                p += 2*(x-y)+1;
            }
            draw_circle_point(img, center, x, y, color);
        }
    }

    void draw_circle_point(Image& img, std::array<int, 2> center, int x, int y, std::array<uint8_t, 3> color)
    {
        img.at(((center[1] + y) * img.width() + center[0] + x) * img.channels())   = color[0];
        img.at(((center[1] + y) * img.width() + center[0] + x) * img.channels()+1) = color[1];
        img.at(((center[1] + y) * img.width() + center[0] + x) * img.channels()+2) = color[2];

        img.at(((center[1] - y) * img.width() + center[0] + x) * img.channels())   = color[0];
        img.at(((center[1] - y) * img.width() + center[0] + x) * img.channels()+1) = color[1];
        img.at(((center[1] - y) * img.width() + center[0] + x) * img.channels()+2) = color[2];

        img.at(((center[1] + y) * img.width() + center[0] - x) * img.channels())   = color[0];
        img.at(((center[1] + y) * img.width() + center[0] - x) * img.channels()+1) = color[1];
        img.at(((center[1] + y) * img.width() + center[0] - x) * img.channels()+2) = color[2];

        img.at(((center[1] - y) * img.width() + center[0] - x) * img.channels())   = color[0];
        img.at(((center[1] - y) * img.width() + center[0] - x) * img.channels()+1) = color[1];
        img.at(((center[1] - y) * img.width() + center[0] - x) * img.channels()+2) = color[2];

        img.at(((center[1] + x) * img.width() + center[0] + y) * img.channels())   = color[0];
        img.at(((center[1] + x) * img.width() + center[0] + y) * img.channels()+1) = color[1];
        img.at(((center[1] + x) * img.width() + center[0] + y) * img.channels()+2) = color[2];

        img.at(((center[1] - x) * img.width() + center[0] + y) * img.channels())   = color[0];
        img.at(((center[1] - x) * img.width() + center[0] + y) * img.channels()+1) = color[1];
        img.at(((center[1] - x) * img.width() + center[0] + y) * img.channels()+2) = color[2];

        img.at(((center[1] + x) * img.width() + center[0] - y) * img.channels())   = color[0];
        img.at(((center[1] + x) * img.width() + center[0] - y) * img.channels()+1) = color[1];
        img.at(((center[1] + x) * img.width() + center[0] - y) * img.channels()+2) = color[2];

        img.at(((center[1] - x) * img.width() + center[0] - y) * img.channels())   = color[0];
        img.at(((center[1] - x) * img.width() + center[0] - y) * img.channels()+1) = color[1];
        img.at(((center[1] - x) * img.width() + center[0] - y) * img.channels()+2) = color[2];
    }
}