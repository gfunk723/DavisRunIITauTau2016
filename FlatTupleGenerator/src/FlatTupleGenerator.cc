/* FlatTupleGenerator imp */
#include "DavisRunIITauTau/FlatTupleGenerator/interface/FlatTupleGenerator.h" 
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "TMatrix.h"
//#include <signal.h>


////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


FlatTupleGenerator::FlatTupleGenerator(const edm::ParameterSet& iConfig):
pairSrc_(iConfig.getParameter<vInputTag>("pairSrc")),
indepSrc_(iConfig.getParameter<edm::InputTag>("indepSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
FillEffLeptonBranches_(iConfig.getParameter<bool>("FillEffLeptonBranches")),
RECOILCORRECTION_(iConfig.getParameter<string>("RecoilCorrection" )),
MetSystematicType_(iConfig.getParameter<string>("MetSystematicType" )),
KeepTheoryScaleFactors_(iConfig.getParameter<bool>("KeepTheoryScaleFactors" )),
EventCutSrc_(iConfig.getParameter<edm::ParameterSet>("EventCutSrc")),
TauEsVariantToKeep_(iConfig.getParameter<string>("TauEsVariantToKeep")),
ElectronEsVariantToKeep_(iConfig.getParameter<string>("ElectronEsVariantToKeep")),
LeptonCutVecSrc_(iConfig.getParameter<std::vector<edm::ParameterSet>>("LeptonCutVecSrc")),
BoostedLeptonCutVecSrc_(iConfig.getParameter<std::vector<edm::ParameterSet>>("BoostedLeptonCutVecSrc")),
svMassAtFlatTupleConfig_(iConfig.getParameter<edm::ParameterSet>("SVMassConfig"))
{

  for(vInputTag::const_iterator it=pairSrc_.begin();it!=pairSrc_.end();it++) 
  {
    pairToken_.push_back( consumes< edm::View< NtupleEvent > >( *it ) );
  }

  indepToken_ = consumes < edm::View<NtuplePairIndependentInfo> >(indepSrc_);


  /* read in the svMassAtFlatTupleConfig_ parameters */

  USE_MVAMET_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_FOR_SVFit_AT_FlatTuple_");
  USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple_");
  USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple_");
  USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple_");
  USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple_");
  USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple_");
  USE_PFMET_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_PFMET_FOR_SVFit_AT_FlatTuple_");
  USE_PUPPIMET_FOR_SVFit_AT_FlatTuple = svMassAtFlatTupleConfig_.getParameter<bool>("USE_PUPPIMET_FOR_SVFit_AT_FlatTuple_");
  flatTuple_svMassVerbose = svMassAtFlatTupleConfig_.getParameter<bool>("flatTuple_svMassVerbose");
  flatTuple_logMterm = svMassAtFlatTupleConfig_.getParameter<double>("flatTuple_logMterm");


	/* read in the EventCutSrc varaibles */

	tauIDsToKeep = EventCutSrc_.getParameter<std::vector<std::string> >("tauIDsToKeep"); 
  assert(THE_MAX>=tauIDsToKeep.size());

  triggerSummaryChecks = EventCutSrc_.getParameter<std::vector<std::string> >("triggerSummaryChecks"); 
  assert(THE_MAX>=triggerSummaryChecks.size());

  SmallTree_ = EventCutSrc_.getParameter<bool>("SmallTree");
  BuildEffTree_ = EventCutSrc_.getParameter<bool>("BuildEffTree");

  BuildEleEle_ = EventCutSrc_.getParameter<bool>("BuildEleEle");
  BuildEleMuon_ = EventCutSrc_.getParameter<bool>("BuildEleMuon");
  BuildEleTau_ = EventCutSrc_.getParameter<bool>("BuildEleTau");
  BuildMuonMuon_ = EventCutSrc_.getParameter<bool>("BuildMuonMuon");
  BuildMuonTau_ = EventCutSrc_.getParameter<bool>("BuildMuonTau");
  BuildTauTau_ = EventCutSrc_.getParameter<bool>("BuildTauTau");


  keepOnlyBestRankedPair = EventCutSrc_.getParameter<bool>("keepOnlyBestRankedPair");
	keepOS = EventCutSrc_.getParameter<bool>("keepOS");
	keepSS = EventCutSrc_.getParameter<bool>("keepSS");
	
  assert(TauEsVariantToKeep_=="NOMINAL" || TauEsVariantToKeep_=="UP" || TauEsVariantToKeep_=="DOWN");
  keepTauEsNominal = 0;
  keepTauEsUp = 0;
  keepTauEsDown = 0;
  
  if( TauEsVariantToKeep_=="NOMINAL" ) keepTauEsNominal = 1;
  else if( TauEsVariantToKeep_=="UP" ) keepTauEsUp = 1;
  else if( TauEsVariantToKeep_=="DOWN" ) keepTauEsDown = 1;


  assert(ElectronEsVariantToKeep_=="NOMINAL" || ElectronEsVariantToKeep_=="UP" || ElectronEsVariantToKeep_=="DOWN");
  keepElectronEsNominal = 0;
  keepElectronEsUp = 0;
  keepElectronEsDown = 0;
  
  if( ElectronEsVariantToKeep_=="NOMINAL" ) keepElectronEsNominal = 1;
  else if( ElectronEsVariantToKeep_=="UP" ) keepElectronEsUp = 1;
  else if( ElectronEsVariantToKeep_=="DOWN" ) keepElectronEsDown = 1;





  rankByPtSum = EventCutSrc_.getParameter<bool>("rankByPtSum");
	rankByIsolation = EventCutSrc_.getParameter<bool>("rankByIsolation");
	assert(rankByPtSum!=rankByIsolation);
	
  electronIsolationForRank = EventCutSrc_.getParameter<std::string>("electronIsolationForRank");
  electron_isSmallerValueMoreIsolated  = EventCutSrc_.getParameter<bool>("electron_isSmallerValueMoreIsolated");

	muonIsolationForRank = EventCutSrc_.getParameter<std::string>("muonIsolationForRank");
  muon_isSmallerValueMoreIsolated  = EventCutSrc_.getParameter<bool>("muon_isSmallerValueMoreIsolated");

	tauIDisolationForRank = EventCutSrc_.getParameter<std::string>("tauIDisolationForRank");
  tau_isSmallerValueMoreIsolated  = EventCutSrc_.getParameter<bool>("tau_isSmallerValueMoreIsolated");

  electronIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("electronIsolationForRelIsoBranch");
  muonIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("muonIsolationForRelIsoBranch");

  tauIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("tauIsolationForRelIsoBranch");
  tauIsolationForRelIsoBranch_forEleTau = EventCutSrc_.getParameter<std::string>("tauIsolationForRelIsoBranch_forEleTau");
  tauIsolationForRelIsoBranch_forMuTau = EventCutSrc_.getParameter<std::string>("tauIsolationForRelIsoBranch_forMuTau");
  tauIsolationForRelIsoBranch_forTauTau = EventCutSrc_.getParameter<std::string>("tauIsolationForRelIsoBranch_forTauTau");







  vetoElectronIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("vetoElectronIsolationForRelIsoBranch");
  vetoMuonIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("vetoMuonIsolationForRelIsoBranch");

  jetIDcut  = EventCutSrc_.getParameter<std::string>("jetIDcut");
  jetLeptonDRmin = EventCutSrc_.getParameter<double>("jetLeptonDRmin");

  thirdEleVeto  = EventCutSrc_.getParameter<std::string>("thirdEleVeto");
  thirdMuonVeto  = EventCutSrc_.getParameter<std::string>("thirdMuonVeto");
  legThirdLeptonMinDR = EventCutSrc_.getParameter<double>("legThirdLeptonMinDR");

  diEleVeto  = EventCutSrc_.getParameter<std::string>("diEleVeto");
  diMuonVeto  = EventCutSrc_.getParameter<std::string>("diMuonVeto");
  diLeptonMinDR = EventCutSrc_.getParameter<double>("diLeptonMinDR");




  /* create all pairs needed for EffLepton tauID and HLT info */


  for(int q = 0; q < THE_MAX; ++q)
  {
    std::vector<float> ATEMP;
    effLep_tauIDs.push_back(std::make_pair(q, ATEMP) );    
    effLep_GoodForHLTPath.push_back(std::make_pair(q, ATEMP) );    
  }

  /* create pair needed for the veto lepton tauID info */

  for(int q = 0; q < THE_MAX; ++q)
  {
    std::vector<float> ATEMP;
    veto_tauIDs.push_back(std::make_pair(q, ATEMP) );    
  }  

  /* setup the btag sf helper tool */

  LooseCut = EventCutSrc_.getParameter<double>("LooseBtagWPcut");
  MediumCut = EventCutSrc_.getParameter<double>("MediumBtagWPcut");
  TightCut = EventCutSrc_.getParameter<double>("TightBtagWPcut");

  sf_fileString = EventCutSrc_.getParameter<std::string>("BtagSF_File");
  looseEff_fileString = EventCutSrc_.getParameter<std::string>("looseBtagEff_file");
  mediumEff_fileString = EventCutSrc_.getParameter<std::string>("mediumBtagEff_file");
  tightEff_fileString = EventCutSrc_.getParameter<std::string>("tightBtagEff_file");

  sf_file = edm::FileInPath(sf_fileString);
  looseEff_file = edm::FileInPath(looseEff_fileString);
  mediumEff_file = edm::FileInPath(mediumEff_fileString);
  tightEff_file = edm::FileInPath(tightEff_fileString); /* for 76X same as med */

  std::cout<<" Instance of FlatTupleGenerator for "<<NAME_<<"\n";
  std::cout<<" **** Setting up Btag Tool with \n";
  std::cout<<" [L, M, T] b-tag cut points set to [ "<<LooseCut<<" , "<<MediumCut<<" , "<<TightCut<<" ] \n";
  std::cout<<" with SF CSV file : "<<sf_fileString<<"\n ";
  std::cout<<" with loose EFF root file : "<<looseEff_fileString<<"\n ";
  std::cout<<" with medium EFF root file : "<<mediumEff_fileString<<"\n ";
  std::cout<<" with tight EFF root file : "<<tightEff_fileString<<" (same as medium for 76X ) \n";


  /* ROOT data files for btag SF */
  TFile m_LooseBtagEff(looseEff_file.fullPath().data(),"READ");
  TFile m_MediumBtagEff(mediumEff_file.fullPath().data(),"READ");
  TFile m_TightBtagEff(tightEff_file.fullPath().data(),"READ");

  /* get, clone, and delete pointers to b-tag sf histograms */

  TH2F * p_LooseEff_b = (TH2F*) m_LooseBtagEff.Get("btag_eff_b");
  p_LooseEff_b->SetDirectory(0);
  m_LooseEff_b = *p_LooseEff_b;
  m_LooseEff_b.SetDirectory(0);
  p_LooseEff_b->Delete();
    

  TH2F * p_LooseEff_c = (TH2F*) m_LooseBtagEff.Get("btag_eff_c");
  p_LooseEff_c->SetDirectory(0);
  m_LooseEff_c = *p_LooseEff_c;
  m_LooseEff_c.SetDirectory(0);
  p_LooseEff_c->Delete();


  TH2F * p_LooseEff_usdg = (TH2F*) m_LooseBtagEff.Get("btag_eff_oth");
  p_LooseEff_usdg->SetDirectory(0);
  m_LooseEff_usdg = *p_LooseEff_usdg;
  m_LooseEff_usdg.SetDirectory(0);
  p_LooseEff_usdg->Delete();  

  TH2F * p_MediumEff_b = (TH2F*) m_MediumBtagEff.Get("btag_eff_b");
  p_MediumEff_b->SetDirectory(0);
  m_MediumEff_b = *p_MediumEff_b;
  m_MediumEff_b.SetDirectory(0);
  p_MediumEff_b->Delete();
    

  TH2F * p_MediumEff_c = (TH2F*) m_MediumBtagEff.Get("btag_eff_c");
  p_MediumEff_c->SetDirectory(0);
  m_MediumEff_c = *p_MediumEff_c;
  m_MediumEff_c.SetDirectory(0);
  p_MediumEff_c->Delete();


  TH2F * p_MediumEff_usdg = (TH2F*) m_MediumBtagEff.Get("btag_eff_oth");
  p_MediumEff_usdg->SetDirectory(0);
  m_MediumEff_usdg = *p_MediumEff_usdg;
  m_MediumEff_usdg.SetDirectory(0);
  p_MediumEff_usdg->Delete();  

  TH2F * p_TightEff_b = (TH2F*) m_TightBtagEff.Get("btag_eff_b");
  p_TightEff_b->SetDirectory(0);
  m_TightEff_b = *p_TightEff_b;
  m_TightEff_b.SetDirectory(0);
  p_TightEff_b->Delete();
    

  TH2F * p_TightEff_c = (TH2F*) m_TightBtagEff.Get("btag_eff_c");
  p_TightEff_c->SetDirectory(0);
  m_TightEff_c = *p_TightEff_c;
  m_TightEff_c.SetDirectory(0);
  p_TightEff_c->Delete();

  TH2F * p_TightEff_usdg = (TH2F*) m_TightBtagEff.Get("btag_eff_oth");
  p_TightEff_usdg->SetDirectory(0);
  m_TightEff_usdg = *p_TightEff_usdg;
  m_TightEff_usdg.SetDirectory(0);
  p_TightEff_usdg->Delete();  

  m_LooseBtagEff.Close();
  m_MediumBtagEff.Close();
  m_TightBtagEff.Close();

  /* setup the b-tag calibration tool & readers */

  BTagCalibration m_calib("csvv2", sf_file.fullPath());
  
  /* mujets */
  BTagCalibrationReader m_LooseWpReaderAllVariants_forB( BTagEntry::OP_LOOSE,"central", {"up", "down"});
  BTagCalibrationReader m_MediumWpReaderAllVariants_forB( BTagEntry::OP_MEDIUM,"central", {"up", "down"});
  BTagCalibrationReader m_TightWpReaderAllVariants_forB( BTagEntry::OP_TIGHT,"central", {"up", "down"});

  /* mujets */
  BTagCalibrationReader m_LooseWpReaderAllVariants_forC( BTagEntry::OP_LOOSE,"central", {"up", "down"});
  BTagCalibrationReader m_MediumWpReaderAllVariants_forC( BTagEntry::OP_MEDIUM,"central", {"up", "down"});
  BTagCalibrationReader m_TightWpReaderAllVariants_forC( BTagEntry::OP_TIGHT,"central", {"up", "down"});

  /* incl */
  BTagCalibrationReader m_LooseWpReaderAllVariants_forUDSG( BTagEntry::OP_LOOSE,"central", {"up", "down"});
  BTagCalibrationReader m_MediumWpReaderAllVariants_forUDSG( BTagEntry::OP_MEDIUM,"central", {"up", "down"});
  BTagCalibrationReader m_TightWpReaderAllVariants_forUDSG( BTagEntry::OP_TIGHT,"central", {"up", "down"});
  
  // m_LooseWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "mujets");             
  // m_MediumWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "mujets");             
  // m_TightWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "mujets");           

  // m_LooseWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "mujets");             
  // m_MediumWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "mujets");             
  // m_TightWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "mujets");      

  /* wisconsin uses comb not mujets */
  m_LooseWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "comb");             
  m_MediumWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "comb");             
  m_TightWpReaderAllVariants_forB.load(m_calib, BTagEntry::FLAV_B, "comb");           

  m_LooseWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "comb");             
  m_MediumWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "comb");             
  m_TightWpReaderAllVariants_forC.load(m_calib, BTagEntry::FLAV_C, "comb");  


  m_LooseWpReaderAllVariants_forUDSG.load(m_calib, BTagEntry::FLAV_UDSG, "incl");             
  m_MediumWpReaderAllVariants_forUDSG.load(m_calib, BTagEntry::FLAV_UDSG, "incl");             
  m_TightWpReaderAllVariants_forUDSG.load(m_calib, BTagEntry::FLAV_UDSG, "incl");      

  /* setup btag SF tool */


  m_BtagSFTool = new bTagSFhelper(m_calib, looseEff_file, mediumEff_file, tightEff_file, 
                      LooseCut, MediumCut, TightCut,
                      m_LooseEff_b, m_LooseEff_c, m_LooseEff_usdg, 
                      m_MediumEff_b, m_MediumEff_c, m_MediumEff_usdg, 
                      m_TightEff_b, m_TightEff_c, m_TightEff_usdg,
                      m_LooseWpReaderAllVariants_forB,
                      m_MediumWpReaderAllVariants_forB,
                      m_TightWpReaderAllVariants_forB, 
                      m_LooseWpReaderAllVariants_forC,
                      m_MediumWpReaderAllVariants_forC,
                      m_TightWpReaderAllVariants_forC, 
                      m_LooseWpReaderAllVariants_forUDSG, 
                      m_MediumWpReaderAllVariants_forUDSG,
                      m_TightWpReaderAllVariants_forUDSG);


  /* setup the SVFit ResolutionPDF file */

  edm::FileInPath inputFileName_visPtResolution("TauAnalysis/SVfitStandalone/data/svFitVisMassAndPtResolutionPDF.root");
  TH1::AddDirectory(false);  
  inputFile_visPtResolution = new TFile(inputFileName_visPtResolution.fullPath().data());

  std::cout<<"********************************************************************************\n";
  std::cout<<" ******* svFitVisMassAndPtResolutionPDF mass and resolution file is \n";
  std::cout<<inputFileName_visPtResolution.fullPath().data()<<"\n";
  std::cout<<" Change in FlatTupleGenerator.cc if not current \n";
  std::cout<<"********************************************************************************\n";

  /* setup the met systematic tool */


  m_metSys = new MEtSys("HTT-utilities/RecoilCorrections/data/MEtSys.root");

  std::cout<<"********************************************************************************\n";
  std::cout<<" ******* Met SYSTEMATIC TOOL ROOT FILE IS : HTT-utilities/RecoilCorrections/data/MEtSys.root \n";
  std::cout<<" Change in FlatTupleGenerator.cc if not current \n";
  std::cout<<"********************************************************************************\n";


  /* setup the recoil correction tool :
  valid correction options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE */
    
  assert(RECOILCORRECTION_=="aMCatNLO_DY" || RECOILCORRECTION_=="aMCatNLO_W" || RECOILCORRECTION_=="MG5_DY"||\
         RECOILCORRECTION_=="MG5_W" || RECOILCORRECTION_=="HIGGS"|| RECOILCORRECTION_=="NONE");

  std::string fnameMVA = "HTT-utilities/RecoilCorrections/data/MvaMET_2016BCD.root";
  std::string fnamePF = "HTT-utilities/RecoilCorrections/data/TypeIPFMET_2016BCD.root";



  // if(RECOILCORRECTION_=="HIGGS" || RECOILCORRECTION_=="MG5_DY" || RECOILCORRECTION_=="MG5_W")
  // {
  //   fnameMVA = "HTT-utilities/RecoilCorrections/data/recoilMvaMEt_76X_newTraining_MG5.root";
  // }
  // else if(RECOILCORRECTION_=="aMCatNLO_DY" || RECOILCORRECTION_=="aMCatNLO_W")
  // {
  //   fnameMVA = "HTT-utilities/RecoilCorrections/data/recoilMvaMEt_76X_newTraining.root";
  // }

  /* not used if RECOILCORRECTION_==NONE, but need a valid file to initialize */
  m_recoilMvaMetCorrector = new RecoilCorrector(fnameMVA); 
  m_recoilPfMetCorrector = new RecoilCorrector(fnamePF); 

  std::cout<<"********************************************************************************\n";
  std::cout<<" ******* MVA Met RECOIL Correction TOOL ROOT FILE IS : "<<fnameMVA<<"\n";
  std::cout<<" ******* PF Met RECOIL Correction TOOL ROOT FILE IS : "<<fnamePF<<"\n";
  std::cout<<" Change in FlatTupleGenerator.cc if not current \n";
  std::cout<<"********************************************************************************\n";


}


//////////////////////////////////////////////////
// class destructor 
//////////////////////////////////////////////////

FlatTupleGenerator::~FlatTupleGenerator()
{ 
  delete m_BtagSFTool;
  inputFile_visPtResolution->Close();
  delete inputFile_visPtResolution;
  delete m_metSys;
  delete m_recoilMvaMetCorrector;
  delete m_recoilPfMetCorrector;
}

//////////////////////////////////////////////////
// ------------ method called for each event  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

//raise(SIGSEGV);
   using namespace edm;


  //////////////
  // init values

  reInit();


  ///////////////
  // get inputs 

  edm::Handle< edm::View<NtuplePairIndependentInfo> > pairIndepInfos;
  iEvent.getByToken(indepToken_, pairIndepInfos);



  ///////////////////////////////////////////
  // for each event, store a vector of NtupleEvent (i.e. pair)
  // objects that pass the specified selection 
  // this is done separately for each channel (and boosted and resolved) since they are ranked
  // indep. from each other
  // only after failing to find a resolved pair will a boosted pair be accepted (separately in each channel)


  /* for resolved pairs */

  std::vector<NtupleEvent> resolvedPairs_EleTau;
  resolvedPairs_EleTau.clear();

  std::vector<NtupleEvent> resolvedPairs_MuonTau;
  resolvedPairs_MuonTau.clear();

  std::vector<NtupleEvent> resolvedPairs_TauTau;
  resolvedPairs_TauTau.clear();

  std::vector<NtupleEvent> resolvedPairs_EleMuon;
  resolvedPairs_EleMuon.clear();

  std::vector<NtupleEvent> resolvedPairs_EleEle;
  resolvedPairs_EleEle.clear();

  std::vector<NtupleEvent> resolvedPairs_MuonMuon;
  resolvedPairs_MuonMuon.clear();


  /* for boosted pairs */

  std::vector<NtupleEvent> boostedPairs_EleTau;
  boostedPairs_EleTau.clear();

  std::vector<NtupleEvent> boostedPairs_MuonTau;
  boostedPairs_MuonTau.clear();

  std::vector<NtupleEvent> boostedPairs_TauTau;
  boostedPairs_TauTau.clear();

  std::vector<NtupleEvent> boostedPairs_EleMuon;
  boostedPairs_EleMuon.clear();

  std::vector<NtupleEvent> boostedPairs_EleEle;
  boostedPairs_EleEle.clear();

  std::vector<NtupleEvent> boostedPairs_MuonMuon;
  boostedPairs_MuonMuon.clear();


  /* combined pairs : will hold resolved, and if none are found will add in boosted */

  std::vector<NtupleEvent> retainedPairs_EleTau;
  retainedPairs_EleTau.clear();

  std::vector<NtupleEvent> retainedPairs_MuonTau;
  retainedPairs_MuonTau.clear();

  std::vector<NtupleEvent> retainedPairs_TauTau;
  retainedPairs_TauTau.clear();

  std::vector<NtupleEvent> retainedPairs_EleMuon;
  retainedPairs_EleMuon.clear();

  std::vector<NtupleEvent> retainedPairs_EleEle;
  retainedPairs_EleEle.clear();

  std::vector<NtupleEvent> retainedPairs_MuonMuon;
  retainedPairs_MuonMuon.clear();







/* loop through pairs and store those that pass cuts in the vectors split by channel */

for ( std::vector<edm::EDGetTokenT<edm::View< NtupleEvent > > >::const_iterator pairToken_i = pairToken_.begin(); 
        pairToken_i != pairToken_.end(); ++pairToken_i )
  {
    edm::Handle< edm::View< NtupleEvent > > pairs;
    iEvent.getByToken(*pairToken_i, pairs);
    

    for(std::size_t p = 0; p<pairs->size(); ++p )
    {

      NtupleEvent currentPairToCheck =   ((*pairs)[p]);


      if(currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::EffCand && FillEffLeptonBranches_) 
      {
          //      std::cout<<" have an EffLepton candidate \n";      

        //////////////////////////////////////////////////////////////////////
        // fill the TTree for a EffLepton list                              //
        //////////////////////////////////////////////////////////////////////


        //////////////////////////////////
        // access pair indep info       //

        NtuplePairIndependentInfo currentINDEP =   ((*pairIndepInfos)[0]);


        /////////////////////////////////////////////////////////////////////
        // init the JetHelper and GenHelper tools and fill pairIndep info  //
        // once per pair note: GenHelper and JetHelper                     // 
        // tools **must** be inititalized                                  //
        // before calling handleXXXX type functions                        //  
        /////////////////////////////////////////////////////////////////////

        if(currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::EffCand) 
        {


          // bTagSFhelper m_BtagSFTool(sf_file, looseEff_file, mediumEff_file, tightEff_file, 
          //               LooseCut, MediumCut, TightCut );


          jethelper.init(currentINDEP.jets(),jetIDcut, m_BtagSFTool, iEvent.isRealData());

          genhelper.init(currentINDEP.genParticles(),currentPairToCheck.EffLepton(),
                       currentPairToCheck.CandidateEventType());

        }

        /* the order of the handleXXX calls matters! 
        switching them around will cause problems */

        handlePairIndepInfo(iEvent,iSetup,currentINDEP);
        handleCurrentEventInfo(iEvent,iSetup,currentPairToCheck);      
        handleEffLeptonInfo(iEvent,iSetup,currentPairToCheck); 

        // std::cout<<" FILL EffCandidate! \n";
        FlatTuple->Fill();

      } // eff lepton


      else if(currentPairToCheck.CandidateEventType()!=TupleCandidateEventTypes::EffCand) 
      {

        // std::cout<<" have a regular pair candidate \n";      

        //////////////////////////////////////////////////////////////////////
        // fill the TTree for a regular H->tau tau pair candidate           //
        //////////////////////////////////////////////////////////////////////

        bool keepSignPair = ((keepOS && currentPairToCheck.isOsPair()==1) || (keepSS && currentPairToCheck.isOsPair()!=1));
      
        bool keepTauEsVariant = (
               (keepTauEsNominal && currentPairToCheck.TauEsNumberSigmasShifted()==0.0) ||
               (keepTauEsNominal && isnan(currentPairToCheck.TauEsNumberSigmasShifted())) || /* for eMu, muMu, EleEle */
               (keepTauEsUp && currentPairToCheck.TauEsNumberSigmasShifted()==1.0) ||
               (keepTauEsDown && currentPairToCheck.TauEsNumberSigmasShifted()==-1.0) 
        );


        bool keepElectronEsVariant = (
               (keepElectronEsNominal && currentPairToCheck.ElectronEsNumberSigmasShifted()==0.0) ||
               (keepElectronEsNominal && isnan(currentPairToCheck.ElectronEsNumberSigmasShifted())) || /* for muTau, eleTau, TauTau, MuMu */
               (keepElectronEsUp && currentPairToCheck.ElectronEsNumberSigmasShifted()==1.0) ||
               (keepElectronEsDown && currentPairToCheck.ElectronEsNumberSigmasShifted()==-1.0) 
        );


        bool buildPairTypeCheck = (
              (BuildEleEle_   && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::EleEle)  ||
              (BuildEleMuon_  && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::EleMuon) ||
              (BuildEleTau_   && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::EleTau)  ||
              (BuildMuonMuon_ && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::MuonMuon)|| 
              (BuildMuonTau_  && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::MuonTau) ||
              (BuildTauTau_   && currentPairToCheck.CandidateEventType()==TupleCandidateEventTypes::TauTau) 
        );




        /* check if the cuts pass */

        bool isBoosted = currentPairToCheck.isBoostedChannel();


        bool leptonCutsPass = 0;

        if(!isBoosted) leptonCutsPass = LeptonCutHelper.cutEvaluator(currentPairToCheck, LeptonCutVecSrc_);
        else leptonCutsPass = LeptonCutHelper.cutEvaluator(currentPairToCheck, BoostedLeptonCutVecSrc_);

        ///////////////////
        if(keepSignPair && keepTauEsVariant && leptonCutsPass && keepElectronEsVariant && buildPairTypeCheck) 
        {
          if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::EleTau) 
          { 
            if(!isBoosted) resolvedPairs_EleTau.push_back(currentPairToCheck);
            else boostedPairs_EleTau.push_back(currentPairToCheck);
          }

          else if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::MuonTau) 
          { 
            if(!isBoosted) resolvedPairs_MuonTau.push_back(currentPairToCheck);
            else boostedPairs_MuonTau.push_back(currentPairToCheck);
          }
         
          else if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::TauTau) 
          { 
            if(!isBoosted) resolvedPairs_TauTau.push_back(currentPairToCheck);
            else boostedPairs_TauTau.push_back(currentPairToCheck);
          }

          else if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::EleMuon) 
          { 
            if(!isBoosted) resolvedPairs_EleMuon.push_back(currentPairToCheck);      
            else boostedPairs_EleMuon.push_back(currentPairToCheck);      
          }

          else if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::EleEle) 
          { 
            if(!isBoosted) resolvedPairs_EleEle.push_back(currentPairToCheck);      
            else boostedPairs_EleEle.push_back(currentPairToCheck);      
          }

          else if(currentPairToCheck.CandidateEventType() == TupleCandidateEventTypes::MuonMuon) 
          { 
            if(!isBoosted) resolvedPairs_MuonMuon.push_back(currentPairToCheck);      
            else boostedPairs_MuonMuon.push_back(currentPairToCheck);       
          }
       
        } // passes cuts
       

      } // not eff cand 

    } // loop on pairs

  } // loop on pairSrc vector 
  /////////////////////////

  /* now that we have 2 vectors (resolved & boosted) for each channel we poplulate the 
  combinde (retained) vector.

    --> the preference will be for resolved
    --> the boosted pairs will be pushed in only if the resolved vector is empty 
  */



  concatenateVectors(resolvedPairs_EleTau, boostedPairs_EleTau, retainedPairs_EleTau);
  //std::cout<<" resolved, boosted, retained in channel EleTau : "<<resolvedPairs_EleTau.size()<<" "<<boostedPairs_EleTau.size()<<" "<<retainedPairs_EleTau.size()<<"\n";
  resolvedPairs_EleTau.clear();
  boostedPairs_EleTau.clear();

  concatenateVectors(resolvedPairs_MuonTau, boostedPairs_MuonTau, retainedPairs_MuonTau);
  //std::cout<<" resolved, boosted, retained in channel MuonTau : "<<resolvedPairs_MuonTau.size()<<" "<<boostedPairs_MuonTau.size()<<" "<<retainedPairs_MuonTau.size()<<"\n";
  resolvedPairs_MuonTau.clear();
  boostedPairs_MuonTau.clear();

  concatenateVectors(resolvedPairs_TauTau, boostedPairs_TauTau, retainedPairs_TauTau);
  //std::cout<<" resolved, boosted, retained in channel TauTau : "<<resolvedPairs_TauTau.size()<<" "<<boostedPairs_TauTau.size()<<" "<<retainedPairs_TauTau.size()<<"\n";
  resolvedPairs_TauTau.clear();
  boostedPairs_TauTau.clear();

  concatenateVectors(resolvedPairs_EleMuon, boostedPairs_EleMuon, retainedPairs_EleMuon);
  //std::cout<<" resolved, boosted, retained in channel EleMuon : "<<resolvedPairs_EleMuon.size()<<" "<<boostedPairs_EleMuon.size()<<" "<<retainedPairs_EleMuon.size()<<"\n";
  resolvedPairs_EleMuon.clear();
  boostedPairs_EleMuon.clear();

  concatenateVectors(resolvedPairs_EleEle, boostedPairs_EleEle, retainedPairs_EleEle);
  //std::cout<<" resolved, boosted, retained in channel EleEle : "<<resolvedPairs_EleEle.size()<<" "<<boostedPairs_EleEle.size()<<" "<<retainedPairs_EleEle.size()<<"\n";
  resolvedPairs_EleEle.clear();
  boostedPairs_EleEle.clear();

  concatenateVectors(resolvedPairs_MuonMuon, boostedPairs_MuonMuon, retainedPairs_MuonMuon);
  //std::cout<<" resolved, boosted, retained in channel MuonMuon : "<<resolvedPairs_MuonMuon.size()<<" "<<boostedPairs_MuonMuon.size()<<" "<<retainedPairs_MuonMuon.size()<<"\n";
  resolvedPairs_MuonMuon.clear();
  boostedPairs_MuonMuon.clear();

  /////////////////////////
  // next figure out how to rank the pairs 


  PairRankHelper rankHelper_EleMuon;
  PairRankHelper rankHelper_EleTau;
  PairRankHelper rankHelper_MuonTau;
  PairRankHelper rankHelper_TauTau;
  PairRankHelper rankHelper_EleEle;
  PairRankHelper rankHelper_MuonMuon;


  if(rankByPtSum) 
  {
    rankHelper_EleMuon.init(retainedPairs_EleMuon);
    rankHelper_EleTau.init(retainedPairs_EleTau);
    rankHelper_MuonTau.init(retainedPairs_MuonTau);
    rankHelper_TauTau.init(retainedPairs_TauTau);
    rankHelper_EleEle.init(retainedPairs_EleEle);
    rankHelper_MuonMuon.init(retainedPairs_MuonMuon);

  }

  else if(rankByIsolation) 
  {
    rankHelper_EleMuon.init(retainedPairs_EleMuon,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      electron_isSmallerValueMoreIsolated, muon_isSmallerValueMoreIsolated);

    rankHelper_EleTau.init(retainedPairs_EleTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      electron_isSmallerValueMoreIsolated, tau_isSmallerValueMoreIsolated);

    rankHelper_MuonTau.init(retainedPairs_MuonTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      muon_isSmallerValueMoreIsolated, tau_isSmallerValueMoreIsolated);

    rankHelper_TauTau.init(retainedPairs_TauTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      tau_isSmallerValueMoreIsolated, tau_isSmallerValueMoreIsolated);

    rankHelper_EleEle.init(retainedPairs_EleEle,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      electron_isSmallerValueMoreIsolated, electron_isSmallerValueMoreIsolated);

    rankHelper_MuonMuon.init(retainedPairs_MuonMuon,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank,
      muon_isSmallerValueMoreIsolated, muon_isSmallerValueMoreIsolated);

  }

  // get the individual rank-pair std::pairs

  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_EleTau = rankHelper_EleTau.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_EleMuon = rankHelper_EleMuon.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_MuonTau = rankHelper_MuonTau.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_TauTau = rankHelper_TauTau.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_EleEle = rankHelper_EleEle.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_MuonMuon = rankHelper_MuonMuon.returnRankedPairVec();



  // combine the individual channel pairs into a single vector
  
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank;
  retainedPairsWithRank.clear();


  for(std::size_t v = 0; v<retainedPairsWithRank_EleTau.size(); ++v )
  {
        retainedPairsWithRank.push_back(retainedPairsWithRank_EleTau[v]);
  }

  retainedPairsWithRank_EleTau.clear();

  for(std::size_t v = 0; v<retainedPairsWithRank_MuonTau.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_MuonTau[v]);    
  }

    retainedPairsWithRank_MuonTau.clear();

  for(std::size_t v = 0; v<retainedPairsWithRank_TauTau.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_TauTau[v]);    
  }

    retainedPairsWithRank_TauTau.clear();


  for(std::size_t v = 0; v<retainedPairsWithRank_EleMuon.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_EleMuon[v]);
  }

    retainedPairsWithRank_EleMuon.clear();



  for(std::size_t v = 0; v<retainedPairsWithRank_EleEle.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_EleEle[v]);
  }

    retainedPairsWithRank_EleEle.clear();

  for(std::size_t v = 0; v<retainedPairsWithRank_MuonMuon.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_MuonMuon[v]);
  }

    retainedPairsWithRank_MuonMuon.clear();


  /////////////////////////////////////////////////////////
  /* now loop over retained & ranked pairs to fill TTree */
  /////////////////////////////////////////////////////////

  for(std::size_t p = 0; p<retainedPairsWithRank.size(); ++p )
  {
      /* reset vals for the current pair */
      reInit();

      pairRank = retainedPairsWithRank[p].first;
      if(pairRank!=0 && keepOnlyBestRankedPair) continue; /* no reason to keep more than the best pair/event */      

      ////////////////////////////////
      // access the current pair    //

      NtupleEvent currentPair =   retainedPairsWithRank[p].second;


      //////////////////////////////////
      // access pair indep info       //

      NtuplePairIndependentInfo currentINDEP =   ((*pairIndepInfos)[0]);

      /////////////////////////////////////////////////////////////////////
      // init the JetHelper and GenHelper tools and fill pairIndep info  //
      // once per pair note: GenHelper and JetHelper                     // 
      // tools **must** be inititalized                                  //
      // before calling handleXXXX type functions                        //  
      /////////////////////////////////////////////////////////////////////

      if(currentPair.CandidateEventType()!=TupleCandidateEventTypes::EffCand) 
      {


        // bTagSFhelper m_BtagSFTool(sf_file, looseEff_file, mediumEff_file, tightEff_file, 
        //               LooseCut, MediumCut, TightCut );

        jethelper.init(currentINDEP.jets(),jetIDcut,
                  jetLeptonDRmin,currentPair.leg1(),currentPair.leg2(), m_BtagSFTool, iEvent.isRealData());

        genhelper.init(currentINDEP.genParticles(),currentPair.leg1(),currentPair.leg2(),
                     currentPair.CandidateEventType());

      }

      /* the order of the handleXXX calls matters! 
      switching them around will cause problems */

      handlePairIndepInfo(iEvent,iSetup,currentINDEP);
      handleCurrentEventInfo(iEvent,iSetup, currentPair);
      handleMvaMetAndRecoil( iEvent, iSetup, currentPair);
      handlePFMetAndRecoil( iEvent, iSetup, currentPair);
      

      /* don't call SVFit for EleEle or MuonMuon */
  
      if(currentPair.CandidateEventType()!=TupleCandidateEventTypes::EleEle &&\
         currentPair.CandidateEventType()!=TupleCandidateEventTypes::MuonMuon)
      {  

        if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_CORR");
        if(USE_PFMET_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "PFMET");
        if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "PUPPIMET");
     
        /* we don't compute systematics on sytematics so only call these for Tau ES nominal*/
        if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
        {
          if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_UNCORR");
          if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_RESPONSEUP");
          if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_RESPONSEDOWN");
          if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_RESOLUTIONUP");
          if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) handleSVFitCall(iEvent,iSetup,currentPair, "MVAMET_RESOLUTIONDOWN");
        }
      }


      handleLeg1AndLeg2Info(iEvent,iSetup,currentPair); 

   //   std::cout<<" ievent isReal data "<<isRealData<<" vs new function "<<currentPair.isRealData();


      FlatTuple->Fill();

  }


  //////////////
  // init values

    reInit();
}

///////////////////////////////////////////////
// ----- set TTree values for parameters that are pair indep.
////////////////////////////////////////////////

 



