#!/bin/tcsh

# setup access
# for fall17

voms-proxy-init -voms cms --valid=72:00

# some defaults

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc630

if ( -d CMSSW_9_4_0_pre2) then
        echo 'directory CMSSW_9_4_0_pre2 already exits, doing nothing further'
        exit 1
endif


# create the working area
	
cmsrel CMSSW_
cd CMSSW_9_4_0_pre2/src/
cmsenv

# set up git

git cms-init

# build command
scram b -j 20 # needed to get correct dir structure for electron ID


echo " -----> INSTALLING WITHOUT MVA MET "
echo " -----> INSTALLING WITHOUT MVA MET "
echo " -----> INSTALLING WITHOUT MVA MET "


# MVA MET 
#git cms-addpkg RecoMET/METPUSubtraction
#git cms-addpkg DataFormats/METReco
#git remote add -f mvamet https://github.com/rfriese/cmssw.git
#git checkout mvamet/mvamet8020 -b mvamet # this line erases the new electron ID for Moriond 2017


# so instead we pull the needed directories only 
# mkdir RecoMET
# cp -r ../../DavisRunIITauTau/ExternalFiles/MVA_MET_8020/ExternalCode/METPUSubtraction RecoMET/. 
# mkdir DataFormats
# cp -r ../../DavisRunIITauTau/ExternalFiles/MVA_MET_8020/ExternalCode/METReco DataFormats/. 
# mkdir RecoMET/METPUSubtraction/data
# cd RecoMET/METPUSubtraction/data
# wget https://github.com/rfriese/cmssw/raw/MVAMET2_beta_0.6/RecoMET/METPUSubtraction/data/weightfile.root
# cd $CMSSW_BASE/src


# to allow rerun of tau ID on miniAOD
# see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_MiniA
git cms-merge-topic -u cms-tau-pog:CMSSW_8_0_X_tau-pog_miniAOD-backport-tauID


# new Moriond17 electron ID 
git cms-merge-topic ikrav:egm_id_80X_v2 -u

# Add in the new MET filter code needed for 8020X and beyond in 2016 
# see: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Notes_regarding_the_ICHEP_datase
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter


# Add in Bad Muon Filter -- we just copied the filter .cc file into our code
# as CustomFilters/plugins/BadGlobalMuonTagger.cc
# since this pulls in nearly all of CMSSW
# this is much less than running : git cms-merge-topic gpetruc:badMuonFilters_80X
git cms-merge-topic gpetruc:badMuonFilters_80X_v2 -u

# update to latest and greatest MET 

git cms-merge-topic cms-met:METRecipe_8020 -u

# allow MET E/Gamma recorrection on-the-fly 
# see https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes#MET_Recipes
git cms-merge-topic cms-met:METRecipe_80X_part2 -u

# SVFIt 

git clone git@github.com:veelken/SVfit_standalone.git TauAnalysis/SVfitStandalone
cd TauAnalysis/SVfitStandalone/
git checkout HIG-16-006
cd $CMSSW_BASE/src

# MET RECOIL CORRECTIONS (SAME CODE FOR PF AND MVA MET)
git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 

# for muon effective area 

git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
cd Muon/MuonAnalysisTools 
git checkout master -- interface/MuonEffectiveArea.h 
cd -

# additional electron MVA ID files

cd $CMSSW_BASE/external
cd slc6_amd64_gcc630
git clone https://github.com/ikrav/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
cd data/RecoEgamma/ElectronIdentification/data
git checkout egm_id_80X_v1
cd $CMSSW_BASE/src


# pilup reweight code -- this is done to turn of cout statements
git cms-addpkg PhysicsTools/Utilities
sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc

# relocate the davis code
mv ../../DavisRunIITauTau .


# copy the PU reweight files 
# when these change (for new data or mc) 
# update the files listed in TupleConfigurations/python/ConfigNtupleWeights_cfi.py

# Moriond17 : SINCE AFS IS GOING AWAY we'll have to carry these in github from now on
# for future updates be sure to adjust this to pull the correct files from whatever source they are hosted on
#cp /afs/cern.ch/user/a/anehrkor/public/MC_Moriond17_PU25ns_V1.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/.
#cp /afs/cern.ch/user/a/anehrkor/public/Data_Pileup_2016_271036-284044_80bins.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/.

cp DavisRunIITauTau/ExternalFiles/PileUpReWeightFiles/MC_Moriond17_PU25ns_V1.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/. 
cp DavisRunIITauTau/ExternalFiles/PileUpReWeightFiles/Data_Pileup_2016_271036-284044_80bins.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/. 




# get the right JER SF file for this release
# if new file, need to code the change in runIIoneStep_v0.py and runIIntuple_v0.py

mkdir DavisRunIITauTau/RunTimeDataInput/data/JER_FILES
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK4PFchs.txt .
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt .
mv Spring16_25nsV10_MC_SF_AK4PFchs.txt DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/.
mv Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/.


# in some cases the GlobalTag containing the update JEC is not ready
# if a .db file is available but a GlobalTag is not you can 
# access it from
# https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC 
# and install into our code using the following lines 
# see secion on LocalSQLfile here 
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections


# Moriond17 : SINCE AFS IS GOING AWAY we'll have to carry these in github from now on
# for future updates be sure to adjust this to pull the correct files from whatever source they are hosted on
# mkdir DavisRunIITauTau/RunTimeDataInput/data/JECSQLiteFiles
#cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/SQLiteFiles/Summer16_23Sep2016AllV3_DATA.db .
#cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/SQLiteFiles/Summer16_23Sep2016V3_MC.db .

