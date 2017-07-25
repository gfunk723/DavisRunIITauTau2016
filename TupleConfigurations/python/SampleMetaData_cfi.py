#########################
# sampleInfo list
# each sample shoud have all parameters filled 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

# ############ EXAMPLE FOR A 2016/Moriond2017  Sample
# aPSet = cms.PSet(   
#     DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
#     EventTotal = cms.int32(1498800),
#     NumberOfLumis = cms.int32(7502), # obtain from DAS using summary dataset command
#     MaxLumiBlock = cms.int32(7508), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
#     EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
#     KeyName = cms.string("SM_SIGNAL_OLDHLT_125GG"), # a unique descriptor for this sample to be used throught all parts of the code
#     DataCard = cms.string("SM_SIGNAL"), # sample classification for H2TauTau datacards 
#     CrossSection = cms.double(2.0), # cross section in pb (include *BR if needed)
#     FilterEff = cms.double(1.0), # generator level filter effi. 
#     CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
#     RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
#     # for MetSystematicType use:
#     #       "NONE" for data 
#     #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
#     #       "MEtSys::ProcessType::EWK" for single top and Diboson
#     #       "MEtSys::ProcessType::TOP" for t t-bar samples
#     MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
#     KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
#     HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
#                 )
# sampleInfo.append(aPSet)
# ########### 

######
#  NOTE FOR MORIOND 2017 since we are using PF MET 
#  the MetSystematicType and RecoilCorrection 
#  are both set to NONE since they are not applied 
#  in the mono_H analysis 
######


####################################
# 2017 Moriond MonoH Backgrounds   #
####################################


