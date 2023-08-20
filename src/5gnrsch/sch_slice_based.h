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

// #define SCH_MULTI_THREAD /* Enable the multi-thread intra-slice scheduling feature */
#define NUM_SLICE 3
// #define SLICE_BASED_DEBUG_LOG /* Enable the debug log */
#define BILLION_NUM  1000000000.0

typedef enum
{
   FLAT,
   HIERARCHY
}SchAlgoMethod;

typedef enum
{
   RR, /* Round Robin */
   WFQ /* Weight Fair Queue */
}SchAlgorithm;

/*Following structures to keep record and estimations of PRB allocated for each
 * LC taking into consideration the RRM policies*/
typedef struct schSliceBasedLcInfo
{
   uint8_t  lcId;     /*LCID for which BO are getting recorded*/
   SchUeCb *ueCb;    /* To store which UE this LC belongs to */
   uint16_t priorLevel; /* Priority Level which is associated with this LC */
   float_t weight; /*  Weight (0 ~ 1) which is used for WFQ algorithm */
   uint32_t reqBO;    /*Size of the BO requested/to be allocated for this LC*/
   uint32_t allocBO;  /*TBS/BO Size which is actually allocated*/
   uint8_t  allocPRB; /*PRB count which is allocated based on RRM policy/FreePRB*/
}SchSliceBasedLcInfo;

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
   float_t prbWeight; /*  prbWeight (0 ~ 1) is used for calculate the number of PRB within this TTI */
   float_t weight; /*  Weight (0 ~ 1) which is used for WFQ algorithm */
   bool isTxPayloadLenAdded;
   bool isDlMsgPending; /*JOJO: Flag for checking if there is DL data for UE.*/
   bool isDlMsgScheduled; /*JOJO: Flag for checking if DL data for UE is scheduled.*/
   bool isUlGrantPending; /*JOJO: Flag for checking if there is UL data for UE.*/
   bool isUlGrantScheduled; /*JOJO: Flag for checking if UL data for UE is scheduled.*/
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
   SchAlgoMethod algoMethod; /* Specify the scheduling method (0: flat, 1: hierarchy) */
   SchAlgorithm algorithm; /* Specify the scheduling algorithm (0: Round Robin, 1: Weight Fair Queue) */
   void (*schedulingAlgorithmforLc)(CmLListCp *lcInfoList, uint8_t numSymbols, uint16_t *availablePrb, \
                                       bool *isTxPayloadLenAdded, bool *srRcvd);
}SchSliceBasedSliceCb;

typedef struct schSliceBasedDlThreadArg
{
   uint8_t *triggerFlag;
   SchCellCb *cell;
   SlotTimingInfo *pdcchTime;
   uint8_t *pdschNumSymbols;
   uint16_t *totalRemainingPrb;
   uint16_t *maxFreePRB;
   SchSliceBasedSliceCb *sliceCb;
   CmLListCp *ueDlNewTransmission;
}SchSliceBasedDlThreadArg;

typedef struct schSliceBasedUlThreadArg
{
   SchCellCb *cell;
   SlotTimingInfo puschTime;
   uint8_t puschNumSymbols;
   uint16_t *totalRemainingPrb;
   uint16_t maxFreePRB;
   SchSliceBasedSliceCb *sliceCb;
   uint8_t ueId;
}SchSliceBasedUlThreadArg;

typedef struct schSliceBasedCellCb
{
   CmLListCp     ueToBeScheduled;                   /*!< Linked list to store UEs pending to be scheduled */
   CmLListCp     sliceCbList;                       /* Linked list to store slice control block with priority, the last node */

   /* For thesis experiment */
   bool isTimerStart;
   uint16_t slot_ind_count;
   uint16_t timer_sec;

   /* For thread creating */
   SchSliceBasedDlThreadArg *threadArg[NUM_SLICE];
   pthread_t intraSliceThread[NUM_SLICE];
   
}SchSliceBasedCellCb;

uint8_t schSliceBasedAddUeToSchedule(SchCellCb *cellCb, uint16_t ueIdToAdd);
void SchSliceBasedSliceCfgReq(SchCellCb *cellCb);
void SchSliceBasedSliceRecfgReq(SchCellCb *cellCb);
uint8_t schSliceBasedFillLcInfoToSliceCb(CmLListCp *sliceCbList, SchUeCb *ueCb);
uint16_t schSliceBasedCalculatePriorLevel(uint16_t fiveQi);
void schSliceBasedSortLcByPriorLevel(CmLListCp *lcInfoList, float_t totalPriorLevel);
void schSliceBasedSortUeByWeight(SchCellCb *cellCb, CmLListCp *ueList, float_t totalWeight);
uint8_t schSliceBasedUpdateLcListReqBo(CmLListCp *lcInfoList, SchUeCb *ueCb, Direction dir);
void schSliceBasedUpdateGrantSizeForBoRpt(CmLListCp *lcLL, DlMsgSchInfo *dlMsgAlloc,\
                                    BsrInfo *bsrInfo, uint32_t *accumalatedBOSize, bool isDedicated);