void FlatTupleGenerator::handlePFMetAndRecoil(const edm::Event& iEvent, const edm::EventSetup& iSetup,
 NtupleEvent currentPair)
{

  /* we do not keep PF variants for effCand as of yet */
  if(CandidateEventType!=TupleCandidateEventTypes::EffCand) 
  {


    /* systematic options are NONE, MEtSys::ProcessType::BOSON, MEtSys::ProcessType::EWK, MEtSys::ProcessType::TOP */

    
    assert(MetSystematicType_=="NONE" || MetSystematicType_=="MEtSys::ProcessType::BOSON" ||\
           MetSystematicType_=="MEtSys::ProcessType::EWK" || MetSystematicType_=="MEtSys::ProcessType::TOP");



    /* non-recoil corrected mva met read directly from ntuple */
    /* make sure pfMET related variables are filled */

    pfMET = currentPair.pfMET()[0].pt();
    pfMETphi = currentPair.pfMET()[0].phi();      
    MTpfMET_leg1 = currentPair.MTpfMET_leg1()[0]; /* will be NAN for effCand case */
    MTpfMET_leg2 = currentPair.MTpfMET_leg2()[0];



    /* some vectors we need */

    TLorentzVector uncorr(0,0,0,0); /* the non-recoil corrected pf met */
    TLorentzVector corr(0,0,0,0); /* the recoil corrected 4-vector */

    TLorentzVector responseUP_corr(0,0,0,0); /* the recoil corrected 4-vector with response shifted 1 sigma up*/
    TLorentzVector responseDOWN_corr(0,0,0,0); /* the recoil corrected 4-vector with response shifted 1 sigma down*/
    TLorentzVector resolutionUP_corr(0,0,0,0); /* the recoil corrected 4-vector with resolution shifted 1 sigma up*/
    TLorentzVector resolutionDOWN_corr(0,0,0,0); /* the recoil corrected 4-vector with resolution shifted 1 sigma down*/

    TLorentzVector responseUP_uncorr(0,0,0,0); /* the NON-recoil corrected 4-vector with response shifted 1 sigma up*/
    TLorentzVector responseDOWN_uncorr(0,0,0,0); /* the NON-recoil corrected 4-vector with response shifted 1 sigma down*/
    TLorentzVector resolutionUP_uncorr(0,0,0,0); /* the NON-recoil corrected 4-vector with resolution shifted 1 sigma up*/
    TLorentzVector resolutionDOWN_uncorr(0,0,0,0); /* the NON-recoil corrected 4-vector with resolution shifted 1 sigma down*/



    /* init the uncorrected pf met */
    uncorr.SetPtEtaPhiM(pfMET, 0., pfMETphi, 0.);


    /* some gen info we need */
    TLorentzVector genTotal(0,0,0,0);
    genTotal.SetPtEtaPhiM(genBosonTotal_pt,genBosonTotal_eta,genBosonTotal_phi,genBosonTotal_M);

    TLorentzVector genVisible(0,0,0,0);
    genVisible.SetPtEtaPhiM(genBosonVisible_pt,genBosonVisible_eta,genBosonVisible_phi,genBosonVisible_M);


    /* the number of jets */
    /* in W+jets njets should be increased by 1 (due to jet-faking-lepton) */
    /* for  diboson, single top, and ttbar : 
           in eTau/muTau if leg2_MCMatchType == GenMcMatchTypes::jetOrPuFake increase jet count by 1 
           in tt channel, increase njets by one for each leg with GenMcMatchTypes::jetOrPuFake */

    ////////////////////////////

    int njets = numberOfJets30; /* always use default not any of the variants */

 //   std::cout<<" In njet adjustment code, leg1 and leg2 mc match types are "<<genhelper.leg1_MCMatchType()<<" "<<genhelper.leg2_MCMatchType()<<"\n";

    if(RECOILCORRECTION_=="MG5_W" || RECOILCORRECTION_=="aMCatNLO_W") /* w+jets */
    {
      njets = numberOfJets30+1;
    }
    
    else if(MetSystematicType_=="MEtSys::ProcessType::EWK" || MetSystematicType_=="MEtSys::ProcessType::TOP") /* t, tt, or vv */
    {
      if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau || currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
      {
        if(genhelper.leg2_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets = numberOfJets30+1;
      }
      else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
      {
        njets = numberOfJets30;
        if(genhelper.leg1_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets++;
        if(genhelper.leg2_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets++;
      }
    }

    ////////////////////////////
    numberOfJetsForRecoilCorr = njets;
    ////////////////////////////


    if(RECOILCORRECTION_=="NONE")
    {
      corr = uncorr;
    }

    else 
    {

      float temp_px = 0;
      float temp_py = 0;

      m_recoilPfMetCorrector->CorrectByMeanResolution(
        float(uncorr.Px()), 
        float(uncorr.Py()), 
        float(genTotal.Px()), 
        float(genTotal.Py()), 
        float(genVisible.Px()), 
        float(genVisible.Py()), 
        njets,  
        temp_px, // corrected met px (float)
        temp_py  // corrected met py (float)
      );

      corr.SetPx(temp_px);
      corr.SetPy(temp_py);

    }



    /* handle the PF met systematics */
    /* need to do this twice once with recoil applied and once without */

    if(MetSystematicType_=="NONE")
    {
      responseUP_corr = corr;
      responseDOWN_corr = corr;
      resolutionUP_corr = corr;
      resolutionDOWN_corr = corr;

      responseUP_uncorr = uncorr;
      responseDOWN_uncorr = uncorr;
      resolutionUP_uncorr = uncorr;
      resolutionDOWN_uncorr = uncorr;

    }

    else
    {

      /* prelims */

      int type_of_process = -999;

      if(MetSystematicType_=="MEtSys::ProcessType::BOSON") type_of_process = MEtSys::ProcessType::BOSON;
      else if(MetSystematicType_=="MEtSys::ProcessType::EWK") type_of_process = MEtSys::ProcessType::EWK;
      else if(MetSystematicType_=="MEtSys::ProcessType::TOP") type_of_process = MEtSys::ProcessType::TOP;


      /* do the responseUP starting with RECOIL corrected PF met */

      float responseUP_px_corr = 0;
      float responseUP_py_corr = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Up,
        responseUP_px_corr, responseUP_py_corr
        );

      responseUP_corr.SetPx(responseUP_px_corr);
      responseUP_corr.SetPy(responseUP_py_corr);

      /* do the responseUP starting with NON-RECOIL corrected PF met */

      float responseUP_px_uncorr = 0;
      float responseUP_py_uncorr = 0;

      m_metSys->ApplyMEtSys(
        float(uncorr.Px()), float(uncorr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Up,
        responseUP_px_uncorr, responseUP_py_uncorr
        );

      responseUP_uncorr.SetPx(responseUP_px_uncorr);
      responseUP_uncorr.SetPy(responseUP_py_uncorr);





      /* do the responseDOWN starting with RECOIL corrected PF met  */

      float responseDOWN_px_corr = 0;
      float responseDOWN_py_corr = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Down,
        responseDOWN_px_corr, responseDOWN_py_corr
        );

      responseDOWN_corr.SetPx(responseDOWN_px_corr);
      responseDOWN_corr.SetPy(responseDOWN_py_corr);


      /* do the responseDOWN starting with NON RECOIL corrected PF met  */


      float responseDOWN_px_uncorr = 0;
      float responseDOWN_py_uncorr = 0;

      m_metSys->ApplyMEtSys(
        float(uncorr.Px()), float(uncorr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Down,
        responseDOWN_px_uncorr, responseDOWN_py_uncorr
        );

      responseDOWN_uncorr.SetPx(responseDOWN_px_uncorr);
      responseDOWN_uncorr.SetPy(responseDOWN_py_uncorr);



      /* do the resolutionUP  starting with RECOIL corrected PF met */

      float resolutionUP_px_corr = 0;
      float resolutionUP_py_corr = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Up,
        resolutionUP_px_corr, resolutionUP_py_corr
        );

      resolutionUP_corr.SetPx(resolutionUP_px_corr);
      resolutionUP_corr.SetPy(resolutionUP_py_corr);

      /* do the resolutionUP  starting with NON RECOIL corrected PF met */

      float resolutionUP_px_uncorr = 0;
      float resolutionUP_py_uncorr = 0;

      m_metSys->ApplyMEtSys(
        float(uncorr.Px()), float(uncorr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Up,
        resolutionUP_px_uncorr, resolutionUP_py_uncorr
        );

      resolutionUP_uncorr.SetPx(resolutionUP_px_uncorr);
      resolutionUP_uncorr.SetPy(resolutionUP_py_uncorr);


      /* do the resolutionDOWN  starting with RECOIL corrected PF met */

      float resolutionDOWN_px_corr = 0;
      float resolutionDOWN_py_corr = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Down,
        resolutionDOWN_px_corr, resolutionDOWN_py_corr
        );

      resolutionDOWN_corr.SetPx(resolutionDOWN_px_corr);
      resolutionDOWN_corr.SetPy(resolutionDOWN_py_corr);
          

      /* do the resolutionDOWN  starting with NON RECOIL corrected PF met */

      float resolutionDOWN_px_uncorr = 0;
      float resolutionDOWN_py_uncorr = 0;

      m_metSys->ApplyMEtSys(
        float(uncorr.Px()), float(uncorr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Down,
        resolutionDOWN_px_uncorr, resolutionDOWN_py_uncorr
        );

      resolutionDOWN_uncorr.SetPx(resolutionDOWN_px_uncorr);
      resolutionDOWN_uncorr.SetPy(resolutionDOWN_py_uncorr);

    }




    /* set values in FlatTuple starting from non RECOIL corrected PF met */


    responseUP_pfMET = responseUP_uncorr.Pt();
    responseUP_pfMETphi = responseUP_uncorr.Phi(); 
    responseUP_MTpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseUP_uncorr);
    responseUP_MTpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseUP_uncorr);

    responseDOWN_pfMET = responseDOWN_uncorr.Pt();
    responseDOWN_pfMETphi = responseDOWN_uncorr.Phi(); 
    responseDOWN_MTpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseDOWN_uncorr);
    responseDOWN_MTpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseDOWN_uncorr);

    resolutionUP_pfMET = resolutionUP_uncorr.Pt();
    resolutionUP_pfMETphi = resolutionUP_uncorr.Phi(); 
    resolutionUP_MTpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionUP_uncorr);
    resolutionUP_MTpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionUP_uncorr);

    resolutionDOWN_pfMET = resolutionDOWN_uncorr.Pt();
    resolutionDOWN_pfMETphi = resolutionDOWN_uncorr.Phi(); 
    resolutionDOWN_MTpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionDOWN_uncorr);
    resolutionDOWN_MTpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionDOWN_uncorr);




    /* set values in FlatTuple starting from  RECOIL corrected PF met */

    CORRpfMET = corr.Pt();
    CORRpfMETphi = corr.Phi();
    MTCORRpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), corr);
    MTCORRpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), corr);


    responseUP_CORRpfMET = responseUP_corr.Pt();
    responseUP_CORRpfMETphi = responseUP_corr.Phi(); 
    responseUP_MTCORRpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseUP_corr);
    responseUP_MTCORRpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseUP_corr);

    responseDOWN_CORRpfMET = responseDOWN_corr.Pt();
    responseDOWN_CORRpfMETphi = responseDOWN_corr.Phi(); 
    responseDOWN_MTCORRpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseDOWN_corr);
    responseDOWN_MTCORRpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseDOWN_corr);

    resolutionUP_CORRpfMET = resolutionUP_corr.Pt();
    resolutionUP_CORRpfMETphi = resolutionUP_corr.Phi(); 
    resolutionUP_MTCORRpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionUP_corr);
    resolutionUP_MTCORRpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionUP_corr);

    resolutionDOWN_CORRpfMET = resolutionDOWN_corr.Pt();
    resolutionDOWN_CORRpfMETphi = resolutionDOWN_corr.Phi(); 
    resolutionDOWN_MTCORRpfMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionDOWN_corr);
    resolutionDOWN_MTCORRpfMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionDOWN_corr);

    // std::cout<<" --------------------------------- \n";

    // std::cout<<" SZS: uncorr_PFMET = "<<uncorr.Pt();
    // std::cout<<" responseUP= "<<responseUP_uncorr.Pt();
    // std::cout<<" responseDOWN= "<<responseDOWN_uncorr.Pt();
    // std::cout<<" resolutionUP= "<<resolutionUP_uncorr.Pt();
    // std::cout<<" resolutionDOWN= "<<resolutionDOWN_uncorr.Pt();
    // std::cout<<"\n";

    // std::cout<<" SZS: corr_PFMET = "<<corr.Pt();
    // std::cout<<" responseUP= "<<responseUP_corr.Pt();
    // std::cout<<" responseDOWN= "<<responseDOWN_corr.Pt();
    // std::cout<<" resolutionUP= "<<resolutionUP_corr.Pt();
    // std::cout<<" resolutionDOWN= "<<resolutionDOWN_corr.Pt();
    // std::cout<<"\n";














  }

}



void FlatTupleGenerator::handleMvaMetAndRecoil(const edm::Event& iEvent, const edm::EventSetup& iSetup,
 NtupleEvent currentPair)
{

  /* we do not keep mvaMET for effCand as of yet */
  if(CandidateEventType!=TupleCandidateEventTypes::EffCand) 
  {


    /* systematic options are NONE, MEtSys::ProcessType::BOSON, MEtSys::ProcessType::EWK, MEtSys::ProcessType::TOP */

    
    assert(MetSystematicType_=="NONE" || MetSystematicType_=="MEtSys::ProcessType::BOSON" ||\
           MetSystematicType_=="MEtSys::ProcessType::EWK" || MetSystematicType_=="MEtSys::ProcessType::TOP");



    /* non-recoil corrected mva met read directly from ntuple */

    uncorr_mvaMET = currentPair.mvaMET()[0].pt();
    uncorr_mvaMETphi = currentPair.mvaMET()[0].phi();
    uncorr_MTmvaMET_leg1 = currentPair.MTmvaMET_leg1()[0];
    uncorr_MTmvaMET_leg2 = currentPair.MTmvaMET_leg2()[0]; 

    /* some vectors we need */

    TLorentzVector uncorr(0,0,0,0); /* the non-recoil corrected mva met */
    TLorentzVector corr(0,0,0,0); /* the recoil corrected 4-vector */
    TLorentzVector responseUP(0,0,0,0); /* the recoil corrected 4-vector with response shifted 1 sigma up*/
    TLorentzVector responseDOWN(0,0,0,0); /* the recoil corrected 4-vector with response shifted 1 sigma down*/
    TLorentzVector resolutionUP(0,0,0,0); /* the recoil corrected 4-vector with resolution shifted 1 sigma up*/
    TLorentzVector resolutionDOWN(0,0,0,0); /* the recoil corrected 4-vector with resolution shifted 1 sigma down*/


    /* init the uncorrected mva met */
    uncorr.SetPtEtaPhiM(uncorr_mvaMET, 0., uncorr_mvaMETphi, 0.);


    /* some gen info we need */
    TLorentzVector genTotal(0,0,0,0);
    genTotal.SetPtEtaPhiM(genBosonTotal_pt,genBosonTotal_eta,genBosonTotal_phi,genBosonTotal_M);

    TLorentzVector genVisible(0,0,0,0);
    genVisible.SetPtEtaPhiM(genBosonVisible_pt,genBosonVisible_eta,genBosonVisible_phi,genBosonVisible_M);


    /* the number of jets */
    /* in W+jets njets should be increased by 1 (due to jet-faking-lepton) */
    /* for  diboson, single top, and ttbar : 
           in eTau/muTau if leg2_MCMatchType == GenMcMatchTypes::jetOrPuFake increase jet count by 1 
           in tt channel, increase njets by one for each leg with GenMcMatchTypes::jetOrPuFake */

    ////////////////////////////

    int njets = numberOfJets30; /* always use default not any of the variants */

 //   std::cout<<" In njet adjustment code, leg1 and leg2 mc match types are "<<genhelper.leg1_MCMatchType()<<" "<<genhelper.leg2_MCMatchType()<<"\n";

    if(RECOILCORRECTION_=="MG5_W" || RECOILCORRECTION_=="aMCatNLO_W") /* w+jets */
    {
      njets = numberOfJets30+1;
    }
    
    else if(MetSystematicType_=="MEtSys::ProcessType::EWK" || MetSystematicType_=="MEtSys::ProcessType::TOP") /* t, tt, or vv */
    {
      if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau || currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
      {
        if(genhelper.leg2_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets = numberOfJets30+1;
      }
      else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
      {
        njets = numberOfJets30;
        if(genhelper.leg1_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets++;
        if(genhelper.leg2_MCMatchType() == GenMcMatchTypes::jetOrPuFake) njets++;
      }
    }

    ////////////////////////////
    numberOfJetsForRecoilCorr = njets;
    ////////////////////////////


    if(RECOILCORRECTION_=="NONE")
    {
      corr = uncorr;
    }

    else 
    {

      float temp_px = 0;
      float temp_py = 0;

      m_recoilMvaMetCorrector->CorrectByMeanResolution(
        float(uncorr.Px()), 
        float(uncorr.Py()), 
        float(genTotal.Px()), 
        float(genTotal.Py()), 
        float(genVisible.Px()), 
        float(genVisible.Py()), 
        njets,  
        temp_px, // corrected met px (float)
        temp_py  // corrected met py (float)
      );

      corr.SetPx(temp_px);
      corr.SetPy(temp_py);

    }

    /* handle the MVA met systematics */

    if(MetSystematicType_=="NONE")
    {
      responseUP = corr;
      responseDOWN = corr;
      resolutionUP = corr;
      resolutionDOWN = corr;
    }

    else
    {

      /* prelims */

      int type_of_process = -999;

      if(MetSystematicType_=="MEtSys::ProcessType::BOSON") type_of_process = MEtSys::ProcessType::BOSON;
      else if(MetSystematicType_=="MEtSys::ProcessType::EWK") type_of_process = MEtSys::ProcessType::EWK;
      else if(MetSystematicType_=="MEtSys::ProcessType::TOP") type_of_process = MEtSys::ProcessType::TOP;


      /* do the responseUP */

      float responseUP_px = 0;
      float responseUP_py = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Up,
        responseUP_px, responseUP_py
        );

      responseUP.SetPx(responseUP_px);
      responseUP.SetPy(responseUP_py);

      /* do the responseDOWN */

      float responseDOWN_px = 0;
      float responseDOWN_py = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Response,
        MEtSys::SysShift::Down,
        responseDOWN_px, responseDOWN_py
        );

      responseDOWN.SetPx(responseDOWN_px);
      responseDOWN.SetPy(responseDOWN_py);

  
      /* do the resolutionUP */

      float resolutionUP_px = 0;
      float resolutionUP_py = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Up,
        resolutionUP_px, resolutionUP_py
        );

      resolutionUP.SetPx(resolutionUP_px);
      resolutionUP.SetPy(resolutionUP_py);

      /* do the resolutionDOWN */

      float resolutionDOWN_px = 0;
      float resolutionDOWN_py = 0;

      m_metSys->ApplyMEtSys(
        float(corr.Px()), float(corr.Py()), 
        float(genTotal.Px()),float(genTotal.Py()), 
        float(genVisible.Px()),float(genVisible.Py()),
        njets,
        type_of_process,
        MEtSys::SysType::Resolution,
        MEtSys::SysShift::Down,
        resolutionDOWN_px, resolutionDOWN_py
        );

      resolutionDOWN.SetPx(resolutionDOWN_px);
      resolutionDOWN.SetPy(resolutionDOWN_py);
          
    }


    /* set vals in flatTuple for recoil corrected mva met */

    corr_mvaMET = corr.Pt();
    corr_mvaMETphi =  corr.Phi();

    responseUP_mvaMET = responseUP.Pt();
    responseUP_mvaMETphi =  responseUP.Phi();

    responseDOWN_mvaMET = responseDOWN.Pt();
    responseDOWN_mvaMETphi =  responseDOWN.Phi();

    resolutionUP_mvaMET = resolutionUP.Pt();
    resolutionUP_mvaMETphi =  resolutionUP.Phi();

    resolutionDOWN_mvaMET = resolutionDOWN.Pt();
    resolutionDOWN_mvaMETphi =  resolutionDOWN.Phi();


    /* set the values of the MT variables */


    uncorr_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), uncorr);
    uncorr_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), uncorr);

    corr_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), corr);
    corr_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), corr);

    responseUP_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseUP);
    responseUP_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseUP);

    responseDOWN_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), responseDOWN);
    responseDOWN_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), responseDOWN);

    resolutionUP_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionUP);
    resolutionUP_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionUP);

    resolutionDOWN_MTmvaMET_leg1 = GetTransverseMass(currentPair.leg1().p4(), resolutionDOWN);
    resolutionDOWN_MTmvaMET_leg2 = GetTransverseMass(currentPair.leg2().p4(), resolutionDOWN);



    // std::cout<<"MET Pt "<<uncorr_mvaMET<<" ---> corrected to "<<corr.Pt()<<"\n";
    // std::cout<<"MET Pt ResponseUP "<<corr_mvaMET<<" ---> shifted to "<<responseUP.Pt()<<"\n";
    // std::cout<<"MET Pt ResponseDOWN "<<corr_mvaMET<<" ---> shifted to "<<responseDOWN.Pt()<<"\n";
    // std::cout<<"MET Pt ResolutionUP "<<corr_mvaMET<<" ---> shifted to "<<resolutionUP.Pt()<<"\n";
    // std::cout<<"MET Pt ResolutionDOWN "<<corr_mvaMET<<" ---> shifted to "<<resolutionDOWN.Pt()<<"\n";
    
    // std::cout<<"MET Phi "<<uncorr_mvaMET<<" ---> corrected to "<<corr.Phi()<<"\n";
    // std::cout<<"MET Phi ResponseUP "<<corr_mvaMET<<" ---> shifted to "<<responseUP.Phi()<<"\n";
    // std::cout<<"MET Phi ResponseDOWN "<<corr_mvaMET<<" ---> shifted to "<<responseDOWN.Phi()<<"\n";
    // std::cout<<"MET Phi ResolutionUP "<<corr_mvaMET<<" ---> shifted to "<<resolutionUP.Phi()<<"\n";
    // std::cout<<"MET Phi ResolutionDOWN "<<corr_mvaMET<<" ---> shifted to "<<resolutionDOWN.Phi()<<"\n";
    




  }

}


    




void FlatTupleGenerator::handleEffLeptonInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup,
 NtupleEvent currentPair)
{




  ////////////////
  // fill the triggerSummaryChecks for effLeptons

  for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
  {

    // check the OR of a specific version or a wildcard v* 
    std::string label_ = triggerSummaryChecks[x]; 
    std::string versionStrippedLabel_ = label_;
    versionStrippedLabel_.erase(label_.find("_v"),label_.length());

    for(std::size_t l = 0; l<currentPair.EffLepton().size(); ++l)
    {

      float trig = 0.0;
      if(currentPair.isEffLeptonGoodForHLTPath(label_,l)) trig = 1.0;
      else if(currentPair.isEffLeptonGoodForHLTPath(versionStrippedLabel_,l)) trig = 1.0;

      effLep_GoodForHLTPath.at(x).second.push_back( trig );  

    }

  }


  ////////////////////////////////
  // fill the tauIDs for effLeptons

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {
   
    for(std::size_t l = 0; l<currentPair.EffLepton().size(); ++l)
    {

      if(currentPair.EffLepton().at(l).leptonType() == TupleLeptonTypes::aTau)
      {
        effLep_tauIDs.at(x).second.push_back( currentPair.EffLepton().at(l).tauID(tauIDsToKeep[x]) );  
      }
      else
      {
        effLep_tauIDs.at(x).second.push_back( -999. );        
      }  

    }

  }





  for(std::size_t i = 0; i<currentPair.EffLepton().size(); ++i)
  {

    /* find and store the L1isoTau match (of max pt) for the EffLepton */

    //double maxIsoTauPt = -999.;
    double maxPt_pt = -999.;
    double maxPt_eta = -999.;
    double maxPt_phi = -999.;


    // the following block causes a crash when effLepton is on
    // for(std::size_t ii = 0; ii<currentPair.EffLepton_L1IsoTauDR05Matches().at(i).size(); ++ii)
    // {

    //   if( currentPair.EffLepton_L1IsoTauDR05Matches()[i][ii].pt() > maxIsoTauPt )
    //   {
    //       maxIsoTauPt = currentPair.EffLepton_L1IsoTauDR05Matches()[i][ii].pt();
    //       maxPt_pt = currentPair.EffLepton_L1IsoTauDR05Matches()[i][ii].pt();
    //       maxPt_eta = currentPair.EffLepton_L1IsoTauDR05Matches()[i][ii].eta();
    //       maxPt_phi = currentPair.EffLepton_L1IsoTauDR05Matches()[i][ii].phi();

    //   }

    // }

    effLep_MaxL1IsoTauMatch_pt.push_back(maxPt_pt);
    effLep_MaxL1IsoTauMatch_eta.push_back(maxPt_eta);
    effLep_MaxL1IsoTauMatch_phi.push_back(maxPt_phi);



    ///////////////////////////////
    // trigger matches (max pt only)
    ////////////////////////////////

    effLep_maxPtTrigObjMatch.push_back(currentPair.EffLeptonMaxPtTriggerObjMatch(i));

    effLep_leptonType.push_back(currentPair.EffLepton().at(i).leptonType());
    effLep_dz.push_back(currentPair.EffLepton().at(i).dz());
    effLep_dxy.push_back(currentPair.EffLepton().at(i).dxy());
    effLep_EffectiveArea.push_back(currentPair.EffLepton().at(i).EffectiveArea());
    effLep_charge.push_back(currentPair.EffLepton().at(i).charge());
    effLep_PFpdgId.push_back(currentPair.EffLepton().at(i).PFpdgId());
    effLep_GENpdgId.push_back(currentPair.EffLepton().at(i).GENpdgId());
    effLep_GENMOTHERpdgId.push_back(currentPair.EffLepton().at(i).GENMOTHERpdgId());
    effLep_IP.push_back(currentPair.EffLepton().at(i).IP());
    effLep_IPerror.push_back(currentPair.EffLepton().at(i).IPerror());
    effLep_PUchargedHadronIso.push_back(currentPair.EffLepton().at(i).PUchargedHadronIso());
    effLep_chargedHadronIso.push_back(currentPair.EffLepton().at(i).chargedHadronIso());
    effLep_neutralHadronIso.push_back(currentPair.EffLepton().at(i).neutralHadronIso());
    effLep_photonIso.push_back(currentPair.EffLepton().at(i).photonIso());
    effLep_DepositR03ECal.push_back(currentPair.EffLepton().at(i).DepositR03ECal());
    effLep_DepositR03Hcal.push_back(currentPair.EffLepton().at(i).DepositR03Hcal());
    effLep_DepositR03TrackerOfficial.push_back(currentPair.EffLepton().at(i).DepositR03TrackerOfficial());
    effLep_isGlobalMuon.push_back(currentPair.EffLepton().at(i).isGlobalMuon());
    effLep_isGoodGlobalMuon.push_back(currentPair.EffLepton().at(i).isGoodGlobalMuon());
    effLep_passesLooseMuonId.push_back(currentPair.EffLepton().at(i).passesLooseMuonId());
    effLep_passesMediumMuonId_ICHEP16.push_back(currentPair.EffLepton().at(i).passesMediumMuonId_ICHEP16());
    effLep_passesMediumMuonId_Moriond17.push_back(currentPair.EffLepton().at(i).passesMediumMuonId_Moriond17());
    effLep_passesMediumMuonId.push_back(currentPair.EffLepton().at(i).passesMediumMuonId());
    effLep_passesTightMuonId.push_back(currentPair.EffLepton().at(i).passesTightMuonId());
    effLep_isLooseMuon.push_back(currentPair.EffLepton().at(i).isLooseMuon());
    effLep_isPFMuon.push_back(currentPair.EffLepton().at(i).isPFMuon());
    effLep_isSoftMuon.push_back(currentPair.EffLepton().at(i).isSoftMuon());
    effLep_isTightMuon.push_back(currentPair.EffLepton().at(i).isTightMuon());
    effLep_isTrackerMuon.push_back(currentPair.EffLepton().at(i).isTrackerMuon());
    effLep_muonCombQualChi2LocalPosition.push_back(currentPair.EffLepton().at(i).muonCombQualChi2LocalPosition());
    effLep_muonCombQualTrkKink.push_back(currentPair.EffLepton().at(i).muonCombQualTrkKink());
    effLep_muonGlobalTrackNormChi2.push_back(currentPair.EffLepton().at(i).muonGlobalTrackNormChi2());
    effLep_muonInnerTrkValidFraction.push_back(currentPair.EffLepton().at(i).muonInnerTrkValidFraction());
    effLep_muonSegmentCompatibility.push_back(currentPair.EffLepton().at(i).muonSegmentCompatibility());
    effLep_raw_electronMVA.push_back(currentPair.EffLepton().at(i).raw_electronMVA());
    effLep_category_electronMVA.push_back(currentPair.EffLepton().at(i).category_electronMVA());
    effLep_passFail_electronMVA80.push_back(currentPair.EffLepton().at(i).passFail_electronMVA80());
    effLep_passFail_electronMVA90.push_back(currentPair.EffLepton().at(i).passFail_electronMVA90());
    effLep_passFail_VetoElectronCutBasedID.push_back(currentPair.EffLepton().at(i).passFail_VetoElectronCutBasedID());
    effLep_passFail_TightElectronCutBasedID.push_back(currentPair.EffLepton().at(i).passFail_TightElectronCutBasedID());
    effLep_ooEmooP.push_back(currentPair.EffLepton().at(i).ooEmooP());
    effLep_full5x5_sigmaIetaIeta.push_back(currentPair.EffLepton().at(i).full5x5_sigmaIetaIeta());
    effLep_SuperClusterEta.push_back(currentPair.EffLepton().at(i).SuperClusterEta());
    effLep_hadronicOverEm.push_back(currentPair.EffLepton().at(i).hadronicOverEm());
    effLep_isEB.push_back(currentPair.EffLepton().at(i).isEB());
    effLep_isEBEEGap.push_back(currentPair.EffLepton().at(i).isEBEEGap());
    effLep_isEBEtaGap.push_back(currentPair.EffLepton().at(i).isEBEtaGap());
    effLep_isEBPhiGap.push_back(currentPair.EffLepton().at(i).isEBPhiGap());
    effLep_isEE.push_back(currentPair.EffLepton().at(i).isEE());
    effLep_isEEDeeGap.push_back(currentPair.EffLepton().at(i).isEEDeeGap());
    effLep_isEERingGap.push_back(currentPair.EffLepton().at(i).isEERingGap());
    effLep_deltaEtaSuperClusterTrackAtVtx.push_back(currentPair.EffLepton().at(i).deltaEtaSuperClusterTrackAtVtx());
    effLep_deltaPhiSuperClusterTrackAtVtx.push_back(currentPair.EffLepton().at(i).deltaPhiSuperClusterTrackAtVtx());
    effLep_sigmaEtaEta.push_back(currentPair.EffLepton().at(i).sigmaEtaEta());
    effLep_sigmaIetaIeta.push_back(currentPair.EffLepton().at(i).sigmaIetaIeta());
    effLep_sigmaIphiIphi.push_back(currentPair.EffLepton().at(i).sigmaIphiIphi());
    effLep_numberOfMissingInnerHits.push_back(currentPair.EffLepton().at(i).numberOfMissingInnerHits());
    effLep_numberOfMissingOuterHits.push_back(currentPair.EffLepton().at(i).numberOfMissingOuterHits());
    effLep_numberOfTrackHits.push_back(currentPair.EffLepton().at(i).numberOfTrackHits());
    effLep_passConversionVeto.push_back(currentPair.EffLepton().at(i).passConversionVeto());
    effLep_ZimpactTau.push_back(currentPair.EffLepton().at(i).ZimpactTau());
    effLep_dzTauVertex.push_back(currentPair.EffLepton().at(i).dzTauVertex());
    effLep_numStrips.push_back(currentPair.EffLepton().at(i).numStrips());
    effLep_numHadrons.push_back(currentPair.EffLepton().at(i).numHadrons());

    effLep_rerunDiscriminationByIsolationMVArun2v1raw.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1raw());
    effLep_rerunDiscriminationByIsolationMVArun2v1VLoose.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1VLoose());
    effLep_rerunDiscriminationByIsolationMVArun2v1Loose.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1Loose());
    effLep_rerunDiscriminationByIsolationMVArun2v1Medium.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1Medium());
    effLep_rerunDiscriminationByIsolationMVArun2v1Tight.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1Tight());
    effLep_rerunDiscriminationByIsolationMVArun2v1VTight.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1VTight());
    effLep_rerunDiscriminationByIsolationMVArun2v1VVTight.push_back(currentPair.EffLepton().at(i).rerunDiscriminationByIsolationMVArun2v1VVTight());

    effLep_decayMode.push_back(currentPair.EffLepton().at(i).decayMode());
    effLep_pt.push_back(currentPair.EffLepton().at(i).p4().pt());
    effLep_gen_pt.push_back(currentPair.EffLepton().at(i).gen_p4().pt());
    effLep_genMother_pt.push_back(currentPair.EffLepton().at(i).genMother_p4().pt());
    effLep_genJet_pt.push_back(currentPair.EffLepton().at(i).genJet_p4().pt());
    effLep_eta.push_back(currentPair.EffLepton().at(i).p4().eta());
    effLep_gen_eta.push_back(currentPair.EffLepton().at(i).gen_p4().eta());
    effLep_genMother_eta.push_back(currentPair.EffLepton().at(i).genMother_p4().eta());
    effLep_genJet_eta.push_back(currentPair.EffLepton().at(i).genJet_p4().eta());
    effLep_phi.push_back(currentPair.EffLepton().at(i).p4().phi());
    effLep_gen_phi.push_back(currentPair.EffLepton().at(i).gen_p4().phi());
    effLep_genMother_phi.push_back(currentPair.EffLepton().at(i).genMother_p4().phi());
    effLep_genJet_phi.push_back(currentPair.EffLepton().at(i).genJet_p4().phi());
    effLep_M.push_back(currentPair.EffLepton().at(i).p4().M());
    effLep_gen_M.push_back(currentPair.EffLepton().at(i).gen_p4().M());
    effLep_genMother_M.push_back(currentPair.EffLepton().at(i).genMother_p4().M());
    effLep_genJet_M.push_back(currentPair.EffLepton().at(i).genJet_p4().M());
    effLep_genJet_pdgId.push_back(currentPair.EffLepton().at(i).genJet_pdgId());



    /* set the relative isolation value dep. on the lepton type */

    if(currentPair.EffLepton().at(i).leptonType() == TupleLeptonTypes::anElectron)
    {
      effLep_RelIso.push_back(currentPair.EffLepton().at(i).relativeIsol(electronIsolationForRelIsoBranch));
    }

    else if(currentPair.EffLepton().at(i).leptonType() == TupleLeptonTypes::aMuon)
    {
      effLep_RelIso.push_back(currentPair.EffLepton().at(i).relativeIsol(muonIsolationForRelIsoBranch));
    }

    else if(currentPair.EffLepton().at(i).leptonType() == TupleLeptonTypes::aTau)
    {
      effLep_RelIso.push_back(currentPair.EffLepton().at(i).tauID(tauIsolationForRelIsoBranch)); // the default
    }

  

    /* stored rho's are the same for all effLeptons since it is an event quantity */
    rho = currentPair.EffLepton().at(i).rho("fixedGridRhoFastjetAll"); 


  }




  /* mc matches */

  effLep_MCMatchType = genhelper.effLep_MCMatchType();
  effLep_genMCmatch_pt = genhelper.effLep_genMCmatch_pt();
  effLep_genMCmatch_eta = genhelper.effLep_genMCmatch_eta();
  effLep_genMCmatch_phi = genhelper.effLep_genMCmatch_phi();
  effLep_genMCmatch_M = genhelper.effLep_genMCmatch_M();
  effLep_MCMatchPdgId = genhelper.effLep_MCMatchPdgId();


}

