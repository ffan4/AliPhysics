/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskCaloHFEpp_H
#define AliAnalysisTaskCaloHFEpp_H

#include "AliAnalysisTaskSE.h"
#include "AliPIDResponse.h"
#include "TProfile.h"
class AliAODMCParticle;
class AliAODMCHeader;
class AliMultSelection;

class AliAnalysisTaskCaloHFEpp : public AliAnalysisTaskSE  
{
	public:
		AliAnalysisTaskCaloHFEpp();
		AliAnalysisTaskCaloHFEpp(const char *name);
		//AliAnalysisTaskCaloHFEpp(const char *name,
		//								      Bool_t flagEG1,
		//						          Bool_t flagEG2,
		//								      Bool_t flagDG1,
		//						          Bool_t flagDG2,
		//						          Bool_t SetFlagClsTypeEMC,
		//						          Bool_t SetFlagClsTypeDCAL);
		virtual                 ~AliAnalysisTaskCaloHFEpp();

		virtual void            UserCreateOutputObjects();
		virtual void            UserExec(Option_t* option);
		virtual void            Terminate(Option_t* option);
		virtual void            SelectPhotonicElectron(Int_t itrack, AliVTrack *track, Bool_t &fFlagPhotonicElec, Int_t iMC, Double_t TrkPt,Double_t DCAxy,Int_t Bsign, Bool_t &iIsocut);
		virtual void            IsolationCut(Int_t itrack, AliVTrack *track, Double_t TrackPt, Double_t MatchPhi, Double_t MatchEta, Double_t MatchclE, Bool_t fFlagPhoto, Bool_t &fFlagIso, Bool_t fFlagB, Bool_t fFlagD, Double_t &IsoEnergy, Int_t &NcontCone);

		virtual void            IsolationTrackBase(Int_t itrack, AliVTrack *track, Double_t MatchclE, Double_t &IsoEnergyTrack, Int_t &NtrackCone);
		virtual void            CheckCorrelation(Int_t itrack, AliVTrack *track, Double_t TrackPt, Double_t Riso, Bool_t fFlagPhoto, Int_t iWevt);

		virtual void            CheckMCgen(AliAODMCHeader* fMCheader,Double_t CutEta, Int_t Nmult);
		virtual void            CalNcharge(AliAODMCHeader* fMCheader,Double_t CutEta);
		virtual void            GetMClevelWdecay(AliAODMCHeader* fMCheadera, Double_t CutEta);
		virtual void            FindMother(AliAODMCParticle* part, int &label, int &pid, double &ptmom);
		virtual void            FindWdecay(AliAODMCParticle* part, int &label, int &pid);
		virtual void            SetEtaRange(Int_t etarange){fetarange = etarange;};

		Bool_t                  GetEMCalTriggerEG1() { return fEMCEG1; };
		Bool_t                  GetEMCalTriggerEG2() { return fEMCEG2; };
		Bool_t                  GetDCalTriggerDG1()  { return fDCDG1; };
		Bool_t                  GetDCalTriggerDG2()  { return fDCDG2; };
		Bool_t                  IsPdecay(int mpid);
		Bool_t                  IsDdecay(int mpid);
		Bool_t                  IsBdecay(int mpid);
		TProfile* 		GetEstimatorHistogram(TFile* fEstimator, const AliAODEvent *fAOD, Int_t mtype);
		TProfile* 		GetEstimatorHistogramMC(TFile* fEstimator, const AliAODEvent *fAOD, Int_t mtype);
		TH1D* 		        GetNtrkWeightMC(TFile* fEstimator, Int_t mtype);
		Double_t                GetCorrectedNtrackletsD(TProfile* estimatorAvg, Double_t uncorrectedNacc, Double_t vtxZ, Double_t refMult);

		void                    SetEG1(Bool_t flagEG1) { fEMCEG1= flagEG1;};
		void                    SetEG2(Bool_t flagEG2) { fEMCEG2= flagEG2;};
		void                    SetDG1(Bool_t flagDG1) { fDCDG1= flagDG1;};
		void                    SetDG2(Bool_t flagDG2) { fDCDG2= flagDG2;};
		void                    SetfFlagClsTypeEMC(Bool_t fEMC){fFlagClsTypeEMC = fEMC;};
		void                    SetfFlagClsTypeDCAL(Bool_t fDCAL){fFlagClsTypeDCAL = fDCAL;};


