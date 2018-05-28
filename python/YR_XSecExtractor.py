import ROOT

ListOfFilesToCheck=[
#Wjets
"/store/mc/PhaseIISpr18AODMiniAOD/WToLNu_0J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5_ext1-v1/40000/4057E045-FE45-E811-A822-D4AE527EDFE4.root",
"/store/mc/PhaseIISpr18AODMiniAOD/WToLNu_1J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/00000/48BC3D62-7646-E811-A7D3-0025905C4300.root",
"/store/mc/PhaseIISpr18AODMiniAOD/WToLNu_2J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/10000/90FB82C8-FF43-E811-9794-002481CFB40E.root",
"/store/mc/PhaseIISpr18AODMiniAOD/WToLNu_3J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/00000/008B96BB-2545-E811-8F9F-1418774124DE.root",
#DYjets
"/store/mc/PhaseIISpr18AODMiniAOD/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5_ext1-v1/00000/06C0DF8F-EC43-E811-87FB-001E6724866F.root",
"/store/mc/PhaseIISpr18AODMiniAOD/DYToLL-M-50_1J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/00000/000AB7A0-4145-E811-8337-7CD30ACE178C.root",
"/store/mc/PhaseIISpr18AODMiniAOD/DYToLL-M-50_2J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5_ext1-v1/20000/7643BBFF-FE51-E811-8466-0CC47A4C8E3C.root",
"/store/mc/PhaseIISpr18AODMiniAOD/DYToLL-M-50_3J_14TeV-madgraphMLM-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/00000/4C596E9E-F248-E811-A2B9-B496910A9788.root",
#TT
"/store/mc/PhaseIISpr18AODMiniAOD/TT_TuneCUETP8M2T4_14TeV-powheg-pythia8/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/100000/744E0163-5B1B-E811-B29F-A0369F7FC540.root",
#ST
"/store/mc/PhaseIISpr18AODMiniAOD/ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/70000/E01AC51F-2043-E811-88B6-90E2BAD4912C.root",
"/store/mc/PhaseIISpr18AODMiniAOD/ST_tch_14TeV_top_incl-powheg-pythia8-madspin/MINIAODSIM/PU200_93X_upgrade2023_realistic_v5-v1/20000/0E92051C-284A-E811-B654-0025905B85DE.root"
#"",
]

for i in ListOfFilesToCheck:
    ##########################
    #Loading full tree to read
    ##########################
    MainChain=ROOT.TChain("LuminosityBlocks")
    MainChain.Add("root://cms-xrd-global.cern.ch/"+i)
    MainChain.LoadTree(0)
    #MainChain.Print("p")
    ##########################
    #Scanning xsec
    ##########################
    MainChain.SetScanField(0)
    print "Scanning:", i
    MainChain.Scan("GenLumiInfoHeader_generator__SIM.obj.configDescription_:GenLumiInfoProduct_generator__SIM.obj.internalProcesses_.lheXSec_.value_:GenLumiInfoProduct_generator__SIM.obj.internalProcesses_.lheXSec_.error_","","colsize=30 precision=3",500)
    del(MainChain)