void FlatTupleGenerator::handleLeg1AndLeg2Info(const edm::Event& iEvent, const edm::EventSetup& iSetup,
 NtupleEvent currentPair)
{

  /* fill info accessed through leg1 and leg2 */


  ///////////////////////////////
  // trigger matches (max pt only)
  ////////////////////////////////


  leg1_maxPtTrigObjMatch = currentPair.leg1MaxPtTriggerObjMatch();
  leg2_maxPtTrigObjMatch = currentPair.leg2MaxPtTriggerObjMatch();




  ////////////////////////////////
  // fill the tauIDs for tau legs

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {
    
    if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
    {
        leg1_tauIDs[x]  =  currentPair.leg1().tauID(tauIDsToKeep[x]);
    }

    if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
    {
        leg2_tauIDs[x]  =  currentPair.leg2().tauID(tauIDsToKeep[x]);
    }

  }


  ////////////////
  // fill the triggerSummaryChecks for both legs

  for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
  {

    // check the OR of a specific version or a wildcard v* 
    std::string label_ = triggerSummaryChecks[x]; 
    std::string versionStrippedLabel_ = label_;
    versionStrippedLabel_.erase(label_.find("_v"),label_.length());

    float l1trig = 0.0;
    float l2trig = 0.0;

    if(currentPair.isLeg1GoodForHLTPath(label_)) l1trig = 1.0;
    else if(currentPair.isLeg1GoodForHLTPath(versionStrippedLabel_)) l1trig = 1.0;

    if(currentPair.isLeg2GoodForHLTPath(label_)) l2trig = 1.0;
    else if(currentPair.isLeg2GoodForHLTPath(versionStrippedLabel_)) l2trig = 1.0;

    leg1_GoodForHLTPath[x]  =  l1trig;
    leg2_GoodForHLTPath[x]  =  l2trig;
  }

  /* general leg info */


  PairPassesDoubleTauIsoTau28MatchCut = currentPair.PairPassesDoubleTauIsoTau28MatchCut();


  for(std::size_t ii = 0; ii<currentPair.leg1_L1IsoTauDR05Matches().size(); ++ii)
  {
    leg1_L1IsoTauMatch_pt.push_back(currentPair.leg1_L1IsoTauDR05Matches().at(ii).pt());
    leg1_L1IsoTauMatch_eta.push_back(currentPair.leg1_L1IsoTauDR05Matches().at(ii).eta());
    leg1_L1IsoTauMatch_phi.push_back(currentPair.leg1_L1IsoTauDR05Matches().at(ii).phi());
  }

  for(std::size_t ii = 0; ii<currentPair.leg2_L1IsoTauDR05Matches().size(); ++ii)
  {
    leg2_L1IsoTauMatch_pt.push_back(currentPair.leg2_L1IsoTauDR05Matches().at(ii).pt());
    leg2_L1IsoTauMatch_eta.push_back(currentPair.leg2_L1IsoTauDR05Matches().at(ii).eta());
    leg2_L1IsoTauMatch_phi.push_back(currentPair.leg2_L1IsoTauDR05Matches().at(ii).phi());
  }


  DeltaR_leg1_leg2 = deltaR(currentPair.leg1().p4(), currentPair.leg2().p4());


  leg1_leptonType = currentPair.leg1().leptonType();
  leg1_dz = currentPair.leg1().dz();
  leg1_dxy = currentPair.leg1().dxy();
  leg1_EffectiveArea = currentPair.leg1().EffectiveArea();
  leg1_charge = currentPair.leg1().charge();
  leg1_PFpdgId = currentPair.leg1().PFpdgId();
  leg1_GENpdgId = currentPair.leg1().GENpdgId();
  leg1_GENMOTHERpdgId = currentPair.leg1().GENMOTHERpdgId();
  leg1_IP = currentPair.leg1().IP();
  leg1_IPerror = currentPair.leg1().IPerror();
  leg1_PUchargedHadronIso = currentPair.leg1().PUchargedHadronIso();
  leg1_chargedHadronIso = currentPair.leg1().chargedHadronIso();
  leg1_neutralHadronIso = currentPair.leg1().neutralHadronIso();
  leg1_photonIso = currentPair.leg1().photonIso();
  leg1_DepositR03ECal = currentPair.leg1().DepositR03ECal();
  leg1_DepositR03Hcal = currentPair.leg1().DepositR03Hcal();
  leg1_DepositR03TrackerOfficial = currentPair.leg1().DepositR03TrackerOfficial();
  leg1_isGlobalMuon = currentPair.leg1().isGlobalMuon();
  leg1_isGoodGlobalMuon = currentPair.leg1().isGoodGlobalMuon();
  leg1_passesLooseMuonId = currentPair.leg1().passesLooseMuonId();
  leg1_passesMediumMuonId_ICHEP16 = currentPair.leg1().passesMediumMuonId_ICHEP16();
  leg1_passesMediumMuonId_Moriond17 = currentPair.leg1().passesMediumMuonId_Moriond17();
  leg1_passesMediumMuonId = currentPair.leg1().passesMediumMuonId();
  leg1_passesTightMuonId = currentPair.leg1().passesTightMuonId();
  leg1_isLooseMuon = currentPair.leg1().isLooseMuon();
  leg1_isPFMuon = currentPair.leg1().isPFMuon();
  leg1_isSoftMuon = currentPair.leg1().isSoftMuon();
  leg1_isTightMuon = currentPair.leg1().isTightMuon();
  leg1_isTrackerMuon = currentPair.leg1().isTrackerMuon();
  leg1_muonCombQualChi2LocalPosition = currentPair.leg1().muonCombQualChi2LocalPosition();
  leg1_muonCombQualTrkKink = currentPair.leg1().muonCombQualTrkKink();
  leg1_muonGlobalTrackNormChi2 = currentPair.leg1().muonGlobalTrackNormChi2();
  leg1_muonInnerTrkValidFraction = currentPair.leg1().muonInnerTrkValidFraction();
  leg1_muonSegmentCompatibility = currentPair.leg1().muonSegmentCompatibility();
  leg1_raw_electronMVA = currentPair.leg1().raw_electronMVA();
  leg1_category_electronMVA = currentPair.leg1().category_electronMVA();
  leg1_passFail_electronMVA80 = currentPair.leg1().passFail_electronMVA80();
  leg1_passFail_electronMVA90 = currentPair.leg1().passFail_electronMVA90();
  leg1_passFail_VetoElectronCutBasedID = currentPair.leg1().passFail_VetoElectronCutBasedID();
  leg1_passFail_TightElectronCutBasedID = currentPair.leg1().passFail_TightElectronCutBasedID();
  leg1_ooEmooP = currentPair.leg1().ooEmooP();
  leg1_full5x5_sigmaIetaIeta = currentPair.leg1().full5x5_sigmaIetaIeta();
  leg1_SuperClusterEta = currentPair.leg1().SuperClusterEta();
  leg1_hadronicOverEm = currentPair.leg1().hadronicOverEm();
  leg1_isEB = currentPair.leg1().isEB();
  leg1_isEBEEGap = currentPair.leg1().isEBEEGap();
  leg1_isEBEtaGap = currentPair.leg1().isEBEtaGap();
  leg1_isEBPhiGap = currentPair.leg1().isEBPhiGap();
  leg1_isEE = currentPair.leg1().isEE();
  leg1_isEEDeeGap = currentPair.leg1().isEEDeeGap();
  leg1_isEERingGap = currentPair.leg1().isEERingGap();
  leg1_deltaEtaSuperClusterTrackAtVtx = currentPair.leg1().deltaEtaSuperClusterTrackAtVtx();
  leg1_deltaPhiSuperClusterTrackAtVtx = currentPair.leg1().deltaPhiSuperClusterTrackAtVtx();
  leg1_sigmaEtaEta = currentPair.leg1().sigmaEtaEta();
  leg1_sigmaIetaIeta = currentPair.leg1().sigmaIetaIeta();
  leg1_sigmaIphiIphi = currentPair.leg1().sigmaIphiIphi();
  leg1_numberOfMissingInnerHits = currentPair.leg1().numberOfMissingInnerHits();
  leg1_numberOfMissingOuterHits = currentPair.leg1().numberOfMissingOuterHits();
  leg1_numberOfTrackHits = currentPair.leg1().numberOfTrackHits();
  leg1_passConversionVeto = currentPair.leg1().passConversionVeto();
  leg1_ZimpactTau = currentPair.leg1().ZimpactTau();
  leg1_dzTauVertex = currentPair.leg1().dzTauVertex();
  leg1_numStrips = currentPair.leg1().numStrips();
  leg1_numHadrons = currentPair.leg1().numHadrons();

  leg1_rerunDiscriminationByIsolationMVArun2v1raw = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1raw();
  leg1_rerunDiscriminationByIsolationMVArun2v1VLoose = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1VLoose();
  leg1_rerunDiscriminationByIsolationMVArun2v1Loose = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1Loose();
  leg1_rerunDiscriminationByIsolationMVArun2v1Medium = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1Medium();
  leg1_rerunDiscriminationByIsolationMVArun2v1Tight = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1Tight();
  leg1_rerunDiscriminationByIsolationMVArun2v1VTight = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1VTight();
  leg1_rerunDiscriminationByIsolationMVArun2v1VVTight = currentPair.leg1().rerunDiscriminationByIsolationMVArun2v1VVTight();

  leg1_decayMode = currentPair.leg1().decayMode();
  leg2_leptonType = currentPair.leg2().leptonType();


  leg2_dz = currentPair.leg2().dz();
  leg2_dxy = currentPair.leg2().dxy();
  leg2_EffectiveArea = currentPair.leg2().EffectiveArea();
  leg2_charge = currentPair.leg2().charge();
  leg2_PFpdgId = currentPair.leg2().PFpdgId();
  leg2_GENpdgId = currentPair.leg2().GENpdgId();
  leg2_GENMOTHERpdgId = currentPair.leg2().GENMOTHERpdgId();
  leg2_IP = currentPair.leg2().IP();
  leg2_IPerror = currentPair.leg2().IPerror();
  leg2_PUchargedHadronIso = currentPair.leg2().PUchargedHadronIso();
  leg2_chargedHadronIso = currentPair.leg2().chargedHadronIso();
  leg2_neutralHadronIso = currentPair.leg2().neutralHadronIso();
  leg2_photonIso = currentPair.leg2().photonIso();
  leg2_DepositR03ECal = currentPair.leg2().DepositR03ECal();
  leg2_DepositR03Hcal = currentPair.leg2().DepositR03Hcal();
  leg2_DepositR03TrackerOfficial = currentPair.leg2().DepositR03TrackerOfficial();
  leg2_isGlobalMuon = currentPair.leg2().isGlobalMuon();
  leg2_isGoodGlobalMuon = currentPair.leg2().isGoodGlobalMuon();
  leg2_passesLooseMuonId = currentPair.leg2().passesLooseMuonId();
  leg2_passesMediumMuonId_ICHEP16 = currentPair.leg2().passesMediumMuonId_ICHEP16();
  leg2_passesMediumMuonId_Moriond17 = currentPair.leg2().passesMediumMuonId_Moriond17();
  leg2_passesMediumMuonId = currentPair.leg2().passesMediumMuonId();
  leg2_passesTightMuonId = currentPair.leg2().passesTightMuonId();
  leg2_isLooseMuon = currentPair.leg2().isLooseMuon();
  leg2_isPFMuon = currentPair.leg2().isPFMuon();
  leg2_isSoftMuon = currentPair.leg2().isSoftMuon();
  leg2_isTightMuon = currentPair.leg2().isTightMuon();
  leg2_isTrackerMuon = currentPair.leg2().isTrackerMuon();
  leg2_muonCombQualChi2LocalPosition = currentPair.leg2().muonCombQualChi2LocalPosition();
  leg2_muonCombQualTrkKink = currentPair.leg2().muonCombQualTrkKink();
  leg2_muonGlobalTrackNormChi2 = currentPair.leg2().muonGlobalTrackNormChi2();
  leg2_muonInnerTrkValidFraction = currentPair.leg2().muonInnerTrkValidFraction();
  leg2_muonSegmentCompatibility = currentPair.leg2().muonSegmentCompatibility();
  leg2_raw_electronMVA = currentPair.leg2().raw_electronMVA();
  leg2_category_electronMVA = currentPair.leg2().category_electronMVA();
  leg2_passFail_electronMVA80 = currentPair.leg2().passFail_electronMVA80();
  leg2_passFail_electronMVA90 = currentPair.leg2().passFail_electronMVA90();
  leg2_passFail_VetoElectronCutBasedID = currentPair.leg2().passFail_VetoElectronCutBasedID();
  leg2_passFail_TightElectronCutBasedID = currentPair.leg2().passFail_TightElectronCutBasedID();
  leg2_ooEmooP = currentPair.leg2().ooEmooP();
  leg2_full5x5_sigmaIetaIeta = currentPair.leg2().full5x5_sigmaIetaIeta();
  leg2_SuperClusterEta = currentPair.leg2().SuperClusterEta();
  leg2_hadronicOverEm = currentPair.leg2().hadronicOverEm();
  leg2_isEB = currentPair.leg2().isEB();
  leg2_isEBEEGap = currentPair.leg2().isEBEEGap();
  leg2_isEBEtaGap = currentPair.leg2().isEBEtaGap();
  leg2_isEBPhiGap = currentPair.leg2().isEBPhiGap();
  leg2_isEE = currentPair.leg2().isEE();
  leg2_isEEDeeGap = currentPair.leg2().isEEDeeGap();
  leg2_isEERingGap = currentPair.leg2().isEERingGap();
  leg2_deltaEtaSuperClusterTrackAtVtx = currentPair.leg2().deltaEtaSuperClusterTrackAtVtx();
  leg2_deltaPhiSuperClusterTrackAtVtx = currentPair.leg2().deltaPhiSuperClusterTrackAtVtx();
  leg2_sigmaEtaEta = currentPair.leg2().sigmaEtaEta();
  leg2_sigmaIetaIeta = currentPair.leg2().sigmaIetaIeta();
  leg2_sigmaIphiIphi = currentPair.leg2().sigmaIphiIphi();
  leg2_numberOfMissingInnerHits = currentPair.leg2().numberOfMissingInnerHits();
  leg2_numberOfMissingOuterHits = currentPair.leg2().numberOfMissingOuterHits();
  leg2_numberOfTrackHits = currentPair.leg2().numberOfTrackHits();
  leg2_passConversionVeto = currentPair.leg2().passConversionVeto();
  leg2_ZimpactTau = currentPair.leg2().ZimpactTau();
  leg2_numStrips = currentPair.leg2().numStrips();
  leg2_numHadrons = currentPair.leg2().numHadrons();

  leg2_rerunDiscriminationByIsolationMVArun2v1raw = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1raw();
  leg2_rerunDiscriminationByIsolationMVArun2v1VLoose = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1VLoose();
  leg2_rerunDiscriminationByIsolationMVArun2v1Loose = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1Loose();
  leg2_rerunDiscriminationByIsolationMVArun2v1Medium = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1Medium();
  leg2_rerunDiscriminationByIsolationMVArun2v1Tight = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1Tight();
  leg2_rerunDiscriminationByIsolationMVArun2v1VTight = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1VTight();
  leg2_rerunDiscriminationByIsolationMVArun2v1VVTight = currentPair.leg2().rerunDiscriminationByIsolationMVArun2v1VVTight();


  leg2_decayMode = currentPair.leg2().decayMode();
  leg2_dzTauVertex = currentPair.leg2().dzTauVertex();


  leg2_pt = currentPair.leg2().p4().pt();
  leg2_gen_pt = currentPair.leg2().gen_p4().pt();
  leg2_genMother_pt = currentPair.leg2().genMother_p4().pt();
  leg2_genJet_pt = currentPair.leg2().genJet_p4().pt();
  leg1_pt = currentPair.leg1().p4().pt();
  leg1_gen_pt = currentPair.leg1().gen_p4().pt();
  leg1_genMother_pt = currentPair.leg1().genMother_p4().pt();
  leg1_genJet_pt = currentPair.leg1().genJet_p4().pt();
  leg2_eta = currentPair.leg2().p4().eta();
  leg2_gen_eta = currentPair.leg2().gen_p4().eta();
  leg2_genMother_eta = currentPair.leg2().genMother_p4().eta();
  leg2_genJet_eta = currentPair.leg2().genJet_p4().eta();
  leg1_eta = currentPair.leg1().p4().eta();
  leg1_gen_eta = currentPair.leg1().gen_p4().eta();
  leg1_genMother_eta = currentPair.leg1().genMother_p4().eta();
  leg1_genJet_eta = currentPair.leg1().genJet_p4().eta();
  leg2_phi = currentPair.leg2().p4().phi();
  leg2_gen_phi = currentPair.leg2().gen_p4().phi();
  leg2_genMother_phi = currentPair.leg2().genMother_p4().phi();
  
  leg2_genJet_phi = currentPair.leg2().genJet_p4().phi();
  leg1_phi = currentPair.leg1().p4().phi();
  leg1_gen_phi = currentPair.leg1().gen_p4().phi();
  leg1_genMother_phi = currentPair.leg1().genMother_p4().phi();
  leg1_genJet_phi = currentPair.leg1().genJet_p4().phi();
  leg2_M = currentPair.leg2().p4().M();
  leg2_gen_M = currentPair.leg2().gen_p4().M();
  leg2_genMother_M = currentPair.leg2().genMother_p4().M();
  leg2_genJet_M = currentPair.leg2().genJet_p4().M();
  leg1_M = currentPair.leg1().p4().M();
  leg1_gen_M = currentPair.leg1().gen_p4().M();
  leg1_genMother_M = currentPair.leg1().genMother_p4().M();
  leg1_genJet_M = currentPair.leg1().genJet_p4().M();


  leg1_genJet_pdgId = currentPair.leg1().genJet_pdgId();
  leg2_genJet_pdgId = currentPair.leg2().genJet_pdgId();


  /* set the relative isolation value dep. on the lepton type */

  if(currentPair.leg1().leptonType() == TupleLeptonTypes::anElectron)
  {
    leg1_RelIso = currentPair.leg1().relativeIsol(electronIsolationForRelIsoBranch);
  }

  else if(currentPair.leg1().leptonType() == TupleLeptonTypes::aMuon)
  {
    leg1_RelIso = currentPair.leg1().relativeIsol(muonIsolationForRelIsoBranch);
  }

  else if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
  {                                       
    if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau)
    {
          leg1_RelIso = currentPair.leg1().tauID(tauIsolationForRelIsoBranch_forEleTau);
    }
    else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
    {
          leg1_RelIso = currentPair.leg1().tauID(tauIsolationForRelIsoBranch_forMuTau);
    }
    else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
    {
          leg1_RelIso = currentPair.leg1().tauID(tauIsolationForRelIsoBranch_forTauTau);
    }
    else leg1_RelIso = currentPair.leg1().tauID(tauIsolationForRelIsoBranch);

  }


  if(currentPair.leg2().leptonType() == TupleLeptonTypes::anElectron)
  {
    leg2_RelIso = currentPair.leg2().relativeIsol(electronIsolationForRelIsoBranch);
  }

  else if(currentPair.leg2().leptonType() == TupleLeptonTypes::aMuon)
  {
    leg2_RelIso = currentPair.leg2().relativeIsol(muonIsolationForRelIsoBranch);
  }

  else if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
  {

    if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau)
    {
          leg2_RelIso = currentPair.leg2().tauID(tauIsolationForRelIsoBranch_forEleTau);
    }
    else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
    {
          leg2_RelIso = currentPair.leg2().tauID(tauIsolationForRelIsoBranch_forMuTau);
    }
    else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
    {
          leg2_RelIso = currentPair.leg2().tauID(tauIsolationForRelIsoBranch_forTauTau);
    }
    else leg2_RelIso = currentPair.leg2().tauID(tauIsolationForRelIsoBranch);

  }

  

  /* stored rho's are the same for both legs */
  rho = currentPair.leg1().rho("fixedGridRhoFastjetAll"); 

 
  /*  MC match type vals - new for 76X */


  leg1_MCMatchType = genhelper.leg1_MCMatchType();
  leg1_genMCmatch_pt = genhelper.leg1_genMCmatch_pt();
  leg1_genMCmatch_eta = genhelper.leg1_genMCmatch_eta();
  leg1_genMCmatch_phi = genhelper.leg1_genMCmatch_phi();
  leg1_genMCmatch_M = genhelper.leg1_genMCmatch_M();
  leg1_MCMatchPdgId = genhelper.leg1_MCMatchPdgId();

  leg2_MCMatchType = genhelper.leg2_MCMatchType();
  leg2_genMCmatch_pt = genhelper.leg2_genMCmatch_pt();
  leg2_genMCmatch_eta = genhelper.leg2_genMCmatch_eta();
  leg2_genMCmatch_phi = genhelper.leg2_genMCmatch_phi();
  leg2_genMCmatch_M = genhelper.leg2_genMCmatch_M();
  leg2_MCMatchPdgId = genhelper.leg2_MCMatchPdgId();


  IsZTT = genhelper.IsZTT();
  IsZL = genhelper.IsZL();
  IsZJ = genhelper.IsZJ();
  IsZLL = genhelper.IsZLL();


  

}



void FlatTupleGenerator::handleSVFitCall(const edm::Event& iEvent, const edm::EventSetup& iSetup,
 NtupleEvent currentPair, std::string METtoUSE)
{

  //std::cout<<" CALLING SVFIT WITH "<<METtoUSE<<" MET \n";

  /* only valid string args */
  assert(METtoUSE == "MVAMET_CORR" ||\
         METtoUSE == "MVAMET_UNCORR" ||\
         METtoUSE == "MVAMET_RESPONSEUP" ||\
         METtoUSE == "MVAMET_RESPONSEDOWN" ||\
         METtoUSE == "MVAMET_RESOLUTIONUP" ||\
         METtoUSE == "MVAMET_RESOLUTIONDOWN" ||\
         METtoUSE == "PFMET" ||\
         METtoUSE == "PUPPIMET");

  /* reset the appropriate vars, and 
     next set the met and cov matrix
  */

  TMatrixD covMET(2, 2); 
  TLorentzVector svMassMET(0,0,0,0);

  if(METtoUSE == "MVAMET_CORR")
  {
    SVMass = NAN;
    SVTransverseMass = NAN;
    svMassMET.SetPtEtaPhiM( corr_mvaMET, 0.0, corr_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;
  }  
  else if(METtoUSE == "MVAMET_UNCORR")
  {
    SVMass_uncorr_mvaMET = NAN;
    SVTransverseMass_uncorr_mvaMET = NAN;
    svMassMET.SetPtEtaPhiM( uncorr_mvaMET, 0.0, uncorr_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;
  }
  else if(METtoUSE == "MVAMET_RESPONSEUP")
  {
    SVMass_responseUP_mvaMET = NAN;
    SVTransverseMass_responseUP_mvaMET = NAN;
    svMassMET.SetPtEtaPhiM( responseUP_mvaMET, 0.0, responseUP_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;

  }
  else if(METtoUSE == "MVAMET_RESPONSEDOWN")
  {
    SVMass_responseDN_mvaMET = NAN;
    SVTransverseMass_responseDN_mvaMET = NAN;
    svMassMET.SetPtEtaPhiM( responseDOWN_mvaMET, 0.0, responseDOWN_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;

  }
  else if(METtoUSE == "MVAMET_RESOLUTIONUP")
  {
    SVMass_resolutionUP_mvaMET = NAN;
    SVTransverseMass_resolutionUP_mvaMET = NAN;
    svMassMET.SetPtEtaPhiM( resolutionUP_mvaMET, 0.0, resolutionUP_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;

  }
  else if(METtoUSE == "MVAMET_RESOLUTIONDOWN")
  {
    SVMass_resolutionDN_mvaMET = NAN;
    SVTransverseMass_resolutionDN_mvaMET = NAN;
    svMassMET.SetPtEtaPhiM( resolutionDOWN_mvaMET, 0.0, resolutionDOWN_mvaMETphi, 0.0 );
    covMET[0][0] = mvaMET_cov00;
    covMET[1][0] = mvaMET_cov10;
    covMET[0][1] = mvaMET_cov01;
    covMET[1][1] = mvaMET_cov11;

  }
  else if(METtoUSE == "PFMET")
  {
    SVMass_pfMET = NAN;
    SVTransverseMass_pfMET = NAN;
    svMassMET.SetPtEtaPhiM( pfMET, 0.0, pfMETphi, 0.0 );
    covMET[0][0] = pfMET_cov00;
    covMET[1][0] = pfMET_cov10;
    covMET[0][1] = pfMET_cov01;
    covMET[1][1] = pfMET_cov11;

  }
  else if(METtoUSE == "PUPPIMET")
  {
    SVMass_puppiMET = NAN;
    SVTransverseMass_puppiMET = NAN;
    svMassMET.SetPtEtaPhiM( puppiMET, 0.0, puppiMETphi, 0.0 );
    /* not sure what cov matrix to use with puppi met */
    covMET[0][0] = pfMET_cov00;
    covMET[1][0] = pfMET_cov10;
    covMET[0][1] = pfMET_cov01;
    covMET[1][1] = pfMET_cov11;
    std::cout<<" WARNING ... PUPPI MET using COV MATRIX FROM PF MET \n";

  }




//////////////////////////////////////////////////////
//////// begin an SVMass computation 

  std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
  measuredTauLeptons.clear();

  // new way to order legs for SV mass in 76X analysis 


  ////////////////////////////////////////////////////////
  // ele + ele choose higher pt leg to push back 1st    //
  ////////////////////////////////////////////////////////


  if(CandidateEventType == TupleCandidateEventTypes::EleEle)
  {
    if(currentPair.leg1().p4().pt() >= currentPair.leg2().p4().pt())
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::electronMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::electronMass));

    }
    else
    {
      
      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::electronMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::electronMass));

    }
  }

  ////////////////////////////////////////////////////////
  // mu + mu choose higher pt leg to push back 1st    //
  ////////////////////////////////////////////////////////


  if(CandidateEventType == TupleCandidateEventTypes::MuonMuon)
  {
    if(currentPair.leg1().p4().pt() >= currentPair.leg2().p4().pt())
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::muonMass));


      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::muonMass));

      
    }
    else
    {


      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::muonMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::muonMass));

      
    }
  }

  ////////////////////////////////////////////////////////
  // tau + tau choose higher pt leg to push back 1st    //
  ////////////////////////////////////////////////////////


  if(CandidateEventType == TupleCandidateEventTypes::TauTau)
  {
  //  std::cout<<" Flat Decay Mode **** 1, 2 = "<<currentPair.leg1().decayMode()<<" "<<currentPair.leg2().decayMode()<<"\n";


    if(currentPair.leg1().p4().pt() >= currentPair.leg2().p4().pt())
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      currentPair.leg1().p4().mass(), currentPair.leg1().decayMode()));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      currentPair.leg2().p4().mass(), currentPair.leg2().decayMode()));

      
    }
    else
    {
      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      currentPair.leg2().p4().mass(), currentPair.leg2().decayMode()));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      currentPair.leg1().p4().mass(), currentPair.leg1().decayMode()));

    }
  }


  ////////////////////////////////////////////////////////
  // ele + mu choose ele leg to push back 1st    //
  ////////////////////////////////////////////////////////


  if(CandidateEventType == TupleCandidateEventTypes::EleMuon)
  {

    if(currentPair.leg1().leptonType() == TupleLeptonTypes::anElectron)
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::electronMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::muonMass));

    }

    else 
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::electronMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::muonMass));

    }

  }


  ////////////////////////////////////////////////////////
  // ele + tau choose ele leg to push back 1st    //
  ////////////////////////////////////////////////////////


  if(CandidateEventType == TupleCandidateEventTypes::EleTau)
  {

    if(currentPair.leg1().leptonType() == TupleLeptonTypes::anElectron)
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::electronMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      currentPair.leg2().p4().mass(), currentPair.leg2().decayMode()));

    }

    else 
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToElecDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::electronMass));


      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      currentPair.leg1().p4().mass(), currentPair.leg1().decayMode()));

    }

  }


  ////////////////////////////////////////////////////////
  // mu + tau choose mu leg to push back 1st    //
  ////////////////////////////////////////////////////////

 if(CandidateEventType == TupleCandidateEventTypes::MuonTau)
  {

    if(currentPair.leg1().leptonType() == TupleLeptonTypes::aMuon)
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      svFitStandalone::muonMass));

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      currentPair.leg2().p4().mass(), currentPair.leg2().decayMode()));

    }

    else 
    {

      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToMuDecay, 
      currentPair.leg2().p4().pt(),currentPair.leg2().p4().eta(),currentPair.leg2().p4().phi(),
      svFitStandalone::muonMass));


      measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
      svFitStandalone::kTauToHadDecay,
      currentPair.leg1().p4().pt(),currentPair.leg1().p4().eta(),currentPair.leg1().p4().phi(),
      currentPair.leg1().p4().mass(), currentPair.leg1().decayMode()));

    }

  }


  if (flatTuple_svMassVerbose)  covMET.Print();

  SVfitStandaloneAlgorithm svFitAlgorithm(measuredTauLeptons, svMassMET.Px(),svMassMET.Py(), covMET, flatTuple_svMassVerbose);

  if(flatTuple_logMterm>0)  svFitAlgorithm.addLogM(true, flatTuple_logMterm);
  else svFitAlgorithm.addLogM(false, 0.);


  //std::cout<<" shiftVisPt turned off \n";

  svFitAlgorithm.shiftVisPt(true, inputFile_visPtResolution);

  svFitAlgorithm.integrateMarkovChain();
  
  //  svFitAlgorithm.integrateVEGAS();

  /* set the fitted diTau pt, eta, phi, mass, and MT */

  /*  double temp_SVMass = svFitAlgorithm.getMass();
  double temp_SVPt = svFitAlgorithm.pt();
  double temp_SVEta = svFitAlgorithm.eta();
  double temp_SVPhi = svFitAlgorithm.phi();
  double temp_SVTransverseMass = svFitAlgorithm.transverseMass();
  */

  /* set the fitted MET */

  /*TLorentzVector temp_SVFitted_MET(0.,0.,0.,0.);
  temp_SVFitted_MET.SetPxPyPzE(svFitAlgorithm.fittedMET().x(),svFitAlgorithm.fittedMET().y(),svFitAlgorithm.fittedMET().z(),0.); 
  */

  /* Dummy variables with no SVFit , set the fitted diTau pt, eta, phi, mass, and MT */

  double temp_SVMass = -999.0;                                                                                                                                             
  double temp_SVPt = -999.0;
  double temp_SVEta = -999.0;
  double temp_SVPhi = -999.0;
  double temp_SVTransverseMass = -999.0;

  /* set the fitted MET */

  TLorentzVector temp_SVFitted_MET(0.,0.,0.,0.);
  temp_SVFitted_MET.SetPxPyPzE(svFitAlgorithm.fittedMET().x(),svFitAlgorithm.fittedMET().y(),svFitAlgorithm.fittedMET().z(),0.); 

  if(METtoUSE == "MVAMET_CORR")
  {
    SVMass = temp_SVMass;
    SVTransverseMass = temp_SVTransverseMass;
    SVFit_mvaMET_diTau_pt = temp_SVPt;
    SVFit_mvaMET_diTau_eta = temp_SVEta;
    SVFit_mvaMET_diTau_phi = temp_SVPhi;    
    SVFit_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }  
  else if(METtoUSE == "MVAMET_UNCORR")
  {
    SVMass_uncorr_mvaMET = temp_SVMass;
    SVTransverseMass_uncorr_mvaMET = temp_SVTransverseMass; 
    SVFit_uncorr_mvaMET_diTau_pt = temp_SVPt;
    SVFit_uncorr_mvaMET_diTau_eta = temp_SVEta;
    SVFit_uncorr_mvaMET_diTau_phi = temp_SVPhi;      
    SVFit_uncorr_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_uncorr_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "MVAMET_RESPONSEUP")
  {
    SVMass_responseUP_mvaMET = temp_SVMass;
    SVTransverseMass_responseUP_mvaMET = temp_SVTransverseMass;   
    SVFit_responseUP_mvaMET_diTau_pt = temp_SVPt;
    SVFit_responseUP_mvaMET_diTau_eta = temp_SVEta;
    SVFit_responseUP_mvaMET_diTau_phi = temp_SVPhi;
    SVFit_responseUP_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_responseUP_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "MVAMET_RESPONSEDOWN")
  {
    SVMass_responseDN_mvaMET = temp_SVMass;
    SVTransverseMass_responseDN_mvaMET = temp_SVTransverseMass;
    SVFit_responseDN_mvaMET_diTau_pt = temp_SVPt;
    SVFit_responseDN_mvaMET_diTau_eta = temp_SVEta;
    SVFit_responseDN_mvaMET_diTau_phi = temp_SVPhi;
    SVFit_responseDN_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_responseDN_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "MVAMET_RESOLUTIONUP")
  {
    SVMass_resolutionUP_mvaMET = temp_SVMass;
    SVTransverseMass_resolutionUP_mvaMET = temp_SVTransverseMass;
    SVFit_resolutionUP_mvaMET_diTau_pt = temp_SVPt;
    SVFit_resolutionUP_mvaMET_diTau_eta = temp_SVEta;
    SVFit_resolutionUP_mvaMET_diTau_phi = temp_SVPhi;
    SVFit_resolutionUP_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_resolutionUP_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "MVAMET_RESOLUTIONDOWN")
  {
    SVMass_resolutionDN_mvaMET = temp_SVMass;
    SVTransverseMass_resolutionDN_mvaMET = temp_SVTransverseMass;
    SVFit_resolutionDN_mvaMET_diTau_pt = temp_SVPt;
    SVFit_resolutionDN_mvaMET_diTau_eta = temp_SVEta;
    SVFit_resolutionDN_mvaMET_diTau_phi = temp_SVPhi;
    SVFit_resolutionDN_mvaMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_resolutionDN_mvaMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "PFMET")
  {
    SVMass_pfMET = temp_SVMass;
    SVTransverseMass_pfMET = temp_SVTransverseMass;
    SVFit_pfMET_diTau_pt = temp_SVPt;
    SVFit_pfMET_diTau_eta = temp_SVEta;
    SVFit_pfMET_diTau_phi = temp_SVPhi;
    SVFit_pfMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_pfMET_FittedMETphi = temp_SVFitted_MET.Phi();
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }
  else if(METtoUSE == "PUPPIMET")
  {
    SVMass_puppiMET = temp_SVMass;
    SVTransverseMass_puppiMET = temp_SVTransverseMass;
    SVFit_puppiMET_diTau_pt = temp_SVPt;
    SVFit_puppiMET_diTau_eta = temp_SVEta;
    SVFit_puppiMET_diTau_phi = temp_SVPhi;
    SVFit_puppiMET_FittedMET = temp_SVFitted_MET.Pt();
    SVFit_puppiMET_FittedMETphi = temp_SVFitted_MET.Phi();    
    if (flatTuple_svMassVerbose) std::cout<<"SVFIT with "<<METtoUSE<<" (Mass, MT) = ( "<<temp_SVMass<<" , "<<temp_SVTransverseMass<<" ) \n";
  }


////////////// END SV MASS COMP ///////////////////////////////  

}


