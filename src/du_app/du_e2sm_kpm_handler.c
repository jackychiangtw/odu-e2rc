#include "du_e2sm_kpm_handler.h"
#include "S-NSSAI.h"
#include "SD.h"

char measInfoStyle1[][25] = {"DRB.UEThpDl", "RRU.PrbUsedDl", "RRU.PrbAvailDl", "RRU.PrbTotDl"}; // UE throughput, Avaliable PRB, Total PRB Usage
char measInfoStyle2[][25] = {"DRB.UEThpDl.SNSSAI", "RRU.PrbUsedDl.SNSSAI"}; // UE throughput, Used PRB, Total PRB

uint8_t kpmInit(){
        
    kpmSlicePmDb.numOfSlice = MAX_SIZE_OF_SLICE;
    kpmSlicePmDb.numOfMacPm = 0;
    kpmSlicePmDb.numOfRlcPm = 0;

    kpmCellPmDb.numOfMacPm = 0;
    kpmCellPmDb.numOfRlcPm = 0;

    kpmCellIndicationEnable = false;
    kpmSliceIndicationEnable = false;

    reportingPeriodFmt1 = 0;
    reportingPeriodFmt3 = 0;
    indicationCountFmt1 = 0;
    indicationCountFmt3 = 0;
    reportingPeriod = 0;
<<<<<<< Updated upstream
=======
    kpmIndicationV3Enable = 0;
>>>>>>> Stashed changes
    return 0;
}

uint8_t kpmEnableIndication(bool *flag){
    *flag = true;
    return 0;
}

uint8_t fillRanFunctionName(RANfunction_Name_t *ranfunc_name, uint8_t kpmVersion){
    uint8_t ranfunc_defin[] = "ORAN-E2SM-KPM"; // RAN Function Definition,
    uint8_t ranfunc_descr[] = "KPM monitor"; // RAN function description
    uint8_t ranfunc_oidv2[] = "1.3.6.1.4.1.53148.1.2.2.2"; // RAN function service model OID
    uint8_t ranfunc_oidv3[] = "1.3.6.1.4.1.53148.1.3.2.2"; 

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
    ranfunc_name->ranFunction_ShortName.size = strlen((const char*)ranfunc_defin);
    // allocate memory for ranfunc_name->ranFunction_ShortName.buf by DU_ALLOC
    DU_ALLOC(ranfunc_name->ranFunction_ShortName.buf, ranfunc_name->ranFunction_ShortName.size);
    if(ranfunc_name->ranFunction_ShortName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_name->ranFunction_ShortName.buf");
        return RFAILED;
    }    
    memcpy(ranfunc_name->ranFunction_ShortName.buf, ranfunc_defin, ranfunc_name->ranFunction_ShortName.size);

    ranfunc_name->ranFunction_Description.size = strlen((const char*)ranfunc_descr);
    // allocation memory for ranfunc_name->ranFunction_Description.buf by DU_ALLOC
    DU_ALLOC(ranfunc_name->ranFunction_Description.buf, ranfunc_name->ranFunction_Description.size);
    if(ranfunc_name->ranFunction_Description.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_name->ranFunction_Description.buf");
        return RFAILED;
    }
    memcpy(ranfunc_name->ranFunction_Description.buf, ranfunc_descr, ranfunc_name->ranFunction_Description.size);

    // allocation memory for ranFunction_Instance by DU_ALLOC
    DU_ALLOC(ranfunc_name->ranFunction_Instance, sizeof(long));
    if(ranfunc_name->ranFunction_Instance == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_name->ranFunction_Instance");
        return RFAILED;
    }
    *ranfunc_name->ranFunction_Instance = 1;

<<<<<<< Updated upstream
    ranfunc_name->ranFunction_E2SM_OID.size = strlen((const char*)ranfunc_oid);
=======
    ranfunc_name->ranFunction_E2SM_OID.size = strlen((const char*)ranfunc_oidv2);
>>>>>>> Stashed changes
    // allocate memory for ranfunc_name->ranFunction_E2SM_OID.buf by DU_ALLOC
    DU_ALLOC(ranfunc_name->ranFunction_E2SM_OID.buf, ranfunc_name->ranFunction_E2SM_OID.size);
    if(ranfunc_name->ranFunction_E2SM_OID.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_name->ranFunction_E2SM_OID.buf");
        return RFAILED;
<<<<<<< Updated upstream
        }
    memcpy(ranfunc_name->ranFunction_E2SM_OID.buf, ranfunc_oid, ranfunc_name->ranFunction_E2SM_OID.size);

=======
    }
    if(kpmVersion == 2)
        memcpy(ranfunc_name->ranFunction_E2SM_OID.buf, ranfunc_oidv2, ranfunc_name->ranFunction_E2SM_OID.size);
    else if(kpmVersion == 3)
        memcpy(ranfunc_name->ranFunction_E2SM_OID.buf, ranfunc_oidv3, ranfunc_name->ranFunction_E2SM_OID.size);
    else{
        printf("\nERROR   -->  E2SM-KPM : Invalid KPM versionf");
    }


>>>>>>> Stashed changes
    return 0;
}

uint8_t fillTriggerStyleItem(RIC_EventTriggerStyle_Item_t *trigger_style){
    printf("\nINFO   -->  E2SM-KPM : Function \"%s\" is start", __func__);

    trigger_style->ric_EventTriggerStyle_Type = 1; // KPM only supports type 1

    uint8_t trig_name[] = "Periodic report";
    trigger_style->ric_EventTriggerStyle_Name.size = strlen((const char*)trig_name);
    // allocate memory for trigger_style->ric_EventTriggerStyle_Name.buf by DU_ALLOC
    DU_ALLOC(trigger_style->ric_EventTriggerStyle_Name.buf, trigger_style->ric_EventTriggerStyle_Name.size);
    if(trigger_style->ric_EventTriggerStyle_Name.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for trigger_style->ric_EventTriggerStyle_Name.buf");
        return RFAILED;
    }
    memcpy(trigger_style->ric_EventTriggerStyle_Name.buf, trig_name, trigger_style->ric_EventTriggerStyle_Name.size);
    trigger_style->ric_EventTriggerFormat_Type = 1;
    return 0;
}

uint8_t fillTriggerStyleList(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *triggerStyleList){
    printf("\nINFO   -->  E2SM-KPM : Function \"%s\" is start", __func__);

    RIC_EventTriggerStyle_Item_t *trigger_style;
    // allocation memory for trigger_style by DU_ALLOC
    DU_ALLOC(trigger_style, sizeof(RIC_EventTriggerStyle_Item_t));
    if(trigger_style == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for trigger_style");
        return RFAILED;
    }
    fillTriggerStyleItem(trigger_style); // fill one trigger style
    ASN_SEQUENCE_ADD(&triggerStyleList->list, trigger_style);
    
    return 0;
}

uint8_t fillTriggerStyleListV3(struct E2SM_KPM_RANfunction_Description_v300__ric_EventTriggerStyle_List *triggerStyleList){
    printf("\nINFO   -->  E2SM-KPM : Function \"%s\" is start", __func__);

    RIC_EventTriggerStyle_Item_t *trigger_style;
    // allocation memory for trigger_style by DU_ALLOC
    DU_ALLOC(trigger_style, sizeof(RIC_EventTriggerStyle_Item_t));
    if(trigger_style == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for trigger_style");
        return RFAILED;
    }
    fillTriggerStyleItem(trigger_style); // fill one trigger style
    ASN_SEQUENCE_ADD(&triggerStyleList->list, trigger_style);
    
    return 0;
}

uint8_t fillReportStyleItemStyle1(RIC_ReportStyle_Item_t *report_style){
    int measurementSize = sizeof(measInfoStyle1) / sizeof(*measInfoStyle1);

    report_style->ric_ReportStyle_Type = 1; // For Report
    uint8_t report_name[] = "O-DU Cell Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = strlen((const char*)report_name);
    // allocate memory for report_style->ric_ReportStyle_Name.buf by DU_ALLOC
    DU_ALLOC(report_style->ric_ReportStyle_Name.buf, report_style->ric_ReportStyle_Name.size);
    if(report_style->ric_ReportStyle_Name.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style->ric_ReportStyle_Name.buf");
        return RFAILED;
    }
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 1;
    report_style->ric_ActionFormat_Type = 1; // new in KPM 2.0

    MeasurementInfo_Action_Item_t *measure_item;
    // allocate memory for measure_item by DU_ALLOC
    DU_ALLOC(measure_item, measurementSize * sizeof(MeasurementInfo_Action_Item_t));
    if(measure_item == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item");
        return RFAILED;
    }

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen((const char*)measInfoStyle1[i]);
        // allocate memory for measure_item[i].measName.buf by DU_ALLOC
        DU_ALLOC(measure_item[i].measName.buf, measure_item[i].measName.size);
        if(measure_item[i].measName.buf == NULL){
            printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item[i].measName.buf");
            return RFAILED;
        }
        memcpy(measure_item[i].measName.buf, measInfoStyle1[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }

    return 0;
}

uint8_t fillReportStyleItemStyle1V3(RIC_ReportStyle_Item_v300_t *report_style){
    int measurementSize = sizeof(measInfoStyle1) / sizeof(*measInfoStyle1);

    report_style->ric_ReportStyle_Type = 1; // For Report
    uint8_t report_name[] = "O-DU Cell Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = strlen((const char*)report_name);
    // allocate memory for report_style->ric_ReportStyle_Name.buf by DU_ALLOC
    DU_ALLOC(report_style->ric_ReportStyle_Name.buf, report_style->ric_ReportStyle_Name.size);
    if(report_style->ric_ReportStyle_Name.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style->ric_ReportStyle_Name.buf");
        return RFAILED;
    }
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 1;
    report_style->ric_ActionFormat_Type = 1; // new in KPM 2.0

    MeasurementInfo_Action_Item_v300_t *measure_item;
    // allocate memory for measure_item by DU_ALLOC
    DU_ALLOC(measure_item, measurementSize * sizeof(MeasurementInfo_Action_Item_v300_t));
    if(measure_item == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item");
        return RFAILED;
    }

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen((const char*)measInfoStyle1[i]);
        // allocate memory for measure_item[i].measName.buf by DU_ALLOC
        DU_ALLOC(measure_item[i].measName.buf, measure_item[i].measName.size);
        if(measure_item[i].measName.buf == NULL){
            printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item[i].measName.buf");
            return RFAILED;
        }
        memcpy(measure_item[i].measName.buf, measInfoStyle1[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }

    return 0;
}

uint8_t fillReportStyleItemStyle2(RIC_ReportStyle_Item_t *report_style){
    int measurementSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);

    report_style->ric_ReportStyle_Type = 3; // For reporting slice measurement
    uint8_t report_name[] = "O-DU Slice Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = strlen((const char*)report_name);
    // allocate memory for report_style->ric_ReportStyle_Name.buf by DU_ALLOC
    DU_ALLOC(report_style->ric_ReportStyle_Name.buf, report_style->ric_ReportStyle_Name.size);
    if(report_style->ric_ReportStyle_Name.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style->ric_ReportStyle_Name.buf");
        return RFAILED;
    }
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 2; // For conditional reporting
    report_style->ric_ActionFormat_Type = 3; // new in KPM 2.0

    MeasurementInfo_Action_Item_t *measure_item;
    // allocate memory for measure_item by DU_ALLOC
    DU_ALLOC(measure_item, measurementSize * sizeof(MeasurementInfo_Action_Item_t));
    if(measure_item == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item");
        return RFAILED;
    }

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen((const char*)measInfoStyle2[i]);
        // allocate memory for measure_item[i].measName.buf by DU_ALLOC
        DU_ALLOC(measure_item[i].measName.buf, measure_item[i].measName.size);
        if(measure_item[i].measName.buf == NULL){
            printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item[i].measName.buf");
            return RFAILED;
        }
        memcpy(measure_item[i].measName.buf, measInfoStyle2[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }

    return 0;
}

uint8_t fillReportStyleItemStyle2V3(RIC_ReportStyle_Item_v300_t *report_style){
    int measurementSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);

    report_style->ric_ReportStyle_Type = 3; // For reporting slice measurement
    uint8_t report_name[] = "O-DU Slice Metrics for SLA Functionality";
    report_style->ric_ReportStyle_Name.size = strlen((const char*)report_name);
    // allocate memory for report_style->ric_ReportStyle_Name.buf by DU_ALLOC
    DU_ALLOC(report_style->ric_ReportStyle_Name.buf, report_style->ric_ReportStyle_Name.size);
    if(report_style->ric_ReportStyle_Name.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style->ric_ReportStyle_Name.buf");
        return RFAILED;
    }
    memcpy(report_style->ric_ReportStyle_Name.buf, report_name, report_style->ric_ReportStyle_Name.size);

    report_style->ric_IndicationHeaderFormat_Type = 1; // only 1 supported in KPM 2.03
    report_style->ric_IndicationMessageFormat_Type = 2; // For conditional reporting
    report_style->ric_ActionFormat_Type = 3; // new in KPM 2.0

    MeasurementInfo_Action_Item_v300_t *measure_item;
    // allocate memory for measure_item by DU_ALLOC
    DU_ALLOC(measure_item, measurementSize * sizeof(MeasurementInfo_Action_Item_v300_t));
    if(measure_item == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item");
        return RFAILED;
    }

    for(int i=0;i<measurementSize;i++){
        measure_item[i].measName.size = strlen((const char*)measInfoStyle2[i]);
        // allocate memory for measure_item[i].measName.buf by DU_ALLOC
        DU_ALLOC(measure_item[i].measName.buf, measure_item[i].measName.size);
        if(measure_item[i].measName.buf == NULL){
            printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measure_item[i].measName.buf");
            return RFAILED;
        }
        memcpy(measure_item[i].measName.buf, measInfoStyle2[i], measure_item[i].measName.size);
        ASN_SEQUENCE_ADD(&report_style->measInfo_Action_List.list, measure_item + i);
    }

    return 0;
}

uint8_t fillReportStyleList(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *reportStyleList){
    RIC_ReportStyle_Item_t *report_style;
    // allocation memory for report_style by DU_ALLOC
    DU_ALLOC(report_style, sizeof(RIC_ReportStyle_Item_t) * 2);
    if(report_style == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style");
        return RFAILED;
    }
    fillReportStyleItemStyle1(report_style);
    fillReportStyleItemStyle2(report_style+1);
    ASN_SEQUENCE_ADD(&reportStyleList->list, report_style);
    ASN_SEQUENCE_ADD(&reportStyleList->list, report_style+1);

    return 0;
}

uint8_t fillReportStyleListV3(struct E2SM_KPM_RANfunction_Description_v300__ric_ReportStyle_List *reportStyleList){
    RIC_ReportStyle_Item_v300_t *report_style;
    // allocation memory for report_style by DU_ALLOC
    DU_ALLOC(report_style, sizeof(RIC_ReportStyle_Item_v300_t) * 2);
    if(report_style == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for report_style");
        return RFAILED;
    }
    fillReportStyleItemStyle1V3(report_style);
    fillReportStyleItemStyle2V3(report_style+1);
    ASN_SEQUENCE_ADD(&reportStyleList->list, report_style);
    ASN_SEQUENCE_ADD(&reportStyleList->list, report_style+1);

    return 0;
}

uint8_t kpmFreeRanFuncName(RANfunction_Name_t *ranfunc_name){
    if(ranfunc_name->ranFunction_Description.size>0){
        DU_FREE(ranfunc_name->ranFunction_Description.buf, ranfunc_name->ranFunction_Description.size);
    }
    if(ranfunc_name->ranFunction_ShortName.size>0){
        DU_FREE(ranfunc_name->ranFunction_ShortName.buf, ranfunc_name->ranFunction_ShortName.size);
    }
    if(ranfunc_name->ranFunction_Description.size){
        DU_FREE(ranfunc_name->ranFunction_Description.buf, ranfunc_name->ranFunction_Description.size);
    }
    if(ranfunc_name->ranFunction_Instance){
        DU_FREE(ranfunc_name->ranFunction_Instance, sizeof(long));
    }

    return 0;
}

uint8_t kpmFreeEventTrigStyleList(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *eventTrigStyleList){
    for(int i=0;i<eventTrigStyleList->list.count;i++){
        if(eventTrigStyleList->list.array[i]){
            if(eventTrigStyleList->list.array[i]->ric_EventTriggerStyle_Name.size>0){
                if(eventTrigStyleList->list.array[i]->ric_EventTriggerStyle_Name.buf){
                    DU_FREE(eventTrigStyleList->list.array[i]->ric_EventTriggerStyle_Name.buf, eventTrigStyleList->list.array[i]->ric_EventTriggerStyle_Name.size);
                }
            }
        }  
    }
    return 0;
}

uint8_t kpmFreeReportStyleList(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *reportStyleList){
    for(int i=0;i<reportStyleList->list.count;i++){
        if(reportStyleList->list.array[i]){
            if(reportStyleList->list.array[i]->ric_ReportStyle_Name.size>0){
                if(reportStyleList->list.array[i]->ric_ReportStyle_Name.buf){
                    DU_FREE(reportStyleList->list.array[i]->ric_ReportStyle_Name.buf, reportStyleList->list.array[i]->ric_ReportStyle_Name.size);
                }
            }
            for(int j=0;j<reportStyleList->list.array[i]->measInfo_Action_List.list.count;j++){
                if(reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measName.size>0){
                    if(reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measName.buf){
                        DU_FREE(reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measName.buf, reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measName.size);
                    }
                    if(reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measID){
                        DU_FREE(reportStyleList->list.array[i]->measInfo_Action_List.list.array[j]->measID, sizeof(long));
                    }
                }
            }
        }
    }
    return 0;

}

uint8_t kpmFreeRanFuncDesc(E2SM_KPM_RANfunction_Description_t *ranfunc_desc){
    kpmFreeRanFuncName(&ranfunc_desc->ranFunction_Name);
    if(ranfunc_desc->ric_EventTriggerStyle_List){
        kpmFreeEventTrigStyleList(ranfunc_desc->ric_EventTriggerStyle_List);
    }
    return 0;

}

uint8_t kpmRanFuncDescriptionV3(RANfunctionDefinition_t  *ranFunDefinition){
    asn_codec_ctx_t *opt_cod = 0;
    E2SM_KPM_RANfunction_Description_v300_t *ranfunc_desc;
    // allocate memory for ranfunc_desc by DU_ALLOC
    DU_ALLOC(ranfunc_desc, sizeof(E2SM_KPM_RANfunction_Description_v300_t));
    if(ranfunc_desc == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc");
        return RFAILED;
    }

    ASN_STRUCT_RESET(asn_DEF_E2SM_KPM_RANfunction_Description_v300, ranfunc_desc);
    
<<<<<<< Updated upstream
    if(fillRanFunctionName(&ranfunc_desc->ranFunction_Name) != 0){
=======
    if(fillRanFunctionName(&ranfunc_desc->ranFunction_Name, 3) != 0){
>>>>>>> Stashed changes
        return RFAILED;
    }

    // allocate memory for ranfunc_desc->ric_EventTriggerStyle_List by DU_ALLOC
    DU_ALLOC(ranfunc_desc->ric_EventTriggerStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description_v300__ric_EventTriggerStyle_List));
    if(ranfunc_desc->ric_EventTriggerStyle_List == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc->ric_EventTriggerStyle_List");
        return RFAILED;
    }
    // allocate memory for ranfunc_desc->ric_ReportStyle_List by DU_ALLOC
    DU_ALLOC(ranfunc_desc->ric_ReportStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description_v300__ric_ReportStyle_List));
    if(ranfunc_desc->ric_ReportStyle_List == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc->ric_ReportStyle_List");
        return RFAILED;
    }
    if(fillTriggerStyleListV3(ranfunc_desc->ric_EventTriggerStyle_List) != 0){
        return RFAILED;
    }
    if(fillReportStyleListV3(ranfunc_desc->ric_ReportStyle_List) != 0){
        return RFAILED;
    }

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_RANfunction_Description_v300, ranfunc_desc);

    uint8_t e2smbuffer[8192];
    size_t e2smbuffer_size = 8192;
    asn_enc_rval_t     encRetVal;

    encRetVal = asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_RANfunction_Description,
         ranfunc_desc, e2smbuffer, e2smbuffer_size);
    
    if(encRetVal.encoded == -1)
        return RFAILED;

    // allocation memory for ranFunDefinition->buf by DU_ALLOC
    DU_ALLOC(ranFunDefinition->buf, encRetVal.encoded *  sizeof(uint8_t));
    if(ranFunDefinition->buf == NULL){
        DU_LOG("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranFunDefinition->buf");
        return RFAILED;
    }
    ranFunDefinition->size = encRetVal.encoded;
    memcpy(ranFunDefinition->buf, e2smbuffer, encRetVal.encoded);

    return 0;
}


