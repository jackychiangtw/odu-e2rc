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
 * @param[in] cellMetricList, CellPmList* cell RLC metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreCellRlcMetric(CellPmList* cellMetricList){
    if(cellMetricList != NULL){
        if(cellMetricList->numUe>0){
            printf("\nINFO   -->  E2SM-KPM : Support sending UE Average Throughput to xApp");
            indexOfCellRlcPm = (indexOfCellRlcPm + 1 ) % SIZE_OF_RLCDB; // Counting the index, prevent out of DB size
            kpmCellPmDb.eachRlcPm[indexOfCellRlcPm].ThpDl = cellMetricList->ueRecord->ThpDl; // Fills the Cell throughput in DB
        }
    }
    if(kpmCellIndicationEnable){ // Counting the number of performace metrics in this interval of sending Indication for cell metrics
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
 * @param[in] sliceMetricList, SlicePmList* slice RLC metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreSliceRlcMetric(SlicePmList* sliceMetricList){
    if(sliceMetricList){
        indexOfCellRlcPm = (indexOfCellRlcPm + 1 ) % SIZE_OF_RLCDB; // Counting the index, prevent out of DB size

        for(int i=0;i<sliceMetricList->numSlice;i++){ // Fills the Slice ID info
            kpmSlicePmDb.eachRlcPm[indexOfSliceRlcPm].sliceRecord[i].ThpDl = (int)sliceMetricList->sliceRecord[i].ThpDl;
            kpmSlicePmDb.snssai[i].sst = (char)sliceMetricList->sliceRecord[i].networkSliceIdentifier.sst;
            kpmSlicePmDb.snssai[i].sd[0] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 100 ) % 10;
            kpmSlicePmDb.snssai[i].sd[1] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd / 10) % 10;
            kpmSlicePmDb.snssai[i].sd[2] = (sliceMetricList->sliceRecord[i].networkSliceIdentifier.sd ) % 10; 
        }
        kpmSlicePmDb.eachRlcPm[indexOfSliceRlcPm].numOfSlice = sliceMetricList->numSlice;
        kpmSlicePmDb.numOfSlice = sliceMetricList->numSlice;
    }   

    if(kpmSliceIndicationEnable){ // Counting the number of performace metrics in this interval of sending Indication for slices metrics
        indicationRlcSliceCount++;
    }

    if(smoRlcSliceCount < PHY_STUB_RATIO * SMO_REPORT_PERIOD)  // Send the slice PM to SMO through O1
        smoRlcSliceCount++;
    else{
        smoRlcSliceCount++;
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
 * @param[in] macPrbPm, MacPrbPm* PRB metrics
 * @return void
 *
 ******************************************************************/

void kpmStoreMacMetric(MacPrbPm* macPrbPm){ // Enter this function per TTI. 
    if(macPrbPm != NULL){
        indexOfCellMacPm = (indexOfCellMacPm + 1 ) % SIZE_OF_MACDB; // Counting the index, prevent out of DB size
        indexOfSliceMacPm = (indexOfSliceMacPm + 1 ) % SIZE_OF_MACDB;
        kpmCellPmDb.eachMacPm[indexOfCellMacPm].usedPrb = macPrbPm->usedPrb; // Fills the PRB infos in Cell DB
        kpmCellPmDb.eachMacPm[indexOfCellMacPm].totalPrb = macPrbPm->totalPrb;
        
        for(int i=0;i<macPrbPm->sliceNum;i++){ // Fills the PRB infos in Slice DB
            kpmSlicePmDb.eachMacPm[indexOfSliceMacPm].numOfSlice = macPrbPm->sliceNum;
            if(macPrbPm->listOfSlicePm){
                kpmSlicePmDb.eachMacPm[indexOfSliceMacPm].sliceRecord[i].usedPrb = macPrbPm->listOfSlicePm[i].usedPrb;
            }
        }
    }
    else{
        printf("\nERROR   -->  E2SM-KPM : Empty Input");
    }

    if(kpmCellIndicationEnable){ // Counting the number of performace metrics in this interval of sending Indication for cell metrics
        indicationMacCellCount++;
    }
    if(kpmSliceIndicationEnable){ // Counting the number of performace metrics in this interval of sending Indication for cell metrics
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
    long rlcIndex = (indexOfCellRlcPm - 1) % SIZE_OF_RLCDB; // The index of first item in this internal
    long macIndex = (indexOfCellMacPm - 1) % SIZE_OF_MACDB; 
    uint64_t usedPrbSum = 0, totalPrbSum = 0, thpSum = 0;

    for(int i=0;i<indicationMacCellCount;i++){ // Query the data in Cell MAC DB
        usedPrbSum += kpmCellPmDb.eachMacPm[macIndex].usedPrb;
        totalPrbSum += kpmCellPmDb.eachMacPm[macIndex].totalPrb;
        macIndex = (macIndex - 1) % SIZE_OF_MACDB;
    }

    for(int i=0;i<indicationRlcCellCount;i++){ // Query the data in Slice RLC DB
        thpSum += kpmCellPmDb.eachRlcPm[rlcIndex].ThpDl;
        rlcIndex = (rlcIndex - 1) % SIZE_OF_RLCDB;
    }

    kpmCellPmDb.avgThpDl = indicationRlcCellCount ? thpSum / indicationRlcCellCount : 0; // Get avg value
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
    long rlcIndex = (indexOfSliceRlcPm - 1) % SIZE_OF_RLCDB; // The index of first item in this internal
    long macIndex = (indexOfSliceMacPm - 1) % SIZE_OF_MACDB;
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    for(int i=0;i<indicationMacSliceCount;i++){  // Query the data in Slice MAC DB
        for(int j=0;j<kpmSlicePmDb.numOfSlice;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[j].usedPrb;
        }
        macIndex = (macIndex - 1) % SIZE_OF_MACDB;
    }

    for(int i=0;i<indicationRlcSliceCount;i++){  // Query the data in Slice RLC DB
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[j].ThpDl;
        }
        rlcIndex = (rlcIndex - 1) % SIZE_OF_RLCDB;
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){ // Get avg value
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
    long rlcIndex = (indexOfSliceRlcPm - 1) % SIZE_OF_RLCDB; // The index of first item in this internal
    long macIndex = (indexOfSliceMacPm - 1) % SIZE_OF_MACDB;
    uint64_t usedPrbSum[MAX_SIZE_OF_SLICE] = {0, };
    uint64_t thpSum[MAX_SIZE_OF_SLICE] = {0, };

    smoMacSliceCount++;

    for(int i=0;i<smoMacSliceCount;i++){ // Query the data in Slice MAC DB
        for(int j=0;j<kpmSlicePmDb.numOfSlice;j++){
            usedPrbSum[j] += kpmSlicePmDb.eachMacPm[macIndex].sliceRecord[j].usedPrb;   
        }
        macIndex = (macIndex - 1) % SIZE_OF_MACDB;
    }

    for(int i=0;i<smoRlcSliceCount;i++){ // Query the data in Slice RLC DB
        for(int j=0;j<MAX_SIZE_OF_SLICE;j++){
            thpSum[j] += kpmSlicePmDb.eachRlcPm[rlcIndex].sliceRecord[j].ThpDl;
        }
        rlcIndex = (rlcIndex - 1) % SIZE_OF_RLCDB;
    }

    for(int i=0;i<MAX_SIZE_OF_SLICE;i++){ // Get avg value
        kpmSlicePmDb.smo_avgUsedPrb[i] = smoMacSliceCount ? (uint64_t)usedPrbSum[i] / smoMacSliceCount : 0;
        kpmSlicePmDb.smo_avgThpDl[i] = smoRlcSliceCount ? (uint64_t)thpSum[i] / smoRlcSliceCount : 0;
    }
    smoRlcSliceCount = 0;
    smoMacSliceCount = 0;
    return 0;
}