void FlatTupleGenerator::handleCurrentEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup,
NtupleEvent currentPair)
{

  

  //////////////////////////////
  // fill info that is accessed directly from the
  // current pair (i.e. not legs or EffLeptons)

  CandidateEventType = currentPair.CandidateEventType();
  isBoostedChannelPair = currentPair.isBoostedChannel();

  pfMET = currentPair.pfMET()[0].pt();
  pfMETphi = currentPair.pfMET()[0].phi();      
  pfMET_cov00 = currentPair.pfMET_cov00()[0];
  pfMET_cov01 = currentPair.pfMET_cov01()[0];
  pfMET_cov10 = currentPair.pfMET_cov10()[0];
  pfMET_cov11 = currentPair.pfMET_cov11()[0];  
  
  
  puppiMET  = currentPair.puppiMET()[0].pt();
  puppiMETphi = currentPair.puppiMET()[0].phi();
  RAWpuppiMET = currentPair.puppiMET()[0].uncorPt();
  RAWpuppiMETphi = currentPair.puppiMET()[0].uncorPhi();

  /* items with no meaning for EffLepton candidates */
  if(CandidateEventType!=TupleCandidateEventTypes::EffCand) 
  {
  
    TauEsNumberSigmasShifted = currentPair.TauEsNumberSigmasShifted(); 
    ElectronEsNumberSigmasShifted = currentPair.ElectronEsNumberSigmasShifted(); 
    isOsPair = currentPair.isOsPair();
    SVMass = currentPair.SVMass()[0];
    VISMass = currentPair.VISMass()[0];   
    SVTransverseMass = currentPair.SVTransverseMass()[0];

    mvaMET_cov00 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][0];
    mvaMET_cov01 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][1];
    mvaMET_cov10 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][0];
    mvaMET_cov11 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][1];


    MTpfMET_leg1 = currentPair.MTpfMET_leg1()[0]; /* will be NAN for effCand case */
    MTpfMET_leg2 = currentPair.MTpfMET_leg2()[0];

    MTpuppiMET_leg1  = currentPair.MTpuppiMET_leg1()[0];
    MTpuppiMET_leg2  = currentPair.MTpuppiMET_leg2()[0];


  }






  //RAWpfMET = currentPair.pfMET()[0].uncorPt();
  //RAWpfMETphi = currentPair.pfMET()[0].uncorPhi();

  if(!currentPair.pfMET()[0].genMET())
  {
    genMET = 0;
    genMETphi = 0;
    genMETeta = 0;
    genMETmass = 0;

  } 
  else 
  {
   
    genMET = currentPair.pfMET()[0].genMET()->pt();
    genMETphi = currentPair.pfMET()[0].genMET()->phi();
    genMETeta = currentPair.pfMET()[0].genMET()->eta();
    genMETmass = currentPair.pfMET()[0].genMET()->mass();

  }

  //std::cout<<" SZSMET genMET "<<genMET<<" , "<<genMETphi<<" "<<genMETeta<<" "<<genMETmass<<"\n";


  /* for pfMET access each of the correction levels as well as the variants */


  GetPFMetVariant(currentPair, pat::MET::NoShift , pat::MET::Raw,
                   pfmet_raw_Pt , pfmet_raw_Phi ,
                   pfmet_raw_MT1 , pfmet_raw_MT2 );

  GetPFMetVariant(currentPair, pat::MET::NoShift , pat::MET::Type1,
                   pfmet_type1_Pt , pfmet_type1_Phi ,
                   pfmet_type1_MT1 , pfmet_type1_MT2 );

  GetPFMetVariant(currentPair, pat::MET::JetResUp , pat::MET::Type1,
                   pfmet_type1_JetResUp_Pt , pfmet_type1_JetResUp_Phi ,
                   pfmet_type1_JetResUp_MT1 , pfmet_type1_JetResUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::JetResDown , pat::MET::Type1,
                   pfmet_type1_JetResDown_Pt , pfmet_type1_JetResDown_Phi ,
                   pfmet_type1_JetResDown_MT1 , pfmet_type1_JetResDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::JetEnUp , pat::MET::Type1,
                   pfmet_type1_JetEnUp_Pt , pfmet_type1_JetEnUp_Phi ,
                   pfmet_type1_JetEnUp_MT1 , pfmet_type1_JetEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::JetEnDown , pat::MET::Type1,
                   pfmet_type1_JetEnDown_Pt , pfmet_type1_JetEnDown_Phi ,
                   pfmet_type1_JetEnDown_MT1 , pfmet_type1_JetEnDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::MuonEnUp , pat::MET::Type1,
                   pfmet_type1_MuonEnUp_Pt , pfmet_type1_MuonEnUp_Phi ,
                   pfmet_type1_MuonEnUp_MT1 , pfmet_type1_MuonEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::MuonEnDown , pat::MET::Type1,
                   pfmet_type1_MuonEnDown_Pt , pfmet_type1_MuonEnDown_Phi ,
                   pfmet_type1_MuonEnDown_MT1 , pfmet_type1_MuonEnDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::ElectronEnUp , pat::MET::Type1,
                   pfmet_type1_ElectronEnUp_Pt , pfmet_type1_ElectronEnUp_Phi ,
                   pfmet_type1_ElectronEnUp_MT1 , pfmet_type1_ElectronEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::ElectronEnDown , pat::MET::Type1,
                   pfmet_type1_ElectronEnDown_Pt , pfmet_type1_ElectronEnDown_Phi ,
                   pfmet_type1_ElectronEnDown_MT1 , pfmet_type1_ElectronEnDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::TauEnUp , pat::MET::Type1,
                   pfmet_type1_TauEnUp_Pt , pfmet_type1_TauEnUp_Phi ,
                   pfmet_type1_TauEnUp_MT1 , pfmet_type1_TauEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::TauEnDown , pat::MET::Type1,
                   pfmet_type1_TauEnDown_Pt , pfmet_type1_TauEnDown_Phi ,
                   pfmet_type1_TauEnDown_MT1 , pfmet_type1_TauEnDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::UnclusteredEnUp , pat::MET::Type1,
                   pfmet_type1_UnclusteredEnUp_Pt , pfmet_type1_UnclusteredEnUp_Phi ,
                   pfmet_type1_UnclusteredEnUp_MT1 , pfmet_type1_UnclusteredEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::UnclusteredEnDown , pat::MET::Type1,
                   pfmet_type1_UnclusteredEnDown_Pt , pfmet_type1_UnclusteredEnDown_Phi ,
                   pfmet_type1_UnclusteredEnDown_MT1 , pfmet_type1_UnclusteredEnDown_MT2 );

  GetPFMetVariant(currentPair, pat::MET::PhotonEnUp , pat::MET::Type1,
                   pfmet_type1_PhotonEnUp_Pt , pfmet_type1_PhotonEnUp_Phi ,
                   pfmet_type1_PhotonEnUp_MT1 , pfmet_type1_PhotonEnUp_MT2 );

  GetPFMetVariant(currentPair, pat::MET::PhotonEnDown , pat::MET::Type1,
                   pfmet_type1_PhotonEnDown_Pt , pfmet_type1_PhotonEnDown_Phi ,
                   pfmet_type1_PhotonEnDown_MT1 , pfmet_type1_PhotonEnDown_MT2 );



  // std::cout<<"pfmet_raw: "<<pfmet_raw_Pt<<" , "<<pfmet_raw_Phi<<" , "<<pfmet_raw_MT1<<" , "<<pfmet_raw_MT2<<"\n";
  // std::cout<<"pfmet_type1_JetResUp: "<<pfmet_type1_JetResUp_Pt<<" , "<<pfmet_type1_JetResUp_Phi<<" , "<<pfmet_type1_JetResUp_MT1<<" , "<<pfmet_type1_JetResUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_JetResDown: "<<pfmet_type1_JetResDown_Pt<<" , "<<pfmet_type1_JetResDown_Phi<<" , "<<pfmet_type1_JetResDown_MT1<<" , "<<pfmet_type1_JetResDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_JetEnUp: "<<pfmet_type1_JetEnUp_Pt<<" , "<<pfmet_type1_JetEnUp_Phi<<" , "<<pfmet_type1_JetEnUp_MT1<<" , "<<pfmet_type1_JetEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_JetEnDown: "<<pfmet_type1_JetEnDown_Pt<<" , "<<pfmet_type1_JetEnDown_Phi<<" , "<<pfmet_type1_JetEnDown_MT1<<" , "<<pfmet_type1_JetEnDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_MuonEnUp: "<<pfmet_type1_MuonEnUp_Pt<<" , "<<pfmet_type1_MuonEnUp_Phi<<" , "<<pfmet_type1_MuonEnUp_MT1<<" , "<<pfmet_type1_MuonEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_MuonEnDown: "<<pfmet_type1_MuonEnDown_Pt<<" , "<<pfmet_type1_MuonEnDown_Phi<<" , "<<pfmet_type1_MuonEnDown_MT1<<" , "<<pfmet_type1_MuonEnDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_ElectronEnUp: "<<pfmet_type1_ElectronEnUp_Pt<<" , "<<pfmet_type1_ElectronEnUp_Phi<<" , "<<pfmet_type1_ElectronEnUp_MT1<<" , "<<pfmet_type1_ElectronEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_ElectronEnDown: "<<pfmet_type1_ElectronEnDown_Pt<<" , "<<pfmet_type1_ElectronEnDown_Phi<<" , "<<pfmet_type1_ElectronEnDown_MT1<<" , "<<pfmet_type1_ElectronEnDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_TauEnUp: "<<pfmet_type1_TauEnUp_Pt<<" , "<<pfmet_type1_TauEnUp_Phi<<" , "<<pfmet_type1_TauEnUp_MT1<<" , "<<pfmet_type1_TauEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_TauEnDown: "<<pfmet_type1_TauEnDown_Pt<<" , "<<pfmet_type1_TauEnDown_Phi<<" , "<<pfmet_type1_TauEnDown_MT1<<" , "<<pfmet_type1_TauEnDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_UnclusteredEnUp: "<<pfmet_type1_UnclusteredEnUp_Pt<<" , "<<pfmet_type1_UnclusteredEnUp_Phi<<" , "<<pfmet_type1_UnclusteredEnUp_MT1<<" , "<<pfmet_type1_UnclusteredEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_UnclusteredEnDown: "<<pfmet_type1_UnclusteredEnDown_Pt<<" , "<<pfmet_type1_UnclusteredEnDown_Phi<<" , "<<pfmet_type1_UnclusteredEnDown_MT1<<" , "<<pfmet_type1_UnclusteredEnDown_MT2<<"\n";
  // std::cout<<"pfmet_type1_PhotonEnUp: "<<pfmet_type1_PhotonEnUp_Pt<<" , "<<pfmet_type1_PhotonEnUp_Phi<<" , "<<pfmet_type1_PhotonEnUp_MT1<<" , "<<pfmet_type1_PhotonEnUp_MT2<<"\n";
  // std::cout<<"pfmet_type1_PhotonEnDown: "<<pfmet_type1_PhotonEnDown_Pt<<" , "<<pfmet_type1_PhotonEnDown_Phi<<" , "<<pfmet_type1_PhotonEnDown_MT1<<" , "<<pfmet_type1_PhotonEnDown_MT2<<"\n";


  /* fill veto lepton parameters, MUST FILL IN SAME ORDER FOR ELECTRONS & MUONS */


  StringCutObjectSelector <NtupleLepton> apply_thirdEleVeto(thirdEleVeto);
  StringCutObjectSelector <NtupleLepton> apply_thirdMuonVeto(thirdMuonVeto);
  StringCutObjectSelector <NtupleLepton> apply_diEleVeto(diEleVeto);
  StringCutObjectSelector <NtupleLepton> apply_diMuonVeto(diMuonVeto);

  /* reset flags */

  DiMuon_Flag = 0.;
  DiElectron_Flag = 0.;
  ThirdMuon_Flag  = 0.;
  ThirdElectron_Flag  = 0.;


  for(std::size_t v = 0; v<currentPair.vetoElectron().size(); ++v)
  {

     // std::cout<<" ele @ "<<v<<" has 3rd lep cuts (without DR leg1, and DR leg2) = "<<apply_thirdEleVeto(currentPair.vetoElectron()[v]);
     // std::cout<<" and diElectron cuts = "<<apply_diEleVeto(currentPair.vetoElectron()[v])<<"\n";


      veto_leptonType.push_back(currentPair.vetoElectron()[v].leptonType());
      veto_pt.push_back(currentPair.vetoElectron()[v].p4().pt());
      veto_eta.push_back(currentPair.vetoElectron()[v].p4().eta());
      veto_phi.push_back(currentPair.vetoElectron()[v].p4().phi());
      veto_M.push_back(currentPair.vetoElectron()[v].p4().M());
      veto_dxy.push_back(currentPair.vetoElectron()[v].dxy());
      veto_dz.push_back(currentPair.vetoElectron()[v].dz());
      veto_passesLooseMuonId.push_back(currentPair.vetoElectron()[v].passesLooseMuonId());
      veto_passesMediumMuonId_ICHEP16.push_back(currentPair.vetoElectron()[v].passesMediumMuonId_ICHEP16());
      veto_passesMediumMuonId_Moriond17.push_back(currentPair.vetoElectron()[v].passesMediumMuonId_Moriond17());
      veto_passesMediumMuonId.push_back(currentPair.vetoElectron()[v].passesMediumMuonId());
      veto_passesTightMuonId.push_back(currentPair.vetoElectron()[v].passesTightMuonId());
      veto_rawElectronMVA.push_back(currentPair.vetoElectron()[v].raw_electronMVA());
      veto_categoryElectronMVA.push_back(currentPair.vetoElectron()[v].category_electronMVA());
      veto_passElectronMVA80.push_back(currentPair.vetoElectron()[v].passFail_electronMVA80());
      veto_passElectronMVA90.push_back(currentPair.vetoElectron()[v].passFail_electronMVA90());
      veto_passVetoElectronCutBased.push_back(currentPair.vetoElectron()[v].passFail_VetoElectronCutBasedID());
      veto_passTightElectronCutBased.push_back(currentPair.vetoElectron()[v].passFail_TightElectronCutBasedID());
      veto_isTrackerGlobalPFMuon.push_back(0.0);         
      veto_RelIso.push_back(currentPair.vetoElectron()[v].relativeIsol(electronIsolationForRelIsoBranch));
      veto_charge.push_back(currentPair.vetoElectron()[v].charge());
      veto_numberOfMissingInnerHits.push_back(currentPair.vetoElectron()[v].numberOfMissingInnerHits());
      veto_numberOfMissingOuterHits.push_back(currentPair.vetoElectron()[v].numberOfMissingOuterHits());
      veto_passConversionVeto.push_back(currentPair.vetoElectron()[v].passConversionVeto());

      int passThirdVetoCuts_ = apply_thirdEleVeto(currentPair.vetoElectron()[v]);

      /* check if overlaps any of the electron legs, if it does set the flag to 0 */

      if(currentPair.leg1().leptonType()==TupleLeptonTypes::anElectron &&\
        deltaR(currentPair.leg1().p4(),currentPair.vetoElectron()[v].p4())<=legThirdLeptonMinDR)
        {
          passThirdVetoCuts_ = 0;
        }
 
      if(currentPair.leg2().leptonType()==TupleLeptonTypes::anElectron &&\
         deltaR(currentPair.leg2().p4(),currentPair.vetoElectron()[v].p4())<=legThirdLeptonMinDR)
        {
          passThirdVetoCuts_ = 0;
        }

      veto_LeptonPassesThirdElectronVetoCuts.push_back(passThirdVetoCuts_);

      /* set event level flag to one if at least one e passes these cuts */
      if(passThirdVetoCuts_ == 1) ThirdElectron_Flag = 1.0; 
 

      /* apply the diElectron cuts */
      veto_LeptonPassesDiElectronVetoCuts.push_back(apply_diEleVeto(currentPair.vetoElectron()[v]));

      /* zeros for the muon cuts */
      veto_LeptonPassesThirdMuonVetoCuts.push_back(0);
      veto_LeptonPassesDiMuonVetoCuts.push_back(0);


      // fill the tauIDs for vetoLeptons (these need to be filled for electron and muon as -999)

      veto_ZimpactTau.push_back(-999.);
      veto_numStrips.push_back(-999.);
      veto_dzTauVertex.push_back(-999.);
      veto_numHadrons.push_back(-999.);

      veto_rerunDiscriminationByIsolationMVArun2v1raw.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VLoose.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Loose.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Medium.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Tight.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VTight.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VVTight.push_back(-999.);


      veto_decayMode.push_back(-999);


      for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
      {
        veto_tauIDs.at(x).second.push_back( -999. );                   
      }

  }



  for(std::size_t v = 0; v<currentPair.vetoMuon().size(); ++v)
  {

     // std::cout<<" muon @ "<<v<<" has 3rd lep cuts (without DR leg1, and DR leg2) = "<<apply_thirdMuonVeto(currentPair.vetoMuon()[v]);
     // std::cout<<" and diMuon cuts = "<<apply_diMuonVeto(currentPair.vetoMuon()[v])<<"\n";


      veto_leptonType.push_back(currentPair.vetoMuon()[v].leptonType());
      veto_pt.push_back(currentPair.vetoMuon()[v].p4().pt());
      veto_eta.push_back(currentPair.vetoMuon()[v].p4().eta());
      veto_phi.push_back(currentPair.vetoMuon()[v].p4().phi());
      veto_M.push_back(currentPair.vetoMuon()[v].p4().M());
      veto_dxy.push_back(currentPair.vetoMuon()[v].dxy());
      veto_dz.push_back(currentPair.vetoMuon()[v].dz());
      veto_passesLooseMuonId.push_back(currentPair.vetoMuon()[v].passesLooseMuonId());
      veto_passesMediumMuonId_ICHEP16.push_back(currentPair.vetoMuon()[v].passesMediumMuonId_ICHEP16());
      veto_passesMediumMuonId_Moriond17.push_back(currentPair.vetoMuon()[v].passesMediumMuonId_Moriond17());
      veto_passesMediumMuonId.push_back(currentPair.vetoMuon()[v].passesMediumMuonId());
      veto_passesTightMuonId.push_back(currentPair.vetoMuon()[v].passesTightMuonId());
      veto_rawElectronMVA.push_back(currentPair.vetoMuon()[v].raw_electronMVA());
      veto_categoryElectronMVA.push_back(currentPair.vetoMuon()[v].category_electronMVA());
      veto_passElectronMVA80.push_back(currentPair.vetoMuon()[v].passFail_electronMVA80());
      veto_passElectronMVA90.push_back(currentPair.vetoMuon()[v].passFail_electronMVA90());
      veto_passVetoElectronCutBased.push_back(currentPair.vetoMuon()[v].passFail_VetoElectronCutBasedID());
      veto_passTightElectronCutBased.push_back(currentPair.vetoMuon()[v].passFail_TightElectronCutBasedID());

     


      float isTrackerGlobalPFMuon = (currentPair.vetoMuon()[v].isTrackerMuon() && \
                                     currentPair.vetoMuon()[v].isGlobalMuon() && \
                                     currentPair.vetoMuon()[v].isPFMuon());
      

      veto_isTrackerGlobalPFMuon.push_back(isTrackerGlobalPFMuon);         
      veto_RelIso.push_back(currentPair.vetoMuon()[v].relativeIsol(muonIsolationForRelIsoBranch));
      veto_charge.push_back(currentPair.vetoMuon()[v].charge());
      veto_numberOfMissingInnerHits.push_back(currentPair.vetoMuon()[v].numberOfMissingInnerHits());
      veto_numberOfMissingOuterHits.push_back(currentPair.vetoMuon()[v].numberOfMissingOuterHits());      
      veto_passConversionVeto.push_back(currentPair.vetoMuon()[v].passConversionVeto());

      /* zeros for the ele cuts */
      veto_LeptonPassesThirdElectronVetoCuts.push_back(0);
      veto_LeptonPassesDiElectronVetoCuts.push_back(0);


      int passThirdVetoCuts_ = apply_thirdMuonVeto(currentPair.vetoMuon()[v]);

      /* check if overlaps any of the muon legs, if it does set the flag to 0 */

      if(currentPair.leg1().leptonType()==TupleLeptonTypes::aMuon &&\
        deltaR(currentPair.leg1().p4(),currentPair.vetoMuon()[v].p4())<=legThirdLeptonMinDR)
        {
          passThirdVetoCuts_ = 0;
        }
 
      if(currentPair.leg2().leptonType()==TupleLeptonTypes::aMuon &&\
         deltaR(currentPair.leg2().p4(),currentPair.vetoMuon()[v].p4())<=legThirdLeptonMinDR)
        {
          passThirdVetoCuts_ = 0;
        }

      veto_LeptonPassesThirdMuonVetoCuts.push_back(passThirdVetoCuts_);   

      /* set event level flag to one if at least one mu passes these cuts */
      if(passThirdVetoCuts_ == 1) ThirdMuon_Flag = 1.0; 
 
      /* apply the di-Muon cuts */
      veto_LeptonPassesDiMuonVetoCuts.push_back(apply_diMuonVeto(currentPair.vetoMuon()[v]));


      ////////////////////////////////
      // fill the tauIDs for vetoLeptons (these need to be filled for electron and muon as -999)

      veto_ZimpactTau.push_back(-999.);
      veto_numStrips.push_back(-999.);
      veto_dzTauVertex.push_back(-999.);
      veto_numHadrons.push_back(-999.);

      veto_rerunDiscriminationByIsolationMVArun2v1raw.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VLoose.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Loose.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Medium.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1Tight.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VTight.push_back(-999.);
      veto_rerunDiscriminationByIsolationMVArun2v1VVTight.push_back(-999.);

      veto_decayMode.push_back(-999);

      for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
      {
        veto_tauIDs.at(x).second.push_back( -999. );                   
      }


  }



  for(std::size_t v = 0; v<currentPair.vetoTau().size(); ++v)
  {

    /* for taus we will just store them and not apply a veto here 
    cuts can be applied at sync level */

    bool DoesNotOverlapALeg = 1;

    /* check if overlaps any of the Higgs legs, if it does set the flag to 0 */

    if(currentPair.leg1().leptonType()==TupleLeptonTypes::aTau &&\
      deltaR(currentPair.leg1().p4(),currentPair.vetoTau()[v].p4())<=legThirdLeptonMinDR)
      {
        DoesNotOverlapALeg = 0;
      }

    if(currentPair.leg2().leptonType()==TupleLeptonTypes::aTau &&\
       deltaR(currentPair.leg2().p4(),currentPair.vetoTau()[v].p4())<=legThirdLeptonMinDR)
      {
        DoesNotOverlapALeg = 0;
      }

    if(DoesNotOverlapALeg==1)
    {

      veto_leptonType.push_back(currentPair.vetoTau()[v].leptonType());
      veto_pt.push_back(currentPair.vetoTau()[v].p4().pt());
      veto_eta.push_back(currentPair.vetoTau()[v].p4().eta());
      veto_phi.push_back(currentPair.vetoTau()[v].p4().phi());
      veto_M.push_back(currentPair.vetoTau()[v].p4().M());
      veto_dxy.push_back(currentPair.vetoTau()[v].dxy());
      veto_dz.push_back(currentPair.vetoTau()[v].dz());
      veto_passesLooseMuonId.push_back(currentPair.vetoTau()[v].passesLooseMuonId());
      veto_passesMediumMuonId_ICHEP16.push_back(currentPair.vetoTau()[v].passesMediumMuonId_ICHEP16());
      veto_passesMediumMuonId_Moriond17.push_back(currentPair.vetoTau()[v].passesMediumMuonId_Moriond17());
      veto_passesMediumMuonId.push_back(currentPair.vetoTau()[v].passesMediumMuonId());
      veto_passesTightMuonId.push_back(currentPair.vetoTau()[v].passesTightMuonId());
      veto_rawElectronMVA.push_back(currentPair.vetoTau()[v].raw_electronMVA());
      veto_categoryElectronMVA.push_back(currentPair.vetoTau()[v].category_electronMVA());
      veto_passElectronMVA80.push_back(currentPair.vetoTau()[v].passFail_electronMVA80());
      veto_passElectronMVA90.push_back(currentPair.vetoTau()[v].passFail_electronMVA90());
      veto_passVetoElectronCutBased.push_back(currentPair.vetoTau()[v].passFail_VetoElectronCutBasedID());
      veto_passTightElectronCutBased.push_back(currentPair.vetoTau()[v].passFail_TightElectronCutBasedID());
     
      float isTrackerGlobalPFMuon = (currentPair.vetoTau()[v].isTrackerMuon() && \
                                     currentPair.vetoTau()[v].isGlobalMuon() && \
                                     currentPair.vetoTau()[v].isPFMuon());
      

      veto_isTrackerGlobalPFMuon.push_back(isTrackerGlobalPFMuon);         
      veto_charge.push_back(currentPair.vetoTau()[v].charge());
      veto_numberOfMissingInnerHits.push_back(currentPair.vetoTau()[v].numberOfMissingInnerHits());
      veto_numberOfMissingOuterHits.push_back(currentPair.vetoTau()[v].numberOfMissingOuterHits());      
      veto_passConversionVeto.push_back(currentPair.vetoTau()[v].passConversionVeto());

      /* zeros for the ele cuts */
      veto_LeptonPassesThirdElectronVetoCuts.push_back(0);
      veto_LeptonPassesDiElectronVetoCuts.push_back(0);

      /* zeros for the muon cust */
      veto_LeptonPassesThirdMuonVetoCuts.push_back(0);   
      veto_LeptonPassesDiMuonVetoCuts.push_back(0);



      ////////////////////////////////
      // fill the tauIDs for veto Taus


      veto_ZimpactTau.push_back(currentPair.vetoTau().at(v).ZimpactTau());
      veto_numStrips.push_back(currentPair.vetoTau().at(v).numStrips());
      veto_dzTauVertex.push_back(currentPair.vetoTau().at(v).dzTauVertex());
      veto_numHadrons.push_back(currentPair.vetoTau().at(v).numHadrons());

      veto_rerunDiscriminationByIsolationMVArun2v1raw.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1raw());
      veto_rerunDiscriminationByIsolationMVArun2v1VLoose.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1VLoose());
      veto_rerunDiscriminationByIsolationMVArun2v1Loose.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1Loose());
      veto_rerunDiscriminationByIsolationMVArun2v1Medium.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1Medium());
      veto_rerunDiscriminationByIsolationMVArun2v1Tight.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1Tight());
      veto_rerunDiscriminationByIsolationMVArun2v1VTight.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1VTight());
      veto_rerunDiscriminationByIsolationMVArun2v1VVTight.push_back(currentPair.vetoTau().at(v).rerunDiscriminationByIsolationMVArun2v1VVTight());




      veto_decayMode.push_back(currentPair.vetoTau().at(v).decayMode());

      for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
      {      
        veto_tauIDs.at(x).second.push_back( currentPair.vetoTau().at(v).tauID(tauIDsToKeep[x]) );            
      }

      //// isolation 
      float tau_relIso_temp = -999.;

      if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau)
      {
            tau_relIso_temp = currentPair.vetoTau()[v].tauID(tauIsolationForRelIsoBranch_forEleTau);
      }
      else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
      {
            tau_relIso_temp = currentPair.vetoTau()[v].tauID(tauIsolationForRelIsoBranch_forMuTau);
      }
      else if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
      {
            tau_relIso_temp = currentPair.vetoTau()[v].tauID(tauIsolationForRelIsoBranch_forTauTau);
      }
      else tau_relIso_temp = currentPair.vetoTau()[v].tauID(tauIsolationForRelIsoBranch);

      veto_RelIso.push_back(tau_relIso_temp);




      ///////////////




    } // tau does not overlap leg 1 or 2        
  } // loop on veto taus



  /* now apply the event level vetos for di-Muon and di-Electrons */

  for(std::size_t p1 = 0; p1<veto_LeptonPassesDiElectronVetoCuts.size(); ++p1)
  {
    for(std::size_t p2 = 0; p2<veto_LeptonPassesDiElectronVetoCuts.size(); ++p2)
    {
      if(p1 != p2 &&\
        veto_LeptonPassesDiElectronVetoCuts[p1]==1.0 &&\
        veto_LeptonPassesDiElectronVetoCuts[p2]==1.0 &&\
        veto_charge[p1]+veto_charge[p2] == 0)
      {

        TLorentzVector v1, v2;
        v1.SetPtEtaPhiM(veto_pt[p1],veto_eta[p1],veto_phi[p1],veto_M[p1]);
        v2.SetPtEtaPhiM(veto_pt[p2],veto_eta[p2],veto_phi[p2],veto_M[p2]);
        if(v1.DeltaR(v2) > diLeptonMinDR ) 
        {
          DiElectron_Flag = 1.0;
          break;
        }
      }  
    }
  }


  for(std::size_t p1 = 0; p1<veto_LeptonPassesDiMuonVetoCuts.size(); ++p1)
  {
    for(std::size_t p2 = 0; p2<veto_LeptonPassesDiMuonVetoCuts.size(); ++p2)
    {
      if(p1 != p2 &&\
        veto_LeptonPassesDiMuonVetoCuts[p1]==1.0 &&\
        veto_LeptonPassesDiMuonVetoCuts[p2]==1.0 &&\
        veto_charge[p1]+veto_charge[p2] == 0)
      {

        TLorentzVector v1, v2;
        v1.SetPtEtaPhiM(veto_pt[p1],veto_eta[p1],veto_phi[p1],veto_M[p1]);
        v2.SetPtEtaPhiM(veto_pt[p2],veto_eta[p2],veto_phi[p2],veto_M[p2]);
        if(v1.DeltaR(v2) > diLeptonMinDR ) 
        {
          DiMuon_Flag = 1.0;
          break;
        }
      }  
    }
  }

 // std::cout<<" DiMuon Flag = "<<DiMuon_Flag<<" and DiElectron Flag = "<<DiElectron_Flag<<"\n";




  ////////////////////////////////////////////
  //bool KEEP_IT = 1;
  // if(applyPostSyncLeptonVetoes)
  // { 
  //   if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleMuon)
  //   {
  //     if(ThirdMuon_Flag > 0.5 || ThirdElectron_Flag > 0.5) KEEP_IT = 0;
  //   }
  //   if(currentPair.CandidateEventType()==TupleCandidateEventTypes::EleTau)
  //   {
  //     if(ThirdElectron_Flag > 0.5 || DiElectron_Flag > 0.5) KEEP_IT = 0;
  //   }
  //   if(currentPair.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
  //   {
  //     if(ThirdMuon_Flag > 0.5 || DiMuon_Flag > 0.5) KEEP_IT = 0;
  //   }
  //   if(currentPair.CandidateEventType()==TupleCandidateEventTypes::TauTau)
  //   {
  //     if(ThirdMuon_Flag > 0.5 || ThirdElectron_Flag > 0.5) KEEP_IT = 0;
  //   }
  // }

  // PassesExtraLepVeto = KEEP_IT;
  ////////////////////////////////////////////


}



