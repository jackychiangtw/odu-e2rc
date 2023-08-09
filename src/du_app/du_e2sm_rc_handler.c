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

/*******************************************************************
 *
 * @brief Process the Parameter ID and and fill in RRM Policy
 *
 * @details
 *
 *    Function : rcProcRrmPolicyValue
 *
 *    Functionality: Process and fill in RRM Policy
 *
 * @param[in] id, int, Parameter ID
 * @param[in] value, void, input value
 * @param[in] size, int, size of input value
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcRrmPolicyValue(int id, void *value, int size){
    int *intValue = (int*)value;
    char *charValue = (char*)value;
    static int memberIdx = 0;

    // TODO: use linked-list

    if(size){
        switch(id){
            case POLICY_RATIO_LIST:
            case POLICY_RATIO_GROUP:
            case RRM_POLICY:
            case POLICY_MEMBER_LIST:
            case POLICY_MEMBER:
            case POLICY_MEMBER_SNSSAI:
                break;
            case POLICY_MEMBER_PLMNID:
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].mcc, charValue, 3);
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].mnc, charValue+3, 3);
                break;
            case POLICY_MEMBER_SST:
                rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].sst = *charValue;
                break;
            case POLICY_MEMBER_SD:
                memcpy(rrmPolicyGroup[policyIdx].rRMPolicyMemberList[memberIdx].sd, charValue, 3);
                memberIdx++;
                break;
            case POLICY_MIN_PRB_RATIO:
                rrmPolicyGroup[policyIdx].rRMPolicyMinRatio = *intValue;
                break;
            case POLICY_MAX_PRB_RATIO:
                rrmPolicyGroup[policyIdx].rRMPolicyMaxRatio = *intValue;
                break;
            case POLICY_DED_PRB_RATIO:
                rrmPolicyGroup[policyIdx].rRMPolicyDedicatedRatio = *intValue;
                rrmPolicyGroup[policyIdx].id[0] = policyIdx + 1;
                rrmPolicyGroup[policyIdx].rRMMemberNum = memberIdx;
                policyIdx++;
                break;
            default:
                DU_LOG("\nERROR   -->  E2SM-RC : Invaild parameter ID, %d", id);
                return RFAILED;
        }
    }
    else{
         switch(id){
            case POLICY_RATIO_LIST:
                policyIdx = 0;
                memberIdx = 0;
                rrmPolicyGroup[policyIdx].resourceType = PRB;
                break;
            case RRM_POLICY:
                memberIdx = 0;
                break;
            case POLICY_MEMBER_LIST:
            case POLICY_RATIO_GROUP:
            case POLICY_MEMBER_PLMNID:
            case POLICY_MEMBER:
            case POLICY_MEMBER_SNSSAI:
            case POLICY_MEMBER_SST:
            case POLICY_MEMBER_SD:
            case POLICY_MIN_PRB_RATIO:
            case POLICY_MAX_PRB_RATIO:
            case POLICY_DED_PRB_RATIO:
                break;
            default:
                DU_LOG("\nERROR   -->  E2SM-RC : Invaild parameter ID, %d", id);
                return RFAILED;
                break;
         }
    }
    return ROK;
}

#ifndef O1_ENABLE
uint8_t setRrmPolicy(RrmPolicyList rrmPolicy[], uint8_t policyNum)
{
   DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC RRM number of policy %d,", \
	  policyNum);
   for(uint8_t i=0; i<policyNum ; i++)
   {
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  id = %d",rrmPolicy[i].id[0]);
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  resourceType = %d", \
		rrmPolicy[i].resourceType);
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  rRMPolicyMaxRatio = %d", \
		rrmPolicy[i].rRMPolicyMaxRatio);
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  rRMPolicyMinRatio = %d", \
		rrmPolicy[i].rRMPolicyMinRatio);
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  rRMPolicyDedicatedRatio = %d", \
		rrmPolicy[i].rRMPolicyDedicatedRatio);
      DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  rRMMemberNum = %d", \
		rrmPolicy[i].rRMMemberNum);
      for(uint8_t j=0; j<rrmPolicy[i].rRMMemberNum ; j++)
      {
         DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  mcc = %x %x %x", \
                 rrmPolicy[i].rRMPolicyMemberList[j].mcc[0], \
		 rrmPolicy[i].rRMPolicyMemberList[j].mcc[1], \
		 rrmPolicy[i].rRMPolicyMemberList[j].mcc[2]);
         DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  mnc = %x %x %x ", \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[0], \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[1], \
		   rrmPolicy[i].rRMPolicyMemberList[j].mnc[2]);

         DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  sd = %x %x %x", \
	           rrmPolicy[i].rRMPolicyMemberList[j].sd[0], \
		   rrmPolicy[i].rRMPolicyMemberList[j].sd[1], \
		   rrmPolicy[i].rRMPolicyMemberList[j].sd[2]);

         DU_LOG("\nINFO   -->  E2SM-RC : E2SM-RC  sst = %x \n", \
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
#endif

/*******************************************************************
 *
 * @brief Fill in the Octet String
 *
 * @details
 *
 *    Function : rcFillOctetString
 *
 *    Functionality: copy the memory from uint8_t src to Octet_String_t dst
 *
 * @param[in] dst, Octet_String_t* for destination
 * @param[in] src, uint8_t* for source
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillOctetString(OCTET_STRING_t *dst, uint8_t *src){
    dst->size = strlen((const char*)src);
    DU_ALLOC(dst->buf, dst->size);
    if(dst->buf == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC:  Memory allocation for rcFillOctetString failed %d",__LINE__);
        return RFAILED;
    }
    memcpy(dst->buf, src, dst->size);
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the item in the structure
 *
 * @details
 *
 *    Function : rcProcRanStructItem
 *
 *    Functionality: Process the RANParameter_STRUCTURE_Item_t
 *
 * @param[in] ranStructItem, RANParameter_STRUCTURE_Item_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcRanStructItem(RANParameter_STRUCTURE_Item_t *ranStructItem){
    uint8_t ret = ROK;
    ret = rcProcRrmPolicyValue(ranStructItem->ranParameter_ID, 0, 0);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to process RAN Parameter %d",__LINE__);
        return RFAILED;
    }

    if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
        DU_LOG("\nERROR  -->  E2SM-RC : Control Message Element True Item isn't supported\n");
        return RFAILED;
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
        ret = rcProcRanElemFalse(ranStructItem->ranParameter_valueType->choice.ranP_Choice_ElementFalse, ranStructItem->ranParameter_ID);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process element false %d",__LINE__);
            return RFAILED;
        }
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_Structure){
        ret = rcProcRanStruct(ranStructItem->ranParameter_valueType->choice.ranP_Choice_Structure);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process structure %d",__LINE__);
            return RFAILED;
        }
    }
    else if(ranStructItem->ranParameter_valueType->present == RANParameter_ValueType_PR_ranP_Choice_List){
        ret = rcProcRanList(ranStructItem->ranParameter_valueType->choice.ranP_Choice_List);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process list, %d",__LINE__);
            return RFAILED;
        }
    }
    else{
        DU_LOG("\nERROR  -->  E2SM-RC : Unknown Control Message Element Item\n");
        return ROK;
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the item in the choice structure
 *
 * @details
 *
 *    Function : rcProcRanStructItem
 *
 *    Functionality: Process the RANParameter_ValueType_Choice_Structure_t
 *
 * @param[in] ranParaChoiceStruct, RANParameter_ValueType_Choice_Structure_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcRanStruct(RANParameter_ValueType_Choice_Structure_t *ranParaChoiceStruct){
    uint8_t ret;
    RANParameter_STRUCTURE_t *ranParaStruct = ranParaChoiceStruct->ranParameter_Structure;
    for(int i=0;i<ranParaStruct->sequence_of_ranParameters->list.count;i++){
        ret = rcProcRanStructItem(ranParaStruct->sequence_of_ranParameters->list.array[i]);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process structure item, %d",__LINE__);
            return RFAILED;
        }
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the structure in the choice list
 *
 * @details
 *
 *    Function : rcProcRanList
 *
 *    Functionality: Process the RANParameter_ValueType_Choice_List_t
 *
 * @param[in] ranParaChoiceList, RANParameter_ValueType_Choice_List_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcRanList(RANParameter_ValueType_Choice_List_t *ranParaChoiceList){
    uint8_t ret;
    RANParameter_LIST_t *ranParaList = ranParaChoiceList->ranParameter_List;
    for(int i=0;i<ranParaList->list_of_ranParameter.list.count;i++){
        RANParameter_STRUCTURE_t *ranParaStruct = ranParaList->list_of_ranParameter.list.array[i];
        if(ranParaStruct == NULLP){
            DU_LOG("\nERROR  --> E2SM-RC: List's item is empty, %d",__LINE__);
            return RFAILED;
        }
        for(int j=0;j<ranParaStruct->sequence_of_ranParameters->list.count;j++){
            ret = rcProcRanStructItem(ranParaStruct->sequence_of_ranParameters->list.array[j]);
            if(ret != ROK){
                DU_LOG("\nERROR  --> E2SM-RC: Failed to process list, %d",__LINE__);
                return RFAILED;
            }
        }
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the false element and fill in the RRM policy
 *
 * @details
 *
 *    Function : rcProcRanElemFalse
 *
 *    Functionality: Process the RANParameter_ValueType_Choice_ElementFalse_t
 *
 * @param[in] ranParaChoiceList, RANParameter_ValueType_Choice_ElementFalse_t*
 * @param[in] id, int, the Parameter ID of the false element
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcRanElemFalse(RANParameter_ValueType_Choice_ElementFalse_t *ranParaChoiceElementFalse, int id){
    uint8_t ret;
    RANParameter_Value_t *ranParaValue = ranParaChoiceElementFalse->ranParameter_value;
    switch(ranParaValue->present){
        case RANParameter_Value_PR_valueOctS:
            rcProcRrmPolicyValue(id, ranParaValue->choice.valueOctS.buf, ranParaValue->choice.valueOctS.size);
            if(ret != ROK){
                DU_LOG("\nERROR  --> E2SM-RC: Failed to process RAN Parameter %d",__LINE__);
                return RFAILED;
            }
            break;
        case RANParameter_Value_PR_valueInt:
            rcProcRrmPolicyValue(id, &ranParaValue->choice.valueInt, 1);
            if(ret != ROK){
                DU_LOG("\nERROR  --> E2SM-RC: Failed to process RAN Parameter %d",__LINE__);
                return RFAILED;
            }
            break;
        default:
            DU_LOG("\nERROR  -->  E2SM-RC : Value type isn't supported\n");
            return RFAILED;
            break;
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the item (structure) of Control Message format 1 list
 *
 * @details
 *
 *    Function : rcProcMessageFrmt1Item
 *
 *    Functionality: Process the E2SM_RC_ControlMessage_Format1_Item_t
 *
 * @param[in] ctrlFrmt1, E2SM_RC_ControlMessage_Format1_Item_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcMessageFrmt1Item(E2SM_RC_ControlMessage_Format1_Item_t *ctrlFrmt1){
    uint8_t ret;
    ret = rcProcRrmPolicyValue(ctrlFrmt1->ranParameter_ID, 0, 0);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to process RAN Parameter, %d",__LINE__);
        return RFAILED;
    }

    if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementTrue){
        DU_LOG("\nERROR  -->  E2SM-RC : Control Message Element True Item isn't supported\n");
        return RFAILED;
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_ElementFalse){
        ret = rcProcRanElemFalse(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_ElementFalse, ctrlFrmt1->ranParameter_ID);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process false element, %d",__LINE__);
            return RFAILED;
        }
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_Structure){
        ret = rcProcRanStruct(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_Structure);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process structure, %d",__LINE__);
            return RFAILED;
        }
    }
    else if(ctrlFrmt1->ranParameter_valueType.present == RANParameter_ValueType_PR_ranP_Choice_List){
        ret = rcProcRanList(ctrlFrmt1->ranParameter_valueType.choice.ranP_Choice_List);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process list, %d",__LINE__);
            return RFAILED;
        }
    }
    else{
        DU_LOG("\nERROR  -->  E2SM-RC : Unknown Control Message Element Item\n");
        return RFAILED;
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Process the structure of Control Message format 1 (list)
 *
 * @details
 *
 *    Function : rcProcMessageFrmt1List
 *
 *    Functionality: Process the E2SM_RC_ControlMessage_Format1_t
 *
 * @param[in] ctrlFrmt1_list, E2SM_RC_ControlMessage_Format1_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcMessageFrmt1List(E2SM_RC_ControlMessage_Format1_t *ctrlFrmt1_list){
    uint8_t ret;
    for(int i=0;i<ctrlFrmt1_list->ranP_List.list.count;i++){
        ret = rcProcMessageFrmt1Item(ctrlFrmt1_list->ranP_List.list.array[i]);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process list, %d",__LINE__);
            return RFAILED;
        }
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Print the RRM Policy
 *
 * @details
 *
 *    Function : rcProcMessageFrmt1List
 *
 *    Functionality: Print the RRM Policy and its value
 *
 * @param[in] policyNum, int, the number of policy group
 * @return void
 *
 ******************************************************************/

