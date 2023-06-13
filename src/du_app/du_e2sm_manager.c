#include "du_e2sm_manager.h"

<<<<<<< Updated upstream
RanFuncInfo ranFuncInfo[SIZE_OF_SERVICE_MODEL] = {{147, 2, "1.3.6.1.4.1.53148.1.2.2.2", }, {168, 3, "1.3.6.1.4.1.53148.1.2.3.2", }, {201, 3, "1.3.6.1.4.1.53148.1.1.2.3", }};

uint8_t smInit(){
    ranFuncInfo[INDEX_OF_KPM_V2].fillRanFuncDescription = kpmRanFuncDescription;
    ranFuncInfo[INDEX_OF_KPM_V2].decapActionDefinition = kpmDecapActionDefinition;
    ranFuncInfo[INDEX_OF_KPM_V2].decapEventTrigDefinition = decapEventTrigDefinitionFormat1;
=======
uint8_t smInit(){
    uint8_t oid_e2kpmv2[] = "1.3.6.1.4.1.53148.1.2.2.2";
    uint8_t oid_e2kpmv3[] = "1.3.6.1.4.1.53148.1.3.2.2";
    uint8_t oid_e2rc[] = "1.3.6.1.4.1.53148.1.1.2.3";

    ranFuncInfo[INDEX_OF_KPM_V2].fillRanFuncDescription = kpmRanFuncDescription;
    ranFuncInfo[INDEX_OF_KPM_V2].decapActionDefinition = kpmDecapActionDefinition;
    ranFuncInfo[INDEX_OF_KPM_V2].decapEventTrigDefinition = decapEventTrigDefinitionFormat1;
    ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionId = 168;
    ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionRev = 2;
    strcpy(ranFuncInfo[INDEX_OF_KPM_V2].ranFunctionOId, oid_e2kpmv2);
>>>>>>> Stashed changes
    
    ranFuncInfo[INDEX_OF_KPM_V3].fillRanFuncDescription = kpmRanFuncDescriptionV3;
    ranFuncInfo[INDEX_OF_KPM_V3].decapActionDefinition = kpmDecapActionDefinitionV3;
    ranFuncInfo[INDEX_OF_KPM_V3].decapEventTrigDefinition = decapEventTrigDefinitionFormat1;
<<<<<<< Updated upstream
=======
    ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionId = 2;
    ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionRev = 3;
    strcpy(ranFuncInfo[INDEX_OF_KPM_V3].ranFunctionOId, oid_e2kpmv3);
>>>>>>> Stashed changes

    ranFuncInfo[INDEX_OF_RC].fillRanFuncDescription = rcFillE2SetupReq;
    ranFuncInfo[INDEX_OF_RC].procRicCtrlHeader = procE2rcCtrlHeader;
    ranFuncInfo[INDEX_OF_RC].procRicCtrlMessage = procE2rcCtrlMessage;
<<<<<<< Updated upstream
=======
    ranFuncInfo[INDEX_OF_RC].ranFunctionId = 3;
    ranFuncInfo[INDEX_OF_RC].ranFunctionRev = 4;
    strcpy(ranFuncInfo[INDEX_OF_RC].ranFunctionOId, oid_e2rc);
>>>>>>> Stashed changes

    return ROK;
}

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

uint8_t smFillE2SetupReq(RANfunctions_List_t  *ranfun_list){
    smInit();
    printf("\nINFO   -->  E2SM Manager : List all RAN functions<<<<\n");

    // Fill RAN Function item in E2AP
    RANfunction_ItemIEs_t *ranfunc_item;
<<<<<<< Updated upstream
    ranfunc_item = (RANfunction_ItemIEs_t*)calloc(SIZE_OF_SERVICE_MODEL, sizeof(RANfunction_ItemIEs_t));

    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
=======
    ranfunc_item = (RANfunction_ItemIEs_t*)calloc(USING_SERVICE_MODEL, sizeof(RANfunction_ItemIEs_t));

    for(int i=0;i<USING_SERVICE_MODEL;i++){
>>>>>>> Stashed changes
        smFillRanFuncItemInfo(&ranfunc_item[i], &ranFuncInfo[i]);
        ranFuncInfo[i].fillRanFuncDescription(&ranfunc_item[i].value.choice.RANfunction_Item.ranFunctionDefinition);
        xer_fprint(stderr, &asn_DEF_RANfunction_ItemIEs, &ranfunc_item[i]);
        ASN_SEQUENCE_ADD(&ranfun_list->list, &ranfunc_item[i]);
    }
}

<<<<<<< Updated upstream
uint8_t smProcRicCtrlHeader(RICcontrolHeader_t *ricCtrlHdr, uint32_t ranFuncId){
=======
uint8_t smProcRicCtrlHeader(RICcontrolHeader_t *ricCtrlHdr, uint32_t ranFuncId, long reqId, long instanceId){
>>>>>>> Stashed changes
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].procRicCtrlHeader(ricCtrlHdr);
        }
    }
    return RFAILED;
}

<<<<<<< Updated upstream
uint8_t smProcRicCtrlMessage(RICcontrolMessage_t *ricCtrlMsg, uint32_t ranFuncId){
=======
uint8_t smProcRicCtrlMessage(RICcontrolMessage_t *ricCtrlMsg, uint32_t ranFuncId, long reqId, long instanceId){
>>>>>>> Stashed changes
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].procRicCtrlMessage(ricCtrlMsg);
        }
    }
    return RFAILED;
}

<<<<<<< Updated upstream
uint8_t smDecapEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefini, uint32_t ranFuncId){
=======
uint8_t smDecapEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefini, uint32_t ranFuncId, long reqId, long instanceId){
>>>>>>> Stashed changes
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].decapEventTrigDefinition(eventTrigDefini);
        }
    }
    return RFAILED;
}

<<<<<<< Updated upstream
uint8_t smDecapActionDefinition(RICactionDefinition_t *ricdifin, uint32_t ranFuncId){
=======
uint8_t smDecapActionDefinition(RICactionDefinition_t *ricdifin, uint32_t ranFuncId, long reqId, long instanceId){
>>>>>>> Stashed changes
    for(int i=0;i<SIZE_OF_SERVICE_MODEL;i++){
        if(ranFuncInfo[i].ranFunctionId == ranFuncId){
            return ranFuncInfo[i].decapActionDefinition(ricdifin);
        }
    }
    return RFAILED;
}
