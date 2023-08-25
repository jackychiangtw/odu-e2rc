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

/* This file contains E2AP message handler functions */
#include "common_def.h"
#include "OCTET_STRING.h"
#include "BIT_STRING.h"
#include "odu_common_codec.h"
#include "ric_stub_sctp.h"
#include "ric_stub.h"
#include "ric_e2ap_msg_hdl.h"
#include "GlobalE2node-gNB-ID.h"
#include "ProtocolIE-FieldE2.h"
#include "InitiatingMessageE2.h"
#include "SuccessfulOutcomeE2.h"
#include "E2AP-PDU.h"
#include "du_log.h"
#include "E2nodeComponentInterfaceF1.h"
#include "ric_e2sm_kpm_handler.h"

uint8_t procKpmRanFunDescrpition(RANfunctionDefinition_t ranFuncDefinition){
   
   E2SM_KPM_RANfunction_Description_t *RAN_Function_Description = (E2SM_KPM_RANfunction_Description_t*)calloc(1, sizeof(E2SM_KPM_RANfunction_Description_t));
   asn_dec_rval_t dr = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_RANfunction_Description, (void **)&RAN_Function_Description, ranFuncDefinition.buf, ranFuncDefinition.size);
    if(dr.code == RC_OK){
         xer_fprint(stderr,  &asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
         ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
         return ROK;
      }
    else{
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
        return RFAILED;
    }
}

uint8_t fillKpmEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefinition, unsigned long report_period){
  E2SM_KPM_EventTriggerDefinition_t *Event_Trigger_Definition = (E2SM_KPM_EventTriggerDefinition_t *)calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));
  if(Event_Trigger_Definition == NULLP){
    DU_LOG("\nERROR   -->  E2SM-KPM : Memory Allocation for Event Trigger Definition Failed, %d", __LINE__);
    return RFAILED;
  }
  E2SM_KPM_EventTriggerDefinition_Format1_t *Format1 = (E2SM_KPM_EventTriggerDefinition_Format1_t *)calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_Format1_t));
  if(Format1 == NULLP){
    DU_LOG("\nERROR   -->  E2SM-KPM : Memory Allocation for Event Trigger Definition Foramt 1 Failed, %d", __LINE__);
    return RFAILED;
  }
  Format1->reportingPeriod = report_period;
  Event_Trigger_Definition->eventDefinition_formats.present = E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1;
  Event_Trigger_Definition->eventDefinition_formats.choice.eventDefinition_Format1 = Format1;

  xer_fprint(stderr,  &asn_DEF_E2SM_KPM_EventTriggerDefinition, Event_Trigger_Definition);
  uint8_t e2smbuffer[8192];
  size_t e2smbuffer_size = 8192;
  asn_enc_rval_t     encRetVal;
  encRetVal = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_EventTriggerDefinition, NULL, Event_Trigger_Definition, e2smbuffer, e2smbuffer_size);

  if(encRetVal.encoded == -1){
        DU_LOG("\nERROR   -->  E2SM-KPM : Failed to encode Event Trigger Defintion, %d", __LINE__);
        return RFAILED;
    }else{
      eventTrigDefinition->size = encRetVal.encoded;
      RIC_ALLOC(eventTrigDefinition->buf, encRetVal.encoded);
      memcpy(eventTrigDefinition->buf, e2smbuffer, encRetVal.encoded);
      return ROK;
    }  
}

