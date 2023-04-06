#include "du_e2sm_kpm_handler.h"
#include "S-NSSAI.h"
#include "SD.h"
long thpDl = 0;


uint8_t fillRanFunctionName(RANfunction_Name_t *ranfunc_name){
    uint8_t ranfunc_defin[] = "ORAN-E2SM-KPM"; // RAN Function Definition,
    uint8_t ranfunc_descr[] = "KPM monitor"; // RAN function description
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.2.2.2"; // RAN function service model OID

    ranfunc_name->ranFunction_ShortName.size = sizeof(ranfunc_defin)-1;
    ranfunc_name->ranFunction_ShortName.buf = (uint8_t*)calloc(sizeof(ranfunc_defin), sizeof(uint8_t));
    memcpy(ranfunc_name->ranFunction_ShortName.buf, ranfunc_defin, ranfunc_name->ranFunction_ShortName.size);

    ranfunc_name->ranFunction_Description.size = sizeof(ranfunc_descr)-1;
    ranfunc_name->ranFunction_Description.buf = (uint8_t*)calloc(sizeof(ranfunc_descr), sizeof(uint8_t));
    memcpy(ranfunc_name->ranFunction_Description.buf, ranfunc_descr, ranfunc_name->ranFunction_Description.size);

    ranfunc_name->ranFunction_Instance = (long*)calloc(1,sizeof(long));
    *ranfunc_name->ranFunction_Instance = 1;

    ranfunc_name->ranFunction_E2SM_OID.size = sizeof(ranfunc_oid)-1;
    ranfunc_name->ranFunction_E2SM_OID.buf = (uint8_t*)calloc(sizeof(ranfunc_oid), sizeof(uint8_t));
    memcpy(ranfunc_name->ranFunction_E2SM_OID.buf, ranfunc_oid, ranfunc_name->ranFunction_E2SM_OID.size);

}

uint8_t fillTriggerStyleItem(RIC_EventTriggerStyle_Item_t **trigger_style){
    *trigger_style = (RIC_EventTriggerStyle_Item_t*)calloc(1, sizeof(RIC_EventTriggerStyle_Item_t));
    (*trigger_style)->ric_EventTriggerStyle_Type = 1; // KPM only supports type 1

    uint8_t trig_name[] = "Periodic report";
    (*trigger_style)->ric_EventTriggerStyle_Name.size = sizeof(trig_name)-1;
    (*trigger_style)->ric_EventTriggerStyle_Name.buf = (uint8_t*)calloc(sizeof(trig_name), sizeof(uint8_t));
    memcpy((*trigger_style)->ric_EventTriggerStyle_Name.buf, trig_name, (*trigger_style)->ric_EventTriggerStyle_Name.size);

    (*trigger_style)->ric_EventTriggerFormat_Type = 1;
}

uint8_t fillTriggerStyleList(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List **triggerStyleList){
    *triggerStyleList = (struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List*)calloc(1, sizeof(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List));
    RIC_EventTriggerStyle_Item_t *trigger_style = (RIC_EventTriggerStyle_Item_t*)calloc(1, sizeof(RIC_EventTriggerStyle_Item_t));
    fillTriggerStyleItem(&trigger_style); // fill one trigger style
    ASN_SEQUENCE_ADD(&(*triggerStyleList)->list, trigger_style);
}

