#pragma once
#include"SceneParent.h"
#include <cstdlib>
#include <ctime>
class SceningTest:
	public syre::SceneParent
{
public:
	SceningTest(GLFWwindow* inWind);
	void Start();
	int Update();
	int PausedUpdate();
	void ImGUIUpdate();
	Camera::sptr& GetCam();
private:
	void KeyEvents(float delta);
	Camera::sptr camera;
	entt::entity m_PCar;
	entt::entity m_enemy;
	entt::entity m_Obstacle;
	entt::entity m_Card;
	entt::entity m_Hazard;
	entt::entity m_Gearbox;
	entt::entity m_GearboxLever;
	entt::entity m_Accelerometer;
	entt::entity m_Needle;
	entt::entity m_Particles1;
	entt::entity m_Particles2;
	entt::entity m_TransparentBlack;


	std::vector<syre::Texture> cardTextures;
	std::vector<syre::Texture> hazardTextures;
	std::vector<syre::Texture> gearboxTextures;
	std::vector<syre::Texture> accelerometerTextures;

	Shader::sptr basicShader;
	Shader::sptr flatShader;
	Shader::sptr morphShader;
	Shader::sptr flatMorphShader;
	bool manualCamera = false;
	float Elapsedtime = 0;
	bool lbutton_down = false;
	bool speedDemon = true;
	bool showGear = false;
	bool isPaused = false;
	bool escRelease = false;
};