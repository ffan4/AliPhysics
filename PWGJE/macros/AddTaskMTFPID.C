AliAnalysisTaskMTFPID *AddTaskMTFPID(Bool_t inputFromOtherTask = kFALSE, Bool_t writeOutputToSeparateFiles = kTRUE, Bool_t useConvolutedGauss = kTRUE, Bool_t storeJetInformation = kFALSE, TString listOfFiles = "", Bool_t doEfficiency = kFALSE, TString nameSuffix = "")
{
  // Macro to set up and add PID task with default settings.
  //
  // Typical parameters to run on 11a1* (MC_pp@7TeV):
  // "PWGJE_taskPID_Jets", kTRUE, kTRUE, "V0A", kTRUE
  // and as a second task
  // "PWGJE_taskPID_Jets_Inclusive", kTRUE, kTRUE, "V0A", kTRUE
  
  TString taskName = Form("PWGJE_taskMTFPID%s", nameSuffix.Data());
  
  // Get the current analysis manager
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddTaskPID", "No analysis manager found.");
    return 0x0;
  }
  
  //========= Add task to the ANALYSIS manager =====
  AliAnalysisTaskMTFPID *task = new AliAnalysisTaskMTFPID(taskName.Data());
  
  task->SelectCollisionCandidates(AliVEvent::kMB | AliVEvent::kINT7 | AliVEvent::kINT8);
  
  printf("\nSetting up task %s:\n", taskName.Data());
  
  if (!inputFromOtherTask) {
    // Add track filters
    
    AliAnalysisFilter* trackFilter = new AliAnalysisFilter("trackFilter");
    AliESDtrackCuts* esdTrackCutsL = 0x0;
    
    if (listOfFiles.Contains("LHC11") || listOfFiles.Contains("LHC12") || listOfFiles.Contains("LHC13") || listOfFiles.Contains("LHC15")) {
      esdTrackCutsL = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(kTRUE);
      printf("Using standard ITS-TPC track cuts 2011\n");
      trackFilter->SetTitle("Standard ITS-TPC track cuts 2011");
    }
    else if (listOfFiles.Contains("LHC10")) {
      esdTrackCutsL = AliESDtrackCuts::GetStandardITSTPCTrackCuts2010(kTRUE);
      printf("Using standard ITS-TPC track cuts 2010\n");
      trackFilter->SetTitle("Standard ITS-TPC track cuts 2010");
    }
    else  {
      esdTrackCutsL = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(kTRUE);
      printf("WARNING: Cuts not configured for this period!!! Using standard ITS-TPC track cuts 2011\n");
      trackFilter->SetTitle("Standard ITS-TPC track cuts 2011");
    }
    /*
    esdTrackCutsL->SetMinNCrossedRowsTPC(120);
    esdTrackCutsL->SetMinRatioCrossedRowsOverFindableClustersTPC(0.8);
    esdTrackCutsL->SetMaxChi2PerClusterITS(36);
    esdTrackCutsL->SetMaxFractionSharedTPCClusters(0.4);
    esdTrackCutsL->SetMaxChi2TPCConstrainedGlobal(36);
    */
    
    trackFilter->AddCuts(esdTrackCutsL);
    task->SetTrackFilter(trackFilter);
  }
  
  // Test whether we have pPb or Pbp
  if (listOfFiles.Contains("pPb") || listOfFiles.Contains("Pbp")) {
    task->SetIsPbpOrpPb(kTRUE);
    printf("pPb/Pbp detected -> Adapting vertex cuts!\n");
    task->SetCentralityEstimator("V0A");
  }
  else  {
    task->SetIsPbpOrpPb(kFALSE);
    printf("Collision type different from pPb/Pbp detected -> Using standard vertex cuts!\n");
    task->SetCentralityEstimator("V0M");
  }
  
  task->SetStoreCentralityPercentile(kTRUE);
  
