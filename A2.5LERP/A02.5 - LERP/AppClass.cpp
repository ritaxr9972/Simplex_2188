#include "AppClass.h"
#include <math.h>
#define M_PI 3.14159265358979323846;
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Akshat Rawat - axr9972@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits
	float fRadius = 0.95f;
	
	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	float doublePI = 2.0f * M_PI;
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		std::vector<vector3> stopslist;//add a list of stops
		for (int j = 0; j < i; j++)
		{
			stopslist.push_back(vector3(fRadius * cos(j * doublePI / i), fRadius * sin(j * doublePI / i),0));
		}
		fSize += 0.5f; //increment the size for the next orbit
		fRadius += 0.5f;
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
		
		stops.push_back(stopslist);//populate the vector with lists of stop positions
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	//m4Offset = glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z);
	
	static uint routeCounter = 0;
	// draw a shapes
	for (uint i = 0; i < m_uOrbits; i++)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 1.5708f, AXIS_X));
		//Get a timer
		static float fTimer = 0;	//store the new timer
		static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
		fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer
		float fTimeBetweenStops = 2.0;//in seconds
		//map the value to be between 0.0 and 1.0
		float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);
	
		//calculate the current position
		vector3 v3CurrentPos;
		vector3 v3StartPos;
		vector3 v3EndPos;
		
		if (routeCounter < stops[i].size() - 1)
		{
			v3StartPos = stops[i][routeCounter];
			v3EndPos = stops[i][routeCounter + 1];
		}
		else
		{
			v3StartPos = stops[i][stops[i].size() - 1];
			v3EndPos = stops[i][0];
		}

		v3CurrentPos = glm::lerp(v3StartPos, v3EndPos, fPercentage);
		if (fPercentage >= 1.0f)
		{
			routeCounter++;
			fTimer = m_pSystem->GetDeltaTime(uClock);
			routeCounter %= stops[stops.size()-1].size() - 1;
		}

		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);

		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.1)), C_WHITE);
	}
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}