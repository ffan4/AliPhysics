//==============================================================\\
// dowang track cut for p-d/t/He3 analysis                      \\
// deuteron part refer to AliFemtoWRzTrackCut.h                 \\
//==============================================================\\

#include "AliFemtoTrackCutPdtHe3.h"
#include "TLorentzVector.h"
AliFemtoTrackCutPdtHe3::AliFemtoTrackCutPdtHe3():
AliFemtoESDTrackCut()
{
    fNsigmaP    = 3.;
    fNsigmaD    = 3.;
    fNsigmaT    = 3.;
    fNsigmaHe3  = 3.;
    fNsigmaRejection = 3.;
    
    SwitchMom_p = 0.5;
    SwitchMom_d = 0.8;
    SwitchMom_t = 999;
    SwitchMom_He3 = 999;

    fdEdxcut = 1;
    fOtherNsigmacut = 0;
    fMinTPCFoundFraction = 0;
   
    fUseTOFMassCut = 0; 
    TOFMassLowLimit = 0.;
    TOFMassUpLimit = 10.;

    fUsePtCut = 0;
    // for Nsigma reject
    fOnlyTPCreject = 1;
}

AliFemtoTrackCutPdtHe3::AliFemtoTrackCutPdtHe3(const AliFemtoTrackCutPdtHe3 &aCut) : 
AliFemtoESDTrackCut(aCut)
{
    //copy constructor 
    fNsigmaP = aCut.fNsigmaP;
    fNsigmaD = aCut.fNsigmaD;
    fNsigmaT = aCut.fNsigmaT;
    fNsigmaHe3 = aCut.fNsigmaHe3;
    fNsigmaRejection = aCut.fNsigmaRejection;

    SwitchMom_p = aCut.SwitchMom_p;
    SwitchMom_d = aCut.SwitchMom_d;
    SwitchMom_t = aCut.SwitchMom_t;
    SwitchMom_He3 = aCut.SwitchMom_He3;

    fdEdxcut = aCut.fdEdxcut;
    fOtherNsigmacut = aCut.fOtherNsigmacut;
    fMinTPCFoundFraction = aCut.fMinTPCFoundFraction;

    fUseTOFMassCut = aCut.fUseTOFMassCut;
    TOFMassLowLimit = aCut.TOFMassLowLimit;
    TOFMassUpLimit = aCut.TOFMassUpLimit;

    fUsePtCut = aCut.fUsePtCut;
    fOnlyTPCreject = aCut.fOnlyTPCreject;
}

AliFemtoTrackCutPdtHe3::~AliFemtoTrackCutPdtHe3()
{
  // Destructor
}


AliFemtoTrackCutPdtHe3& AliFemtoTrackCutPdtHe3::operator=(const AliFemtoTrackCutPdtHe3& aCut)
{
    // assignment operator
    if (this == &aCut)
        return *this;

    AliFemtoESDTrackCut::operator=(aCut);

    fNsigmaP = aCut.fNsigmaP;
    fNsigmaD = aCut.fNsigmaD;
    fNsigmaT = aCut.fNsigmaD;
    fNsigmaHe3 = aCut.fNsigmaHe3;

    fNsigmaRejection = aCut.fNsigmaRejection;
    SwitchMom_p = aCut.SwitchMom_p;
    SwitchMom_d = aCut.SwitchMom_d;
    SwitchMom_t = aCut.SwitchMom_t;
    SwitchMom_He3 = aCut.SwitchMom_He3;

    fdEdxcut = aCut.fdEdxcut;
    fOtherNsigmacut = aCut.fOtherNsigmacut;
    fMinTPCFoundFraction = aCut.fMinTPCFoundFraction;

    fUseTOFMassCut = aCut.fUseTOFMassCut;
    TOFMassLowLimit = aCut.TOFMassLowLimit;
    TOFMassUpLimit = aCut.TOFMassUpLimit;

    fUsePtCut = aCut.fUsePtCut;
    return *this;
}