uint8_t kpmRanFuncDescription(RANfunctionDefinition_t  *ranFunDefinition)
{
    asn_codec_ctx_t *opt_cod = 0;

    kpmInit();
    E2SM_KPM_RANfunction_Description_t *ranfunc_desc;
    // allocate memory for ranfunc_desc by DU_ALLOC
    DU_ALLOC(ranfunc_desc, sizeof(E2SM_KPM_RANfunction_Description_t));
    if(ranfunc_desc == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc");
        return RFAILED;
    }

    ASN_STRUCT_RESET(asn_DEF_E2SM_KPM_RANfunction_Description, ranfunc_desc);

<<<<<<< Updated upstream
    if(fillRanFunctionName(&ranfunc_desc->ranFunction_Name) != 0){
=======
    if(fillRanFunctionName(&ranfunc_desc->ranFunction_Name, 2) != 0){
>>>>>>> Stashed changes
        return RFAILED;
    }
    // allocation memory for ranfunc_desc->ric_EventTriggerStyle_List by DU_ALLOC
    DU_ALLOC(ranfunc_desc->ric_EventTriggerStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List));
    if(ranfunc_desc->ric_EventTriggerStyle_List == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc->ric_EventTriggerStyle_List");
        return RFAILED;
    }
    // allocation memory for ranfunc_desc->ric_ReportStyle_List by DU_ALLOC
    DU_ALLOC(ranfunc_desc->ric_ReportStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List));
    if(ranfunc_desc->ric_ReportStyle_List == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranfunc_desc->ric_ReportStyle_List");
        return RFAILED;
    }
    if(fillTriggerStyleList(ranfunc_desc->ric_EventTriggerStyle_List) != 0){
        return RFAILED;
    }
    if(fillReportStyleList(ranfunc_desc->ric_ReportStyle_List) != 0){
        return RFAILED;
    }

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_RANfunction_Description, ranfunc_desc);

    uint8_t e2smbuffer[8192];
    size_t e2smbuffer_size = 8192;
    asn_enc_rval_t     encRetVal;

    encRetVal = asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_RANfunction_Description,
         ranfunc_desc, e2smbuffer, e2smbuffer_size);
    
    if(encRetVal.encoded == -1)
        return RFAILED;

    // allocation memory for ranFunDefinition->buf by DU_ALLOC
    DU_ALLOC(ranFunDefinition->buf, encRetVal.encoded *  sizeof(uint8_t));
    if(ranFunDefinition->buf == NULL){
        DU_LOG("\nERROR   -->  E2SM-KPM : Memory allocation failed for ranFunDefinition->buf");
        return RFAILED;
    }
    ranFunDefinition->size = encRetVal.encoded;
    memcpy(ranFunDefinition->buf, e2smbuffer, encRetVal.encoded);

    return 0;
}

uint8_t fillMeasInfoItem(MeasurementInfoItem_t *measInfoItem, uint8_t *measName, int size){
    LabelInfoItem_t *measLabelInfo;
    // allocate memory for measLabelInfo by DU_ALLOC
    DU_ALLOC(measLabelInfo, sizeof(LabelInfoItem_t));
    if(measLabelInfo == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measLabelInfo");
        return RFAILED;
    }

    long *measLabelInfo_noLabel;
    // allocate memory for measLabelInfo_noLabel by DU_ALLOC
    DU_ALLOC(measLabelInfo_noLabel, sizeof(long));
    if(measLabelInfo_noLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measLabelInfo_noLabel");
        return RFAILED;
    }
    measInfoItem->measType.present = MeasurementType_PR_measName; // Choose name or ID
    measInfoItem->measType.choice.measName.size = size;
    // allocate memory for measInfoItem->measType.choice.measName.buf by DU_ALLOC
    DU_ALLOC(measInfoItem->measType.choice.measName.buf, size);
    if(measInfoItem->measType.choice.measName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoItem->measType.choice.measName.buf");
        return RFAILED;
    }
    memcpy(measInfoItem->measType.choice.measName.buf, measName, measInfoItem->measType.choice.measName.size);

    *measLabelInfo_noLabel = MeasurementLabel__noLabel_true;
    measLabelInfo->measLabel.noLabel = measLabelInfo_noLabel;

    ASN_SEQUENCE_ADD(&measInfoItem->labelInfoList.list, measLabelInfo);
    return 0;
}

uint8_t fillMeasInfoItemV3(MeasurementInfoItem_v300_t *measInfoItem, uint8_t *measName, int size){
    LabelInfoItem_v300_t *measLabelInfo;
    // allocate memory for measLabelInfo by DU_ALLOC
    DU_ALLOC(measLabelInfo, sizeof(LabelInfoItem_v300_t));
    if(measLabelInfo == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measLabelInfo");
        return RFAILED;
    }

    long *measLabelInfo_noLabel;
    // allocate memory for measLabelInfo_noLabel by DU_ALLOC
    DU_ALLOC(measLabelInfo_noLabel, sizeof(long));
    if(measLabelInfo_noLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measLabelInfo_noLabel");
        return RFAILED;
    }
    measInfoItem->measType.present = MeasurementType_PR_measName; // Choose name or ID
    measInfoItem->measType.choice.measName.size = size;
    // allocate memory for measInfoItem->measType.choice.measName.buf by DU_ALLOC
    DU_ALLOC(measInfoItem->measType.choice.measName.buf, size);
    if(measInfoItem->measType.choice.measName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoItem->measType.choice.measName.buf");
        return RFAILED;
    }
    memcpy(measInfoItem->measType.choice.measName.buf, measName, measInfoItem->measType.choice.measName.size);

    *measLabelInfo_noLabel = MeasurementLabel__noLabel_true;
    measLabelInfo->measLabel.noLabel = measLabelInfo_noLabel;

    ASN_SEQUENCE_ADD(&measInfoItem->labelInfoList.list, measLabelInfo);
    return 0;
}

uint8_t decapEventTrigDefinitionFormat1(RICeventTriggerDefinition_t *defini){
    asn_dec_rval_t  rval;
    E2SM_KPM_EventTriggerDefinition_t *kpmEventTrig;
    // allocate memory for kpmEventTrig by DU_ALLOC
    DU_ALLOC(kpmEventTrig, sizeof(E2SM_KPM_EventTriggerDefinition_t));
    if(kpmEventTrig == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for kpmEventTrig");
        return RFAILED;
    }
    printf("\nINFO   -->  E2SM-KPM : Decap Event Trigger Definition<<<<\n");

    rval = aper_decode(0, &asn_DEF_E2SM_KPM_EventTriggerDefinition, (void **)&kpmEventTrig, defini->buf, defini->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
   {
      printf("\nERROR  -->  E2SM-KPM : ASN decode failed");
   }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_EventTriggerDefinition, kpmEventTrig);
    printf("\nINFO  -->  E2SM-KPM : Report Period is %ld\n", kpmEventTrig->eventDefinition_formats.choice.eventDefinition_Format1->reportingPeriod);
    reportingPeriod = kpmEventTrig->eventDefinition_formats.choice.eventDefinition_Format1->reportingPeriod;
    return 0;
}

int actionFmt1measNameIsSupport(uint8_t *measNameBuf){
    int measSize = sizeof(measInfoStyle1) / sizeof(*measInfoStyle1);

    for(int i=0;i<measSize;i++){
        if(strcmp((const char*)measNameBuf, measInfoStyle1[i]) == 0)
            return i;
    }
    return -1; 
}

int actionFmt3measNameIsSupport(uint8_t *measNameBuf){
    int measSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);

    for(int i=0;i<measSize;i++){
        if(strcmp((const char*)measNameBuf, measInfoStyle2[i]) == 0)
            return i;
    }
    return -1; 
}

