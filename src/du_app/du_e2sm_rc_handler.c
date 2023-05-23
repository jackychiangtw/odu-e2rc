#include "du_e2sm_rc_handler.h"
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

RrmPolicyList rrmPolicyGroup[3];
int policyIdx = 0;

char parameterName[][30] = {"PLMN Identity", "SST", "SD", "Min PRB Policy Ratio", "Max PRB Policy Ratio", "Ded PRB Policy Ratio"};
int parameterId[] = {7,9,10,11,12,13};
int paraSize = 6;



void procRrmPolicyValue(int id, void *value, int size){
    int *intValue = (int*)value;
    char *charValue = (char*)value;

    static int memberIdx = 0;

    if(size){
        switch(id){
            case 1:
            case 5:
            case 8:
            case 3:
                break;
            case 7:
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].mcc, charValue, 3);
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].mnc, charValue+3, 3);
                break;
            case 9:
                rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].sst = *charValue;
                break;
            case 10:
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].sd, charValue, 3);
                memberIdx++;
                break;
            case 11:
                rrmPolicyGroup[policyIdx].rRMPolicyMinRatio = *intValue;
                break;
            case 12:
                rrmPolicyGroup[policyIdx].rRMPolicyMaxRatio = *intValue;
                break;
            case 13:
                rrmPolicyGroup[policyIdx].rRMPolicyDedicatedRatio = *intValue;
                rrmPolicyGroup[policyIdx].id[0] = policyIdx + 1;
                rrmPolicyGroup[policyIdx].rRMMemberNum = memberIdx;
                policyIdx++;
                break;
            default:
                printf("fillRrmPolicyValue: Invaild parameter ID\n");
        }
    }
    else{
         switch(id){
            case 1:
                policyIdx = 0;
                memberIdx = 0;
                rrmPolicyGroup[policyIdx].resourceType = PRB;
                break;
            case 3:
                memberIdx = 0;
                break;
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            default:
                break;
         }
    }
}

// Function to insert a node at the beginning of the linked list
void paraIdList_push(paraIdList** head_ref, int new_data) {
    paraIdList* new_node = (paraIdList*)malloc(sizeof(paraIdList));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to print the linked list
void print_paraId_List(paraIdList* node) {
    while (node != NULL) {
        //printf("%d ", node->data);
        node = node->next;
    }
    // printf("\n");
}

int printHeadNode(paraIdList* node){
    return node->data;
}

uint8_t setRrmPolicy(RrmPolicyList rrmPolicy[], uint8_t policyNum)
{
   DU_LOG("\nINFO   -->  DU_APP : DU APP RRM number of policy %d,", \
	  policyNum);
   for(uint8_t i=0; i<policyNum ; i++)
   {
      DU_LOG("\nINFO   -->  DU_APP : DU APP  id = %d",rrmPolicy[i].id[0]);
      DU_LOG("\nINFO   -->  DU_APP : DU APP  resourceType = %d", \
		rrmPolicy[i].resourceType);
      DU_LOG("\nINFO   -->  DU_APP : DU APP  rRMPolicyMaxRatio = %d", \
		rrmPolicy[i].rRMPolicyMaxRatio);
      DU_LOG("\nINFO   -->  DU_APP : DU APP  rRMPolicyMinRatio = %d", \
		rrmPolicy[i].rRMPolicyMinRatio);
      DU_LOG("\nINFO   -->  DU_APP : DU APP  rRMPolicyDedicatedRatio = %d", \
		rrmPolicy[i].rRMPolicyDedicatedRatio);
      DU_LOG("\nINFO   -->  DU_APP : DU APP  rRMMemberNum = %d", \
		rrmPolicy[i].rRMMemberNum);
      for(uint8_t j=0; j<rrmPolicy[i].rRMMemberNum ; j++)
      {
         DU_LOG("\nINFO   -->  DU_APP : DU APP  mcc = %x %x %x", \
                 rrmPolicy[i].rRMPolicyMemberList[j].mcc[0], \
		 rrmPolicy[i].rRMPolicyMemberList[j].mcc[1], \
		 rrmPolicy[i].rRMPolicyMemberList[j].mcc[2]);
         DU_LOG("\nINFO   -->  DU_APP : DU APP  mnc = %x %x %x ", \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[0], \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[1], \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[2]);

         DU_LOG("\nINFO   -->  DU_APP : DU APP  sd = %x %x %x", \
	           rrmPolicy[i].rRMPolicyMemberList[j].sd[0], \
		   rrmPolicy[i].rRMPolicyMemberList[j].sd[1], \
		   rrmPolicy[i].rRMPolicyMemberList[j].sd[2]);

         DU_LOG("\nINFO   -->  DU_APP : DU APP  sst = %x \n", \
		   rrmPolicy[i].rRMPolicyMemberList[j].sst);
      }

   }
   DuCellCb *cellCb = NULLP;

    cpyRrmPolicyInDuCfgParams(rrmPolicy, policyNum, &duCfgParam.tempSliceCfg);
    cellCb = duCb.actvCellLst[0];

    if(cellCb)
    {
       if(cellCb->cellStatus == ACTIVATED)
       {
           if(duCb.sliceState == SLICE_INFO_NOT_AVAILABLE)
           {
              BuildAndSendSliceConfigReq();
           }
           else 
           {
              BuildAndSendSliceRecfgReq();
           }
       }
    }
   return ROK;
}


int procE2rcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem, paraIdList *paraIdLinkList){
    // printf("\nINFO  -->  E2SM_RC handler : RAN Parameter ID = %ld\n", ranStructItem->ranParameter_ID);
    paraIdList_push(&paraIdLinkList, ranStructItem->ranParameter_ID);
    procRrmPolicyValue(ranStructItem->ranParameter_ID, 0,0);

    if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
        printf("\nERROR  -->  E2SM_RC handler : Control Message Element True Item isn't supported\n");
        return -1;
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
        procE2rcRanElemFalse(ranStructItem->ranParameter_valueType->choice.ranP_Choice_ElementFalse, paraIdLinkList);
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_Structure){
        procE2rcRanStruct(ranStructItem->ranParameter_valueType->choice.ranP_Choice_Structure, paraIdLinkList);
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_List){
        procE2rcRanList(ranStructItem->ranParameter_valueType->choice.ranP_Choice_List, paraIdLinkList);
    }
    else{
        printf("\nERROR  -->  E2SM_RC handler : Unknown Control Message Element Item\n");
        return -1;
    }

}