mkdir DavisRunIITauTau/RunTimeDataInput/data/JECSQLiteFiles
cp DavisRunIITauTau/ExternalFiles/JECSQLiteFiles/Summer16_23Sep2016AllV3_DATA.db DavisRunIITauTau/RunTimeDataInput/data/JECSQLiteFiles/.
cp DavisRunIITauTau/ExternalFiles/JECSQLiteFiles/Summer16_23Sep2016V3_MC.db DavisRunIITauTau/RunTimeDataInput/data/JECSQLiteFiles/.

# get the BTAG SF CSV File  and EFF root files 
# make sure discirminator and working points are set in
# ConfigNtupleContent_cfi.py (look for DEFAULT_BTAG_ALGORITHM)
# and in the section `b-tag configuration`
# of FlatTupleConfig_cfi.py
# here is the current setup for 8_0_25 
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
# note we support 2 methods from
# https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#2a_Jet_by_jet_updating_of_the_b
# the SM analysis and MSSM analysis use promote-demote (method 2a)
# while mono-H uses an event-based SF for MC (method 1c)
# note : only promote-demote uses the BTAGEFF file


# Moriond17 : SINCE AFS IS GOING AWAY we'll have to carry these in github from now on
# for future updates be sure to adjust this to pull the correct files from whatever source they are hosted on
#mkdir DavisRunIITauTau/RunTimeDataInput/data/BTAGSF
#cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/CSVv2_Moriond17_B_H.csv .
#mv CSVv2_Moriond17_B_H.csv DavisRunIITauTau/RunTimeDataInput/data/BTAGSF/.

mkdir DavisRunIITauTau/RunTimeDataInput/data/BTAGSF
cp DavisRunIITauTau/ExternalFiles/BTAGSF/CSVv2_Moriond17_B_H.csv DavisRunIITauTau/RunTimeDataInput/data/BTAGSF/.



# so far in 80X only a single WP eff. is available for sf > 1 case 
# if the file is new, need to change the name used in FlatTupleConfig_cfi.py
# Moriond17 : SINCE AFS IS GOING AWAY we'll have to carry these in github from now on
# for future updates be sure to adjust this to pull the correct files from whatever source they are hosted on

mkdir DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF
#cp /afs/cern.ch/work/a/adewit/public/MSSM2016/tagging_efficiencies_ichep2016.root DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/.
cp DavisRunIITauTau/ExternalFiles/BTAGEFF/tagging_efficiencies_ichep2016.root DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/.



# for PF MET, manual patch applied 
# Additionally, apply these two patches: 
# - https://github.com/vhbb/cmssw/pull/524/commits/1dd40d418ddc3f769daff7aff5a37a81edd1c9a9 
# - https://github.com/vhbb/cmssw/pull/524/commits/3c18062dc38f56c01c6ee68da5cf79951208bd16
# instead I have modified the files directly (these are fine in 820X)

git cms-addpkg DataFormats/PatCandidates
# cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/METReco/MET.h_mod DataFormats/METReco/interface/MET.h
# cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/METReco/MET.cc_mod DataFormats/METReco/src/MET.cc
# cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/PatCandidates/MET.cc_mod DataFormats/PatCandidates/src/MET.cc
# Moriond17 : SINCE AFS IS GOING AWAY we'll have to carry these in github from now on
# for future updates be sure to adjust this to pull the correct files from whatever source they are hosted on
# cp DavisRunIITauTau/ExternalFiles/CMSSW_8X_MODS/METReco/MET.h_mod DataFormats/METReco/interface/MET.h
# cp DavisRunIITauTau/ExternalFiles/CMSSW_8X_MODS/METReco/MET.cc_mod DataFormats/METReco/src/MET.cc 
# cp DavisRunIITauTau/ExternalFiles/CMSSW_8X_MODS/PatCandidates/MET.cc_mod  DataFormats/PatCandidates/src/MET.cc




# electron ID ----> cut based ID/mva ID are already integrated into this release but cuts must be modified
# muon ID --> already integrated into this release but cuts must be modified
# PF jet ID --> no new code cuts must be modifed
# PU jet ID --> for this rel, no code is needed but must follow recalc instructions
# JEC --> method unchanged from 76X no code is needed
# b-jets -> no new code, should update sf code






# Lepton Eff for Muon & Electron for Spring 16
# check that the correct  files used (they are hard-coded in generateH2TauSyncTree.cc)
#-- cd DavisRunIITauTau/AnalysisRunII/Analysis/
#-- git clone https://github.com/CMS-HTT/LeptonEff-interface.git HTT-utilities
#-- cd HTT-utilities/LepEffInterface
#-- git clone https://github.com/CMS-HTT/LeptonEfficiencies.git data
#-- cd ${CMSSW_BASE}/src

# compile

# there is a bug in 
git cms-addpkg PhysicsTools/PatUtils
sed -i 's/from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection/from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection \nfrom RecoMET.METProducers.METSignificanceParams_cfi import METSignificanceParams_Data/1' ./PhysicsTools/PatUtils/python/tools/runMETCorrectionsAndUncertainties.py
#mv DavisRunIITauTau/CustomFilters/plugins/BadGlobalMuonTagger.cc DavisRunIITauTau/CustomFilters/plugins/BadGlobalMuonTagger.cc_doNotUse

scram b -j 20