		void                    SetTrackEta(Double_t min, Double_t max) {TrackEtaMin = min, TrackEtaMax = max;};
		void                    SetTrackClust(Int_t TPC, Int_t ITS, Int_t Crossed) {NTPCClust = TPC, NITSClust = ITS, NCrossedRow = Crossed;};
		void                    SetDCA(Double_t xy, Double_t z) {DCAxy = xy, DCAz = z;};
		void                    SetNsigma(Double_t min, Double_t max) {NsigmaMin = min, NsigmaMax = max;};
		void                    SetM20(Double_t min, Double_t max) {M20Min = min, M20Max = max;};
		void                    SetEop(Double_t min, Double_t max) {EopMin = min, EopMax = max;};
		void                    SetConeR(Double_t coneR) {MaxConeR = coneR;};
		void                    SetptAsso(Double_t ptassoMin) {ptAssoMin = ptassoMin;};
		void                    SetMimClE(Double_t MimClE) {CutMimClE = MimClE;};
		void                    SetptCut(TString pte) {pTe = pte;};
		void                    SetMassMin(Double_t MassMin) {massMin = MassMin;};
		void                    SetNref(Double_t nref) {Nref = nref;};
		void                    SetNrefV0(Double_t nrefV0) {NrefV0 = nrefV0;};
		void                    SetMaxNtr(Double_t maxNtr) {MaxNtr = maxNtr;};
		void                    SetMinNtr(Double_t minNtr) {MinNtr = minNtr;};
		void                    SetEstimatorFile(TString filename) {festimatorFile = filename;}
		void                    SetMultType(Int_t mult_type) {fmult_type = mult_type;}
               

		//void      SetWeightNtrkl(TH1D* hWeight){
		//	if(fweightNtrkl) delete fweightNtrkl;
		//	fweightNtrkl=new TH1D(*hWeight);
		//}


	private:
		AliAODEvent*            fAOD;           //! input event
		TList*                  fOutputList;    //! output list
		AliVEvent*              fVevent;        //!event object
		AliMultSelection*       fMultSelection;
		AliPIDResponse*         fpidResponse; //!pid response  

		//==== Tender ====
		Bool_t                  fUseTender;// switch to add tender
		TClonesArray*           fTracks_tender;
		TClonesArray*           fCaloClusters_tender;

		//==== cut parameters ====
		Double_t TrackEtaMin, TrackEtaMax;
		Double_t NTPCClust, NITSClust, NCrossedRow;
		Double_t DCAxy, DCAz;
		Double_t NsigmaMin, NsigmaMax;
		Double_t M20Min, M20Max;
		Double_t EopMin, EopMax;
		Double_t MaxConeR;
		Double_t ptAssoMin;
		Double_t CutMimClE;
		TString pTe;
		Double_t massMin;
		Double_t Nref;
		Double_t NrefV0;
		Int_t Nch;
		Int_t MinNtr;
		Int_t MaxNtr;
                TString festimatorFile;
                TProfile* estimatorAvg;
                TProfile* estimatorV0Avg;
                TH1D* NtrkWeightMC;
                Int_t fmult_type;

		//==== basic parameters ====
		TH1F*                   fNevents;
		TH1F*                   fNDB;
		TH1F*                   fHist_VertexZ;    
		TH1F*                   fHist_VertexZ_all;    
		TH1F*                   fHist_Centrality; 
		TH2F*                   fHist_Mult;       
		TH2F*                   fTrigMulti;
		TH1F*                   fHistEta_track;   
		TH1F*                   fHistPhi_track;   
		TH1F*                   fHistEta_EMcal;   
		TH1F*                   fHistPhi_EMcal;   
		TH2F*                   fHistScatter_EMcal;        
		TH2F*                   fHistScatter_EMcal_aftMatch; 
		TH2F*                   fHistoNCells;
		TH2F*                   fM02;
		TH2F*                   fM20;
		TH1F*                   fM02_ele;
		TH1F*                   fM20_ele;
		TH1F*                   fM02_had;
		TH1F*                   fM20_had;

		//==== check cut parameters ====
		TH1F*                   fTPCNcls;
		TH1F*                   fITSNcls;
		TH1F*                   fTPCCrossedRow;
		TH2F*                   fTPCnsig_ele;
		TH2F*                   fTPCnsig_iso;
		TH2F*                   fM02_2;
		TH2F*                   fM20_2;
		TH1F*                   fEop_ele;
		TH2F*                   fEop_iso;
		TH2F*                   fEop_iso_eID;
		TH2F*                   fConeR;
		TH2F*                   fConeE;
		TH2F*                   fNpart;

