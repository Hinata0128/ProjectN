#pragma once
#include "GameObject//StaticMeshObject//StaticMeshObject.h"

class StaticMeshMnager;

/******************************************************************
*	�|�[�^���N���X.
**/

class Portal final
	: public StaticMeshObject
{
public:
	Portal();
	~Portal() override;

	void Update() override;
	void Draw() override;

private:

};