int procE2rcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct, paraIdList *paraIdLinkList){
    RANParameter_STRUCTURE_t *ranParaStruct = ranParaChoiceStruct->ranParameter_Structure;
    //xer_fprint(stdout, &asn_DEF_RANParameter_STRUCTURE, ranParaStruct);
    for(int i=0;i<ranParaStruct->sequence_of_ranParameters->list.count;i++){
        procE2rcRanStructItem(ranParaStruct->sequence_of_ranParameters->list.array[i], paraIdLinkList);
    }
}

int procE2rcRanList(RANParameter_ValueType_Choice_List_t *ranParaChoiceList, paraIdList *paraIdLinkList){
    RANParameter_LIST_t *ranParaList = ranParaChoiceList->ranParameter_List;
    //xer_fprint(stdout, &asn_DEF_RANParameter_LIST, ranParaList);
    for(int i=0;i<ranParaList->list_of_ranParameter.list.count;i++){
        RANParameter_STRUCTURE_t *ranParaStruct = ranParaList->list_of_ranParameter.list.array[i];
        for(int j=0;j<ranParaStruct->sequence_of_ranParameters->list.count;j++){
            procE2rcRanStructItem(ranParaStruct->sequence_of_ranParameters->list.array[j], paraIdLinkList);
        }
    }
}

int procE2rcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, paraIdList *paraIdLinkList){
    RANParameter_Value_t *ranParaValue = ranParaChoiceElementFalse->ranParameter_value;
    int paraId = printHeadNode(paraIdLinkList);
    switch(ranParaValue->present){
        case RANParameter_Value_PR_valueOctS:
            // printf("Parameter ID: %d\n", paraId);
            // printf("Value: ");
            // for(int i=0;i<ranParaValue->choice.valueOctS.size;i++){
            //     printf("%x ", ranParaValue->choice.valueOctS.buf[i]);
            // }
            procRrmPolicyValue(paraId, ranParaValue->choice.valueOctS.buf, ranParaValue->choice.valueOctS.size);

            printf("\n");

            break;
        case RANParameter_Value_PR_valueInt:
            // printf("Parameter ID: %d\n", paraId);
            // printf("Value:%d", ranParaValue->choice.valueInt);
            // printf("\n");
            procRrmPolicyValue(paraId, &ranParaValue->choice.valueInt, 1);
            break;
        default:
            printf("\nERROR  -->  E2SM_RC handler : Value type isn't supported\n");
            return -1;
            break;
    }
}