		//==== Real data output ====
		TH1F*                   fHist_trackPt;        //! dummy histogram
		TH1F*                   fHistMatchPt;        
		TH1F*                   fHistSelectPt;        
		TH2F*                   fHistCheff0;        
		TH2F*                   fHistCheff1;        
		TH1F*                   fHist_ClustE;        //! dummy histogram
		TH1F*                   fHist_SelectClustE;
		TH1F*                   fHist_SelectClustE_time;
		TH1F*                   fHistMatchE;
		TH1F*                   fHistMatchE_time;
		TH2F*                   fHistoTimeEMC;
		TH2F*                   fdEdx;
		TH2F*                   fTPCnsig;
		TH2F*                   fHistNsigEop;
		TH2F*                   fEopPt_ele_loose;
		TH2F*                   fEopPt_ele_tight;
		TH2F*                   fEopPt_ele_tight_PYTHIA;
		TH2F*                   fEopPt_ele_tight_forSys;
		TH2F*                   fEopPt_had;
		TH1F*                   fEtadiff;
		TH1F*                   fPhidiff;
		TH2F*                   fInv_pT_LS;
		TH2F*                   fInv_pT_ULS;
		TH2F*                   fInv_pT_LS_forW;
		TH2F*                   fInv_pT_ULS_forW;
		TH1F*                   fHistPt_Inc;
		TH1F*                   fHistPt_Iso;
		TH2F*                   fHistPt_R_Iso;
		TH2F*                   fRiso_phidiff;
		TH2F*                   fRiso_phidiff_LS;
		TH2F*                   fRiso_phidiff_35;
		TH2F*                   fRiso_phidiff_LS_35;
		THnSparseD*             fWh_phidiff;
		THnSparseD*             fhad_phidiff;
		THnSparseD*             fIsoArray;      
		THnSparseD*             fHFArray;      
		TH2F*                   fzvtx_Ntrkl;
		TH2F*                   fzvtx_Nch;
		TH2F*                   fzvtx_Ntrkl_V0;
		TH2F*                   fzvtx_Ntrkl_Corr;
		TH1F*                   fzvtx_Corr;
		TH1F*                   fNtrkl_Corr;
		TH1F*                   fNtrkl_noCorr;
		TH2F*                   fzvtx_V0M;
		TH2F*                   fcent_V0M;
		TH2F*                   fNchNtr;
		TH2F*                   fNchNtr_Corr;
		TH2F*                   fNchMC;
		TH2F*                   fDCAxy_Pt_ele;
		TH2F*                   fDCAxy_Pt_had;
		TH2F*                   fDCAxy_Pt_LS;
		TH2F*                   fDCAxy_Pt_ULS;
		TH2F*                   fDCAxy_Pt_Dpm;
		TH2F*                   fDCAxy_Pt_D0;
		TH2F*                   fDCAxy_Pt_Ds;
		TH2F*                   fDCAxy_Pt_lambda;
		TH2F*                   fDCAxy_Pt_B;
		TH2F*                   fDCAxy_Pt_We;
		TH2F*                   fPt_Btoe;

		//==== Trigger or Calorimeter flag ====
		Bool_t                  fEMCEG1;//EMcal Threshold EG1
		Bool_t                  fEMCEG2;//EMcal Threshold EG2
		Bool_t                  fDCDG1;//Dcal Threshold DG1
		Bool_t                  fDCDG2;//Dcal Threshold DG2
		Bool_t                  fFlagClsTypeEMC;//switch to select EMC clusters
		Bool_t                  fFlagClsTypeDCAL;//switch to select DCAL clusters

		//==== MC output ====
		TH1F*                   fMCcheckMother;
		TClonesArray*           fMCarray;//! MC array
		AliAODMCParticle*       fMCparticle;
		AliAODMCParticle*       fMCTrackpart;
		AliAODMCHeader*         fMCheader;
		TH1F*                   fCheckEtaMC;
		TH2F*                   fHistMCorgPi0;
		TH2F*                   fHistMCorgEta;
		TH1F*                   fHistMCorgD;
		TH1F*                   fHistMCorgB;
		Int_t                   NembMCpi0; // # of process in MC (no GEANT process)
		Int_t                   NembMCeta; // # of process in MC (no GEANT process)
		Int_t                   NpureMCproc; // # of process in MC (no GEANT process)
		Int_t                   NpureMC; // # of process in MC (no GEANT process)
		TH1D*                   fHistPhoReco0;
		TH1D*                   fHistPhoReco1;
		TH1D*                   fHistPhoReco2;
		TH1D*               	fHistPhoPi0;
		TH1D*               	fHistPhoPi1;
		TH1D*               	fHistPhoEta0;
		TH1D*               	fHistPhoEta1;
		TF1*                    fPi000;
		TF1*                    fPi005;
		TF1*                    fPi010;
		TF1*                    fEta000;
		TF1*                    fEta005;
		TF1*                    fEta010;
		TF1*                    fCorrZvtx;
		TF1*                    fCorrNtrkl;
		TH1F*               	fHistPt_HFE_MC_D;
		TH1F*               	fHistPt_HFE_MC_B;
		TH1F*               	fHistPt_HFE_PYTHIA;
		TH1F*               	fHistPt_HFE_emb;
		TH1F*               	fHistPt_HFE_Gen;
		TH2F*               	fHistPt_HFE_GenvsReco;
		TH1F*               	fHist_eff_HFE;
		TH1F*               	fHist_eff_match;
		TH1F*               	fHist_eff_TPC;
		TH1F*               	fHist_eff_M20;
		TH2F*               	fHist_eff_Iso;
		TH1F*                   fHistWeOrg;
		TH1F*                   fHistWeOrgPos;
		TH1F*                   fHistWeOrgNeg;

		AliAnalysisTaskCaloHFEpp(const AliAnalysisTaskCaloHFEpp&); // not implemented
		AliAnalysisTaskCaloHFEpp& operator=(const AliAnalysisTaskCaloHFEpp&); // not implemented
		Int_t fetarange;
		TProfile*		fMultEstimatorAvg;
		TH1D*       fweightNtrkl;


		ClassDef(AliAnalysisTaskCaloHFEpp, 1);
};

#endif
