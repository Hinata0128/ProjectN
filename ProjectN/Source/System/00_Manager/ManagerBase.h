#pragma once

/******************************************************************
*	�}�l�[�W���[�x�[�X�N���X.
**/

class ManagerBase
{
public:
	ManagerBase() {};
	virtual ~ManagerBase() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Create() {};
	virtual void Release() {};

protected:

};
