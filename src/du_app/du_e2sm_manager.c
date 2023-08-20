#include "du_e2sm_manager.h"

/*******************************************************************
 *
 * @brief Initialize the E2SM Manager
 *
 * @details
 *
 *    Function : smInit
 *
 *    Functionality: Initialize the parameters in the E2SM Manager
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smInit(){
    uint8_t oid_e2kpmv2[] = "1.3.6.1.4.1.53148.1.2.2.2";
    uint8_t oid_e2kpmv3[] = "1.3.6.1.4.1.53148.1.3.2.2";
    uint8_t oid_e2rc[] = "1.3.6.1.4.1.53148.1.1.2.3";

    kpmInit();

    ranFuncInfo[INDEX_OF_KPM_V2].fillRanFuncDescription = kpmFillRanFuncDescription;
    ranFuncInfo[INDEX_OF_KPM_V2].decapActionDefinition = kpmProcActionDefinition;
    ranFuncInfo[INDEX_OF_KPM_V2].decapEventTrigDefinition = kpmProcEventTrigDefinitionFormat1;
    ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionId = 168;
    ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionRev = 2;
    strcpy(ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionOId, oid_e2kpmv2);
    
    ranFuncInfo[INDEX_OF_KPM_V3].fillRanFuncDescription = kpmFillRanFuncDescriptionV3;
    ranFuncInfo[INDEX_OF_KPM_V3].decapActionDefinition = kpmProcActionDefinitionV3;
    ranFuncInfo[INDEX_OF_KPM_V3].decapEventTrigDefinition = kpmProcEventTrigDefinitionFormat1;
    ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionId = 2;
    ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionRev = 3;
    strcpy(ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionOId, oid_e2kpmv3);

    ranFuncInfo[INDEX_OF_RC].fillRanFuncDescription = rcFillRanFuncDescription;
    ranFuncInfo[INDEX_OF_RC].procRicCtrlHeader = rcProcCtrlHeader;
    ranFuncInfo[INDEX_OF_RC].procRicCtrlMessage = rcProcCtrlMessage;
    ranFuncInfo[INDEX_OF_RC].ranFunctionId = 3;
    ranFuncInfo[INDEX_OF_RC].ranFunctionRev = 1;
    strcpy(ranFuncInfo[INDEX_OF_RC].ranFunctionOId, oid_e2rc);

    return ROK;
}

/*******************************************************************
 *
 * @brief Fills the RAN Function items infos
 *
 * @details
 *
 *    Function : smFillRanFuncItemInfo
 *
 *    Functionality: Fills the RANfunction_ItemIEs_t
 *
 * @param[in] ranfunc_item, RANfunction_ItemIEs_t* for destination
 * @param[in] info, RanFuncInfo for source info
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smFillRanFuncItemInfo(RANfunction_ItemIEs_t *ranfunc_item, RanFuncInfo *info){
    ranfunc_item->id = ProtocolIE_IDE2_id_RANfunction_Item;
    ranfunc_item->criticality = Criticality_reject;
    ranfunc_item->value.present = RANfunction_ItemIEs__value_PR_RANfunction_Item;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionID = info->ranFunctionId;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionRevision = info->ranFunctionRev;

    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size = strlen(info->ranFunctionOId);
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf = (uint8_t*)calloc(strlen(info->ranFunctionOId), sizeof(uint8_t));
    memcpy(ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf, info->ranFunctionOId, ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size);
}

/*******************************************************************
 *
 * @brief Fills the E2 Setup Request RAN Function infos 
 *
 * @details
 *
 *    Function : smFillE2SetupReq
 *
 *    Functionality: Fills the RANfunctions_List_t by iterativing the all E2SM Module
 *
 * @param[in] ranfun_list, RANfunctions_List_t*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smFillE2SetupReq(RANfunctions_List_t  *ranfun_list){
    smInit();
    printf("\nINFO   -->  E2SM Manager : List all RAN functions<<<<\n");

    // Fill RAN Function item in E2AP
    RANfunction_ItemIEs_t *ranfunc_item;
    ranfunc_item = (RANfunction_ItemIEs_t*)calloc(USING_SERVICE_MODEL, sizeof(RANfunction_ItemIEs_t));

    for(int i=0;i<USING_SERVICE_MODEL;i++){
        smFillRanFuncItemInfo(&ranfunc_item[i], &ranFuncInfo[i]);
        ranFuncInfo[i].fillRanFuncDescription(&ranfunc_item[i].value.choice.RANfunction_Item.ranFunctionDefinition);
        xer_fprint(stderr, &asn_DEF_RANfunction_ItemIEs, &ranfunc_item[i]);
        ASN_SEQUENCE_ADD(&ranfun_list->list, &ranfunc_item[i]);
    }
}

/*******************************************************************
 *
 * @brief Process the RIC Control Header
 *
 * @details
 *
 *    Function : smProcRicCtrlHeader
 *
 *    Functionality: Maps the RICcontrolHeader_t to the respective E2SM Module
 *
 * @param[in] ricCtrlHdr, RICcontrolHeader_t*
 * @param[in] ranFuncId, uint32_t*
 * @param[in] reqId, long*
 * @param[in] instanceId, long*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smProcRicCtrlHeader(RICcontrolHeader_t *ricCtrlHdr, uint32_t ranFuncId, long reqId, long instanceId){
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].procRicCtrlHeader(ricCtrlHdr);
        }
    }
    DU_LOG("\nERROR  -->  E2SM Manager : Unknown RAN function ID");
    return RFAILED;
}

/*******************************************************************
 *
 * @brief Process the RIC Control Message
 *
 * @details
 *
 *    Function : smProcRicCtrlMessage
 *
 *    Functionality: Maps the RICcontrolMessage_t to the respective E2SM Module
 *
 * @param[in] ricCtrlHdr, RICcontrolMessage_t*
 * @param[in] ranFuncId, uint32_t*
 * @param[in] reqId, long*
 * @param[in] instanceId, long*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smProcRicCtrlMessage(RICcontrolMessage_t *ricCtrlMsg, uint32_t ranFuncId, long reqId, long instanceId){
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].procRicCtrlMessage(ricCtrlMsg);
        }
    }
    DU_LOG("\nERROR  -->  E2SM Manager : Unknown RAN function ID");
    return RFAILED;
}

/*******************************************************************
 *
 * @brief Process the Event Trigger Definition
 *
 * @details
 *
 *    Function : smProcEventTrigDefinition
 *
 *    Functionality: Maps the RICeventTriggerDefinition_t to the respective E2SM Module
 *
 * @param[in] eventTrigDefini, RICeventTriggerDefinition_t*
 * @param[in] ranFuncId, uint32_t*
 * @param[in] reqId, long*
 * @param[in] instanceId, long*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smProcEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefini, uint32_t ranFuncId, long reqId, long instanceId){
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].decapEventTrigDefinition(eventTrigDefini);
        }
    }
    DU_LOG("\nERROR  -->  E2SM Manager : Unknown RAN function ID");
    return RFAILED;
}

/*******************************************************************
 *
 * @brief Process the Action Definition
 *
 * @details
 *
 *    Function : smProcActionDefinition
 *
 *    Functionality: Maps the RICactionDefinition_t to the respective E2SM Module
 *
 * @param[in] acitiondifin, RICactionDefinition_t*
 * @param[in] ranFuncId, uint32_t*
 * @param[in] reqId, long*
 * @param[in] instanceId, long*
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t smProcActionDefinition(RICactionDefinition_t *acitiondifin, uint32_t ranFuncId, long reqId, long instanceId){
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].decapActionDefinition(acitiondifin);
        }
    }
    DU_LOG("\nERROR  -->  E2SM Manager : Unknown RAN function ID");
    return RFAILED;
}
