#include "Editor.h"


void Editor::LoadJointsRoot()
{
	for (const auto [key, val] : model->joint_map)
	{
		Joint newJoint;

		newJoint.parentLink = linkMap[val->parent_link_name];
		newJoint.childLink = linkMap[val->child_link_name];


		newJoint.jointName = val->name;
		newJoint.axis.x = val->axis.x; newJoint.axis.y = val->axis.y; newJoint.axis.z = val->axis.z;

		if (val->calibration.has_value())
		{
			JointCallibration jointCallibration;
			jointCallibration.rising = val->calibration.value()->rising;
			jointCallibration.falling = val->calibration.value()->falling;
			newJoint.jointCallibration = jointCallibration;
		}

		if (val->dynamics.has_value())
		{
			JoinDynamics jointDynamics;
			jointDynamics.damping = val->dynamics.value()->damping;
			jointDynamics.friction = val->dynamics.value()->friction;
			newJoint.jointDynamics = jointDynamics;
		}

		if (val->limits.has_value())
		{
			JointLimits jointLimits;
			jointLimits.effort = val->limits.value()->effort;
			jointLimits.velocity = val->limits.value()->velocity;
			jointLimits.lower = val->limits.value()->lower;
			jointLimits.upper = val->limits.value()->upper;
			newJoint.jointLimit = jointLimits;
		}

		if(val->mimic.has_value())
		{
			JointMimic jointMimic;
			jointMimic.offset = val->mimic.value()->offset;
			jointMimic.jointName = val->mimic.value()->joint_name;
			jointMimic.offset = val->mimic.value()->offset;
			newJoint.jointMimic = jointMimic;
		}

		if(val->safety.has_value())
		{
			JointSafety jointSafety;
			jointSafety.k_position = val->safety.value()->k_position;
			jointSafety.k_velocity = val->safety.value()->k_velocity;
			jointSafety.lower_limit = val->safety.value()->lower_limit;
			jointSafety.upper_limit = val->safety.value()->upper_limit;
			newJoint.jointSafety = jointSafety;
		}

		newJoint.type = val->type;
		jointMap[val->name] = &newJoint;
	}
}


void Editor::UI2()
{
	ImGui::Begin("Components");

	if(selectedShape != nullptr)
	{
		float p[3] = { 0, 0, 0 };

		//Position
		p[0] = gizmosTransform->translation.x;
		p[1] = gizmosTransform->translation.y;
		p[2] = gizmosTransform->translation.z;

		ImGui::InputFloat3("Position", p);

		selectedShape->trans.x = p[0];
		selectedShape->trans.y = p[1];
		selectedShape->trans.z = p[2];

		gizmosTransform->translation.x = p[0];
		gizmosTransform->translation.y = p[1];
		gizmosTransform->translation.z = p[2];


		//scale
		p[0] = gizmosTransform->scale.x;
		p[1] = gizmosTransform->scale.y;
		p[2] = gizmosTransform->scale.z;

		ImGui::InputFloat3("Scale", p);

		selectedShape->scale.x = p[0];
		selectedShape->scale.y = p[1];
		selectedShape->scale.z = p[2];

		gizmosTransform->scale.x = p[0];
		gizmosTransform->scale.y = p[1];
		gizmosTransform->scale.z = p[2];


		//rotation
		p[0] = gizmosTransform->rotation.x;
		p[1] = gizmosTransform->rotation.y;
		p[2] = gizmosTransform->rotation.z;

		ImGui::InputFloat3("Rotation", p);

		selectedShape->rot.x = p[0];
		selectedShape->rot.y = p[1];
		selectedShape->rot.z = p[2];

		gizmosTransform->rotation.x = p[0];
		gizmosTransform->rotation.y = p[1];
		gizmosTransform->rotation.z = p[2];
		
	}

	ImGui::End();
}