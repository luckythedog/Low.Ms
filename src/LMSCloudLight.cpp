/*
 * LMSCloudLight.cpp

 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#include "LMSCloudLight.h"
#include "LMSCloud.h"
#include "LMSCloudData.h"
#include "LMSCloudHeavy.h"


	bool LMSCloudLight::SetHeavyCloud(std::string strIp, unsigned int uiPort){
		return false;
	}
	bool LMSCloudLight::AddDataCloud(LMSCloudData* dataNewCloud){
		m_rgDataClouds.push_back(dataNewCloud);
		m_uiDataCloudsConnected++;
		LMSCloud::WriteDebug("Added New Data Cloud to List");
		return true;
	}
	bool LMSCloudLight::LoadWithUniqueId(){
		if(m_strUniqueId != ""){

		}
		LMSCloud::WriteDebug("There was an error loading with unique ID");
		return false;

	}
	bool LMSCloudLight::Start(){
		return true;
	}
	bool LMSCloudLight::Stop(){
		return true;

	}