uint8_t fillReportStyleItemStyle1(RIC_ReportStyle_Item_t *report_style){
    int measurementSize = sizeof(measurementStyle1) / sizeof(*measurementStyle1);

    report_style->ric_ReportStyle_Type = 1; // For Report
    uint8_t report_name[] = "O-DU Cell Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = sizeof(report_name)-1;
    report_style->ric_ReportStyle_Name.buf = (uint8_t*)calloc(sizeof(report_name), sizeof(uint8_t));
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 1;
    report_style->ric_ActionFormat_Type = 1; // new in KPM 2.0

    MeasurementInfo_Action_Item_t *measure_item;
    measure_item = (MeasurementInfo_Action_Item_t*)calloc(measurementSize, sizeof(MeasurementInfo_Action_Item_t));

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen(measurementStyle1[i]);
        measure_item[i].measName.buf = (uint8_t*)calloc(sizeof(measurementStyle1[i]), sizeof(uint8_t));
        memcpy(measure_item[i].measName.buf, measurementStyle1[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }
}

uint8_t fillReportStyleItemStyle2(RIC_ReportStyle_Item_t *report_style){
    int measurementSize = sizeof(measurementStyle2) / sizeof(*measurementStyle2);

    report_style->ric_ReportStyle_Type = 1; // For Report
    uint8_t report_name[] = "O-DU Slice Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = sizeof(report_name)-1;
    report_style->ric_ReportStyle_Name.buf = (uint8_t*)calloc(sizeof(report_name), sizeof(uint8_t));
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 2; // For single Slice
    report_style->ric_ActionFormat_Type = 3; // new in KPM 2.0

    MeasurementInfo_Action_Item_t *measure_item;
    measure_item = (MeasurementInfo_Action_Item_t*)calloc(measurementSize, sizeof(MeasurementInfo_Action_Item_t));

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen(measurementStyle2[i]);
        measure_item[i].measName.buf = (uint8_t*)calloc(sizeof(measurementStyle2[i]), sizeof(uint8_t));
        memcpy(measure_item[i].measName.buf, measurementStyle2[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }
}

uint8_t fillReportStyleList(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List **reportStyleList){
    *reportStyleList = (struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List*)calloc(1, sizeof(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List));
    RIC_ReportStyle_Item_t *report_style = (RIC_ReportStyle_Item_t*)calloc(2, sizeof(RIC_ReportStyle_Item_t));
    fillReportStyleItemStyle1(report_style);
    fillReportStyleItemStyle2(report_style+1);
    ASN_SEQUENCE_ADD(&(*reportStyleList)->list, report_style);
    ASN_SEQUENCE_ADD(&(*reportStyleList)->list, report_style+1);
}

uint8_t kpm(RANfunctions_List_t  *ranfun_list)
{
    uint8_t arrIdx = 0;
    int8_t ret = 0;
    asn_codec_ctx_t *opt_cod;
    uint8_t ranfunc_oid[] = "1.3.6.1.4.1.53148.1.2.2.2"; // RAN function service model OID

    E2SM_KPM_RANfunction_Description_t *ranfunc_desc = (E2SM_KPM_RANfunction_Description_t*)calloc(1, sizeof(E2SM_KPM_RANfunction_Description_t));
    long *inst;

    printf("\nINFO   -->  E2 Agent : List all RAN functions<<<<\n");
    ASN_STRUCT_RESET(asn_DEF_E2SM_KPM_RANfunction_Description, ranfunc_desc);

    fillRanFunctionName(&ranfunc_desc->ranFunction_Name);
    fillTriggerStyleList(&ranfunc_desc->ric_EventTriggerStyle_List);
    fillReportStyleList(&ranfunc_desc->ric_ReportStyle_List);


    xer_fprint(stderr, &asn_DEF_E2SM_KPM_RANfunction_Description, ranfunc_desc);

    // RAN Function item in E2AP
    RANfunction_ItemIEs_t *ranfunc_item;
    ranfunc_item = (RANfunction_ItemIEs_t*)calloc(1, sizeof(RANfunction_ItemIEs_t));
    ranfunc_item->id = ProtocolIE_IDE2_id_RANfunction_Item;
    ranfunc_item->criticality = Criticality_reject;
    ranfunc_item->value.present = RANfunction_ItemIEs__value_PR_RANfunction_Item;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionID = 1;

    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size = sizeof(ranfunc_oid);
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf = (uint8_t*)calloc(sizeof(ranfunc_oid), sizeof(uint8_t));
    memcpy(ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.buf, ranfunc_oid, ranfunc_item->value.choice.RANfunction_Item.ranFunctionOID.size);

    // encode the E2SM-KPM message into the E2AP buffer (OCTET_STRING_t in E2AP)

    uint8_t e2smbuffer[8192];
    size_t e2smbuffer_size = 8192;
    asn_enc_rval_t     encRetVal;

    encRetVal = asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_RANfunction_Description,
         ranfunc_desc, e2smbuffer, e2smbuffer_size);
    
    if(encRetVal.encoded == -1)
        return -1;

    OCTET_STRING_t *ranfunc_ostr = (OCTET_STRING_t*)calloc(1,sizeof(OCTET_STRING_t));
    ranfunc_ostr->buf = (uint8_t*)calloc(encRetVal.encoded, sizeof(uint8_t));
    ranfunc_ostr->size = encRetVal.encoded;
    memcpy(ranfunc_ostr->buf, e2smbuffer, encRetVal.encoded);

    ranfunc_item->value.choice.RANfunction_Item.ranFunctionDefinition.size = (uint8_t*)ranfunc_ostr->size;
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionDefinition.buf = (uint8_t*)calloc(ranfunc_ostr->size, sizeof(uint8_t));
    memcpy(ranfunc_item->value.choice.RANfunction_Item.ranFunctionDefinition.buf, ranfunc_ostr->buf, ranfunc_item->value.choice.RANfunction_Item.ranFunctionDefinition.size);
    ranfunc_item->value.choice.RANfunction_Item.ranFunctionRevision = 1;  

    xer_fprint(stderr, &asn_DEF_RANfunction_ItemIEs, ranfunc_item);

    // Fill in list of RAN funcion
    ASN_SEQUENCE_ADD(&ranfun_list->list, ranfunc_item);
    
    return ret;
}

uint8_t fillMeasInfoItem(MeasurementInfoItem_t *measInfoItem){
    char measureName[] = "DRB.UEThpDl";
    LabelInfoItem_t *measLabelInfo = (LabelInfoItem_t*)calloc(1, sizeof(LabelInfoItem_t)); // can't use malloc
    long *measLabelInfo_noLabel = (long*)malloc(sizeof(long));
    measInfoItem->measType.present = MeasurementType_PR_measName; // Choose name or ID

    measInfoItem->measType.choice.measName.size = sizeof(measureName);
    measInfoItem->measType.choice.measName.buf = (uint8_t*)calloc(sizeof(measureName), sizeof(uint8_t));
    memcpy(measInfoItem->measType.choice.measName.buf, measureName, measInfoItem->measType.choice.measName.size);

    *measLabelInfo_noLabel = MeasurementLabel__noLabel_true;
    measLabelInfo->measLabel.noLabel = measLabelInfo_noLabel;

    ASN_SEQUENCE_ADD(&measInfoItem->labelInfoList.list, measLabelInfo);
    //xer_fprint(stderr, &asn_DEF_MeasurementInfoItem, measInfoItem);

}


uint8_t fillActionDefinition(RICactionDefinition_t **ricdifin){ // for RIC Stub
    asn_enc_rval_t     encRetVal;
    asn_codec_ctx_t *opt_cod;
    E2SM_KPM_ActionDefinition_Format1_t *actionDefinFormat = (E2SM_KPM_ActionDefinition_Format1_t*)calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    *ricdifin = (RICactionDefinition_t*)malloc(sizeof(RICactionDefinition_t));

    printf("\nINFO   -->  E2 Agent : Print Action Definition<<<<\n");
    actionDefinFormat->granulPeriod = 100; // 100ms

    MeasurementInfoItem_t *measInfoItem;
    fillMeasInfoItem(measInfoItem);

    ASN_SEQUENCE_ADD(&actionDefinFormat->measInfoList.list, measInfoItem);

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;

    // Encode to OCTET STRING

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_ActionDefinition_Format1,
         actionDefinFormat, e2smbuffer, e2smbuffer_size);

    OCTET_STRING_t *ricdifin_ostr = (OCTET_STRING_t*)calloc(1,sizeof(OCTET_STRING_t));
    ricdifin_ostr->buf = (uint8_t*)calloc(er.encoded, sizeof(uint8_t));
    ricdifin_ostr->size = er.encoded;
    memcpy(ricdifin_ostr->buf,e2smbuffer,er.encoded);

    (*ricdifin)->size = ricdifin_ostr->size;
    (*ricdifin)->buf = (uint8_t*)malloc(ricdifin_ostr->size);
    memcpy((*ricdifin)->buf, ricdifin_ostr->buf, (*ricdifin)->size);

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_ActionDefinition_Format1, actionDefinFormat);


    printf("\nINFO   -->  E2 Agent : Print Action Definition End<<<<\n");

}

