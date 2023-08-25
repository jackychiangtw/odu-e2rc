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

/* This file contains all E2AP message handler related functionality */

//Include Libraries
# include "E2SM-KPM-RANfunction-Description.h"

# include "E2SM-KPM-EventTriggerDefinition.h"
# include "E2SM-KPM-EventTriggerDefinition-Format1.h"

# include "E2SM-KPM-ActionDefinition.h"
# include "E2SM-KPM-ActionDefinition-Format1.h"
# include "E2SM-KPM-ActionDefinition-Format2.h"
# include "E2SM-KPM-ActionDefinition-Format3.h"
# include "E2SM-KPM-ActionDefinition-Format4.h"
# include "E2SM-KPM-ActionDefinition-Format5.h"


# include "E2SM-KPM-IndicationHeader.h"
# include "E2SM-KPM-IndicationHeader-Format1.h"
# include "E2SM-KPM-IndicationMessage.h"
# include "E2SM-KPM-IndicationMessage-Format1.h"
# include "E2SM-KPM-IndicationMessage-Format2.h"
# include "E2SM-KPM-IndicationMessage-Format3.h"

# include "MeasurementInfoItem.h"
# include "MeasurementInfoList.h"
# include "MeasurementTypeName.h"
# include "MeasurementTypeID.h"
# include "MeasurementCondItem.h"
# include "MeasurementCondList.h"
# include "MeasurementTypeID.h"
# include "MeasurementLabel.h"

# include "MatchingCondList.h"
# include "MatchingCondItem.h"
# include "MatchingUEidList.h"
# include "MatchingUeCondPerSubList.h"
# include "MatchingUeCondPerSubItem.h"
# include "MatchingUEidPerSubItem.h"

# include "LabelInfoItem.h"
# include "CGI.h"
# include "PLMNIdentity.h"
# include "NRCellIdentity.h"
# include "EUTRACellIdentity.h"
# include "NR-CGI.h"
# include "EUTRA-CGI.h"

# include "TestCondInfo.h"
# include "TestCond-Value.h"
# include "GranularityPeriod.h"
# include "UEID.h"

# include "GlobalGNB-ID.h"
# include "GlobalNgENB-ID.h"
# include "GlobalNGRANNodeID.h"
# include "MatchingUEidItem.h"
# include "MeasurementCondUEidItem.h"
# include "MeasurementDataItem.h"
# include "MeasurementInfo-Action-Item.h"
# include "MeasurementRecordItem.h"
# include "RIC-EventTriggerStyle-Item.h"
# include "RIC-ReportStyle-Item.h"
# include "S-NSSAI.h"
# include "UEID-GNB-CU-CP-E1AP-ID-Item.h"
# include "UEID-GNB-CU-CP-E1AP-ID-List.h"
# include "UEID-GNB-CU-CP-F1AP-ID-Item.h"
# include "UEID-GNB-CU-F1AP-ID-List.h"
# include "UEID-GNB-CU-UP.h"
# include "UEID-GNB-DU.h"
# include "UEID-GNB.h"
# include "UEMeasurementReportItem.h"

uint8_t procKpmRanFunDescrpition(RANfunctionDefinition_t ranFuncDefinition);
uint8_t fillKpmEventTrigDefinition(RICeventTriggerDefinition_t *eventTrigDefinition, unsigned long report_period);
uint8_t fillKpmActionDefinition(RICactionDefinition_t *actionDefinition);


/**********************************************************************
         End of file
**********************************************************************/
