#include "Editor.h"
#include <rlgl.h>
#include <raymath.h>

void Editor::LoadUrdf()
{
    urdf_model.shapes.clear();
    //Testing stuff
    const char* urdfstr_geometry_test =
        "<?xml version=\"1.0\"?>\n"
        "<robot name=\"test\">\n"
        "  <link name=\"base_link\">\n"

        "    <visual>\n"
        "      <origin xyz=\"0 0 0\" rpy=\"0 0 0\"/>\n"
        "      <geometry>\n"
        "        <cylinder length=\"3.6\" radius=\"0.25\"/>\n"
        "      </geometry>\n"
        "    </visual>\n"

        "    <visual>\n"
        "      <origin xyz=\"2 5 0\" rpy=\"0 0 0\"/>\n"
        "      <geometry>\n"
        "        <sphere radius=\"0.5\"/>\n"
        "      </geometry>\n"
        "    </visual>\n"

        "    <visual>\n"
        "      <origin xyz=\"-2 0 0\" rpy=\"0 0 0\"/>\n"
        "      <geometry>\n"
        "        <box size=\"0.1 0.2 0.3\"/>\n"
        "      </geometry>\n"
        "    </visual>\n"

        "    <visual>\n"
        "      <origin xyz=\"0 2 0\" rpy=\"0 0 0\"/>\n"
        "      <geometry>\n"
        "        <mesh filename=\"test.obj\" scale=\"0.7 0.8 0.9\"/>\n"
        "      </geometry>\n"
        "    </visual>\n"

        "  </link>\n"
        "</robot>";

        model = urdf::UrdfModel::fromUrdfStr(std::string(urdfstr_geometry_test));

        auto base_link = model->getLink("base_link");
        LoadLinks(base_link, rootLink);


        /*
         auto& visuals = base_link->visuals;


        //Die einzelnen links sind sowas wie nodes?
        //shared_ptr<urdf::Link> link = model->getRoot();
        //link->child_links
        //urdf::Link testLink;
        

        for(auto &v : visuals)
        {
            switch ((*v->geometry.value()).type)
            {
            case urdf::CYLINDER: {
                auto cylinder = (std::shared_ptr<urdf::Cylinder>&) v->geometry;
                cout << "Cylinder" << endl;

                Shape newShape;
                newShape.type = "Cylinder";

                newShape.trans.x =  v->origin.position.x;
                newShape.trans.y = v->origin.position.y;
                newShape.trans.z = v->origin.position.z;

                newShape.radius = cylinder->radius;
                newShape.lenght = cylinder->length;
                
                newShape.color = BLUE;

                urdf_model.shapes.push_back(newShape);

                break;
            };
                    

            case urdf::BOX: {
                auto box = (std::shared_ptr<urdf::Box>&) v->geometry;
                cout << "Box" << endl;

                Shape newShape;
                newShape.type = "Box";

                newShape.trans.x = v->origin.position.x;
                newShape.trans.y = v->origin.position.y;
                newShape.trans.z = v->origin.position.z;

                newShape.scale.x = box->dim.x;
                newShape.scale.y = box->dim.y;
                newShape.scale.z = box->dim.z;
                newShape.color = RED;

                urdf_model.shapes.push_back(newShape);

                break;
            };

            case urdf::SPHERE: {
                auto sphere = (std::shared_ptr<urdf::Sphere>&) v->geometry;
                cout << "Sphere" << endl;

                Shape newShape;

                newShape.trans.x =  v->origin.position.x;
                newShape.trans.y = v->origin.position.y;
                newShape.trans.z = v->origin.position.z;

                newShape.type = "Sphere";
                newShape.radius = sphere->radius;
                newShape.color = GREEN;

                urdf_model.shapes.push_back(newShape);

                break;
            };

            case urdf::MESH: {
                auto mesh = (std::shared_ptr<urdf::Mesh>&) v->geometry;
                cout << "Mesh" << endl;
                break;
            }; 
            }
        }
        */
}


void Editor::LoadLinks(shared_ptr<urdf::Link> link, URDF_Link &l)
{
    for (auto& v : link->visuals)
    {
        switch ((*v->geometry.value()).type)
        {
        case urdf::CYLINDER: {
            auto cylinder = (std::shared_ptr<urdf::Cylinder>&) v->geometry;
            cout << "Cylinder" << endl;

            Shape newShape;
            newShape.type = "Cylinder";

            newShape.trans.x = v->origin.position.x;
            newShape.trans.y = v->origin.position.y;
            newShape.trans.z = v->origin.position.z;

            newShape.radius = cylinder->radius;
            newShape.lenght = cylinder->length;

            newShape.color = BLUE;

            l.shapes.push_back(newShape);

            break;
        };


        case urdf::BOX: {
            auto box = (std::shared_ptr<urdf::Box>&) v->geometry;
            cout << "Box" << endl;

            Shape newShape;
            newShape.type = "Box";

            newShape.trans.x = v->origin.position.x;
            newShape.trans.y = v->origin.position.y;
            newShape.trans.z = v->origin.position.z;

            newShape.scale.x = box->dim.x;
            newShape.scale.y = box->dim.y;
            newShape.scale.z = box->dim.z;
            newShape.color = RED;

            l.shapes.push_back(newShape);

            break;
        };

        case urdf::SPHERE: {
            auto sphere = (std::shared_ptr<urdf::Sphere>&) v->geometry;
            cout << "Sphere" << endl;

            Shape newShape;

            newShape.trans.x = v->origin.position.x;
            newShape.trans.y = v->origin.position.y;
            newShape.trans.z = v->origin.position.z;

            newShape.type = "Sphere";
            newShape.radius = sphere->radius;
            newShape.color = GREEN;

            l.shapes.push_back(newShape);

            break;
        };

        case urdf::MESH: {
            auto mesh = (std::shared_ptr<urdf::Mesh>&) v->geometry;
            cout << "Mesh" << endl;
            break;
        };
        }
    }

    //Lade Collisions
    for(auto &coll : link->collisions)
    {
        Collision newCollision;
        newCollision.name = coll->name;
        newCollision.type = coll->geometry.value()->type;

        newCollision.origin.translation.x = coll->origin.position.x;
        newCollision.origin.translation.y = coll->origin.position.y;
        newCollision.origin.translation.z = coll->origin.position.z;

        newCollision.origin.rotation.x = coll->origin.rotation.x;
        newCollision.origin.rotation.y = coll->origin.rotation.y;
        newCollision.origin.rotation.z = coll->origin.rotation.z;

        l.collisions.push_back(newCollision);
    }

    //Lade joints

    auto childLinks = link->child_links;
    for(int i = 0; i<childLinks.size(); i++)
    {
        shared_ptr<urdf::Link> childLink = childLinks[i];
        URDF_Link newChildLink;
        LoadLinks(childLink, newChildLink);
        l.childLinks.push_back(newChildLink);

        linkMap[newChildLink.linkName] = &l.childLinks[l.childLinks.size() - 1];
    }

    linkMap[l.linkName] = &l;
}



