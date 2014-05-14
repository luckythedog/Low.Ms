/*******************************************************************
 * Application: Low.Ms
 * Version: 1.0 (Initial Build)
 * Changelog:
 * -Added
 *******************************************************************/
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
/*LowMs include*/
#include "LMSCloud.h"
#include "LMSCore.h"
#include "LMSCloudHeavy.h"
#include "LMSCloudLight.h"
#include "LMSCloudData.h"

/*Global variables*/
char* g_szIp[16];
char* g_uiPort;

class LMSCloud;
class LMSCloudHeavy;
class LMSCloudLight;
class LMSCloudData;
class LMSCore;

int main(int argc, char* argv[]) {
	/*Create a boolean to check if it is a valid address*/
	bool bCoreReady = false;
	LMSCore coreNew; /*Use default path*/
	bCoreReady = coreNew.LoadConfig();
	if(!bCoreReady) return 1;

	printf("1 - Run a Cloud with a Unique ID\n");
	printf("2 - Create a Cloud\n");
	printf("3 - Exit Low.Ms\n");
	unsigned int uiChoice;
	std::cin >> uiChoice;
	if(uiChoice == 1){
		printf("Enter the Cloud's Unique ID: ");
		std::string strUniqueId;
		std::cin >> strUniqueId;
		printf("\n");
		CloudType typeCloud;
		if((typeCloud = coreNew.GetCloudType(strUniqueId))){
			printf("Found Cloud with Unique ID!");

			if(typeCloud == HeavyCloud){
				LMSCloudHeavy cloudHeavy(strUniqueId);
				cloudHeavy.Start();
				while(cloudHeavy.Alive());
			}
			if(typeCloud == LightCloud){
				LMSCloudLight cloudLight(strUniqueId);
				cloudLight.Start();
				while(cloudLight.Alive());
			}
			if(typeCloud == DataCloud){
				LMSCloudData cloudData(strUniqueId);
				cloudData.Start();
				while(cloudData.Alive());

			}
		}else{

			return 1;
		}

	}
	if(uiChoice == 2){
		unsigned int uiCloudTypeChoice;
		printf("1 - Heavy Cloud\n");
		printf("2 - Light Cloud\n");
		printf("3 - Data Cloud\n");
		std::cin >> uiCloudTypeChoice;
		if(uiCloudTypeChoice < 1 || uiCloudTypeChoice > 3){
			printf("Invalid Cloud Type");
			return 1;
		}
		std::string strIpChoice;
		unsigned int uiPort;
		printf("Enter IP Address desired: ");
		std::cin >> strIpChoice;
		printf("\nEnter Port Number desired: ");
		std::cin >> uiPort;

		std::string strHeavyUniqueID;
		std::string strHeavyIp;
		unsigned int uiHeavyPort;
		bool LinkedToHeavy = false;
		if(uiCloudTypeChoice == 1){
			LMSCloudHeavy cloudHeavy(strIpChoice, uiPort);
			cloudHeavy.Start();
			while(cloudHeavy.Alive()){
				printf("Heavy Clouds need to link up with Light Clouds and Data Clouds\n");
				printf("They provide relaying services and client directory.\n");
				printf("However there are no Light Cloud or Data Cloud servers in your list!\n");
				printf("Enter an IP Address (for a Light or Data Cloud): ");
				std::cin >> strHeavyIp;
				printf("\nEnter a Port Number: ");
				std::cin >> uiHeavyPort;
				printf("Seems like no Light or Data Cloud is responding.\n");
				printf("Try entering a Unique ID associated with a Light or Data Cloud: ");
				std::cin >> strHeavyUniqueID;
				coreNew.GetLightCloud(strHeavyUniqueID);
			}
		}
		if(uiCloudTypeChoice == 2){
			LMSCloudLight cloudLight(strIpChoice, uiPort);
			cloudLight.Start();
			while(cloudLight.Alive()){
				if(!LinkedToHeavy){
					printf("Light Clouds need to link up to a Heavy Cloud");
					printf("Enter an IP Address (for Heavy Cloud): ");
					std::cin >> strHeavyIp;
					printf("\nEnter Port Number: ");
					std::cin >> uiHeavyPort;
				}
				LinkedToHeavy = cloudLight.SetHeavyCloud(strHeavyIp, uiHeavyPort);
				if(!LinkedToHeavy){
					printf("No Heavy Cloud responded at that address\n");
					printf("You can use a UniqueID to connect to a Heavy Cloud\n");
					printf("Enter a Unique ID associated with a Heavy Cloud: ");
					std::cin >> strHeavyUniqueID;
					coreNew.GetHeavyCloud(strHeavyUniqueID);
				}
			}
		}
		if(uiCloudTypeChoice == 3){
			LMSCloudData cloudData(strIpChoice, uiPort);
			cloudData.Start();

			while(cloudData.Alive()){
				if(!LinkedToHeavy){
					printf("Data Clouds need to link up to a Heavy Cloud");
					printf("Enter an IP Address (for Heavy Cloud): ");
					std::cin >> strHeavyIp;
					printf("\nEnter Port Number: ");
					std::cin >> uiHeavyPort;
				}
				LinkedToHeavy = cloudData.SetHeavyCloud(strHeavyIp, uiHeavyPort);
				if(!LinkedToHeavy){
					printf("No Heavy Cloud responded at that address\n");
					printf("You can use a UniqueID to connect to a Heavy Cloud\n");
					printf("Enter a Unique ID associated with a Heavy Cloud: ");
					std::cin >> strHeavyUniqueID;
					coreNew.GetHeavyCloud(strHeavyUniqueID);
				}
			}
		}

	}
	return 0;
	}

