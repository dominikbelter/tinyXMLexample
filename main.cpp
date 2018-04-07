/** @file main.cpp
 *
 * This example shows how to use 3rdParty tinyXML2 library
 *
 * @author Dominik Belter
 */


#include "3rdParty/tinyXML/tinyxml2.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    try {
        tinyxml2::XMLDocument config;
        std::string configXML("../../resources/configGlobal.xml");
        config.LoadFile(configXML.c_str());
        if (config.ErrorID())
            std::cout << "unable to load config file.\n";
        tinyxml2::XMLElement* robotParams = config.FirstChildElement( "Robot" );
        std::string robotType(robotParams->FirstChildElement("type")->GetText());
        std::string robotConfig(robotParams->FirstChildElement("config")->GetText());

        std::cout << "Robot type: " << robotType << "\n";
        std::cout << "Robot config file: " << robotConfig << "\n";

        int legsNo;
        robotParams->FirstChildElement("parameters")->QueryIntAttribute("legsNo",&legsNo);
        std::cout << "Legs no: " << legsNo << "\n";
        double mass;
        robotParams->FirstChildElement("parameters")->QueryDoubleAttribute("mass",&mass);
        std::cout << "Mass of the robot: " << mass << "\n";

        double newMass(0.0);
        std::cout << "Insert new mass:\n";
        std::cin >> newMass;
        robotParams->FirstChildElement("parameters")->SetAttribute("mass",newMass);
        config.SaveFile(configXML.c_str());
    }
	catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
