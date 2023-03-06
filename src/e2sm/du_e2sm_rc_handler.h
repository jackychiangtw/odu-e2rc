#ifndef _RC_H_
#define _RC_H_
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
#include "RANParameter-ValueType-Choice-Structure.h"
#include "RANParameter-ValueType-Choice-ElementFalse.h"


typedef struct paraID_linkList {
    int data;
    struct paraID_linkList* next;
}paraID;

void print_paraID_List(paraID* node);
int procE2rcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem, paraID *paraIdLinkList);
int procE2rcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct, paraID *paraIdLinkList);
int procE2rcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, paraID *paraIdLinkList);
int procE2rcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1, paraID *paraIdLinkList);
int procE2rcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list);
void procE2rcCtrlHeader(RICcontrolHeader_t *RICcontrolHeader);
void procE2rcCtrlMessage(RICcontrolMessage_t *RICcontrolMessage);

#endif
