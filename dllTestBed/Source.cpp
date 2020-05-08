#include <iostream>
#include "HumanHead.h"
using namespace std;


int main(int argc, char** argv)
{
	try
	{
		cout << "\nHello dllTestBed!" << endl;
		int cam = 0;
		IHumanHeadDetection *m_LandmarkDetection;
		m_LandmarkDetection = (IHumanHeadDetection*)CreateHumanDetection();
		cout << "Hit enter to CreateFR_AICentral..." << endl;
		cin.get();
		m_LandmarkDetection->CreateFR_AICentral(cam);
		cout << "Hit enter to exit..." << endl;
		cin.get();
	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}

