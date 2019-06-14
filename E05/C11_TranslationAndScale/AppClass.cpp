#include "AppClass.h"
#include <list>
#include <vector>
#include <iostream>
using namespace std;

void Application::InitVariables(void)
{
	
	for (int i = 0; i < 46; i++)
	{
		m_pMesh = new MyMesh();
		meshVector.push_back(m_pMesh);
		meshVector[i]->GenerateCube(1.0f, C_PURPLE);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	//matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(1.0f, 1.0f, 1.0f));
	
	//matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 2.0f, 3.0f));
	//value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	//matrix4 m4Model = m4Scale * m4Translate;
	static float value[11] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11};
	//meshVector[1]->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, vector3(4.0f, 4.0f, 3.0f)));
	vector<vector3> cubeVectors;
	cubeVectors.push_back(vector3(value[8],5.0f,3.0f));
	cubeVectors.push_back(vector3(value[2],5.0f,3.0f));
	cubeVectors.push_back(vector3(value[7],4.0f,3.0f));
	cubeVectors.push_back(vector3(value[3],4.0f,3.0f));
	cubeVectors.push_back(vector3(value[8],3.0f,3.0f));
	cubeVectors.push_back(vector3(value[7],3.0f,3.0f));
	cubeVectors.push_back(vector3(value[6],3.0f,3.0f));
	cubeVectors.push_back(vector3(value[5],3.0f,3.0f));
	cubeVectors.push_back(vector3(value[4], 3.0f, 3.0f));
	cubeVectors.push_back(vector3(value[3], 3.0f, 3.0f));
	cubeVectors.push_back(vector3(value[2], 3.0f, 3.0f));
	cubeVectors.push_back(vector3(value[9], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[8], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[6],2.0f,3.0f));
	cubeVectors.push_back(vector3(value[5], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[4], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[2], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[1], 2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[10],1.0f,3.0f));
	cubeVectors.push_back(vector3(value[9], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[8],1.0f,3.0f));
	cubeVectors.push_back(vector3(value[7], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[6],1.0f,3.0f));
	cubeVectors.push_back(vector3(value[5], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[4],1.0f,3.0f));
	cubeVectors.push_back(vector3(value[3],1.0f,3.0f));
	cubeVectors.push_back(vector3(value[2], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[1], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[0], 1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[10], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[10],-1.0f,3.0f));
	cubeVectors.push_back(vector3(value[8], -1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[8],-0.0f,3.0f));
	cubeVectors.push_back(vector3(value[7], -0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[6], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[5], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[4], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[3], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[2], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[0], 0.0f, 3.0f));
	cubeVectors.push_back(vector3(value[7], -2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[6], -2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[2], -1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[0], -1.0f, 3.0f));
	cubeVectors.push_back(vector3(value[3], -2.0f, 3.0f));
	cubeVectors.push_back(vector3(value[4], -2.0f, 3.0f));
	for (int i = 0; i < 11; i++)
	{
		value[i] += 0.01f;
	}
	
	//m_pMesh->Render(m4Projection, m4View, m4Model);
	for (int i = 0; i < 46; i++)
	{
		meshVector[i]->Render(m4Projection,m4View,glm::translate(IDENTITY_M4,cubeVectors[i]));
	}

	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
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
	for(int i = 0; i < 46; i++)
	SafeDelete(meshVector[i]);

	//release GUI
	ShutdownGUI();
}