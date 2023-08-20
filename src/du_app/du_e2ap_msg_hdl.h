/*******************************************************************************
################################################################################
#   Copyright (c) [2017-2019] [Radisys]                                        #
#                                                                              #
#   Licensed under the Apache License, Version 2.0 (the "License");            #
#   you may not use this file except in compliance with the License.           #
#   You may obtain a copy of the License at                                    #
#                                                                              #
#       http://www.apache.org/licenses/LICENSE-2.0                             #
#                                                                              #
#   Unless required by applicable law or agreed to in writing, software        #
#   distributed under the License is distributed on an "AS IS" BASIS,          #
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   #
#   See the License for the specific language governing permissions and        #
#   limitations under the License.                                             #
################################################################################
*******************************************************************************/

/* This file contains all E2AP message handler related functionality */

#ifndef _AP_H_
#define _AP_H_

#define ENCODE_FAIL -1

uint8_t sctpSend(Buffer *mBuf, uint8_t itfType);
uint8_t setRrmPolicy(RrmPolicyList rrmPolicy[], uint8_t policyNum);

typedef struct e2apDb
{
   uint16_t     ricId;                    
   uint8_t      *plmn;
   uint32_t     ricReqId;
   uint32_t     ricInstanceId;
   uint32_t     ranFuncId;
   uint8_t     *ricEventTrigger;
   uint32_t     ricActionId;
   uint32_t     ricActionType;

   // For E2SM-RC
   uint32_t     ricCtrlReqId;
   uint32_t     ricCtrlInstanceId;
   uint32_t     ranCtrlFuncId;

}E2apMsgDb;

E2apMsgDb e2apMsgDb;

uint8_t BuildAndSendE2SetupReq();
uint8_t SendE2APMsg(Region , Pool );
void E2APMsgHdlr(Buffer *mBuf);
uint8_t BuildAndSendE2NodeConfigUpdate();

#endif
/**********************************************************************
  End of file
 **********************************************************************/