aPSet = cms.PSet(
    DataSet = cms.string(""),
    EventTotal = cms.int32(),
    NumberOfLumis = cms.int32(),
    MaxLumiBlock = cms.int32(),
    EventType = cms.string("MC"),
    KeyName = cms.string(""),
    DataCard = cms.string(""),
    CrossSection = cms.double(),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(96658943),
    NumberOfLumis = cms.int32(608331),
    MaxLumiBlock = cms.int32(633581),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToLL_M-50"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(4954.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"),
    EventTotal = cms.int32(49144274),
    NumberOfLumis = cms.int32(710475),
    MaxLumiBlock = cms.int32(3655000),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToLL_M-50ext1-v2"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(4954.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(62627174),
    NumberOfLumis = cms.int32(316059),
    MaxLumiBlock = cms.int32(342500),
    EventType = cms.string("MC"),
    KeyName = cms.string("DY1JetsToLL_M-50"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(1012.50000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(19970551),
    NumberOfLumis = cms.int32(100052),
    MaxLumiBlock = cms.int32(100500),
    EventType = cms.string("MC"),
    KeyName = cms.string("DY2JetsToLL_M-50"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(332.80000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(5856110),
    NumberOfLumis = cms.int32(29086),
    MaxLumiBlock = cms.int32(29407),
    EventType = cms.string("MC"),
    KeyName = cms.string("DY3JetsToLL_M-50"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(101.80000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(4197868),
    NumberOfLumis = cms.int32(30869),
    MaxLumiBlock = cms.int32(31929),
    EventType = cms.string("MC"),
    KeyName = cms.string("DY4JetsToLL_M-50"),
    DataCard = cms.string("DY"),
    CrossSection = cms.double(54.80000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(77229341),
    NumberOfLumis = cms.int32(482081),
    MaxLumiBlock = cms.int32(499376),
    EventType = cms.string("MC"),
    KeyName = cms.string("TT_TuneCUETP8M2T4"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(831.76000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(1992438),
    NumberOfLumis = cms.int32(10542),
    MaxLumiBlock = cms.int32(10582),
    EventType = cms.string("MC"),
    KeyName = cms.string("TTZToLLNuNu_M-10ext1"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(0.2529),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(5982035),
    NumberOfLumis = cms.int32(34578),
    MaxLumiBlock = cms.int32(34682),
    EventType = cms.string("MC"),
    KeyName = cms.string("TTZToLLNuNu_M-10ext2"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(0.2529),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"),
    EventTotal = cms.int32(5934228),
    NumberOfLumis = cms.int32(30316),
    MaxLumiBlock = cms.int32(30652),
    EventType = cms.string("MC"),
    KeyName = cms.string("TTZToLLNuNu_M-10ext3"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(0.2529),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"),
    EventTotal = cms.int32(2160168),
    NumberOfLumis = cms.int32(16555),
    MaxLumiBlock = cms.int32(16567),
    EventType = cms.string("MC"),
    KeyName = cms.string("TTWJetsToLNu"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(0.2043),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(10045633),
    NumberOfLumis = cms.int32(52144),
    MaxLumiBlock = cms.int32(52411),
    EventType = cms.string("MC"),
    KeyName = cms.string("TT"),
    DataCard = cms.string("ttHJetToNonbb"),
    CrossSection = cms.double(0.2151),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(29705748),
    NumberOfLumis = cms.int32(149804),
    MaxLumiBlock = cms.int32(373943),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(50380.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(57026058),
    NumberOfLumis = cms.int32(351053),
    MaxLumiBlock = cms.int32(369549),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNuext2-v1"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(50380.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(10094300),
    NumberOfLumis = cms.int32(59911),
    MaxLumiBlock = cms.int32(60681),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-70To100"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1354.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(10235198),
    NumberOfLumis = cms.int32(65565),
    MaxLumiBlock = cms.int32(65953),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-100To200orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1345.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(29503700),
    NumberOfLumis = cms.int32(149601),
    MaxLumiBlock = cms.int32(153587),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-100To200"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1345.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(39617787),
    NumberOfLumis = cms.int32(390142),
    MaxLumiBlock = cms.int32(391877),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-100To200ext2-v1"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1345.00000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(4950373),
    NumberOfLumis = cms.int32(36290),
    MaxLumiBlock = cms.int32(38686),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-200To400orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(359.70000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(14815928),
    NumberOfLumis = cms.int32(108330),
    MaxLumiBlock = cms.int32(111421),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-200To400ext1-v1"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(359.70000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(19914590),
    NumberOfLumis = cms.int32(118099),
    MaxLumiBlock = cms.int32(118179),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-200To400"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(359.70000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1963464),
    NumberOfLumis = cms.int32(12714),
    MaxLumiBlock = cms.int32(12754),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-400To600orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(48.91000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(5796237),
    NumberOfLumis = cms.int32(42536),
    MaxLumiBlock = cms.int32(43325),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-400To600"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(48.91000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(3779141),
    NumberOfLumis = cms.int32(23842),
    MaxLumiBlock = cms.int32(26146),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-600To800orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(12.04000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(14908339),
    NumberOfLumis = cms.int32(88226),
    MaxLumiBlock = cms.int32(92869),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-600To800"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(12.04000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1544513),
    NumberOfLumis = cms.int32(11503),
    MaxLumiBlock = cms.int32(11741),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-800To1200orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(5.52000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6200954),
    NumberOfLumis = cms.int32(48543),
    MaxLumiBlock = cms.int32(53849),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-800To1200"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(5.52000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(244532),
    NumberOfLumis = cms.int32(1949),
    MaxLumiBlock = cms.int32(2105),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-1200To2500orig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.33000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6627909),
    NumberOfLumis = cms.int32(66440),
    MaxLumiBlock = cms.int32(74143),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-1200To2500"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.33000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(253561),
    NumberOfLumis = cms.int32(2417),
    MaxLumiBlock = cms.int32(2417),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-2500ToInforig"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(0.03220),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(2384260),
    NumberOfLumis = cms.int32(22773),
    MaxLumiBlock = cms.int32(23167),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT-2500ToInf"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(0.03220),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1703772),
    NumberOfLumis = cms.int32(8579),
    MaxLumiBlock = cms.int32(8583),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo1L3Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(3.05000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1993200),
    NumberOfLumis = cms.int32(9969),
    MaxLumiBlock = cms.int32(10003),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo3LNu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(4.43),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"),
    EventTotal = cms.int32(24221923),
    NumberOfLumis = cms.int32(118042),
    MaxLumiBlock = cms.int32(120900),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo1L1Nu2Q"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(10.71000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6933094),
    NumberOfLumis = cms.int32(44636),
    MaxLumiBlock = cms.int32(45065),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_tW_antitop_5f_inclusiveDecays"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(35.60000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6952830),
    NumberOfLumis = cms.int32(39356),
    MaxLumiBlock = cms.int32(39623),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_tW_top_5f_inclusiveDecays"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(35.60000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(5176114),
    NumberOfLumis = cms.int32(26016),
    MaxLumiBlock = cms.int32(26443),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWTo1L1Nu2Q"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(49.99700),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1999200),
    NumberOfLumis = cms.int32(9996),
    MaxLumiBlock = cms.int32(10000),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWToLNuQQ"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(10.71),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6998600),
    NumberOfLumis = cms.int32(34993),
    MaxLumiBlock = cms.int32(35000),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWToLNuQQext1"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(10.71),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(15345572),
    NumberOfLumis = cms.int32(73853),
    MaxLumiBlock = cms.int32(92189),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZTo2L2Q"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(3.22000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(2852958),
    NumberOfLumis = cms.int32(14396),
    MaxLumiBlock = cms.int32(40780),
    EventType = cms.string("MC"),
    KeyName = cms.string("VVTo2L2Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(11.95000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(296800),
    NumberOfLumis = cms.int32(1487),
    MaxLumiBlock = cms.int32(1503),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToNuNu"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(10.01000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(300000),
    NumberOfLumis = cms.int32(1708),
    MaxLumiBlock = cms.int32(1708),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToNuNu--ext1-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(10.01000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1471061),
    NumberOfLumis = cms.int32(7363),
    MaxLumiBlock = cms.int32(7506),
    EventType = cms.string("MC"),
    KeyName = cms.string("GluGluHToTauTau_M125"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(2.76758),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1499400),
    NumberOfLumis = cms.int32(7716),
    MaxLumiBlock = cms.int32(7719),
    EventType = cms.string("MC"),
    KeyName = cms.string("VBFHToTauTau_M125"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.23713),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(571597),
    NumberOfLumis = cms.int32(5774),
    MaxLumiBlock = cms.int32(6061),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZHToTauTau_M125"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.05543),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(5246318),
    NumberOfLumis = cms.int32(25543),
    MaxLumiBlock = cms.int32(25684),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-100To200orig"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(280.92000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(19026540),
    NumberOfLumis = cms.int32(92697),
    MaxLumiBlock = cms.int32(106106),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-100To200"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(280.92000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(5132650),
    NumberOfLumis = cms.int32(44090),
    MaxLumiBlock = cms.int32(44279),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-200To400orig"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(77.64000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(19612266),
    NumberOfLumis = cms.int32(109571),
    MaxLumiBlock = cms.int32(114969),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-200To400"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(77.64000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1020309),
    NumberOfLumis = cms.int32(9231),
    MaxLumiBlock = cms.int32(9237),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-400To600orig"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(10.67100),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(8842560),
    NumberOfLumis = cms.int32(57279),
    MaxLumiBlock = cms.int32(59289),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-400To600"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(10.67100),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-600To800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(5763506),
    NumberOfLumis = cms.int32(46758),
    MaxLumiBlock = cms.int32(48000),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-600To800"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(2.56110),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(2170137),
    NumberOfLumis = cms.int32(15885),
    MaxLumiBlock = cms.int32(16019),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-800To1200"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.17780),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(143957),
    NumberOfLumis = cms.int32(738),
    MaxLumiBlock = cms.int32(758),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-1200To2500"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(0.28740),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(369514),
    NumberOfLumis = cms.int32(2776),
    MaxLumiBlock = cms.int32(2782),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-1200To2500orig"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(0.28740),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(405030),
    NumberOfLumis = cms.int32(2490),
    MaxLumiBlock = cms.int32(2500),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT-2500ToInf"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(0.00693),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(26517272),
    NumberOfLumis = cms.int32(129237),
    MaxLumiBlock = cms.int32(155764),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo2L2Q"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(5.59500),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(30082038),
    NumberOfLumis = cms.int32(146960),
    MaxLumiBlock = cms.int32(181739),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZTo2Q2Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(4.03000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(240000),
    NumberOfLumis = cms.int32(1200),
    MaxLumiBlock = cms.int32(1250),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWW_4F"),
    DataCard = cms.string("VVV"),
    CrossSection = cms.double(0.20860),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(250000),
    NumberOfLumis = cms.int32(1253),
    MaxLumiBlock = cms.int32(1253),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWZ"),
    DataCard = cms.string("VVV"),
    CrossSection = cms.double(0.16510),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(246800),
    NumberOfLumis = cms.int32(2473),
    MaxLumiBlock = cms.int32(2505),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZZ"),
    DataCard = cms.string("VVV"),
    CrossSection = cms.double(0.05565),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(249237),
    NumberOfLumis = cms.int32(1248),
    MaxLumiBlock = cms.int32(1250),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZZ"),
    DataCard = cms.string("VVV"),
    CrossSection = cms.double(0.01398),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1682400),
    NumberOfLumis = cms.int32(16824),
    MaxLumiBlock = cms.int32(17000),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_antitop_4f_leptonDecays"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(25.49900),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(3279200),
    NumberOfLumis = cms.int32(16396),
    MaxLumiBlock = cms.int32(16500),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_top_4f_leptonDecays"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(42.84630),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)




aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(499200),
    NumberOfLumis = cms.int32(2551),
    MaxLumiBlock = cms.int32(2555),
    EventType = cms.string("MC"),
    KeyName = cms.string("VBFHToWWTo2L2Nu_M125"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.0858),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(492200),
    NumberOfLumis = cms.int32(2463),
    MaxLumiBlock = cms.int32(2502),
    EventType = cms.string("MC"),
    KeyName = cms.string("GluGluHToWWTo2L2Nu_M125---v1"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(1.00100),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(428036),
    NumberOfLumis = cms.int32(2217),
    MaxLumiBlock = cms.int32(2331),
    EventType = cms.string("MC"),
    KeyName = cms.string("WplusHToTauTau"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.052),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(445200),
    NumberOfLumis = cms.int32(2226),
    MaxLumiBlock = cms.int32(2250),
    EventType = cms.string("MC"),
    KeyName = cms.string("WminusHToTauTau"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.0334),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(489205),
    NumberOfLumis = cms.int32(2447),
    MaxLumiBlock = cms.int32(2501),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWMinus2Jets_WToLNu_M-50"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(20.25000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(489205),
    NumberOfLumis = cms.int32(2776),
    MaxLumiBlock = cms.int32(2831),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWMinus2Jets_WToLNu_M-50--ext1-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(20.25000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(3841472),
    NumberOfLumis = cms.int32(23418),
    MaxLumiBlock = cms.int32(24391),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWMinus2Jets_WToLNu_M-50--ext2-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(20.25000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(496000),
    NumberOfLumis = cms.int32(2480),
    MaxLumiBlock = cms.int32(2500),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWPlus2Jets_WToLNu_M-50"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(25.62000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(500000),
    NumberOfLumis = cms.int32(2571),
    MaxLumiBlock = cms.int32(2571),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWPlus2Jets_WToLNu_M-50--ext1-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(25.62000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(3939705),
    NumberOfLumis = cms.int32(20256),
    MaxLumiBlock = cms.int32(20566),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWPlus2Jets_WToLNu_M-50--ext2-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(25.62000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(150000),
    NumberOfLumis = cms.int32(751),
    MaxLumiBlock = cms.int32(751),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToLL_M-50"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(3.98700),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(150000),
    NumberOfLumis = cms.int32(973),
    MaxLumiBlock = cms.int32(973),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToLL_M-50--ext1-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(3.98700),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"),
    EventTotal = cms.int32(699451),
    NumberOfLumis = cms.int32(3823),
    MaxLumiBlock = cms.int32(3826),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToLL_M-50--ext2-v1"),
    DataCard = cms.string("EWK"),
    CrossSection = cms.double(3.98700),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(38811017),
    NumberOfLumis = cms.int32(203542),
    MaxLumiBlock = cms.int32(209771),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_antitop_4f_inclusiveDecaysV2---v1"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(80.95000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(67240808),
    NumberOfLumis = cms.int32(349939),
    MaxLumiBlock = cms.int32(364267),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_top_4f_inclusiveDecaysV2---v1"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(136.02000),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(10709784),
    NumberOfLumis = cms.int32(59558),
    MaxLumiBlock = cms.int32(59639),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZTo4L--ext1-v1"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(1.21200),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1999000),
    NumberOfLumis = cms.int32(10073),
    MaxLumiBlock = cms.int32(9999),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWTo2L2Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(12.178),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(999367),
    NumberOfLumis = cms.int32(6315),
    MaxLumiBlock = cms.int32(6319),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWTo2L2Nu_DoubleScattering"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(1.62),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/WWJJToLNuLNu_EWK_noTop_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(499500),
    NumberOfLumis = cms.int32(2997),
    MaxLumiBlock = cms.int32(3000),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWJJToLNuLNu_EWK_noTop"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(0.3452),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/WpWpJJ_QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(146436),
    NumberOfLumis = cms.int32(904),
    MaxLumiBlock = cms.int32(926),
    EventType = cms.string("MC"),
    KeyName = cms.string("WpWpJJ_QCD"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(0.02615),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/WpWpJJ_EWK_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(150000),
    NumberOfLumis = cms.int32(1215),
    MaxLumiBlock = cms.int32(1215),
    EventType = cms.string("MC"),
    KeyName = cms.string("WpWpJJ_EWK"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(0.02696),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/GluGluWWTo2L2Nu_MCFM_13TeV/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(500000),
    NumberOfLumis = cms.int32(2500),
    MaxLumiBlock = cms.int32(2500),
    EventType = cms.string("MC"),
    KeyName = cms.string("GluGluWWTo2L2Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(0.59),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(8842475),
    NumberOfLumis = cms.int32(46879),
    MaxLumiBlock = cms.int32(47461),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZTo2L2Nu"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(0.564),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)


################################
# 2017 Moriond MonoH Signals   #
################################

aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98549),
    NumberOfLumis = cms.int32(543),
    MaxLumiBlock = cms.int32(551),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98600),
    NumberOfLumis = cms.int32(493),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(96000),
    NumberOfLumis = cms.int32(480),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1000_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(94271),
    NumberOfLumis = cms.int32(532),
    MaxLumiBlock = cms.int32(563),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1200_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(659),
    MaxLumiBlock = cms.int32(659),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"),
    EventTotal = cms.int32(95600),
    NumberOfLumis = cms.int32(478),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98400),
    NumberOfLumis = cms.int32(492),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1400_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(601),
    MaxLumiBlock = cms.int32(601),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99600),
    NumberOfLumis = cms.int32(498),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp1700_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(585),
    MaxLumiBlock = cms.int32(585),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98800),
    NumberOfLumis = cms.int32(494),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(95800),
    NumberOfLumis = cms.int32(479),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(97200),
    NumberOfLumis = cms.int32(486),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2000_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(95560),
    NumberOfLumis = cms.int32(517),
    MaxLumiBlock = cms.int32(541),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98400),
    NumberOfLumis = cms.int32(492),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98400),
    NumberOfLumis = cms.int32(492),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99600),
    NumberOfLumis = cms.int32(498),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-700_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0700"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp2500_A0800"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99337),
    NumberOfLumis = cms.int32(599),
    MaxLumiBlock = cms.int32(603),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp600_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98800),
    NumberOfLumis = cms.int32(494),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp600_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-300_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98260),
    NumberOfLumis = cms.int32(677),
    MaxLumiBlock = cms.int32(689),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp800_A0300"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99400),
    NumberOfLumis = cms.int32(497),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp800_A0400"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp800_A0500"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_2HDM_Zp800_A0600"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(96760),
    NumberOfLumis = cms.int32(598),
    MaxLumiBlock = cms.int32(618),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi1000"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-10_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98946),
    NumberOfLumis = cms.int32(563),
    MaxLumiBlock = cms.int32(569),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi10"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(524),
    MaxLumiBlock = cms.int32(524),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(509),
    MaxLumiBlock = cms.int32(509),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(95976),
    NumberOfLumis = cms.int32(573),
    MaxLumiBlock = cms.int32(597),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi500"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(96235),
    NumberOfLumis = cms.int32(512),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10000_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(96428),
    NumberOfLumis = cms.int32(540),
    MaxLumiBlock = cms.int32(560),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp1000_Chi1000"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(531),
    MaxLumiBlock = cms.int32(531),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp1000_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(97240),
    NumberOfLumis = cms.int32(564),
    MaxLumiBlock = cms.int32(580),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp1000_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-100_MChi-10_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99365),
    NumberOfLumis = cms.int32(626),
    MaxLumiBlock = cms.int32(630),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp100_Chi10"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-100_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(527),
    MaxLumiBlock = cms.int32(527),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp100_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(514),
    MaxLumiBlock = cms.int32(514),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi1000"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-10_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99272),
    NumberOfLumis = cms.int32(546),
    MaxLumiBlock = cms.int32(550),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi10"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"),
    EventTotal = cms.int32(98898),
    NumberOfLumis = cms.int32(539),
    MaxLumiBlock = cms.int32(545),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(97116),
    NumberOfLumis = cms.int32(539),
    MaxLumiBlock = cms.int32(555),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98131),
    NumberOfLumis = cms.int32(630),
    MaxLumiBlock = cms.int32(642),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi500"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(532),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp10_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-15_MChi-10_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(525),
    MaxLumiBlock = cms.int32(525),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp15_Chi10"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1995_MChi-1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(532),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp1995_Chi1000"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-2000_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(531),
    MaxLumiBlock = cms.int32(531),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp2000_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-2000_MChi-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(97220),
    NumberOfLumis = cms.int32(525),
    MaxLumiBlock = cms.int32(540),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp2000_Chi500"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(575),
    MaxLumiBlock = cms.int32(575),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp200_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(502),
    MaxLumiBlock = cms.int32(502),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp200_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(528),
    MaxLumiBlock = cms.int32(528),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp200_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-20_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(595),
    MaxLumiBlock = cms.int32(595),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp20_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-295_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98205),
    NumberOfLumis = cms.int32(493),
    MaxLumiBlock = cms.int32(502),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp295_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-300_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(96532),
    NumberOfLumis = cms.int32(557),
    MaxLumiBlock = cms.int32(577),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp300_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-300_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98590),
    NumberOfLumis = cms.int32(559),
    MaxLumiBlock = cms.int32(567),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp300_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-150_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(619),
    MaxLumiBlock = cms.int32(619),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp500_Chi150"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(507),
    MaxLumiBlock = cms.int32(507),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp500_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(97705),
    NumberOfLumis = cms.int32(511),
    MaxLumiBlock = cms.int32(523),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp500_Chi500"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-10_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(558),
    MaxLumiBlock = cms.int32(558),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp50_Chi10"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(512),
    MaxLumiBlock = cms.int32(512),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp50_Chi1"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"),
    EventTotal = cms.int32(98483),
    NumberOfLumis = cms.int32(529),
    MaxLumiBlock = cms.int32(537),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp50_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-95_MChi-50_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(98832),
    NumberOfLumis = cms.int32(508),
    MaxLumiBlock = cms.int32(514),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp95_Chi50"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-995_MChi-500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(99192),
    NumberOfLumis = cms.int32(614),
    MaxLumiBlock = cms.int32(619),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_Moriond17_ZpBaryonic_Zp995_Chi500"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)




#############
# 2016 DATA -- for Moriond 2017
################

aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016B-03Feb2017_ver2-v2/MINIAOD"),
    EventTotal = cms.int32(246440440),
    NumberOfLumis = cms.int32(59819),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_B-03Feb2017_ver2-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016C-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(97259854),
    NumberOfLumis = cms.int32(18769),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_C-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016D-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(148167727),
    NumberOfLumis = cms.int32(30238),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_D-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016E-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(117321545),
    NumberOfLumis = cms.int32(27153),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_E-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016F-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(70593532),
    NumberOfLumis = cms.int32(19441),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_F-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016G-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(153330123),
    NumberOfLumis = cms.int32(46306),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_G-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016H-03Feb2017_ver2-v1/MINIAOD"),
    EventTotal = cms.int32(125826667),
    NumberOfLumis = cms.int32(51328),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_H-03Feb2017_ver2-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016H-03Feb2017_ver3-v1/MINIAOD"),
    EventTotal = cms.int32(3191585),
    NumberOfLumis = cms.int32(1233),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_H-03Feb2017_ver3-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD"),
    EventTotal = cms.int32(158145722),
    NumberOfLumis = cms.int32(58962),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_B-03Feb2017_ver2-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016C-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(67441308),
    NumberOfLumis = cms.int32(18611),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_C-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016D-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(98017996),
    NumberOfLumis = cms.int32(30072),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_D-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016E-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(90963495),
    NumberOfLumis = cms.int32(26865),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_E-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016F-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(65489554),
    NumberOfLumis = cms.int32(19204),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_F-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016G-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(149916849),
    NumberOfLumis = cms.int32(45788),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_G-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD"),
    EventTotal = cms.int32(169642135),
    NumberOfLumis = cms.int32(50502),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_H-03Feb2017_ver2-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD"),
    EventTotal = cms.int32(4393029),
    NumberOfLumis = cms.int32(1241),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_H-03Feb2017_ver3-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016B-03Feb2017_ver2-v2/MINIAOD"),
    EventTotal = cms.int32(68727458),
    NumberOfLumis = cms.int32(59642),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_B-03Feb2017_ver2-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016C-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(36931473),
    NumberOfLumis = cms.int32(18810),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_C-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016D-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(56827771),
    NumberOfLumis = cms.int32(30295),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_D-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016E-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(58348773),
    NumberOfLumis = cms.int32(27199),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_E-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016F-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(40549716),
    NumberOfLumis = cms.int32(19584),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_F-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016G-03Feb2017-v1/MINIAOD"),
    EventTotal = cms.int32(79557782),
    NumberOfLumis = cms.int32(46448),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_G-03Feb2017-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016H-03Feb2017_ver2-v1/MINIAOD"),
    EventTotal = cms.int32(74860701),
    NumberOfLumis = cms.int32(51512),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_H-03Feb2017_ver2-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016H-03Feb2017_ver3-v1/MINIAOD"),
    EventTotal = cms.int32(1898053),
    NumberOfLumis = cms.int32(1246),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_H-03Feb2017_ver3-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)






###############################