uint8_t fillEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *eventTrigDefi){ // for RIC Stub

    E2SM_KPM_EventTriggerDefinition_t *kpmEventTrig = (E2SM_KPM_EventTriggerDefinition_t*)calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));
    E2SM_KPM_EventTriggerDefinition_Format1_t *kpmEventTrigFormat1 = (E2SM_KPM_EventTriggerDefinition_Format1_t*)calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_Format1_t));

    printf("\nINFO   -->  E2 Agent : Fill Event Trigger Definition<<<<\n");

    kpmEventTrig->eventDefinition_formats.present = E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1;
    kpmEventTrig->eventDefinition_formats.choice.eventDefinition_Format1 = kpmEventTrigFormat1;
    kpmEventTrigFormat1->reportingPeriod = 1000; // 1000ms

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_EventTriggerDefinition,
         kpmEventTrig, e2smbuffer, e2smbuffer_size);

    eventTrigDefi->buf = (uint8_t*)calloc(1,er.encoded);
    eventTrigDefi->size = er.encoded;
    memcpy(eventTrigDefi->buf,e2smbuffer,er.encoded);

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_EventTriggerDefinition, kpmEventTrig);
    printf("\nINFO   -->  E2 Agent : Event Trigger Definition End<<<<\n");

}


uint8_t decapEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *defini){
    asn_dec_rval_t  rval;
    E2SM_KPM_EventTriggerDefinition_t *kpmEventTrig = (E2SM_KPM_EventTriggerDefinition_t*)calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));

    printf("\nINFO   -->  E2 Agent : Decap Event Trigger Definition<<<<\n");

    rval = aper_decode(0, &asn_DEF_E2SM_KPM_EventTriggerDefinition, (void **)&kpmEventTrig, defini->buf, defini->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
   {
      printf("\nERROR  -->  E2 Agent : ASN decode failed");
   }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_EventTriggerDefinition, kpmEventTrig);
    printf("\nINFO  -->  E2 Agent : Report Period is %d\n", kpmEventTrig->eventDefinition_formats.choice.eventDefinition_Format1->reportingPeriod);

}