bool AliFemtoTrackCutPdtHe3::Pass(const AliFemtoTrack* track){
    if (fStatus && (track->Flags() & fStatus) != fStatus) {
        return false;
    }
    if (fRemoveKinks && (track->KinkIndex(0) || track->KinkIndex(1) || track->KinkIndex(2))) {
        return false;
    }
    if (fRemoveITSFake && track->ITSncls() < 0) {
        return false;
    }
    if (fminTPCclsF > track->TPCnclsF()) {
        return false;
    }
    if (fminTPCncls > track->TPCncls()) {
        return false;
    }
    if (fminITScls > track->ITSncls()) {
        return false;
    }

    if (fMaxImpactXY < TMath::Abs(track->ImpactD())) {
        return false;
    }
    if (fMinImpactXY > TMath::Abs(track->ImpactD())) {
        return false;
    }
    if (fMaxImpactZ < TMath::Abs(track->ImpactZ())) {
        return false;
    }
    if (fMaxSigmaToVertex < track->SigmaToVertex()) {
        return false;
    }

    if (track->ITSncls() > 0 && (track->ITSchi2() / track->ITSncls()) > fMaxITSchiNdof) {
        return false;
    }

    if (track->TPCchi2perNDF() > fMaxTPCchiNdof) {
        return false;
    }


    // ITS cluster requirenments
    for (Int_t i = 0; i < 3; i++) {
        if (!CheckITSClusterRequirement(fCutClusterRequirementITS[i], track->HasPointOnITSLayer(i * 2), track->HasPointOnITSLayer(i*2+1))) {
        return false;
        }
    }

    if (fLabel) {
        if (track->Label() < 0) {
        fNTracksFailed++;
        return false;
        }
    }
    if (fCharge != 0 && (track->Charge() != fCharge)) {
        fNTracksFailed++;
        return false;
    }


    Bool_t tTPCPidIn = (track->Flags() & AliFemtoTrack::kTPCpid) > 0;
    Bool_t tITSPidIn = (track->Flags() & AliFemtoTrack::kITSpid) > 0;
    Bool_t tTOFPidIn = (track->Flags() & AliFemtoTrack::kTOFpid) > 0;
    
    // no use!
    //const double momentum = track->P().Mag();
    
    
//    if (fMinPforTOFpid > 0
//        && fMinPforTOFpid < momentum && momentum < fMaxPforTOFpid
//        && !tTOFPidIn) {
//        fNTracksFailed++;
//        return false;
//    }
//
//    if (fMinPforTPCpid > 0
//        && fMinPforTPCpid < momentum && momentum < fMaxPforTPCpid
//        && !tTPCPidIn) {
//        fNTracksFailed++;
//        return false;
//    }
//
//    if (fMinPforITSpid > 0
//        && fMinPforITSpid < momentum && momentum < fMaxPforITSpid
//        && !tITSPidIn) {
//        fNTracksFailed++;
//        return false;
//    }

    // dowang for He3, it needs change
    float tEnergy = 0.;
    float tRapidity = 0.;
    float tPt = 0.;
    float tEta = 0.;
    float tTotalP = 0.;
    if(fMostProbable == 15){
        TLorentzVector thisTrackMom;
        tEnergy = ::sqrt(track->P().Mag2() * 4. + fMass * fMass);
        thisTrackMom.SetPxPyPzE(2.*track->P().x(),2.*track->P().y(),2.*track->P().z(),tEnergy);
        if (tEnergy-2.*track->P().z() != 0 && (tEnergy + 2. * track->P().z()) / (tEnergy- 2. * track->P().z()) > 0)
            //tRapidity = 0.5 * ::log((tEnergy + 2. * track->P().z())/(tEnergy- 2. * track->P().z()));
            tRapidity = thisTrackMom.Rapidity();
        tPt = thisTrackMom.Pt();
        tTotalP = thisTrackMom.P();
        tEta = thisTrackMom.PseudoRapidity();
    }
    else{
        tEnergy = ::sqrt(track->P().Mag2() + fMass * fMass);
        if (tEnergy-track->P().z() != 0 && (tEnergy + track->P().z()) / (tEnergy-track->P().z()) > 0)
            tRapidity = 0.5 * ::log((tEnergy + track->P().z())/(tEnergy-track->P().z()));
        tPt = track->P().Perp();
	tTotalP = track->P().Mag();
        tEta = track->P().PseudoRapidity();
    }

    // not use
    if (fMaxImpactXYPtOff < 999.0) {
        if ((fMaxImpactXYPtOff + fMaxImpactXYPtNrm*TMath::Power(tPt, fMaxImpactXYPtPow)) < TMath::Abs(track->ImpactD())) {
        fNTracksFailed++;
        return false;
        }
    }

    if ((tRapidity < fRapidity[0]) || (tRapidity > fRapidity[1])) {
        fNTracksFailed++;
        return false;
    }
    if ((tEta < fEta[0]) || (tEta > fEta[1])) {
        fNTracksFailed++;
        return false;
    }

    // dowang 2.22
    if(fUsePtCut){
	    if ((tPt < fPt[0]) || (tPt > fPt[1])) {
		fNTracksFailed++;
		return false;
	    }
    }
    else{
	    if ((tTotalP < fPt[0]) || (tTotalP > fPt[1])) {
		fNTracksFailed++;
		return false;
	    }
    }


    if ((track->PidProbElectron() < fPidProbElectron[0]) || (track->PidProbElectron() > fPidProbElectron[1])) {
        fNTracksFailed++;
        return false;
    }
    if ((track->PidProbPion() < fPidProbPion[0]) || (track->PidProbPion() > fPidProbPion[1])) {
        fNTracksFailed++;
        return false;
    }
    if ((track->PidProbKaon() < fPidProbKaon[0]) || (track->PidProbKaon() > fPidProbKaon[1])) {
        fNTracksFailed++;
        return false;
    }
    if ((track->PidProbProton() < fPidProbProton[0]) || (track->PidProbProton() > fPidProbProton[1])) {
        fNTracksFailed++;
        return false;
    }
    if ((track->PidProbMuon() < fPidProbMuon[0]) || (track->PidProbMuon() > fPidProbMuon[1])) {
        fNTracksFailed++;
        return false;
    }

    //****N Sigma Method -- electron rejection****
    if (fElectronRejection)
        if (!IsElectron(track->NSigmaTPCE(),track->NSigmaTPCPi(),track->NSigmaTPCK(), track->NSigmaTPCP()))
            return false;
    
    if (fMostProbable>0) {
        
        int imost=0;
        //****N Sigma Method****
        if (fPIDMethod==0) {
	    //\ for proton PID
            if (fMostProbable == 4) { // proton nsigma-PID required contour adjusting (in LHC10h)
                if (IsProtonNSigma(track->P().Mag(), track->NSigmaTPCP(), track->NSigmaTOFP()) ) {
                    	imost = 4;
                }
		//\ reject
		if( fOtherNsigmacut && RejectFakeP(track,track->P().Mag()) ){
			imost = 0;			
		}
            }
	    //\ for deuteron PID
            else if (fMostProbable == 13){   //cut on Nsigma deuteron
                if ( IsDeuteronNSigma(track->P().Mag(), track->MassTOF(), fNsigmaMass, track->NSigmaTPCD(), track->NSigmaTOFD())){
			imost = 13;
		}
		//\ reject 
                if( fOtherNsigmacut && RejectFakeD(track,track->P().Mag()) ){
			imost = 0;			
		}
                //\ dE/dx cut for low pt abnormal
                if ( fdEdxcut && !IsDeuteronTPCdEdx(track->P().Mag(), track->TPCsignal()) ){
                    	imost = 0;
                }
            }
	    //\ for triton PID
            else if (fMostProbable == 14){   //cut on Nsigma triton
                if (IsTritonNSigma(track->P().Mag(), track->MassTOF(), fNsigmaMass, track->NSigmaTPCT(), track->NSigmaTOFT()) ){
                    imost = 14;
                }
                if ( fdEdxcut && !IsTritonTPCdEdx(track->P().Mag(), track->TPCsignal()) ){
                    imost = 0;
                }   
            }
 	    //\ for He3 PID
            else if (fMostProbable == 15){
		        //cout<<"enter He PID"<<endl;
                if (IsHe3NSigma(track->P().Mag(), track->MassTOF(), fNsigmaMass, track->NSigmaTPCH(), track->NSigmaTOFH()) ){
                // if (IsHe3NSigma(track->P().Mag(), track->MassTOF(), fNsigmaMass, track->NSigmaTPCH(), track->NSigmaTOFH()) 
		        //     && !IsElectronNSigmaRejection(track->P().Mag(),track->NSigmaTPCE())
                //     && !IsPionNSigmaRejection(track->P().Mag(),track->NSigmaTPCPi(), track->NSigmaTOFPi())
                //     && !IsKaonNSigmaRejection(track->P().Mag(),track->NSigmaTPCK(), track->NSigmaTOFK())
                //     && !IsProtonNSigmaRejection(track->P().Mag(),track->NSigmaTPCP(), track->NSigmaTOFP()) ){ 
                //cout<<"wdf "<<track->NSigmaTPCH()<<endl;    
		        imost = 15;
                }
            }
            else if(fMostProbable == 16){
                if (IsElectronNSigma(track->P().Mag(), track->NSigmaTPCE(), track->NSigmaTOFE()) ){
                    imost = 16;
                }
            }
	    if (imost != fMostProbable) return false;
	    if(fUseTOFMassCut){
		//Mass square!
		float TmpTOFMass = ReturnTOFMass(track,imost);
		if(TmpTOFMass == -999) return false;
	    	if(TmpTOFMass < TOFMassLowLimit || TmpTOFMass > TOFMassUpLimit){
			return false;
		}
	    }
            
            
        }
        
        //cout<<"AliFemtoTrackCutPdtHe3 "<<track->ImpactD()<<" "<<track->ImpactZ()<<endl;
        fNTracksPassed++ ;
        return true;
    
    }

    return false;

    
}
bool AliFemtoTrackCutPdtHe3::IsProtonNSigma(float mom, float nsigmaTPCP, float nsigmaTOFP){
    if (mom > SwitchMom_p) {
	        if (TMath::Hypot( nsigmaTOFP, nsigmaTPCP ) < fNsigmaP)
	            return true;	
	}
    else {
        if (TMath::Abs(nsigmaTPCP) < fNsigmaP)
            return true;
    }
    return false;

}
bool AliFemtoTrackCutPdtHe3::IsDeuteronNSigma(float mom, float massTOFPDG, float sigmaMass, float nsigmaTPCD, float nsigmaTOFD){
    //double massPDGD=1.8756;
    if (fNsigmaTPCTOF) {
        //Identyfication with only TPC for mom<1.4 and TPC&TOF for mom>1.4
        if (mom > SwitchMom_d){
            if (TMath::Hypot( nsigmaTPCD, nsigmaTOFD ) < fNsigmaD)
            //if ((TMath::Abs(nsigmaTPCD) < fNsigma) && (TMath::Abs(nsigmaTOFD) < fNsigma))
                return true;
        }
        else{
            if (TMath::Abs(nsigmaTPCD) < fNsigmaD)
                return true;
        }
        
    }
    else{
        if (TMath::Abs(nsigmaTPCD) < fNsigmaD)
            return true;
    } 
    return false;
}
bool AliFemtoTrackCutPdtHe3::IsTritonNSigma(float mom, float massTOFPDG, float sigmaMass, float nsigmaTPCT, float nsigmaTOFT){
    //double massPDGD=2.8089;
    if (fNsigmaTPCTOF) {
        //Identyfication with only TPC for mom<1.4 and TPC&TOF for mom>1.4
        if (mom > SwitchMom_t){
            if ((TMath::Abs(nsigmaTPCT) < fNsigmaT) && (TMath::Abs(nsigmaTOFT) < fNsigmaT))
                return true;
        }
        else{
            if (TMath::Abs(nsigmaTPCT) < fNsigmaT)
                return true;
        }
        
    }
    else{
        if (TMath::Abs(nsigmaTPCT) < fNsigmaT)
            return true;
    } 
    return false;
}
bool AliFemtoTrackCutPdtHe3::IsHe3NSigma(float mom, float massTOFPDG, float sigmaMass, float nsigmaTPCHe3, float nsigmaTOFHe3){
	//cout<<"IsHe3NSigma "<<nsigmaTPCHe3<<" "<<nsigmaTOFHe3<<endl;
    //double massPDGD=2.8089;
    if (fNsigmaTPCTOF) {
        if (mom > SwitchMom_He3){
            if ((TMath::Abs(nsigmaTPCHe3) < fNsigmaHe3) && (TMath::Abs(nsigmaTOFHe3) < fNsigmaHe3))
                return true;
        }
        else{
            if (TMath::Abs(nsigmaTPCHe3) < fNsigmaHe3)
                return true;
        }
    }
    else{
        if (TMath::Abs(nsigmaTPCHe3) < fNsigmaHe3)
            return true;
    }
    return false;
  
}

