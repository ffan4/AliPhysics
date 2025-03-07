#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TString.h"
#include "TObjArray.h"
#include "TGrid.h"

#include "AliLog.h"

#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"
#include "AliAnalysisTaskLambdaProtonCVE.h"
#endif

using std::cout;
using std::endl;

AliAnalysisTaskLambdaProtonCVE* AddTaskLambdaProtonCVE(
    int               debug=0, // debug level controls amount of output statements
    TString     trigger="kMB",
    TString   period="LHC10h",
    int           filterBit=1, // AOD filter bit selection
    bool       v0calibOn=true,
    bool      zdccalibOn=true,
    bool         QAVZERO=true,
    bool           QAZDC=true,
    bool           QATPC=true,
    bool          doNUE=false,
    bool           doNUA=true,
    bool    checkPIDFlow=true,
    TString        uniqueID=""
    )
{  
  // Creates a pid task and adds it to the analysis manager
  // Get the pointer to the existing analysis manager via the static
  // access method
  //=========================================================================
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTaskLambdaProtonCVE.C", "No analysis manager to connect to.");
    return NULL;
  }

  // Check the analysis type using the event handlers connected to the
  // analysis manager The availability of MC handler can also be
  // checked here.
  // =========================================================================
  if (!mgr->GetInputEventHandler()) {
    Error("AddTaskLambdaProtonCVE.C", "This task requires an input event handler.");
    return NULL;
  }
  //TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"

  // --- instantiate analysis task
  AliAnalysisTaskLambdaProtonCVE *task = new AliAnalysisTaskLambdaProtonCVE("TaskLambdaProtonCVE");
  task->SetDebug(debug);
  task->SetTrigger(trigger);
  task->SetPeriod(period);
  task->SetFilterBit(filterBit);
  task->SetNUEOn(doNUE);
  task->SetNUAOn(doNUA);  
  task->IfVZEROCalibOn(v0calibOn);
  task->IfZDCCalibOn(zdccalibOn);
  task->IfQAVZERO(QAVZERO);
  task->IfQAZDC(QAZDC);
  task->IfCheckPIDFlow(checkPIDFlow);

  //=========================================================================
  //Read in Files
  TFile* fNUEFile = nullptr;
  TFile* fNUAFile = nullptr;
  TFile* fVZEROCalibFile = nullptr;
  TFile* fZDCCalibFile = nullptr;

  TList* fListNUE = nullptr;
  TList* fListNUA = nullptr;
  TList* fVZEROCalibList = nullptr;
  TList* fZDCCalibList = nullptr;

  if (!gGrid) TGrid::Connect("alien://");
  if (doNUE) {
    if (period.EqualTo("LHC10h")) {
      fNUEFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC10h/Run1NUE.root","READ");
      fListNUE = dynamic_cast <TList*> (fNUEFile->Get("listNUE"));
    }
    if (period.EqualTo("LHC15o")) {
      fNUEFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC15o/efficiencyBothpol.root","READ");
      fListNUE = dynamic_cast <TList*> (fNUEFile->Get("fMcEffiHij"));
    }
    if(fListNUE) {
      task->SetListForNUE(fListNUE);
      std::cout<<"================  NUE List Set ================="<<std::endl;
    } else std::cout<<"!!!!!!!!!!!!!!!NUE List not Found!!!!!!!!!!!!!!!"<<std::endl;
  }

  if (doNUA) {
    if (period.EqualTo("LHC10h")) {
      fNUAFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC10h/10hNUAFB1.root","READ");
      fListNUA = dynamic_cast <TList*> (fNUAFile->Get("10hListNUAFB1"));
    }
    if (period.EqualTo("LHC15o")) {
      fNUAFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC15o/wgtPion_NUAFB768DeftwPUcut_LHC15op2_24Aug2021.root","READ");
      fListNUA = dynamic_cast <TList*> (fNUAFile->Get("15oListNUA"));
    }
    if(fListNUA) {
      task->SetListForNUA(fListNUA);
      std::cout<<"================  NUA List Set ================="<<std::endl;
    } else std::cout<<"!!!!!!!!!!!!!!!NUA List not Found!!!!!!!!!!!!!!!"<<std::endl;
  }

  if (v0calibOn) {
    if (period.EqualTo("LHC10h")) {
      fVZEROCalibFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC10h/10hQnCalib.root","READ");
      fVZEROCalibList = dynamic_cast <TList*> (fVZEROCalibFile->Get("10hlistqncalib"));
    }
    if (period.EqualTo("LHC15o")) {
      fVZEROCalibFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC15o/VZEROCalibFile.root","READ");
      fVZEROCalibList = dynamic_cast <TList*> (fVZEROCalibFile->Get("VZEROCalibList"));
    }
    if(fVZEROCalibList) {
      task->SetListForVZEROCalib(fVZEROCalibList);
      std::cout<<"================  VZERO List Set ================="<<std::endl;
    } else std::cout<<"!!!!!!!!!!!!!!!VZERO List not Found!!!!!!!!!!!!!!!"<<std::endl;
  }

  if (zdccalibOn) {
    if (period.EqualTo("LHC10h")) {
      fZDCCalibFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC10h/ZDCCalibFile.root","READ");
      fZDCCalibList = dynamic_cast <TList*> (fZDCCalibFile->Get("ZDCCalibList"));
    }
    // if (period.EqualTo("LHC15o")) {
    //   fZDCCalibFile = TFile::Open("alien:///alice/cern.ch/user/c/chunzhen/CalibFiles/LHC15o/10hQnCalib.root","READ");
    //   fZDCCalibList = dynamic_cast <TList*> (fZDCCalibFile->Get("10hlistqncalib"));
    // }
    if(fZDCCalibList) {
      task->SetListForZDCCalib(fZDCCalibList);
      std::cout<<"================  ZDC List Set ================="<<std::endl;
    } else std::cout<<"!!!!!!!!!!!!!!!ZDC List not Found!!!!!!!!!!!!!!!"<<std::endl;
  }

  // Create ONLY the output containers for the data produced by the
  // task.  Get and connect other common input/output containers via
  // the manager as below
  //======================================================================
    mgr->AddTask(task);
    AliAnalysisDataContainer* cinput  = mgr->GetCommonInputContainer();
    TString outputFileName = mgr->GetCommonFileName();
    cout<<"outputfileName::::==========:::"<<outputFileName<<endl;
    AliAnalysisDataContainer* coutput = mgr->CreateContainer("output", TList::Class(), 
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName.Data());
    mgr->ConnectInput (task, 0, cinput);
    mgr->ConnectOutput(task, 1, coutput);

  //==============================================================
  // Return task pointer at the end

  cout<<"================  Return task ================="<<endl;
  return task;
}  

