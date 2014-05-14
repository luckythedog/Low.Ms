/*
 * LowMs.cpp
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */
#include "LMSCloud.h"

bool LMSCloud::SetUniqueId(std::string strNewUniqueId){
		m_strUniqueId = strNewUniqueId;
		WriteDebug("Unique Id has been set to " + m_strUniqueId);
		return true;
}