uint8_t procKpmRicIndication(RICindicationMessage_t ricIndication){
  asn_dec_rval_t decRetVal;
  E2SM_KPM_IndicationMessage_t *indicationMsg = (E2SM_KPM_IndicationMessage_t*)calloc(1, sizeof(E2SM_KPM_IndicationMessage_t));
  decRetVal = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_IndicationMessage, (void **)&indicationMsg, ricIndication.buf, ricIndication.size);
  if(decRetVal.code != RC_OK){
      DU_LOG("Failed to decode element %d\n", decRetVal.consumed);
      ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, indicationMsg);
      return RFAILED;
  }
  if(indicationMsg->indicationMessage_formats.present == E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1){
    E2SM_KPM_IndicationMessage_Format1_t *indicationMsgFmt1 = indicationMsg->indicationMessage_formats.choice.indicationMessage_Format1;
    for(int i=0;i<indicationMsgFmt1->measInfoList->list.size;i++){
      if(indicationMsgFmt1->measInfoList->list.array[i]){
        if(indicationMsgFmt1->measInfoList->list.array[i]->measType.present == MeasurementType_PR_measName && \
         indicationMsgFmt1->measInfoList->list.array[i]->labelInfoList.list.array[0]->measLabel.noLabel){
          if(indicationMsgFmt1->measData.list.array[i]->measRecord.list.array[0]->present == MeasurementRecordItem_PR_integer){
            DU_LOG("\nCell Measurement \"%s\" = %ld",indicationMsgFmt1->measInfoList->list.array[i]->measType.choice.measName.buf, 
            indicationMsgFmt1->measData.list.array[i]->measRecord.list.array[0]->choice.integer);
          }
          else{
            DU_LOG("\nCell Measurement \"%s\" = %.2f",indicationMsgFmt1->measInfoList->list.array[i]->measType.choice.measName.buf, 
            indicationMsgFmt1->measData.list.array[i]->measRecord.list.array[0]->choice.real);
          }
         }
      }
    }
    return ROK;
  }else if(indicationMsg->indicationMessage_formats.present == E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2){
    E2SM_KPM_IndicationMessage_Format2_t *indicationMsgFmt2 = indicationMsg->indicationMessage_formats.choice.indicationMessage_Format2;
    for(int i=0;i<indicationMsgFmt2->measCondUEidList.list.size;i++){
      if(indicationMsgFmt2->measCondUEidList.list.array[i]){
        if(indicationMsgFmt2->measCondUEidList.list.array[i]->measType.present == MeasurementType_PR_measName && \
        indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID){
          if(indicationMsgFmt2->measData.list.array[0]->measRecord.list.array[0]->present == MeasurementRecordItem_PR_integer){
            DU_LOG("\nSlice {%d-%d%d%d} Measurement \"%s\" = %ld", 
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sST.buf[0],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[0],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[1],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[2],
            indicationMsgFmt2->measCondUEidList.list.array[i]->measType.choice.measName.buf, 
            indicationMsgFmt2->measData.list.array[i]->measRecord.list.array[0]->choice.integer);
          }
          else{
            DU_LOG("\nSlice {%d-%d%d%d} Measurement \"%s\" = %.2f", 
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sST.buf[0],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[0],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[1],
            indicationMsgFmt2->measCondUEidList.list.array[i]->matchingCond.list.array[0]->matchingCondChoice.choice.measLabel->sliceID->sD->buf[2],
            indicationMsgFmt2->measCondUEidList.list.array[i]->measType.choice.measName.buf, 
            indicationMsgFmt2->measData.list.array[i]->measRecord.list.array[0]->choice.real);
          }
        }
      }
    }
    return ROK;
  }
}


uint8_t fillKpmCellActionDefinition(RICactionDefinition_t *actionDefinition){
   uint8_t cellMeasName[][25] = {"DRB.UEThpDl", "RRU.PrbUsedDl", "RRU.PrbAvailDl", "RRU.PrbTotDl"}; // UE throughput, Avaliable PRB, Total PRB Usage
   int infoSize = 4;
   E2SM_KPM_ActionDefinition_t *actionDefini;
   actionDefini = (E2SM_KPM_ActionDefinition_t*)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
   MeasurementInfoItem_t *measInfoItem = (MeasurementInfoItem_t*)calloc(infoSize, sizeof(MeasurementInfoItem_t));
   LabelInfoItem_t *labelInfoItem = (LabelInfoItem_t*)calloc(infoSize, sizeof(LabelInfoItem_t));
   actionDefini->ric_Style_Type = 1;
   actionDefini->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
   actionDefini->actionDefinition_formats.choice.actionDefinition_Format1 = calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format1_t));
   actionDefini->actionDefinition_formats.choice.actionDefinition_Format1->granulPeriod = 1;
   for(int i=0;i<infoSize;i++){
      measInfoItem[i].measType.present = MeasurementType_PR_measName;
      measInfoItem[i].measType.choice.measName.size = strlen(cellMeasName[i]);
      measInfoItem[i].measType.choice.measName.buf = (uint8_t*)calloc(strlen(cellMeasName[i]), sizeof(uint8_t));
      strcpy(measInfoItem[i].measType.choice.measName.buf, cellMeasName[i]);
      labelInfoItem[i].measLabel.noLabel = (long*)calloc(1, sizeof(long));
      *labelInfoItem[i].measLabel.noLabel = MeasurementLabel__noLabel_true;
      ASN_SEQUENCE_ADD(&measInfoItem[i].labelInfoList.list, &labelInfoItem[i]);
      ASN_SEQUENCE_ADD(&actionDefini->actionDefinition_formats.choice.actionDefinition_Format1->measInfoList.list, &measInfoItem[i]);
   }

   xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, actionDefini);

   uint8_t e2smbuffer[8192];
   size_t e2smbuffer_size = 8192;
   asn_enc_rval_t     encRetVal;
   encRetVal = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, actionDefini, e2smbuffer, e2smbuffer_size);

   if(encRetVal.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Failed to encode Action Defintion, %d", __LINE__);
        return RFAILED;
    }else{
      actionDefinition->size = encRetVal.encoded;
      RIC_ALLOC(actionDefinition->buf, encRetVal.encoded);
      memcpy(actionDefinition->buf, e2smbuffer, encRetVal.encoded);
      return ROK;
    }    
}