uint8_t decapActionDefinitionFmt1(E2SM_KPM_ActionDefinition_Format1_t *actionDefinFormat1){
    int index;
    printf("\nINFO  -->  E2SM-KPM : Granularity Period is %ld\n", actionDefinFormat1->granulPeriod);
    sizeOfMeasNameFmt1 = 0;

    for(int i=0;i<actionDefinFormat1->measInfoList.list.count;i++){
        if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measID)
            printf("\nINFO  -->  E2SM-KPM : Measurement ID is %ld", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPM : Measurement Name is %s", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt1measNameIsSupport(actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPM : Measurement name in Fmt 1 is vaild \n");
<<<<<<< Updated upstream
                memcpy(indicationMeasNameFmt1[index], measInfoStyle1[index], strlen((const char*)measInfoStyle1[index])+1);
=======
                memcpy(indicationMeasNameFmt1[sizeOfMeasNameFmt1], measInfoStyle1[index], strlen((const char*)measInfoStyle1[index])+1);
>>>>>>> Stashed changes
                sizeOfMeasNameFmt1++;
            }
            else{
                printf("\nINFO  -->  E2SM-KPM : Measurement name is invaild \n");
                return RFAILED;
            }
        }
        else{
            printf("\nINFO  -->  E2SM-KPM : Measurement type is invaild \n");
        }
    }

    for(int i=0;i<sizeOfMeasNameFmt1;i++){
<<<<<<< Updated upstream
        printf("\nINFO  -->  E2SM-KPM : # %d Measurement name is %s", i, indicationMeasNameFmt1[index]);
=======
        printf("\nINFO  -->  E2SM-KPM : # %d Measurement name is %s", i, indicationMeasNameFmt1[i]);
>>>>>>> Stashed changes
    }
    if(sizeOfMeasNameFmt1>0)
        return ROK;
    else
        return RFAILED;

}

uint8_t decapActionDefinitionFmt1V3(E2SM_KPM_ActionDefinition_Format1_v300_t *actionDefinFormat1){
    int index;
<<<<<<< Updated upstream
    printf("\nINFO  -->  E2SM-KPM : Granularity Period is %ld\n", actionDefinFormat1->granulPeriod);
=======
    printf("\nINFO  -->  E2SM-KPMv3 : Granularity Period is %ld\n", actionDefinFormat1->granulPeriod);
>>>>>>> Stashed changes
    sizeOfMeasNameFmt1 = 0;

    for(int i=0;i<actionDefinFormat1->measInfoList.list.count;i++){
        if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measID)
<<<<<<< Updated upstream
            printf("\nINFO  -->  E2SM-KPM : Measurement ID is %ld", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPM : Measurement Name is %s", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt1measNameIsSupport(actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPM : Measurement name in Fmt 1 is vaild \n");
                memcpy(indicationMeasNameFmt1[index], measInfoStyle1[index], strlen((const char*)measInfoStyle1[index])+1);
                sizeOfMeasNameFmt1++;
            }
            else{
                printf("\nINFO  -->  E2SM-KPM : Measurement name is invaild \n");
=======
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement ID is %ld", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat1->measInfoList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement Name is %s", actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt1measNameIsSupport(actionDefinFormat1->measInfoList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPMv3 : Measurement name in Fmt 1 is vaild, %d\n", index);
                memcpy(indicationMeasNameFmt1[sizeOfMeasNameFmt1], measInfoStyle1[index], strlen((const char*)measInfoStyle1[index])+1);
                sizeOfMeasNameFmt1++;
            }
            else{
                printf("\nINFO  -->  E2SM-KPMv3 : Measurement name is invaild \n");
>>>>>>> Stashed changes
                return RFAILED;
            }
        }
        else{
<<<<<<< Updated upstream
            printf("\nINFO  -->  E2SM-KPM : Measurement type is invaild \n");
=======
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement type is invaild \n");
>>>>>>> Stashed changes
        }
    }

    for(int i=0;i<sizeOfMeasNameFmt1;i++){
<<<<<<< Updated upstream
        printf("\nINFO  -->  E2SM-KPM : # %d Measurement name is %s", i, indicationMeasNameFmt1[index]);
=======
        printf("\nINFO  -->  E2SM-KPMv3 : # %d Measurement name is %s", i, indicationMeasNameFmt1[i]);
>>>>>>> Stashed changes
    }
    if(sizeOfMeasNameFmt1>0)
        return ROK;
    else
        return RFAILED;

}

uint8_t decapActionDefinitionFmt3(E2SM_KPM_ActionDefinition_Format3_t *actionDefinFormat3){
    int index;
    printf("\nINFO  -->  E2SM-KPM : Granularity Period is %ld\n", actionDefinFormat3->granulPeriod);
    sizeOfMeasNameFmt3 = 0;

    for(int i=0;i<actionDefinFormat3->measCondList.list.count;i++){
        if(actionDefinFormat3->measCondList.list.array[i]->measType.present == MeasurementType_PR_measID)
            printf("\nINFO  -->  E2SM-KPM : Measurement ID is %ld", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat3->measCondList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPM : Measurement Name is %s", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt3measNameIsSupport(actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPM : Measurement name in Fmt 3 is vaild \n");
<<<<<<< Updated upstream
                memcpy(indicationMeasNameFmt3, measInfoStyle2[index], strlen((const char*)measInfoStyle2[index])+1);
=======
                memcpy(indicationMeasNameFmt3[sizeOfMeasNameFmt3], measInfoStyle2[index], strlen((const char*)measInfoStyle2[index])+1);
>>>>>>> Stashed changes
                sizeOfMeasNameFmt3++;
            }
        }
        else{
            printf("\nINFO  -->  E2SM-KPM : Measurement type is invaild \n");
        }
    }
<<<<<<< Updated upstream
    if(sizeOfMeasNameFmt1>0)
=======
    for(int i=0;i<sizeOfMeasNameFmt3;i++){
        printf("\nINFO  -->  E2SM-KPM : # %d Measurement name is %s", i, indicationMeasNameFmt3[i]);
    }
    if(sizeOfMeasNameFmt3>0)
>>>>>>> Stashed changes
        return ROK;
    else
        return RFAILED;
}

uint8_t decapActionDefinitionFmt3V3(E2SM_KPM_ActionDefinition_Format3_v300_t *actionDefinFormat3){
    int index;
<<<<<<< Updated upstream
    printf("\nINFO  -->  E2SM-KPM : Granularity Period is %ld\n", actionDefinFormat3->granulPeriod);
=======
    printf("\nINFO  -->  E2SM-KPMv3 : Granularity Period is %ld\n", actionDefinFormat3->granulPeriod);
>>>>>>> Stashed changes
    sizeOfMeasNameFmt3 = 0;

    for(int i=0;i<actionDefinFormat3->measCondList.list.count;i++){
        if(actionDefinFormat3->measCondList.list.array[i]->measType.present == MeasurementType_PR_measID)
<<<<<<< Updated upstream
            printf("\nINFO  -->  E2SM-KPM : Measurement ID is %ld", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat3->measCondList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPM : Measurement Name is %s", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt3measNameIsSupport(actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPM : Measurement name in Fmt 3 is vaild \n");
                memcpy(indicationMeasNameFmt3, measInfoStyle2[index], strlen((const char*)measInfoStyle2[index])+1);
=======
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement ID is %ld", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measID);
        else if(actionDefinFormat3->measCondList.list.array[i]->measType.present == MeasurementType_PR_measName){
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement Name is %s", actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            index = actionFmt3measNameIsSupport(actionDefinFormat3->measCondList.list.array[i]->measType.choice.measName.buf);
            if(index != -1){
                printf("\nINFO  -->  E2SM-KPMv3 : Measurement name in Fmt 3 is vaild \n");
                memcpy(indicationMeasNameFmt3[sizeOfMeasNameFmt3], measInfoStyle2[index], strlen((const char*)measInfoStyle2[index])+1);
>>>>>>> Stashed changes
                sizeOfMeasNameFmt3++;
            }
        }
        else{
<<<<<<< Updated upstream
            printf("\nINFO  -->  E2SM-KPM : Measurement type is invaild \n");
        }
    }
    if(sizeOfMeasNameFmt1>0)
=======
            printf("\nINFO  -->  E2SM-KPMv3 : Measurement type is invaild \n");
        }
    }
     for(int i=0;i<sizeOfMeasNameFmt3;i++){
        printf("\nINFO  -->  E2SM-KPM : # %d Measurement name is %s", i, indicationMeasNameFmt3[i]);
    }
    if(sizeOfMeasNameFmt3>0)
>>>>>>> Stashed changes
        return ROK;
    else
        return RFAILED;
}

uint8_t kpmDecapActionDefinition(RICactionDefinition_t *ricdifin){
    printf("\nINFO   -->  E2SM-KPM : Decap Action Definition<<<<\n");

    asn_dec_rval_t  rval;
    E2SM_KPM_ActionDefinition_t *actionDefin;
    // allocate memory for actionDefin by DU_ALLOC
    DU_ALLOC(actionDefin, sizeof(E2SM_KPM_ActionDefinition_t));
    if(actionDefin == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for actionDefin");
        return RFAILED;
    }

    rval = aper_decode(0, &asn_DEF_E2SM_KPM_ActionDefinition, (void **)&actionDefin, ricdifin->buf, ricdifin->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
      printf("\nERROR  -->  E2SM-KPM : Action Definition decode failed %d\n", rval.code);
    }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_ActionDefinition, actionDefin);
    printf("\nINFO   -->  E2SM-KPM: RIC Style Type = %ld", actionDefin->ric_Style_Type);

    switch(actionDefin->actionDefinition_formats.present){
        case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1:
            if(decapActionDefinitionFmt1(actionDefin->actionDefinition_formats.choice.actionDefinition_Format1) == ROK){
                kpmEnableIndication(&kpmCellIndicationEnable);
                reportingPeriodFmt1 = reportingPeriod; 
                printf("\nINFO   -->  E2SM-KPM: Reporting Period format 1 = %d", reportingPeriodFmt1);
            }
            else{
                printf("\nINFO   -->  E2SM-KPM: Subscription Definition isn't supported");
                return RFAILED;
            }
            
        break;
        case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3:
            if(decapActionDefinitionFmt3(actionDefin->actionDefinition_formats.choice.actionDefinition_Format3) == ROK){
                kpmEnableIndication(&kpmSliceIndicationEnable);
                reportingPeriodFmt3 = reportingPeriod; 
                printf("\nINFO   -->  E2SM-KPM: Reporting Period format 3 = %d", reportingPeriodFmt3);
            }
            else{
                printf("\nINFO   -->  E2SM-KPM: Subscription Definition isn't supported");
                return RFAILED;
            }
        break;
        default:
            printf("\nINFO   -->  E2 Agent: Action Definition Format doesn't support");
    }
<<<<<<< Updated upstream
=======

    kpmIndicationV3Enable = 0;
>>>>>>> Stashed changes
    // ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_ActionDefinition, actionDefin);
    return 0;
}

uint8_t kpmDecapActionDefinitionV3(RICactionDefinition_t *ricdifin){
<<<<<<< Updated upstream
    printf("\nINFO   -->  E2SM-KPM : Decap Action Definition v3<<<<\n");
=======
    printf("\nINFO   -->  E2SM-KPMv3 : Decap Action Definition v3<<<<\n");
>>>>>>> Stashed changes

    asn_dec_rval_t  rval;
    E2SM_KPM_ActionDefinition_v300_t *actionDefin;
    // allocate memory for actionDefin by DU_ALLOC
    DU_ALLOC(actionDefin, sizeof(E2SM_KPM_ActionDefinition_v300_t));
    if(actionDefin == NULL){
<<<<<<< Updated upstream
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for actionDefin");
=======
        printf("\nERROR   -->  E2SM-KPMv3 : Memory allocation failed for actionDefin");
>>>>>>> Stashed changes
        return RFAILED;
    }

    rval = aper_decode(0, &asn_DEF_E2SM_KPM_ActionDefinition_v300, (void **)&actionDefin, ricdifin->buf, ricdifin->size, 0, 0);
    if(rval.code == RC_FAIL || rval.code == RC_WMORE)
    {
<<<<<<< Updated upstream
      printf("\nERROR  -->  E2SM-KPM : Action Definition decode failed %d\n", rval.code);
    }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_ActionDefinition_v300, actionDefin);
    printf("\nINFO   -->  E2SM-KPM: RIC Style Type = %ld", actionDefin->ric_Style_Type);
=======
      printf("\nERROR  -->  E2SM-KPMv3 : Action Definition decode failed %d\n", rval.code);
    }
    
    xer_fprint(stdout, &asn_DEF_E2SM_KPM_ActionDefinition_v300, actionDefin);
    printf("\nINFO   -->  E2SM-KPMv3: RIC Style Type = %ld", actionDefin->ric_Style_Type);
>>>>>>> Stashed changes

    switch(actionDefin->actionDefinition_formats.present){
        case E2SM_KPM_ActionDefinition_v300__actionDefinition_formats_PR_actionDefinition_Format1:
            if(decapActionDefinitionFmt1V3(actionDefin->actionDefinition_formats.choice.actionDefinition_Format1) == ROK){
                kpmEnableIndication(&kpmCellIndicationEnable);
                reportingPeriodFmt1 = reportingPeriod; 
<<<<<<< Updated upstream
                printf("\nINFO   -->  E2SM-KPM: Reporting Period format 1 = %d", reportingPeriodFmt1);
            }
            else{
                printf("\nINFO   -->  E2SM-KPM: Subscription Definition isn't supported");
=======
                printf("\nINFO   -->  E2SM-KPMv3: Reporting Period format 1 = %d", reportingPeriodFmt1);
            }
            else{
                printf("\nINFO   -->  E2SM-KPMv3: Subscription Definition isn't supported");
>>>>>>> Stashed changes
            }
            
        break;
        case E2SM_KPM_ActionDefinition_v300__actionDefinition_formats_PR_actionDefinition_Format3:
            if(decapActionDefinitionFmt3V3(actionDefin->actionDefinition_formats.choice.actionDefinition_Format3) == ROK){
                kpmEnableIndication(&kpmSliceIndicationEnable);
                reportingPeriodFmt3 = reportingPeriod; 
<<<<<<< Updated upstream
                printf("\nINFO   -->  E2SM-KPM: Reporting Period format 3 = %d", reportingPeriodFmt3);
            }
            else
                printf("\nINFO   -->  E2SM-KPM: Subscription Definition isn't supported");
            
        break;
        default:
            printf("\nINFO   -->  E2 Agent: Action Definition Format doesn't support");
    }