uint32_t schSliceBasedcalculateEstimateTBSize(uint32_t reqBO, uint16_t mcsIdx, uint8_t numSymbols,\
                                   uint16_t maxPRB, uint16_t *estPrb);                                  
void schSliceBasedAllApisInit(SchAllApis *allSliceBasedApi);

/* DL Slice-Based Function */
bool schSliceBasedDlScheduling(SchCellCb *cell, SlotTimingInfo currTime, uint8_t ueId, bool isRetx, SchDlHqProcCb **hqP);
uint8_t schSliceBasedDlIntraSliceScheduling(SchCellCb *cellCb, SlotTimingInfo pdcchTime, uint8_t pdschNumSymbols, \
                                            uint16_t *totalRemainingPrb, uint16_t maxFreePRB, SchSliceBasedSliceCb *sliceCb, \
                                            CmLListCp *ueDlNewTransmission);
void *schSliceBasedDlIntraSliceThreadScheduling(void *threadArg);
uint8_t schSliceBasedDlFinalScheduling(SchCellCb *cellCb, SlotTimingInfo pdschTime, SlotTimingInfo pdcchTime, \
                  SlotTimingInfo pucchTime, uint8_t pdschStartSymbol, uint8_t pdschNumSymbols, CmLListCp *ueDlNewTransmission, \
                  bool isRetx, SchDlHqProcCb **ueNewHarqList, uint16_t remainingPrb, uint16_t startPrb);

/* UL Slice-Based Function */
/* Once the scheduler supports multi-UEs per TTI scheduling, the parameter 'ueId' should be deleted */
bool schSliceBasedUlScheduling(SchCellCb *cell, SlotTimingInfo currTime, uint8_t ueId, bool isRetx, SchUlHqProcCb **hqP);
uint8_t schSliceBasedUlIntraSliceScheduling(SchCellCb *cellCb, SlotTimingInfo puschTime, uint8_t puschNumSymbols, \
                                            uint16_t *totalRemainingPrb, uint16_t maxFreePRB, SchSliceBasedSliceCb *sliceCb, uint8_t ueId);
void *schSliceBasedUlIntraSliceThreadScheduling(void *threadArg);
uint8_t schSliceBasedUlFinalScheduling(SchCellCb *cellCb, SlotTimingInfo puschTime, SlotTimingInfo dciTime, \
                  uint8_t puschStartSymbol, uint8_t puschNumSymbols, uint8_t ueId, \
                  bool isRetx, SchUlHqProcCb **hqP, uint16_t remainingPrb, uint16_t startPrb);

/* Scheduling Algorithm */
uint8_t schSliceBasedRoundRobinAlgo(SchCellCb *cellCb, CmLListCp *ueList, CmLListCp *lcInfoList, uint8_t numSymbols, \
                                 uint16_t *availablePrb, SchAlgoMethod algoMethod, bool *srRcvd);
uint8_t schSliceBasedWeightedFairQueueAlgo(SchCellCb *cellCb, CmLListCp *ueList, CmLListCp *lcInfoList, uint8_t numSymbols, \
                                 uint16_t *availablePrb, SchAlgoMethod algoMethod, bool *srRcvd);

/* Scheduling Algorithm for Logical Channel Level */
void schSliceBasedRoundRobinAlgoforLc(CmLListCp *lcInfoList, uint8_t numSymbols, uint16_t *availablePrb, \
                                       bool *isTxPayloadLenAdded, bool *srRcvd);
void schSliceBasedWeightedFairQueueAlgoforLc(CmLListCp *lcInfoList, uint8_t numSymbols, uint16_t *availablePrb, \
                                       bool *isTxPayloadLenAdded, bool *srRcvd);
void schSliceBasedPrbAllocUsingRRMPolicy(CmLListCp *lcInfoList, uint16_t mcsIdx, uint8_t numSymbols, uint16_t *availablePrb, \
                                      bool *isTxPayloadLenAdded, bool *srRcvd);

/* For thesis experiment */
void setRrmPolicyWithTimer(SchCellCb *cell); /* For experiment 1.1 */
/**********************************************************************
    End of file
 *********************************************************************/