//rejection methods
bool AliFemtoTrackCutPdtHe3::IsElectronNSigmaRejection(float mom, float nsigmaTPCE){
  if(TMath::Abs(nsigmaTPCE) < fNsigmaRejection)
    return true;
 

  return false;
}

bool AliFemtoTrackCutPdtHe3::IsPionNSigmaRejection(float mom, float nsigmaTPCPi, float nsigmaTOFPi){
  if(fOnlyTPCreject){
    if(TMath::Abs(nsigmaTPCPi) < fNsigmaRejection)
      return true;
  }
  else{
    if(TMath::Hypot( nsigmaTOFPi, nsigmaTPCPi ) < fNsigmaRejection)
      return true;
  }

  return false;
}


bool AliFemtoTrackCutPdtHe3::IsKaonNSigmaRejection(float mom, float nsigmaTPCK, float nsigmaTOFK){
  if(fOnlyTPCreject){
    if(TMath::Abs(nsigmaTPCK) < fNsigmaRejection)
      return true;
  }
  else{
    if(TMath::Hypot( nsigmaTOFK, nsigmaTPCK ) < fNsigmaRejection)
      return true;
  }

  return false;
}

bool AliFemtoTrackCutPdtHe3::IsProtonNSigmaRejection(float mom, float nsigmaTPCP, float nsigmaTOFP){
  if(fOnlyTPCreject){
    if(TMath::Abs(nsigmaTPCP) < fNsigmaRejection)
      return true;
  }
  else{
    if(TMath::Hypot( nsigmaTOFP, nsigmaTPCP ) < fNsigmaRejection)
      return true;
  }
 
  return false;
}
void AliFemtoTrackCutPdtHe3::SetProtonSwitchMom(float SwitchMom){
	SwitchMom_p = SwitchMom;
}
void AliFemtoTrackCutPdtHe3::SetDeuteronSwitchMom(float SwitchMom){
	SwitchMom_d = SwitchMom;
}
void AliFemtoTrackCutPdtHe3::SetTritonSwitchMom(float SwitchMom){
	SwitchMom_t = SwitchMom;
}
void AliFemtoTrackCutPdtHe3::SetHe3SwitchMom(float SwitchMom){
	SwitchMom_He3 = SwitchMom;
}