=======
                printf("\nINFO   -->  E2SM-KPMv3: Reporting Period format 3 = %d", reportingPeriodFmt3);
            }
            else{
                printf("\nINFO   -->  E2SM-KPMv3: Subscription Definition isn't supported");
            }
        break;
        default:
            printf("\nINFO   -->  E2SM-KPMv3: Action Definition Format doesn't support");
    }

    kpmIndicationV3Enable = 1;
>>>>>>> Stashed changes
    // ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_ActionDefinition, actionDefin);
    return 0;

}

uint8_t kpmFreeIndicationHeader(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1){
    if(indicaHeaderFormat1->colletStartTime.size>0){
        if(indicaHeaderFormat1->colletStartTime.buf){
            DU_FREE(indicaHeaderFormat1->colletStartTime.buf, indicaHeaderFormat1->colletStartTime.size);
        }
    }
    if(indicaHeaderFormat1->senderName){
        kpmFreeOctetString(indicaHeaderFormat1->senderName); 
    }
    if(indicaHeaderFormat1->senderType){
        kpmFreeOctetString(indicaHeaderFormat1->senderType); 
    }
    if(indicaHeaderFormat1->vendorName){
        kpmFreeOctetString(indicaHeaderFormat1->vendorName); 
    }
    if(indicaHeaderFormat1->fileFormatversion){
        kpmFreeOctetString(indicaHeaderFormat1->fileFormatversion); 
    }
   return 0;
}

<<<<<<< Updated upstream
=======
uint8_t kpmFreeIndicationHeaderV3(E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1){
    if(indicaHeaderFormat1->colletStartTime.size>0){
        if(indicaHeaderFormat1->colletStartTime.buf){
            DU_FREE(indicaHeaderFormat1->colletStartTime.buf, indicaHeaderFormat1->colletStartTime.size);
        }
    }
    if(indicaHeaderFormat1->senderName){
        kpmFreeOctetString(indicaHeaderFormat1->senderName); 
    }
    if(indicaHeaderFormat1->senderType){
        kpmFreeOctetString(indicaHeaderFormat1->senderType); 
    }
    if(indicaHeaderFormat1->vendorName){
        kpmFreeOctetString(indicaHeaderFormat1->vendorName); 
    }
    if(indicaHeaderFormat1->fileFormatversion){
        kpmFreeOctetString(indicaHeaderFormat1->fileFormatversion); 
    }
   return 0;
}

>>>>>>> Stashed changes
uint8_t fillIndicationHeaderFormat1Optional(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1){
    uint8_t sender[] = "NTUST";
    uint8_t type[] = "DU";
    uint8_t vendor[] = "OSC";

    DU_ALLOC(indicaHeaderFormat1->senderName, sizeof(PrintableString_t));
    DU_ALLOC(indicaHeaderFormat1->senderType, sizeof(PrintableString_t));
    DU_ALLOC(indicaHeaderFormat1->vendorName, sizeof(PrintableString_t));

    // allocate memory for senderName.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->senderName->buf, sizeof(sender) * sizeof(uint8_t));
    if(indicaHeaderFormat1->senderName->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->senderName.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->senderName->size = sizeof(sender);
    memcpy(indicaHeaderFormat1->senderName->buf, sender, indicaHeaderFormat1->senderName->size);

    // allocate memory for senderType.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->senderType->buf, sizeof(type) * sizeof(uint8_t));
    if(indicaHeaderFormat1->senderType->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->senderType.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->senderType->size = sizeof(type);
    memcpy(indicaHeaderFormat1->senderType->buf, type, indicaHeaderFormat1->senderType->size);

    // allocate memory for vendorName.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->vendorName->buf, sizeof(vendor) * sizeof(uint8_t));
    if(indicaHeaderFormat1->vendorName->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->vendorName.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->vendorName->size = sizeof(vendor);
    memcpy(indicaHeaderFormat1->vendorName->buf, vendor, indicaHeaderFormat1->vendorName->size);

    return 0;
}

<<<<<<< Updated upstream
=======
uint8_t fillIndicationHeaderFormat1OptionalV3(E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1){
    uint8_t sender[] = "NTUST";
    uint8_t type[] = "DU";
    uint8_t vendor[] = "OSC";

    DU_ALLOC(indicaHeaderFormat1->senderName, sizeof(PrintableString_t));
    DU_ALLOC(indicaHeaderFormat1->senderType, sizeof(PrintableString_t));
    DU_ALLOC(indicaHeaderFormat1->vendorName, sizeof(PrintableString_t));

    // allocate memory for senderName.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->senderName->buf, sizeof(sender) * sizeof(uint8_t));
    if(indicaHeaderFormat1->senderName->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->senderName.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->senderName->size = sizeof(sender);
    memcpy(indicaHeaderFormat1->senderName->buf, sender, indicaHeaderFormat1->senderName->size);

    // allocate memory for senderType.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->senderType->buf, sizeof(type) * sizeof(uint8_t));
    if(indicaHeaderFormat1->senderType->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->senderType.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->senderType->size = sizeof(type);
    memcpy(indicaHeaderFormat1->senderType->buf, type, indicaHeaderFormat1->senderType->size);

    // allocate memory for vendorName.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->vendorName->buf, sizeof(vendor) * sizeof(uint8_t));
    if(indicaHeaderFormat1->vendorName->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->vendorName.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->vendorName->size = sizeof(vendor);
    memcpy(indicaHeaderFormat1->vendorName->buf, vendor, indicaHeaderFormat1->vendorName->size);

    return 0;
}

>>>>>>> Stashed changes
uint8_t fillIndicationHeaderFormat1(E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1){
    //printf("Function \"%s\" is start\n", __func__);
    
    time_t now = time(NULL);
    // unsigned long timestamp = (unsigned long)now * 1000; // 64-bit timestamp defined in section 6 of IETF RFC 5905
    unsigned long timestamp = (unsigned long)now;
    uint8_t ts[4];
    for(int i=0;i<4;i++){
        ts[i] = timestamp % 256;
        timestamp = timestamp / 256;
    }
    // allocate memory for colletStartTime.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->colletStartTime.buf, 4 * sizeof(uint8_t));
    if(indicaHeaderFormat1->colletStartTime.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->colletStartTime.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->colletStartTime.size = 4;
    memcpy(indicaHeaderFormat1->colletStartTime.buf,ts, 4);
    if(fillIndicationHeaderFormat1Optional(indicaHeaderFormat1) != RFAILED){
        return RFAILED;
    }

    return 0;
}

<<<<<<< Updated upstream
=======
uint8_t fillIndicationHeaderFormat1V3(E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1){
    //printf("Function \"%s\" is start\n", __func__);

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    uint64_t timestamp = (uint64_t)current_time.tv_sec * 1000000 + current_time.tv_usec;

    // printf("64-bit timestamp in microseconds: %llu\n", timestamp);
    // unsigned long timestamp = (unsigned long)now * 1000; // 64-bit timestamp defined in section 6 of IETF RFC 5905
    // unsigned long timestamp = (unsigned long)now;
    uint8_t ts[8];
    for(int i=0;i<8;i++){
        ts[i] = timestamp % 256;
        timestamp = timestamp / 256;
    }
    // allocate memory for colletStartTime.buf by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1->colletStartTime.buf, 8 * sizeof(uint8_t));
    if(indicaHeaderFormat1->colletStartTime.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1->colletStartTime.buf");
        return RFAILED;
    }
    indicaHeaderFormat1->colletStartTime.size = 8;
    memcpy(indicaHeaderFormat1->colletStartTime.buf,ts, 8);
    if(fillIndicationHeaderFormat1OptionalV3(indicaHeaderFormat1) != RFAILED){
        return RFAILED;
    }

    return 0;
}

>>>>>>> Stashed changes

uint8_t fillRicIndicationHeader(RICindicationHeader_t *ricIndicationHeader){
    printf("\nINFO   -->  E2SM-KPM : Fill KPM RIC Indication Header");

    E2SM_KPM_IndicationHeader_t *indicaHeader;
    // allocate memory for indicaHeader by DU_ALLOC
    DU_ALLOC(indicaHeader, sizeof(E2SM_KPM_IndicationHeader_t));
    if(indicaHeader == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeader");
        return RFAILED;
    }
    E2SM_KPM_IndicationHeader_Format1_t *indicaHeaderFormat1;
    // allocate memory for indicaHeaderFormat1 by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1, sizeof(E2SM_KPM_IndicationHeader_Format1_t));
    if(indicaHeaderFormat1 == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaHeaderFormat1");
        return RFAILED;
    }
    
    if(fillIndicationHeaderFormat1(indicaHeaderFormat1) != RFAILED){
        return RFAILED; 
    }

    indicaHeader->indicationHeader_formats.present = E2SM_KPM_IndicationHeader__indicationHeader_formats_PR_indicationHeader_Format1;
    indicaHeader->indicationHeader_formats.choice.indicationHeader_Format1 = indicaHeaderFormat1;

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationHeader, indicaHeader);

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;
    
    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
          ATS_ALIGNED_BASIC_PER,
          &asn_DEF_E2SM_KPM_IndicationHeader,
          indicaHeader, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Encode E2SM-KPM Indication Header failed");
    }
    else{
        // allocate memory for ricIndicationHeader->buf
        DU_ALLOC(ricIndicationHeader->buf, er.encoded * sizeof(uint8_t));
        if(ricIndicationHeader->buf == NULL){
            printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationHeader->buf");
            return RFAILED;
        }
        ricIndicationHeader->size = er.encoded;
        memcpy(ricIndicationHeader->buf,e2smbuffer,er.encoded);
    }

    kpmFreeIndicationHeader(indicaHeaderFormat1);
    DU_FREE(indicaHeaderFormat1, sizeof(E2SM_KPM_IndicationHeader_Format1_t));
    DU_FREE(indicaHeader, sizeof(E2SM_KPM_IndicationHeader_t));
    return 0;

<<<<<<< Updated upstream
=======
}

uint8_t fillRicIndicationHeaderV3(RICindicationHeader_t *ricIndicationHeader){
    printf("\nINFO   -->  E2SM-KPMv3 : Fill KPM RIC Indication Header");

    E2SM_KPM_IndicationHeader_v300_t *indicaHeader;
    // allocate memory for indicaHeader by DU_ALLOC
    DU_ALLOC(indicaHeader, sizeof(E2SM_KPM_IndicationHeader_v300_t));
    if(indicaHeader == NULL){
        printf("\nERROR   -->  E2SM-KPMv3 : Memory allocation failed for indicaHeader");
        return RFAILED;
    }
    E2SM_KPM_IndicationHeader_Format1_v300_t *indicaHeaderFormat1;
    // allocate memory for indicaHeaderFormat1 by DU_ALLOC
    DU_ALLOC(indicaHeaderFormat1, sizeof(E2SM_KPM_IndicationHeader_Format1_v300_t));
    if(indicaHeaderFormat1 == NULL){
        printf("\nERROR   -->  E2SM-KPMv3 : Memory allocation failed for indicaHeaderFormat1");
        return RFAILED;
    }
    
    if(fillIndicationHeaderFormat1V3(indicaHeaderFormat1) != RFAILED){
        return RFAILED; 
    }

    indicaHeader->indicationHeader_formats.present = E2SM_KPM_IndicationHeader_v300__indicationHeader_formats_PR_indicationHeader_Format1;
    indicaHeader->indicationHeader_formats.choice.indicationHeader_Format1 = indicaHeaderFormat1;

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationHeader_v300, indicaHeader);

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;
    
    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
          ATS_ALIGNED_BASIC_PER,
          &asn_DEF_E2SM_KPM_IndicationHeader_v300,
          indicaHeader, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPMv3 : Encode E2SM-KPM Indication Header failed");
    }
    else{
        // allocate memory for ricIndicationHeader->buf
        DU_ALLOC(ricIndicationHeader->buf, er.encoded * sizeof(uint8_t));
        if(ricIndicationHeader->buf == NULL){
            printf("\nERROR   -->  E2SM-KPMv3 : Memory allocation failed for ricIndicationHeader->buf");
            return RFAILED;
        }
        ricIndicationHeader->size = er.encoded;
        memcpy(ricIndicationHeader->buf,e2smbuffer,er.encoded);
    }

    kpmFreeIndicationHeaderV3(indicaHeaderFormat1);
    DU_FREE(indicaHeaderFormat1, sizeof(E2SM_KPM_IndicationHeader_Format1_v300_t));
    DU_FREE(indicaHeader, sizeof(E2SM_KPM_IndicationHeader_v300_t));
    return 0;
>>>>>>> Stashed changes
}

uint8_t fillSliceMeasDataItem(MeasurementDataItem_t *measDataItem, unsigned long intValue){
    //printf("Function \"%s\" is start\n", __func__);
    MeasurementRecordItem_t *measRecordItem;
    // allocate memory for measRecordItem by DU_ALLOC
    DU_ALLOC(measRecordItem, sizeof(MeasurementRecordItem_t));
    if(measRecordItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measRecordItem");
        return RFAILED;
    }
    
    measRecordItem->present = MeasurementRecordItem_PR_integer;
    measRecordItem->choice.integer = intValue; 
    ASN_SEQUENCE_ADD(&measDataItem->measRecord.list, measRecordItem);
    return 0;
}

uint8_t fillMeasDataItem(MeasurementDataItem_t *item, MeasurementRecordItem_PR present, int integer, double real){
    MeasurementRecordItem_t *measRecordItem;
    // allocate memory for measRecordItem by DU_ALLOC
    DU_ALLOC(measRecordItem, sizeof(MeasurementRecordItem_t));
    if(measRecordItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measRecordItem");
        return RFAILED;
    }
    
    if(present == MeasurementRecordItem_PR_integer){
        measRecordItem->present = MeasurementRecordItem_PR_integer;
        measRecordItem->choice.integer = integer;
    }
    else if(present == MeasurementRecordItem_PR_real){
        measRecordItem->present = MeasurementRecordItem_PR_real;
        measRecordItem->choice.real = real;
    }
    else if(present == MeasurementRecordItem_PR_noValue){
        measRecordItem->present = MeasurementRecordItem_PR_noValue;
    }
    else{
        return RFAILED;
    }
    ASN_SEQUENCE_ADD(&item->measRecord.list, measRecordItem);
    return 0;
}

uint8_t fillIndicationMessageFormat1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1){
    int index;

    MeasurementDataItem_t *measDataItem;
    // allocate memory for measDataItem by DU_ALLOC
    DU_ALLOC(measDataItem, sizeOfMeasNameFmt1 * sizeof(MeasurementDataItem_t));
    if(measDataItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measDataItem");
        return RFAILED;
    }
    MeasurementInfoList_t *measInfoList;
    // allocate memory for measInfoList by DU_ALLOC
    DU_ALLOC(measInfoList, sizeof(MeasurementInfoList_t));
    if(measInfoList == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoList");
        return RFAILED;
    }
    MeasurementInfoItem_t *measInfoItem;
    // allocate memory for measInfoItem by DU_ALLOC
    DU_ALLOC(measInfoItem, sizeOfMeasNameFmt1 * sizeof(MeasurementInfoItem_t));
    if(measInfoItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoItem");
        return RFAILED;
    }

    for(int i=0;i<sizeOfMeasNameFmt1;i++){
        index = actionFmt1measNameIsSupport(indicationMeasNameFmt1[i]);
        if(index == 0){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgThpDl, 0);
<<<<<<< Updated upstream
        }
        else if(index == 1){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgUsedPrb, 0);
        }
        else if(index == 2){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgTotalPrb, 0);
        }
        else if(index == 3){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_real, 0, (double)kpmCellPmDb.avgUsagePrb);
        }
