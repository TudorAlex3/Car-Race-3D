#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/transform3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */
vector<VertexFormat> in_points;
vector<VertexFormat> ex_points;
vector<VertexFormat> mid_points;
vector<VertexFormat> circuit;
vector<glm::vec3> ex_tree_points;
vector<glm::vec3> in_tree_points;
vector<glm::vec3> car1_points;
vector<glm::vec3> car2_points;
vector<glm::vec3> car3_points;
vector<glm::vec3> car4_points;
float offset_x;
float offset_y;
float offset_z;
bool minimap;

tema2::tema2()
{
}


tema2::~tema2()
{
}


void tema2::Init()
{
    camera = new implemented::Camera();
    camera->Set(glm::vec3(-5, 10, 5), glm::vec3(0, 10, 0), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, zNear, zFar);

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(1000, 50, resolution.x / 5.f, resolution.y / 5.f);


    // Create grass
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1000, 0.5, -1000), glm::vec3(0, 0.5, 0)),
            VertexFormat(glm::vec3(1000, 0.5, -1000), glm::vec3(0, 0.5, 0)),
            VertexFormat(glm::vec3(-1000, 0.5, 1000), glm::vec3(0, 0.5, 0)),
            VertexFormat(glm::vec3(1000, 0.5, 1000), glm::vec3(0, 0.5, 0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 2, 3,
        };

        meshes["grass"] = new Mesh("grass");
        meshes["grass"]->InitFromData(vertices, indices);
    }

    // Create circuit
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0.7, 0), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(18.98, 0.7, -19.83), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(41.75, 0.7, -39.34), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(77.52, 0.7, -58.85), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(106.79, 0.7, -71.86), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(145.82, 0.7, -91.38), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(183.22, 0.7, -97.88), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(219, 0.7, -110.89), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(253.14, 0.7, -120.75), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(278.44, 0.7, -127.99), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(307.15, 0.7, -129.5), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(325.33, 0.7, -126.17), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(338.57, 0.7, -111.27), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(351.82, 0.7, -82.3), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(361.75, 0.7, -54.98), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(371.02, 0.7, -38.74), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(385.59, 0.7, -29.58), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(403.5, 0.7, -27.91), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(425.15, 0.7, -26.25), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(451.38, 0.7, -29.58), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(471.37, 0.7, -34.16), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(480, 0.7, -40), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(489.87, 0.7, -52.39), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(504.24, 0.7, -62.87), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(520.17, 0.7, -76.08), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(531.05, 0.7, -86.18), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(546.59, 0.7, -90.84), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(562.91, 0.7, -92.23), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(584.87, 0.7, -84.87), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(615.77, 0.7, -63.73), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(640.16, 0.7, -34.46), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(675.93, 0.7, -6.82), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(693.82, 0.7, 20.82), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(713.33, 0.7, 51.72), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(721.46, 0.7, 84.24), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(705.2, 0.7, 113.51), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(679.19, 0.7, 147.66), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(643.41, 0.7, 170.43), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(614.14, 0.7, 186.69), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(575.11, 0.7, 202.95), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(540.97, 0.7, 209.45), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(511.7, 0.7, 214.33), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(479.23, 0.7, 212.92), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(443.4, 0.7, 196.44), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(419.01, 0.7, 181.81), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(389.74, 0.7, 155.79), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(366.97, 0.7, 146.04), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(336.08, 0.7, 136.28), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(298.68, 0.7, 142.78), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(266.15, 0.7, 154.17), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(235.26, 0.7, 170.43), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(223.87, 0.7, 194.82), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(209.24, 0.7, 220.84), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(181.6, 0.7, 250.11), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(158.83, 0.7, 279.38), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(132.81, 0.7, 307.02), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(92.16, 0.7, 326.53), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(64.52, 0.7, 341.17), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(30.37, 0.7, 350.93), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-7.03, 0.7, 359.06), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-42.81, 0.7, 359.06), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-75.33, 0.7, 347.67), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-96.47, 0.7, 331.41), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-127.37, 0.7, 307.02), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-156.64, 0.7, 279.38), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-177.77, 0.7, 250.11), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-205.42, 0.7, 237.1), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-244.45, 0.7, 235.47), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-285.1, 0.7, 246.85), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-306.24, 0.7, 263.12), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-324.12, 0.7, 287.51), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-359.9, 0.7, 316.78), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-395.67, 0.7, 334.66), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-424.94, 0.7, 344.42), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-450.96, 0.7, 349.3), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-478.6, 0.7, 344.42), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-507.87, 0.7, 329.79), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-525.76, 0.7, 307.02), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-532.27, 0.7, 279.38), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-532.27, 0.7, 246.85), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-529.01, 0.7, 215.96), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-512.75, 0.7, 188.31), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-491.61, 0.7, 168.8), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-465.6, 0.7, 154.17), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-439.58, 0.7, 137.9), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-407.06, 0.7, 133.03), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-379.41, 0.7, 128.15), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-343.64, 0.7, 116.77), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-317.62, 0.7, 98.88), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-311.12, 0.7, 71.23), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-306.24, 0.7, 40.34), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-309.49, 0.7, 15.95), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-325.75, 0.7, -11.7), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-340.39, 0.7, -32.84), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-351.77, 0.7, -65.36), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-355.02, 0.7, -94.63), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-348.52, 0.7, -123.9), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-329, 0.7, -141.79), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-301.36, 0.7, -154.79), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-268.84, 0.7, -158.05), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-236.31, 0.7, -154.79), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-205.42, 0.7, -135.28), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-187.53, 0.7, -115.77), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-166.39, 0.7, -83.25), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-143.63, 0.7, -50.72), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-133.87, 0.7, -19.83), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-120.86, 0.7, 12.69), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-109.2, 0.7, 37.09), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-83.46, 0.7, 61.48), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-55.82, 0.7, 56.6), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-37.15, 0.7, 36), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-18.42, 0.7, 17.57), glm::vec3(0, 0, 0)),
        };

        // Create outer and inner points
        mid_points = vertices;
        InExPoints();

        circuit = CreateVertices();
        vector<unsigned int> indices;
        for (int i = 0; i < circuit.size(); i++)
            indices.push_back(i);

        InExPoints();
        meshes["points"] = new Mesh("points");
        meshes["points"]->InitFromData(circuit, indices);
    }

    // Create tree
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(1, -1, 1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(-1, 1, -1), glm::vec3(0.2, 1, 0)),
            VertexFormat(glm::vec3(1, 1, -1), glm::vec3(0.2, 1, 0)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["tree"] = new Mesh("tree");
        meshes["tree"]->InitFromData(vertices, indices);
    }

    // Create trunk
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.7, 0.4, 0.2)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.7, 0.4, 0.2)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["trunk"] = new Mesh("trunk");
        meshes["trunk"]->InitFromData(vertices, indices);
    }

    // Create car1
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.1, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.1, 0.7, 1)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["car1"] = new Mesh("car1");
        meshes["car1"]->InitFromData(vertices, indices);
    }

    // Create car2
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.7, 0.1, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.7, 0.1, 1)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["car2"] = new Mesh("car2");
        meshes["car2"]->InitFromData(vertices, indices);
    }

    // Create car3
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.7, 0.7, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.7, 0.7, 1)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["car3"] = new Mesh("car3");
        meshes["car3"]->InitFromData(vertices, indices);
    }

    // Create car4
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.3, 0.5, 0.8)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.3, 0.5, 0.8)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["car4"] = new Mesh("car4");
        meshes["car4"]->InitFromData(vertices, indices);
    }

    // Player car
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.1, 1, 0.7)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.1, 1, 0.7)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

        };

        meshes["player"] = new Mesh("player");
        meshes["player"]->InitFromData(vertices, indices);
    }

    // Create points for trees
    TreePoints();

    tX_c1 = car1_points[c1_p1][0];
    tZ_c1 = car1_points[c1_p1][2];
    tX_c2 = car2_points[c2_p1][0];
    tZ_c2 = car2_points[c2_p1][2];
    tX_c3 = car3_points[c3_p1][0];
    tZ_c3 = car3_points[c3_p1][0];
    tX_c4 = car4_points[c4_p1][0];
    tZ_c4 = car4_points[c4_p1][0];
    sphere_X_c1 = tX_c1;
    sphere_Y_c1 = tY_c1;
    sphere_Z_c1 = tZ_c1;
    sphere_X_c2 = tX_c2;
    sphere_Y_c2 = tY_c2;
    sphere_Z_c2 = tZ_c2;
    sphere_Y_c3 = tY_c3;
    sphere_Z_c3 = tZ_c3;;

    offset_x = 15;
    offset_y = -8;
    offset_z = -15;
}


void tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema2::Update(float deltaTimeSeconds)
{
    // Move obstacles
    CarMove(deltaTimeSeconds, car1_points, &(c1_p1), &(c1_p2), &(tX_c1), &(tZ_c1), &(angular_c1), 30);
    CarMove(deltaTimeSeconds, car2_points, &(c2_p1), &(c2_p2), &(tX_c2), &(tZ_c2), &(angular_c2), 40);
    CarMove(deltaTimeSeconds, car3_points, &(c3_p1), &(c3_p2), &(tX_c3), &(tZ_c3), &(angular_c3), 10);
    CarMove(deltaTimeSeconds, car4_points, &(c4_p1), &(c4_p2), &(tX_c4), &(tZ_c4), &(angular_c4), 20);


    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, zNear, zFar);

    // Render principal window
    minimap = false;
    RenderScene(deltaTimeSeconds);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Render minimap
    minimap = true;
    RenderScene(deltaTimeSeconds);
}


void tema2::FrameEnd()
{
}


void tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();

    if (minimap) {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
        glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix1));
    }
    else {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
        glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void tema2::RenderScene(float deltaTimeSeconds) {

    // If minimap is true
    if (minimap)
    {
        glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

        glm::ivec2 resolution = window->GetResolution();

        // Generate camera for minimap
        camera1 = new implemented::Camera();

        glm::vec3 camera_pos = camera->GetTargetPosition();
        float x = camera_pos[0];
        float y = camera_pos[1];
        float z = camera_pos[2];

        camera1->Set(glm::vec3(x, 250, z), glm::vec3(x + offset_x, y, z + offset_z), glm::vec3(0, 0, 1));
        glm::vec3 camera_pos1 = camera1->GetTargetPosition();
        projectionMatrix1 = glm::ortho(-50.f, 100.f, -50.f, 100.f, 10.f, 500.f);
    }

    for (int i = 0; i < ex_tree_points.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(ex_tree_points[i][0], 30, ex_tree_points[i][2]);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(ex_tree_points[i][0], 10, ex_tree_points[i][2]);
        modelMatrix *= transform3D::Scale(2, 20, 2);
        RenderMesh(meshes["trunk"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < in_tree_points.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(in_tree_points[i][0], 30, in_tree_points[i][2]);
        modelMatrix *= transform3D::Scale(10, 10, 10);
        RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(in_tree_points[i][0], 10, in_tree_points[i][2]);
        modelMatrix *= transform3D::Scale(2, 20, 2);
        RenderMesh(meshes["trunk"], shaders["VertexColor"], modelMatrix);
    }

    sphere_X_c1 = tX_c1;
    sphere_Y_c1 = tY_c1;
    sphere_Z_c1 = tZ_c1;;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(tX_c1, tY_c1, tZ_c1);
    modelMatrix *= transform3D::RotateOY(initial - angular_c1);
    modelMatrix *= transform3D::Scale(5, 5, 15);
    RenderMesh(meshes["car1"], shaders["VertexColor"], modelMatrix);

    sphere_X_c2 = tX_c2;
    sphere_Y_c2 = tY_c2;
    sphere_Z_c2 = tZ_c2;;
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(tX_c2, tY_c2, tZ_c2);
    modelMatrix *= transform3D::RotateOY(initial - angular_c2);
    modelMatrix *= transform3D::Scale(5, 5, 15);
    RenderMesh(meshes["car2"], shaders["VertexColor"], modelMatrix);

    sphere_X_c3 = tX_c3;
    sphere_Y_c3 = tY_c3;
    sphere_Z_c3 = tZ_c3;;
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(tX_c3, tY_c3, tZ_c3);
    modelMatrix *= transform3D::RotateOY(initial - angular_c3);
    modelMatrix *= transform3D::Scale(5, 5, 15);
    RenderMesh(meshes["car3"], shaders["VertexColor"], modelMatrix);

    sphere_X_c4 = tX_c4;
    sphere_Y_c4 = tY_c4;
    sphere_Z_c4 = tZ_c4;;
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(tX_c4, tY_c4, tZ_c4);
    modelMatrix *= transform3D::RotateOY(initial - angular_c4);
    modelMatrix *= transform3D::Scale(5, 5, 15);
    RenderMesh(meshes["car4"], shaders["VertexColor"], modelMatrix);

    glm::vec3 camera_pos = camera->GetTargetPosition();
    float x = camera_pos[0];
    float y = camera_pos[1] + offset_y;
    float z = camera_pos[2];

    x += cos(player_rotate + 1) * (offset_x);
    z += sin(player_rotate + 1) * (offset_z);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(x, y, z);
    modelMatrix *= transform3D::RotateOY(initial + player_rotate);
    modelMatrix *= transform3D::Scale(5, 5, 15);
    RenderMesh(meshes["player"], shaders["VertexColor"], modelMatrix);

    RenderMesh(meshes["grass"], shaders["VertexColor"], glm::mat4(1));
    RenderMesh(meshes["points"], shaders["VertexColor"], glm::mat4(1));
}


// Create outer and inner points
void tema2::InExPoints() {
    for (int i = 0; i < mid_points.size() - 1; i++) {
        glm::vec3 P1 = mid_points[i].position;
        glm::vec3 P2 = mid_points[i + 1].position;

        glm::vec3 D;
        D[0] = P1[0] - P2[0];
        D[1] = P1[1] - P2[1];
        D[2] = P1[2] - P2[2];

        glm::vec3 UP = glm::vec3(0, 1, 0);

        glm::vec3 P;
        P = normalize(glm::cross(D, UP));

        glm::vec3 R;
        glm::vec3 A;
        glm::vec3 dist(30, 0, 30);
        R = P1 + dist * P;
        A = P1 - dist * P;

        ex_points.push_back(VertexFormat(R, glm::vec3(0, 0, 0)));
        in_points.push_back(VertexFormat(A, glm::vec3(0, 0, 0)));

        glm::vec3 C1;
        glm::vec3 C2;
        glm::vec3 C3;
        glm::vec3 C4;
        glm::vec3 dist_cars(20, 0, 20);
        glm::vec3 dist_cars2(5, 0, 5);
        C1 = P1 + dist_cars * P;
        C2 = P1 - dist_cars * P;
        C3 = P1 + dist_cars2 * P;
        C4 = P1 - dist_cars2 * P;

        car1_points.push_back(C1);
        car2_points.push_back(C2);
        car3_points.push_back(C3);
        car4_points.push_back(C4);
    }

}


// Create points for trees
void tema2::TreePoints() {
    for (int i = 0; i < ex_points.size() - 1; i++) {
        glm::vec3 P1R = ex_points[i].position;
        glm::vec3 P2R = ex_points[i + 1].position;

        glm::vec3 P1A = in_points[i].position;
        glm::vec3 P2A = in_points[i + 1].position;

        glm::vec3 DR;
        glm::vec3 DA;
        DR[0] = P1R[0] - P2R[0];
        DR[1] = P1R[1] - P2R[1];
        DR[2] = P1R[2] - P2R[2];
        DA[0] = P1A[0] - P2A[0];
        DA[1] = P1A[1] - P2A[1];
        DA[2] = P1A[2] - P2A[2];

        glm::vec3 UP = glm::vec3(0, 1, 0);

        glm::vec3 PR;
        glm::vec3 PA;
        glm::vec3 R;
        glm::vec3 A;
        glm::vec3 distR(10, 0, 30);
        glm::vec3 distA(5, 0, 10);
        PR = normalize(glm::cross(DR, UP));
        PA = normalize(glm::cross(DA, UP));
        R = P1R + distR * PR;
        A = P1A - distA * PA;

        ex_tree_points.push_back(R);
        in_tree_points.push_back(A);
    }
}


// Add vertices in specified order
vector<VertexFormat> tema2::CreateVertices() {
    vector<VertexFormat> vertices;
    int i;
    for (i = 1; i < ex_points.size(); i++) {
        vertices.push_back(ex_points[i - 1]);
        vertices.push_back(in_points[i - 1]);
        vertices.push_back(in_points[i]);
        vertices.push_back(ex_points[i - 1]);
        vertices.push_back(in_points[i]);
        vertices.push_back(ex_points[i]);
    }

    i--;
    vertices.push_back(ex_points[i]);
    vertices.push_back(in_points[i]);
    vertices.push_back(in_points[0]);
    vertices.push_back(ex_points[i]);
    vertices.push_back(in_points[0]);
    vertices.push_back(ex_points[0]);

    return vertices;
}


// Move obstacles
void tema2::CarMove(float deltaTimeSeconds, glm::vector<glm::vec3> points,
    int(*p1), int(*p2), float(*tX), float(*tZ), float(*angular), int move) {
    float x_p1 = points[*(p1)][0];
    float z_p1 = points[*(p1)][2];
    float x_p2 = points[*(p2)][0];
    float z_p2 = points[*(p2)][2];

    // X point from which I left < X point to which I have to reach
    // Z point from which I left < Z point to which I have to reach
    if (x_p1 < x_p2 && z_p1 < z_p2) {
        // the car has reached the second point (change the points)
        if (*(tX) >= x_p2 && *(tZ) >= z_p2) {
            *(p1) = *(p1)+1;
            *(p2) = *(p2)+1;
            // if the end of the list of points has been reached, I start from the beginning
            if (*(p2) == points.size())
                *(p2) = 0;
            if (*(p1) == points.size())
                *(p1) = 0;
        }
        else {
            // move the car to the point I need to reach
            if (*(tX) < x_p2)
                *(tX) += move * deltaTimeSeconds;
            if (*(tZ) < z_p2)
                *(tZ) += move * deltaTimeSeconds;
            if (*(angular) > 0.5)
                *(angular) = 0.5;
            *(angular) += 0.5 * deltaTimeSeconds;
        }
    }

    // X point from which I left < X point to which I have to reach
    // Z point from which I left > Z point to which I have to reach
    else if (x_p1 < x_p2 && z_p1 > z_p2) {
        if (*(tX) >= x_p2 && *(tZ) <= z_p2) {
            *(p1) = *(p1)+1;
            *(p2) = *(p2)+1;
            if (*(p2) == points.size())
                *(p2) = 0;
            if (*(p1) == points.size())
                *(p1) = 0;
        }
        else {
            if (*(tX) < x_p2)
                *(tX) += move * deltaTimeSeconds;
            if (*(tZ) > z_p2)
                *(tZ) -= move * deltaTimeSeconds;
            if (*(angular) < 0.5)
                *(angular) = 0.5;
            *(angular) -= 0.5 * deltaTimeSeconds;
        }
    }
    // X point from which I left > X point to which I have to reach
    // Z point from which I left < Z point to which I have to reach
    else if (x_p1 > x_p2 && z_p1 < z_p2) {
        if (*(tX) <= x_p2 && *(tZ) >= z_p2) {
            *(p1) = *(p1)+1;
            *(p2) = *(p2)+1;
            if (*(p2) == points.size())
                *(p2) = 0;
            if (*(p1) == points.size())
                *(p1) = 0;
        }
        else {
            if (*(tX) > x_p2)
                *(tX) -= move * deltaTimeSeconds;
            if (*(tZ) < z_p2)
                *(tZ) += move * deltaTimeSeconds;
            if (*(angular) < 0.5)
                *(angular) = 0.5;
            *(angular) -= 0.5 * deltaTimeSeconds;
        }
    }
    // X point from which I left < X point to which I have to reach
    // Z point from which I left > Z point to which I have to reach
    else if (x_p1 > x_p2 && z_p1 > z_p2) {
        if (*(tX) <= x_p2 && *(tZ) <= z_p2) {
            *(p1) = *(p1)+1;
            *(p2) = *(p2)+1;
            if (*(p2) == points.size())
                *(p2) = 0;
            if (*(p1) == points.size())
                *(p1) = 0;
        }
        else {
            if (*(tX) > x_p2)
                *(tX) -= move * deltaTimeSeconds;
            if (*(tZ) > z_p2)
                *(tZ) -= move * deltaTimeSeconds;
            if (*(angular) > 0.05)
                *(angular) = 0.05;
            *(angular) += 0.05 * deltaTimeSeconds;
        }
    }
}


// Check if the car is on the track using the formula
float tema2::TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C)
{
    glm::vec2 AB(B[0] - A[0], B[2] - A[2]);
    glm::vec2 AC(C[0] - A[0], C[2] - A[2]);
    float cross_product = AB[0] * AC[1] - AB[1] * AC[0];
    return abs(cross_product) / 2;
}


bool tema2::InsideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C)
{
    float triangle_area = TriangleArea(A, B, C);
    float area_sum = 0;
    area_sum += TriangleArea(A, B, P);
    area_sum += TriangleArea(A, C, P);
    area_sum += TriangleArea(B, C, P);

    if ((triangle_area <= area_sum && triangle_area >= area_sum - 0.2) ||
        (triangle_area >= area_sum && triangle_area <= area_sum + 0.2))
        return true;
    else
        return false;
}


bool tema2::ExitCheck(glm::vec3 pos) {
    glm::vec3 position = {
            pos[0] + cos(player_rotate + 1) * (offset_x),
            0,
            pos[2] + sin(player_rotate + 1) * (offset_z)
    };

    for (int i = 0; (i + 2) < circuit.size(); i += 3) {
        glm::vec3 A = circuit[i].position;
        glm::vec3 B = circuit[i + 1].position;
        glm::vec3 C = circuit[i + 2].position;

        if (InsideTriangle(position, A, B, C))
            return false;
    }

    return true;
}


// Check collisions between cars
bool tema2::SphereCollision(glm::vec4 player_sphere, glm::vec4 car_sphere) {
    float Ax = player_sphere[0] + cos(player_rotate + 1) * (offset_x);
    float Ay = player_sphere[1] + offset_y;
    float Az = player_sphere[2] + sin(player_rotate + 1) * (offset_z);
    float Aradius = player_sphere[3];

    float Bx = car_sphere[0];
    float By = car_sphere[1];
    float Bz = car_sphere[2];
    float Bradius = car_sphere[3];

    float diff1 = (Ax - Bx) * (Ax - Bx);
    float diff2 = (Ay - By) * (Ay - By);
    float diff3 = (Az - Bz) * (Ay - Bz);
    float diff = sqrt(diff1 + diff2 + diff3);

    if (diff <= (Aradius + Bradius))
        return true;
    return false;
}


void tema2::OnInputUpdate(float deltaTime, int mods)
{
    // W, S - > move forward/back
    if (window->KeyHold(GLFW_KEY_W)) {
        camera->MoveForward(camera_move * deltaTime);

        // Check for collisions with grass or obstacles
        bool grass_collision = ExitCheck(camera->GetTargetPosition());


        glm::vec4 player_sphere(camera->GetTargetPosition(), 15);
        glm::vec4 car1_sphere(glm::vec3(tX_c1, tY_c1, tZ_c1), 5);
        glm::vec4 car2_sphere(glm::vec3(tX_c2, tY_c2, tZ_c2), 5);
        glm::vec4 car3_sphere(glm::vec3(tX_c3, tY_c3, tZ_c3), 5);
        glm::vec4 car4_sphere(glm::vec3(tX_c4, tY_c4, tZ_c4), 5);

        bool cars_collision = SphereCollision(player_sphere, car1_sphere);
        cars_collision = cars_collision || SphereCollision(player_sphere, car2_sphere);
        cars_collision = cars_collision || SphereCollision(player_sphere, car3_sphere);
        cars_collision = cars_collision || SphereCollision(player_sphere, car4_sphere);

        if (grass_collision || cars_collision)
            camera->MoveForward(-camera_move * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        camera->MoveForward(-camera_move * deltaTime);

        bool grass_collision = ExitCheck(camera->GetTargetPosition());

        glm::vec4 player_sphere(camera->GetTargetPosition(), 15);
        glm::vec4 car1_sphere(glm::vec3(tX_c1, tY_c1, tZ_c1), 5);
        glm::vec4 car2_sphere(glm::vec3(tX_c2, tY_c2, tZ_c2), 5);

        bool cars_collision = SphereCollision(player_sphere, car1_sphere);
        cars_collision = cars_collision || SphereCollision(player_sphere, car2_sphere);

        if (grass_collision || cars_collision)
            camera->MoveForward(camera_move * deltaTime);
    }

    // A , D -> Rotate
    if (window->KeyHold(GLFW_KEY_A)) {
        camera->RotateThirdPerson_OY(camera_rotate * deltaTime);
        player_rotate += camera_rotate * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        camera->RotateThirdPerson_OY(-camera_rotate * deltaTime);
        player_rotate -= camera_rotate * deltaTime;
    }
}


void tema2::OnKeyPress(int key, int mods)
{
}


void tema2::OnKeyRelease(int key, int mods)
{
}


void tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema2::OnWindowResize(int width, int height)
{
}
