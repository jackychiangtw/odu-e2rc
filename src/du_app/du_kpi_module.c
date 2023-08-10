#include "du_kpi_module.h"

/*******************************************************************
 *
 * @brief Initialize the KPI Module
 *
 * @details
 *
 *    Function : kpiModuleInit
 *
 *    Functionality: Initialize the parameters in the KPI module
 *
 * @return void
 *
 ******************************************************************/

void kpiModuleInit(){
    kpmSlicePmDb.numOfSlice = MAX_SIZE_OF_SLICE;
    indexOfSliceMacPm = 0;
    indexOfSliceRlcPm = 0;

    indexOfCellMacPm = 0;
    indexOfCellRlcPm = 0;
    indicationRlcCellCount = 0;
    indicationRlcSliceCount = 0;
    indicationMacCellCount= 0;
    indicationMacSliceCount = 0;

    smoRlcSliceCount = 0;
    smoMacSliceCount = 0;
}

/*******************************************************************
 *
 * @brief Store the Cell Metrics by RLC
 *
 * @details
 *
 *    Function : kpmStoreCellRlcMetric
 *
 *    Functionality: Store the Cell Metrics by RLC
 *
 * @param[in] cellMetricList, CellPmList* cell metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreCellRlcMetric(CellPmList* cellMetricList){
    if(cellMetricList != NULL){
        if(cellMetricList->numUe>0){
            printf("\nINFO   -->  E2SM-KPM : Support sending UE Average Throughput to xApp");
            if(indexOfCellRlcPm<SIZE_OF_RLCDB){
                indexOfCellRlcPm++;
            }
            else{
                indexOfCellRlcPm=0;
            }
            kpmCellPmDb.eachRlcPm[indexOfCellRlcPm].ThpDl = cellMetricList->ueRecord->ThpDl;
        }
    }
    if(kpmCellIndicationEnable){
        indicationRlcCellCount++;
    }
}

/*******************************************************************
 *
 * @brief Store the SliceMetrics by RLC
 *
 * @details
 *
 *    Function : kpmStoreSliceRlcMetric
 *
 *    Functionality: Store the Slice Metrics by RLC
 *
 * @param[in] sliceMetricList, SlicePmList* slice metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList){
    if(sliceMetricList){
        indexOfSliceRlcPm++;
        if(indexOfSliceRlcPm == SIZE_OF_RLCDB)
            indexOfSliceRlcPm = 0;

        for(int i=0;i<sliceMetricList->numSlice;i++){
                kpmSlicePmDb.eachRlcPm[indexOfSliceRlcPm].sliceRecord[i].ThpDl = (int)sliceMetricList->sliceRecord[i].ThpDl;
                kpmSlicePmDb.snssai[i].sst = (char)sliceMetricList->sliceRecord[i].networkSliceIdentifier.sst;
                kpmSlicePmDb.snssai[i].sd[0] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 100 ) % 10;
                kpmSlicePmDb.snssai[i].sd[1] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 10) % 10;
                kpmSlicePmDb.snssai[i].sd[2] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd ) % 10; 
        }
        kpmSlicePmDb.eachRlcPm[indexOfSliceRlcPm].numOfSlice = sliceMetricList->numSlice;
        kpmSlicePmDb.numOfSlice = sliceMetricList->numSlice;
    }   

    if(kpmSliceIndicationEnable){
        indicationRlcSliceCount++;
    }

    if(smoRlcSliceCount<2 * SMO_REPORT_PERIOD)
        smoRlcSliceCount++;
    else{
        calcSmoMetric();
        #ifdef O1_ENABLE
            SliceMetricList *sliceStatsList = (SliceMetricList*)calloc(1, sizeof(SliceMetricList));
            sliceStatsList->nRecords = kpmSlicePmDb.numOfSlice;
            sliceStatsList->sliceRecord = (SliceMetricRecord*)calloc(sliceStatsList->nRecords, sizeof(SliceMetricRecord));
            for(int i = 0; i < kpmSlicePmDb.numOfSlice; i++)
            {
                sliceStatsList->sliceRecord[i].networkSliceIdentifier.sd = 10000 * kpmSlicePmDb.snssai[i].sd[0] + 100 * kpmSlicePmDb.snssai[i].sd[1] + (uint32_t)kpmSlicePmDb.snssai[i].sd[2];
                sliceStatsList->sliceRecord[i].networkSliceIdentifier.sst = kpmSlicePmDb.snssai[i].sst;
                sliceStatsList->sliceRecord[i].DRB_UEThpDl_SNSSAI = kpmSlicePmDb.smo_avgThpDl[i];
                sliceStatsList->sliceRecord[i].DRB_PrbUsedDl_SNSSAI = kpmSlicePmDb.smo_avgUsedPrb[i];
                printf("\nJacky   -->  SMO : slice %d, throughput = %.2f, PRB = %.2f ", i, kpmSlicePmDb.smo_avgThpDl[i], kpmSlicePmDb.smo_avgUsedPrb[i]);
            }
            sendSliceMetric(sliceStatsList);
            free(sliceStatsList->sliceRecord);
            free(sliceStatsList);
        #endif
    }   
}

/*******************************************************************
 *
 * @brief Store the Metric by MAC
 *
 * @details
 *
 *    Function : kpmStoreMacMetric
 *
 *    Functionality: Store the Metrics by MAC
 *
 * @param[in] macPrbPm, MacPrbPm* metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreMacMetric(MacPrbPm* macPrbPm){ // Enter this function per millisecond. 
    if(macPrbPm != NULL){
        if(indexOfCellMacPm<SIZE_OF_MACDB)
            indexOfCellMacPm++;
        else
            indexOfCellMacPm = 0;
        kpmCellPmDb.eachMacPm[indexOfCellMacPm].usedPrb = macPrbPm->usedPrb;
        kpmCellPmDb.eachMacPm[indexOfCellMacPm].totalPrb = macPrbPm->totalPrb;
        if(indexOfSliceMacPm<SIZE_OF_MACDB)
            indexOfSliceMacPm++;
        else
            indexOfSliceMacPm = 0;
        
        for(int i=0;i<macPrbPm->sliceNum;i++){
            kpmSlicePmDb.eachMacPm[indexOfSliceMacPm].numOfSlice = macPrbPm->sliceNum;
            if(macPrbPm->listOfSlicePm){
                kpmSlicePmDb.eachMacPm[indexOfSliceMacPm].sliceRecord[i].usedPrb = macPrbPm->listOfSlicePm[i].usedPrb;
            }
        }
    }
    else{
        printf("\nERROR   -->  E2SM-KPM : Empty Input");
    }

    if(kpmCellIndicationEnable){
        indicationMacCellCount++;
    }
    if(kpmSliceIndicationEnable){
        indicationMacSliceCount++;
    }
    smoMacSliceCount++;
    return;
}

/*******************************************************************
 *
 * @brief Get the average value of cell metrics
 *
 * @details
 *
 *    Function : kpmCalcCellMetric
 *
 *    Functionality: Get the average value of cell metrics
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t kpmCalcCellMetric(){
    long rlcIndex = indexOfCellRlcPm - 1;
    long macIndex = indexOfCellMacPm - 1;
    uint64_t usedPrbSum = 0, totalPrbSum = 0, thpSum = 0;

    for(int i=0;i<indicationMacCellCount;i++){
        usedPrbSum += kpmCellPmDb.eachMacPm[macIndex].usedPrb;
        totalPrbSum += kpmCellPmDb.eachMacPm[macIndex].totalPrb;
        if(macIndex>0)
            macIndex--;
        else{
            macIndex = SIZE_OF_MACDB - 1;
        }
    }

    for(int i=0;i<indicationRlcCellCount;i++){
        thpSum += kpmCellPmDb.eachRlcPm[rlcIndex].ThpDl;
        if(rlcIndex>0)
            rlcIndex--;
        else{
            rlcIndex = SIZE_OF_RLCDB - 1;
        }
    }

    kpmCellPmDb.avgThpDl = indicationRlcCellCount ? thpSum / indicationRlcCellCount : 0;
    kpmCellPmDb.avgUsedPrb = indicationMacCellCount ? usedPrbSum / indicationMacCellCount : 0;
    kpmCellPmDb.avgTotalPrb = indicationMacCellCount ? totalPrbSum / indicationMacCellCount : 0;
    kpmCellPmDb.avgUsagePrb = indicationMacCellCount ? (double)100.0 * kpmCellPmDb.avgUsedPrb / kpmCellPmDb.avgTotalPrb  : 0;

    indicationMacCellCount = 0;
    indicationRlcCellCount = 0;

    return ROK;    
}

/*******************************************************************
 *
 * @brief Get the average value of slice metrics
 *
 * @details
 *
 *    Function : kpmCalcSliceMetric
 *
 *    Functionality: Get the average value of slice metrics
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t kpmCalcSliceMetric(){
    long rlcIndex = indexOfSliceRlcPm;
    long macIndex = indexOfSliceMacPm;
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    for(int i=0;i<indicationMacSliceCount;i++){
        for(int j=0;j<kpmSlicePmDb.numOfSlice;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[j].usedPrb;
        }
        if(macIndex>0)
            macIndex--;
        else{
            macIndex = SIZE_OF_MACDB - 1;
        }
    }

    for(int i=0;i<indicationRlcSliceCount;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[j].ThpDl;
        }
        if(rlcIndex>0)
            rlcIndex--;
        else{
            rlcIndex = SIZE_OF_RLCDB - 1;
        }
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){
        kpmSlicePmDb.avgUsedPrb[i] = indicationMacSliceCount ? usedPrbSum[i] / indicationMacSliceCount : 0;
        kpmSlicePmDb.avgThpDl[i] = indicationRlcSliceCount ? thpSum[i] / indicationRlcSliceCount : 0;
        DU_LOG("\nJacky --> KPM: SNSSAI(sst:%d,sd [%d, %d, %d]), DL PRBUsed : %d, DLtpt : %d", \
            kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1], \
            kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.avgUsedPrb[i], kpmSlicePmDb.avgThpDl[i]);
    }
    indicationMacSliceCount = 0;
    indicationRlcSliceCount = 0;
    return 0;
}

/*******************************************************************
 *
 * @brief Get the average value for O1 Module
 *
 * @details
 *
 *    Function : calcSmoMetric
 *
 *    Functionality: Get the average value for O1 Module
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t calcSmoMetric(){
    long rlcIndex = indexOfSliceRlcPm;
    long macIndex = indexOfSliceMacPm;
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    smoMacSliceCount++;

    for(int i=0;i<smoMacSliceCount;i++){
        for(int j=0;j<kpmSlicePmDb.numOfSlice;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[j].usedPrb;   
        }
        // DU_LOG("\nJacky --> SMO: # %d tpt = %d, %d, %d", macIndex, kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[0].usedPrb, kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[1].usedPrb,  kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[2].usedPrb);

        if(macIndex>0)
            macIndex--;
        else{
            macIndex = SIZE_OF_MACDB - 1;
        }
    }

    for(int i=0;i<smoRlcSliceCount;i++){
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[j].ThpDl;
        }
        // DU_LOG("\nJacky --> SMO: # %d tpt = %d, %d, %d", rlcIndex, kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[0].ThpDl, kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[1].ThpDl,  kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[2].ThpDl);
        if(rlcIndex>0)
            rlcIndex--;
        else{
            rlcIndex = SIZE_OF_RLCDB - 1;
        }
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){
        kpmSlicePmDb.smo_avgUsedPrb[i] = smoMacSliceCount ? (uint64_t)usedPrbSum[i] / smoMacSliceCount : 0;
        kpmSlicePmDb.smo_avgThpDl[i] = smoRlcSliceCount ? (uint64_t)thpSum[i] / smoRlcSliceCount : 0;
        // DU_LOG("\nJacky --> SMO: SNSSAI(sst:%d,sd [%d, %d, %d]), DL PRBUsed : %d, DLtpt : %d", \
            kpmSlicePmDb.snssai[i].sst, kpmSlicePmDb.snssai[i].sd[0], kpmSlicePmDb.snssai[i].sd[1], \
            kpmSlicePmDb.snssai[i].sd[2], kpmSlicePmDb.smo_avgUsedPrb[i], kpmSlicePmDb.smo_avgThpDl[i]);
    }
    smoRlcSliceCount = 0;
    smoMacSliceCount = 0;
    return 0;
}