//\ for e+e femto
bool AliFemtoTrackCutPdtHe3::IsElectronNSigma(float mom, float nsigmaTPCE, float nsigmaTOFE){

    if(TMath::Abs(nsigmaTPCE) < 3.) return true;
    return false;
}

void AliFemtoTrackCutPdtHe3::SetMostProbableElectron(){

    fMostProbable = 16; 
}
//\ follow wiola
bool AliFemtoTrackCutPdtHe3::IsDeuteronTPCdEdx(float mom, float dEdx){

//   double a1 = -250.0,  b1 = 400.0;
//   double a2 = -135.0,  b2 = 270.0;
//   double a3 = -80,   b3 = 190.0;
//   double a4 = 0.0,   b4 = 20.0;

//   double a5 = 125.0,   b5 = -100.0; 

//   if (mom < 1.1) {
//     if (dEdx < a1*mom+b1) return false;
//   }
//   else if (mom < 1.4) {
//     if (dEdx < a2*mom+b2) return false;
//   }
//   else if (mom < 2) {
//     if (dEdx < a3*mom+b3) return false;
//   }
//   else if (mom >= 2) {
//     if (dEdx < a4*mom+b4) return false;
//   }

    double a1 = -400./1.5,  b1 = 400.0;
    if (mom < 1.5) {
        if (dEdx < a1*mom+b1) return false;
    }
    return true;

}
bool AliFemtoTrackCutPdtHe3::IsTritonTPCdEdx(float mom, float dEdx){
    double a1 = -125.,  b1 = 350.;
    double a2 = -50.,  b2 = 200.;
    if (mom < 2) {
        if (dEdx < a1*mom+b1) return false;
    }
    else if (mom >= 2) {
        if (dEdx < a2*mom+b2) return false;
    }
    return true;

}