=======
            printf("\nINFO   -->  E2SM-KPM : Cell Measurement \"%s\" : %d", indicationMeasNameFmt1[index], kpmCellPmDb.avgThpDl);
        }
        else if(index == 1){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgUsedPrb, 0);
            printf("\nINFO   -->  E2SM-KPM : Cell Measurement \"%s\" : %d", indicationMeasNameFmt1[index], kpmCellPmDb.avgUsedPrb);

        }
        else if(index == 2){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgTotalPrb, 0);
            printf("\nINFO   -->  E2SM-KPM : Cell Measurement \"%s\" : %d", indicationMeasNameFmt1[index], kpmCellPmDb.avgTotalPrb);

        }
        else if(index == 3){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_real, 0, (double)kpmCellPmDb.avgUsagePrb);
            printf("\nINFO   -->  E2SM-KPM : Cell Measurement \"%s\" : %f", indicationMeasNameFmt1[index], kpmCellPmDb.avgUsagePrb);

        }
         

>>>>>>> Stashed changes
    }

    indicaMessageFormat1->measInfoList = measInfoList;
    for(int i=0;i<sizeOfMeasNameFmt1;i++){
<<<<<<< Updated upstream
        fillMeasInfoItem(measInfoItem+i, (uint8_t*)measInfoStyle1+i, strlen((const char*)measInfoStyle1+i));
=======
        fillMeasInfoItem(measInfoItem+i, (uint8_t*)indicationMeasNameFmt1[i], strlen((const char*)indicationMeasNameFmt1[i]));
>>>>>>> Stashed changes
        ASN_SEQUENCE_ADD(&indicaMessageFormat1->measInfoList->list, measInfoItem+i);
        ASN_SEQUENCE_ADD(&indicaMessageFormat1->measData.list, measDataItem+i);
    }
    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage_Format1, indicaMessageFormat1);
    return 0; 
}

uint8_t fillIndicationMessageFormat1V3(E2SM_KPM_IndicationMessage_Format1_v300_t *indicaMessageFormat1){
    int index;

    MeasurementDataItem_t *measDataItem;
    // allocate memory for measDataItem by DU_ALLOC
    DU_ALLOC(measDataItem, sizeOfMeasNameFmt1 * sizeof(MeasurementDataItem_t));
    if(measDataItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measDataItem");
        return RFAILED;
    }
    MeasurementInfoList_v300_t *measInfoList;
    // allocate memory for measInfoList by DU_ALLOC
    DU_ALLOC(measInfoList, sizeof(MeasurementInfoList_v300_t));
    if(measInfoList == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoList");
        return RFAILED;
    }
    MeasurementInfoItem_v300_t *measInfoItem;
    // allocate memory for measInfoItem by DU_ALLOC
    DU_ALLOC(measInfoItem, sizeOfMeasNameFmt1 * sizeof(MeasurementInfoItem_v300_t));
    if(measInfoItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measInfoItem");
        return RFAILED;
    }

    for(int i=0;i<sizeOfMeasNameFmt1;i++){
        index = actionFmt1measNameIsSupport(indicationMeasNameFmt1[i]);
        if(index == 0){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgThpDl, 0);
        }
        else if(index == 1){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgUsedPrb, 0);
        }
        else if(index == 2){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_integer, kpmCellPmDb.avgTotalPrb, 0);
        }
        else if(index == 3){
            fillMeasDataItem(measDataItem + i, MeasurementRecordItem_PR_real, 0, (double)kpmCellPmDb.avgUsagePrb);
        }
    }

    indicaMessageFormat1->measInfoList = measInfoList;
    for(int i=0;i<sizeOfMeasNameFmt1;i++){
<<<<<<< Updated upstream
        fillMeasInfoItemV3(measInfoItem+i, (uint8_t*)measInfoStyle1+i, strlen((const char*)measInfoStyle1+i));
=======
        fillMeasInfoItemV3(measInfoItem+i, (uint8_t*)indicationMeasNameFmt1[i], strlen((const char*)indicationMeasNameFmt1[i]));
>>>>>>> Stashed changes
        ASN_SEQUENCE_ADD(&indicaMessageFormat1->measInfoList->list, measInfoItem+i);
        ASN_SEQUENCE_ADD(&indicaMessageFormat1->measData.list, measDataItem+i);
    }
    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage_Format1_v300, indicaMessageFormat1);
    return 0; 
}


uint8_t fillMeasCondItem(MeasurementCondUEidItem_t *measCondItem, char measureName[], Snssai snssai){
<<<<<<< Updated upstream
    printf("\nFunction \"%s\" is start\n", __func__);

=======
>>>>>>> Stashed changes
    MatchingCondItem_t *matchCondItem;
    // allocate memory for matchCondItem by DU_ALLOC
    DU_ALLOC(matchCondItem, sizeof(MatchingCondItem_t));
    if(matchCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem");
        return RFAILED;
    }

    measCondItem->measType.present = MeasurementType_PR_measName;
    measCondItem->measType.choice.measName.size = strlen((const char*)measureName);
    // allocate memory for measCondItem->measType.choice.measName.buf by DU_ALLOC
    DU_ALLOC(measCondItem->measType.choice.measName.buf, measCondItem->measType.choice.measName.size);
    if(measCondItem->measType.choice.measName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem->measType.choice.measName.buf");
        return RFAILED;
    }
<<<<<<< Updated upstream
    memcpy(measCondItem->measType.choice.measName.buf, measureName, measCondItem->measType.choice.measName.size);
    
    matchCondItem->present = MatchingCondItem_PR_measLabel;
    //allocate memory for matchCondItem->choice.measLabel by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel, sizeof(MeasurementLabel_t));
    if(matchCondItem->choice.measLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel");
        return RFAILED;
    }
    // allocte memory for matchCondItem->choice.measLabel->sliceID by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID, sizeof(S_NSSAI_t));
    if(matchCondItem->choice.measLabel->sliceID == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID");
        return RFAILED;
    }

    // allocate memory for matchCondItem->choice.measLabel->sliceID->sD by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sD, sizeof(SD_t));
    if(matchCondItem->choice.measLabel->sliceID->sD == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sD");
        return RFAILED;
    }
    
    matchCondItem->choice.measLabel->sliceID->sST.size = 1;
    // allocate memory for matchCondItem->choice.measLabel->sliceID->sST.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sST.buf, sizeof(uint8_t));
    if(matchCondItem->choice.measLabel->sliceID->sST.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sST.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->choice.measLabel->sliceID->sST.buf, &snssai.sst, 1);
    matchCondItem->choice.measLabel->sliceID->sD->size = 3;
    // allocate memory for matchCondItem->choice.measLabel->sliceID->sD.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sD->buf, sizeof(uint8_t));
    if(matchCondItem->choice.measLabel->sliceID->sD->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sD.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->choice.measLabel->sliceID->sD->buf, snssai.sd, 3);
    ASN_SEQUENCE_ADD(&measCondItem->matchingCond.list, matchCondItem);
    return 0;
}

uint8_t fillMeasCondItemV3(MeasurementCondUEidItem_v300_t *measCondItem, char measureName[], Snssai snssai){
    printf("\nINFO   -->  E2SM-KPM : Function \"%s\" is start\n", __func__);

    MatchingCondItem_v300_t *matchCondItem;
    // allocate memory for matchCondItem by DU_ALLOC
    DU_ALLOC(matchCondItem, sizeof(MatchingCondItem_v300_t));
    if(matchCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem");
        return RFAILED;
    }

    measCondItem->measType.present = MeasurementType_PR_measName;
    measCondItem->measType.choice.measName.size = strlen((const char*)measureName);
    // allocate memory for measCondItem->measType.choice.measName.buf by DU_ALLOC
    DU_ALLOC(measCondItem->measType.choice.measName.buf, measCondItem->measType.choice.measName.size);
    if(measCondItem->measType.choice.measName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem->measType.choice.measName.buf");
        return RFAILED;
    }
    memcpy(measCondItem->measType.choice.measName.buf, measureName, measCondItem->measType.choice.measName.size);


    matchCondItem->matchingCondChoice.present = MatchingCondItem_Choice_PR_measLabel;

    //allocate memory for matchCondItem->matchingCondChoice.choice.measLabel by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel, sizeof(MeasurementLabel_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel");
        return RFAILED;
    }
    // allocte memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID, sizeof(S_NSSAI_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID");
        return RFAILED;
    }

    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD, sizeof(SD_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD");
        return RFAILED;
    }
    
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.size = 1;
    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf, sizeof(uint8_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf, &snssai.sst, 1);
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->size = 3;
    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf, sizeof(uint8_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf, snssai.sd, 3);
=======
    memcpy(measCondItem->measType.choice.measName.buf, measureName, measCondItem->measType.choice.measName.size);
    
    matchCondItem->present = MatchingCondItem_PR_measLabel;
    //allocate memory for matchCondItem->choice.measLabel by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel, sizeof(MeasurementLabel_t));
    if(matchCondItem->choice.measLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel");
        return RFAILED;
    }
    // allocte memory for matchCondItem->choice.measLabel->sliceID by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID, sizeof(S_NSSAI_t));
    if(matchCondItem->choice.measLabel->sliceID == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID");
        return RFAILED;
    }

    // allocate memory for matchCondItem->choice.measLabel->sliceID->sD by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sD, sizeof(SD_t));
    if(matchCondItem->choice.measLabel->sliceID->sD == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sD");
        return RFAILED;
    }
    
    matchCondItem->choice.measLabel->sliceID->sST.size = 1;
    // allocate memory for matchCondItem->choice.measLabel->sliceID->sST.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sST.buf, sizeof(uint8_t));
    if(matchCondItem->choice.measLabel->sliceID->sST.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sST.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->choice.measLabel->sliceID->sST.buf, &snssai.sst, 1);
    matchCondItem->choice.measLabel->sliceID->sD->size = 3;
    // allocate memory for matchCondItem->choice.measLabel->sliceID->sD.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->choice.measLabel->sliceID->sD->buf, sizeof(uint8_t));
    if(matchCondItem->choice.measLabel->sliceID->sD->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->choice.measLabel->sliceID->sD.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->choice.measLabel->sliceID->sD->buf, snssai.sd, 3);
>>>>>>> Stashed changes
    ASN_SEQUENCE_ADD(&measCondItem->matchingCond.list, matchCondItem);
    return 0;
}

<<<<<<< Updated upstream

uint8_t fillIndicationMessageFormat2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2){
    printf("\nFunction \"%s\" is start\n", __func__);
    int styleSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);
    int measSize = MAX_SIZE_OF_SLICE;
    int cnt = 0;
    MeasurementDataItem_t *measDataItem;
    // allocate memory for measDataItem by DU_ALLOC
    DU_ALLOC(measDataItem, measSize * styleSize * sizeof(MeasurementDataItem_t));
    if(measDataItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measDataItem");
        return RFAILED;
    }
    MeasurementCondUEidItem_t *measCondItem;
    // allocate memory for measCondItem by DU_ALLOC
    DU_ALLOC(measCondItem, measSize * styleSize * sizeof(MeasurementCondUEidItem_t));
    if(measCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem");
        return RFAILED;
    }

    for(int i=0;i<kpmSlicePmDb.numOfSlice;i++){
        fillSliceMeasDataItem(measDataItem+cnt, kpmSlicePmDb.avgThpDl[i]);
        fillMeasCondItem(measCondItem+cnt, measInfoStyle2[0], kpmSlicePmDb.snssai[i]);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
        cnt = cnt + 1;
        fillSliceMeasDataItem(measDataItem+cnt, kpmSlicePmDb.avgUsedPrb[i]);
        fillMeasCondItem(measCondItem+cnt, measInfoStyle2[1], kpmSlicePmDb.snssai[i]);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
        cnt = cnt + 1;
=======
uint8_t fillMeasCondItemV3(MeasurementCondUEidItem_v300_t *measCondItem, char measureName[], Snssai snssai){
    printf("\nINFO   -->  E2SM-KPM : Function \"%s\" is start\n", __func__);

    MatchingCondItem_v300_t *matchCondItem;
    // allocate memory for matchCondItem by DU_ALLOC
    DU_ALLOC(matchCondItem, sizeof(MatchingCondItem_v300_t));
    if(matchCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem");
        return RFAILED;
    }

    measCondItem->measType.present = MeasurementType_PR_measName;
    measCondItem->measType.choice.measName.size = strlen((const char*)measureName);
    // allocate memory for measCondItem->measType.choice.measName.buf by DU_ALLOC
    DU_ALLOC(measCondItem->measType.choice.measName.buf, measCondItem->measType.choice.measName.size);
    if(measCondItem->measType.choice.measName.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem->measType.choice.measName.buf");
        return RFAILED;
    }
    memcpy(measCondItem->measType.choice.measName.buf, measureName, measCondItem->measType.choice.measName.size);


    matchCondItem->matchingCondChoice.present = MatchingCondItem_Choice_PR_measLabel;

    //allocate memory for matchCondItem->matchingCondChoice.choice.measLabel by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel, sizeof(MeasurementLabel_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel");
        return RFAILED;
    }
    // allocte memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID, sizeof(S_NSSAI_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID");
        return RFAILED;
    }

    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD, sizeof(SD_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD");
        return RFAILED;
    }
    
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.size = 1;
    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf, sizeof(uint8_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sST.buf, &snssai.sst, 1);
    matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->size = 3;
    // allocate memory for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD.buf by DU_ALLOC
    DU_ALLOC(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf, sizeof(uint8_t));
    if(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD.buf");
        return RFAILED;
    }
    memcpy(matchCondItem->matchingCondChoice.choice.measLabel->sliceID->sD->buf, snssai.sd, 3);
    ASN_SEQUENCE_ADD(&measCondItem->matchingCond.list, matchCondItem);
    return 0;
}


