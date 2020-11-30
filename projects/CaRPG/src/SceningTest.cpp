#include "SceningTest.h"
#include "Cars.h"
#include "Obstacles.h"

int start = 0;

SceningTest::SceningTest(GLFWwindow* inWind)
{
	window = inWind;
}

void SceningTest::Start()
{

	camera = Camera::Create();
	std::string fileName = "monkey.obj";
	entt::entity testModel = m_Registry.create();
	entt::entity shader = m_Registry.create();
	entt::entity Car = m_Registry.create();
	entt::entity EnemyCar = m_Registry.create();
	entt::entity Track = m_Registry.create();
	entt::entity Obstacle = m_Registry.create();
	//cards
	m_Card = m_Registry.create();

	entt::entity morphTest = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(morphTest);
	m_Registry.emplace<syre::Texture>(morphTest, "Car2.png");
	m_Registry.emplace<syre::Transform>(morphTest, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("morph01.obj");
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("morph02.obj");
	


	m_Registry.emplace<syre::Mesh>(Track, "Track1.obj");
	m_Registry.emplace<syre::Transform>(Track, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(Track, "PossibleRoad.png");

	m_Registry.emplace<Obstacles>(Obstacle);

	m_Shader = shader;
	m_PCar = Car;
	m_Obstacle = Obstacle;
	m_ECar = EnemyCar;
	
	m_Registry.emplace<Cars>(Car);
	m_Registry.emplace<syre::Mesh>(Car, "Car2.obj");
	m_Registry.emplace<syre::Transform>(Car, glm::vec3(6.0f, 0.0f, 0.0f),glm::vec3(90.f,0.0f,0.0f),glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(Car, "Car2.png");
	m_Registry.emplace<syre::PathAnimator>(Car,syre::PathType::BEZIER);
	auto& carPath = m_Registry.get<syre::PathAnimator>(Car);

	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(10.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of first turn
	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of 2nd straight 
	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -85.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 2nd turn 
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 3rd str 
	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(145.0f, -247.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(205.0f, -247.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //mid s  
	carPath.AddPoint(glm::vec3(205.0f, -247.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(235.0f, -230.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of S 
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of str
	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(240.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //mid u turn
	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(151.f, -466.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //end u turn
	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(164.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //end turn 
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //str
	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(24.f, -370.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //turn
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //str
	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(20.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid s 
	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-73.f, -490.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end s 
	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-64.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-148.f, -580.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //end u turn 
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //str
	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-138.f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(90.0f, 0.0f, -280.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-70.f, -360.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end u 
	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-76.f, -448.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-56.f, -448.f, 0.0f), glm::vec3(90.0f, 0.0f, 80.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-56.f, -448.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-9.f, -460.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //end u 
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //str
	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(30.f, -310.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(90.0f, 0.0f, 260.0f)); //turn 
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 265.0f)); //str
	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-133.f, -285.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); // mid u 
	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-147.f, -219.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //end u 
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //str
	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(15.f, -220.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); //mid u
	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(16.f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //end u
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //str
	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-150.f, -133.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //turn ///////
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, 175.0f)); //str
	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-125.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //mid u////////////
	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-220.f, 13.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //end u ///////
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(90.0f, 0.0f, 337.0f)); //str
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.SpeedControl();


	m_Registry.emplace<Cars>(EnemyCar);
	m_Registry.emplace<syre::Mesh>(EnemyCar, "Car2.obj");
	m_Registry.emplace<syre::Transform>(EnemyCar, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(EnemyCar, "Car2.png");
	m_Registry.emplace<syre::PathAnimator>(EnemyCar, syre::PathType::BEZIER);
	auto& enemyCarPath = m_Registry.get<syre::PathAnimator>(EnemyCar);

	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(14.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of first turn
	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(110.0f, -97.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of 2nd straight 
	enemyCarPath.AddPoint(glm::vec3(110.0f, -97.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(159.0f, -81.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 2nd turn 
	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(159.0f, -205.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 3rd str 
	enemyCarPath.AddPoint(glm::vec3(159.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(149.0f, -243.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(205.0f, -243.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //mid s  
	enemyCarPath.AddPoint(glm::vec3(205.0f, -243.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(235.0f, -230.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of S 
	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(240.f, -420.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of str
	enemyCarPath.AddPoint(glm::vec3(240.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(244.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));            ///////

	enemyCarPath.AddPoint(glm::vec3(198.f, -462.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //mid u turn
	enemyCarPath.AddPoint(glm::vec3(198.f, -462.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(151.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(157.f, -416.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //end u turn
	enemyCarPath.AddPoint(glm::vec3(157.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(160.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //end turn 
	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(63.f, -377.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(63.f, -377.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(28.f, -374.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));      ////////

	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(20.f, -470.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(20.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(24.f, -503.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-26.f, -506.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid s
	enemyCarPath.AddPoint(glm::vec3(-26.f, -506.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-77.f, -495.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-68.f, -537.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end s
	enemyCarPath.AddPoint(glm::vec3(-68.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-60.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));   ///

	enemyCarPath.AddPoint(glm::vec3(-114.f, -574.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-114.f, -574.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-152.f, -582.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //end u turn 
	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));    /////

	enemyCarPath.AddPoint(glm::vec3(-134.f, -393.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-134.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-142.f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-88.f, -361.f, 0.0f), glm::vec3(90.0f, 0.0f, -280.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-88.f, -361.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-64.f, -356.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-70.f, -405.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-70.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-72.f, -450.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-56.f, -444.f, 0.0f), glm::vec3(90.0f, 0.0f, 80.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-56.f, -444.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-11.f, -456.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-3.5f, -346.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-3.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(26.f, -310.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));   /////////

	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(90.0f, 0.0f, 260.0f)); //turn 
	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  /////

	enemyCarPath.AddPoint(glm::vec3(-117.f, -290.f, 0.0f), glm::vec3(90.0f, 0.0f, 265.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-117.f, -290.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-131.f, -287.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  ///

	enemyCarPath.AddPoint(glm::vec3(-137.f, -252.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); // mid u 
	enemyCarPath.AddPoint(glm::vec3(-137.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-149.f, -219.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-34.f, -206.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-34.f, -206.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(15.f, -216.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(4.f, -160.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); //mid u
	enemyCarPath.AddPoint(glm::vec3(4.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(12.f, -122.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-108.f, -133.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-108.f, -133.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-150.f, -137.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  //////////

	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //turn 
	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-149.f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, 175.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-149.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-129.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-195.f, 10.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //mid u
	enemyCarPath.AddPoint(glm::vec3(-195.f, 10.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-216.f, 9.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(90.0f, 0.0f, 337.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.SpeedControl();

	//cards

	m_Registry.emplace<syre::Mesh>(m_Card, "Card.obj");
	m_Registry.emplace<syre::Transform>(m_Card, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(m_Card, "NO2.png");



	cardTextures.push_back(syre::Texture("NO2.png"));
	cardTextures.push_back(syre::Texture("Drift.png"));
	cardTextures.push_back(syre::Texture("Slipstream.png"));
	cardTextures.push_back(syre::Texture("Muffler.png"));

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();




	m_Registry.emplace<Shader::sptr>(shader);

	auto& shaderComponent = m_Registry.get<Shader::sptr>(shader);
	shaderComponent = Shader::Create();
	shaderComponent->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderComponent->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
	shaderComponent->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     lightAmbientPow = 0.1f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.5f;
	float     shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	shaderComponent->SetUniform("u_LightPos", lightPos);
	shaderComponent->SetUniform("u_LightCol", lightCol);
	shaderComponent->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shaderComponent->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shaderComponent->SetUniform("u_AmbientCol", ambientCol);
	shaderComponent->SetUniform("u_AmbientStrength", ambientPow);
	shaderComponent->SetUniform("u_Shininess", shininess);


	morphShader = Shader::Create();
	morphShader->LoadShaderPartFromFile("morph_vertex_shader.glsl", GL_VERTEX_SHADER);
	morphShader->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
	morphShader->Link();

	lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	lightAmbientPow = 0.1f;
	lightSpecularPow = 1.0f;
	ambientCol = glm::vec3(1.0f);
	ambientPow = 0.5f;
	shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	morphShader->SetUniform("u_LightPos", lightPos);
	morphShader->SetUniform("u_LightCol", lightCol);
	morphShader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	morphShader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	morphShader->SetUniform("u_AmbientCol", ambientCol);
	morphShader->SetUniform("u_AmbientStrength", ambientPow);
	morphShader->SetUniform("u_Shininess", shininess);
	
	auto& camComponent = camera;
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);


	lastFrame = glfwGetTime();
}

void SceningTest::Update()
{
	thisFrame = glfwGetTime();
	float deltaTime = thisFrame - lastFrame;
	auto& camComponent = camera;
	auto& shaderComponent = m_Registry.get<Shader::sptr>(m_Shader);
	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	auto& EnemyComponent = m_Registry.get<Cars>(m_ECar);
	int temp;
	if (start == 0)
	{
		start += 1;
		obstacleComponent.Draw();
	}
	glm::vec3 camX = glm::cross(camComponent->GetForward(), camComponent->GetUp());
	KeyEvents(deltaTime);
	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.13f)));
	flatShader->SetUniform("aspect", camera->GetAspect());
	for (int i = 0; i <= 4; i++)
	{
		int cardVal = PlayerComponent.GetCard(i, true);
		if (cardVal != -1)
		{
			flatShader->SetUniform("offset", glm::vec2(-0.2f+i/3.8f, -.62f));
			cardTextures[cardVal].Bind();
			m_Registry.get<syre::Mesh>(m_Card).Render();
		}
		
	}
	if (PlayerComponent.GetAction1() != -1 && PlayerComponent.GetAction2() != -1)
	{
		obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear());
		if (PlayerComponent.GetAction1() == 2 || PlayerComponent.GetAction2() == 2)
		{
			temp = PlayerComponent.GetGear();
			PlayerComponent.ChangeGears(EnemyComponent.GetGear());
			EnemyComponent.ChangeGears(temp);
		}
		if (EnemyComponent.GetAction1() == 2 || EnemyComponent.GetAction2() == 2)
		{
			temp = EnemyComponent.GetGear();
			EnemyComponent.ChangeGears(PlayerComponent.GetGear());
			PlayerComponent.ChangeGears(temp);
		}
		obstacleComponent.Draw();
		//TODO: Change the Segment index and speed
		PlayerComponent.ResetTurn();
		EnemyComponent.ResetTurn();

	}
	auto pathView = m_Registry.view<syre::PathAnimator, syre::Transform>();
	for (auto entity : pathView)
	{
		auto& transform = m_Registry.get<syre::Transform>(entity);
		m_Registry.get<syre::PathAnimator>(entity).Update(transform, deltaTime);
	}


	shaderComponent->Bind();
	shaderComponent->SetUniform("u_CamPos", camComponent->GetPosition());
	auto renderView = m_Registry.view<syre::Mesh,syre::Transform,syre::Texture>();
	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		shaderComponent->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		shaderComponent->SetUniformMatrix("u_Model", transform);
		shaderComponent->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}
	auto morphRenderView = m_Registry.view<syre::MorphRenderer, syre::Transform, syre::Texture>();
	morphShader->Bind();
	for (auto entity : morphRenderView)
	{
		float t = morphRenderView.get<syre::MorphRenderer>(entity).Update(deltaTime);
		glm::mat4 transform = morphRenderView.get<syre::Transform>(entity).GetModelMat();
		morphShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		morphShader->SetUniformMatrix("u_Model", transform);
		morphShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		morphShader->SetUniform("t", t);
		morphRenderView.get<syre::Texture>(entity).Bind();
		morphRenderView.get<syre::MorphRenderer>(entity).Render();
	}
	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 3.0f, 3.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));

	lastFrame = thisFrame;
}

void SceningTest::ImGUIUpdate()
{
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
		// Implementation new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui context new frame
		ImGui::NewFrame();

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff
			

			auto movable = m_Registry.view<syre::Mesh, syre::Transform>();
			auto& camComponent = camera;
			glm::vec3 camPos = camComponent->GetPosition();
			if (ImGui::Button(manualCamera?"Auto Camera": "Manual Camera"))
			{
				manualCamera = !manualCamera;
			}
			if (manualCamera)
			{
				ImGui::SliderFloat3("Camera Position", &camPos.x,-200.f, 200.f);
			}
			camComponent->SetPosition(camPos);
			ImGui::End();
		}

		// Make sure ImGui knows how big our window is
		ImGuiIO& io = ImGui::GetIO();
		int width{ 0 }, height{ 0 };
		glfwGetWindowSize(window, &width, &height);
		io.DisplaySize = ImVec2((float)width, (float)height);

		// Render all of our ImGui elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			// Update the windows that ImGui is using
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			// Restore our gl context
			glfwMakeContextCurrent(window);
		}
	
}

Camera::sptr& SceningTest::GetCam()
{
	// TODO: insert return statement here
	return camera;
}

void SceningTest::KeyEvents(float delta)
{
	auto& camComponent = camera;
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	auto& EnemyComponent = m_Registry.get<Cars>(m_ECar);
	int temp;
	glm::vec3 curCamPos = camComponent->GetPosition();
	glm::vec3 curCamFor = camComponent->GetForward();

	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	{
		curCamPos.x += 10.f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		curCamPos.x -= 10.f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		curCamPos.y -= 10.f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		curCamPos.y += 10.f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		curCamFor.x += 0.1f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		curCamFor.x -= 0.1f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		curCamFor.y -= 0.1f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		curCamFor.y += 0.1f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		PlayerComponent.Draw();
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double* x = new double;
		double* y = new double;

		glfwGetCursorPos(window, x,y);
		//printf("Mouse at X %f Y %f\n", *x, *y);
		for (float i = 0; i <= 5; i++)
		{
			if ((i * 165) + 429 <= *x && (i + 1) * 165 + 429 >= *x && *y >= 457 && *y <= 706 && PlayerComponent.GetCard(i, true) != -1)
			{
				if (PlayerComponent.GetCard(i, true) == 1)
				{
					temp = PlayerComponent.GetGear();
					PlayerComponent.PlayCard(i, EnemyComponent.GetGear());
					EnemyComponent.ChangeGears(temp);
				}
				else
				{
					PlayerComponent.PlayCard(i, 0);
				}
			}
		}
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Reset();
	}
	camComponent->SetPosition(curCamPos);
}

