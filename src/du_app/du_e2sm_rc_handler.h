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
#include "du_mgr_main.h"
#include "du_mgr.h"
#include "RICcontrolRequest.h"
#include "RICcontrolHeader.h"
#include "RICcontrolMessage.h"
#include "E2SM-RC-ControlHeader.h"
#include "E2SM-RC-ControlHeader-Format1.h"
#include "E2SM-RC-ControlMessage.h"
#include "E2SM-RC-ControlMessage-Format1.h"
#include "E2SM-RC-ControlMessage-Format1-Item.h"
#include "RANParameter-ValueType.h"
#include "RANParameter-Value.h"
#include "RANParameter-STRUCTURE.h"
#include "RANParameter-STRUCTURE-Item.h"
#include "RANParameter-LIST.h"
#include "RANParameter-ValueType-Choice-Structure.h"
#include "RANParameter-ValueType-Choice-ElementFalse.h"
#include "RANParameter-ValueType-Choice-List.h"


typedef struct paraIdList_linkList {
    int data;
    struct paraIdList_linkList* next;
}paraIdList;

/*
//RRM POLICY STRUCT

typedef struct rRMPolicyMemberList
{
   uint8_t mcc[3];
   uint8_t mnc[3];
   uint8_t sd[3];
   uint8_t sst;
}RRMPolicyMemberList;

typedef enum
{
  PRB,
  PRB_UL,
  PRB_DL,
  RRC,
  DRB
}RrmResourceType;

typedef struct rrmPolicyList
{
   char id[1];
   RrmResourceType resourceType;
   uint8_t rRMMemberNum;
   RRMPolicyMemberList rRMPolicyMemberList[2];
   uint8_t rRMPolicyMaxRatio;
   uint8_t rRMPolicyMinRatio;
   uint8_t rRMPolicyDedicatedRatio;
}RrmPolicyList;

*/

//RrmPolicyList *rrmPolicyList;
//RrmPolicyList rrmPolicy;

//uint8_t setRrmPolicy(RrmPolicyList rrmPolicy[],uint8_t policyNum);

void print_paraID_List(paraIdList* node);
int procE2rcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem, paraIdList *paraIdLinkList);
int procE2rcRanList(RANParameter_ValueType_Choice_List_t *ranParaChoiceList, paraIdList *paraIdLinkList);
int procE2rcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct, paraIdList *paraIdLinkList);
int procE2rcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, paraIdList *paraIdLinkList);
int procE2rcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1, paraIdList *paraIdLinkList);
int procE2rcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list);
void procE2rcCtrlHeader(RICcontrolHeader_t *RICcontrolHeader);
int procE2rcCtrlMessage(RICcontrolMessage_t *RICcontrolMessage);

#endif