uint8_t fillIndicationMessageFormat2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2){
    // printf("\nFunction \"%s\" is start\n", __func__);
    int styleSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);
    int measSize = MAX_SIZE_OF_SLICE;
    int cnt = 0;
    int index;
    MeasurementDataItem_t *measDataItem;
    // allocate memory for measDataItem by DU_ALLOC
    DU_ALLOC(measDataItem, measSize * styleSize * sizeof(MeasurementDataItem_t));
    if(measDataItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measDataItem");
        return RFAILED;
    }
    MeasurementCondUEidItem_t *measCondItem;
    // allocate memory for measCondItem by DU_ALLOC
    DU_ALLOC(measCondItem, measSize * styleSize * sizeof(MeasurementCondUEidItem_t));
    if(measCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem");
        return RFAILED;
    }

    for(int i=0;i<kpmSlicePmDb.numOfSlice;i++){
        for(int j=0;j<sizeOfMeasNameFmt3;j++){
            index = actionFmt3measNameIsSupport(indicationMeasNameFmt3[j]);
            if(index == 0){
                printf("\nINFO   -->  E2SM-KPM : Slice Measurement \"%s\" in slice {%d-%d%d%d} : %d", indicationMeasNameFmt3[index],
                kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1],
                kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.avgThpDl[i]);
                fillSliceMeasDataItem(measDataItem + cnt, kpmSlicePmDb.avgThpDl[i]);
            }
            else if(index == 1){
                printf("\nINFO   -->  E2SM-KPM : Slice Measurement \"%s\" in slice {%d-%d%d%d} : %d", indicationMeasNameFmt3[index],
                kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1],
                kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.avgUsedPrb[i]);
                fillSliceMeasDataItem(measDataItem + cnt, kpmSlicePmDb.avgUsedPrb[i]);
            }
            else if(index = -1)
                return RFAILED;
            fillMeasCondItem(measCondItem+cnt, indicationMeasNameFmt3[index], kpmSlicePmDb.snssai[i]);
            ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
            ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
            cnt = cnt + 1;
        }
>>>>>>> Stashed changes
    }

    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage_Format2, indicaMessageFormat2);
    return 0; 
}

uint8_t fillIndicationMessageFormat2V3(E2SM_KPM_IndicationMessage_Format2_v300_t *indicaMessageFormat2){
    printf("\nFunction \"%s\" is start\n", __func__);
    int styleSize = sizeof(measInfoStyle2) / sizeof(*measInfoStyle2);
    int measSize = MAX_SIZE_OF_SLICE;
    int cnt = 0;
<<<<<<< Updated upstream
=======
    int index = 0;
>>>>>>> Stashed changes
    MeasurementDataItem_t *measDataItem;
    // allocate memory for measDataItem by DU_ALLOC
    DU_ALLOC(measDataItem, measSize * styleSize * sizeof(MeasurementDataItem_t));
    if(measDataItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measDataItem");
        return RFAILED;
    }
    MeasurementCondUEidItem_v300_t *measCondItem;
    // allocate memory for measCondItem by DU_ALLOC
    DU_ALLOC(measCondItem, measSize * styleSize * sizeof(MeasurementCondUEidItem_v300_t));
    if(measCondItem == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for measCondItem");
        return RFAILED;
    }
<<<<<<< Updated upstream

    for(int i=0;i<kpmSlicePmDb.numOfSlice;i++){
        fillSliceMeasDataItem(measDataItem+cnt, kpmSlicePmDb.avgThpDl[i]);
        fillMeasCondItemV3(measCondItem+cnt, measInfoStyle2[0], kpmSlicePmDb.snssai[i]);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
        cnt = cnt + 1;
        fillSliceMeasDataItem(measDataItem+cnt, kpmSlicePmDb.avgUsedPrb[i]);
        fillMeasCondItemV3(measCondItem+cnt, measInfoStyle2[1], kpmSlicePmDb.snssai[i]);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
        ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
        cnt = cnt + 1;
    }

=======

    for(int i=0;i<kpmSlicePmDb.numOfSlice;i++){
        for(int j=0;j<sizeOfMeasNameFmt3;j++){
            index = actionFmt3measNameIsSupport(indicationMeasNameFmt3[j]);
            if(index == 0){
                printf("\nINFO   -->  E2SM-KPMv3 : Slice Measurement \"%s\" in slice {%d-%d%d%d} : %d", indicationMeasNameFmt3[index],
                kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1],
                kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.avgThpDl[i]);
                fillSliceMeasDataItem(measDataItem + cnt, kpmSlicePmDb.avgThpDl[j]);
            }
            else if(index == 1){
                printf("\nINFO   -->  E2SM-KPMv3 : Slice Measurement \"%s\" in slice {%d-%d%d%d} : %d", indicationMeasNameFmt3[index],
                kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1],
                kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.avgUsedPrb[i]);
                fillSliceMeasDataItem(measDataItem + cnt, kpmSlicePmDb.avgUsedPrb[j]);
            }
            else if(index = -1)
                return RFAILED;
            fillMeasCondItemV3(measCondItem+cnt, indicationMeasNameFmt3[index], kpmSlicePmDb.snssai[i]);
            ASN_SEQUENCE_ADD(&indicaMessageFormat2->measData.list, measDataItem+cnt);
            ASN_SEQUENCE_ADD(&indicaMessageFormat2->measCondUEidList.list, measCondItem+cnt);
            cnt = cnt + 1;
        }
    }
>>>>>>> Stashed changes
    xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage_Format2, indicaMessageFormat2);
    return 0; 
}

uint8_t kpmFreeMeasInfoList(MeasurementInfoList_t *measInfoList){
    for(int i=0;i<measInfoList->list.count;i++){
        if(measInfoList->list.array[i]->measType.present == MeasurementType_PR_measName){
            DU_FREE(measInfoList->list.array[i]->measType.choice.measName.buf, measInfoList->list.array[i]->measType.choice.measName.size);
        }
        for(int j=0;j<measInfoList->list.array[i]->labelInfoList.list.count;j++){
            kpmFreeMeasLabel(&measInfoList->list.array[i]->labelInfoList.list.array[j]->measLabel);
        }
    }
    return 0;
}

uint8_t kpmFreeMeasInfoListV3(MeasurementInfoList_v300_t *measInfoList){
    for(int i=0;i<measInfoList->list.count;i++){
        if(measInfoList->list.array[i]->measType.present == MeasurementType_PR_measName){
            DU_FREE(measInfoList->list.array[i]->measType.choice.measName.buf, measInfoList->list.array[i]->measType.choice.measName.size);
        }
        for(int j=0;j<measInfoList->list.array[i]->labelInfoList.list.count;j++){
            kpmFreeMeasLabelV3(&measInfoList->list.array[i]->labelInfoList.list.array[j]->measLabel);
        }
    }
    return 0;
}

uint8_t kpmFreeRicIndicationMessageFmt1(E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1){
    // printf("\nFunction \"%s\" is start", __func__);
    kpmFreeMeasData(&indicaMessageFormat1->measData);
    if(indicaMessageFormat1->measInfoList){
        kpmFreeMeasInfoList(indicaMessageFormat1->measInfoList);
    }
    if(indicaMessageFormat1->granulPeriod){
        DU_FREE(indicaMessageFormat1->granulPeriod, sizeof(unsigned long));
    }
    return 0;
}

uint8_t kpmFreeRicIndicationMessageFmt1V3(E2SM_KPM_IndicationMessage_Format1_v300_t *indicaMessageFormat1){
    // printf("\nFunction \"%s\" is start", __func__);
    kpmFreeMeasData(&indicaMessageFormat1->measData);
    if(indicaMessageFormat1->measInfoList){
        kpmFreeMeasInfoListV3(indicaMessageFormat1->measInfoList);
    }
    if(indicaMessageFormat1->granulPeriod){
        DU_FREE(indicaMessageFormat1->granulPeriod, sizeof(unsigned long));
    }
    return 0;
}

uint8_t fillRicindicationMessageFmt1(RICindicationMessage_t *ricIndicaMsg){
    E2SM_KPM_IndicationMessage_t *indicaMessage;
    E2SM_KPM_IndicationMessage_Format1_t *indicaMessageFormat1;
    // allocate memory for indicaMessage by DU_ALLOC
    DU_ALLOC(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_t));
    if(indicaMessage == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessage");
        return RFAILED;
    }
    
    // allocate memory for indicaMessageFormat1 by DU_ALLOC
    DU_ALLOC(indicaMessageFormat1, sizeof(E2SM_KPM_IndicationMessage_Format1_t));
    if(indicaMessageFormat1 == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessageFormat1");
        return RFAILED;
    }

    fillIndicationMessageFormat1(indicaMessageFormat1);  
    indicaMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1;
    indicaMessage->indicationMessage_formats.choice.indicationMessage_Format1 = indicaMessageFormat1;
    
    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_IndicationMessage,
         indicaMessage, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Encode asn_DEF_E2SM_KPM_IndicationMessage 1 failed");
        printf("Failed to encode element %s", er.failed_type ? er.failed_type->name : ""); 

        return RFAILED;
    }
    else{
        // allocate memory for ricIndicaMsg->buf by DU_ALLOC
        DU_ALLOC(ricIndicaMsg->buf, er.encoded * sizeof(uint8_t));
        ricIndicaMsg->size = er.encoded;
        if(ricIndicaMsg->buf == NULL){
            DU_LOG("\nERROR   -->  E2SM-KPM : Allocate memory for ricIndicaMsg->buf failed");
            return RFAILED;
        }
        ricIndicaMsg->size = er.encoded;
        memcpy(ricIndicaMsg->buf,e2smbuffer,er.encoded);
    }

    kpmFreeRicIndicationMessageFmt1(indicaMessageFormat1);
    DU_FREE(indicaMessageFormat1, sizeof(E2SM_KPM_IndicationMessage_Format1_t));
    DU_FREE(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_t));

    return 0; 
}

int8_t fillRicindicationMessageFmt1V3(RICindicationMessage_t *ricIndicaMsg){
    E2SM_KPM_IndicationMessage_v300_t *indicaMessage;
    E2SM_KPM_IndicationMessage_Format1_v300_t *indicaMessageFormat1;
    // allocate memory for indicaMessage by DU_ALLOC
    DU_ALLOC(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_v300_t));
    if(indicaMessage == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessage");
        return RFAILED;
    }
    
    // allocate memory for indicaMessageFormat1 by DU_ALLOC
    DU_ALLOC(indicaMessageFormat1, sizeof(E2SM_KPM_IndicationMessage_Format1_v300_t));
    if(indicaMessageFormat1 == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessageFormat1");
        return RFAILED;
    }

    fillIndicationMessageFormat1V3(indicaMessageFormat1);  
    indicaMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1;
    indicaMessage->indicationMessage_formats.choice.indicationMessage_Format1 = indicaMessageFormat1;
    
    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_IndicationMessage_v300,
         indicaMessage, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Encode asn_DEF_E2SM_KPM_IndicationMessage 1 failed");
        printf("Failed to encode element %s", er.failed_type ? er.failed_type->name : ""); 

        return RFAILED;
    }
    else{
        // allocate memory for ricIndicaMsg->buf by DU_ALLOC
        DU_ALLOC(ricIndicaMsg->buf, er.encoded * sizeof(uint8_t));
        ricIndicaMsg->size = er.encoded;
        if(ricIndicaMsg->buf == NULL){
            DU_LOG("\nERROR   -->  E2SM-KPM : Allocate memory for ricIndicaMsg->buf failed");
            return RFAILED;
        }
        ricIndicaMsg->size = er.encoded;
        memcpy(ricIndicaMsg->buf,e2smbuffer,er.encoded);
    }

    kpmFreeRicIndicationMessageFmt1V3(indicaMessageFormat1);
    DU_FREE(indicaMessageFormat1, sizeof(E2SM_KPM_IndicationMessage_Format1_v300_t));
    DU_FREE(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_v300_t));

    return 0; 
}

uint8_t kpmFreeMeasData(MeasurementData_t *measData){
    for(int i=0;i<measData->list.count;i++){
        if(measData->list.array[i] != NULL){
            if(measData->list.array[i]->incompleteFlag){
                DU_FREE(measData->list.array[i]->incompleteFlag, sizeof(long));
            }

            for(int j=0;j<measData->list.array[i]->measRecord.list.count;j++){
                if(measData->list.array[i]->measRecord.list.array[j] != NULL){
                    DU_FREE(measData->list.array[i]->measRecord.list.array[j], sizeof(MeasurementRecordItem_t));
                }
            }
        }
    }

    return 0;
}

