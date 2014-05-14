/*
 * LMSCloudHeavy.h
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#ifndef LMSCLOUDHEAVY_H_
#define LMSCLOUDHEAVY_H_
#include "LMSCloud.h"


class LMSCloudLight;
class LMSCloudData;

class LMSCloudHeavy : LMSCloud{
public:
	LMSCloudHeavy(){
		SetDefault();
	}
	LMSCloudHeavy(std::string strUniqueId){
		m_strUniqueId = strUniqueId;
		LoadWithUniqueId();
	}
	LMSCloudHeavy(std::string strIp, unsigned int uiPort) {
		SetDefault();
		LMSCloud::SetIp(strIp);
		LMSCloud::SetPort(uiPort);
	}

	~LMSCloudHeavy(){

	}

	bool SetDefault(){
		m_strUniqueId = "";

		m_uiAllowedTotalConnections = 0;
		m_uiTotalConnections = 0;

		m_uiLightCloudsConnected = 0;
		m_rgLightClouds.clear();

		m_uiDataCloudsConnected = 0;
		m_rgDataClouds.clear();
		LMSCloud::WriteDebug("Everything has been set to default");
		return true;
	}
	bool LoadWithUniqueId();
	bool Start();
	bool Stop();


	bool SetAllowedTotalConnections(unsigned int uiNewMax){
		if(uiNewMax > GetTotalConnections()) LMSCloud::WriteDebug("Setting Allowed Total Connections lower than Clients connected currently");
		LMSCloud::WriteDebug("Allowed Total Connections is now set to "+uiNewMax);
		return true;
	}
	unsigned int GetAllowedTotalConnections(){
		return m_uiAllowedTotalConnections;
	}
	bool CheckIfAllowedToConnect(){
		if(GetAllowedTotalConnections() == 0) return true;
		if(GetTotalConnections() >= GetAllowedTotalConnections()) return false;
		return true;
	}
	unsigned int GetTotalConnections(){
		return m_uiTotalConnections;
	}

	bool AddLightCloud(LMSCloudLight lightNewCloud);
	bool RemoveAllLightClouds(){
		m_rgLightClouds.clear();
		m_uiLightCloudsConnected = 0;
		LMSCloud::WriteDebug("Removed All Light Clouds from List");
		return true;
	}
	bool AddDataCloud(LMSCloudData dataNewCloud);
	bool RemoveAllDataClouds(){
		m_rgDataClouds.clear();
		m_uiDataCloudsConnected = 0;
		LMSCloud::WriteDebug("Removed All Data Clouds from List");
		return true;
	}
	bool SetUniqueId(std::string strNewName){
		LMSCloud::SetUniqueId(strNewName);
		return true;
	}
	std::string GetUniqueId(){
		return LMSCloud::GetUniqueId();
	}
	std::string GetIp(){
		return LMSCloud::GetIp();
	}
	unsigned int GetPort(){
		return LMSCloud::GetPort();
	}
	CloudType GetCloudType(){
		return LMSCloud::GetCloudType();
	}
	bool Alive(){
		return LMSCloud::Alive();
	}
private:
	unsigned int m_uiAllowedTotalConnections;
	unsigned int m_uiTotalConnections;

	std::vector<LMSCloudLight> m_rgLightClouds;
	unsigned int m_uiLightCloudsConnected;

	std::vector<LMSCloudData> m_rgDataClouds;
	unsigned int m_uiDataCloudsConnected;
};

#endif /* LMSCLOUDHEAVY_H_ */
