#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <string>
#include "raylib.h"

#include "urdf/model.h"
#include "tinyxml/txml.h"
#include <exception>
#include <vector>

#include "imgui.h"

using namespace std;

struct Shape
{
	Vector3 trans{ 0.0f, 0.0f, 0.0f };
	Vector3 rot{ 0.0f, 0.0f, 0.0f };
	Vector3 scale{ 1.0f,1.0f, 1.0f };

	string type = "None";

	float lenght;
	float radius;
	Color color = RED;
};

struct ModelShape : public Shape
{
	Model model;
};


struct Collision
{
	Transform origin;
	urdf::GeometryType type;
	string name;
};



struct URDF_Link
{
	string linkName = "None";
	vector<URDF_Link> childLinks;

	vector<Collision> collisions;
	vector<Shape> shapes;
};


struct UrdfModel
{
	vector<Shape> shapes;
};

//////JOINTS
struct JointCallibration
{
	std::optional<double> falling;
	std::optional<double> rising;
};

struct JoinDynamics
{
	double friction;
	double damping;
};

struct JointLimits
{
	double effort;
	double velocity;
	double lower;
	double upper;
};

struct JointMimic
{
	string jointName;
	double multiplier;
	double offset;
};

struct JointSafety
{
	double k_position;
	double k_velocity;
	double lower_limit;
	double upper_limit;
};

struct Joint
{
	string jointName;
	URDF_Link* parentLink = nullptr;
	URDF_Link* childLink = nullptr;

	JointCallibration jointCallibration;
	JoinDynamics jointDynamics;
	JointLimits jointLimit;
	JointMimic jointMimic;
	JointSafety jointSafety;
	urdf::JointType type;

	Vector3 axis;
};





class Editor
{
private:
	void RecrusiveUI(URDF_Link &link);

public:
	std::shared_ptr<urdf::UrdfModel> model;

	Transform* gizmosTransform;

	Shape *selectedShape;
	Collision *selectedCollision;
	Joint* selectedJoint;


	UrdfModel urdf_model;

	URDF_Link rootLink;
	map<string, URDF_Link*> linkMap;
	map<string, Joint*> jointMap;

	void LoadUrdf();
	void LoadLinks(shared_ptr<urdf::Link> link, URDF_Link &l);

	void LoadJointsRoot();
	

	void UI();
	void UI2();

	void Start();
	void Render(Camera3D& cam, Transform& transform);
	void RenderRekursive(Camera3D& cam, Transform& transform, URDF_Link &rootLink);
	void Delete();
};

#endif // !EDITOR_H
