#ifndef ALIRSNMINIPAIR_H
#define ALIRSNMINIPAIR_H

//
// This object is used as lightweight temporary container
// of all information needed from any input object and
// useful for resonance analysis.
//

#include <TObject.h>
#include <TLorentzVector.h>
#include <TRandom.h>
#include "TClonesArray.h"
#include "AliRsnListOutput.h"

class AliRsnListOutput;
class AliRsnMiniParticle;
class AliRsnMiniEvent;
class AliRsnDaughter;


class AliRsnMiniPair : public TObject {
public:

  AliRsnMiniPair() : fIndex1(-1), fIndex2(-1), fDCA1(0), fDCA2(0), fMother(-1), fMotherPDG(0), fNSisters(-1), fIsFromB(kFALSE), fIsQuarkFound(kFALSE),fContainsV0Daughter(kFALSE), fPassesOOBPileupCut(kFALSE), K0sIM(0) {for (Int_t i = 0; i<3; i++) fPmother[i] = 0.0;}
  
   Int_t          &Mother()    {return fMother;}
   Double_t       &K0IM()      {return K0sIM;} //added by prottay
   Long_t         &MotherPDG() {return fMotherPDG;}
   Bool_t         &IsFromB()      {return fIsFromB;}
   Bool_t         &IsQuarkFound() {return fIsQuarkFound;}
   Bool_t         &ContainsV0Daughter() {return fContainsV0Daughter;}
   Bool_t         &PassesOOBPileupCut() {return fPassesOOBPileupCut;}
   Float_t        &PmotherX()  {return fPmother[0];}
   Float_t        &PmotherY()  {return fPmother[1];}
   Float_t        &PmotherZ()  {return fPmother[2];} 
   void           Fill(AliRsnMiniParticle *p1, AliRsnMiniParticle *p2, Double_t m1, Double_t m2, Double_t refMass);
   void           FillRef(Double_t mass);
   void           InvertP(Bool_t first);

   Int_t          ID(Bool_t mc) const {if (mc) return 1; else return 0;}
   Int_t          &Index1() {return fIndex1;}    
   Int_t          &Index2() {return fIndex2;} 

   TLorentzVector &P1 (Bool_t mc) {return fP1 [ID(mc)];}
   TLorentzVector &P2 (Bool_t mc) {return fP2 [ID(mc)];}
   TLorentzVector &Sum(Bool_t mc) {return fSum[ID(mc)];}
   TLorentzVector &Ref(Bool_t mc) {return fRef[ID(mc)];}

   Double_t        Pt(Bool_t mc)             const  {return fSum[ID(mc)].Pt();}
   Double_t        Pz(Bool_t mc)             const  {return fSum[ID(mc)].Pz();}
   Double_t        Eta(Bool_t mc)            const  {return fSum[ID(mc)].Eta();}
   Double_t        InvMass(Bool_t mc)        const  {return fSum[ID(mc)].M();}
   Double_t        InvMassRes()              const;
   Double_t        InvMassDiff()             const;
   Double_t        Mt(Bool_t mc)             const  {return fRef[ID(mc)].Mt();}
   Double_t        Y(Bool_t mc)              const  {return fRef[ID(mc)].Rapidity();}
   Double_t        PtRatio(Bool_t mc)        const;
   Double_t        DipAngle(Bool_t mc)       const;
   Double_t        DeltaCos(Bool_t mc)       const;
   Double_t        CosThetaStar(Bool_t mc);
   Double_t        CosThetaStarAbs(Bool_t mc);
   Double_t        CosThetaHe(Bool_t mc);
   Double_t        CosThetaHeAbs(Bool_t mc);
   Double_t        CosThetaCsAbs(Bool_t mc);
   Double_t        PhiHePbPb5(Bool_t mc);
   Double_t        PhiHePP5(Bool_t mc);
   Double_t        CosThetaJackson(Bool_t mc);
   Double_t        CosThetaTransversity(Bool_t mc);
   Double_t        CosThetaToEventPlane(AliRsnMiniEvent *event, Bool_t mc);
   Double_t        PhiV(Bool_t mc); 
   Double_t        DaughterPt(Int_t daughterId, Bool_t mc);
   Double_t        DaughterIM(); 
   Double_t        DaughterDCA(Int_t daughterId); 
   Double_t        DCAProduct();                                                   
   void            DaughterPxPyPz(Int_t daughterId, Bool_t mc, Double_t *pxpypz); 
   Short_t         NSisters()  {return fNSisters;}
   Double_t        PairPtRes()              const;
   Double_t        PairYRes()               const;
   Double_t        PairAsymmetry(Bool_t mc); 
   Bool_t          ContainsIndex(Int_t index);


 private:
   
   TLorentzVector fP1 [2];    // 1st daughter momentum
   TLorentzVector fP2 [2];    // 2nd daughter momentum
   TLorentzVector fSum[2];    // sum of momenta
   TLorentzVector fRef[2];    // same as 'fSum' but with nominal resonance mass
   
   Double_t       fDCA1;      // 1st daughter DCA
   Double_t       fDCA2;      // 2nd daughter DCA 
   Int_t          fIndex1;    //ID 1st daughter
   Int_t          fIndex2;    //ID 2nd daughter
   
   Int_t          fMother;    // label of mothers (when common)
   Long_t         fMotherPDG; // PDG code of mother (when common)
   Short_t        fNSisters;  // total number of mother's daughters in the MC stack
   Bool_t         fIsFromB;	      // is the particle from B meson flag	
   Bool_t         fIsQuarkFound;      // is the particle from a quark flag (used to reject or accept Hijing event)
   Float_t        fPmother[3];// MC momentum of the pair corresponding mother
   Bool_t         fContainsV0Daughter; // Flag if one of particle is part of V0's daughter
   Bool_t         fPassesOOBPileupCut; // At least one daughter passes the out-of-bunch pileup cut
   Double_t       K0sIM;      // K0s IM (by prottay)
  
   ClassDef(AliRsnMiniPair, 7)
     };

#endif