void FlatTupleGenerator::handlePairIndepInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup,
  NtuplePairIndependentInfo currentINDEP)
{

  

  /* info about the event */

  run = iEvent.id().run();
  luminosityBlock = iEvent.id().luminosityBlock();
  event = iEvent.id().event();
  isRealData = iEvent.isRealData();
  treeInfoString = NAME_;
  RecoilCorrectionType = RECOILCORRECTION_;
  MetSystematicType = MetSystematicType_;

  /* should also add for boosted cuts -- low prioirity since this is just book keeping */
  AppliedLepCuts = LeptonCutHelper.getCutSummary(LeptonCutVecSrc_);


  /* info about the data sample */


  DataSet = currentINDEP.DataSet();
  EventTotal = currentINDEP.EventTotal();
  EventType = currentINDEP.EventType();
  KeyName = currentINDEP.KeyName();
  DataCard = currentINDEP.DataCard();
  CrossSection = currentINDEP.CrossSection();
  FilterEff = currentINDEP.FilterEff();
  CodeVersion = currentINDEP.CodeVersion();



  /* info about the primary vertex */
  NumberOfGoodVertices = currentINDEP.numberOfGoodVertices();
  vertex_NDOF = currentINDEP.primaryVertex().ndof();
  vertex_CHI2 = currentINDEP.primaryVertex().chi2();
  vertex_positionRho = currentINDEP.primaryVertex().position().Rho();
  vertex_positionX = currentINDEP.primaryVertex().position().x();
  vertex_positionY  = currentINDEP.primaryVertex().position().y();
  vertex_positionZ = currentINDEP.primaryVertex().position().z();
  vertex_positionTheta = currentINDEP.primaryVertex().position().theta();
  vertex_positionEta = currentINDEP.primaryVertex().position().eta();
  vertex_positionPhi = currentINDEP.primaryVertex().position().phi();

  /* MET filters */

  HBHENoiseFilter = currentINDEP.HBHENoiseFilter();
  HBHENoiseIsoFilter = currentINDEP.HBHENoiseIsoFilter();
  CSCTightHalo2015Filter = currentINDEP.CSCTightHalo2015Filter();
  EcalDeadCellTriggerPrimitiveFilter = currentINDEP.EcalDeadCellTriggerPrimitiveFilter();
  goodVerticesFilter = currentINDEP.goodVertices();
  eeBadScFilter = currentINDEP.eeBadScFilter();
  chargedHadronTrackResolutionFilter = currentINDEP.chargedHadronTrackResolutionFilter();
  muonBadTrackFilter = currentINDEP.muonBadTrackFilter();
  globalTightHalo2016Filter = currentINDEP.globalTightHalo2016Filter();
  BadChargedCandidateFilter = currentINDEP.BadChargedCandidateFilter();
  BadPFMuonFilter = currentINDEP.BadPFMuonFilter();

  /* bad and duplicate muons */

  BadMuonTaggedMoriond17 = currentINDEP.BadMuonTaggedMoriond17();
  DuplicateMuonTaggedMoriond17 = currentINDEP.DuplicateMuonTaggedMoriond17();



  /* pileup & other weights */

  puWeight = currentINDEP.puWeight();
  NumPileupInt = currentINDEP.NumPileupInt();
  NumTruePileUpInt = currentINDEP.NumTruePileUpInt();
  generatorEventWeight = currentINDEP.generatorEventWeight();
  hepNUP = currentINDEP.hepNUP();
  lheHT = currentINDEP.lheHT();
  lheOutGoingPartons = currentINDEP.lheOutGoingPartons();
  lheZmass = currentINDEP.lheZmass();



  /* 4-vectors of gen level boson */
  genBosonTotal_pt = currentINDEP.GenBosonTotalMomentum().pt();
  genBosonTotal_eta = currentINDEP.GenBosonTotalMomentum().eta();
  genBosonTotal_phi = currentINDEP.GenBosonTotalMomentum().phi();
  genBosonTotal_M = currentINDEP.GenBosonTotalMomentum().M();

  genBosonVisible_pt = currentINDEP.GenBosonVisibleMomentum().pt();
  genBosonVisible_eta = currentINDEP.GenBosonVisibleMomentum().eta();
  genBosonVisible_phi = currentINDEP.GenBosonVisibleMomentum().phi();
  genBosonVisible_M = currentINDEP.GenBosonVisibleMomentum().M();


  MaxPtGenBoson_WisconinStyle_pt = currentINDEP.MaxPtGenBoson_WisconinStyle().pt();
  MaxPtGenBoson_WisconinStyle_eta = currentINDEP.MaxPtGenBoson_WisconinStyle().eta();
  MaxPtGenBoson_WisconinStyle_phi = currentINDEP.MaxPtGenBoson_WisconinStyle().phi();
  MaxPtGenBoson_WisconinStyle_M = currentINDEP.MaxPtGenBoson_WisconinStyle().M();


  /* handle the jets - there is a slight dep. on leptons here due to DR cuts */



  /* get the jets and bjets passing the cuts provided in JetHelper init */
  std::vector<NtupleJet> goodJets = jethelper.PtOrderedPassingJets("fullyCorrected");

  std::vector<NtupleJet> goodJets_JECshiftedUp = jethelper.PtOrderedPassingJets("JECshiftedUp");

  std::vector<NtupleJet> goodJets_JECshiftedDown = jethelper.PtOrderedPassingJets("JECshiftedDown");

  std::vector<NtupleJet> goodJets_JERup = jethelper.PtOrderedPassingJets("JERup");

  std::vector<NtupleJet> goodJets_JERdown = jethelper.PtOrderedPassingJets("JERdown");

  numberOfJets =   goodJets.size();
  numberOfJets30 = 0;

  numberOfJets_JECshiftedUp =   goodJets_JECshiftedUp.size();
  numberOfJets30_JECshiftedUp = 0;

  numberOfJets_JECshiftedDown =   goodJets_JECshiftedDown.size();
  numberOfJets30_JECshiftedDown = 0;

  numberOfJets_JERup =   goodJets_JERup.size();
  numberOfJets30_JERup = 0;

  numberOfJets_JERdown =   goodJets_JERdown.size();
  numberOfJets30_JERdown = 0;


  /* compute the btag product scale factors */
  BtagEventSFproduct_looseWpDown = 1.0;
  BtagEventSFproduct_looseWpCentral = 1.0;
  BtagEventSFproduct_looseWpUp = 1.0;
  BtagEventSFproduct_mediumWpDown = 1.0;
  BtagEventSFproduct_mediumWpCentral = 1.0;
  BtagEventSFproduct_mediumWpUp = 1.0;
  BtagEventSFproduct_tightWpDown = 1.0;
  BtagEventSFproduct_tightWpCentral = 1.0;
  BtagEventSFproduct_tightWpUp = 1.0;
  BtagEventSFproduct_looseWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_mediumWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_tightWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_looseWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_mediumWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_tightWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_looseWpCentral_JERup = 1.0;
  BtagEventSFproduct_mediumWpCentral_JERup = 1.0;
  BtagEventSFproduct_tightWpCentral_JERup = 1.0;
  BtagEventSFproduct_looseWpCentral_JERdown = 1.0;
  BtagEventSFproduct_mediumWpCentral_JERdown = 1.0;
  BtagEventSFproduct_tightWpCentral_JERdown = 1.0;


  /* set the Wisconsin style zero b-tag event weights */

  jets_zero_btag_event_weight = jethelper.getZeroBtagEventSF("fullyCorrected","central", event);
  jets_zero_btag_event_weight_up = jethelper.getZeroBtagEventSF("fullyCorrected","up", event);
  jets_zero_btag_event_weight_down = jethelper.getZeroBtagEventSF("fullyCorrected","down", event);
  jets_JECshiftedUp_zero_btag_event_weight = jethelper.getZeroBtagEventSF("JECshiftedUp","central", event);
  jets_JECshiftedDown_zero_btag_event_weight = jethelper.getZeroBtagEventSF("JECshiftedDown","central", event);
  jets_JERup_zero_btag_event_weight = jethelper.getZeroBtagEventSF("JERup","central", event);
  jets_JERdown_zero_btag_event_weight = jethelper.getZeroBtagEventSF("JERdown","central", event);



  jets_zero_btag_event_weight_LOOSE = jethelper.getZeroBtagEventSF_LOOSE("fullyCorrected","central", event);
  jets_zero_btag_event_weight_LOOSE_up = jethelper.getZeroBtagEventSF_LOOSE("fullyCorrected","up", event);
  jets_zero_btag_event_weight_LOOSE_down = jethelper.getZeroBtagEventSF_LOOSE("fullyCorrected","down", event);
  jets_JECshiftedUp_zero_btag_event_weight_LOOSE = jethelper.getZeroBtagEventSF_LOOSE("JECshiftedUp","central", event);
  jets_JECshiftedDown_zero_btag_event_weight_LOOSE = jethelper.getZeroBtagEventSF_LOOSE("JECshiftedDown","central", event);
  jets_JERup_zero_btag_event_weight_LOOSE = jethelper.getZeroBtagEventSF_LOOSE("JERup","central", event);
  jets_JERdown_zero_btag_event_weight_LOOSE = jethelper.getZeroBtagEventSF_LOOSE("JERdown","central", event);




  /* now fill the FlatTuple jet vector */
  for(std::size_t j=0; j<goodJets.size(); ++j)
  {      

    goodJets[j].Use4VectorVariant("fullyCorrected"); 
    if(goodJets[j].jet_p4().pt()>30) numberOfJets30++;  
    jets_pt.push_back(goodJets[j].jet_p4().pt());
    jets_eta.push_back(goodJets[j].jet_p4().eta());
    jets_phi.push_back(goodJets[j].jet_p4().phi());
    jets_M.push_back(goodJets[j].jet_p4().M());

    jets_PU_jetIdRaw.push_back(goodJets[j].PU_jetIdRaw());
    jets_PU_jetIdPassed.push_back(goodJets[j].PU_jetIdPassed());
    jets_PF_jetIdPassed.push_back(goodJets[j].PF_jetIdPassed());
    jets_defaultBtagAlgorithm_RawScore.push_back(goodJets[j].defaultBtagAlgorithm_RawScore());
    jets_PARTON_flavour.push_back(goodJets[j].PARTON_flavour());
    jets_HADRON_flavour.push_back(goodJets[j].HADRON_flavour());

    jets_BtagSF_LooseWpCentral.push_back(goodJets[j].defaultBtagAlgorithmSF_LooseWpCentral());
    jets_BtagSF_LooseWpUp.push_back(goodJets[j].defaultBtagAlgorithmSF_LooseWpUp());
    jets_BtagSF_LooseWpDown.push_back(goodJets[j].defaultBtagAlgorithmSF_LooseWpDown());
    jets_BtagSF_MediumWpCentral.push_back(goodJets[j].defaultBtagAlgorithmSF_MediumWpCentral());
    jets_BtagSF_MediumWpUp.push_back(goodJets[j].defaultBtagAlgorithmSF_MediumWpUp());
    jets_BtagSF_MediumWpDown.push_back(goodJets[j].defaultBtagAlgorithmSF_MediumWpDown());
    jets_BtagSF_TightWpCentral.push_back(goodJets[j].defaultBtagAlgorithmSF_TightWpCentral());
    jets_BtagSF_TightWpUp.push_back(goodJets[j].defaultBtagAlgorithmSF_TightWpUp());
    jets_BtagSF_TightWpDown.push_back(goodJets[j].defaultBtagAlgorithmSF_TightWpDown());



    if(goodJets[j].defaultBtagAlgorithm_RawScore() > LooseCut) 
    {
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_LooseWpDown())) BtagEventSFproduct_looseWpDown *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_LooseWpDown()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_LooseWpCentral())) BtagEventSFproduct_looseWpCentral *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_LooseWpCentral()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_LooseWpUp())) BtagEventSFproduct_looseWpUp      *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_LooseWpUp()));
    }
    
    if(goodJets[j].defaultBtagAlgorithm_RawScore() > MediumCut) 
    {
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_MediumWpDown())) BtagEventSFproduct_mediumWpDown    *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_MediumWpDown()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_MediumWpCentral())) BtagEventSFproduct_mediumWpCentral *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_MediumWpCentral()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_MediumWpUp())) BtagEventSFproduct_mediumWpUp      *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_MediumWpUp()));
    }

    if(goodJets[j].defaultBtagAlgorithm_RawScore() > TightCut) 
    {
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_TightWpDown())) BtagEventSFproduct_tightWpDown     *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_TightWpDown()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_TightWpCentral())) BtagEventSFproduct_tightWpCentral  *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_TightWpCentral()));
      if(!std::isnan(goodJets[j].defaultBtagAlgorithmSF_TightWpUp())) BtagEventSFproduct_tightWpUp       *= (1.0-std::min(1.0,goodJets[j].defaultBtagAlgorithmSF_TightWpUp()));
    }

    jets_BtagEff_LooseWp.push_back(goodJets[j].defaultBtagAlgorithmEff_LooseWp());
    jets_BtagEff_MediumWp.push_back(goodJets[j].defaultBtagAlgorithmEff_MediumWp());
    jets_BtagEff_TightWp.push_back(goodJets[j].defaultBtagAlgorithmEff_TightWp());

    jets_IsBTagged_LooseWpCentral.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_LooseWpCentral());
    jets_IsBTagged_LooseWpUp.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_LooseWpUp());
    jets_IsBTagged_LooseWpDown.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_LooseWpDown());
    jets_IsBTagged_MediumWpCentral.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_MediumWpCentral());
    jets_IsBTagged_MediumWpUp.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_MediumWpUp());
    jets_IsBTagged_MediumWpDown.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_MediumWpDown());
    jets_IsBTagged_TightWpCentral.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_TightWpCentral());
    jets_IsBTagged_TightWpUp.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_TightWpUp());
    jets_IsBTagged_TightWpDown.push_back(goodJets[j].defaultBtagAlgorithmIsTagged_TightWpDown());

    jets_PF_jetIdPassedTight.push_back(goodJets[j].PF_jetIdPassedTight());
   
  }

 

  /* now fill the FlatTuple JECshiftedUp jet vector */
  for(std::size_t j=0; j<goodJets_JECshiftedUp.size(); ++j)
  {      
    goodJets_JECshiftedUp[j].Use4VectorVariant("JECshiftedUp"); 
    if(goodJets_JECshiftedUp[j].jet_p4().pt()>30) numberOfJets30_JECshiftedUp++;  
    jets_pt_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].jet_p4().pt());
    jets_eta_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].jet_p4().eta());
    jets_phi_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].jet_p4().phi());
    jets_M_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].jet_p4().M());

    jets_PU_jetIdRaw_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].PU_jetIdRaw());
    jets_PU_jetIdPassed_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].PU_jetIdPassed());
    jets_PF_jetIdPassed_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].PF_jetIdPassed());
    jets_defaultBtagAlgorithm_RawScore_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithm_RawScore());
    jets_PARTON_flavour_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].PARTON_flavour());
    jets_HADRON_flavour_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].HADRON_flavour());

    jets_BtagSF_LooseWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_LooseWpCentral());
    jets_BtagSF_LooseWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_LooseWpUp());
    jets_BtagSF_LooseWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_LooseWpDown());
    jets_BtagSF_MediumWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_MediumWpCentral());
    jets_BtagSF_MediumWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_MediumWpUp());
    jets_BtagSF_MediumWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_MediumWpDown());
    jets_BtagSF_TightWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_TightWpCentral());
    jets_BtagSF_TightWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_TightWpUp());
    jets_BtagSF_TightWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_TightWpDown());

    if(goodJets_JECshiftedUp[j].defaultBtagAlgorithm_RawScore() > LooseCut) 
    {
      if(!std::isnan(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_LooseWpCentral())) BtagEventSFproduct_looseWpCentral_JECshiftedUp *= (1.0 - std::min(1.0,goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_LooseWpCentral()));
    }
    
    if(goodJets_JECshiftedUp[j].defaultBtagAlgorithm_RawScore() > MediumCut) 
    {
     if(!std::isnan(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_MediumWpCentral())) BtagEventSFproduct_mediumWpCentral_JECshiftedUp *= (1.0 - std::min(1.0,goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_MediumWpCentral()));
    }  

    if(goodJets_JECshiftedUp[j].defaultBtagAlgorithm_RawScore() > TightCut) 
    {
      if(!std::isnan(goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_TightWpCentral())) BtagEventSFproduct_tightWpCentral_JECshiftedUp *= (1.0 - std::min(1.0,goodJets_JECshiftedUp[j].defaultBtagAlgorithmSF_TightWpCentral()));
    }
    
    jets_BtagEff_LooseWp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmEff_LooseWp());
    jets_BtagEff_MediumWp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmEff_MediumWp());
    jets_BtagEff_TightWp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmEff_TightWp());

    jets_IsBTagged_LooseWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_LooseWpCentral());
    jets_IsBTagged_LooseWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_LooseWpUp());
    jets_IsBTagged_LooseWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_LooseWpDown());
    jets_IsBTagged_MediumWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_MediumWpCentral());
    jets_IsBTagged_MediumWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_MediumWpUp());
    jets_IsBTagged_MediumWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_MediumWpDown());
    jets_IsBTagged_TightWpCentral_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_TightWpCentral());
    jets_IsBTagged_TightWpUp_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_TightWpUp());
    jets_IsBTagged_TightWpDown_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].defaultBtagAlgorithmIsTagged_TightWpDown());
    jets_PF_jetIdPassedTight_JECshiftedUp.push_back(goodJets_JECshiftedUp[j].PF_jetIdPassedTight());
   


  }


  /* now fill the FlatTuple JECshiftedDown jet vector */
  for(std::size_t j=0; j<goodJets_JECshiftedDown.size(); ++j)
  {      
    goodJets_JECshiftedDown[j].Use4VectorVariant("JECshiftedDown"); 
    if(goodJets_JECshiftedDown[j].jet_p4().pt()>30) numberOfJets30_JECshiftedDown++;  
    jets_pt_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].jet_p4().pt());
    jets_eta_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].jet_p4().eta());
    jets_phi_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].jet_p4().phi());
    jets_M_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].jet_p4().M());

    jets_PU_jetIdRaw_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].PU_jetIdRaw());
    jets_PU_jetIdPassed_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].PU_jetIdPassed());
    jets_PF_jetIdPassed_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].PF_jetIdPassed());
    jets_defaultBtagAlgorithm_RawScore_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithm_RawScore());
    jets_PARTON_flavour_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].PARTON_flavour());
    jets_HADRON_flavour_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].HADRON_flavour());

    jets_BtagSF_LooseWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_LooseWpCentral());
    jets_BtagSF_LooseWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_LooseWpUp());
    jets_BtagSF_LooseWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_LooseWpDown());
    jets_BtagSF_MediumWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_MediumWpCentral());
    jets_BtagSF_MediumWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_MediumWpUp());
    jets_BtagSF_MediumWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_MediumWpDown());
    jets_BtagSF_TightWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_TightWpCentral());
    jets_BtagSF_TightWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_TightWpUp());
    jets_BtagSF_TightWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_TightWpDown());


    if(goodJets_JECshiftedDown[j].defaultBtagAlgorithm_RawScore() > LooseCut) 
    {
      if(!std::isnan(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_LooseWpCentral())) BtagEventSFproduct_looseWpCentral_JECshiftedDown *= (1.0 - std::min(1.0,goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_LooseWpCentral()));
    }

    if(goodJets_JECshiftedDown[j].defaultBtagAlgorithm_RawScore() > MediumCut) 
    {  
      if(!std::isnan(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_MediumWpCentral())) BtagEventSFproduct_mediumWpCentral_JECshiftedDown *= (1.0 - std::min(1.0,goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_MediumWpCentral()));
    }
    
    if(goodJets_JECshiftedDown[j].defaultBtagAlgorithm_RawScore() > TightCut) 
    {
      if(!std::isnan(goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_TightWpCentral())) BtagEventSFproduct_tightWpCentral_JECshiftedDown *= (1.0 - std::min(1.0,goodJets_JECshiftedDown[j].defaultBtagAlgorithmSF_TightWpCentral()));
    }

    jets_BtagEff_LooseWp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmEff_LooseWp());
    jets_BtagEff_MediumWp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmEff_MediumWp());
    jets_BtagEff_TightWp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmEff_TightWp());

    jets_IsBTagged_LooseWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_LooseWpCentral());
    jets_IsBTagged_LooseWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_LooseWpUp());
    jets_IsBTagged_LooseWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_LooseWpDown());
    jets_IsBTagged_MediumWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_MediumWpCentral());
    jets_IsBTagged_MediumWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_MediumWpUp());
    jets_IsBTagged_MediumWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_MediumWpDown());
    jets_IsBTagged_TightWpCentral_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_TightWpCentral());
    jets_IsBTagged_TightWpUp_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_TightWpUp());
    jets_IsBTagged_TightWpDown_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].defaultBtagAlgorithmIsTagged_TightWpDown());
    jets_PF_jetIdPassedTight_JECshiftedDown.push_back(goodJets_JECshiftedDown[j].PF_jetIdPassedTight());
  

  }


  /* now fill the FlatTuple JERup jet vector */
  for(std::size_t j=0; j<goodJets_JERup.size(); ++j)
  {      
    goodJets_JERup[j].Use4VectorVariant("JERup"); 
    if(goodJets_JERup[j].jet_p4().pt()>30) numberOfJets30_JERup++;  
    jets_pt_JERup.push_back(goodJets_JERup[j].jet_p4().pt());
    jets_eta_JERup.push_back(goodJets_JERup[j].jet_p4().eta());
    jets_phi_JERup.push_back(goodJets_JERup[j].jet_p4().phi());
    jets_M_JERup.push_back(goodJets_JERup[j].jet_p4().M());

    jets_PU_jetIdRaw_JERup.push_back(goodJets_JERup[j].PU_jetIdRaw());
    jets_PU_jetIdPassed_JERup.push_back(goodJets_JERup[j].PU_jetIdPassed());
    jets_PF_jetIdPassed_JERup.push_back(goodJets_JERup[j].PF_jetIdPassed());
    jets_defaultBtagAlgorithm_RawScore_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithm_RawScore());
    jets_PARTON_flavour_JERup.push_back(goodJets_JERup[j].PARTON_flavour());
    jets_HADRON_flavour_JERup.push_back(goodJets_JERup[j].HADRON_flavour());

    jets_BtagSF_LooseWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_LooseWpCentral());
    jets_BtagSF_LooseWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_LooseWpUp());
    jets_BtagSF_LooseWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_LooseWpDown());
    jets_BtagSF_MediumWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_MediumWpCentral());
    jets_BtagSF_MediumWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_MediumWpUp());
    jets_BtagSF_MediumWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_MediumWpDown());
    jets_BtagSF_TightWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_TightWpCentral());
    jets_BtagSF_TightWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_TightWpUp());
    jets_BtagSF_TightWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmSF_TightWpDown());

    if(goodJets_JERup[j].defaultBtagAlgorithm_RawScore() > LooseCut) 
    {
      if(!std::isnan(goodJets_JERup[j].defaultBtagAlgorithmSF_LooseWpCentral())) BtagEventSFproduct_looseWpCentral_JERup *= (1.0 - std::min(1.0,goodJets_JERup[j].defaultBtagAlgorithmSF_LooseWpCentral()));
    }
    if(goodJets_JERup[j].defaultBtagAlgorithm_RawScore() > MediumCut) 
    {
      if(!std::isnan(goodJets_JERup[j].defaultBtagAlgorithmSF_MediumWpCentral())) BtagEventSFproduct_mediumWpCentral_JERup *= (1.0 - std::min(1.0,goodJets_JERup[j].defaultBtagAlgorithmSF_MediumWpCentral()));
    }

    if(goodJets_JERup[j].defaultBtagAlgorithm_RawScore() > TightCut) 
    {
      if(!std::isnan(goodJets_JERup[j].defaultBtagAlgorithmSF_TightWpCentral())) BtagEventSFproduct_tightWpCentral_JERup *= (1.0 - std::min(1.0,goodJets_JERup[j].defaultBtagAlgorithmSF_TightWpCentral()));
    }


    jets_BtagEff_LooseWp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmEff_LooseWp());
    jets_BtagEff_MediumWp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmEff_MediumWp());
    jets_BtagEff_TightWp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmEff_TightWp());

    jets_IsBTagged_LooseWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_LooseWpCentral());
    jets_IsBTagged_LooseWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_LooseWpUp());
    jets_IsBTagged_LooseWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_LooseWpDown());
    jets_IsBTagged_MediumWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_MediumWpCentral());
    jets_IsBTagged_MediumWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_MediumWpUp());
    jets_IsBTagged_MediumWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_MediumWpDown());
    jets_IsBTagged_TightWpCentral_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_TightWpCentral());
    jets_IsBTagged_TightWpUp_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_TightWpUp());
    jets_IsBTagged_TightWpDown_JERup.push_back(goodJets_JERup[j].defaultBtagAlgorithmIsTagged_TightWpDown());

    jets_PF_jetIdPassedTight_JERup.push_back(goodJets_JERup[j].PF_jetIdPassedTight());
   
  }

  /* now fill the FlatTuple JERdown jet vector */
  for(std::size_t j=0; j<goodJets_JERdown.size(); ++j)
  {      
    goodJets_JERdown[j].Use4VectorVariant("JERdown"); 
    if(goodJets_JERdown[j].jet_p4().pt()>30) numberOfJets30_JERdown++;  
    jets_pt_JERdown.push_back(goodJets_JERdown[j].jet_p4().pt());
    jets_eta_JERdown.push_back(goodJets_JERdown[j].jet_p4().eta());
    jets_phi_JERdown.push_back(goodJets_JERdown[j].jet_p4().phi());
    jets_M_JERdown.push_back(goodJets_JERdown[j].jet_p4().M());

    jets_PU_jetIdRaw_JERdown.push_back(goodJets_JERdown[j].PU_jetIdRaw());
    jets_PU_jetIdPassed_JERdown.push_back(goodJets_JERdown[j].PU_jetIdPassed());
    jets_PF_jetIdPassed_JERdown.push_back(goodJets_JERdown[j].PF_jetIdPassed());
    jets_defaultBtagAlgorithm_RawScore_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithm_RawScore());
    jets_PARTON_flavour_JERdown.push_back(goodJets_JERdown[j].PARTON_flavour());
    jets_HADRON_flavour_JERdown.push_back(goodJets_JERdown[j].HADRON_flavour());
    
    jets_BtagSF_LooseWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_LooseWpCentral());
    jets_BtagSF_LooseWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_LooseWpUp());
    jets_BtagSF_LooseWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_LooseWpDown());
    jets_BtagSF_MediumWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_MediumWpCentral());
    jets_BtagSF_MediumWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_MediumWpUp());
    jets_BtagSF_MediumWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_MediumWpDown());
    jets_BtagSF_TightWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_TightWpCentral());
    jets_BtagSF_TightWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_TightWpUp());
    jets_BtagSF_TightWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmSF_TightWpDown());


    if(goodJets_JERdown[j].defaultBtagAlgorithm_RawScore() > LooseCut) 
    {
      if(!std::isnan(goodJets_JERdown[j].defaultBtagAlgorithmSF_LooseWpCentral())) BtagEventSFproduct_looseWpCentral_JERdown *= (1.0 - std::min(1.0,goodJets_JERdown[j].defaultBtagAlgorithmSF_LooseWpCentral()));
    } 
    
    if(goodJets_JERdown[j].defaultBtagAlgorithm_RawScore() > MediumCut) 
    {
      if(!std::isnan(goodJets_JERdown[j].defaultBtagAlgorithmSF_MediumWpCentral())) BtagEventSFproduct_mediumWpCentral_JERdown *= (1.0 - std::min(1.0,goodJets_JERdown[j].defaultBtagAlgorithmSF_MediumWpCentral()));
    } 

    if(goodJets_JERdown[j].defaultBtagAlgorithm_RawScore() > TightCut) 
    {
      if(!std::isnan(goodJets_JERdown[j].defaultBtagAlgorithmSF_TightWpCentral())) BtagEventSFproduct_tightWpCentral_JERdown *= (1.0 - std::min(1.0,goodJets_JERdown[j].defaultBtagAlgorithmSF_TightWpCentral()));
    }
    
    jets_BtagEff_LooseWp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmEff_LooseWp());
    jets_BtagEff_MediumWp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmEff_MediumWp());
    jets_BtagEff_TightWp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmEff_TightWp());

    jets_IsBTagged_LooseWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_LooseWpCentral());
    jets_IsBTagged_LooseWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_LooseWpUp());
    jets_IsBTagged_LooseWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_LooseWpDown());
    jets_IsBTagged_MediumWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_MediumWpCentral());
    jets_IsBTagged_MediumWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_MediumWpUp());
    jets_IsBTagged_MediumWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_MediumWpDown());
    jets_IsBTagged_TightWpCentral_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_TightWpCentral());
    jets_IsBTagged_TightWpUp_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_TightWpUp());
    jets_IsBTagged_TightWpDown_JERdown.push_back(goodJets_JERdown[j].defaultBtagAlgorithmIsTagged_TightWpDown());

    jets_PF_jetIdPassedTight_JERdown.push_back(goodJets_JERdown[j].PF_jetIdPassedTight());


  }






  /* gen info not related to the reco legs/eff leptons */

  genParticle_pdgId = genhelper.genParticle_pdgId();
  genParticle_status = genhelper.genParticle_status();
  genParticle_isPrompt = genhelper.genParticle_isPrompt();
  genParticle_isPromptFinalState = genhelper.genParticle_isPromptFinalState();
  genParticle_isDirectPromptTauDecayProduct = genhelper.genParticle_isDirectPromptTauDecayProduct();
  genParticle_isDirectPromptTauDecayProductFinalState = genhelper.genParticle_isDirectPromptTauDecayProductFinalState();
  genParticle_fromHardProcess = genhelper.genParticle_fromHardProcess();
  genParticle_isLastCopy = genhelper.genParticle_isLastCopy();


  isZEEatGenLevel = genhelper.isZXXatGenLevel(currentINDEP.genParticles(),11);
  isZMMatGenLevel = genhelper.isZXXatGenLevel(currentINDEP.genParticles(),13);
  isZTTatGenLevel = genhelper.isZXXatGenLevel(currentINDEP.genParticles(),15);


  genParticle_pt = genhelper.genParticle_pt();
  genParticle_eta = genhelper.genParticle_eta();
  genParticle_phi = genhelper.genParticle_phi();
  genParticle_M = genhelper.genParticle_M();
  genDaughter_pdgId = genhelper.genDaughter_pdgId();
  genDaughter_status = genhelper.genDaughter_status();
  genDaughter_pt = genhelper.genDaughter_pt();
  genDaughter_eta = genhelper.genDaughter_eta();
  genDaughter_phi = genhelper.genDaughter_phi();
  genDaughter_M = genhelper.genDaughter_M();
  genMother_pdgId = genhelper.genMother_pdgId();
  genMother_status = genhelper.genMother_status();
  genMother_pt = genhelper.genMother_pt();
  genMother_eta = genhelper.genMother_eta();
  genMother_phi = genhelper.genMother_phi();
  genMother_M = genhelper.genMother_M();




  /* top pT */
  std::vector<double> topPts = genhelper.getTopPts();
  if(topPts.size()>0) genTopPt1 = topPts[0];
  if(topPts.size()>1) genTopPt2 = topPts[1];

  /* theory scale factors */
  originalXWGTUP = currentINDEP.originalXWGTUP();
  if(KeepTheoryScaleFactors_) 
  {
    theory_scale_factors = currentINDEP.theory_scale_factors();
  }



}



//////////////////////////////////////////////////
// ------------ method called to reset values and clear vectors each event ----
//////////////////////////////////////////////////

 void FlatTupleGenerator::reInit()
 {



   run = 0;
   luminosityBlock = 0;
   event = 0;
   pairRank = 999;
   isBoostedChannelPair = 0;
   isRealData  = 0;
   treeInfoString = "NULL";
   RecoilCorrectionType = "NULL";
   MetSystematicType = "NULL";
   VISMass  = NAN;
   AppliedLepCuts.clear(); 
   isSmallTree = 0;

  for(int r =0; r<THE_MAX;++r)
  {  leg1_tauIDs[r] = NAN;
     leg2_tauIDs[r] = NAN;
  }

  for(int r =0; r<THE_MAX;++r)
  {  leg1_GoodForHLTPath[r] = NAN;
     leg2_GoodForHLTPath[r] = NAN;
  }


  for(int q = 0; q < THE_MAX; ++q)
  {    

    effLep_tauIDs.at(q).second.clear(); 
    effLep_GoodForHLTPath.at(q).second.clear(); 
  }


  CandidateEventType = -999; 
  TauEsNumberSigmasShifted = NAN;
  ElectronEsNumberSigmasShifted = NAN;
  isOsPair = -999;
  

  uncorr_mvaMET = NAN;
  uncorr_mvaMETphi = NAN;
  uncorr_MTmvaMET_leg1 = NAN;
  uncorr_MTmvaMET_leg2 = NAN;
  corr_mvaMET = NAN;
  corr_mvaMETphi = NAN;
  corr_MTmvaMET_leg1 = NAN;
  corr_MTmvaMET_leg2 = NAN;
  responseUP_mvaMET = NAN;
  responseUP_mvaMETphi = NAN;
  responseUP_MTmvaMET_leg1 = NAN;
  responseUP_MTmvaMET_leg2 = NAN;
  responseDOWN_mvaMET = NAN;
  responseDOWN_mvaMETphi = NAN;
  responseDOWN_MTmvaMET_leg1 = NAN;
  responseDOWN_MTmvaMET_leg2 = NAN;
  resolutionUP_mvaMET = NAN;
  resolutionUP_mvaMETphi = NAN;
  resolutionUP_MTmvaMET_leg1 = NAN;
  resolutionUP_MTmvaMET_leg2 = NAN;
  resolutionDOWN_mvaMET = NAN;
  resolutionDOWN_mvaMETphi = NAN;
  resolutionDOWN_MTmvaMET_leg1 = NAN;
  resolutionDOWN_MTmvaMET_leg2 = NAN;

  mvaMET_cov00 = NAN;
  mvaMET_cov01 = NAN; 
  mvaMET_cov10 = NAN; 
  mvaMET_cov11 = NAN;   


  SVMass = NAN;
  SVTransverseMass = NAN;
  SVMass_uncorr_mvaMET = NAN;
  SVTransverseMass_uncorr_mvaMET = NAN;
  SVMass_responseUP_mvaMET = NAN;
  SVTransverseMass_responseUP_mvaMET = NAN;
  SVMass_responseDN_mvaMET = NAN;
  SVTransverseMass_responseDN_mvaMET = NAN;
  SVMass_resolutionUP_mvaMET = NAN;
  SVTransverseMass_resolutionUP_mvaMET = NAN;
  SVMass_resolutionDN_mvaMET = NAN;
  SVTransverseMass_resolutionDN_mvaMET = NAN;
  SVMass_pfMET = NAN;
  SVTransverseMass_pfMET = NAN;
  SVMass_puppiMET = NAN;
  SVTransverseMass_puppiMET = NAN;

  SVFit_mvaMET_diTau_pt = NAN; 
  SVFit_mvaMET_diTau_eta = NAN; 
  SVFit_mvaMET_diTau_phi = NAN; 
  SVFit_uncorr_mvaMET_diTau_pt = NAN; 
  SVFit_uncorr_mvaMET_diTau_eta = NAN; 
  SVFit_uncorr_mvaMET_diTau_phi = NAN; 
  SVFit_responseUP_mvaMET_diTau_pt = NAN; 
  SVFit_responseUP_mvaMET_diTau_eta = NAN; 
  SVFit_responseUP_mvaMET_diTau_phi = NAN; 
  SVFit_responseDN_mvaMET_diTau_pt = NAN; 
  SVFit_responseDN_mvaMET_diTau_eta = NAN; 
  SVFit_responseDN_mvaMET_diTau_phi = NAN; 
  SVFit_resolutionUP_mvaMET_diTau_pt = NAN; 
  SVFit_resolutionUP_mvaMET_diTau_eta = NAN; 
  SVFit_resolutionUP_mvaMET_diTau_phi = NAN; 
  SVFit_resolutionDN_mvaMET_diTau_pt = NAN; 
  SVFit_resolutionDN_mvaMET_diTau_eta = NAN; 
  SVFit_resolutionDN_mvaMET_diTau_phi = NAN; 
  SVFit_pfMET_diTau_pt = NAN; 
  SVFit_pfMET_diTau_eta = NAN; 
  SVFit_pfMET_diTau_phi = NAN; 
  SVFit_puppiMET_diTau_pt = NAN; 
  SVFit_puppiMET_diTau_eta = NAN; 
  SVFit_puppiMET_diTau_phi = NAN; 

  SVFit_mvaMET_FittedMET = NAN; 
  SVFit_mvaMET_FittedMETphi = NAN; 
  SVFit_uncorr_mvaMET_FittedMET = NAN; 
  SVFit_uncorr_mvaMET_FittedMETphi = NAN; 
  SVFit_responseUP_mvaMET_FittedMET = NAN; 
  SVFit_responseUP_mvaMET_FittedMETphi = NAN; 
  SVFit_responseDN_mvaMET_FittedMET = NAN; 
  SVFit_responseDN_mvaMET_FittedMETphi = NAN; 
  SVFit_resolutionUP_mvaMET_FittedMET = NAN; 
  SVFit_resolutionUP_mvaMET_FittedMETphi = NAN; 
  SVFit_resolutionDN_mvaMET_FittedMET = NAN; 
  SVFit_resolutionDN_mvaMET_FittedMETphi = NAN; 
  SVFit_pfMET_FittedMET = NAN; 
  SVFit_pfMET_FittedMETphi = NAN; 
  SVFit_puppiMET_FittedMET = NAN; 
  SVFit_puppiMET_FittedMETphi = NAN; 




  MTpfMET_leg1 = NAN;
  MTpfMET_leg2 = NAN;
 
  pfMET = NAN;
  pfMETphi = NAN;
  pfMET_cov00 = NAN; 
  pfMET_cov01 = NAN; 
  pfMET_cov10 = NAN; 
  pfMET_cov11 = NAN;   

  genMET = NAN; 
  genMETphi = NAN; 
  genMETeta = NAN;
  genMETmass = NAN;

  MTpuppiMET_leg1 = NAN; 
  MTpuppiMET_leg2 = NAN; 
  puppiMET = NAN; 
  puppiMETphi = NAN; 
  RAWpfMET = NAN; 
  RAWpfMETphi = NAN; 
  RAWpuppiMET = NAN; 
  RAWpuppiMETphi = NAN; 

  CORRpfMET = NAN;
  CORRpfMETphi = NAN;
  MTCORRpfMET_leg1 = NAN;
  MTCORRpfMET_leg2 = NAN;
  responseUP_pfMET = NAN;
  responseUP_pfMETphi = NAN;
  responseUP_MTpfMET_leg1 = NAN;
  responseUP_MTpfMET_leg2 = NAN;
  responseDOWN_pfMET = NAN;
  responseDOWN_pfMETphi = NAN;
  responseDOWN_MTpfMET_leg1 = NAN;
  responseDOWN_MTpfMET_leg2 = NAN;
  resolutionUP_pfMET = NAN;
  resolutionUP_pfMETphi = NAN;
  resolutionUP_MTpfMET_leg1 = NAN;
  resolutionUP_MTpfMET_leg2 = NAN;
  resolutionDOWN_pfMET = NAN;
  resolutionDOWN_pfMETphi = NAN;
  resolutionDOWN_MTpfMET_leg1 = NAN;
  resolutionDOWN_MTpfMET_leg2 = NAN;
  responseUP_CORRpfMET = NAN;
  responseUP_CORRpfMETphi = NAN;
  responseUP_MTCORRpfMET_leg1 = NAN;
  responseUP_MTCORRpfMET_leg2 = NAN;
  responseDOWN_CORRpfMET = NAN;
  responseDOWN_CORRpfMETphi = NAN;
  responseDOWN_MTCORRpfMET_leg1 = NAN;
  responseDOWN_MTCORRpfMET_leg2 = NAN;
  resolutionUP_CORRpfMET = NAN;
  resolutionUP_CORRpfMETphi = NAN;
  resolutionUP_MTCORRpfMET_leg1 = NAN;
  resolutionUP_MTCORRpfMET_leg2 = NAN;
  resolutionDOWN_CORRpfMET = NAN;
  resolutionDOWN_CORRpfMETphi = NAN;
  resolutionDOWN_MTCORRpfMET_leg1 = NAN;
  resolutionDOWN_MTCORRpfMET_leg2 = NAN;

  pfmet_raw_Pt = NAN;
  pfmet_raw_Phi = NAN;
  pfmet_raw_MT1 = NAN;
  pfmet_raw_MT2 = NAN;

  pfmet_type1_Pt = NAN;
  pfmet_type1_Phi = NAN;
  pfmet_type1_MT1 = NAN;
  pfmet_type1_MT2 = NAN;


  pfmet_type1_JetResUp_Pt = NAN;
  pfmet_type1_JetResUp_Phi = NAN;
  pfmet_type1_JetResUp_MT1 = NAN;
  pfmet_type1_JetResUp_MT2 = NAN;
  pfmet_type1_JetResDown_Pt = NAN;
  pfmet_type1_JetResDown_Phi = NAN;
  pfmet_type1_JetResDown_MT1 = NAN;
  pfmet_type1_JetResDown_MT2 = NAN;
  pfmet_type1_JetEnUp_Pt = NAN;
  pfmet_type1_JetEnUp_Phi = NAN;
  pfmet_type1_JetEnUp_MT1 = NAN;
  pfmet_type1_JetEnUp_MT2 = NAN;
  pfmet_type1_JetEnDown_Pt = NAN;
  pfmet_type1_JetEnDown_Phi = NAN;
  pfmet_type1_JetEnDown_MT1 = NAN;
  pfmet_type1_JetEnDown_MT2 = NAN;
  pfmet_type1_MuonEnUp_Pt = NAN;
  pfmet_type1_MuonEnUp_Phi = NAN;
  pfmet_type1_MuonEnUp_MT1 = NAN;
  pfmet_type1_MuonEnUp_MT2 = NAN;
  pfmet_type1_MuonEnDown_Pt = NAN;
  pfmet_type1_MuonEnDown_Phi = NAN;
  pfmet_type1_MuonEnDown_MT1 = NAN;
  pfmet_type1_MuonEnDown_MT2 = NAN;
  pfmet_type1_ElectronEnUp_Pt = NAN;
  pfmet_type1_ElectronEnUp_Phi = NAN;
  pfmet_type1_ElectronEnUp_MT1 = NAN;
  pfmet_type1_ElectronEnUp_MT2 = NAN;
  pfmet_type1_ElectronEnDown_Pt = NAN;
  pfmet_type1_ElectronEnDown_Phi = NAN;
  pfmet_type1_ElectronEnDown_MT1 = NAN;
  pfmet_type1_ElectronEnDown_MT2 = NAN;
  pfmet_type1_TauEnUp_Pt = NAN;
  pfmet_type1_TauEnUp_Phi = NAN;
  pfmet_type1_TauEnUp_MT1 = NAN;
  pfmet_type1_TauEnUp_MT2 = NAN;
  pfmet_type1_TauEnDown_Pt = NAN;
  pfmet_type1_TauEnDown_Phi = NAN;
  pfmet_type1_TauEnDown_MT1 = NAN;
  pfmet_type1_TauEnDown_MT2 = NAN;
  pfmet_type1_UnclusteredEnUp_Pt = NAN;
  pfmet_type1_UnclusteredEnUp_Phi = NAN;
  pfmet_type1_UnclusteredEnUp_MT1 = NAN;
  pfmet_type1_UnclusteredEnUp_MT2 = NAN;
  pfmet_type1_UnclusteredEnDown_Pt = NAN;
  pfmet_type1_UnclusteredEnDown_Phi = NAN;
  pfmet_type1_UnclusteredEnDown_MT1 = NAN;
  pfmet_type1_UnclusteredEnDown_MT2 = NAN;
  pfmet_type1_PhotonEnUp_Pt = NAN;
  pfmet_type1_PhotonEnUp_Phi = NAN;
  pfmet_type1_PhotonEnUp_MT1 = NAN;
  pfmet_type1_PhotonEnUp_MT2 = NAN;
  pfmet_type1_PhotonEnDown_Pt = NAN;
  pfmet_type1_PhotonEnDown_Phi = NAN;
  pfmet_type1_PhotonEnDown_MT1 = NAN;
  pfmet_type1_PhotonEnDown_MT2 = NAN;



  leg1_dz = NAN;
  leg1_dxy = NAN;
  leg1_EffectiveArea = NAN;
  leg1_IP = NAN;
  leg1_IPerror = NAN;
  leg1_PUchargedHadronIso = NAN;
  leg1_chargedHadronIso = NAN;
  leg1_neutralHadronIso = NAN;
  leg1_photonIso = NAN;
  leg1_DepositR03ECal = NAN;
  leg1_DepositR03Hcal = NAN;
  leg1_DepositR03TrackerOfficial = NAN;
  leg1_isGlobalMuon = NAN;
  leg1_isGoodGlobalMuon = NAN;
  leg1_passesMediumMuonId = NAN;
  leg1_passesLooseMuonId = NAN;
  leg1_passesMediumMuonId_ICHEP16 = NAN;
  leg1_passesMediumMuonId_Moriond17 = NAN;  
  leg1_passesTightMuonId = NAN;
  leg1_isLooseMuon = NAN;
  leg1_isPFMuon = NAN;
  leg1_isSoftMuon = NAN;
  leg1_isTightMuon = NAN;
  leg1_isTrackerMuon = NAN;
  leg1_muonCombQualChi2LocalPosition = NAN;
  leg1_muonCombQualTrkKink = NAN;
  leg1_muonGlobalTrackNormChi2 = NAN;
  leg1_muonInnerTrkValidFraction = NAN;
  leg1_muonSegmentCompatibility = NAN;
  leg1_raw_electronMVA = NAN;
  leg1_category_electronMVA = NAN;
  leg1_passFail_electronMVA80 = NAN;
  leg1_passFail_electronMVA90 = NAN;
  leg1_passFail_VetoElectronCutBasedID = NAN;
  leg1_passFail_TightElectronCutBasedID = NAN;
  leg1_ooEmooP = NAN;
  leg1_full5x5_sigmaIetaIeta = NAN;
  leg1_SuperClusterEta = NAN;
  leg1_hadronicOverEm = NAN;
  leg1_isEB = NAN;
  leg1_isEBEEGap = NAN;
  leg1_isEBEtaGap = NAN;
  leg1_isEBPhiGap = NAN;
  leg1_isEE = NAN;
  leg1_isEEDeeGap = NAN;
  leg1_isEERingGap = NAN;
  leg1_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg1_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg1_sigmaEtaEta = NAN;
  leg1_sigmaIetaIeta = NAN;
  leg1_sigmaIphiIphi = NAN;
  leg1_numberOfMissingInnerHits = NAN;
  leg1_numberOfMissingOuterHits = NAN;
  leg1_numberOfTrackHits = NAN;
  leg1_passConversionVeto = NAN;
  leg1_ZimpactTau = NAN;
  leg1_dzTauVertex = NAN;
  leg1_numStrips = NAN;
  leg1_numHadrons = NAN;

  leg1_rerunDiscriminationByIsolationMVArun2v1raw = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1VLoose = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1Loose = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1Medium = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1Tight = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1VTight = NAN;
  leg1_rerunDiscriminationByIsolationMVArun2v1VVTight = NAN;


  leg1_decayMode = -999;
  leg2_dz = NAN;
  leg2_dxy = NAN;
  leg2_EffectiveArea = NAN;
  leg2_IP = NAN;
  leg2_IPerror = NAN;
  leg2_PUchargedHadronIso = NAN;
  leg2_chargedHadronIso = NAN;
  leg2_neutralHadronIso = NAN;
  leg2_photonIso = NAN;
  leg2_DepositR03ECal = NAN;
  leg2_DepositR03Hcal = NAN;
  leg2_DepositR03TrackerOfficial = NAN;
  leg2_isGlobalMuon = NAN;
  leg2_isGoodGlobalMuon = NAN;
  leg2_passesMediumMuonId = NAN;
  leg2_passesLooseMuonId = NAN;
  leg2_passesMediumMuonId_ICHEP16 = NAN;
  leg2_passesMediumMuonId_Moriond17 = NAN;
  leg2_passesTightMuonId = NAN;
  leg2_isLooseMuon = NAN;
  leg2_isPFMuon = NAN;
  leg2_isSoftMuon = NAN;
  leg2_isTightMuon = NAN;
  leg2_isTrackerMuon = NAN;
  leg2_muonCombQualChi2LocalPosition = NAN;
  leg2_muonCombQualTrkKink = NAN;
  leg2_muonGlobalTrackNormChi2 = NAN;
  leg2_muonInnerTrkValidFraction = NAN;
  leg2_muonSegmentCompatibility = NAN;
  leg2_raw_electronMVA = NAN;
  leg2_category_electronMVA = NAN;
  leg2_passFail_electronMVA80 = NAN;
  leg2_passFail_electronMVA90 = NAN;
  leg2_passFail_VetoElectronCutBasedID = NAN;
  leg2_passFail_TightElectronCutBasedID = NAN;
  leg2_ooEmooP = NAN;
  leg2_full5x5_sigmaIetaIeta = NAN;  
  leg2_SuperClusterEta = NAN;
  leg2_hadronicOverEm = NAN;
  leg2_isEB = NAN;
  leg2_isEBEEGap = NAN;
  leg2_isEBEtaGap = NAN;
  leg2_isEBPhiGap = NAN;
  leg2_isEE = NAN;
  leg2_isEEDeeGap = NAN;
  leg2_isEERingGap = NAN;
  leg2_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg2_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg2_sigmaEtaEta = NAN;
  leg2_sigmaIetaIeta = NAN;
  leg2_sigmaIphiIphi = NAN;
  leg2_numberOfMissingInnerHits = NAN;
  leg2_numberOfMissingOuterHits = NAN;
  leg2_numberOfTrackHits = NAN;
  leg2_passConversionVeto = NAN;
  leg2_ZimpactTau = NAN;
  leg2_numStrips = NAN;
  leg2_numHadrons = NAN;

  leg2_rerunDiscriminationByIsolationMVArun2v1raw = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1VLoose = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1Loose = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1Medium = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1Tight = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1VTight = NAN;
  leg2_rerunDiscriminationByIsolationMVArun2v1VVTight = NAN;


  leg2_decayMode = -999;
  leg2_dzTauVertex = NAN;


  DeltaR_leg1_leg2  = NAN;
  leg1_leptonType = -999;
  leg1_charge = -999;
  leg1_PFpdgId = -999;
  leg1_GENpdgId = -999;
  leg1_GENMOTHERpdgId = -999;
  leg2_leptonType = -999;
  leg2_charge = -999;
  leg2_PFpdgId = -999;
  leg2_GENpdgId = -999;
  leg2_GENMOTHERpdgId = -999;


  leg2_pt = NAN;
  leg2_gen_pt = NAN;
  leg2_genMother_pt = NAN;
  leg2_genJet_pt = NAN;
  leg1_pt = NAN;
  leg1_gen_pt = NAN;
  leg1_genMother_pt = NAN;
  leg1_genJet_pt = NAN;
  leg2_eta = NAN;
  leg2_gen_eta = NAN;
  leg2_genMother_eta = NAN;
  leg2_genJet_eta = NAN;
  leg1_eta = NAN;
  leg1_gen_eta = NAN;
  leg1_genMother_eta = NAN;
  leg1_genJet_eta = NAN;
  leg2_phi = NAN;
  leg2_gen_phi = NAN;
  leg2_genMother_phi = NAN;
  leg2_genJet_phi = NAN;
  leg1_phi = NAN;
  leg1_gen_phi = NAN;
  leg1_genMother_phi = NAN;
  leg1_genJet_phi = NAN;
  leg2_M = NAN;
  leg2_gen_M = NAN;
  leg2_genMother_M = NAN;
  leg2_genJet_M = NAN;
  leg1_M = NAN;
  leg1_gen_M = NAN;
  leg1_genMother_M = NAN;
  leg1_genJet_M = NAN;
  leg1_RelIso = NAN;
  leg2_RelIso = NAN;

  leg1_genJet_pdgId = -999;
  leg2_genJet_pdgId = -999;
  effLep_genJet_pdgId.clear();  



  effLep_leptonType.clear();    
  effLep_pt.clear();
  effLep_eta.clear();
  effLep_phi.clear();
  effLep_M.clear(); 
  effLep_gen_pt.clear();
  effLep_gen_eta.clear();
  effLep_gen_phi.clear();
  effLep_gen_M.clear();     
  effLep_genMother_pt.clear();
  effLep_genMother_eta.clear();
  effLep_genMother_phi.clear();
  effLep_genMother_M.clear(); 
  effLep_genJet_pt.clear();
  effLep_genJet_eta.clear();
  effLep_genJet_phi.clear();
  effLep_genJet_M.clear(); 
  effLep_dz.clear();          
  effLep_dxy.clear();       
  effLep_EffectiveArea.clear(); 
  effLep_charge.clear();      
  effLep_PFpdgId.clear();     
  effLep_GENpdgId.clear();    
  effLep_GENMOTHERpdgId.clear(); 
  effLep_IP.clear();      
  effLep_IPerror.clear(); 
  effLep_PUchargedHadronIso.clear(); 
  effLep_chargedHadronIso.clear();   
  effLep_neutralHadronIso.clear();   
  effLep_photonIso.clear();          
  effLep_DepositR03ECal.clear();  
  effLep_DepositR03Hcal.clear();  
  effLep_DepositR03TrackerOfficial.clear(); 
  effLep_isGlobalMuon.clear();
  effLep_isGoodGlobalMuon.clear();
  effLep_passesLooseMuonId.clear();
  effLep_passesMediumMuonId_ICHEP16.clear();
  effLep_passesMediumMuonId_Moriond17.clear();
  effLep_passesMediumMuonId.clear();
  effLep_passesTightMuonId.clear();
  effLep_isLooseMuon.clear();
  effLep_isPFMuon.clear();
  effLep_isSoftMuon.clear();
  effLep_isTightMuon.clear();
  effLep_isTrackerMuon.clear();
  effLep_muonCombQualChi2LocalPosition.clear();
  effLep_muonCombQualTrkKink.clear();
  effLep_muonGlobalTrackNormChi2.clear();
  effLep_muonInnerTrkValidFraction.clear();
  effLep_muonSegmentCompatibility.clear();
  effLep_raw_electronMVA.clear();
  effLep_category_electronMVA.clear();
  effLep_passFail_electronMVA80.clear();
  effLep_passFail_electronMVA90.clear();
  effLep_passFail_VetoElectronCutBasedID.clear();
  effLep_passFail_TightElectronCutBasedID.clear();
  effLep_ooEmooP.clear();
  effLep_full5x5_sigmaIetaIeta.clear();
  effLep_SuperClusterEta.clear();
  effLep_hadronicOverEm.clear();
  effLep_isEB.clear();
  effLep_isEBEEGap.clear();
  effLep_isEBEtaGap.clear();
  effLep_isEBPhiGap.clear();
  effLep_isEE.clear();
  effLep_isEEDeeGap.clear();
  effLep_isEERingGap.clear();
  effLep_deltaEtaSuperClusterTrackAtVtx.clear();
  effLep_deltaPhiSuperClusterTrackAtVtx.clear();
  effLep_sigmaEtaEta.clear();
  effLep_sigmaIetaIeta.clear();
  effLep_sigmaIphiIphi.clear();
  effLep_numberOfMissingInnerHits.clear();
  effLep_numberOfMissingOuterHits.clear();
  effLep_numberOfTrackHits.clear();
  effLep_passConversionVeto.clear();
  effLep_ZimpactTau.clear();
  effLep_numStrips.clear();
  effLep_dzTauVertex.clear();
  effLep_numHadrons.clear();

  effLep_rerunDiscriminationByIsolationMVArun2v1raw.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1VLoose.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1Loose.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1Medium.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1Tight.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1VTight.clear();
  effLep_rerunDiscriminationByIsolationMVArun2v1VVTight.clear();


  effLep_decayMode.clear();
  effLep_RelIso.clear();



  leg1_L1IsoTauMatch_pt.clear();
  leg1_L1IsoTauMatch_eta.clear();
  leg1_L1IsoTauMatch_phi.clear();

  leg2_L1IsoTauMatch_pt.clear();
  leg2_L1IsoTauMatch_eta.clear();
  leg2_L1IsoTauMatch_phi.clear();

  PairPassesDoubleTauIsoTau28MatchCut = -999;

  effLep_MaxL1IsoTauMatch_pt.clear();
  effLep_MaxL1IsoTauMatch_eta.clear();
  effLep_MaxL1IsoTauMatch_phi.clear();

  veto_leptonType.clear(); 
  veto_pt.clear(); 
  veto_eta.clear(); 
  veto_phi.clear(); 
  veto_M.clear(); 
  veto_charge.clear(); 
  veto_dxy.clear(); 
  veto_dz.clear(); 
  veto_RelIso.clear(); 
  veto_passesLooseMuonId.clear(); 
  veto_passesMediumMuonId_ICHEP16.clear(); 
  veto_passesMediumMuonId_Moriond17.clear(); 
  veto_passesMediumMuonId.clear(); 
  veto_passesTightMuonId.clear(); 
  veto_rawElectronMVA.clear(); 
  veto_categoryElectronMVA.clear(); 
  veto_passElectronMVA80.clear(); 
  veto_passElectronMVA90.clear(); 
  veto_passVetoElectronCutBased.clear(); 
  veto_passTightElectronCutBased.clear(); 
  veto_isTrackerGlobalPFMuon.clear(); 
  veto_numberOfMissingInnerHits.clear();
  veto_numberOfMissingOuterHits.clear();
  veto_passConversionVeto.clear();
  
  veto_ZimpactTau.clear(); 
  veto_numStrips.clear(); 
  veto_dzTauVertex.clear(); 
  veto_numHadrons.clear(); 

  veto_rerunDiscriminationByIsolationMVArun2v1raw.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1VLoose.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1Loose.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1Medium.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1Tight.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1VTight.clear();
  veto_rerunDiscriminationByIsolationMVArun2v1VVTight.clear();

  veto_decayMode.clear(); 

  for(int q = 0; q < THE_MAX; ++q)
  {    
    veto_tauIDs.at(q).second.clear(); 
  }



  veto_LeptonPassesThirdElectronVetoCuts.clear();
  veto_LeptonPassesThirdMuonVetoCuts.clear();
  veto_LeptonPassesDiElectronVetoCuts.clear();
  veto_LeptonPassesDiMuonVetoCuts.clear();




  NumberOfGoodVertices = -999;
  vertex_NDOF = NAN;
  vertex_CHI2 = NAN;
  vertex_positionRho = NAN;
  vertex_positionX = NAN;
  vertex_positionY  = NAN;
  vertex_positionZ = NAN;
  vertex_positionTheta = NAN;
  vertex_positionEta = NAN;
  vertex_positionPhi = NAN;

  puWeight = NAN;
  NumPileupInt = NAN;
  NumTruePileUpInt = NAN;
  generatorEventWeight = NAN;
  hepNUP = -999;
  lheHT = NAN;
  lheOutGoingPartons = -999;
  lheZmass = NAN;

  HBHENoiseFilter = 1;
  HBHENoiseIsoFilter = 1;
  CSCTightHalo2015Filter = 1;
  EcalDeadCellTriggerPrimitiveFilter = 1;
  goodVerticesFilter = 1;
  eeBadScFilter = 1;
  chargedHadronTrackResolutionFilter = 1;
  muonBadTrackFilter = 1;
  globalTightHalo2016Filter = 1;
  BadChargedCandidateFilter  = 1;
  BadPFMuonFilter = 1;

  /* init the two taggers to 0 which means event is OK */
  BadMuonTaggedMoriond17 = 0;
  DuplicateMuonTaggedMoriond17 = 0;



  numberOfJetsForRecoilCorr = -999;
  numberOfJets30 = -999;
  numberOfJets = -999;

  /* init the btag product SF to 1.0 */
  BtagEventSFproduct_looseWpDown = 1.0;
  BtagEventSFproduct_looseWpCentral = 1.0;
  BtagEventSFproduct_looseWpUp = 1.0;
  BtagEventSFproduct_mediumWpDown = 1.0;
  BtagEventSFproduct_mediumWpCentral = 1.0;
  BtagEventSFproduct_mediumWpUp = 1.0;
  BtagEventSFproduct_tightWpDown = 1.0;
  BtagEventSFproduct_tightWpCentral = 1.0;
  BtagEventSFproduct_tightWpUp = 1.0;
  BtagEventSFproduct_looseWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_mediumWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_tightWpCentral_JECshiftedUp = 1.0;
  BtagEventSFproduct_looseWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_mediumWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_tightWpCentral_JECshiftedDown = 1.0;
  BtagEventSFproduct_looseWpCentral_JERup = 1.0;
  BtagEventSFproduct_mediumWpCentral_JERup = 1.0;
  BtagEventSFproduct_tightWpCentral_JERup = 1.0;
  BtagEventSFproduct_looseWpCentral_JERdown = 1.0;
  BtagEventSFproduct_mediumWpCentral_JERdown = 1.0;
  BtagEventSFproduct_tightWpCentral_JERdown = 1.0;



  jets_pt.clear();
  jets_eta.clear();
  jets_phi.clear();
  jets_M.clear();
  jets_PU_jetIdRaw.clear();
  jets_PU_jetIdPassed.clear();
  jets_PF_jetIdPassed.clear();
  jets_defaultBtagAlgorithm_RawScore.clear();
  jets_PARTON_flavour.clear();
  jets_HADRON_flavour.clear();
  jets_BtagSF_LooseWpCentral.clear();
  jets_BtagSF_LooseWpUp.clear();
  jets_BtagSF_LooseWpDown.clear();
  jets_BtagSF_MediumWpCentral.clear();
  jets_BtagSF_MediumWpUp.clear();
  jets_BtagSF_MediumWpDown.clear();
  jets_BtagSF_TightWpCentral.clear();
  jets_BtagSF_TightWpUp.clear();
  jets_BtagSF_TightWpDown.clear();
  jets_BtagEff_LooseWp.clear();
  jets_BtagEff_MediumWp.clear();
  jets_BtagEff_TightWp.clear();
  jets_IsBTagged_LooseWpCentral.clear();
  jets_IsBTagged_LooseWpUp.clear();
  jets_IsBTagged_LooseWpDown.clear();
  jets_IsBTagged_MediumWpCentral.clear();
  jets_IsBTagged_MediumWpUp.clear();
  jets_IsBTagged_MediumWpDown.clear();
  jets_IsBTagged_TightWpCentral.clear();
  jets_IsBTagged_TightWpUp.clear();
  jets_IsBTagged_TightWpDown.clear();
  jets_PF_jetIdPassedTight.clear();



  numberOfJets_JECshiftedUp = -999;
  numberOfJets30_JECshiftedUp = -999;
  jets_pt_JECshiftedUp.clear();
  jets_eta_JECshiftedUp.clear();
  jets_phi_JECshiftedUp.clear();
  jets_M_JECshiftedUp.clear();
  jets_PU_jetIdRaw_JECshiftedUp.clear();
  jets_PU_jetIdPassed_JECshiftedUp.clear();
  jets_PF_jetIdPassed_JECshiftedUp.clear();
  jets_defaultBtagAlgorithm_RawScore_JECshiftedUp.clear();
  jets_PARTON_flavour_JECshiftedUp.clear();
  jets_HADRON_flavour_JECshiftedUp.clear();
  jets_BtagSF_LooseWpCentral_JECshiftedUp.clear();
  jets_BtagSF_LooseWpUp_JECshiftedUp.clear();
  jets_BtagSF_LooseWpDown_JECshiftedUp.clear();
  jets_BtagSF_MediumWpCentral_JECshiftedUp.clear();
  jets_BtagSF_MediumWpUp_JECshiftedUp.clear();
  jets_BtagSF_MediumWpDown_JECshiftedUp.clear();
  jets_BtagSF_TightWpCentral_JECshiftedUp.clear();
  jets_BtagSF_TightWpUp_JECshiftedUp.clear();
  jets_BtagSF_TightWpDown_JECshiftedUp.clear();
  jets_BtagEff_LooseWp_JECshiftedUp.clear();
  jets_BtagEff_MediumWp_JECshiftedUp.clear();
  jets_BtagEff_TightWp_JECshiftedUp.clear();
  jets_IsBTagged_LooseWpCentral_JECshiftedUp.clear();
  jets_IsBTagged_LooseWpUp_JECshiftedUp.clear();
  jets_IsBTagged_LooseWpDown_JECshiftedUp.clear();
  jets_IsBTagged_MediumWpCentral_JECshiftedUp.clear();
  jets_IsBTagged_MediumWpUp_JECshiftedUp.clear();
  jets_IsBTagged_MediumWpDown_JECshiftedUp.clear();
  jets_IsBTagged_TightWpCentral_JECshiftedUp.clear();
  jets_IsBTagged_TightWpUp_JECshiftedUp.clear();
  jets_IsBTagged_TightWpDown_JECshiftedUp.clear();
  jets_PF_jetIdPassedTight_JECshiftedUp.clear();



  numberOfJets_JECshiftedDown = -999;
  numberOfJets30_JECshiftedDown = -999;
  jets_pt_JECshiftedDown.clear();
  jets_eta_JECshiftedDown.clear();
  jets_phi_JECshiftedDown.clear();
  jets_M_JECshiftedDown.clear();
  jets_PU_jetIdRaw_JECshiftedDown.clear();
  jets_PU_jetIdPassed_JECshiftedDown.clear();
  jets_PF_jetIdPassed_JECshiftedDown.clear();
  jets_defaultBtagAlgorithm_RawScore_JECshiftedDown.clear();
  jets_PARTON_flavour_JECshiftedDown.clear();
  jets_HADRON_flavour_JECshiftedDown.clear();
  jets_BtagSF_LooseWpCentral_JECshiftedDown.clear();
  jets_BtagSF_LooseWpUp_JECshiftedDown.clear();
  jets_BtagSF_LooseWpDown_JECshiftedDown.clear();
  jets_BtagSF_MediumWpCentral_JECshiftedDown.clear();
  jets_BtagSF_MediumWpUp_JECshiftedDown.clear();
  jets_BtagSF_MediumWpDown_JECshiftedDown.clear();
  jets_BtagSF_TightWpCentral_JECshiftedDown.clear();
  jets_BtagSF_TightWpUp_JECshiftedDown.clear();
  jets_BtagSF_TightWpDown_JECshiftedDown.clear();
  jets_BtagEff_LooseWp_JECshiftedDown.clear();
  jets_BtagEff_MediumWp_JECshiftedDown.clear();
  jets_BtagEff_TightWp_JECshiftedDown.clear();
  jets_IsBTagged_LooseWpCentral_JECshiftedDown.clear();
  jets_IsBTagged_LooseWpUp_JECshiftedDown.clear();
  jets_IsBTagged_LooseWpDown_JECshiftedDown.clear();
  jets_IsBTagged_MediumWpCentral_JECshiftedDown.clear();
  jets_IsBTagged_MediumWpUp_JECshiftedDown.clear();
  jets_IsBTagged_MediumWpDown_JECshiftedDown.clear();
  jets_IsBTagged_TightWpCentral_JECshiftedDown.clear();
  jets_IsBTagged_TightWpUp_JECshiftedDown.clear();
  jets_IsBTagged_TightWpDown_JECshiftedDown.clear();
  jets_PF_jetIdPassedTight_JECshiftedDown.clear();


  numberOfJets_JERup = -999;
  numberOfJets30_JERup = -999;
  jets_pt_JERup.clear();
  jets_eta_JERup.clear();
  jets_phi_JERup.clear();
  jets_M_JERup.clear();
  jets_PU_jetIdRaw_JERup.clear();
  jets_PU_jetIdPassed_JERup.clear();
  jets_PF_jetIdPassed_JERup.clear();
  jets_defaultBtagAlgorithm_RawScore_JERup.clear();
  jets_PARTON_flavour_JERup.clear();
  jets_HADRON_flavour_JERup.clear();
  jets_BtagSF_LooseWpCentral_JERup.clear();
  jets_BtagSF_LooseWpUp_JERup.clear();
  jets_BtagSF_LooseWpDown_JERup.clear();
  jets_BtagSF_MediumWpCentral_JERup.clear();
  jets_BtagSF_MediumWpUp_JERup.clear();
  jets_BtagSF_MediumWpDown_JERup.clear();
  jets_BtagSF_TightWpCentral_JERup.clear();
  jets_BtagSF_TightWpUp_JERup.clear();
  jets_BtagSF_TightWpDown_JERup.clear();
  jets_BtagEff_LooseWp_JERup.clear();
  jets_BtagEff_MediumWp_JERup.clear();
  jets_BtagEff_TightWp_JERup.clear();
  jets_IsBTagged_LooseWpCentral_JERup.clear();
  jets_IsBTagged_LooseWpUp_JERup.clear();
  jets_IsBTagged_LooseWpDown_JERup.clear();
  jets_IsBTagged_MediumWpCentral_JERup.clear();
  jets_IsBTagged_MediumWpUp_JERup.clear();
  jets_IsBTagged_MediumWpDown_JERup.clear();
  jets_IsBTagged_TightWpCentral_JERup.clear();
  jets_IsBTagged_TightWpUp_JERup.clear();
  jets_IsBTagged_TightWpDown_JERup.clear();
  jets_PF_jetIdPassedTight_JERup.clear();


  numberOfJets_JERdown = -999;
  numberOfJets30_JERdown = -999;
  jets_pt_JERdown.clear();
  jets_eta_JERdown.clear();
  jets_phi_JERdown.clear();
  jets_M_JERdown.clear();
  jets_PU_jetIdRaw_JERdown.clear();
  jets_PU_jetIdPassed_JERdown.clear();
  jets_PF_jetIdPassed_JERdown.clear();
  jets_defaultBtagAlgorithm_RawScore_JERdown.clear();
  jets_PARTON_flavour_JERdown.clear();
  jets_HADRON_flavour_JERdown.clear();
  jets_BtagSF_LooseWpCentral_JERdown.clear();
  jets_BtagSF_LooseWpUp_JERdown.clear();
  jets_BtagSF_LooseWpDown_JERdown.clear();
  jets_BtagSF_MediumWpCentral_JERdown.clear();
  jets_BtagSF_MediumWpUp_JERdown.clear();
  jets_BtagSF_MediumWpDown_JERdown.clear();
  jets_BtagSF_TightWpCentral_JERdown.clear();
  jets_BtagSF_TightWpUp_JERdown.clear();
  jets_BtagSF_TightWpDown_JERdown.clear();
  jets_BtagEff_LooseWp_JERdown.clear();
  jets_BtagEff_MediumWp_JERdown.clear();
  jets_BtagEff_TightWp_JERdown.clear();
  jets_IsBTagged_LooseWpCentral_JERdown.clear();
  jets_IsBTagged_LooseWpUp_JERdown.clear();
  jets_IsBTagged_LooseWpDown_JERdown.clear();
  jets_IsBTagged_MediumWpCentral_JERdown.clear();
  jets_IsBTagged_MediumWpUp_JERdown.clear();
  jets_IsBTagged_MediumWpDown_JERdown.clear();
  jets_IsBTagged_TightWpCentral_JERdown.clear();
  jets_IsBTagged_TightWpUp_JERdown.clear();
  jets_IsBTagged_TightWpDown_JERdown.clear();
  jets_PF_jetIdPassedTight_JERdown.clear();

  /* new wisconsin style zero b-tag event weights */
  jets_zero_btag_event_weight = 1.0;
  jets_zero_btag_event_weight_up = 1.0;
  jets_zero_btag_event_weight_down = 1.0;
  jets_JECshiftedUp_zero_btag_event_weight = 1.0;
  jets_JECshiftedDown_zero_btag_event_weight = 1.0;
  jets_JERup_zero_btag_event_weight = 1.0;
  jets_JERdown_zero_btag_event_weight = 1.0;

  jets_zero_btag_event_weight_LOOSE = 1.0;
  jets_zero_btag_event_weight_LOOSE_up = 1.0;
  jets_zero_btag_event_weight_LOOSE_down = 1.0;
  jets_JECshiftedUp_zero_btag_event_weight_LOOSE = 1.0;
  jets_JECshiftedDown_zero_btag_event_weight_LOOSE = 1.0;
  jets_JERup_zero_btag_event_weight_LOOSE = 1.0;
  jets_JERdown_zero_btag_event_weight_LOOSE = 1.0;





  genParticle_pdgId.clear();
  genParticle_status.clear();
  genParticle_isPrompt.clear();
  genParticle_isPromptFinalState.clear();
  genParticle_isDirectPromptTauDecayProduct.clear();
  genParticle_isDirectPromptTauDecayProductFinalState.clear();
  genParticle_fromHardProcess.clear();
  genParticle_isLastCopy.clear();

  genParticle_pt.clear();
  genParticle_eta.clear();
  genParticle_phi.clear();
  genParticle_M.clear();
  genDaughter_pdgId.clear();
  genDaughter_status.clear();
  genDaughter_pt.clear();
  genDaughter_eta.clear();
  genDaughter_phi.clear();
  genDaughter_M.clear();
  genMother_pdgId.clear();
  genMother_status.clear();
  genMother_pt.clear();
  genMother_eta.clear();
  genMother_phi.clear();
  genMother_M.clear();


  leg1_MCMatchType = -999;
  leg1_genMCmatch_pt = NAN;
  leg1_genMCmatch_eta = NAN;
  leg1_genMCmatch_phi = NAN;
  leg1_genMCmatch_M = NAN;
  leg1_MCMatchPdgId = -999;    
  leg2_MCMatchType = -999;
  leg2_genMCmatch_pt = NAN;
  leg2_genMCmatch_eta = NAN;
  leg2_genMCmatch_phi = NAN;
  leg2_genMCmatch_M = NAN;
  leg2_MCMatchPdgId = -999;

  effLep_MCMatchType.clear();
  effLep_genMCmatch_pt.clear();
  effLep_genMCmatch_eta.clear();
  effLep_genMCmatch_phi.clear();
  effLep_genMCmatch_M.clear();
  effLep_MCMatchPdgId.clear();



  IsZTT = -999;
  IsZL = -999;
  IsZJ = -999;
  IsZLL = -999;



  rho  = NAN;

  DataSet = "NULL";
  EventTotal = 0;
  EventType = "NULL";
  KeyName = "NULL";
  DataCard = "NULL";
  CrossSection = 1.0;
  FilterEff = 1.0;
  CodeVersion = 0.0;


  genBosonTotal_pt = NAN;
  genBosonTotal_eta = NAN;
  genBosonTotal_phi = NAN;
  genBosonTotal_M = NAN;

  genBosonVisible_pt = NAN;
  genBosonVisible_eta = NAN;
  genBosonVisible_phi = NAN;
  genBosonVisible_M = NAN;


MaxPtGenBoson_WisconinStyle_pt  = NAN;
MaxPtGenBoson_WisconinStyle_eta  = NAN;
MaxPtGenBoson_WisconinStyle_phi  = NAN;
MaxPtGenBoson_WisconinStyle_M  = NAN;

  isZTTatGenLevel = 0;
  isZEEatGenLevel = 0;
  isZMMatGenLevel = 0;


  genTopPt1 = NAN;
  genTopPt2 = NAN;

  originalXWGTUP = NAN;
  theory_scale_factors.clear();



  DiMuon_Flag = 0;
  DiElectron_Flag = 0;
  ThirdMuon_Flag  = 0;
  ThirdElectron_Flag  = 0;




  leg1_maxPtTrigObjMatch = NAN;
  leg2_maxPtTrigObjMatch = NAN;
  effLep_maxPtTrigObjMatch.clear();

 }

 //////////////////////////////////////////////////
