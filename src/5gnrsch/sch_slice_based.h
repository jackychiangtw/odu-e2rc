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

typedef struct schSliceBasedCellCb
{
   CmLListCp     ueToBeScheduled;                   /*!< Linked list to store UEs pending to be scheduled */
   CmLListCp     sliceCbList;                       /* Linked list to store slice control block with priority, the last node */
}SchSliceBasedCellCb;

typedef struct schSliceBasedLcCb
{
   /* TODO: For Multiple RRMPolicies, Make DedicatedLcInfo as array/Double Pointer 
    * and have separate DedLCInfo for each RRMPolcyMemberList */
   /* Dedicated LC List will be allocated, if any available */
   CmLListCp dedLcList;	/*Contain LCInfo per RRMPolicy*/
   CmLListCp defLcList; /*Linklist of LC assoc with Default S-NSSAI(s)*/
   /* SharedPRB number can be used by any LC.
    * Need to calculate in every Slot based on PRB availability*/
   uint16_t sharedNumPrb;
}SchSliceBasedLcCb;

typedef struct schSliceBasedHqProcCb
{
   SchSliceBasedLcCb lcCb; 
}SchSliceBasedHqProcCb;

typedef struct schSliceBasedHqCb
{
   CmLListCp  ulRetxHqList;
   CmLListCp  dlRetxHqList;
}SchSliceBasedHqCb;

typedef struct schSliceBasedUeCb
{
   SchSliceBasedHqCb   hqRetxCb;
   bool isTxPayloadLenAdded;
}SchSliceBasedUeCb;

typedef struct schSliceBasedSliceCb
{
   Snssai  snssai;
   CmLListCp lcInfoList[MAX_NUM_UE];  /* Linked list to store logical channel Info of each UE which is associated with this slice */
   uint16_t dedicatedPrb;
   uint16_t prioritizedPrb;
   uint16_t sharedPrb;
   uint16_t allocatedPrb; /* Store the allocated PRB after intra-slice scheduling per slice */
   SchRrmPolicyRatio rrmPolicyRatioInfo;
}SchSliceBasedSliceCb;

uint8_t schSliceBasedAddUeToSchedule(SchCellCb *cellCb, uint16_t ueIdToAdd);
void SchSliceBasedSliceCfgReq(SchCellCb *cellCb);
void SchSliceBasedSliceRecfgReq(SchCellCb *cellCb);
uint8_t schSliceBasedFillLcInfoToSliceCb(CmLListCp *sliceCbList, SchUeCb *ueCb);
uint8_t schSliceBasedUpdateLcListReqBo(CmLListCp *lcInfoList, SchUeCb *ueCb);
void schSliceBasedPrbAllocUsingRRMPolicy(CmLListCp *lcInfoList, uint16_t mcsIdx, uint8_t numSymbols, uint16_t *availablePrb, \
                                      bool *isTxPayloadLenAdded, bool *srRcvd);
void schSliceBasedUpdateGrantSizeForBoRpt(CmLListCp *lcLL, DlMsgSchInfo *dlMsgAlloc,\
                                    BsrInfo *bsrInfo, uint32_t *accumalatedBOSize, bool isDedicated);
/* Once the scheduler supports multi-UEs per TTI scheduling, the parameter 'ueId' should be deleted */
bool schSliceBasedDlScheduling(SchCellCb *cell, SlotTimingInfo currTime, uint8_t ueId, bool isRetx, SchDlHqProcCb **hqP);
uint8_t schSliceBasedDlIntraSliceScheduling(SchCellCb *cellCb, SlotTimingInfo pdcchTime, uint8_t pdschNumSymbols, \
                                             uint16_t maxFreePRB, SchSliceBasedSliceCb *sliceCb, uint8_t ueId);
uint8_t schSliceBasedDlFinalScheduling(SchCellCb *cellCb, SlotTimingInfo pdschTime, SlotTimingInfo pdcchTime, \
                  SlotTimingInfo pucchTime, uint8_t pdschStartSymbol, uint8_t pdschNumSymbols, uint8_t ueId, \
                  bool isRetx, SchDlHqProcCb **hqP, uint16_t remainingPrb, uint16_t startPrb);
void schSliceBasedAllApisInit(SchAllApis *allSliceBasedApi);

/**********************************************************************
    End of file
 *********************************************************************/