#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, only in debug mode
#endif

#include "raylib.h"
#include "raymath.h"
#include "raygizmo.h"
#include "urdf/model.h"

#include "Editor.h"
#include "imgui.h"
#include "rlImGui.h"

const char* EXAMPLE_TITLE = "Example 01 - Getting Started";

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

Editor editor;

int main(int argc, char** argv)
{
   
    Transform crateTransform = GizmoIdentity();

    // Setup: Initialize the window and basic configurations.
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TextFormat("raylib-gizmo | %s", EXAMPLE_TITLE));
    SetTargetFPS(60);
    rlImGuiSetup(true);

    // Load the crate texture.
    Texture crateTexture = LoadTexture("resources/crate_texture.jpg");
    GenTextureMipmaps(&crateTexture);
    SetTextureFilter(crateTexture, TEXTURE_FILTER_TRILINEAR);

    // Load the crate model and apply the texture.
    Model crateModel = LoadModel("resources/crate_model.obj");
    //crateModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = crateTexture;

    // Setup the 3D camera.
    Camera cam = { 0 };
    cam.fovy = 45.0f;
    cam.position = Vector3{ 7.5f, 5.5f, 5.0f };
    cam.target = Vector3{ 0, 1.5f, 0 };
    cam.up = Vector3{ 0, 1, 0 };
    cam.projection = CAMERA_PERSPECTIVE;

    //Editor
    editor.gizmosTransform = &crateTransform;
    editor.Start();
    editor.LoadUrdf();

    GizmoFlags flag = GIZMO_TRANSLATE;

    // Main game loop.
    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Clear the background with a dark blue color.
        ClearBackground(Color { 0, 0, 10, 255 });

        BeginMode3D(cam);


        //edior rendering
        editor.Render(cam, crateTransform);

        // Update the crate's transform matrix from the gizmo.
        crateModel.transform = GizmoToMatrix(crateTransform);

        //DrawCube(Vector3{ crateTransform.translation.x, crateTransform.translation.y, crateTransform.translation.z }, crateTransform.scale.x, crateTransform.scale.y, crateTransform.scale.z, BLUE);

        // Draw the translation gizmo and handle its input.
        // This will directly update the crateTransform variable.
        
        if(IsKeyPressed(KEY_T))
        {
            flag = GIZMO_TRANSLATE;
        }
        else if(IsKeyPressed(KEY_R))
        {
            flag = GIZMO_ROTATE;
        }
        else if (IsKeyPressed(KEY_S))
        {
            flag = GIZMO_SCALE;
        }

        DrawGizmo3D(flag, &crateTransform);

        EndMode3D();


        rlImGuiBegin();

        editor.UI();
        editor.UI2();

        // end ImGui Content
        rlImGuiEnd();

        EndDrawing();
    }

    // Unload resources and clean up.
    UnloadTexture(crateTexture);
    UnloadModel(crateModel);
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}