// ------------ method called once each job just before starting event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginJob() 
{

   /* create TTree */
   
  edm::Service<TFileService> fs;
  FlatTuple = fs->make<TTree>("FlatTuple","FlatTuple");

  //////////////
  // init values

    reInit(); 


  ///////////////////////////////////////////////////
  // the branches                             
  ///////////////////////////////////////////////////


  /////////////////////////
  /* general info        */
  /////////////////////////

  FlatTuple->Branch("run", &run);
  FlatTuple->Branch("luminosityBlock", &luminosityBlock);
  FlatTuple->Branch("event", &event);
  FlatTuple->Branch("isRealData", &isRealData);
  FlatTuple->Branch("DataSet", &DataSet); 
  FlatTuple->Branch("EventTotal", &EventTotal); 
  FlatTuple->Branch("EventType", &EventType); 
  FlatTuple->Branch("KeyName", &KeyName); 
  FlatTuple->Branch("DataCard", &DataCard);
  FlatTuple->Branch("CrossSection", &CrossSection); 
  FlatTuple->Branch("FilterEff", &FilterEff); 
  FlatTuple->Branch("CodeVersion", &CodeVersion); 
  
  if( !SmallTree_ ) 
  {
    FlatTuple->Branch("AppliedLepCuts", &AppliedLepCuts);
  }

  /////////////////////////
  /* run settings        */
  /////////////////////////

  FlatTuple->Branch("TauEsNumberSigmasShifted", &TauEsNumberSigmasShifted);
  FlatTuple->Branch("ElectronEsNumberSigmasShifted", &ElectronEsNumberSigmasShifted);
  FlatTuple->Branch("isSmallTree",&SmallTree_);

  if( !SmallTree_ ) 
  {
    FlatTuple->Branch("treeInfoString", &treeInfoString);
    FlatTuple->Branch("RecoilCorrectionType", &RecoilCorrectionType);
    FlatTuple->Branch("MetSystematicType", &MetSystematicType);
  }

  /////////////////////////
  /* pair general info   */
  /////////////////////////

  FlatTuple->Branch("pairRank",&pairRank);
  FlatTuple->Branch("isBoostedChannelPair",&isBoostedChannelPair);
  FlatTuple->Branch("isOsPair", &isOsPair);
  FlatTuple->Branch("CandidateEventType", &CandidateEventType);

  /////////////////////////
  /* basic observables   */
  /////////////////////////
  
  FlatTuple->Branch("VISMass", &VISMass);
  FlatTuple->Branch("DeltaR_leg1_leg2", &DeltaR_leg1_leg2);
  FlatTuple->Branch("rho", &rho);

  /////////////////////////
  /* pileup info         */
  /////////////////////////
  
  FlatTuple->Branch("NumberOfGoodVertices",&NumberOfGoodVertices);
  FlatTuple->Branch("puWeight",&puWeight);
  FlatTuple->Branch("NumPileupInt",&NumPileupInt);
  FlatTuple->Branch("NumTruePileUpInt",&NumTruePileUpInt);
  
  if(!SmallTree_)
  {
    FlatTuple->Branch("vertex_NDOF",&vertex_NDOF);
    FlatTuple->Branch("vertex_CHI2",&vertex_CHI2);
    FlatTuple->Branch("vertex_positionRho",&vertex_positionRho);

    FlatTuple->Branch("vertex_positionX",&vertex_positionX);
    FlatTuple->Branch("vertex_positionY",&vertex_positionY);
    FlatTuple->Branch("vertex_positionZ",&vertex_positionZ);
    FlatTuple->Branch("vertex_positionTheta",&vertex_positionTheta);
    FlatTuple->Branch("vertex_positionEta",&vertex_positionEta);
    FlatTuple->Branch("vertex_positionPhi",&vertex_positionPhi);
  }


  //////////////////////////////
  /* MVA MET related branches */
  //////////////////////////////

  // corrected & uncorrected - always present

  FlatTuple->Branch("corr_mvaMET", &corr_mvaMET);
  FlatTuple->Branch("corr_mvaMETphi", &corr_mvaMETphi);
  FlatTuple->Branch("corr_MTmvaMET_leg1", &corr_MTmvaMET_leg1);
  FlatTuple->Branch("corr_MTmvaMET_leg2", &corr_MTmvaMET_leg2);

  FlatTuple->Branch("mvaMET_cov00", &mvaMET_cov00);
  FlatTuple->Branch("mvaMET_cov01", &mvaMET_cov01);
  FlatTuple->Branch("mvaMET_cov10", &mvaMET_cov10);
  FlatTuple->Branch("mvaMET_cov11", &mvaMET_cov11);

  FlatTuple->Branch("uncorr_mvaMET", &uncorr_mvaMET);
  FlatTuple->Branch("uncorr_mvaMETphi", &uncorr_mvaMETphi);
  FlatTuple->Branch("uncorr_MTmvaMET_leg1", &uncorr_MTmvaMET_leg1);
  FlatTuple->Branch("uncorr_MTmvaMET_leg2", &uncorr_MTmvaMET_leg2);

  // response +/- and resolusion +/- variants
  // only keep for non-tau ES and non-electron ES systematic varied pairs 

  if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
  {
    FlatTuple->Branch("responseUP_mvaMET", &responseUP_mvaMET);
    FlatTuple->Branch("responseUP_mvaMETphi", &responseUP_mvaMETphi);
    FlatTuple->Branch("responseUP_MTmvaMET_leg1", &responseUP_MTmvaMET_leg1);
    FlatTuple->Branch("responseUP_MTmvaMET_leg2", &responseUP_MTmvaMET_leg2);
    FlatTuple->Branch("responseDOWN_mvaMET", &responseDOWN_mvaMET);
    FlatTuple->Branch("responseDOWN_mvaMETphi", &responseDOWN_mvaMETphi);
    FlatTuple->Branch("responseDOWN_MTmvaMET_leg1", &responseDOWN_MTmvaMET_leg1);
    FlatTuple->Branch("responseDOWN_MTmvaMET_leg2", &responseDOWN_MTmvaMET_leg2);
    FlatTuple->Branch("resolutionUP_mvaMET", &resolutionUP_mvaMET);
    FlatTuple->Branch("resolutionUP_mvaMETphi", &resolutionUP_mvaMETphi);
    FlatTuple->Branch("resolutionUP_MTmvaMET_leg1", &resolutionUP_MTmvaMET_leg1);
    FlatTuple->Branch("resolutionUP_MTmvaMET_leg2", &resolutionUP_MTmvaMET_leg2);
    FlatTuple->Branch("resolutionDOWN_mvaMET", &resolutionDOWN_mvaMET);
    FlatTuple->Branch("resolutionDOWN_mvaMETphi", &resolutionDOWN_mvaMETphi);
    FlatTuple->Branch("resolutionDOWN_MTmvaMET_leg1", &resolutionDOWN_MTmvaMET_leg1);
    FlatTuple->Branch("resolutionDOWN_MTmvaMET_leg2", &resolutionDOWN_MTmvaMET_leg2);
  }


  //////////////////////////////
  /* pf-MET                   */
  //////////////////////////////

  FlatTuple->Branch("pfMET", &pfMET);                         /* PF MET direct from miniAOD */
  FlatTuple->Branch("pfMETphi", &pfMETphi);                   /* PF MET direct from miniAOD */

  FlatTuple->Branch("MTpfMET_leg1", &MTpfMET_leg1);           /* mt_1 using PF MET direct from miniAOD */
  FlatTuple->Branch("MTpfMET_leg2", &MTpfMET_leg2);           /* mt_2 using PF MET direct from miniAOD */
    
  FlatTuple->Branch("CORRpfMET", &CORRpfMET);         /* PF MET with RECOIL CORRECTIONS applied */
  FlatTuple->Branch("CORRpfMETphi", &CORRpfMETphi);   /* PF MET with RECOIL CORRECTIONS applied */

  FlatTuple->Branch("MTCORRpfMET_leg1", &MTCORRpfMET_leg1);    /* mt_1 using PF MET with recoil corr */
  FlatTuple->Branch("MTCORRpfMET_leg2", &MTCORRpfMET_leg2);    /* mt_2 using PF MET with recoil corr */
    

  // only keep for non-tau ES and non-electron ES systematic varied pairs 

  if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
  {

    // response +/- and resolusion +/- variants APPLIED ONTO NON-RECOIL CORRECTED PFMET

    FlatTuple->Branch("responseUP_pfMET", &responseUP_pfMET);
    FlatTuple->Branch("responseUP_pfMETphi", &responseUP_pfMETphi);
    FlatTuple->Branch("responseUP_MTpfMET_leg1", &responseUP_MTpfMET_leg1);
    FlatTuple->Branch("responseUP_MTpfMET_leg2", &responseUP_MTpfMET_leg2);
    FlatTuple->Branch("responseDOWN_pfMET", &responseDOWN_pfMET);
    FlatTuple->Branch("responseDOWN_pfMETphi", &responseDOWN_pfMETphi);
    FlatTuple->Branch("responseDOWN_MTpfMET_leg1", &responseDOWN_MTpfMET_leg1);
    FlatTuple->Branch("responseDOWN_MTpfMET_leg2", &responseDOWN_MTpfMET_leg2);
    FlatTuple->Branch("resolutionUP_pfMET", &resolutionUP_pfMET);
    FlatTuple->Branch("resolutionUP_pfMETphi", &resolutionUP_pfMETphi);
    FlatTuple->Branch("resolutionUP_MTpfMET_leg1", &resolutionUP_MTpfMET_leg1);
    FlatTuple->Branch("resolutionUP_MTpfMET_leg2", &resolutionUP_MTpfMET_leg2);
    FlatTuple->Branch("resolutionDOWN_pfMET", &resolutionDOWN_pfMET);
    FlatTuple->Branch("resolutionDOWN_pfMETphi", &resolutionDOWN_pfMETphi);
    FlatTuple->Branch("resolutionDOWN_MTpfMET_leg1", &resolutionDOWN_MTpfMET_leg1);
    FlatTuple->Branch("resolutionDOWN_MTpfMET_leg2", &resolutionDOWN_MTpfMET_leg2);

    // response +/- and resolusion +/- variants APPLIED ONTO RECOIL CORRECTED PFMET

    FlatTuple->Branch("responseUP_CORRpfMET", &responseUP_CORRpfMET);
    FlatTuple->Branch("responseUP_CORRpfMETphi", &responseUP_CORRpfMETphi);
    FlatTuple->Branch("responseUP_MTCORRpfMET_leg1", &responseUP_MTCORRpfMET_leg1);
    FlatTuple->Branch("responseUP_MTCORRpfMET_leg2", &responseUP_MTCORRpfMET_leg2);
    FlatTuple->Branch("responseDOWN_CORRpfMET", &responseDOWN_CORRpfMET);
    FlatTuple->Branch("responseDOWN_CORRpfMETphi", &responseDOWN_CORRpfMETphi);
    FlatTuple->Branch("responseDOWN_MTCORRpfMET_leg1", &responseDOWN_MTCORRpfMET_leg1);
    FlatTuple->Branch("responseDOWN_MTCORRpfMET_leg2", &responseDOWN_MTCORRpfMET_leg2);
    FlatTuple->Branch("resolutionUP_CORRpfMET", &resolutionUP_CORRpfMET);
    FlatTuple->Branch("resolutionUP_CORRpfMETphi", &resolutionUP_CORRpfMETphi);
    FlatTuple->Branch("resolutionUP_MTCORRpfMET_leg1", &resolutionUP_MTCORRpfMET_leg1);
    FlatTuple->Branch("resolutionUP_MTCORRpfMET_leg2", &resolutionUP_MTCORRpfMET_leg2);
    FlatTuple->Branch("resolutionDOWN_CORRpfMET", &resolutionDOWN_CORRpfMET);
    FlatTuple->Branch("resolutionDOWN_CORRpfMETphi", &resolutionDOWN_CORRpfMETphi);
    FlatTuple->Branch("resolutionDOWN_MTCORRpfMET_leg1", &resolutionDOWN_MTCORRpfMET_leg1);
    FlatTuple->Branch("resolutionDOWN_MTCORRpfMET_leg2", &resolutionDOWN_MTCORRpfMET_leg2);


  }


  FlatTuple->Branch("pfmet_raw_Pt" , &pfmet_raw_Pt);
  FlatTuple->Branch("pfmet_raw_Phi" , &pfmet_raw_Phi);
  FlatTuple->Branch("pfmet_raw_MT1" , &pfmet_raw_MT1);
  FlatTuple->Branch("pfmet_raw_MT2" , &pfmet_raw_MT2);
  FlatTuple->Branch("pfmet_type1_Pt" , &pfmet_type1_Pt);
  FlatTuple->Branch("pfmet_type1_Phi" , &pfmet_type1_Phi);
  FlatTuple->Branch("pfmet_type1_MT1" , &pfmet_type1_MT1);
  FlatTuple->Branch("pfmet_type1_MT2" , &pfmet_type1_MT2);
  FlatTuple->Branch("pfmet_type1_JetResUp_Pt" , &pfmet_type1_JetResUp_Pt);
  FlatTuple->Branch("pfmet_type1_JetResUp_Phi" , &pfmet_type1_JetResUp_Phi);
  FlatTuple->Branch("pfmet_type1_JetResUp_MT1" , &pfmet_type1_JetResUp_MT1);
  FlatTuple->Branch("pfmet_type1_JetResUp_MT2" , &pfmet_type1_JetResUp_MT2);
  FlatTuple->Branch("pfmet_type1_JetResDown_Pt" , &pfmet_type1_JetResDown_Pt);
  FlatTuple->Branch("pfmet_type1_JetResDown_Phi" , &pfmet_type1_JetResDown_Phi);
  FlatTuple->Branch("pfmet_type1_JetResDown_MT1" , &pfmet_type1_JetResDown_MT1);
  FlatTuple->Branch("pfmet_type1_JetResDown_MT2" , &pfmet_type1_JetResDown_MT2);
  FlatTuple->Branch("pfmet_type1_JetEnUp_Pt" , &pfmet_type1_JetEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_JetEnUp_Phi" , &pfmet_type1_JetEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_JetEnUp_MT1" , &pfmet_type1_JetEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_JetEnUp_MT2" , &pfmet_type1_JetEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_JetEnDown_Pt" , &pfmet_type1_JetEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_JetEnDown_Phi" , &pfmet_type1_JetEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_JetEnDown_MT1" , &pfmet_type1_JetEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_JetEnDown_MT2" , &pfmet_type1_JetEnDown_MT2);
  FlatTuple->Branch("pfmet_type1_MuonEnUp_Pt" , &pfmet_type1_MuonEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_MuonEnUp_Phi" , &pfmet_type1_MuonEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_MuonEnUp_MT1" , &pfmet_type1_MuonEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_MuonEnUp_MT2" , &pfmet_type1_MuonEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_MuonEnDown_Pt" , &pfmet_type1_MuonEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_MuonEnDown_Phi" , &pfmet_type1_MuonEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_MuonEnDown_MT1" , &pfmet_type1_MuonEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_MuonEnDown_MT2" , &pfmet_type1_MuonEnDown_MT2);
  FlatTuple->Branch("pfmet_type1_ElectronEnUp_Pt" , &pfmet_type1_ElectronEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_ElectronEnUp_Phi" , &pfmet_type1_ElectronEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_ElectronEnUp_MT1" , &pfmet_type1_ElectronEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_ElectronEnUp_MT2" , &pfmet_type1_ElectronEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_ElectronEnDown_Pt" , &pfmet_type1_ElectronEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_ElectronEnDown_Phi" , &pfmet_type1_ElectronEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_ElectronEnDown_MT1" , &pfmet_type1_ElectronEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_ElectronEnDown_MT2" , &pfmet_type1_ElectronEnDown_MT2);
  FlatTuple->Branch("pfmet_type1_TauEnUp_Pt" , &pfmet_type1_TauEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_TauEnUp_Phi" , &pfmet_type1_TauEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_TauEnUp_MT1" , &pfmet_type1_TauEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_TauEnUp_MT2" , &pfmet_type1_TauEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_TauEnDown_Pt" , &pfmet_type1_TauEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_TauEnDown_Phi" , &pfmet_type1_TauEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_TauEnDown_MT1" , &pfmet_type1_TauEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_TauEnDown_MT2" , &pfmet_type1_TauEnDown_MT2);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnUp_Pt" , &pfmet_type1_UnclusteredEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnUp_Phi" , &pfmet_type1_UnclusteredEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnUp_MT1" , &pfmet_type1_UnclusteredEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnUp_MT2" , &pfmet_type1_UnclusteredEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnDown_Pt" , &pfmet_type1_UnclusteredEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnDown_Phi" , &pfmet_type1_UnclusteredEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnDown_MT1" , &pfmet_type1_UnclusteredEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_UnclusteredEnDown_MT2" , &pfmet_type1_UnclusteredEnDown_MT2);
  FlatTuple->Branch("pfmet_type1_PhotonEnUp_Pt" , &pfmet_type1_PhotonEnUp_Pt);
  FlatTuple->Branch("pfmet_type1_PhotonEnUp_Phi" , &pfmet_type1_PhotonEnUp_Phi);
  FlatTuple->Branch("pfmet_type1_PhotonEnUp_MT1" , &pfmet_type1_PhotonEnUp_MT1);
  FlatTuple->Branch("pfmet_type1_PhotonEnUp_MT2" , &pfmet_type1_PhotonEnUp_MT2);
  FlatTuple->Branch("pfmet_type1_PhotonEnDown_Pt" , &pfmet_type1_PhotonEnDown_Pt);
  FlatTuple->Branch("pfmet_type1_PhotonEnDown_Phi" , &pfmet_type1_PhotonEnDown_Phi);
  FlatTuple->Branch("pfmet_type1_PhotonEnDown_MT1" , &pfmet_type1_PhotonEnDown_MT1);
  FlatTuple->Branch("pfmet_type1_PhotonEnDown_MT2" , &pfmet_type1_PhotonEnDown_MT2);

  FlatTuple->Branch("RAWpfMET", &RAWpfMET);
  FlatTuple->Branch("RAWpfMETphi", &RAWpfMETphi);

  FlatTuple->Branch("pfMET_cov00", &pfMET_cov00);
  FlatTuple->Branch("pfMET_cov01", &pfMET_cov01);
  FlatTuple->Branch("pfMET_cov10", &pfMET_cov10);
  FlatTuple->Branch("pfMET_cov11", &pfMET_cov11);


  //////////////////////////////
  /* puppi-MET                */
  //////////////////////////////

  FlatTuple->Branch("puppiMET", &puppiMET);
  FlatTuple->Branch("puppiMETphi", &puppiMETphi);


  if(!SmallTree_)
  {
    FlatTuple->Branch("MTpuppiMET_leg1", &MTpuppiMET_leg1);
    FlatTuple->Branch("MTpuppiMET_leg2", &MTpuppiMET_leg2);

    FlatTuple->Branch("RAWpuppiMET", &RAWpuppiMET);
    FlatTuple->Branch("RAWpuppiMETphi", &RAWpuppiMETphi);  
  }  

  //////////////////////////////
  /* gen-MET    */
  //////////////////////////////

  FlatTuple->Branch("genMET", &genMET);
  FlatTuple->Branch("genMETphi", &genMETphi);

  FlatTuple->Branch("genMETeta", &genMETeta);
  FlatTuple->Branch("genMETmass", &genMETmass);


  //////////////////////////////
  /* SVFit related info       */
  //////////////////////////////

  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass", &SVMass);
  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass", &SVTransverseMass);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_uncorr_mvaMET", &SVMass_uncorr_mvaMET);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_uncorr_mvaMET", &SVTransverseMass_uncorr_mvaMET);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_responseUP_mvaMET", &SVMass_responseUP_mvaMET);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_responseUP_mvaMET", &SVTransverseMass_responseUP_mvaMET);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_responseDN_mvaMET", &SVMass_responseDN_mvaMET);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_responseDN_mvaMET", &SVTransverseMass_responseDN_mvaMET);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_resolutionUP_mvaMET", &SVMass_resolutionUP_mvaMET);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_resolutionUP_mvaMET", &SVTransverseMass_resolutionUP_mvaMET);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_resolutionDN_mvaMET", &SVMass_resolutionDN_mvaMET);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_resolutionDN_mvaMET", &SVTransverseMass_resolutionDN_mvaMET);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_pfMET", &SVMass_pfMET);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_pfMET", &SVTransverseMass_pfMET);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVMass_puppiMET", &SVMass_puppiMET);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVTransverseMass_puppiMET", &SVTransverseMass_puppiMET);

  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_mvaMET_diTau_pt", &SVFit_mvaMET_diTau_pt);
  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_mvaMET_diTau_eta", &SVFit_mvaMET_diTau_eta);
  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_mvaMET_diTau_phi", &SVFit_mvaMET_diTau_phi);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_uncorr_mvaMET_diTau_pt", &SVFit_uncorr_mvaMET_diTau_pt);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_uncorr_mvaMET_diTau_eta", &SVFit_uncorr_mvaMET_diTau_eta);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_uncorr_mvaMET_diTau_phi", &SVFit_uncorr_mvaMET_diTau_phi);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseUP_mvaMET_diTau_pt", &SVFit_responseUP_mvaMET_diTau_pt);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseUP_mvaMET_diTau_eta", &SVFit_responseUP_mvaMET_diTau_eta);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseUP_mvaMET_diTau_phi", &SVFit_responseUP_mvaMET_diTau_phi);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseDN_mvaMET_diTau_pt", &SVFit_responseDN_mvaMET_diTau_pt);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseDN_mvaMET_diTau_eta", &SVFit_responseDN_mvaMET_diTau_eta);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseDN_mvaMET_diTau_phi", &SVFit_responseDN_mvaMET_diTau_phi);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionUP_mvaMET_diTau_pt", &SVFit_resolutionUP_mvaMET_diTau_pt);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionUP_mvaMET_diTau_eta", &SVFit_resolutionUP_mvaMET_diTau_eta);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionUP_mvaMET_diTau_phi", &SVFit_resolutionUP_mvaMET_diTau_phi);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionDN_mvaMET_diTau_pt", &SVFit_resolutionDN_mvaMET_diTau_pt);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionDN_mvaMET_diTau_eta", &SVFit_resolutionDN_mvaMET_diTau_eta);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionDN_mvaMET_diTau_phi", &SVFit_resolutionDN_mvaMET_diTau_phi);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_pfMET_diTau_pt", &SVFit_pfMET_diTau_pt);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_pfMET_diTau_eta", &SVFit_pfMET_diTau_eta);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_pfMET_diTau_phi", &SVFit_pfMET_diTau_phi);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_puppiMET_diTau_pt", &SVFit_puppiMET_diTau_pt);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_puppiMET_diTau_eta", &SVFit_puppiMET_diTau_eta);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_puppiMET_diTau_phi", &SVFit_puppiMET_diTau_phi);

  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_mvaMET_FittedMET", &SVFit_mvaMET_FittedMET);
  if(USE_MVAMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_mvaMET_FittedMETphi", &SVFit_mvaMET_FittedMETphi);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_uncorr_mvaMET_FittedMET", &SVFit_uncorr_mvaMET_FittedMET);
  if(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_uncorr_mvaMET_FittedMETphi", &SVFit_uncorr_mvaMET_FittedMETphi);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseUP_mvaMET_FittedMET", &SVFit_responseUP_mvaMET_FittedMET);
  if(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseUP_mvaMET_FittedMETphi", &SVFit_responseUP_mvaMET_FittedMETphi);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseDN_mvaMET_FittedMET", &SVFit_responseDN_mvaMET_FittedMET);
  if(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_responseDN_mvaMET_FittedMETphi", &SVFit_responseDN_mvaMET_FittedMETphi);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionUP_mvaMET_FittedMET", &SVFit_resolutionUP_mvaMET_FittedMET);
  if(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionUP_mvaMET_FittedMETphi", &SVFit_resolutionUP_mvaMET_FittedMETphi);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionDN_mvaMET_FittedMET", &SVFit_resolutionDN_mvaMET_FittedMET);
  if(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_resolutionDN_mvaMET_FittedMETphi", &SVFit_resolutionDN_mvaMET_FittedMETphi);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_pfMET_FittedMET", &SVFit_pfMET_FittedMET);
  if(USE_PFMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_pfMET_FittedMETphi", &SVFit_pfMET_FittedMETphi);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_puppiMET_FittedMET", &SVFit_puppiMET_FittedMET);
  if(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple) FlatTuple->Branch("SVFit_puppiMET_FittedMETphi", &SVFit_puppiMET_FittedMETphi);


  //////////////////////////////
  /* trigger related info     */
  //////////////////////////////


  /* in 2016 samples we always need this ! */
  // if(!SmallTree_)
  // {
    for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
    {
      std::string versionStrippedName = triggerSummaryChecks.at(x);
      versionStrippedName.erase(versionStrippedName.find("_v"),versionStrippedName.length());

      std::cout<<versionStrippedName<<"\n";

      FlatTuple->Branch(("leg1_"+versionStrippedName).c_str(), &leg1_GoodForHLTPath[x]);
      FlatTuple->Branch(("leg2_"+versionStrippedName).c_str(), &leg2_GoodForHLTPath[x]);
    }

    FlatTuple->Branch("leg1_L1IsoTauMatch_pt", &leg1_L1IsoTauMatch_pt);
    FlatTuple->Branch("leg1_L1IsoTauMatch_eta", &leg1_L1IsoTauMatch_eta);
    FlatTuple->Branch("leg1_L1IsoTauMatch_phi", &leg1_L1IsoTauMatch_phi);

    FlatTuple->Branch("leg2_L1IsoTauMatch_pt", &leg2_L1IsoTauMatch_pt);
    FlatTuple->Branch("leg2_L1IsoTauMatch_eta", &leg2_L1IsoTauMatch_eta);
    FlatTuple->Branch("leg2_L1IsoTauMatch_phi", &leg2_L1IsoTauMatch_phi);

    FlatTuple->Branch("leg1_maxPtTrigObjMatch", &leg1_maxPtTrigObjMatch);
    FlatTuple->Branch("leg2_maxPtTrigObjMatch", &leg2_maxPtTrigObjMatch);

    FlatTuple->Branch("PairPassesDoubleTauIsoTau28MatchCut", &PairPassesDoubleTauIsoTau28MatchCut);
  //}

  //////////////////////////////
  /* leg1 info                */
  //////////////////////////////


  /* essentials */

  FlatTuple->Branch("leg1_leptonType", &leg1_leptonType);
  FlatTuple->Branch("leg1_pt", &leg1_pt);
  FlatTuple->Branch("leg1_eta", &leg1_eta);
  FlatTuple->Branch("leg1_phi", &leg1_phi);
  FlatTuple->Branch("leg1_M", &leg1_M);
  FlatTuple->Branch("leg1_RelIso",&leg1_RelIso);
  FlatTuple->Branch("leg1_dz", &leg1_dz);
  FlatTuple->Branch("leg1_dxy", &leg1_dxy);
  FlatTuple->Branch("leg1_charge", &leg1_charge);

  FlatTuple->Branch("leg1_raw_electronMVA", &leg1_raw_electronMVA);
  FlatTuple->Branch("leg1_category_electronMVA", &leg1_category_electronMVA);
  FlatTuple->Branch("leg1_passFail_electronMVA80", &leg1_passFail_electronMVA80);
  FlatTuple->Branch("leg1_passFail_electronMVA90", &leg1_passFail_electronMVA90);
  FlatTuple->Branch("leg1_passFail_VetoElectronCutBasedID", &leg1_passFail_VetoElectronCutBasedID);
  FlatTuple->Branch("leg1_passFail_TightElectronCutBasedID", &leg1_passFail_TightElectronCutBasedID);
  FlatTuple->Branch("leg1_SuperClusterEta", &leg1_SuperClusterEta);
  FlatTuple->Branch("leg1_numberOfMissingInnerHits", &leg1_numberOfMissingInnerHits);
  FlatTuple->Branch("leg1_passConversionVeto", &leg1_passConversionVeto);

  FlatTuple->Branch("leg1_ZimpactTau", &leg1_ZimpactTau);
  FlatTuple->Branch("leg1_numStrips", &leg1_numStrips);
  FlatTuple->Branch("leg1_dzTauVertex", &leg1_dzTauVertex);
  FlatTuple->Branch("leg1_numHadrons", &leg1_numHadrons);

  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1raw", &leg1_rerunDiscriminationByIsolationMVArun2v1raw);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1VLoose", &leg1_rerunDiscriminationByIsolationMVArun2v1VLoose);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1Loose", &leg1_rerunDiscriminationByIsolationMVArun2v1Loose);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1Medium", &leg1_rerunDiscriminationByIsolationMVArun2v1Medium);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1Tight", &leg1_rerunDiscriminationByIsolationMVArun2v1Tight);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1VTight", &leg1_rerunDiscriminationByIsolationMVArun2v1VTight);
  FlatTuple->Branch("leg1_rerunDiscriminationByIsolationMVArun2v1VVTight", &leg1_rerunDiscriminationByIsolationMVArun2v1VVTight);


  FlatTuple->Branch("leg1_decayMode", &leg1_decayMode);

  FlatTuple->Branch("leg1_isGlobalMuon", &leg1_isGlobalMuon);
  FlatTuple->Branch("leg1_isGoodGlobalMuon", &leg1_isGoodGlobalMuon);
  FlatTuple->Branch("leg1_passesLooseMuonId", &leg1_passesLooseMuonId);
  FlatTuple->Branch("leg1_passesMediumMuonId", &leg1_passesMediumMuonId);
  FlatTuple->Branch("leg1_passesMediumMuonId_ICHEP16", &leg1_passesMediumMuonId_ICHEP16);
  FlatTuple->Branch("leg1_passesMediumMuonId_Moriond17", &leg1_passesMediumMuonId_Moriond17);
  FlatTuple->Branch("leg1_passesTightMuonId", &leg1_passesTightMuonId);
  FlatTuple->Branch("leg1_isPFMuon", &leg1_isPFMuon);
  FlatTuple->Branch("leg1_isLooseMuon", &leg1_isLooseMuon);
  FlatTuple->Branch("leg1_isTightMuon", &leg1_isTightMuon);

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {
      FlatTuple->Branch(("leg1_"+tauIDsToKeep.at(x)).c_str(), &leg1_tauIDs[x]);
  }

  FlatTuple->Branch("leg1_MCMatchType", &leg1_MCMatchType);
  FlatTuple->Branch("leg1_genMCmatch_pt", &leg1_genMCmatch_pt);
  FlatTuple->Branch("leg1_genMCmatch_eta", &leg1_genMCmatch_eta);
  FlatTuple->Branch("leg1_genMCmatch_phi", &leg1_genMCmatch_phi);
  FlatTuple->Branch("leg1_genMCmatch_M", &leg1_genMCmatch_M);
  FlatTuple->Branch("leg1_MCMatchPdgId", &leg1_MCMatchPdgId);


  if( !SmallTree_ )
  {
    FlatTuple->Branch("leg1_gen_pt", &leg1_gen_pt);
    FlatTuple->Branch("leg1_gen_eta", &leg1_gen_eta);
    FlatTuple->Branch("leg1_gen_phi", &leg1_gen_phi);
    FlatTuple->Branch("leg1_gen_M", &leg1_gen_M);

    FlatTuple->Branch("leg1_genMother_pt", &leg1_genMother_pt);
    FlatTuple->Branch("leg1_genMother_eta", &leg1_genMother_eta);
    FlatTuple->Branch("leg1_genMother_phi", &leg1_genMother_phi);
    FlatTuple->Branch("leg1_genMother_M", &leg1_genMother_M);

    FlatTuple->Branch("leg1_genJet_pt", &leg1_genJet_pt);
    FlatTuple->Branch("leg1_genJet_eta", &leg1_genJet_eta);
    FlatTuple->Branch("leg1_genJet_phi", &leg1_genJet_phi);
    FlatTuple->Branch("leg1_genJet_M", &leg1_genJet_M);
    FlatTuple->Branch("leg1_genJet_pdgId", &leg1_genJet_pdgId);

    FlatTuple->Branch("leg1_EffectiveArea", &leg1_EffectiveArea);
    FlatTuple->Branch("leg1_PFpdgId", &leg1_PFpdgId);
    FlatTuple->Branch("leg1_GENpdgId", &leg1_GENpdgId);
    FlatTuple->Branch("leg1_GENMOTHERpdgId", &leg1_GENMOTHERpdgId);
    FlatTuple->Branch("leg1_IP", &leg1_IP);
    FlatTuple->Branch("leg1_IPerror", &leg1_IPerror);
    FlatTuple->Branch("leg1_PUchargedHadronIso", &leg1_PUchargedHadronIso);
    FlatTuple->Branch("leg1_chargedHadronIso", &leg1_chargedHadronIso);
    FlatTuple->Branch("leg1_neutralHadronIso", &leg1_neutralHadronIso);
    FlatTuple->Branch("leg1_photonIso", &leg1_photonIso);
    FlatTuple->Branch("leg1_DepositR03ECal", &leg1_DepositR03ECal);
    FlatTuple->Branch("leg1_DepositR03Hcal", &leg1_DepositR03Hcal);
    FlatTuple->Branch("leg1_DepositR03TrackerOfficial", &leg1_DepositR03TrackerOfficial);
    FlatTuple->Branch("leg1_isSoftMuon", &leg1_isSoftMuon);
    FlatTuple->Branch("leg1_isTrackerMuon", &leg1_isTrackerMuon);
    FlatTuple->Branch("leg1_muonCombQualChi2LocalPosition", &leg1_muonCombQualChi2LocalPosition);
    FlatTuple->Branch("leg1_muonCombQualTrkKink", &leg1_muonCombQualTrkKink);
    FlatTuple->Branch("leg1_muonGlobalTrackNormChi2", &leg1_muonGlobalTrackNormChi2);
    FlatTuple->Branch("leg1_muonInnerTrkValidFraction", &leg1_muonInnerTrkValidFraction);
    FlatTuple->Branch("leg1_muonSegmentCompatibility", &leg1_muonSegmentCompatibility);
    FlatTuple->Branch("leg1_ooEmooP", &leg1_ooEmooP);
    FlatTuple->Branch("leg1_full5x5_sigmaIetaIeta", &leg1_full5x5_sigmaIetaIeta);
    FlatTuple->Branch("leg1_hadronicOverEm", &leg1_hadronicOverEm);
    FlatTuple->Branch("leg1_isEB", &leg1_isEB);
    FlatTuple->Branch("leg1_isEBEEGap", &leg1_isEBEEGap);
    FlatTuple->Branch("leg1_isEBEtaGap", &leg1_isEBEtaGap);
    FlatTuple->Branch("leg1_isEBPhiGap", &leg1_isEBPhiGap);
    FlatTuple->Branch("leg1_isEE", &leg1_isEE);
    FlatTuple->Branch("leg1_isEEDeeGap", &leg1_isEEDeeGap);
    FlatTuple->Branch("leg1_isEERingGap", &leg1_isEERingGap);
    FlatTuple->Branch("leg1_deltaEtaSuperClusterTrackAtVtx", &leg1_deltaEtaSuperClusterTrackAtVtx);
    FlatTuple->Branch("leg1_deltaPhiSuperClusterTrackAtVtx", &leg1_deltaPhiSuperClusterTrackAtVtx);
    FlatTuple->Branch("leg1_sigmaEtaEta", &leg1_sigmaEtaEta);
    FlatTuple->Branch("leg1_sigmaIetaIeta", &leg1_sigmaIetaIeta);
    FlatTuple->Branch("leg1_sigmaIphiIphi", &leg1_sigmaIphiIphi);
    FlatTuple->Branch("leg1_numberOfMissingOuterHits", &leg1_numberOfMissingOuterHits);
    FlatTuple->Branch("leg1_numberOfTrackHits", &leg1_numberOfTrackHits);

  }


  //////////////////////////////
  /* leg2 info                */
  //////////////////////////////


  /* essentials */

  FlatTuple->Branch("leg2_leptonType", &leg2_leptonType);
  FlatTuple->Branch("leg2_pt", &leg2_pt);
  FlatTuple->Branch("leg2_eta", &leg2_eta);
  FlatTuple->Branch("leg2_phi", &leg2_phi);
  FlatTuple->Branch("leg2_M", &leg2_M);
  FlatTuple->Branch("leg2_RelIso",&leg2_RelIso);
  FlatTuple->Branch("leg2_dz", &leg2_dz);
  FlatTuple->Branch("leg2_dxy", &leg2_dxy);
  FlatTuple->Branch("leg2_charge", &leg2_charge);

  FlatTuple->Branch("leg2_raw_electronMVA", &leg2_raw_electronMVA);
  FlatTuple->Branch("leg2_category_electronMVA", &leg2_category_electronMVA);
  FlatTuple->Branch("leg2_passFail_electronMVA80", &leg2_passFail_electronMVA80);
  FlatTuple->Branch("leg2_passFail_electronMVA90", &leg2_passFail_electronMVA90);
  FlatTuple->Branch("leg2_passFail_VetoElectronCutBasedID", &leg2_passFail_VetoElectronCutBasedID);
  FlatTuple->Branch("leg2_passFail_TightElectronCutBasedID", &leg2_passFail_TightElectronCutBasedID);
  FlatTuple->Branch("leg2_SuperClusterEta", &leg2_SuperClusterEta);
  FlatTuple->Branch("leg2_numberOfMissingInnerHits", &leg2_numberOfMissingInnerHits);
  FlatTuple->Branch("leg2_passConversionVeto", &leg2_passConversionVeto);

  FlatTuple->Branch("leg2_ZimpactTau", &leg2_ZimpactTau);
  FlatTuple->Branch("leg2_numStrips", &leg2_numStrips);
  FlatTuple->Branch("leg2_dzTauVertex", &leg2_dzTauVertex);
  FlatTuple->Branch("leg2_numHadrons", &leg2_numHadrons);

  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1raw", &leg2_rerunDiscriminationByIsolationMVArun2v1raw);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1VLoose", &leg2_rerunDiscriminationByIsolationMVArun2v1VLoose);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1Loose", &leg2_rerunDiscriminationByIsolationMVArun2v1Loose);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1Medium", &leg2_rerunDiscriminationByIsolationMVArun2v1Medium);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1Tight", &leg2_rerunDiscriminationByIsolationMVArun2v1Tight);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1VTight", &leg2_rerunDiscriminationByIsolationMVArun2v1VTight);
  FlatTuple->Branch("leg2_rerunDiscriminationByIsolationMVArun2v1VVTight", &leg2_rerunDiscriminationByIsolationMVArun2v1VVTight);

  FlatTuple->Branch("leg2_decayMode", &leg2_decayMode);

  FlatTuple->Branch("leg2_isGlobalMuon", &leg2_isGlobalMuon);
  FlatTuple->Branch("leg2_isGoodGlobalMuon", &leg2_isGoodGlobalMuon);
  FlatTuple->Branch("leg2_passesLooseMuonId", &leg2_passesLooseMuonId);
  FlatTuple->Branch("leg2_passesMediumMuonId", &leg2_passesMediumMuonId);
  FlatTuple->Branch("leg2_passesMediumMuonId_ICHEP16", &leg2_passesMediumMuonId_ICHEP16);
  FlatTuple->Branch("leg2_passesMediumMuonId_Moriond17", &leg2_passesMediumMuonId_Moriond17);
  FlatTuple->Branch("leg2_passesTightMuonId", &leg2_passesTightMuonId);
  FlatTuple->Branch("leg2_isPFMuon", &leg2_isPFMuon);
  FlatTuple->Branch("leg2_isLooseMuon", &leg2_isLooseMuon);
  FlatTuple->Branch("leg2_isTightMuon", &leg2_isTightMuon);

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {
      FlatTuple->Branch(("leg2_"+tauIDsToKeep.at(x)).c_str(), &leg2_tauIDs[x]);
  }

  FlatTuple->Branch("leg2_MCMatchType", &leg2_MCMatchType);
  FlatTuple->Branch("leg2_genMCmatch_pt", &leg2_genMCmatch_pt);
  FlatTuple->Branch("leg2_genMCmatch_eta", &leg2_genMCmatch_eta);
  FlatTuple->Branch("leg2_genMCmatch_phi", &leg2_genMCmatch_phi);
  FlatTuple->Branch("leg2_genMCmatch_M", &leg2_genMCmatch_M);
  FlatTuple->Branch("leg2_MCMatchPdgId", &leg2_MCMatchPdgId);


  if( !SmallTree_ )
  {
    FlatTuple->Branch("leg2_gen_pt", &leg2_gen_pt);
    FlatTuple->Branch("leg2_gen_eta", &leg2_gen_eta);
    FlatTuple->Branch("leg2_gen_phi", &leg2_gen_phi);
    FlatTuple->Branch("leg2_gen_M", &leg2_gen_M);

    FlatTuple->Branch("leg2_genMother_pt", &leg2_genMother_pt);
    FlatTuple->Branch("leg2_genMother_eta", &leg2_genMother_eta);
    FlatTuple->Branch("leg2_genMother_phi", &leg2_genMother_phi);
    FlatTuple->Branch("leg2_genMother_M", &leg2_genMother_M);

    FlatTuple->Branch("leg2_genJet_pt", &leg2_genJet_pt);
    FlatTuple->Branch("leg2_genJet_eta", &leg2_genJet_eta);
    FlatTuple->Branch("leg2_genJet_phi", &leg2_genJet_phi);
    FlatTuple->Branch("leg2_genJet_M", &leg2_genJet_M);
    FlatTuple->Branch("leg2_genJet_pdgId", &leg2_genJet_pdgId);

    FlatTuple->Branch("leg2_EffectiveArea", &leg2_EffectiveArea);
    FlatTuple->Branch("leg2_PFpdgId", &leg2_PFpdgId);
    FlatTuple->Branch("leg2_GENpdgId", &leg2_GENpdgId);
    FlatTuple->Branch("leg2_GENMOTHERpdgId", &leg2_GENMOTHERpdgId);
    FlatTuple->Branch("leg2_IP", &leg2_IP);
    FlatTuple->Branch("leg2_IPerror", &leg2_IPerror);
    FlatTuple->Branch("leg2_PUchargedHadronIso", &leg2_PUchargedHadronIso);
    FlatTuple->Branch("leg2_chargedHadronIso", &leg2_chargedHadronIso);
    FlatTuple->Branch("leg2_neutralHadronIso", &leg2_neutralHadronIso);
    FlatTuple->Branch("leg2_photonIso", &leg2_photonIso);
    FlatTuple->Branch("leg2_DepositR03ECal", &leg2_DepositR03ECal);
    FlatTuple->Branch("leg2_DepositR03Hcal", &leg2_DepositR03Hcal);
    FlatTuple->Branch("leg2_DepositR03TrackerOfficial", &leg2_DepositR03TrackerOfficial);
    FlatTuple->Branch("leg2_isSoftMuon", &leg2_isSoftMuon);
    FlatTuple->Branch("leg2_isTrackerMuon", &leg2_isTrackerMuon);
    FlatTuple->Branch("leg2_muonCombQualChi2LocalPosition", &leg2_muonCombQualChi2LocalPosition);
    FlatTuple->Branch("leg2_muonCombQualTrkKink", &leg2_muonCombQualTrkKink);
    FlatTuple->Branch("leg2_muonGlobalTrackNormChi2", &leg2_muonGlobalTrackNormChi2);
    FlatTuple->Branch("leg2_muonInnerTrkValidFraction", &leg2_muonInnerTrkValidFraction);
    FlatTuple->Branch("leg2_muonSegmentCompatibility", &leg2_muonSegmentCompatibility);
    FlatTuple->Branch("leg2_ooEmooP", &leg2_ooEmooP);
    FlatTuple->Branch("leg2_full5x5_sigmaIetaIeta", &leg2_full5x5_sigmaIetaIeta);
    FlatTuple->Branch("leg2_hadronicOverEm", &leg2_hadronicOverEm);
    FlatTuple->Branch("leg2_isEB", &leg2_isEB);
    FlatTuple->Branch("leg2_isEBEEGap", &leg2_isEBEEGap);
    FlatTuple->Branch("leg2_isEBEtaGap", &leg2_isEBEtaGap);
    FlatTuple->Branch("leg2_isEBPhiGap", &leg2_isEBPhiGap);
    FlatTuple->Branch("leg2_isEE", &leg2_isEE);
    FlatTuple->Branch("leg2_isEEDeeGap", &leg2_isEEDeeGap);
    FlatTuple->Branch("leg2_isEERingGap", &leg2_isEERingGap);
    FlatTuple->Branch("leg2_deltaEtaSuperClusterTrackAtVtx", &leg2_deltaEtaSuperClusterTrackAtVtx);
    FlatTuple->Branch("leg2_deltaPhiSuperClusterTrackAtVtx", &leg2_deltaPhiSuperClusterTrackAtVtx);
    FlatTuple->Branch("leg2_sigmaEtaEta", &leg2_sigmaEtaEta);
    FlatTuple->Branch("leg2_sigmaIetaIeta", &leg2_sigmaIetaIeta);
    FlatTuple->Branch("leg2_sigmaIphiIphi", &leg2_sigmaIphiIphi);
    FlatTuple->Branch("leg2_numberOfMissingOuterHits", &leg2_numberOfMissingOuterHits);
    FlatTuple->Branch("leg2_numberOfTrackHits", &leg2_numberOfTrackHits);

  }


  //////////////////////////////
  /* event level filters      */
  //////////////////////////////


  FlatTuple->Branch("HBHENoiseFilter", &HBHENoiseFilter);
  FlatTuple->Branch("HBHENoiseIsoFilter", &HBHENoiseIsoFilter);
  FlatTuple->Branch("CSCTightHalo2015Filter", &CSCTightHalo2015Filter);
  FlatTuple->Branch("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
  FlatTuple->Branch("goodVerticesFilter", &goodVerticesFilter);
  FlatTuple->Branch("eeBadScFilter", &eeBadScFilter);
  FlatTuple->Branch("chargedHadronTrackResolutionFilter", &chargedHadronTrackResolutionFilter);
  FlatTuple->Branch("muonBadTrackFilter", &muonBadTrackFilter);
  FlatTuple->Branch("globalTightHalo2016Filter", &globalTightHalo2016Filter);
  FlatTuple->Branch("BadChargedCandidateFilter", &BadChargedCandidateFilter);
  FlatTuple->Branch("BadPFMuonFilter", &BadPFMuonFilter);

  FlatTuple->Branch("BadMuonTaggedMoriond17", &BadMuonTaggedMoriond17);
  FlatTuple->Branch("DuplicateMuonTaggedMoriond17", &DuplicateMuonTaggedMoriond17);



  FlatTuple->Branch("DiMuon_Flag", &DiMuon_Flag);
  FlatTuple->Branch("DiElectron_Flag", &DiElectron_Flag);
  FlatTuple->Branch("ThirdMuon_Flag", &ThirdMuon_Flag);
  FlatTuple->Branch("ThirdElectron_Flag", &ThirdElectron_Flag);

  //////////////////////////////////////
  /* the veto lepton collections      */
  //////////////////////////////////////
  // need to keep to allow us to do VH (Z->ll or W->lv) + H->tau tau

  // if( !SmallTree_ )
  // {  
    FlatTuple->Branch("veto_leptonType", &veto_leptonType);
    FlatTuple->Branch("veto_pt", &veto_pt);
    FlatTuple->Branch("veto_eta", &veto_eta);
    FlatTuple->Branch("veto_phi", &veto_phi);
    FlatTuple->Branch("veto_M", &veto_M);
    FlatTuple->Branch("veto_charge", &veto_charge);

    FlatTuple->Branch("veto_dxy", &veto_dxy);
    FlatTuple->Branch("veto_dz", &veto_dz);
    FlatTuple->Branch("veto_RelIso", &veto_RelIso);
    FlatTuple->Branch("veto_passesLooseMuonId", &veto_passesLooseMuonId);
    FlatTuple->Branch("veto_passesMediumMuonId_ICHEP16", &veto_passesMediumMuonId_ICHEP16);
    FlatTuple->Branch("veto_passesMediumMuonId_Moriond17", &veto_passesMediumMuonId_Moriond17);
    FlatTuple->Branch("veto_passesMediumMuonId", &veto_passesMediumMuonId);
    FlatTuple->Branch("veto_passesTightMuonId", &veto_passesTightMuonId);
    FlatTuple->Branch("veto_rawElectronMVA", &veto_rawElectronMVA);
    FlatTuple->Branch("veto_categoryElectronMVA", &veto_categoryElectronMVA);
    FlatTuple->Branch("veto_passElectronMVA80", &veto_passElectronMVA80);
    FlatTuple->Branch("veto_passElectronMVA90", &veto_passElectronMVA90);
    FlatTuple->Branch("veto_passVetoElectronCutBased", &veto_passVetoElectronCutBased);
    FlatTuple->Branch("veto_passTightElectronCutBased", &veto_passTightElectronCutBased);
    FlatTuple->Branch("veto_isTrackerGlobalPFMuon", &veto_isTrackerGlobalPFMuon);
    FlatTuple->Branch("veto_numberOfMissingInnerHits", &veto_numberOfMissingInnerHits);
    FlatTuple->Branch("veto_numberOfMissingOuterHits", &veto_numberOfMissingOuterHits);
    FlatTuple->Branch("veto_passConversionVeto", &veto_passConversionVeto);

    FlatTuple->Branch("veto_ZimpactTau", &veto_ZimpactTau);
    FlatTuple->Branch("veto_numStrips", &veto_numStrips);
    FlatTuple->Branch("veto_dzTauVertex", &veto_dzTauVertex);
    FlatTuple->Branch("veto_numHadrons", &veto_numHadrons);


    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1raw", &veto_rerunDiscriminationByIsolationMVArun2v1raw);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1VLoose", &veto_rerunDiscriminationByIsolationMVArun2v1VLoose);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1Loose", &veto_rerunDiscriminationByIsolationMVArun2v1Loose);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1Medium", &veto_rerunDiscriminationByIsolationMVArun2v1Medium);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1Tight", &veto_rerunDiscriminationByIsolationMVArun2v1Tight);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1VTight", &veto_rerunDiscriminationByIsolationMVArun2v1VTight);
    FlatTuple->Branch("veto_rerunDiscriminationByIsolationMVArun2v1VVTight", &veto_rerunDiscriminationByIsolationMVArun2v1VVTight);

    FlatTuple->Branch("veto_decayMode", &veto_decayMode);

    for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
    {
      FlatTuple->Branch(("veto_"+tauIDsToKeep.at(x)).c_str(), &veto_tauIDs.at(x).second);
    }

    FlatTuple->Branch("veto_LeptonPassesThirdElectronVetoCuts", &veto_LeptonPassesThirdElectronVetoCuts);
    FlatTuple->Branch("veto_LeptonPassesThirdMuonVetoCuts", &veto_LeptonPassesThirdMuonVetoCuts);
    FlatTuple->Branch("veto_LeptonPassesDiElectronVetoCuts", &veto_LeptonPassesDiElectronVetoCuts);
    FlatTuple->Branch("veto_LeptonPassesDiMuonVetoCuts", &veto_LeptonPassesDiMuonVetoCuts);
  // }


  //////////////////////////////////////
  /* essential gen level summary info */
  //////////////////////////////////////

  FlatTuple->Branch("generatorEventWeight",&generatorEventWeight);
  FlatTuple->Branch("hepNUP",&hepNUP);
  FlatTuple->Branch("lheHT",&lheHT);
  FlatTuple->Branch("lheOutGoingPartons",&lheOutGoingPartons);
  FlatTuple->Branch("lheZmass", &lheZmass);

  FlatTuple->Branch("IsZTT", &IsZTT);
  FlatTuple->Branch("IsZL", &IsZL);
  FlatTuple->Branch("IsZJ", &IsZJ);
  FlatTuple->Branch("IsZLL", &IsZLL);

  FlatTuple->Branch("genBosonTotal_pt", &genBosonTotal_pt); 
  FlatTuple->Branch("genBosonTotal_eta", &genBosonTotal_eta); 
  FlatTuple->Branch("genBosonTotal_phi", &genBosonTotal_phi); 
  FlatTuple->Branch("genBosonTotal_M", &genBosonTotal_M); 

  FlatTuple->Branch("genBosonVisible_pt", &genBosonVisible_pt); 
  FlatTuple->Branch("genBosonVisible_eta", &genBosonVisible_eta); 
  FlatTuple->Branch("genBosonVisible_phi", &genBosonVisible_phi); 
  FlatTuple->Branch("genBosonVisible_M", &genBosonVisible_M); 


  FlatTuple->Branch("MaxPtGenBoson_WisconinStyle_pt", &MaxPtGenBoson_WisconinStyle_pt); 
  FlatTuple->Branch("MaxPtGenBoson_WisconinStyle_eta", &MaxPtGenBoson_WisconinStyle_eta); 
  FlatTuple->Branch("MaxPtGenBoson_WisconinStyle_phi", &MaxPtGenBoson_WisconinStyle_phi); 
  FlatTuple->Branch("MaxPtGenBoson_WisconinStyle_M", &MaxPtGenBoson_WisconinStyle_M); 



  FlatTuple->Branch("isZTTatGenLevel", &isZTTatGenLevel);
  FlatTuple->Branch("isZEEatGenLevel", &isZEEatGenLevel);
  FlatTuple->Branch("isZMMatGenLevel", &isZMMatGenLevel);


  FlatTuple->Branch("genTopPt1",&genTopPt1);
  FlatTuple->Branch("genTopPt2",&genTopPt2);

  FlatTuple->Branch("originalXWGTUP",&originalXWGTUP);

  /* only keep theory scale factors in the nominal case */
  if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
  {
    FlatTuple->Branch("theory_scale_factors",&theory_scale_factors);
  }

  //////////////////////////////////////////
  /* non-essential gen level summary info */
  //////////////////////////////////////////

  if( !SmallTree_ || BuildEffTree_) /* keep for eff tree studies */
  {
    FlatTuple->Branch("genParticle_pdgId", &genParticle_pdgId);
    FlatTuple->Branch("genParticle_status", &genParticle_status);
    FlatTuple->Branch("genParticle_isPrompt", &genParticle_isPrompt);
    FlatTuple->Branch("genParticle_isPromptFinalState", &genParticle_isPromptFinalState);
    FlatTuple->Branch("genParticle_isDirectPromptTauDecayProduct", &genParticle_isDirectPromptTauDecayProduct);
    FlatTuple->Branch("genParticle_isDirectPromptTauDecayProductFinalState", &genParticle_isDirectPromptTauDecayProductFinalState);
    FlatTuple->Branch("genParticle_fromHardProcess", &genParticle_fromHardProcess);
    FlatTuple->Branch("genParticle_isLastCopy", &genParticle_isLastCopy);
    FlatTuple->Branch("genParticle_pt", &genParticle_pt);
    FlatTuple->Branch("genParticle_eta", &genParticle_eta);
    FlatTuple->Branch("genParticle_phi", &genParticle_phi);
    FlatTuple->Branch("genParticle_M", &genParticle_M);

    FlatTuple->Branch("genDaughter_pdgId", &genDaughter_pdgId);
    FlatTuple->Branch("genDaughter_status", &genDaughter_status);
    FlatTuple->Branch("genDaughter_pt", &genDaughter_pt);
    FlatTuple->Branch("genDaughter_eta", &genDaughter_eta);
    FlatTuple->Branch("genDaughter_phi", &genDaughter_phi);
    FlatTuple->Branch("genDaughter_M", &genDaughter_M);
   
    FlatTuple->Branch("genMother_pdgId", &genMother_pdgId);
    FlatTuple->Branch("genMother_status", &genMother_status);
    FlatTuple->Branch("genMother_pt", &genMother_pt);
    FlatTuple->Branch("genMother_eta", &genMother_eta);
    FlatTuple->Branch("genMother_phi", &genMother_phi);
    FlatTuple->Branch("genMother_M", &genMother_M);
  }





  //////////////////////////////////////////
  /* lepton efficiency info for studies   */
  //////////////////////////////////////////

  if( BuildEffTree_ )
  {
    for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
    {
      std::string versionStrippedName = triggerSummaryChecks.at(x);
      versionStrippedName.erase(versionStrippedName.find("_v"),versionStrippedName.length());
      FlatTuple->Branch(("effLep_"+versionStrippedName).c_str(), &effLep_GoodForHLTPath.at(x).second);    
    }

    for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
    {

      FlatTuple->Branch(("effLep_"+tauIDsToKeep.at(x)).c_str(), &effLep_tauIDs.at(x).second);
    }

    FlatTuple->Branch("effLep_MaxL1IsoTauMatch_pt", &effLep_MaxL1IsoTauMatch_pt);
    FlatTuple->Branch("effLep_MaxL1IsoTauMatch_eta", &effLep_MaxL1IsoTauMatch_eta);
    FlatTuple->Branch("effLep_MaxL1IsoTauMatch_phi", &effLep_MaxL1IsoTauMatch_phi);
    FlatTuple->Branch("effLep_leptonType", &effLep_leptonType);
    FlatTuple->Branch("effLep_pt", &effLep_pt);
    FlatTuple->Branch("effLep_eta", &effLep_eta);
    FlatTuple->Branch("effLep_phi", &effLep_phi);
    FlatTuple->Branch("effLep_M", &effLep_M);
    FlatTuple->Branch("effLep_gen_pt", &effLep_gen_pt);
    FlatTuple->Branch("effLep_gen_eta", &effLep_gen_eta);
    FlatTuple->Branch("effLep_gen_phi", &effLep_gen_phi);
    FlatTuple->Branch("effLep_gen_M", &effLep_gen_M);
    FlatTuple->Branch("effLep_genMother_pt", &effLep_genMother_pt);
    FlatTuple->Branch("effLep_genMother_eta", &effLep_genMother_eta);
    FlatTuple->Branch("effLep_genMother_phi", &effLep_genMother_phi);
    FlatTuple->Branch("effLep_genMother_M", &effLep_genMother_M);
    FlatTuple->Branch("effLep_genJet_pt", &effLep_genJet_pt);
    FlatTuple->Branch("effLep_genJet_eta", &effLep_genJet_eta);
    FlatTuple->Branch("effLep_genJet_phi", &effLep_genJet_phi);
    FlatTuple->Branch("effLep_genJet_M", &effLep_genJet_M);
    FlatTuple->Branch("effLep_dz", &effLep_dz);
    FlatTuple->Branch("effLep_dxy", &effLep_dxy);
    FlatTuple->Branch("effLep_EffectiveArea", &effLep_EffectiveArea);
    FlatTuple->Branch("effLep_charge", &effLep_charge);
    FlatTuple->Branch("effLep_PFpdgId", &effLep_PFpdgId);
    FlatTuple->Branch("effLep_GENpdgId", &effLep_GENpdgId);
    FlatTuple->Branch("effLep_GENMOTHERpdgId", &effLep_GENMOTHERpdgId);
    FlatTuple->Branch("effLep_IP", &effLep_IP);
    FlatTuple->Branch("effLep_IPerror", &effLep_IPerror);
    FlatTuple->Branch("effLep_PUchargedHadronIso", &effLep_PUchargedHadronIso);
    FlatTuple->Branch("effLep_chargedHadronIso", &effLep_chargedHadronIso);
    FlatTuple->Branch("effLep_neutralHadronIso", &effLep_neutralHadronIso);
    FlatTuple->Branch("effLep_photonIso", &effLep_photonIso);
    FlatTuple->Branch("effLep_DepositR03ECal", &effLep_DepositR03ECal);
    FlatTuple->Branch("effLep_DepositR03Hcal", &effLep_DepositR03Hcal);
    FlatTuple->Branch("effLep_DepositR03TrackerOfficial", &effLep_DepositR03TrackerOfficial);
    FlatTuple->Branch("effLep_isGlobalMuon", &effLep_isGlobalMuon);
    FlatTuple->Branch("effLep_isGoodGlobalMuon", &effLep_isGoodGlobalMuon);
    FlatTuple->Branch("effLep_passesLooseMuonId", &effLep_passesLooseMuonId);
    FlatTuple->Branch("effLep_passesMediumMuonId", &effLep_passesMediumMuonId);
    FlatTuple->Branch("effLep_passesMediumMuonId_ICHEP16", &effLep_passesMediumMuonId_ICHEP16);
    FlatTuple->Branch("effLep_passesMediumMuonId_Moriond17", &effLep_passesMediumMuonId_Moriond17);
    FlatTuple->Branch("effLep_passesTightMuonId", &effLep_passesTightMuonId);
    FlatTuple->Branch("effLep_isLooseMuon", &effLep_isLooseMuon);
    FlatTuple->Branch("effLep_isPFMuon", &effLep_isPFMuon);
    FlatTuple->Branch("effLep_isSoftMuon", &effLep_isSoftMuon);
    FlatTuple->Branch("effLep_isTightMuon", &effLep_isTightMuon);
    FlatTuple->Branch("effLep_isTrackerMuon", &effLep_isTrackerMuon);
    FlatTuple->Branch("effLep_muonCombQualChi2LocalPosition", &effLep_muonCombQualChi2LocalPosition);
    FlatTuple->Branch("effLep_muonCombQualTrkKink", &effLep_muonCombQualTrkKink);
    FlatTuple->Branch("effLep_muonGlobalTrackNormChi2", &effLep_muonGlobalTrackNormChi2);
    FlatTuple->Branch("effLep_muonInnerTrkValidFraction", &effLep_muonInnerTrkValidFraction);
    FlatTuple->Branch("effLep_muonSegmentCompatibility", &effLep_muonSegmentCompatibility);
    FlatTuple->Branch("effLep_raw_electronMVA", &effLep_raw_electronMVA);
    FlatTuple->Branch("effLep_category_electronMVA", &effLep_category_electronMVA);
    FlatTuple->Branch("effLep_passFail_electronMVA80", &effLep_passFail_electronMVA80);
    FlatTuple->Branch("effLep_passFail_electronMVA90", &effLep_passFail_electronMVA90);
    FlatTuple->Branch("effLep_passFail_VetoElectronCutBasedID", &effLep_passFail_VetoElectronCutBasedID);
    FlatTuple->Branch("effLep_passFail_TightElectronCutBasedID", &effLep_passFail_TightElectronCutBasedID);
    FlatTuple->Branch("effLep_ooEmooP", &effLep_ooEmooP);
    FlatTuple->Branch("effLep_full5x5_sigmaIetaIeta", &effLep_full5x5_sigmaIetaIeta);
    FlatTuple->Branch("effLep_SuperClusterEta", &effLep_SuperClusterEta);
    FlatTuple->Branch("effLep_hadronicOverEm", &effLep_hadronicOverEm);
    FlatTuple->Branch("effLep_isEB", &effLep_isEB);
    FlatTuple->Branch("effLep_isEBEEGap", &effLep_isEBEEGap);
    FlatTuple->Branch("effLep_isEBEtaGap", &effLep_isEBEtaGap);
    FlatTuple->Branch("effLep_isEBPhiGap", &effLep_isEBPhiGap);
    FlatTuple->Branch("effLep_isEE", &effLep_isEE);
    FlatTuple->Branch("effLep_isEEDeeGap", &effLep_isEEDeeGap);
    FlatTuple->Branch("effLep_isEERingGap", &effLep_isEERingGap);
    FlatTuple->Branch("effLep_deltaEtaSuperClusterTrackAtVtx", &effLep_deltaEtaSuperClusterTrackAtVtx);
    FlatTuple->Branch("effLep_deltaPhiSuperClusterTrackAtVtx", &effLep_deltaPhiSuperClusterTrackAtVtx);
    FlatTuple->Branch("effLep_sigmaEtaEta", &effLep_sigmaEtaEta);
    FlatTuple->Branch("effLep_sigmaIetaIeta", &effLep_sigmaIetaIeta);
    FlatTuple->Branch("effLep_sigmaIphiIphi", &effLep_sigmaIphiIphi);
    FlatTuple->Branch("effLep_numberOfMissingInnerHits", &effLep_numberOfMissingInnerHits);
    FlatTuple->Branch("effLep_numberOfMissingOuterHits", &effLep_numberOfMissingOuterHits);
    FlatTuple->Branch("effLep_numberOfTrackHits", &effLep_numberOfTrackHits);
    FlatTuple->Branch("effLep_passConversionVeto", &effLep_passConversionVeto);
    FlatTuple->Branch("effLep_ZimpactTau", &effLep_ZimpactTau);
    FlatTuple->Branch("effLep_numStrips", &effLep_numStrips);
    FlatTuple->Branch("effLep_dzTauVertex", &effLep_dzTauVertex);
    FlatTuple->Branch("effLep_numHadrons", &effLep_numHadrons);
    
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1raw", &effLep_rerunDiscriminationByIsolationMVArun2v1raw);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1VLoose", &effLep_rerunDiscriminationByIsolationMVArun2v1VLoose);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1Loose", &effLep_rerunDiscriminationByIsolationMVArun2v1Loose);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1Medium", &effLep_rerunDiscriminationByIsolationMVArun2v1Medium);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1Tight", &effLep_rerunDiscriminationByIsolationMVArun2v1Tight);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1VTight", &effLep_rerunDiscriminationByIsolationMVArun2v1VTight);
    FlatTuple->Branch("effLep_rerunDiscriminationByIsolationMVArun2v1VVTight", &effLep_rerunDiscriminationByIsolationMVArun2v1VVTight);

    FlatTuple->Branch("effLep_decayMode", &effLep_decayMode);
    FlatTuple->Branch("effLep_RelIso", &effLep_RelIso);
    FlatTuple->Branch("effLep_genJet_pdgId", &effLep_genJet_pdgId); 
    FlatTuple->Branch("effLep_MCMatchType", &effLep_MCMatchType);
    FlatTuple->Branch("effLep_genMCmatch_pt", &effLep_genMCmatch_pt);
    FlatTuple->Branch("effLep_genMCmatch_eta", &effLep_genMCmatch_eta);
    FlatTuple->Branch("effLep_genMCmatch_phi", &effLep_genMCmatch_phi);
    FlatTuple->Branch("effLep_genMCmatch_M", &effLep_genMCmatch_M);
    FlatTuple->Branch("effLep_MCMatchPdgId", &effLep_MCMatchPdgId);
    FlatTuple->Branch("effLep_maxPtTrigObjMatch", &effLep_maxPtTrigObjMatch);

  }


  ///////////////////////////////////////////
  /* jet info                               */
  ///////////////////////////////////////////

  /* always keep a list of fully corrected jets */

  FlatTuple->Branch("numberOfJets", &numberOfJets);
  FlatTuple->Branch("numberOfJets30", &numberOfJets30);
  FlatTuple->Branch("jets_pt", &jets_pt);
  FlatTuple->Branch("jets_eta", &jets_eta);
  FlatTuple->Branch("jets_phi", &jets_phi);
  FlatTuple->Branch("jets_M", &jets_M);  
  FlatTuple->Branch("jets_PU_jetIdRaw", &jets_PU_jetIdRaw);
  FlatTuple->Branch("jets_PU_jetIdPassed", &jets_PU_jetIdPassed);
  FlatTuple->Branch("jets_PF_jetIdPassed", &jets_PF_jetIdPassed);
  FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore", &jets_defaultBtagAlgorithm_RawScore);
  FlatTuple->Branch("jets_PARTON_flavour", &jets_PARTON_flavour);
  FlatTuple->Branch("jets_HADRON_flavour", &jets_HADRON_flavour);
  FlatTuple->Branch("jets_IsBTagged_LooseWpCentral", &jets_IsBTagged_LooseWpCentral);
  FlatTuple->Branch("jets_IsBTagged_MediumWpCentral", &jets_IsBTagged_MediumWpCentral);
  FlatTuple->Branch("jets_IsBTagged_TightWpCentral", &jets_IsBTagged_TightWpCentral);
  FlatTuple->Branch("jets_PF_jetIdPassedTight", &jets_PF_jetIdPassedTight);

  /* the wisconsin style zero btag event weights */

  FlatTuple->Branch("jets_zero_btag_event_weight", &jets_zero_btag_event_weight);
  FlatTuple->Branch("jets_zero_btag_event_weight_up", &jets_zero_btag_event_weight_up);
  FlatTuple->Branch("jets_zero_btag_event_weight_down", &jets_zero_btag_event_weight_down);
 
  FlatTuple->Branch("jets_JECshiftedUp_zero_btag_event_weight", &jets_JECshiftedUp_zero_btag_event_weight);
  FlatTuple->Branch("jets_JECshiftedDown_zero_btag_event_weight", &jets_JECshiftedDown_zero_btag_event_weight);
  FlatTuple->Branch("jets_JERup_zero_btag_event_weight", &jets_JERup_zero_btag_event_weight);
  FlatTuple->Branch("jets_JERdown_zero_btag_event_weight", &jets_JERdown_zero_btag_event_weight);



  FlatTuple->Branch("jets_zero_btag_event_weight_LOOSE", &jets_zero_btag_event_weight_LOOSE);
  FlatTuple->Branch("jets_zero_btag_event_weight_LOOSE_up", &jets_zero_btag_event_weight_LOOSE_up);
  FlatTuple->Branch("jets_zero_btag_event_weight_LOOSE_down", &jets_zero_btag_event_weight_LOOSE_down);
 
  FlatTuple->Branch("jets_JECshiftedUp_zero_btag_event_weight_LOOSE", &jets_JECshiftedUp_zero_btag_event_weight_LOOSE);
  FlatTuple->Branch("jets_JECshiftedDown_zero_btag_event_weight_LOOSE", &jets_JECshiftedDown_zero_btag_event_weight_LOOSE);
  FlatTuple->Branch("jets_JERup_zero_btag_event_weight_LOOSE", &jets_JERup_zero_btag_event_weight_LOOSE);
  FlatTuple->Branch("jets_JERdown_zero_btag_event_weight_LOOSE", &jets_JERdown_zero_btag_event_weight_LOOSE);




  /* the new mono_H style btag SFs */
  FlatTuple->Branch("BtagEventSFproduct_looseWpDown",  &BtagEventSFproduct_looseWpDown);
  FlatTuple->Branch("BtagEventSFproduct_looseWpCentral",  &BtagEventSFproduct_looseWpCentral);
  FlatTuple->Branch("BtagEventSFproduct_looseWpUp",  &BtagEventSFproduct_looseWpUp);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpDown",  &BtagEventSFproduct_mediumWpDown);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpCentral",  &BtagEventSFproduct_mediumWpCentral);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpUp",  &BtagEventSFproduct_mediumWpUp);
  FlatTuple->Branch("BtagEventSFproduct_tightWpDown",  &BtagEventSFproduct_tightWpDown);
  FlatTuple->Branch("BtagEventSFproduct_tightWpCentral",  &BtagEventSFproduct_tightWpCentral);
  FlatTuple->Branch("BtagEventSFproduct_tightWpUp",  &BtagEventSFproduct_tightWpUp);

  FlatTuple->Branch("BtagEventSFproduct_looseWpCentral_JECshiftedUp",  &BtagEventSFproduct_looseWpCentral_JECshiftedUp);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpCentral_JECshiftedUp",  &BtagEventSFproduct_mediumWpCentral_JECshiftedUp);
  FlatTuple->Branch("BtagEventSFproduct_tightWpCentral_JECshiftedUp",  &BtagEventSFproduct_tightWpCentral_JECshiftedUp);
  FlatTuple->Branch("BtagEventSFproduct_looseWpCentral_JECshiftedDown",  &BtagEventSFproduct_looseWpCentral_JECshiftedDown);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpCentral_JECshiftedDown",  &BtagEventSFproduct_mediumWpCentral_JECshiftedDown);
  FlatTuple->Branch("BtagEventSFproduct_tightWpCentral_JECshiftedDown",  &BtagEventSFproduct_tightWpCentral_JECshiftedDown);
  FlatTuple->Branch("BtagEventSFproduct_looseWpCentral_JERup",  &BtagEventSFproduct_looseWpCentral_JERup);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpCentral_JERup",  &BtagEventSFproduct_mediumWpCentral_JERup);
  FlatTuple->Branch("BtagEventSFproduct_tightWpCentral_JERup",  &BtagEventSFproduct_tightWpCentral_JERup);
  FlatTuple->Branch("BtagEventSFproduct_looseWpCentral_JERdown",  &BtagEventSFproduct_looseWpCentral_JERdown);
  FlatTuple->Branch("BtagEventSFproduct_mediumWpCentral_JERdown",  &BtagEventSFproduct_mediumWpCentral_JERdown);
  FlatTuple->Branch("BtagEventSFproduct_tightWpCentral_JERdown",  &BtagEventSFproduct_tightWpCentral_JERdown);





  /* only keep b-tag shifts in nominal case */
  if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
  {
    FlatTuple->Branch("jets_IsBTagged_LooseWpUp", &jets_IsBTagged_LooseWpUp);
    FlatTuple->Branch("jets_IsBTagged_LooseWpDown", &jets_IsBTagged_LooseWpDown);
    FlatTuple->Branch("jets_IsBTagged_MediumWpUp", &jets_IsBTagged_MediumWpUp);
    FlatTuple->Branch("jets_IsBTagged_MediumWpDown", &jets_IsBTagged_MediumWpDown);
    FlatTuple->Branch("jets_IsBTagged_TightWpUp", &jets_IsBTagged_TightWpUp);
    FlatTuple->Branch("jets_IsBTagged_TightWpDown", &jets_IsBTagged_TightWpDown);

  }

  /* only keep alternate jet lists in the nominal tau and electron ES case */
  /* also since all jets kept pass pf jet id, we don't retain this info for
     varied jet lists -- in 8X may need to modify this for PU + PF id */

  if(TauEsVariantToKeep_=="NOMINAL" && ElectronEsVariantToKeep_=="NOMINAL" )
  {

    /* scale (response) up jet info */

    FlatTuple->Branch("jets_pt_JECshiftedUp", &jets_pt_JECshiftedUp);
    FlatTuple->Branch("jets_eta_JECshiftedUp", &jets_eta_JECshiftedUp);
    FlatTuple->Branch("jets_phi_JECshiftedUp", &jets_phi_JECshiftedUp);
    FlatTuple->Branch("jets_M_JECshiftedUp", &jets_M_JECshiftedUp);
    FlatTuple->Branch("jets_IsBTagged_LooseWpCentral_JECshiftedUp", &jets_IsBTagged_LooseWpCentral_JECshiftedUp);
    FlatTuple->Branch("jets_IsBTagged_MediumWpCentral_JECshiftedUp", &jets_IsBTagged_MediumWpCentral_JECshiftedUp);
    FlatTuple->Branch("jets_IsBTagged_TightWpCentral_JECshiftedUp", &jets_IsBTagged_TightWpCentral_JECshiftedUp);
    
    if( !SmallTree_ ) 
    {
      FlatTuple->Branch("numberOfJets_JECshiftedUp", &numberOfJets_JECshiftedUp);
      FlatTuple->Branch("numberOfJets30_JECshiftedUp", &numberOfJets30_JECshiftedUp);
      FlatTuple->Branch("jets_PU_jetIdRaw_JECshiftedUp", &jets_PU_jetIdRaw_JECshiftedUp);
      FlatTuple->Branch("jets_PU_jetIdPassed_JECshiftedUp", &jets_PU_jetIdPassed_JECshiftedUp);
      FlatTuple->Branch("jets_PF_jetIdPassed_JECshiftedUp", &jets_PF_jetIdPassed_JECshiftedUp);
      FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore_JECshiftedUp", &jets_defaultBtagAlgorithm_RawScore_JECshiftedUp);
      FlatTuple->Branch("jets_PARTON_flavour_JECshiftedUp", &jets_PARTON_flavour_JECshiftedUp);
      FlatTuple->Branch("jets_HADRON_flavour_JECshiftedUp", &jets_HADRON_flavour_JECshiftedUp);
      FlatTuple->Branch("jets_PF_jetIdPassedTight_JECshiftedUp", &jets_PF_jetIdPassedTight_JECshiftedUp);
    }

    /* scale (response) down jet info */
   

    FlatTuple->Branch("jets_pt_JECshiftedDown", &jets_pt_JECshiftedDown);
    FlatTuple->Branch("jets_eta_JECshiftedDown", &jets_eta_JECshiftedDown);
    FlatTuple->Branch("jets_phi_JECshiftedDown", &jets_phi_JECshiftedDown);
    FlatTuple->Branch("jets_M_JECshiftedDown", &jets_M_JECshiftedDown);
    FlatTuple->Branch("jets_IsBTagged_LooseWpCentral_JECshiftedDown", &jets_IsBTagged_LooseWpCentral_JECshiftedDown);
    FlatTuple->Branch("jets_IsBTagged_MediumWpCentral_JECshiftedDown", &jets_IsBTagged_MediumWpCentral_JECshiftedDown);
    FlatTuple->Branch("jets_IsBTagged_TightWpCentral_JECshiftedDown", &jets_IsBTagged_TightWpCentral_JECshiftedDown);

    if( !SmallTree_ ) 
    {
      FlatTuple->Branch("numberOfJets_JECshiftedDown", &numberOfJets_JECshiftedDown);
      FlatTuple->Branch("numberOfJets30_JECshiftedDown", &numberOfJets30_JECshiftedDown);
      FlatTuple->Branch("jets_PU_jetIdRaw_JECshiftedDown", &jets_PU_jetIdRaw_JECshiftedDown);
      FlatTuple->Branch("jets_PU_jetIdPassed_JECshiftedDown", &jets_PU_jetIdPassed_JECshiftedDown);
      FlatTuple->Branch("jets_PF_jetIdPassed_JECshiftedDown", &jets_PF_jetIdPassed_JECshiftedDown);
      FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore_JECshiftedDown", &jets_defaultBtagAlgorithm_RawScore_JECshiftedDown);
      FlatTuple->Branch("jets_PARTON_flavour_JECshiftedDown", &jets_PARTON_flavour_JECshiftedDown);
      FlatTuple->Branch("jets_HADRON_flavour_JECshiftedDown", &jets_HADRON_flavour_JECshiftedDown);
      FlatTuple->Branch("jets_PF_jetIdPassedTight_JECshiftedDown", &jets_PF_jetIdPassedTight_JECshiftedDown);
    }

    /* resolution up jet info */  
    

    FlatTuple->Branch("jets_pt_JERup", &jets_pt_JERup);
    FlatTuple->Branch("jets_eta_JERup", &jets_eta_JERup);
    FlatTuple->Branch("jets_phi_JERup", &jets_phi_JERup);
    FlatTuple->Branch("jets_M_JERup", &jets_M_JERup);
    FlatTuple->Branch("jets_IsBTagged_LooseWpCentral_JERup", &jets_IsBTagged_LooseWpCentral_JERup);
    FlatTuple->Branch("jets_IsBTagged_MediumWpCentral_JERup", &jets_IsBTagged_MediumWpCentral_JERup);
    FlatTuple->Branch("jets_IsBTagged_TightWpCentral_JERup", &jets_IsBTagged_TightWpCentral_JERup);

    if( !SmallTree_ ) 
    {
      FlatTuple->Branch("numberOfJets_JERup", &numberOfJets_JERup);
      FlatTuple->Branch("numberOfJets30_JERup", &numberOfJets30_JERup);
      FlatTuple->Branch("jets_PU_jetIdRaw_JERup", &jets_PU_jetIdRaw_JERup);
      FlatTuple->Branch("jets_PU_jetIdPassed_JERup", &jets_PU_jetIdPassed_JERup);
      FlatTuple->Branch("jets_PF_jetIdPassed_JERup", &jets_PF_jetIdPassed_JERup);
      FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore_JERup", &jets_defaultBtagAlgorithm_RawScore_JERup);
      FlatTuple->Branch("jets_PARTON_flavour_JERup", &jets_PARTON_flavour_JERup);
      FlatTuple->Branch("jets_HADRON_flavour_JERup", &jets_HADRON_flavour_JERup);
      FlatTuple->Branch("jets_PF_jetIdPassedTight_JERup", &jets_PF_jetIdPassedTight_JERup);
    }


    /* resolution down jet info */
   

    FlatTuple->Branch("jets_pt_JERdown", &jets_pt_JERdown);
    FlatTuple->Branch("jets_eta_JERdown", &jets_eta_JERdown);
    FlatTuple->Branch("jets_phi_JERdown", &jets_phi_JERdown);
    FlatTuple->Branch("jets_M_JERdown", &jets_M_JERdown);
    FlatTuple->Branch("jets_IsBTagged_LooseWpCentral_JERdown", &jets_IsBTagged_LooseWpCentral_JERdown);
    FlatTuple->Branch("jets_IsBTagged_MediumWpCentral_JERdown", &jets_IsBTagged_MediumWpCentral_JERdown);
    FlatTuple->Branch("jets_IsBTagged_TightWpCentral_JERdown", &jets_IsBTagged_TightWpCentral_JERdown);

    if( !SmallTree_ ) 
    {
      FlatTuple->Branch("numberOfJets_JERdown", &numberOfJets_JERdown);
      FlatTuple->Branch("numberOfJets30_JERdown", &numberOfJets30_JERdown);
      FlatTuple->Branch("jets_PU_jetIdRaw_JERdown", &jets_PU_jetIdRaw_JERdown);
      FlatTuple->Branch("jets_PU_jetIdPassed_JERdown", &jets_PU_jetIdPassed_JERdown);
      FlatTuple->Branch("jets_PF_jetIdPassed_JERdown", &jets_PF_jetIdPassed_JERdown);
      FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore_JERdown", &jets_defaultBtagAlgorithm_RawScore_JERdown);
      FlatTuple->Branch("jets_PARTON_flavour_JERdown", &jets_PARTON_flavour_JERdown);
      FlatTuple->Branch("jets_HADRON_flavour_JERdown", &jets_HADRON_flavour_JERdown);
      FlatTuple->Branch("jets_PF_jetIdPassedTight_JERdown", &jets_PF_jetIdPassedTight_JERdown);
    }


    /* shifts of the b-tagging on top of shifts to the JEC or JER are not needed */
    // FlatTuple->Branch("jets_IsBTagged_LooseWpUp_JECshiftedUp", &jets_IsBTagged_LooseWpUp_JECshiftedUp);
    // FlatTuple->Branch("jets_IsBTagged_LooseWpDown_JECshiftedUp", &jets_IsBTagged_LooseWpDown_JECshiftedUp);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpUp_JECshiftedUp", &jets_IsBTagged_MediumWpUp_JECshiftedUp);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpDown_JECshiftedUp", &jets_IsBTagged_MediumWpDown_JECshiftedUp);
    // FlatTuple->Branch("jets_IsBTagged_TightWpUp_JECshiftedUp", &jets_IsBTagged_TightWpUp_JECshiftedUp);
    // FlatTuple->Branch("jets_IsBTagged_TightWpDown_JECshiftedUp", &jets_IsBTagged_TightWpDown_JECshiftedUp);
    
    // FlatTuple->Branch("jets_IsBTagged_LooseWpUp_JECshiftedDown", &jets_IsBTagged_LooseWpUp_JECshiftedDown);
    // FlatTuple->Branch("jets_IsBTagged_LooseWpDown_JECshiftedDown", &jets_IsBTagged_LooseWpDown_JECshiftedDown);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpUp_JECshiftedDown", &jets_IsBTagged_MediumWpUp_JECshiftedDown);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpDown_JECshiftedDown", &jets_IsBTagged_MediumWpDown_JECshiftedDown);
    // FlatTuple->Branch("jets_IsBTagged_TightWpUp_JECshiftedDown", &jets_IsBTagged_TightWpUp_JECshiftedDown);
    // FlatTuple->Branch("jets_IsBTagged_TightWpDown_JECshiftedDown", &jets_IsBTagged_TightWpDown_JECshiftedDown);
   
    // FlatTuple->Branch("jets_IsBTagged_LooseWpUp_JERup", &jets_IsBTagged_LooseWpUp_JERup);
    // FlatTuple->Branch("jets_IsBTagged_LooseWpDown_JERup", &jets_IsBTagged_LooseWpDown_JERup);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpUp_JERup", &jets_IsBTagged_MediumWpUp_JERup);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpDown_JERup", &jets_IsBTagged_MediumWpDown_JERup);
    // FlatTuple->Branch("jets_IsBTagged_TightWpUp_JERup", &jets_IsBTagged_TightWpUp_JERup);
    // FlatTuple->Branch("jets_IsBTagged_TightWpDown_JERup", &jets_IsBTagged_TightWpDown_JERup);
    
    // FlatTuple->Branch("jets_IsBTagged_LooseWpUp_JERdown", &jets_IsBTagged_LooseWpUp_JERdown);
    // FlatTuple->Branch("jets_IsBTagged_LooseWpDown_JERdown", &jets_IsBTagged_LooseWpDown_JERdown);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpUp_JERdown", &jets_IsBTagged_MediumWpUp_JERdown);
    // FlatTuple->Branch("jets_IsBTagged_MediumWpDown_JERdown", &jets_IsBTagged_MediumWpDown_JERdown);
    // FlatTuple->Branch("jets_IsBTagged_TightWpUp_JERdown", &jets_IsBTagged_TightWpUp_JERdown);
    // FlatTuple->Branch("jets_IsBTagged_TightWpDown_JERdown", &jets_IsBTagged_TightWpDown_JERdown);

  }


  if( !SmallTree_ )
  { 

    FlatTuple->Branch("numberOfJetsForRecoilCorr",&numberOfJetsForRecoilCorr);
    FlatTuple->Branch("jets_BtagSF_LooseWpCentral", &jets_BtagSF_LooseWpCentral);
    FlatTuple->Branch("jets_BtagSF_LooseWpUp", &jets_BtagSF_LooseWpUp);
    FlatTuple->Branch("jets_BtagSF_LooseWpDown", &jets_BtagSF_LooseWpDown);
    FlatTuple->Branch("jets_BtagSF_MediumWpCentral", &jets_BtagSF_MediumWpCentral);
    FlatTuple->Branch("jets_BtagSF_MediumWpUp", &jets_BtagSF_MediumWpUp);
    FlatTuple->Branch("jets_BtagSF_MediumWpDown", &jets_BtagSF_MediumWpDown);
    FlatTuple->Branch("jets_BtagSF_TightWpCentral", &jets_BtagSF_TightWpCentral);
    FlatTuple->Branch("jets_BtagSF_TightWpUp", &jets_BtagSF_TightWpUp);
    FlatTuple->Branch("jets_BtagSF_TightWpDown", &jets_BtagSF_TightWpDown);
    FlatTuple->Branch("jets_BtagEff_LooseWp", &jets_BtagEff_LooseWp);
    FlatTuple->Branch("jets_BtagEff_MediumWp", &jets_BtagEff_MediumWp);
    FlatTuple->Branch("jets_BtagEff_TightWp", &jets_BtagEff_TightWp);
   
    FlatTuple->Branch("jets_BtagSF_LooseWpCentral_JECshiftedUp", &jets_BtagSF_LooseWpCentral_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_LooseWpUp_JECshiftedUp", &jets_BtagSF_LooseWpUp_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_LooseWpDown_JECshiftedUp", &jets_BtagSF_LooseWpDown_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_MediumWpCentral_JECshiftedUp", &jets_BtagSF_MediumWpCentral_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_MediumWpUp_JECshiftedUp", &jets_BtagSF_MediumWpUp_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_MediumWpDown_JECshiftedUp", &jets_BtagSF_MediumWpDown_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_TightWpCentral_JECshiftedUp", &jets_BtagSF_TightWpCentral_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_TightWpUp_JECshiftedUp", &jets_BtagSF_TightWpUp_JECshiftedUp);
    FlatTuple->Branch("jets_BtagSF_TightWpDown_JECshiftedUp", &jets_BtagSF_TightWpDown_JECshiftedUp);
    FlatTuple->Branch("jets_BtagEff_LooseWp_JECshiftedUp", &jets_BtagEff_LooseWp_JECshiftedUp);
    FlatTuple->Branch("jets_BtagEff_MediumWp_JECshiftedUp", &jets_BtagEff_MediumWp_JECshiftedUp);
    FlatTuple->Branch("jets_BtagEff_TightWp_JECshiftedUp", &jets_BtagEff_TightWp_JECshiftedUp);

    FlatTuple->Branch("jets_BtagSF_LooseWpCentral_JECshiftedDown", &jets_BtagSF_LooseWpCentral_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_LooseWpUp_JECshiftedDown", &jets_BtagSF_LooseWpUp_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_LooseWpDown_JECshiftedDown", &jets_BtagSF_LooseWpDown_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_MediumWpCentral_JECshiftedDown", &jets_BtagSF_MediumWpCentral_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_MediumWpUp_JECshiftedDown", &jets_BtagSF_MediumWpUp_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_MediumWpDown_JECshiftedDown", &jets_BtagSF_MediumWpDown_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_TightWpCentral_JECshiftedDown", &jets_BtagSF_TightWpCentral_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_TightWpUp_JECshiftedDown", &jets_BtagSF_TightWpUp_JECshiftedDown);
    FlatTuple->Branch("jets_BtagSF_TightWpDown_JECshiftedDown", &jets_BtagSF_TightWpDown_JECshiftedDown);
    FlatTuple->Branch("jets_BtagEff_LooseWp_JECshiftedDown", &jets_BtagEff_LooseWp_JECshiftedDown);
    FlatTuple->Branch("jets_BtagEff_MediumWp_JECshiftedDown", &jets_BtagEff_MediumWp_JECshiftedDown);
    FlatTuple->Branch("jets_BtagEff_TightWp_JECshiftedDown", &jets_BtagEff_TightWp_JECshiftedDown);


    FlatTuple->Branch("jets_BtagSF_LooseWpCentral_JERup", &jets_BtagSF_LooseWpCentral_JERup);
    FlatTuple->Branch("jets_BtagSF_LooseWpUp_JERup", &jets_BtagSF_LooseWpUp_JERup);
    FlatTuple->Branch("jets_BtagSF_LooseWpDown_JERup", &jets_BtagSF_LooseWpDown_JERup);
    FlatTuple->Branch("jets_BtagSF_MediumWpCentral_JERup", &jets_BtagSF_MediumWpCentral_JERup);
    FlatTuple->Branch("jets_BtagSF_MediumWpUp_JERup", &jets_BtagSF_MediumWpUp_JERup);
    FlatTuple->Branch("jets_BtagSF_MediumWpDown_JERup", &jets_BtagSF_MediumWpDown_JERup);
    FlatTuple->Branch("jets_BtagSF_TightWpCentral_JERup", &jets_BtagSF_TightWpCentral_JERup);
    FlatTuple->Branch("jets_BtagSF_TightWpUp_JERup", &jets_BtagSF_TightWpUp_JERup);
    FlatTuple->Branch("jets_BtagSF_TightWpDown_JERup", &jets_BtagSF_TightWpDown_JERup);
    FlatTuple->Branch("jets_BtagEff_LooseWp_JERup", &jets_BtagEff_LooseWp_JERup);
    FlatTuple->Branch("jets_BtagEff_MediumWp_JERup", &jets_BtagEff_MediumWp_JERup);
    FlatTuple->Branch("jets_BtagEff_TightWp_JERup", &jets_BtagEff_TightWp_JERup);



    FlatTuple->Branch("jets_BtagSF_LooseWpCentral_JERdown", &jets_BtagSF_LooseWpCentral_JERdown);
    FlatTuple->Branch("jets_BtagSF_LooseWpUp_JERdown", &jets_BtagSF_LooseWpUp_JERdown);
    FlatTuple->Branch("jets_BtagSF_LooseWpDown_JERdown", &jets_BtagSF_LooseWpDown_JERdown);
    FlatTuple->Branch("jets_BtagSF_MediumWpCentral_JERdown", &jets_BtagSF_MediumWpCentral_JERdown);
    FlatTuple->Branch("jets_BtagSF_MediumWpUp_JERdown", &jets_BtagSF_MediumWpUp_JERdown);
    FlatTuple->Branch("jets_BtagSF_MediumWpDown_JERdown", &jets_BtagSF_MediumWpDown_JERdown);
    FlatTuple->Branch("jets_BtagSF_TightWpCentral_JERdown", &jets_BtagSF_TightWpCentral_JERdown);
    FlatTuple->Branch("jets_BtagSF_TightWpUp_JERdown", &jets_BtagSF_TightWpUp_JERdown);
    FlatTuple->Branch("jets_BtagSF_TightWpDown_JERdown", &jets_BtagSF_TightWpDown_JERdown);
    FlatTuple->Branch("jets_BtagEff_LooseWp_JERdown", &jets_BtagEff_LooseWp_JERdown);
    FlatTuple->Branch("jets_BtagEff_MediumWp_JERdown", &jets_BtagEff_MediumWp_JERdown);
    FlatTuple->Branch("jets_BtagEff_TightWp_JERdown", &jets_BtagEff_TightWp_JERdown);

  }




}


/* for exotica group type PF met systematics */
/* the doubles are set to met pt, phi, mt1 and mt2 using the uncertainty and corr. specified */
void FlatTupleGenerator::GetPFMetVariant(NtupleEvent EVE, pat::MET::METUncertainty UNC, pat::MET::METCorrectionLevel LEV, 
                                        double & PT, double & PHI, double & MT1, double & MT2) 
{

  /* sometimes PF MET is NAN, want to set everything to 0 in this case */

  if(std::isnan(EVE.pfMET()[0].pt()))
  {
    PT = 0.0; 
    PHI = 0.0;
    MT1 = 0.0;
    MT2 = 0.0;
    return;

  } 

  PT = EVE.pfMET()[0].shiftedPt(UNC,LEV); 
  PHI = EVE.pfMET()[0].shiftedPhi(UNC,LEV); 

  TLorentzVector pfmet_local(0.,0.,0.,0.);
  pfmet_local.SetPtEtaPhiM(PT, 0.0, PHI, 0.0);

  MT1 = GetTransverseMass(EVE.leg1().p4() , pfmet_local); 
  MT2 = GetTransverseMass(EVE.leg2().p4() , pfmet_local); 
  return;
} 




double FlatTupleGenerator::GetTransverseMass(LorentzVector L, TLorentzVector T)
{
  double pTxMET = sqrt(L.x()*L.x()+L.y()*L.y())*sqrt(T.X()*T.X()+T.Y()*T.Y());
  double CosDphi = cos(deltaPhi(L.phi(), T.Phi()));
  double MtSq = (2 * pTxMET*(1-CosDphi));
  return sqrt(MtSq);

}



/* conditionally concatenate arg1 (std::vector<NtupleEvent>) and arg2 (std::vector<NtupleEvent>) 
   into arg3 (std::vector<NtupleEvent>)

if arg1 is populated arg2 will not be added into arg3

- in the usual usage arg1 = resoved, arg2 = boosted, arg3 = retained pairs

- since we prefer resolved pairs, boosted pairs are only added into arg3 if no resolved pairs are found  
*/    


void FlatTupleGenerator::concatenateVectors(std::vector<NtupleEvent> RESOLVED, std::vector<NtupleEvent> BOOSTED, 
                                            std::vector<NtupleEvent> & RETAINED)
{

  /* if no resolved pairs take boosted ones */
 
  if(RESOLVED.size() == 0)
  {  
    for(std::size_t v = 0; v<BOOSTED.size(); ++v )
    {
      RETAINED.push_back(BOOSTED[v]);
    }
  }  

  /* else if resolved pairs exist take onlythem */
 
  else if(RESOLVED.size() > 0)
  {  
    for(std::size_t v = 0; v<RESOLVED.size(); ++v )
    {
      RETAINED.push_back(RESOLVED[v]);
    }
  }  


  return;
}




//////////////////////////////////////////////////
// ------------ method called once each job just after ending the event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endJob() {}


/*
//////////////////////////////////////////////////
// ------------ method called when starting to processes a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
//////////////////////////////////////////////////
*/
void FlatTupleGenerator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }
