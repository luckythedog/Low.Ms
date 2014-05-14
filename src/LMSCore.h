/*
 * LMSCore.h
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#ifndef LMSCORE_H_
#define LMSCORE_H_
#include <string>
#include <map>
#include <libgen.h>
#include "LMSCloud.h"
#include "LMSCloudHeavy.h"
#include "LMSCloudLight.h"
#include "LMSCloudData.h"
#include <fstream>
#define DEFAULT_PATH_TO_CONFIG "/config"

class LMSCore{
public:
	LMSCore(){
		m_strPathToConfig = DEFAULT_PATH_TO_CONFIG;
		LoadConfig();
	}
	LMSCore(std::string strPathToConfig){
		m_strPathToConfig = strPathToConfig;
		LoadConfig();
	}

	~LMSCore(){

	}
	bool SetDefault(){
		bLoaded = false;
		if(m_mapEventsAndScripts.size() != 0) m_mapEventsAndScripts.clear();
		if(m_rgHeavyCloudsDefault.size() != 0) m_rgHeavyCloudsDefault.clear();
		if(m_rgHeavyCloudsDefault.size() != 0) m_rgLightCloudsDefault.clear();
		if(m_rgHeavyCloudsDefault.size() != 0) m_rgDataCloudsDefault.clear();

		m_uiHeavyCloudsCount = 0;
		m_uiLightCloudsCount = 0;
		m_uiDataCloudsCount = 0;

		for(unsigned int i=0; i<10; i++){
			LMSDataRange invalidRange;
			invalidRange.m_uiStart = 255;
			invalidRange.m_uiEnd = 255;
			m_rgDataRangeAndDataCloud[i] = invalidRange;
		}
		return true;
	}
	bool LoadConfig(){
		SetDefault();
		if(!bLoaded){
			WriteConsole("Loading Config..");
			bLoaded = true;
		}
		if(bLoaded) {
			WriteConsole("Verifying Config..");
			bLoaded = VerifyConfig();
		}else{
			WriteConsole("Error loading Config. Make sure your file paths are correct.");
		}
		return bLoaded;
	}
	bool WriteConsole(std::string strMessage){
		printf("[CORE] %s", strMessage.c_str());
		return true;
	}
	std::string FindScriptForEvent(std::string strEvent){
		if(bLoaded){
			return m_mapEventsAndScripts[strEvent];
		}else{
			WriteConsole("Config has not been loaded up yet!");
		}
		return "";
	}
	bool AddEventAndScript(std::string strEvent, std::string strScript){
		m_mapEventsAndScripts[strEvent] = strScript;
		WriteConsole("Event " + strEvent + " has been attached to script " + strScript);
		return true;
	}
	bool AddHeavyCloud(std::string strUniqueId, std::string strIp, unsigned int uiPort, unsigned int uiAllowedTotalConnections){
		LMSCloudHeavy heavyNewCloud(strIp, uiPort);
		heavyNewCloud.SetUniqueId(strUniqueId);
		heavyNewCloud.SetAllowedTotalConnections(uiAllowedTotalConnections);
		m_rgHeavyCloudsDefault[strUniqueId] = heavyNewCloud;
		m_uiHeavyCloudsCount++;
		AddCloudType(strUniqueId, HeavyCloud);
		return true;
	}
	LMSCloudHeavy GetHeavyCloud(std::string strUniqueId){
		if(AllowedToTouch()){
			if(m_rgHeavyCloudsDefault.find(strUniqueId) != m_rgHeavyCloudsDefault.end()) return m_rgHeavyCloudsDefault[strUniqueId];
		}
		WriteConsole("Could not find Heavy Cloud with that Unique ID!");
		LMSCloudHeavy cNoReturn;
		return cNoReturn;
	}

	bool AddLightCloud(std::string strUniqueId, std::string strIp, unsigned int uiPort, unsigned int uiAllowedConnections){
		LMSCloudLight lightNewCloud(strIp, uiPort);
		lightNewCloud.SetUniqueId(strUniqueId);
		lightNewCloud.SetAllowedConnections(uiAllowedConnections);
		m_rgLightCloudsDefault[strUniqueId] = lightNewCloud;
		m_uiLightCloudsCount++;
		AddCloudType(strUniqueId, LightCloud);
		return true;
	}
	LMSCloudLight GetLightCloud(std::string strUniqueId){
		if(AllowedToTouch()){
			if(m_rgLightCloudsDefault.find(strUniqueId) != m_rgLightCloudsDefault.end()) return m_rgLightCloudsDefault[strUniqueId];
		}
		WriteConsole("Could not find Light Cloud with that Unique ID!");
		LMSCloudLight cNoReturn;
		return cNoReturn;
	}

	bool AddDataCloud(std::string strUniqueId, std::string strIp, unsigned int uiPort, std::string strPathToLocalDatabase, LMSDataRange dataRange){
		LMSCloudData dataNewCloud(strIp, uiPort);
		dataNewCloud.SetLocalPathToDatabase(strPathToLocalDatabase);
		dataRange.m_strAssignedToDataCloud = strUniqueId;
		AddCloudType(strUniqueId, DataCloud);
		AddDataRange(dataRange);
		return true;
	}
	bool AddDataRange(LMSDataRange dataRange){
		if(dataRange.m_uiStart < 1 || dataRange.m_uiStart > 9){
			WriteConsole("Data Range's Start must be a number between 1-9");
			return false;
		}
		if(dataRange.m_uiEnd < 1 || dataRange.m_uiEnd > 9){
			WriteConsole("Data Range's End must be a number between 1-9");
			return false;
		}
		if(dataRange.m_uiStart == dataRange.m_uiEnd){
			m_rgDataRangeAndDataCloud[dataRange.m_uiStart-1] = dataRange;
			return true;
		}
		if(dataRange.m_uiStart > dataRange.m_uiEnd){
			WriteConsole("Data Range's Start must be lower or equal to its End. It has to be in ascending order");
			return false;
		}

		unsigned int uiStart = dataRange.m_uiStart;
		unsigned int uiSteps = dataRange.m_uiStart - dataRange.m_uiEnd;
		do{
			m_rgDataRangeAndDataCloud[uiStart-1] = dataRange;
			uiStart++;
			uiSteps--;
		}while(uiSteps!=0);

		/*Maybe get rid of this*/
		return true;

	}
	LMSCloudData GetDataCloud(std::string strUniqueId){
		if(AllowedToTouch()){
			if(m_rgDataCloudsDefault.find(strUniqueId) != m_rgDataCloudsDefault.end()) return m_rgDataCloudsDefault[strUniqueId];
		}
		WriteConsole("Could not find Data Cloud with that Unique ID!");
		LMSCloudData cNoReturn;
		return cNoReturn;
	}
	bool AddCloudType(std::string strUniqueId, CloudType typeCloud){
		m_rgCloudType[strUniqueId] = typeCloud;
		return true;
	}
	CloudType GetCloudType(std::string strUniqueId){
		if(m_rgHeavyCloudsDefault.find(strUniqueId) != m_rgHeavyCloudsDefault.end()) return m_rgHeavyCloudsDefault[strUniqueId].GetCloudType();
		if(m_rgLightCloudsDefault.find(strUniqueId) != m_rgLightCloudsDefault.end()) return m_rgLightCloudsDefault[strUniqueId].GetCloudType();
		if(m_rgDataCloudsDefault.find(strUniqueId) != m_rgDataCloudsDefault.end()) return m_rgDataCloudsDefault[strUniqueId].GetCloudType();
		WriteConsole("Cannot find Cloud Type because Unique ID does not exist!");
		return NoneCloud;
	}
	bool AllowedToTouch(){
		if(IsLoaded()) return true;
		WriteConsole("Core has not been loaded. Please try to load config again");
		return false;
	}
	bool IsLoaded(){
		return bLoaded;
	}
	bool VerifyConfig(){
		if(!CheckClouds()) return false;
		if(!CheckKeys()) return false;
		WriteConsole("Config has been loaded and verified.");
		return true;
	}
	bool CheckClouds(){
		bool bCloudsValid = true;
		std::vector<std::string> rgstrUniqueId;
		std::vector<std::string> rgstrIp;
		std::vector<unsigned int> rguiPort;
		unsigned int uiLengthOfArrays = 0;

		LMSCloudHeavy* ptrHeavyCloud;
		std::map<std::string, LMSCloudHeavy>::iterator itHeavyCloud;
		LMSCloudLight* ptrLightCloud;
		std::map<std::string, LMSCloudLight>::iterator itLightCloud;
		LMSCloudData* ptrDataCloud;
		std::map<std::string, LMSCloudData>::iterator itDataCloud;


		 for(itHeavyCloud=m_rgHeavyCloudsDefault.begin(); itHeavyCloud!=m_rgHeavyCloudsDefault.end(); ++itHeavyCloud){
			 ptrHeavyCloud = &itHeavyCloud->second;
			 rgstrUniqueId.push_back(ptrHeavyCloud->GetUniqueId());
			 rgstrIp.push_back(ptrHeavyCloud->GetIp());
			 rguiPort.push_back(ptrHeavyCloud->GetPort());
			 uiLengthOfArrays++;
		 }
		 ptrHeavyCloud = NULL;

		 for(itLightCloud=m_rgLightCloudsDefault.begin(); itLightCloud!=m_rgLightCloudsDefault.end(); ++itLightCloud){
			 ptrLightCloud = &itLightCloud->second;
			 rgstrIp.push_back(ptrLightCloud->GetIp());
			 rguiPort.push_back(ptrLightCloud->GetPort());
			 uiLengthOfArrays++;
		 }
		 ptrLightCloud = NULL;

		 for(itDataCloud=m_rgDataCloudsDefault.begin(); itDataCloud!=m_rgDataCloudsDefault.end(); ++itDataCloud){
			 ptrDataCloud = &itDataCloud->second;
			 rgstrIp.push_back(ptrDataCloud->GetIp());
			 rguiPort.push_back(ptrDataCloud->GetPort());
			 uiLengthOfArrays++;
			 bCloudsValid = CheckIfDatabaseExists(ptrDataCloud);
		 }
		 ptrDataCloud = NULL;


		 for(unsigned int i=0; i<uiLengthOfArrays; i++){
			 for(unsigned int b=0; b<uiLengthOfArrays; b++){
				 if(rgstrUniqueId[i] == rgstrUniqueId[b]){
					 WriteConsole("Unique Names must be different from each other! Check your config to make sure they are all unique.");
					 bCloudsValid = false;
				 }
				 if(!(strcmp(rgstrIp[i].c_str(),rgstrIp[b].c_str())) && rguiPort[i] == rguiPort[b]){
					 WriteConsole("IP addresses can be the same but their ports must be different if that is the case.");
					 bCloudsValid = false;
				 }
			 }
		 }
		 if(rgstrUniqueId.size() != 0) rgstrUniqueId.clear();
		 if(rgstrIp.size() != 0) rgstrIp.clear();
		 if(rguiPort.size() != 0) rguiPort.clear();

		 return bCloudsValid;

	}
	inline bool CheckIfDatabaseExists(LMSCloudData* ptrDataCloudCheck){
		bool bDoesExist = false;
		std::fstream fsExistCheck;
		fsExistCheck.open(ptrDataCloudCheck->GetLocalPathToDatabase().c_str());

		if(fsExistCheck)
			bDoesExist = true;

		fsExistCheck.close();
		return bDoesExist;
	}
	bool CheckKeys(){
		bool bKeysValid = true;
		unsigned int uiStart;
		unsigned int uiEnd;
		for(unsigned int i=0; i<9; i++){
			uiStart = m_rgDataRangeAndDataCloud[i].m_uiStart;
			uiEnd = m_rgDataRangeAndDataCloud[i].m_uiEnd;
			if((uiStart * uiEnd) == 65025) {
				bKeysValid = false;
				WriteConsole("Missing a range from number. Make sure all Data Clouds encompass all 1-9 ranges.");
			}
			if((uiStart < 1 || uiStart > 9)){
				WriteConsole("A range's start number is out of bounds (Must be 1-9)");
				bKeysValid = false;
			}
			if((uiEnd < 1 || uiEnd > 9)){
				WriteConsole("A range's end number is out of bounds (Must be 1-9)");
				bKeysValid = false;
			}
			if(uiStart > uiEnd) {
				WriteConsole("A range's start number can't be higher than its end number. It must be in ascending order!");
				bKeysValid = false;
			}
		}
		if(m_uiDataCloudsCount > 1 && bKeysValid){ /*Should really only check if there's more than one and if it is still valid*/
			std::vector<unsigned int> rguiStart;
			std::vector<unsigned int> rguiEnd;
			std::vector<std::string> rgstrUniqueIdAssigned;
			unsigned int uiLengthOfArrays = 0;

			LMSCloudData* ptrDataCloud;
			std::map<std::string, LMSCloudData>::iterator itDataCloud;

			for(itDataCloud=m_rgDataCloudsDefault.begin(); itDataCloud!=m_rgDataCloudsDefault.end(); ++itDataCloud){
				ptrDataCloud = &itDataCloud->second;
				rguiStart.push_back(ptrDataCloud->GetRangeKey().m_uiStart);
				rguiEnd.push_back(ptrDataCloud->GetRangeKey().m_uiEnd);
				rgstrUniqueIdAssigned.push_back(ptrDataCloud->GetUniqueId());
				uiLengthOfArrays++;
			}
			ptrDataCloud = NULL;

			bool bKeysTaken[9] = {false};
			unsigned int uiStart;
			unsigned int uiEnd;
		 	unsigned int uiSteps;
		 	 for(unsigned int i=0; i<uiLengthOfArrays; i++){
		 		 uiStart = rguiStart[i];
		 		 uiEnd = rguiEnd[i];
		 		 uiSteps = uiStart - uiEnd;

			 do{
				if(bKeysTaken[uiStart-1]) {
					bKeysValid = false;
					WriteConsole("A Data Cloud's Range is conflicting with another Data Cloud's Range");
				}
				bKeysTaken[uiStart-1] = true;
				 uiStart++;
				 uiSteps--;
			 }while(uiSteps != 0);
		 }

		 if(rguiStart.size() != 0) rguiStart.clear();
		 if(rguiEnd.size() != 0) rguiEnd.clear();

		}
		return bKeysValid;
		/*Check to see if they hit complete ranges*/

	}



private:
	bool bLoaded;
	std::map<std::string, std::string> m_mapEventsAndScripts;
	unsigned int m_uiEventsAndScriptsCount;
	std::map<std::string, CloudType> m_rgCloudType;
	std::map<std::string, LMSCloudHeavy> m_rgHeavyCloudsDefault;
	unsigned int m_uiHeavyCloudsCount;
	std::map<std::string, LMSCloudLight> m_rgLightCloudsDefault;
	unsigned int m_uiLightCloudsCount;
	std::map<std::string, LMSCloudData> m_rgDataCloudsDefault;
	unsigned int m_uiDataCloudsCount;

	LMSDataRange m_rgDataRangeAndDataCloud[9];

	std::string m_strPathToConfig;
};

#endif /* LMSCORE_H_ */