uint8_t kpmFreeMeasLabel(MeasurementLabel_t *measLabel){
    if(measLabel->noLabel){
        DU_FREE(measLabel->noLabel, sizeof(long));
    }
    if(measLabel->plmnID){
        kpmFreeOctetString(measLabel->plmnID);
    }
    if(measLabel->sliceID){
        if(measLabel->sliceID->sD){
            kpmFreeOctetString(measLabel->sliceID->sD);
        }
        if(measLabel->sliceID->sST.size>0){
            DU_FREE(measLabel->sliceID->sST.buf, measLabel->sliceID->sST.size);
        }
    }
    if(measLabel->fiveQI){
        DU_FREE(measLabel->fiveQI, sizeof(long));
    }
    if(measLabel->qFI){
        DU_FREE(measLabel->qFI, sizeof(long));
    }
    if(measLabel->qCI){
        DU_FREE(measLabel->qCI, sizeof(long));   
    }
    if(measLabel->qCImax){
        DU_FREE(measLabel->qCImax, sizeof(long));
    }
    if(measLabel->qCImin){
        DU_FREE(measLabel->qCImin, sizeof(long));
    }
    if(measLabel->aRPmax){
        DU_FREE(measLabel->aRPmax, sizeof(long));
    }
    if(measLabel->aRPmin){
        DU_FREE(measLabel->aRPmin, sizeof(long));
    }
    if(measLabel->bitrateRange){
        DU_FREE(measLabel->bitrateRange, sizeof(long));
    }
    if(measLabel->layerMU_MIMO){
        DU_FREE(measLabel->layerMU_MIMO, sizeof(long));
    }
    if(measLabel->sUM){
        DU_FREE(measLabel->sUM, sizeof(long));
    }
    if(measLabel->distBinX){
        DU_FREE(measLabel->distBinX, sizeof(long));
    }
    if(measLabel->distBinY){
        DU_FREE(measLabel->distBinY, sizeof(long));
    }
    if(measLabel->distBinZ){
        DU_FREE(measLabel->distBinZ, sizeof(long));
    }
    if(measLabel->min){
        DU_FREE(measLabel->min, sizeof(long));
    }
    if(measLabel->max){
        DU_FREE(measLabel->max, sizeof(long));
    }
    if(measLabel->avg){
        DU_FREE(measLabel->avg, sizeof(long));
    }
    return 0;
}

uint8_t kpmFreeMeasLabelV3(MeasurementLabel_v300_t *measLabel){
    if(measLabel->noLabel){
        DU_FREE(measLabel->noLabel, sizeof(long));
    }
    if(measLabel->plmnID){
        kpmFreeOctetString(measLabel->plmnID);
    }
    if(measLabel->sliceID){
        if(measLabel->sliceID->sD){
            kpmFreeOctetString(measLabel->sliceID->sD);
        }
        if(measLabel->sliceID->sST.size>0){
            DU_FREE(measLabel->sliceID->sST.buf, measLabel->sliceID->sST.size);
        }
    }
    if(measLabel->fiveQI){
        DU_FREE(measLabel->fiveQI, sizeof(long));
    }
    if(measLabel->qFI){
        DU_FREE(measLabel->qFI, sizeof(long));
    }
    if(measLabel->qCI){
        DU_FREE(measLabel->qCI, sizeof(long));   
    }
    if(measLabel->qCImax){
        DU_FREE(measLabel->qCImax, sizeof(long));
    }
    if(measLabel->qCImin){
        DU_FREE(measLabel->qCImin, sizeof(long));
    }
    if(measLabel->aRPmax){
        DU_FREE(measLabel->aRPmax, sizeof(long));
    }
    if(measLabel->aRPmin){
        DU_FREE(measLabel->aRPmin, sizeof(long));
    }
    if(measLabel->bitrateRange){
        DU_FREE(measLabel->bitrateRange, sizeof(long));
    }
    if(measLabel->layerMU_MIMO){
        DU_FREE(measLabel->layerMU_MIMO, sizeof(long));
    }
    if(measLabel->sUM){
        DU_FREE(measLabel->sUM, sizeof(long));
    }
    if(measLabel->distBinX){
        DU_FREE(measLabel->distBinX, sizeof(long));
    }
    if(measLabel->distBinY){
        DU_FREE(measLabel->distBinY, sizeof(long));
    }
    if(measLabel->distBinZ){
        DU_FREE(measLabel->distBinZ, sizeof(long));
    }
    if(measLabel->min){
        DU_FREE(measLabel->min, sizeof(long));
    }
    if(measLabel->max){
        DU_FREE(measLabel->max, sizeof(long));
    }
    if(measLabel->avg){
        DU_FREE(measLabel->avg, sizeof(long));
    }
    if(measLabel->ssbIndex){
        DU_FREE(measLabel->ssbIndex, sizeof(long));
    }
    if(measLabel->ssbIndex){
        DU_FREE(measLabel->nonGoB_BFmode_Index, sizeof(long));
    }
    if(measLabel->ssbIndex){
        DU_FREE(measLabel->mIMO_mode_Index, sizeof(long));
    }
    return 0;
}

uint8_t kpmFreeCondUEidList(MeasurementCondUEidList_t *measCondUEidList){
    MeasurementLabel_t *measLabel;
    for(int i=0;i<measCondUEidList->list.count;i++){
        if(measCondUEidList->list.array[i] != NULL){
            if(measCondUEidList->list.array[i]->measType.present == MeasurementType_PR_measName){
                DU_FREE(measCondUEidList->list.array[i]->measType.choice.measName.buf, measCondUEidList->list.array[i]->measType.choice.measName.size);
            }
            for(int j=0;j<measCondUEidList->list.array[i]->matchingCond.list.count;j++){
                if(measCondUEidList->list.array[i]->matchingCond.list.array[j]){
                    switch(measCondUEidList->list.array[i]->matchingCond.list.array[j]->present){
                        case MatchingCondItem_PR_measLabel:
                            measLabel = measCondUEidList->list.array[i]->matchingCond.list.array[j]->choice.measLabel;
                            kpmFreeMeasLabel(measLabel);
                        break;
                        case MatchingCondItem_PR_testCondInfo:
                            printf("\nERROR   -->  E2SM-KPM : Freeing testCondInfo is not supported");
                        default:
                            printf("\nERROR   -->  E2SM-KPM : kpmFreeCondUEidList type is invaild");
                        break;
                    }
                }
            }
            if(measCondUEidList->list.array[i]->matchingUEidList){
                printf("\nERROR   -->  E2SM-KPM : Free matchingUEidList is not supported");
            }

        }
    }
    return 0;
}

uint8_t kpmFreeCondUEidListV3(MeasurementCondUEidList_v300_t *measCondUEidList){
    MeasurementLabel_v300_t *measLabel;
    for(int i=0;i<measCondUEidList->list.count;i++){
        if(measCondUEidList->list.array[i] != NULL){
            if(measCondUEidList->list.array[i]->measType.present == MeasurementType_PR_measName){
                DU_FREE(measCondUEidList->list.array[i]->measType.choice.measName.buf, measCondUEidList->list.array[i]->measType.choice.measName.size);
            }
            for(int j=0;j<measCondUEidList->list.array[i]->matchingCond.list.count;j++){
                if(measCondUEidList->list.array[i]->matchingCond.list.array[j]){
                    switch(measCondUEidList->list.array[i]->matchingCond.list.array[j]->matchingCondChoice.present){
                        case MatchingCondItem_Choice_PR_measLabel:
                            measLabel = measCondUEidList->list.array[i]->matchingCond.list.array[j]->matchingCondChoice.choice.measLabel;
                            kpmFreeMeasLabelV3(measLabel);
                        break;
                        case MatchingCondItem_Choice_PR_testCondInfo:
                            printf("\nERROR   -->  E2SM-KPM : Freeing testCondInfo is not supported");
                        default:
                            printf("\nERROR   -->  E2SM-KPM : kpmFreeCondUEidListV3 type is invaild");
                        break;
                    }
                }
            }
            if(measCondUEidList->list.array[i]->matchingUEidList){
                printf("\nERROR   -->  E2SM-KPM : Free matchingUEidList is not supported");
            }

        }
    }
    return 0;
}

uint8_t kpmFreeRicIndicationMessageFmt2(E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2){
    kpmFreeMeasData(&indicaMessageFormat2->measData);
    kpmFreeCondUEidList(&indicaMessageFormat2->measCondUEidList);
    if(indicaMessageFormat2->granulPeriod){
        DU_FREE(indicaMessageFormat2->granulPeriod, sizeof(unsigned long));
    }
    return 0;
}

uint8_t kpmFreeRicIndicationMessageFmt2V3(E2SM_KPM_IndicationMessage_Format2_v300_t *indicaMessageFormat2){
    kpmFreeMeasData(&indicaMessageFormat2->measData);
    kpmFreeCondUEidListV3(&indicaMessageFormat2->measCondUEidList);
    if(indicaMessageFormat2->granulPeriod){
        DU_FREE(indicaMessageFormat2->granulPeriod, sizeof(unsigned long));
    }
    return 0;
}

uint8_t fillRicindicationMessageFmt2(RICindicationMessage_t *ricIndicaMsg){
    E2SM_KPM_IndicationMessage_t *indicaMessage;
    
    // allocate memory for indicaMessage by DU_ALLOC
    DU_ALLOC(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_t));
    if(indicaMessage == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessage");
        return RFAILED;
    }

    E2SM_KPM_IndicationMessage_Format2_t *indicaMessageFormat2;
    // allocate memory for indicaMessageFormat2 by DU_ALLOC
    DU_ALLOC(indicaMessageFormat2, sizeof(E2SM_KPM_IndicationMessage_Format2_t));
    if(indicaMessageFormat2 == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessageFormat2");
        return RFAILED;
    }
    
    fillIndicationMessageFormat2(indicaMessageFormat2);  
    indicaMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2;
    indicaMessage->indicationMessage_formats.choice.indicationMessage_Format2 = indicaMessageFormat2;

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_IndicationMessage,
         indicaMessage, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Encode asn_DEF_E2SM_KPM_IndicationMessage 2 failed");
        return RFAILED;
    }
    else{
        // allocate memory for ricIndicaMsg->buf by DU_ALLOC
        DU_ALLOC(ricIndicaMsg->buf, er.encoded * sizeof(uint8_t));
        ricIndicaMsg->size = er.encoded;
        if(ricIndicaMsg->buf == NULL){
            DU_LOG("\nERROR   -->  E2SM-KPM : Allocate memory for ricIndicaMsg->buf failed");
            return RFAILED;
        }
        ricIndicaMsg->size = er.encoded;
        memcpy(ricIndicaMsg->buf,e2smbuffer,er.encoded);
    }

    kpmFreeRicIndicationMessageFmt2(indicaMessageFormat2);
    DU_FREE(indicaMessageFormat2, sizeof(E2SM_KPM_IndicationMessage_Format2_t));
    DU_FREE(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_t));

    return 0; 
}

uint8_t fillRicindicationMessageFmt2V3(RICindicationMessage_t *ricIndicaMsg){
    E2SM_KPM_IndicationMessage_v300_t *indicaMessage;
    
    // allocate memory for indicaMessage by DU_ALLOC
    DU_ALLOC(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_v300_t));
    if(indicaMessage == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessage");
        return RFAILED;
    }

    E2SM_KPM_IndicationMessage_Format2_v300_t *indicaMessageFormat2;
    // allocate memory for indicaMessageFormat2 by DU_ALLOC
    DU_ALLOC(indicaMessageFormat2, sizeof(E2SM_KPM_IndicationMessage_Format2_v300_t));
    if(indicaMessageFormat2 == NULL){
        printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for indicaMessageFormat2");
        return RFAILED;
    }
    
    fillIndicationMessageFormat2V3(indicaMessageFormat2);  
    indicaMessage->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2;
    indicaMessage->indicationMessage_formats.choice.indicationMessage_Format2 = indicaMessageFormat2;

    uint8_t e2smbuffer[8192] = {0, };
    size_t e2smbuffer_size = 8192;
    asn_codec_ctx_t *opt_cod = 0;

    asn_enc_rval_t er =
    asn_encode_to_buffer(opt_cod,
         ATS_ALIGNED_BASIC_PER,
         &asn_DEF_E2SM_KPM_IndicationMessage_v300,
         indicaMessage, e2smbuffer, e2smbuffer_size);

    if(er.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Encode asn_DEF_E2SM_KPM_IndicationMessage_v300 failed");
        return RFAILED;
    }
    else{
        // allocate memory for ricIndicaMsg->buf by DU_ALLOC
        DU_ALLOC(ricIndicaMsg->buf, er.encoded * sizeof(uint8_t));
        ricIndicaMsg->size = er.encoded;
        if(ricIndicaMsg->buf == NULL){
            DU_LOG("\nERROR   -->  E2SM-KPM : Allocate memory for ricIndicaMsg->buf failed");
            return RFAILED;
        }
        ricIndicaMsg->size = er.encoded;
        memcpy(ricIndicaMsg->buf,e2smbuffer,er.encoded);
    }

    kpmFreeRicIndicationMessageFmt2V3(indicaMessageFormat2);
    DU_FREE(indicaMessageFormat2, sizeof(E2SM_KPM_IndicationMessage_Format2_v300_t));
    DU_FREE(indicaMessage, sizeof(E2SM_KPM_IndicationMessage_v300_t));

    return 0; 
<<<<<<< Updated upstream
}

uint8_t kpmFreeOctetString(OCTET_STRING_t *octetString){
    if(octetString){
        if(octetString->size > 0){
            if(octetString->buf){
                DU_FREE(octetString->buf, octetString->size);
            }
        }
        DU_FREE(octetString, sizeof(OCTET_STRING_t));
        octetString = NULL;
        return ROK;
    }
    else{
        return RFAILED;
    }

}

void kpmSendSliceMetric(){
    if(kpmSliceIndicationEnable){
        if(ricIndicationMessage == NULL){
            // allocate memory for ricIndicationMessage by DU_ALLOC
            DU_ALLOC(ricIndicationMessage, sizeof(RICindicationMessage_t));
            if(ricIndicationMessage == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationMessage");
                return;
            }
        }
        kpmCalcCellMetric();
        fillRicindicationMessageFmt2(ricIndicationMessage);
        BuildAndSendRicIndication();
        DU_FREE(ricIndicationMessage->buf, ricIndicationMessage->size);
    }
}

void kpmSendCellMetric(){
    if(kpmCellIndicationEnable){
        if(ricIndicationMessage == NULL){
            // allocate memory for ricIndicationMessage by DU_ALLOC
            DU_ALLOC(ricIndicationMessage, sizeof(RICindicationMessage_t));
            if(ricIndicationMessage == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationMessage");
                return;
            }
        }
        kpmCalcSliceMetric();
        fillRicindicationMessageFmt1(ricIndicationMessage);
        BuildAndSendRicIndication();
        DU_FREE(ricIndicationMessage->buf, ricIndicationMessage->size);
    }
    else{
        printf("\nINFO   -->  E2SM-KPM : Do nothing");
    }
}