uint8_t decapActionDefinition(RICactionDefinition_t *ricdifin){
    
    printf("\nINFO   -->  E2 Agent : Decap Action Definition<<<<\n");

    asn_dec_rval_t  rval;
    E2SM_KPM_ActionDefinition_t *actionDefin = (E2SM_KPM_ActionDefinition_t*)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));

    rval = aper_decode(0, &asn_DEF_E2SM_KPM_ActionDefinition, (void **)&actionDefin, ricdifin->buf, ricdifin->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
      printf("\nERROR  -->  E2 Agent : Action Definition decode failed %d\n", rval.code);
    }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_ActionDefinition, actionDefin);
    printf("\nINFO   -->  E2 Agent: RIC Style Type = %ld", actionDefin->ric_Style_Type);

    E2SM_KPM_ActionDefinition_Format1_t *actionDefinFormat1;
    switch(actionDefin->actionDefinition_formats.present){
        case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1:
            actionDefinFormat1 = actionDefin->actionDefinition_formats.choice.actionDefinition_Format1;
        break;
        default:
            printf("\nINFO   -->  E2 Agent: Action Definition Format doesn't support");
    }
    
    printf("\nINFO  -->  E2 Agent : Granularity Period is %d\n", actionDefinFormat1->granulPeriod);

    for(int i=0;i<actionDefinFormat1->measInfoList.list.count;i++){
        if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measID)
            printf("\nINFO  -->  E2 Agent : Measurement ID is %ld", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2 Agent : Measurement Name is %s", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
        }
        else{
            printf("\nINFO  -->  E2 Agent : Measurement type is invaild \n");
        }
    }
}