int procE2rcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1, paraIdList *paraIdLinkList){
    // printf("\nINFO  -->  E2SM_RC handler : RAN Parameter ID = %ld\n", ctrlFrmt1->ranParameter_ID);
    paraIdList_push(&paraIdLinkList, ctrlFrmt1->ranParameter_ID);
    procRrmPolicyValue(ctrlFrmt1->ranParameter_ID, 0,0);


    if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
        printf("\nERROR  -->  E2SM_RC handler : Control Message Element True Item isn't supported\n");
        return -1;
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
        procE2rcRanElemFalse(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_ElementFalse, paraIdLinkList);
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_Structure){
        procE2rcRanStruct(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_Structure, paraIdLinkList);
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_List){
        procE2rcRanList(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_List, paraIdLinkList);
    }
    else{
        printf("\nERROR  -->  E2SM_RC handler : Unknown Control Message Element Item\n");
        return -1;
    }
}

int procE2rcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list){
    paraIdList* paraIdHead = NULL;
    //xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage_Format1, ctrlFrmt1_list);
    for(int i=0;i<ctrlFrmt1_list->ranP_List.list.count;i++){
        procE2rcMessageFrmt1Item(ctrlFrmt1_list->ranP_List.list.array[i], paraIdHead);
    }
}


void printRrmPolicy(int policyNum){
    for(int i=0;i<policyNum;i++){
        printf("Policy Group %d:\n", i);
        int memberNum = rrmPolicyGroup[i].rRMMemberNum;
        for(int j=0;j<memberNum;j++){
            printf("\tMember %d:\n", j);
            printf("\t\tPLMN ID: ");
            for(int k=0;k<3;k++){
                printf("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].mcc[k]);
            }
            for(int k=0;k<3;k++){
                printf("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].mnc[k]);
            }
            printf("\n\t\tS-NSSAI: %x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].sst);
            for(int k=0;k<3;k++){
                printf("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].sd[k]);
            }
            printf("\n");
        }
        printf("\tMin PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyMinRatio);
        printf("\tMax PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyMaxRatio);
        printf("\tDed PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyDedicatedRatio);
    }

}


int procE2rcCtrlMessage(RICcontrolMessage_t *ricControlMessage){
    asn_dec_rval_t  rval;
    E2SM_RC_ControlMessage_t *ctrlMessage = (E2SM_RC_ControlMessage_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_t));

    printf("\nINFO   -->  E2SM_RC handler : Process RIC Control Message<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlMessage, (void **)&ctrlMessage, ricControlMessage->buf, ricControlMessage->size, 0, 0);

    xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage, ctrlMessage);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
        printf("\nERROR  -->  E2SM_RC handler : Control Message ASN decode failed %d, %ld\n", rval.code, rval.consumed);
        return -1;

    }

    if(ctrlMessage->ric_controlMessage_formats.present == E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format2){
        printf("\nERROR  -->  E2SM_RC handler : Control Message format 2 isn't supported\n");
        return -1;
    }
    else{
        procE2rcMessageFrmt1List(ctrlMessage->ric_controlMessage_formats.choice.controlMessage_Format1);
        printRrmPolicy(policyIdx);
        setRrmPolicy(rrmPolicyGroup, policyIdx);
    }
}

void procE2rcCtrlHeader(RICcontrolHeader_t *ricControlHeader){
    asn_dec_rval_t  rval;
    E2SM_RC_ControlHeader_t *ctrlHeader = (E2SM_RC_ControlHeader_t*)calloc(1, sizeof(E2SM_RC_ControlHeader_t));;

    printf("\nINFO   -->  E2SM_RC handler : Process RIC Control Header<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlHeader, (void **)&ctrlHeader, ricControlHeader->buf, ricControlHeader->size, 0, 0);

    xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlHeader, ctrlHeader);

    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
      printf("\nERROR  -->  E2SM_RC handler : Control Header ASN decode failed\n");
    }

    printf("\nINFO  -->  E2SM_RC Handler : Header Format = %d", ctrlHeader->ric_controlHeader_formats.present);
    printf("\nINFO  -->  E2SM_RC Handler : RIC Style Type = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_Style_Type);
    printf("\nINFO  -->  E2SM_RC Handler : RIC Control Action ID = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_ControlAction_ID);
}

uint8_t rcFillRanFunctionName(RANfunction_Name_t *ranFuncName){
    uint8_t shortName[] = "ORAN-E2SM-RC";
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.1.2.3"; // RAN function service model OID
    uint8_t description[] = "RAN Control";

    ranFuncName->ranFunction_ShortName.size = sizeof(shortName)-1;
    ranFuncName->ranFunction_ShortName.buf = (uint8_t*)calloc(sizeof(shortName), sizeof(uint8_t));
    memcpy(ranFuncName->ranFunction_ShortName.buf, shortName, ranFuncName->ranFunction_ShortName.size);

    ranFuncName->ranFunction_Description.size = sizeof(description)-1;
    ranFuncName->ranFunction_Description.buf = (uint8_t*)calloc(sizeof(description), sizeof(uint8_t));
    memcpy(ranFuncName->ranFunction_Description.buf, description, ranFuncName->ranFunction_Description.size);

    ranFuncName->ranFunction_E2SM_OID.size = sizeof(ranfunc_oid)-1;
    ranFuncName->ranFunction_E2SM_OID.buf = (uint8_t*)calloc(sizeof(ranfunc_oid), sizeof(uint8_t));
    memcpy(ranFuncName->ranFunction_E2SM_OID.buf, ranfunc_oid, ranFuncName->ranFunction_E2SM_OID.size);

    xer_fprint(stderr, &asn_DEF_RANfunction_Name, ranFuncName);


}

uint8_t rcFillCtrlActionRanParameterItem(ControlAction_RANParameter_Item_t *ctrlActionRanParaItem, int index){
    ctrlActionRanParaItem->ranParameter_ID = parameterId[index];
    ctrlActionRanParaItem->ranParameter_name.size = strlen(parameterName[index]);
    
    ctrlActionRanParaItem->ranParameter_name.buf = (uint8_t*)calloc(strlen(parameterName[index]), sizeof(uint8_t));
    memcpy(ctrlActionRanParaItem->ranParameter_name.buf, parameterName[index], ctrlActionRanParaItem->ranParameter_name.size);

    xer_fprint(stderr, &asn_DEF_ControlAction_RANParameter_Item, ctrlActionRanParaItem);


}

uint8_t rcFillRanFuncDefiCtrlActionItem(RANFunctionDefinition_Control_Action_Item_t *ranFunCtrlActionItem){
    uint8_t actionName[] = "Slice-level PRB quota";
    ranFunCtrlActionItem->ric_ControlAction_ID = 6;

    ranFunCtrlActionItem->ric_ControlAction_Name.size = strlen(actionName);
    ranFunCtrlActionItem->ric_ControlAction_Name.buf = (uint8_t*)calloc(sizeof(actionName), sizeof(uint8_t));
    memcpy(ranFunCtrlActionItem->ric_ControlAction_Name.buf, actionName, ranFunCtrlActionItem->ric_ControlAction_Name.size);
    ranFunCtrlActionItem->ran_ControlActionParameters_List = (struct RANFunctionDefinition_Control_Action_Item__ran_ControlActionParameters_List*)calloc(1, sizeof(struct RANFunctionDefinition_Control_Action_Item__ran_ControlActionParameters_List));

    ControlAction_RANParameter_Item_t *ctrlActionRanItem = (ControlAction_RANParameter_Item_t*)calloc(paraSize, sizeof(ControlAction_RANParameter_Item_t));

    xer_fprint(stderr, &asn_DEF_RANFunctionDefinition_Control_Action_Item, ranFunCtrlActionItem);

    for(int i=0;i<paraSize;i++){
        rcFillCtrlActionRanParameterItem(&ctrlActionRanItem[i], i);
        ASN_SEQUENCE_ADD(&ranFunCtrlActionItem->ran_ControlActionParameters_List->list, ctrlActionRanItem+i);
    }

}

uint8_t rcFillRanFuncDefiControl(RANFunctionDefinition_Control_t **ranFuncDefi){
    uint8_t styleName[] = "Radio resource allocation control";

    *ranFuncDefi = (RANFunctionDefinition_Control_t*)calloc(1, sizeof(RANFunctionDefinition_Control_t));

    RANFunctionDefinition_Control_Item_t *ranFuncCtrlItem = (RANFunctionDefinition_Control_Item_t*)calloc(1, sizeof(RANFunctionDefinition_Control_Item_t));
    ranFuncCtrlItem->ric_ControlStyle_Type = 2;
    ranFuncCtrlItem->ric_ControlMessageFormat_Type = 1;
    ranFuncCtrlItem->ric_ControlHeaderFormat_Type = 1;
    ranFuncCtrlItem->ric_ControlOutcomeFormat_Type = 1;

    ranFuncCtrlItem->ric_ControlStyle_Name.size  = sizeof(styleName)-1;
    ranFuncCtrlItem->ric_ControlStyle_Name.buf = (uint8_t*)calloc(sizeof(styleName), sizeof(uint8_t));
    memcpy(ranFuncCtrlItem->ric_ControlStyle_Name.buf, styleName, ranFuncCtrlItem->ric_ControlStyle_Name.size);

    ranFuncCtrlItem->ric_ControlAction_List = (struct RANFunctionDefinition_Control_Item__ric_ControlAction_List*)calloc(1, sizeof(struct RANFunctionDefinition_Control_Item__ric_ControlAction_List));

    RANFunctionDefinition_Control_Action_Item_t *ranFunCtrlActionItem = (RANFunctionDefinition_Control_Action_Item_t*)calloc(1, sizeof(RANFunctionDefinition_Control_Action_Item_t));
    rcFillRanFuncDefiCtrlActionItem(ranFunCtrlActionItem);

    ASN_SEQUENCE_ADD(&ranFuncCtrlItem->ric_ControlAction_List->list, ranFunCtrlActionItem);
    ASN_SEQUENCE_ADD(&(*ranFuncDefi)->ric_ControlStyle_List.list, ranFuncCtrlItem);

}

uint8_t rcFillE2SetupReq(RANfunctionDefinition_t  *ranFunDefinition){
    uint8_t arrIdx = 0;
    int8_t ret = 0;
    asn_codec_ctx_t *opt_cod;
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.1.2.3"; // RAN function service model OID

    E2SM_RC_RANFunctionDefinition_t *ranfunc_desc = (E2SM_RC_RANFunctionDefinition_t*)calloc(1, sizeof(E2SM_RC_RANFunctionDefinition_t));
    long *inst;

    ASN_STRUCT_RESET(asn_DEF_E2SM_RC_RANFunctionDefinition, ranfunc_desc);

    rcFillRanFunctionName(&ranfunc_desc->ranFunction_Name);
    rcFillRanFuncDefiControl(&ranfunc_desc->ranFunctionDefinition_Control);

    xer_fprint(stderr, &asn_DEF_E2SM_RC_RANFunctionDefinition, ranfunc_desc);

    // encode the E2SM-KPM message into the E2AP buffer (OCTET_STRING_t in E2AP)

    uint8_t e2smbuffer[8192];
    size_t e2smbuffer_size = 8192;
    asn_enc_rval_t     encRetVal;

    encRetVal = asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_RC_RANFunctionDefinition,
         ranfunc_desc, e2smbuffer, e2smbuffer_size);
    
    if(encRetVal.encoded == -1)
        return -1;

    // OCTET_STRING_t *ranfunc_ostr = (OCTET_STRING_t*)calloc(1,sizeof(OCTET_STRING_t));
    // ranfunc_ostr->buf = (uint8_t*)calloc(encRetVal.encoded, sizeof(uint8_t));
    // ranfunc_ostr->size = encRetVal.encoded;
    // memcpy(ranfunc_ostr->buf, e2smbuffer, encRetVal.encoded);

    ranFunDefinition->buf = (uint8_t*)calloc(encRetVal.encoded, sizeof(uint8_t));
    ranFunDefinition->size = encRetVal.encoded;
    memcpy(ranFunDefinition->buf, e2smbuffer, encRetVal.encoded);

    return ret;
}
