/*
 * USBEmulationConstants.h
 *
 *  Created on: Oct 4, 2015
 *      Author: zlatan
 */

#ifndef USBEMULATIONCONSTANTS_H_
#define USBEMULATIONCONSTANTS_H_
#include <map>

const std::map<int, std::string> what{
	{0,"URB_RQ_GET_STATUS"},
	{1,"URB_RQ_CLEAR_FEATURE"},
	{3,"URB_RQ_SET_FEATURE"},
	{5,"URB_RQ_SET_ADDRESS"},
	{6,"URB_RQ_GET_DESCRIPTOR"},
	{7,"URB_RQ_SET_DESCRIPTOR"},
	{8,"URB_RQ_GET_CONFIGURATION"},
	{9," URB_RQ_SET_CONFIGURATION"},
	{10,"URB_RQ_GET_INTERFACE"},
	{11,"URB_RQ_SET_INTERFACE"},
	{12,"URB_RQ_SYNCH_FRAME"}
};

#endif /* USBEMULATIONCONSTANTS_H_ */