//   if (listOfFiles.Contains("pp")) {
//     task->SetCentralityEstimator("ITSTPCtracklets");
//     task->SetCentralityEstimator("ppMultV0M");
//   }
  
  task->SetEtaAbsCutRange(0.0, 0.9);
  task->SetUsePhiCut(kFALSE);
  
  // Do not set the covolution parameters if they are not used (saves some cpu time for the initialisation)
  if (useConvolutedGauss) {
    if ((listOfFiles.Contains("pPb") || listOfFiles.Contains("Pbp")) && listOfFiles.Contains("LHC13")) {
      printf("\n13* pPb @ 5.023 ATeV data detected -> Setting corresponding convolution parameters...\n");
      task->SetConvolutedGaussLambdaParameter(2.6);
    } else if (listOfFiles.Contains("LHC11a_without_SDD")) {
      printf("\n11a (pp 2.76 TeV) detected -> Setting corresponding convolution parameters...\n");
      task->SetConvolutedGaussLambdaParameter(3.0);
    } else if (listOfFiles.Contains("LHC15")) {
      printf("\n15* (pp 13 TeV) detected -> Setting corresponding convolution parameters...\n");
      task->SetConvolutedGaussLambdaParameter(2.2);
    }  else {
      printf("\nUsing default convolution parameters...\n");
      task->SetConvolutedGaussLambdaParameter(2.0);
    }
  }
  
  task->SetDoEfficiency(doEfficiency);
  
  task->SetUseMCidForGeneration(kFALSE); // Set to kFALSE on 2013-01-09
  task->SetUseITS(kTRUE);
  task->SetUseTOF(kTRUE);
  task->SetUsePriors(kTRUE);
  task->SetUseTPCDefaultPriors(kTRUE);
  task->SetUseConvolutedGaus(useConvolutedGauss);
  task->SetTakeIntoAccountMuons(kTRUE);
  
  task->SetStoreTOFInfo(kFALSE);
  task->SetStoreCharge(kFALSE);
  
  task->SetInputFromOtherTask(inputFromOtherTask);
  task->SetStoreAdditionalJetInformation(storeJetInformation);
  
  task->SetStorePt(kTRUE);
  task->SetStoreZ(kTRUE && storeJetInformation);
  task->SetStoreXi(kTRUE && storeJetInformation);
  task->SetStoreRadialDistance(kTRUE && storeJetInformation);
  task->SetStorejT(kTRUE && storeJetInformation);
  
  task->SetPileUpRejectionType(AliAnalysisTaskPIDV0base::kPileUpRejectionSPD);
  
  //Settings of AliAnalysisTaskPIDV0base
  task->SetTPCcutType(AliAnalysisTaskPIDV0base::kTPCnclCut);
  task->SetCutPureNcl(80);
  
  task->PrintSettings();
  
  mgr->AddTask(task);


  //================================================
  //              data containers
  //================================================

  //connect containers
  mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());
  
  if (mgr->GetCommonOutputContainer()) {
    //Not present for local runs
    mgr->ConnectOutput(task, 0, mgr->GetCommonOutputContainer());
  }
  
  //define output containers
  AliAnalysisDataContainer *coutput1 = 
    mgr->CreateContainer(Form("%s", taskName.Data()),
                         TObjArray::Class(),
                         AliAnalysisManager::kOutputContainer,
                         writeOutputToSeparateFiles
                          ? Form("%s.root", taskName.Data())
                          : Form("%s:%s", AliAnalysisManager::GetCommonFileName(), taskName.Data()));
  mgr->ConnectOutput(task, 1, coutput1);
  
  if (task->GetDoEfficiency()) {
    AliAnalysisDataContainer *coutput2 = 
        mgr->CreateContainer(Form("%s_efficiency", taskName.Data()),
                            AliCFContainer::Class(),
                            AliAnalysisManager::kOutputContainer,
                            writeOutputToSeparateFiles
                              ? Form("%s_efficiency.root", taskName.Data())
                              : Form("%s:%s_efficiency", AliAnalysisManager::GetCommonFileName(), taskName.Data()));
    mgr->ConnectOutput (task, 2, coutput2);
  }
  
//   if (task->GetDoDeDxCheck() || task->GetDoPtResolution()) {
//     AliAnalysisDataContainer *coutput3 = 
//         mgr->CreateContainer(Form("%s_PtResolution", taskName.Data()),
//                             TObjArray::Class(),
//                             AliAnalysisManager::kOutputContainer,
//                             writeOutputToSeparateFiles
//                               ? Form("%s_PtResolution.root", taskName.Data())
//                               : Form("%s:%s_PtResolution", AliAnalysisManager::GetCommonFileName(), taskName.Data()));
//     mgr->ConnectOutput(task, 3, coutput3);
//   }

  return task;
}
