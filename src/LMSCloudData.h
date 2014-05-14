/*
 * LMSCloudData.h
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#ifndef LMSDATACLOUD_H_
#define LMSDATACLOUD_H_
#include <string>
#include "LMSCloud.h"


struct LMSDataRange{
	std::string m_strUniqueId;
	std::string m_strAssignedToDataCloud;
	unsigned int m_uiStart;
	unsigned int m_uiEnd;
};

class LMSCloudData : LMSCloud {
public:
	LMSCloudData(){

	}
	LMSCloudData(std::string strUniqueId){

	}
	LMSCloudData(std::string strIp, unsigned int uiPort){
		m_strIp = strIp;
		m_uiPort = uiPort;
	}
	~LMSCloudData(){

	}

	bool LoadWithUniqueId();
	bool Start();
	bool Stop();
	std::string GetIp(){
		return LMSCloud::GetIp();
	}
	unsigned int GetPort(){
		return LMSCloud::GetPort();
	}
	std::string GetUniqueId(){
		return LMSCloud::GetUniqueId();
	}

	bool SetLocalPathToDatabase(std::string strPath){
		m_strLocalPathToDatabase = strPath;
		return true;
	}
	std::string GetLocalPathToDatabase(){
		return m_strLocalPathToDatabase;
	}
	LMSDataRange GetRangeKey(){
		return m_rangeKey;
	}
	bool SetHeavyCloud(std::string strIp, unsigned int uiPort){
		return false;
	}
	CloudType GetCloudType(){
		return LMSCloud::GetCloudType();
	}
	bool Alive(){
		return LMSCloud::Alive();
	}
private:
	std::string m_strLocalPathToDatabase;
	LMSDataRange m_rangeKey;


};

#endif /* LMSDATACLOUD_H_ */
