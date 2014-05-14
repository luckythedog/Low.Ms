/*
 * LMSCloudHeavy.cpp
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */


#include "LMSCloudHeavy.h"
#include "LMSCloud.h"
#include "LMSCloudLight.h"
#include "LMSCloudData.h"



bool LMSCloudHeavy::LoadWithUniqueId(){
	LMSCloud::WriteDebug("Loading Unique Id " + m_strUniqueId + " from clouds.xml");
	return true;
}
bool LMSCloudHeavy::Start(){
	return true;
}
bool LMSCloudHeavy::Stop(){
	return true;

}
bool LMSCloudHeavy::AddLightCloud(LMSCloudLight lightNewCloud){
	m_rgLightClouds.push_back(lightNewCloud);
	m_uiLightCloudsConnected++;
	LMSCloud::WriteDebug("Light Cloud has been added to this Heavy Cloud's list");
	LMSCloud::WriteDebug("Added New Light Cloud to List");
	return true;
}

bool LMSCloudHeavy::AddDataCloud(LMSCloudData dataNewCloud){
	m_rgDataClouds.push_back(dataNewCloud);
	m_uiDataCloudsConnected++;
	LMSCloud::WriteDebug("Added New Data Cloud to List");
	return true;
}