uint8_t kpmCalcCellMetric(){
    uint64_t usedPrbSum = 0, totalPrbSum = 0, thpSum = 0;

    if(kpmCellPmDb.numOfMacPm>SIZE_OF_MACDB){
        kpmCellPmDb.numOfMacPm = SIZE_OF_MACDB;
    }

    for(int i=0;i<kpmCellPmDb.numOfMacPm;i++){
        usedPrbSum += kpmCellPmDb.eachMacPm[i].usedPrb;
        totalPrbSum += kpmCellPmDb.eachMacPm[i].totalPrb;
    }

    for(int i=0;i<kpmCellPmDb.numOfRlcPm;i++){
        thpSum += kpmCellPmDb.eachRlcPm[i].ThpDl;
    }

    kpmCellPmDb.avgThpDl = kpmCellPmDb.numOfRlcPm ? thpSum / kpmCellPmDb.numOfRlcPm : kpmCellPmDb.avgThpDl;
    kpmCellPmDb.avgUsedPrb = kpmCellPmDb.numOfMacPm ? usedPrbSum / kpmCellPmDb.numOfMacPm : 0;
    kpmCellPmDb.avgTotalPrb = kpmCellPmDb.numOfMacPm ? totalPrbSum / kpmCellPmDb.numOfMacPm : 0;
    kpmCellPmDb.avgUsagePrb = kpmCellPmDb.numOfMacPm ? (double)100.0 * kpmCellPmDb.avgUsedPrb / kpmCellPmDb.avgTotalPrb  : 0;

    kpmCellPmDb.numOfMacPm = 0;
    kpmCellPmDb.numOfRlcPm = 0;
    return 0;    
}

uint8_t kpmCalcSliceMetric(){
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    if(kpmSlicePmDb.numOfMacPm>SIZE_OF_MACDB){
        kpmSlicePmDb.numOfMacPm = SIZE_OF_MACDB;
    }

    for(int i=0;i<kpmSlicePmDb.numOfMacPm;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[i].sliceRecord[j].usedPrb;
        }
    }

    for(int i=0;i<kpmSlicePmDb.numOfRlcPm;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[i].sliceRecord[j].ThpDl;
        }
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){
        printf("\nINFO   -->  E2KPM : thpSum[%d] = %ld", i, thpSum[i]);
        kpmSlicePmDb.avgUsedPrb[i] = kpmSlicePmDb.numOfMacPm ? usedPrbSum[i] / kpmSlicePmDb.numOfMacPm : 0;
        kpmSlicePmDb.avgThpDl[i] = kpmSlicePmDb.numOfRlcPm ? thpSum[i] / kpmSlicePmDb.numOfRlcPm : kpmSlicePmDb.avgThpDl[i];
    }

    kpmSlicePmDb.numOfMacPm = 0;
    kpmSlicePmDb.numOfRlcPm = 0;
    return 0;

}

void kpmStoreCellRlcMetric(CellPmList* cellMetricList){
    if(cellMetricList != NULL){
        if(cellMetricList->numUe>0){
            printf("\nINFO   -->  E2SM-KPM : Support sending UE Average Throughput to xApp");
            if(kpmCellPmDb.numOfRlcPm<SIZE_OF_RLCDB){
                kpmCellPmDb.eachRlcPm[kpmCellPmDb.numOfRlcPm].ThpDl = cellMetricList->ueRecord->ThpDl;
                kpmCellPmDb.numOfRlcPm++;
            }
            else{
                printf("\nINFO   -->  E2SM-KPM : kpmCellPmDb is full at kpmStoreCellRlcMetric");
            }
        }
    }
}

void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList){
    if(sliceMetricList){
        if(kpmSlicePmDb.numOfRlcPm < SIZE_OF_RLCDB){
            for(int i=0;i<sliceMetricList->numSlice;i++){
                kpmSlicePmDb.eachRlcPm[kpmSlicePmDb.numOfRlcPm].sliceRecord[i].ThpDl = (int)sliceMetricList->sliceRecord[i].ThpDl;
                kpmSlicePmDb.snssai[i].sst = (char)sliceMetricList->sliceRecord[i].networkSliceIdentifier.sst;
                kpmSlicePmDb.snssai[i].sd[0] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 100 ) % 10;
                kpmSlicePmDb.snssai[i].sd[1] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 10) % 10;
                kpmSlicePmDb.snssai[i].sd[2] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd ) % 10; 
            }
            kpmSlicePmDb.eachRlcPm[kpmSlicePmDb.numOfRlcPm].numOfSlice = sliceMetricList->numSlice;
        }
        kpmSlicePmDb.numOfRlcPm++;
    }
}

=======
}

uint8_t kpmFreeOctetString(OCTET_STRING_t *octetString){
    if(octetString){
        if(octetString->size > 0){
            if(octetString->buf){
                DU_FREE(octetString->buf, octetString->size);
            }
        }
        DU_FREE(octetString, sizeof(OCTET_STRING_t));
        octetString = NULL;
        return ROK;
    }
    else{
        return RFAILED;
    }

}

void kpmSendSliceMetric(){
    if(kpmSliceIndicationEnable){
        if(ricIndicationMessage == NULL){
            // allocate memory for ricIndicationMessage by DU_ALLOC
            DU_ALLOC(ricIndicationMessage, sizeof(RICindicationMessage_t));
            if(ricIndicationMessage == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationMessage");
                return;
            }
        }

        if(ricIndicationHeader == NULL){
            // allocate memory for ricIndicationHeader by DU_ALLOC
            DU_ALLOC(ricIndicationHeader, sizeof(RICindicationHeader_t));
            if(ricIndicationHeader == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationHeader");
                return;
            }
        }

        kpmCalcSliceMetric();
        if(kpmIndicationV3Enable){
            fillRicIndicationHeaderV3(ricIndicationHeader);
            fillRicindicationMessageFmt2V3(ricIndicationMessage);
        }else{
            fillRicIndicationHeader(ricIndicationHeader);
            fillRicindicationMessageFmt2(ricIndicationMessage);
        }
        BuildAndSendRicIndication();
        DU_FREE(ricIndicationMessage->buf, ricIndicationMessage->size);
    }
}

void kpmSendCellMetric(){
    if(kpmCellIndicationEnable){
        if(ricIndicationMessage == NULL){
            // allocate memory for ricIndicationMessage by DU_ALLOC
            DU_ALLOC(ricIndicationMessage, sizeof(RICindicationMessage_t));
            if(ricIndicationMessage == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationMessage");
                return;
            }
        }
        if(ricIndicationHeader == NULL){
            // allocate memory for ricIndicationHeader by DU_ALLOC
            DU_ALLOC(ricIndicationHeader, sizeof(RICindicationHeader_t));
            if(ricIndicationHeader == NULL){
                printf("\nERROR   -->  E2SM-KPM : Memory allocation failed for ricIndicationHeader");
                return;
            }
        }

        kpmCalcCellMetric();
        if(kpmIndicationV3Enable){
            fillRicIndicationHeaderV3(ricIndicationHeader);
            fillRicindicationMessageFmt1V3(ricIndicationMessage);
        }else{
            fillRicIndicationHeader(ricIndicationHeader);
            fillRicindicationMessageFmt1(ricIndicationMessage);
        }
        BuildAndSendRicIndication();
        DU_FREE(ricIndicationMessage->buf, ricIndicationMessage->size);
    }
}

uint8_t kpmCalcCellMetric(){
    uint64_t usedPrbSum = 0, totalPrbSum = 0, thpSum = 0;

    if(kpmCellPmDb.numOfMacPm>SIZE_OF_MACDB){
        kpmCellPmDb.numOfMacPm = SIZE_OF_MACDB;
    }

    for(int i=0;i<kpmCellPmDb.numOfMacPm;i++){
        usedPrbSum += kpmCellPmDb.eachMacPm[i].usedPrb;
        totalPrbSum += kpmCellPmDb.eachMacPm[i].totalPrb;
    }

    for(int i=0;i<kpmCellPmDb.numOfRlcPm;i++){
        thpSum += kpmCellPmDb.eachRlcPm[i].ThpDl;
    }

    kpmCellPmDb.avgThpDl = kpmCellPmDb.numOfRlcPm ? thpSum / kpmCellPmDb.numOfRlcPm : kpmCellPmDb.avgThpDl;
    kpmCellPmDb.avgUsedPrb = kpmCellPmDb.numOfMacPm ? usedPrbSum / kpmCellPmDb.numOfMacPm : 0;
    kpmCellPmDb.avgTotalPrb = kpmCellPmDb.numOfMacPm ? totalPrbSum / kpmCellPmDb.numOfMacPm : 0;
    kpmCellPmDb.avgUsagePrb = kpmCellPmDb.numOfMacPm ? (double)100.0 * kpmCellPmDb.avgUsedPrb / kpmCellPmDb.avgTotalPrb  : 0;

    kpmCellPmDb.numOfMacPm = 0;
    kpmCellPmDb.numOfRlcPm = 0;

    return 0;    
}

uint8_t kpmCalcSliceMetric(){
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    if(kpmSlicePmDb.numOfMacPm>SIZE_OF_MACDB){
        kpmSlicePmDb.numOfMacPm = SIZE_OF_MACDB;
    }

    for(int i=0;i<kpmSlicePmDb.numOfMacPm;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[i].sliceRecord[j].usedPrb;
        }
    }

    for(int i=0;i<kpmSlicePmDb.numOfRlcPm;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[i].sliceRecord[j].ThpDl;
        }
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){
        kpmSlicePmDb.avgUsedPrb[i] = kpmSlicePmDb.numOfMacPm ? usedPrbSum[i] / kpmSlicePmDb.numOfMacPm : 0;
        kpmSlicePmDb.avgThpDl[i] = kpmSlicePmDb.numOfRlcPm ? thpSum[i] / kpmSlicePmDb.numOfRlcPm : kpmSlicePmDb.avgThpDl[i];
    }


    kpmSlicePmDb.numOfMacPm = 0;
    kpmSlicePmDb.numOfRlcPm = 0;

    return 0;

}

void kpmStoreCellRlcMetric(CellPmList* cellMetricList){
    if(cellMetricList != NULL){
        if(cellMetricList->numUe>0){
            printf("\nINFO   -->  E2SM-KPM : Support sending UE Average Throughput to xApp");
            if(kpmCellPmDb.numOfRlcPm<SIZE_OF_RLCDB){
                kpmCellPmDb.eachRlcPm[kpmCellPmDb.numOfRlcPm].ThpDl = cellMetricList->ueRecord->ThpDl;
                kpmCellPmDb.numOfRlcPm++;
            }
            else{
                printf("\nINFO   -->  E2SM-KPM : kpmCellPmDb is full at kpmStoreCellRlcMetric");
            }
        }
    }
}

void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList){
    if(sliceMetricList){
        if(kpmSlicePmDb.numOfRlcPm < SIZE_OF_RLCDB){
            for(int i=0;i<sliceMetricList->numSlice;i++){
                kpmSlicePmDb.eachRlcPm[kpmSlicePmDb.numOfRlcPm].sliceRecord[i].ThpDl = (int)sliceMetricList->sliceRecord[i].ThpDl;
                kpmSlicePmDb.snssai[i].sst = (char)sliceMetricList->sliceRecord[i].networkSliceIdentifier.sst;
                kpmSlicePmDb.snssai[i].sd[0] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 100 ) % 10;
                kpmSlicePmDb.snssai[i].sd[1] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 10) % 10;
                kpmSlicePmDb.snssai[i].sd[2] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd ) % 10; 
            }
            kpmSlicePmDb.eachRlcPm[kpmSlicePmDb.numOfRlcPm].numOfSlice = sliceMetricList->numSlice;
        }
        kpmSlicePmDb.numOfRlcPm++;
    }

    kpmSendCellMetric();
    kpmSendSliceMetric();
}

>>>>>>> Stashed changes
void kpmStoreMacMetric(MacPrbPm* macPrbPm){ // Enter this function per millisecond. 
    if(macPrbPm != NULL){
        kpmCellPmDb.eachMacPm[kpmCellPmDb.numOfMacPm % SIZE_OF_MACDB].usedPrb = macPrbPm->usedPrb;
        kpmCellPmDb.eachMacPm[kpmCellPmDb.numOfMacPm % SIZE_OF_MACDB].totalPrb = macPrbPm->totalPrb;
        kpmCellPmDb.numOfMacPm++;
        
        kpmSlicePmDb.numOfSlice = macPrbPm->sliceNum;
        // printf("\nINFO   -->  E2SM-KPM : kpmSlicePmDb.numOfSlice = %d", kpmSlicePmDb.numOfSlice);
        for(int i=0;i<macPrbPm->sliceNum;i++){
            kpmSlicePmDb.eachMacPm[kpmSlicePmDb.numOfMacPm % SIZE_OF_MACDB].numOfSlice = macPrbPm->sliceNum;
<<<<<<< Updated upstream
            if(macPrbPm->listOfSlicePm)
                kpmSlicePmDb.eachMacPm[kpmSlicePmDb.numOfMacPm % SIZE_OF_MACDB].sliceRecord[i].usedPrb = macPrbPm->listOfSlicePm[i].usedPrb;
=======
            if(macPrbPm->listOfSlicePm){
                kpmSlicePmDb.eachMacPm[kpmSlicePmDb.numOfMacPm % SIZE_OF_MACDB].sliceRecord[i].usedPrb = macPrbPm->listOfSlicePm[i].usedPrb;
            }

>>>>>>> Stashed changes
        }
        kpmSlicePmDb.numOfMacPm++;
    }
    else{
        printf("\nERROR   -->  E2SM-KPM : Empty macPrbPm");
    }

<<<<<<< Updated upstream
    if(indicationCountFmt1<reportingPeriodFmt1){
=======
    if(indicationCountFmt1<reportingPeriodFmt1 / 4){ // Phy stub sends slot indication by 4. 
>>>>>>> Stashed changes
        indicationCountFmt1++;
    }
    else{
        indicationCountFmt1 = 0;
<<<<<<< Updated upstream
        kpmSendCellMetric();
    }

    if(indicationCountFmt3<reportingPeriodFmt3){
=======
        // kpmSendCellMetric();
    }

    if(indicationCountFmt3<reportingPeriodFmt3 / 4){
>>>>>>> Stashed changes
        indicationCountFmt3++;
    }
    else{
        indicationCountFmt3 = 0;
<<<<<<< Updated upstream
        kpmSendSliceMetric();
=======
        // kpmSendSliceMetric();
>>>>>>> Stashed changes
    }

    return;
}