uint8_t fillIndicationHeaderFormat1(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1){

    //printf("Function \"%s\" is start\n", __func__);

    time_t now = time(NULL);
    unsigned long timestamp = (unsigned long)now * 1000; // 64-bit timestamp defined in section 6 of IETF RFC 5905

    uint8_t ts[4];
    for(int i=3;i>=0;i--){
        ts[i] = timestamp % 256;
        timestamp = timestamp / 256;
    }

    indicaHeaderFormat1->colletStartTime.buf = (uint8_t*)calloc(1, 4);
    indicaHeaderFormat1->colletStartTime.size = 4;
    memcpy(indicaHeaderFormat1->colletStartTime.buf,ts, 4);
    
    return 0;

}


uint8_t fillRicIndicationHeader(RICindicationHeader_t *ricIndicationHeader){

    printf("\nINFO   -->  E2 Agent : Fill KPM RIC Indication Header");

    E2SM_KPM_IndicationHeader_t *indicaHeader = (E2SM_KPM_IndicationHeader_t*)calloc(1, sizeof(E2SM_KPM_IndicationHeader_t));
    E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1 = (E2SM_KPM_IndicationHeader_Format1_t*)calloc(1, sizeof(E2SM_KPM_IndicationHeader_Format1_t));
    fillIndicationHeaderFormat1(indicaHeaderFormat1);

    indicaHeader->indicationHeader_formats.present = E2SM_KPM_IndicationHeader__indicationHeader_formats_PR_indicationHeader_Format1;
    indicaHeader->indicationHeader_formats.choice.indicationHeader_Format1 = indicaHeaderFormat1;

    //xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationHeader, indicaHeader);


    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod;
    
    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
          ATS_ALIGNED_BASIC_PER,
          &asn_DEF_E2SM_KPM_IndicationHeader,
          indicaHeader, e2smbuffer, e2smbuffer_size);
    
    ricIndicationHeader->buf = (uint8_t*)calloc(1,er.encoded);
    ricIndicationHeader->size = er.encoded;
    memcpy(ricIndicationHeader->buf,e2smbuffer,er.encoded);

    return 0;


}

uint8_t fillMeasDataItem(MeasurementDataItem_t *measDataItem){

    //printf("Function \"%s\" is start\n", __func__);
    srand(time(NULL));

    MeasurementRecordItem_t *measRecordItem = (MeasurementRecordItem_t*)calloc(1, sizeof(MeasurementRecordItem_t));
    measRecordItem->present = MeasurementRecordItem_PR_integer;
    //measRecordItem->choice.integer = rand() % (11); // Dummy Data
    measRecordItem->choice.integer = thpDl; // Measurement to RLC
    printf("\nINFO   -->  E2 Agent : Downlink Throughput = %ld<<<<\n", measRecordItem->choice.integer);
    ASN_SEQUENCE_ADD(&measDataItem->measRecord.list, measRecordItem);

    return 0;

}

uint8_t fillIndicationMessageFormat1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1){
    //printf("\nFunction \"%s\" is start\n", __func__);

    MeasurementDataItem_t *measDataItem = (MeasurementDataItem_t*)calloc(1, sizeof(MeasurementDataItem_t));
    MeasurementInfoList_t *measInfoList = (MeasurementInfoList_t*)calloc(1, sizeof(MeasurementInfoList_t));
    MeasurementInfoItem_t *measInfoItem = (MeasurementInfoItem_t*)calloc(1, sizeof(MeasurementInfoItem_t));
    indicaMessageFormat1->measInfoList = measInfoList;

    fillMeasDataItem(measDataItem);
    fillMeasInfoItem(measInfoItem);

    ASN_SEQUENCE_ADD(&indicaMessageFormat1->measData.list, measDataItem);
    ASN_SEQUENCE_ADD(&indicaMessageFormat1->measInfoList->list, measInfoItem);
    return 0; 

}