void printRrmPolicy(int policyNum){
    for(int i=0;i<policyNum;i++){
        DU_LOG("\nINFO   -->  E2SM-RC : Policy Group %d:\n", i);
        int memberNum = rrmPolicyGroup[i].rRMMemberNum;
        for(int j=0;j<memberNum;j++){
            DU_LOG("\tMember %d:\n", j);
            DU_LOG("\t\tPLMN ID: ");
            for(int k=0;k<3;k++){
                DU_LOG("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].mcc[k]);
            }
            for(int k=0;k<3;k++){
                DU_LOG("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].mnc[k]);
            }
            DU_LOG("\n\t\tS-NSSAI: %x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].sst);
            for(int k=0;k<3;k++){
                DU_LOG("%x ", rrmPolicyGroup[i].rRMPolicyMemberList[j].sd[k]);
            }
            DU_LOG("\n");
        }
        DU_LOG("\tMin PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyMinRatio);
        DU_LOG("\tMax PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyMaxRatio);
        DU_LOG("\tDed PRB Ratio = %d\n", rrmPolicyGroup[i].rRMPolicyDedicatedRatio);
    }
}

/*******************************************************************
 *
 * @brief Process the Control Message
 *
 * @details
 *
 *    Function : rcProcCtrlMessage
 *
 *    Functionality: Process the RICcontrolMessage_t and send slice reconfiguration
 *
 * @param[in] ricControlMessage, RICcontrolMessage_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcCtrlMessage(RICcontrolMessage_t *ricControlMessage){
    asn_dec_rval_t  rval;
    uint8_t ret;
    E2SM_RC_ControlMessage_t *ctrlMessage = (E2SM_RC_ControlMessage_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_t));
    // DU_ALLOC(ctrlMessage, sizeof(E2SM_RC_ControlMessage_t));
    if(ctrlMessage == NULLP){
        DU_LOG("\nERROR   -->  E2SM-RC : Memory allocation for ctrlMessage failed");
        return RFAILED;
    }
    DU_LOG("\nINFO   -->  E2SM-RC : Process RIC Control Message<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlMessage, (void **)&ctrlMessage, ricControlMessage->buf, ricControlMessage->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
        DU_LOG("\nERROR  -->  E2SM-RC : Control Message ASN decode failed %d, %ld\n", rval.code, rval.consumed);
        return RFAILED;
    }else{
        xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlMessage, ctrlMessage);
    }
    if(ctrlMessage->ric_controlMessage_formats.present == E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format2){
        DU_LOG("\nERROR  -->  E2SM-RC : Control Message format 2 isn't supported\n");
        return RFAILED;
    }
    else{
        policyIdx = 0;
        ret = rcProcMessageFrmt1List(ctrlMessage->ric_controlMessage_formats.choice.controlMessage_Format1);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to process list of Format 1, %d",__LINE__);
            return RFAILED;
        }
        printRrmPolicy(policyIdx);
        setRrmPolicy(rrmPolicyGroup, policyIdx);
        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, ctrlMessage);
        return ROK;
    }
}

/*******************************************************************
 *
 * @brief Process the Control Header
 *
 * @details
 *
 *    Function : rcProcCtrlHeader
 *
 *    Functionality: Process the RICcontrolHeader_t
 *
 * @param[in] ricControlHeader, RICcontrolHeader_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcProcCtrlHeader(RICcontrolHeader_t *ricControlHeader){
    asn_dec_rval_t  rval;
    E2SM_RC_ControlHeader_t *ctrlHeader = (E2SM_RC_ControlHeader_t*)calloc(1, sizeof(E2SM_RC_ControlHeader_t));
    // DU_ALLOC(ctrlHeader ,sizeof(E2SM_RC_ControlHeader_t));
    if(ctrlHeader == NULLP){
        DU_LOG("\nERROR   -->  E2SM-RC : Memory allocation for ctrlHeader failed");
        return RFAILED;
    }
    DU_LOG("\nINFO   -->  E2SM-RC : Process RIC Control Header<<<<\n");
    rval = aper_decode(0, &asn_DEF_E2SM_RC_ControlHeader, (void **)&ctrlHeader, ricControlHeader->buf, ricControlHeader->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
        DU_LOG("\nERROR  -->  E2SM-RC : Control Header ASN decode failed\n");
        return RFAILED;
    }else{
        xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlHeader, ctrlHeader);
    }
    DU_LOG("\nINFO  -->  E2SM-RC : Header Format = %d", ctrlHeader->ric_controlHeader_formats.present);
    DU_LOG("\nINFO  -->  E2SM-RC : RIC Style Type = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_Style_Type);
    DU_LOG("\nINFO  -->  E2SM-RC : RIC Control Action ID = %ld", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_ControlAction_ID);
    if(ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_Style_Type != RADIO_RESOURCE_ALLOCATION){
        DU_LOG("\nINFO  -->  E2SM-RC : E2SM-RC handler doesn't support RIC Style Type, %d", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_Style_Type);
        return RFAILED;
    }
    if(ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_ControlAction_ID != SLICE_LEVEL_PRB_QUOTA){
        DU_LOG("\nINFO  -->  E2SM-RC : E2SM-RC handler doesn't support RIC Style Type, %d", ctrlHeader->ric_controlHeader_formats.choice.controlHeader_Format1->ric_ControlAction_ID);
        return RFAILED;
    }
    ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, ctrlHeader);
    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the RAN Function Name for RAN Function Description
 *
 * @details
 *
 *    Function : rcFillRanFunctionName
 *
 *    Functionality: Fills the RANfunction_Name_t for RAN Function Description
 *
 * @param[in] ranFuncName, RANfunction_Name_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillRanFunctionName(RANfunction_Name_t *ranFuncName){
    uint8_t ret;
    uint8_t shortName[] = "ORAN-E2SM-RC";
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.1.2.3"; // RAN function service model OID
    uint8_t description[] = "RAN Control";
    ret = rcFillOctetString(&ranFuncName->ranFunction_ShortName, shortName);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign shortName, %d",__LINE__);
        return RFAILED;
    }
    rcFillOctetString(&ranFuncName->ranFunction_Description, description);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign Description, %d",__LINE__);
        return RFAILED;
    }
    rcFillOctetString(&ranFuncName->ranFunction_E2SM_OID, ranfunc_oid);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign OID, %d",__LINE__);
        return RFAILED;
    }
    xer_fprint(stderr, &asn_DEF_RANfunction_Name, ranFuncName);
    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the RAN Parameter of Control Action Item to indicate the supported RAN Parameter
 *
 * @details
 *
 *    Function : rcFillCtrlActionRanParameterItem
 *
 *    Functionality: Fills the ControlAction_RANParameter_Item_t
 *
 * @param[in] ctrlActionRanParaItem, ControlAction_RANParameter_Item_t*
 * @param[in] index, int, the number of Parameter Name and ID
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillCtrlActionRanParameterItem(ControlAction_RANParameter_Item_t *ctrlActionRanParaItem, int index){
    uint8_t ret;
    char parameterName[][30] = {"PLMN Identity", "SST", "SD", "Min PRB Policy Ratio", "Max PRB Policy Ratio", "Ded PRB Policy Ratio"};
    int parameterId[] = {7, 9, 10, 11, 12, 13};

    ctrlActionRanParaItem->ranParameter_ID = parameterId[index];
    ret = rcFillOctetString(&ctrlActionRanParaItem->ranParameter_name, parameterName[index]);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign parameter Item, %d",__LINE__);
        return RFAILED;
    }
    xer_fprint(stderr, &asn_DEF_ControlAction_RANParameter_Item, ctrlActionRanParaItem);
    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the Contol Action Item to indicate the supported Control Action
 *
 * @details
 *
 *    Function : rcFillRanFuncDefiCtrlActionItem
 *
 *    Functionality: Fills the RANFunctionDefinition_Control_Action_Item_t
 *
 * @param[in] ranFunCtrlActionItem, RANFunctionDefinition_Control_Action_Item_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillRanFuncDefiCtrlActionItem(RANFunctionDefinition_Control_Action_Item_t *ranFunCtrlActionItem){
    uint8_t actionName[] = "Slice-level PRB quota";
    uint8_t ret;
    ranFunCtrlActionItem->ric_ControlAction_ID = SLICE_LEVEL_PRB_QUOTA;
    
    ret = rcFillOctetString(&ranFunCtrlActionItem->ric_ControlAction_Name, actionName);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign action name, %d",__LINE__);
        return RFAILED;
    }
    DU_ALLOC(ranFunCtrlActionItem->ran_ControlActionParameters_List, sizeof(struct RANFunctionDefinition_Control_Action_Item__ran_ControlActionParameters_List));
    if(ranFunCtrlActionItem->ran_ControlActionParameters_List == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for contorl action paramter list failed, %d",__LINE__);
        return RFAILED;
    }
    ControlAction_RANParameter_Item_t *ctrlActionRanItem;
    DU_ALLOC(ctrlActionRanItem, PARAMETER_SIZE * sizeof(ControlAction_RANParameter_Item_t));
    if(ranFunCtrlActionItem->ran_ControlActionParameters_List == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for contorl action RAN parameter item failed, %d",__LINE__);
        return RFAILED;
    }
    xer_fprint(stderr, &asn_DEF_RANFunctionDefinition_Control_Action_Item, ranFunCtrlActionItem);

    for(int i=0;i<PARAMETER_SIZE;i++){
        ret = rcFillCtrlActionRanParameterItem(&ctrlActionRanItem[i], i);
        if(ret != ROK){
            DU_LOG("\nERROR  --> E2SM-RC: Failed to assign contorl action RAN parameter item, %d",__LINE__);
            return RFAILED;
        }
        ASN_SEQUENCE_ADD(&ranFunCtrlActionItem->ran_ControlActionParameters_List->list, ctrlActionRanItem+i);
    }
    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the RAN Function Definition Control
 *
 * @details
 *
 *    Function : rcFillRanFuncDefiControl
 *
 *    Functionality: Fills the RANFunctionDefinition_Control_t
 *
 * @param[in] ranFuncDefi, RANFunctionDefinition_Control_t**
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillRanFuncDefiControl(RANFunctionDefinition_Control_t **ranFuncDefi){
    uint8_t styleName[] = "Radio resource allocation control";
    uint8_t ret;
    DU_ALLOC(*ranFuncDefi, sizeof(RANFunctionDefinition_Control_t));
    if(*ranFuncDefi == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for RAN Function Definition Control failed, %d",__LINE__);
        return RFAILED;
    }

    RANFunctionDefinition_Control_Item_t *ranFuncCtrlItem;
    DU_ALLOC(ranFuncCtrlItem, sizeof(RANFunctionDefinition_Control_Item_t)); 
    if(ranFuncCtrlItem == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for RAN Function Definition item failed, %d", __LINE__);
        return RFAILED;
    }
    ranFuncCtrlItem->ric_ControlStyle_Type = RADIO_RESOURCE_ALLOCATION;
    ranFuncCtrlItem->ric_ControlMessageFormat_Type = 1;
    ranFuncCtrlItem->ric_ControlHeaderFormat_Type = 1;
    ranFuncCtrlItem->ric_ControlOutcomeFormat_Type = 1;

    ret = rcFillOctetString(&ranFuncCtrlItem->ric_ControlStyle_Name, styleName);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign control style name, %d", __LINE__);
        return RFAILED;
    }
    
    DU_ALLOC(ranFuncCtrlItem->ric_ControlAction_List, sizeof(struct RANFunctionDefinition_Control_Item__ric_ControlAction_List));
    if(ranFuncCtrlItem->ric_ControlAction_List == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for RAN Function Definition item control action list failed, %d", __LINE__);
        return RFAILED;
    }
    
    RANFunctionDefinition_Control_Action_Item_t *ranFunCtrlActionItem;
    DU_ALLOC(ranFunCtrlActionItem, sizeof(RANFunctionDefinition_Control_Action_Item_t));
    if(ranFunCtrlActionItem == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for RAN Function Definition item control action list item failed, %d", __LINE__);
        return RFAILED;
    }
    ret = rcFillRanFuncDefiCtrlActionItem(ranFunCtrlActionItem);
    if(ret != NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to fill RAN function definition item, %d", __LINE__);
        return RFAILED;
    }
    ASN_SEQUENCE_ADD(&ranFuncCtrlItem->ric_ControlAction_List->list, ranFunCtrlActionItem);
    ASN_SEQUENCE_ADD(&(*ranFuncDefi)->ric_ControlStyle_List.list, ranFuncCtrlItem);
    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the RAN Function Definition
 *
 * @details
 *
 *    Function : rcFillRanFuncDescription
 *
 *    Functionality: Fills the RANfunctionDefinition_t for E2 Setup Request
 *
 * @param[in] ranFunDefinition, RANfunctionDefinition_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t rcFillRanFuncDescription(RANfunctionDefinition_t  *ranFunDefinition){
    uint8_t arrIdx = 0;
    int8_t ret = 0;
    asn_codec_ctx_t *opt_cod;
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.1.2.3"; // RAN function service model OID
    E2SM_RC_RANFunctionDefinition_t *ranfunc_desc;
    DU_ALLOC(ranfunc_desc, sizeof(E2SM_RC_RANFunctionDefinition_t));
    if(ranfunc_desc == NULLP){
        DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for ranfunc_desc failed, %d", __LINE__);
        return RFAILED;
    }

    ret = rcFillRanFunctionName(&ranfunc_desc->ranFunction_Name);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign RAN Function name, %d",__LINE__);
        return RFAILED;
    }
    ret = rcFillRanFuncDefiControl(&ranfunc_desc->ranFunctionDefinition_Control);
    if(ret != ROK){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign RAN Functio definition control, %d",__LINE__);
        return RFAILED;
    }
    xer_fprint(stderr, &asn_DEF_E2SM_RC_RANFunctionDefinition, ranfunc_desc);

    uint8_t e2smbuffer[8192];
    size_t e2smbuffer_size = 8192;
    asn_enc_rval_t     encRetVal;

    encRetVal = asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_RC_RANFunctionDefinition,
         ranfunc_desc, e2smbuffer, e2smbuffer_size);
    
    if(encRetVal.encoded == RC_FAIL){
        DU_LOG("\nERROR  --> E2SM-RC: Failed to assign RAN Functio definition control, %d",__LINE__);
        return RFAILED;
    }else{
        DU_ALLOC(ranFunDefinition->buf, encRetVal.encoded * sizeof(uint8_t));
        if(ranFunDefinition->buf == NULLP){
            DU_LOG("\nERROR  --> E2SM-RC: Memory allocation for RAN Function Definition failed, %d",__LINE__);
            return RFAILED;
        }
        ranFunDefinition->size = encRetVal.encoded;
        memcpy(ranFunDefinition->buf, e2smbuffer, encRetVal.encoded);
    }

    return ROK;
}
