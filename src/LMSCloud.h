#ifndef LMS_CLOUD
#define LMS_CLOUD
/*C Standard libraries*/
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>
/*Network libraries*/
#ifndef _WIN32
#include <poll.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm/socket.h>
#include <unistd.h>
#else
#include <winsocks.h>
#include <windows.h>
#endif
/*cloud linker*/

enum CloudType{
	NoneCloud = 0xAA,
	HeavyCloud = 0xA0,
	LightCloud = 0xA1,
	DataCloud = 0XA2
};

class LMSCloud{
public:

	 bool SetCloudDefault(){
		 m_bIsAlive = false;
		 m_bHasCore = false;
		 return true;
	 }
	bool Start();
	bool Stop();
	bool LoadWithUniqueId();
	/*For both core and non-core*/
	bool SetIp(std::string strNewIp){
		m_strIp = strNewIp;
			WriteDebug("IP has been set to ");
			WriteDebug(m_strIp);
		return true;
	}
	std::string GetIp(){
		return m_strIp;
	}
	bool SetPort(unsigned int uiPortSet)
	{
		m_uiPort = uiPortSet;
		WriteDebug("Port has been set to "+uiPortSet);
		return true;
	}
	unsigned int GetPort(){
		return m_uiPort;
	}
	bool SetSocket(unsigned int uiNewSocket){
		close(m_uiSocket);
		m_uiSocket=  uiNewSocket;
		WriteDebug("Socket has been set to " + uiNewSocket);
		return true;
	}
	unsigned int GetSocket(){
		return m_uiSocket;
	}
	bool SetAlive(bool bNewValue){
		m_bIsAlive = bNewValue;
		WriteDebug("Alive status has been set to " +bNewValue);
		return true;
	}
	bool SetUniqueId(std::string strNewUniqueId);
	bool Alive(){
		return m_bIsAlive;
	}

	const char* GetUniqueId(){
		return m_strUniqueId.c_str();
	}

	bool SetDebugEnabled(bool bNewBool){
		m_bDebugEnabled = bNewBool;
		WriteDebug("Debug messages enabled have been set to " + m_bDebugEnabled);
		return true;
	}
	bool GetDebugEnabled(){
		return m_bDebugEnabled;
	}
	/*Debug messages*/
	bool WriteDebug(std::string strMessage){
		if(GetDebugEnabled())
			printf("[%s]: %s", GetUniqueId(), strMessage.c_str());
		return true;
	}
	bool WriteConsole(std::string strMessage){
		printf("[%s]: %s", GetUniqueId(), strMessage.c_str());
		return true;
	}
	/*CORE COMMANDS*/

	bool SetCloudType(CloudType chNewCloudType){
		m_chCloudType = chNewCloudType;
		WriteDebug("Cloud Type has been changed to " + m_chCloudType);
		return true;
	}
	CloudType GetCloudType(){
		return m_chCloudType;
	}

protected:
	/*Server Information*/
	unsigned int m_uiSocket;
	struct sockaddr_in m_sckAddress;
	std::string m_strIp;
	unsigned int m_uiPort;
	std::string m_strUniqueId;
	CloudType m_chCloudType;

	/*Server instance items*/
	bool m_bHasCore;
	bool m_bIsAlive;
	bool m_bDebugEnabled;
	pthread_t m_pthrCloudThread;

private:

};

#endif