uint8_t fillMeasCondItem(MeasurementCondUEidItem_t *measCondItem, char measureName[], char *sst, char sd[]){
    printf("\nFunction \"%s\" is start\n", __func__);

    MatchingCondItem_t *matchCondItem = (MatchingCondItem_t*)calloc(1, sizeof(MatchingCondItem_t));

    measCondItem->measType.present = MeasurementType_PR_measName;
    measCondItem->measType.choice.measName.size = strlen(measureName);
    measCondItem->measType.choice.measName.buf = (uint8_t*)calloc(strlen(measureName), sizeof(uint8_t));
    memcpy(measCondItem->measType.choice.measName.buf, measureName, measCondItem->measType.choice.measName.size);

    matchCondItem->matchingCondChoice.present = MatchingCondItem_Choice_PR_measLabel;
    matchCondItem->matchingCondChoice.choice.measLabel = (MeasurementLabel_t*)calloc(1, sizeof(MeasurementLabel_t));
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID = (S_NSSAI_t*)calloc(1, sizeof(S_NSSAI_t));
    
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD = (SD_t*)calloc(1, sizeof(SD_t));
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.size = 1;
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf = (uint8_t*)calloc(1, sizeof(uint8_t));
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf, sst, 1);
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->size = 3;
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf = (uint8_t*)calloc(3, sizeof(uint8_t));
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf, sd, 3);

    ASN_SEQUENCE_ADD(&measCondItem->matchingCond.list, matchCondItem);

}

uint8_t fillIndicationMessageFormat2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2){
    printf("\nFunction \"%s\" is start\n", __func__);

    MeasurementDataItem_t *measDataItem = (MeasurementDataItem_t*)calloc(1, sizeof(MeasurementDataItem_t));
    MeasurementCondUEidItem_t *measCondItem = (MeasurementCondUEidItem_t*)calloc(1, sizeof(MeasurementCondUEidItem_t));

    fillMeasDataItem(measDataItem);
    fillMeasCondItem(measCondItem, measurementStyle2[0], sst, sd);
    ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem);
    ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem);

    return 0; 
}

uint8_t fillRicindicationMessage(RICindicationMessage_t *ricIndicationMessage){

    printf("\nFunction \"%s\" is start", __func__);

    E2SM_KPM_IndicationMessage_t *indicaMessage = (E2SM_KPM_IndicationMessage_t*)calloc(1, sizeof(E2SM_KPM_IndicationMessage_t));

    // E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1 =  (E2SM_KPM_IndicationMessage_Format1_t*)calloc(1, sizeof(E2SM_KPM_IndicationMessage_Format1_t));
    // fillIndicationMessageFormat1(indicaMessageFormat1);  
    // ricIndicationMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1;
    // ricIndicationMessage->indicationMessage_formats.choice.indicationMessage_Format1 = indicaMessageFormat1;
    
   
    E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2 = (E2SM_KPM_IndicationMessage_Format2_t*)calloc(1, sizeof(E2SM_KPM_IndicationMessage_Format2_t));
    fillIndicationMessageFormat2(indicaMessageFormat2);  
    indicaMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2;
    indicaMessage->indicationMessage_formats.choice.indicationMessage_Format2 = indicaMessageFormat2;

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_IndicationMessage,
         indicaMessage, e2smbuffer, e2smbuffer_size);

    ricIndicationMessage->buf = (uint8_t*)calloc(er.encoded,sizeof(uint8_t));
    ricIndicationMessage->size = er.encoded;
    memcpy(ricIndicationMessage->buf,e2smbuffer,er.encoded);

    return 0; 
}


void kpmSendSliceMetric(SlicePmList* sliceMetricList){
    
    printf("\nINFO   -->  E2 Agent : Get slice number %d<<<<\n", sliceMetricList->numSlice);
    if(sliceMetricList->numSlice>1){
        printf("\nINFO   -->  E2 Agent : Support sending 1 slice to xApp");
        thpDl = sliceMetricList->sliceRecord[0].ThpDl;
        BuildAndSendRicIndication();
    }
    else{
        printf("\nINFO   -->  E2 Agent : Do nothing");
    }

}