void Editor::UI()
{
    ImGui::Begin("Hello");
   
    /*
    if(ImGui::TreeNode("Robot"))
    {
        if (ImGui::CollapsingHeader("Visuals"))
        {
            if (ImGui::Button("Hi"))
            {
                cout << "Hi" << endl;
            }
        }

        if (ImGui::TreeNode("base_link"))
        {
            if (ImGui::CollapsingHeader("Visuals"))
            {
               if(ImGui::Button("Hi"))
               {
                   cout << "Hi2" << endl;
               }
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
    
    */

    RecrusiveUI(rootLink);

    ImGui::End();

}

void Editor::RecrusiveUI(URDF_Link &link)
{

    if(ImGui::TreeNode(link.linkName.c_str()))
    {
        //Und hier jetzt die komponenten welche der link halt eben so hat

        ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_Leaf |            // kein Pfeil
            ImGuiTreeNodeFlags_NoTreePushOnOpen; // kein TreePush nötig

        for(int i = 0; i<link.shapes.size(); i++)
        {
            string name = "Shape" + to_string(i);
            if(ImGui::TreeNodeEx(name.c_str()))
            {
                
                ImGui::TreePop();
            }

            if (ImGui::IsItemClicked())
            {
                selectedShape = &link.shapes[i];
                selectedJoint = nullptr;
                selectedCollision = nullptr;
                gizmosTransform->translation = link.shapes[i].trans;
                //gizmosTransform->rotation = link.shapes[i].rot;
                gizmosTransform->scale = link.shapes[i].scale;
            }
        }

        for(int i = 0; i<link.collisions.size(); i++)
        {
            string name = "Collision" + to_string(i);
            if(ImGui::TreeNode(name.c_str()), flags)
            {
                if(ImGui::IsItemClicked())
                {
                    selectedShape = nullptr;
                    selectedJoint = nullptr;
                    selectedCollision = &link.collisions[i];
                }
                ImGui::TreePop();
            }
        }


        for(int i = 0; i<link.childLinks.size(); i++)
        {
            RecrusiveUI(link.childLinks[i]);
        }

        ImGui::TreePop();
    }
}

void Editor::Start()
{
    cout << "Started" << endl;
}

void Editor::Render(Camera3D &camera, Transform &transform)
{
    //Render das model
    RenderRekursive(camera, transform, rootLink);
}

void Editor::RenderRekursive(Camera3D& cam, Transform& transform, URDF_Link &rootLink)
{
    Ray ray = { 0 };
    RayCollision collision = { 0 };
    ray = GetMouseRay(GetMousePosition(), cam);

    for (auto& shape : rootLink.shapes)
    {
        rlPushMatrix();
        rlTranslatef(shape.trans.x, shape.trans.y, shape.trans.z);
        rlRotatef(shape.rot.y, 0, 1, 0);
        rlRotatef(shape.rot.x, 1, 0, 0);
        rlRotatef(shape.rot.z, 0, 0, 1);
        rlScalef(shape.scale.x, shape.scale.y, shape.scale.z);

        if (shape.type == "Cylinder")
        {
            //hier mit raylib noch checken ob das objekt angeklickt wurde
            DrawCylinder(Vector3Zero(), shape.radius, shape.radius, shape.lenght, 1, shape.color);
        }
        else if (shape.type == "Box")
        {
            DrawCube(Vector3Zero(), shape.scale.x, shape.scale.y, shape.scale.z, shape.color);
        }
        else if (shape.type == "Sphere")
        {
            collision = GetRayCollisionSphere(ray, shape.trans, shape.radius);
            if (collision.hit && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                gizmosTransform->scale = shape.scale;
                gizmosTransform->translation = shape.trans;

                selectedShape = &shape;
            }
            
            DrawSphere(Vector3Zero(), shape.radius, shape.color);
        }

        rlPopMatrix();
    }

    for(int i = 0; i< rootLink.childLinks.size(); i++)
    {
        RenderRekursive(cam, transform, rootLink.childLinks[i]);
    }
}