uint8_t fillKpmSliceActionDefinition(RICactionDefinition_t *actionDefinition){
  uint8_t sliceMeasName[][25] = {"DRB.UEThpDl.SNSSAI", "RRU.PrbUsedDl.SNSSAI"}; // UE throughput, Used PRB
  int infoSize = 2;
  E2SM_KPM_ActionDefinition_t *actionDefini;
    actionDefini = (E2SM_KPM_ActionDefinition_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
    E2SM_KPM_ActionDefinition_Format3_t *actionDefiniFmt3;
    actionDefiniFmt3 = (E2SM_KPM_ActionDefinition_Format3_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format3_t));
    MeasurementCondItem_t *measCondItem = (MeasurementCondItem_t*)calloc(infoSize, sizeof(MeasurementCondItem_t));
    MeasurementLabel_t *measLabel = (MeasurementLabel_t*)calloc(infoSize, sizeof(MeasurementLabel_t));
    MatchingCondItem_t *matchingCondItem = (MatchingCondItem_t*)calloc(infoSize, sizeof(MatchingCondItem_t));

    actionDefini->ric_Style_Type = 3;
    actionDefini->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3;
    actionDefini->actionDefinition_formats.choice.actionDefinition_Format3 = actionDefiniFmt3;
    actionDefiniFmt3->granulPeriod = 1;

    for(int i=0;i<infoSize;i++){
        measCondItem[i].measType.present = MeasurementType_PR_measName;
        measCondItem[i].measType.choice.measName.size = strlen(sliceMeasName[i]);
        measCondItem[i].measType.choice.measName.buf = (uint8_t*)calloc(strlen(sliceMeasName[i]), sizeof(uint8_t));
        memcpy(measCondItem[i].measType.choice.measName.buf, sliceMeasName[i], strlen(sliceMeasName[i]));
        
        matchingCondItem[i].matchingCondChoice.present = MatchingCondItem_Choice_PR_measLabel;
        matchingCondItem[i].matchingCondChoice.choice.measLabel = &measLabel[i];
        measLabel[i].noLabel = (long*)calloc(1, sizeof(long));
        *measLabel[i].noLabel = MeasurementLabel__noLabel_true;
        ASN_SEQUENCE_ADD(&measCondItem[i].matchingCond.list, &matchingCondItem[i]);
        ASN_SEQUENCE_ADD(&actionDefiniFmt3->measCondList.list, &measCondItem[i]);
    }

   xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, actionDefini);

   uint8_t e2smbuffer[8192];
   size_t e2smbuffer_size = 8192;
   asn_enc_rval_t     encRetVal;
   encRetVal = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, actionDefini, e2smbuffer, e2smbuffer_size);

   if(encRetVal.encoded == -1){
        printf("\nERROR   -->  E2SM-KPM : Failed to encode Action Defintion, %d", __LINE__);
        return RFAILED;
    }else{
      actionDefinition->size = encRetVal.encoded;
      RIC_ALLOC(actionDefinition->buf, encRetVal.encoded);
      memcpy(actionDefinition->buf, e2smbuffer, encRetVal.encoded);
      return ROK;
    }    
}