void AliFemtoTrackCutPdtHe3::SetdEdxcutLabel(int dEdxcutLabel){
    fdEdxcut = dEdxcutLabel;
}
void AliFemtoTrackCutPdtHe3::SetProtonNsigma(float Nsigma){
    fNsigmaP = Nsigma;
}
void AliFemtoTrackCutPdtHe3::SetDeuteronNsigma(float Nsigma){
    fNsigmaD = Nsigma;
}
void AliFemtoTrackCutPdtHe3::SetTritonNsigma(float Nsigma){
    fNsigmaT = Nsigma;
}
void AliFemtoTrackCutPdtHe3::SetHe3Nsigma(float Nsigma){
    fNsigmaHe3 = Nsigma;
}
void AliFemtoTrackCutPdtHe3::SetRejectionNsigma(float Nsigma){
    fNsigmaRejection = Nsigma;
}
void AliFemtoTrackCutPdtHe3::SetOtherNsigmacutLabel(int OtherNsigmaLabel){
    fOtherNsigmacut = OtherNsigmaLabel;
}
void AliFemtoTrackCutPdtHe3::SetMinTPCFoundFraction(float MinTPCFoundFraction){
    fMinTPCFoundFraction = MinTPCFoundFraction;
}
void AliFemtoTrackCutPdtHe3::SetUseTOFMassCut(int UseTOFMassCut){
    fUseTOFMassCut = UseTOFMassCut;
}
void AliFemtoTrackCutPdtHe3::SetTOFMassLimit(float LowMass,float UpMass){
    TOFMassLowLimit = LowMass;
    TOFMassUpLimit  = UpMass;  
}
float AliFemtoTrackCutPdtHe3::ReturnTOFMass(const AliFemtoTrack* track,int imost){
	float tMom = track->P().Mag();
	float c=1.;
	float beta = track->VTOF();
	float massTOF = -1.;//Mass square

	float imostMass = 0.;
	if(imost==4) 	imostMass = 0.938272;
	if(imost==13)	imostMass = 1.8756;
	if(imost==14)	imostMass = 2.8089;
	if(imost==15)	imostMass = 2.8084;

	if(beta!=0){
		massTOF = tMom*tMom/c/c*(1/(beta*beta)-1);  
		return  massTOF - imostMass*imostMass;
	}
	else{
		return -999;	
	}
	

}
void AliFemtoTrackCutPdtHe3::SetfUsePtCut(int aUsePtCut){
	fUsePtCut = aUsePtCut;
}
void AliFemtoTrackCutPdtHe3::SetfOnlyTPCreject(int aOnlyTPCreject){
	fOnlyTPCreject = aOnlyTPCreject;
}
bool AliFemtoTrackCutPdtHe3::RejectFakeP(const AliFemtoTrack* track, float mom){

	bool rejected = true;
	float p_NsigmaCombine = 0.;
	float k_NsigmaCombine = 0.;
	float e_NsigmaCombine = 0.;
	float pi_NsigmaCombine = 0.;
	if (mom > SwitchMom_p) {
		p_NsigmaCombine = TMath::Hypot(track->NSigmaTPCP(), track->NSigmaTOFP());
		k_NsigmaCombine = TMath::Hypot(track->NSigmaTPCK(), track->NSigmaTOFK());
		e_NsigmaCombine = TMath::Hypot(track->NSigmaTPCE(), track->NSigmaTOFE());
		pi_NsigmaCombine = TMath::Hypot(track->NSigmaTPCPi(), track->NSigmaTOFPi());
	        if ( 	(k_NsigmaCombine < p_NsigmaCombine) || 
			(e_NsigmaCombine < p_NsigmaCombine) || 
			(pi_NsigmaCombine < p_NsigmaCombine) )
	            return rejected;	
	}
    	else {
		p_NsigmaCombine = track->NSigmaTPCP();
		k_NsigmaCombine = track->NSigmaTPCK();
		e_NsigmaCombine = track->NSigmaTPCE();
		pi_NsigmaCombine = track->NSigmaTPCPi();
	        if ( 	(k_NsigmaCombine < p_NsigmaCombine) || 
			(e_NsigmaCombine < p_NsigmaCombine) || 
			(pi_NsigmaCombine < p_NsigmaCombine) )
	            return rejected;
    	}
	return false;

}
bool AliFemtoTrackCutPdtHe3::RejectFakeD(const AliFemtoTrack* track, float mom){

	bool rejected = true;
	float d_NsigmaCombine = 0.;
	float p_NsigmaCombine = 0.;
	float k_NsigmaCombine = 0.;
	float e_NsigmaCombine = 0.;
	float pi_NsigmaCombine = 0.;
	if (mom > SwitchMom_p) {
		d_NsigmaCombine = TMath::Hypot(track->NSigmaTPCD(), track->NSigmaTOFD());
		p_NsigmaCombine = TMath::Hypot(track->NSigmaTPCP(), track->NSigmaTOFP());
		k_NsigmaCombine = TMath::Hypot(track->NSigmaTPCK(), track->NSigmaTOFK());
		e_NsigmaCombine = TMath::Hypot(track->NSigmaTPCE(), track->NSigmaTOFE());
		pi_NsigmaCombine = TMath::Hypot(track->NSigmaTPCPi(), track->NSigmaTOFPi());
	        if ( 	(k_NsigmaCombine 	< d_NsigmaCombine) || 
			(e_NsigmaCombine 	< d_NsigmaCombine) || 
			(pi_NsigmaCombine 	< d_NsigmaCombine) ||
			(p_NsigmaCombine 	< d_NsigmaCombine) )
	            return rejected;	
	}
    	else {
		d_NsigmaCombine = track->NSigmaTPCD();      	
		p_NsigmaCombine = track->NSigmaTPCP();
		k_NsigmaCombine = track->NSigmaTPCK();
		e_NsigmaCombine = track->NSigmaTPCE();
		pi_NsigmaCombine = track->NSigmaTPCPi();
	        if ( 	(k_NsigmaCombine 	< d_NsigmaCombine) || 
			(e_NsigmaCombine 	< d_NsigmaCombine) || 
			(pi_NsigmaCombine 	< d_NsigmaCombine) ||
			(p_NsigmaCombine 	< d_NsigmaCombine) )
	            return rejected;
    	}
	return false;

}


