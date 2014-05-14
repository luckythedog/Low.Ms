/*
 * LMSPacket.h
 *
 *  Created on: May 13, 2014
 *      Author: lucky
 */

#ifndef LMSPACKET_H_
#define LMSPACKET_H_
#include <iostream>
#include <string>

class LMSPacket {
public:
	LMSPacket();
	virtual ~LMSPacket();
private:
	std::string strRawData;
};

#endif /* LMSPACKET_H_ */
