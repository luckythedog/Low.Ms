/*
 * LMSCloudLight.h
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#ifndef LMSCLOUDLIGHT_H_
#define LMSCLOUDLIGHT_H_
#include "LMSCloud.h"


class LMSCloudData;
class LMSCloudHeavy;

class LMSCloudLight : LMSCloud {
public:
	LMSCloudLight(){
		SetDefault();
	}
	LMSCloudLight(std::string strUniqueId){
		m_strUniqueId = strUniqueId;
		LoadWithUniqueId();
	}
	LMSCloudLight(std::string strIp, unsigned int uiPort){
		SetDefault();
		LMSCloud::SetIp(strIp);
		LMSCloud::SetPort(uiPort);
	}
	~LMSCloudLight(){

	}
	bool SetDefault(){
		m_strUniqueId = "";
		m_uiAllowedConnections = 0;
		m_uiConnectionsCount = 0;
		m_uiLightCloudsConnected = 0;
		m_rgLightClouds.clear();
		m_uiDataCloudsConnected = 0;
		m_rgDataClouds.clear();

		m_heavyCloud = NULL;

		LMSCloud::WriteDebug("Everything has been set to default");
		return true;
	}
	bool LoadWithUniqueId();
	bool Start();
	bool Stop();

	bool SetHeavyCloud(std::string strIp, unsigned int uiPort);

	bool AddLightCloud(LMSCloudLight* lightNewCloud){
		m_rgLightClouds.push_back(lightNewCloud);
		m_uiLightCloudsConnected++;
		LMSCloud::WriteDebug("Light Cloud has been added to this Heavy Cloud's list");
		LMSCloud::WriteDebug("Added New Light Cloud to List");
		return true;
	}
	bool RemoveAllLightClouds(){
		m_rgLightClouds.clear();
		m_uiLightCloudsConnected = 0;
		LMSCloud::WriteDebug("Removed All Light Clouds from List");
		return true;
	}
	bool AddDataCloud(LMSCloudData* dataNewCloud);

	bool RemoveAllDataClouds(){
		m_rgDataClouds.clear();
		m_uiDataCloudsConnected = 0;
		LMSCloud::WriteDebug("Removed All Data Clouds from List");
		return true;
	}

	bool SetAllowedConnections(unsigned int uiNewAmount){
		m_uiAllowedConnections = uiNewAmount;
		return true;
	}
	unsigned int GetAllowedConnections(){
		return m_uiAllowedConnections;
	}
	unsigned int GetConnectionsCount(){
		return m_uiConnectionsCount;
	}
	unsigned int IsFull(){
		if(GetAllowedConnections() == 0) return false;
		if(m_uiConnectionsCount >= GetAllowedConnections()){
			return true;
		}
		return false;
	}

	bool SetUniqueId(std::string strNewName){
		LMSCloud::SetUniqueId(strNewName);
		return true;
	}
	std::string GetIp(){
		return LMSCloud::GetIp();
	}
	unsigned int GetPort(){
		return LMSCloud::GetPort();
	}
	std::string GetUniqueId(){
		return LMSCloud::GetUniqueId();
	}
	CloudType GetCloudType(){
		return LMSCloud::GetCloudType();
	}
	bool Alive(){
		return LMSCloud::Alive();
	}
private:
	unsigned int m_uiAllowedConnections;
	unsigned int m_uiConnectionsCount;

	LMSCloudHeavy* m_heavyCloud;

	std::vector<LMSCloudLight*> m_rgLightClouds;
	unsigned int m_uiLightCloudsConnected;

	std::vector<LMSCloudData*> m_rgDataClouds;
	unsigned int m_uiDataCloudsConnected;

};

#endif /* LMSCLOUDLIGHT_H_ */
