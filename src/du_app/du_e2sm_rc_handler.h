#ifndef _RC_H_
#define _RC_H_
#include "common_def.h"
#include "lrg.h"
#include "lkw.x"
#include "lrg.x"
#include "legtp.h"
#include "du_app_mac_inf.h"
#include "du_app_rlc_inf.h"
#include "du_cfg.h"
#include "du_mgr.h"
#include "du_utils.h"
#include "RANfunction-Item.h"
#include "RICcontrolRequest.h"
#include "RICcontrolHeader.h"
#include "RICcontrolMessage.h"
#include "E2SM-RC-ControlHeader.h"
#include "E2SM-RC-ControlHeader-Format1.h"
#include "E2SM-RC-ControlMessage.h"
#include "E2SM-RC-ControlMessage-Format1.h"
#include "E2SM-RC-ControlMessage-Format1-Item.h"
#include "E2SM-RC-RANFunctionDefinition.h"
#include "RANParameter-ValueType.h"
#include "RANParameter-Value.h"
#include "RANParameter-STRUCTURE.h"
#include "RANParameter-STRUCTURE-Item.h"
#include "RANParameter-LIST.h"
#include "RANParameter-ValueType-Choice-Structure.h"
#include "RANParameter-ValueType-Choice-ElementFalse.h"
#include "RANParameter-ValueType-Choice-List.h" 
#include "RANFunctionDefinition-Control.h"
#include "RANFunctionDefinition-Control-Item.h"
#include "RANFunctionDefinition-Control-Action-Item.h"
#include "ControlAction-RANParameter-Item.h"

#define PARAMETER_SIZE 6
#define RADIO_RESOURCE_ALLOCATION 2
#define SLICE_LEVEL_PRB_QUOTA 6

#define POLICY_RATIO_LIST 1
#define POLICY_RATIO_GROUP 2
#define RRM_POLICY 3
#define POLICY_MEMBER_LIST 5
#define POLICY_MEMBER 6
#define POLICY_MEMBER_PLMNID 7
#define POLICY_MEMBER_SNSSAI 8
#define POLICY_MEMBER_SST 9
#define POLICY_MEMBER_SD 10
#define POLICY_MIN_PRB_RATIO 11
#define POLICY_MAX_PRB_RATIO 12
#define POLICY_DED_PRB_RATIO 13

#ifndef O1_ENABLE
uint8_t setRrmPolicy(RrmPolicyList rrmPolicy[],uint8_t policyNum);
#endif

uint8_t rcProcRrmPolicyValue(int id, void *value, int size);
uint8_t rcFillOctetString(OCTET_STRING_t *dst, uint8_t *src);
uint8_t rcFillRanFuncDescription(RANfunctionDefinition_t  *ranFunDefinition);
uint8_t rcProcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem);
uint8_t rcProcRanList(RANParameter_ValueType_Choice_List_t *ranParaChoiceList);
uint8_t rcProcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct);
uint8_t rcProcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, int id);
uint8_t rcProcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1);
uint8_t rcProcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list);
uint8_t rcProcCtrlHeader(RICcontrolHeader_t *RICcontrolHeader);
uint8_t rcProcCtrlMessage(RICcontrolMessage_t *RICcontrolMessage);

int policyIdx;
RrmPolicyList rrmPolicyGroup[3];

#endif
