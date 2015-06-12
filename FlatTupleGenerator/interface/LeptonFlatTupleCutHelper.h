#ifndef DavisRunIITauTau_FlatTupleGenerator_LeptonFlatTupleCutHelper_h
#define DavisRunIITauTau_FlatTupleGenerator_LeptonFlatTupleCutHelper_h


/* class LeptonFlatTupleCutHelper :


contains functions to apply simple cuts at the FlatTuple 
production stage based on cms.PSet and NtupleEvent arguments


- Shalhout
*/



// system include files
#include <memory>
#include <assert.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// needed by ntuple Tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
 

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<edm::InputTag> VInputTag;

/* ranking comparator */



class LeptonFlatTupleCutHelper {


public:

  LeptonFlatTupleCutHelper();
  virtual ~LeptonFlatTupleCutHelper(){}


  void setEMuTauCutSets(edm::ParameterSet, edm::ParameterSet, edm::ParameterSet);
  bool pairPasses(NtupleEvent);
  bool checkMuon(NtupleLepton);
  bool checkElectron(NtupleLepton);
  bool checkTau(NtupleLepton);


private:
	edm::ParameterSet m_eCutSet;
	edm::ParameterSet m_muCutSet;
	edm::ParameterSet m_tauCutSet;
	


};

#endif
