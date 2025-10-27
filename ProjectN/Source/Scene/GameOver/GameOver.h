#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

/*********************************************
*	�Q�[���I�[�o�[�摜�N���X.
**/

class GameOver
	: public CSceneBase
{
public:
	GameOver();
	~GameOver() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

private:
};