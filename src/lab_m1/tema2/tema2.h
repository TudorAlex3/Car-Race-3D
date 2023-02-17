#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"


namespace m1
{
    class tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        tema2();
        ~tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene(float deltaTimeSeconds);
        void InExPoints();
        void TreePoints();
        glm::vector<VertexFormat> CreateVertices();
        float TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);
        bool InsideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C);
        bool ExitCheck(glm::vec3 pos);
        bool SphereCollision(glm::vec4 player_sphere, glm::vec4 car_sphere);
        void CarMove(float deltaTimeSeconds, glm::vector<glm::vec3> points, 
            int (*p1), int(*p2), float (*tX), float(*tZ), float (*angular), int move);

    private:
        implemented::Camera* camera;
        glm::mat4 projectionMatrix;
        implemented::Camera* camera1;
        glm::mat4 projectionMatrix1;

        float fov = 3.14f / 4;
        float left = 10, right = 20, bottom = 0.01, top = 20, zNear = 0.1, zFar = 200;
        glm::vec3 lightPosition;

        // car 1
        float tX_c1 = 0, tY_c1 = 3, tZ_c1 = 0;
        int c1_p1 = 0, c1_p2 = 1;
        float angular_c1 = 0;
        float sphere_X_c1, sphere_Y_c1, sphere_Z_c1;

        // car 2
        float tX_c2 = 0, tY_c2 = 3, tZ_c2 = 0;
        int c2_p1 = 0, c2_p2 = 1;
        float angular_c2 = 0;
        float sphere_X_c2, sphere_Y_c2, sphere_Z_c2;

        // car 3
        float tX_c3 = 0, tY_c3 = 3, tZ_c3 = 0;
        int c3_p1 = 0, c3_p2 = 1;
        float angular_c3 = 0;
        float sphere_X_c3, sphere_Y_c3, sphere_Z_c3;

        // car 4
        float tX_c4 = 0, tY_c4 = 3, tZ_c4 = 0;
        int c4_p1 = 0, c4_p2 = 1;
        float angular_c4 = 0;
        float sphere_X_c4, sphere_Y_c4, sphere_Z_c4;

        // player car
        float tX_player = 15, tZ_player = -15;
        float angular_player = 0;
        float initial = -(3.14/4);
        float move_player = 0;
        float player_rotate = 0;
        float camera_rotate = 1;
        float camera_move = 50;

        // minimap
        ViewportArea miniViewportArea;
    };
}   // namespace m1
