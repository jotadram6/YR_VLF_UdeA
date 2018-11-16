from Generic import *
import CMS_lumi, tdrstyle
CMS_lumi.cmsText = "CMS"
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_13TeV = "3000 fb^{-1}"
tdrstyle.setTDRStyle()

def YOURcanvas(name="icanvas", size=(800, 600)):
    """Helper method for creating canvas"""

    # Check if icanvas already exists
    canvas = ROOT.gROOT.FindObject(name)
    assert len(size) == 2
    if canvas:
        return canvas
    else:
        return ROOT.TCanvas(name, name, size[0], size[1])

ROOT.gROOT.ProcessLine("#include <math.h>")

ROOT.gROOT.Macro("rootphi.C")


BasePath="/home/joser/VLF_YR/MergedRootFiles_20180622/"

#Signal

SigChain=ROOT.TChain("Delphes")
#SigChain.Add(BasePath+"MF100_MS80_BR_1_0_PU0_part10_ntuple.root")
#SigChain.Add(BasePath+"MF100_MS80_BR_1_0_PU0_part21_ntuple.root")
SigChain.Add(BasePath+"signal0_ntuple.root")

#Backgrounds

W0Jetschain=ROOT.TChain("Delphes")
W1Jetschain=ROOT.TChain("Delphes")
W2Jetschain=ROOT.TChain("Delphes")
W3Jetschain=ROOT.TChain("Delphes")
TTchain=ROOT.TChain("Delphes")
DY0chain=ROOT.TChain("Delphes")
DY1chain=ROOT.TChain("Delphes")
DY2chain=ROOT.TChain("Delphes")
DY3chain=ROOT.TChain("Delphes")

W0Jetschain.Add(BasePath+"W0J_total.root")
W1Jetschain.Add(BasePath+"W1J_total.root")
W2Jetschain.Add(BasePath+"W2J_total.root")
W3Jetschain.Add(BasePath+"W3J_total.root")
TTchain.Add(BasePath+"TT_total.root")
DY0chain.Add(BasePath+"DY0J_total.root")
DY1chain.Add(BasePath+"DY1J_total.root")
DY2chain.Add(BasePath+"DY2J_total.root")
DY3chain.Add(BasePath+"DY3J_total.root")

SignalEventsP=SigChain.GetEntries()
W0JetsEventsP=W0Jetschain.GetEntries()
W1JetsEventsP=W1Jetschain.GetEntries()
W2JetsEventsP=W2Jetschain.GetEntries()
W3JetsEventsP=W3Jetschain.GetEntries()
TTEventsP=TTchain.GetEntries()
DY0EventsP=DY0chain.GetEntries()
DY1EventsP=DY1chain.GetEntries()
DY2EventsP=DY2chain.GetEntries()
DY3EventsP=DY3chain.GetEntries()

SignalEvents=30465
W0JetsEvents=20437582
W1JetsEvents=20223922
W2JetsEvents=21322007
W3JetsEvents=7999155
TTEvents=49800568
DY0Events=19883879
DY1Events=12878206
DY2Events=10430290
DY3Events=11794679

Lumi = 3000000

SignalXS = 0.815
W0JetsXS = 38870.0
W1JetsXS = 10330.0
W2JetsXS = 3314.0
W3JetsXS = 1891.0
TTXS = 864.4
DY0XS = 3668.0
DY1XS = 1094.0
DY2XS = 369.7
DY3XS = 190.2

SignalW = Lumi*SignalXS/SignalEvents
W0JetsW = Lumi*W0JetsXS/W0JetsEvents
W1JetsW = Lumi*W1JetsXS/W1JetsEvents
W2JetsW = Lumi*W2JetsXS/W2JetsEvents
W3JetsW = Lumi*W3JetsXS/W3JetsEvents
TTW = Lumi*TTXS/TTEvents
DY0W = Lumi*DY0XS/DY0Events
DY1W = Lumi*DY1XS/DY1Events
DY2W = Lumi*DY2XS/DY2Events
DY3W = Lumi*DY3XS/DY3Events

print "--------------------------------------------------------------------------------------------"
print "Luminosity=", Lumi
print "Number of events for signal=", SignalEvents, " XS=", SignalXS, " Weight=", SignalW, " Passed events=",  float(SignalEventsP)/SignalEvents
print "Number of events for W+0jets=", W0JetsEvents, " XS=", W0JetsXS, " Weight=", W0JetsW, " Passed events=", float(W0JetsEventsP)/W0JetsEvents
print "Number of events for W+1jets=", W1JetsEvents, " XS=", W1JetsXS, " Weight=", W1JetsW, " Passed events=", float(W1JetsEventsP)/W1JetsEvents
print "Number of events for W+2jets=", W2JetsEvents, " XS=", W2JetsXS, " Weight=", W2JetsW, " Passed events=", float(W2JetsEventsP)/W2JetsEvents
print "Number of events for W+3jets=", W3JetsEvents, " XS=", W3JetsXS, " Weight=", W3JetsW, " Passed events=", float(W3JetsEventsP)/W3JetsEvents
print "Number of events for TT=", TTEvents, " XS=", TTXS, " Weight=", TTW, " Passed events=", float(TTEventsP)/TTEvents
print "Number of events for DY=", DY0Events, " XS=", DY0XS, " Weight=", DY0W, " Passed events=", float(DY0EventsP)/DY0Events
print "Number of events for DY=", DY1Events, " XS=", DY1XS, " Weight=", DY1W, " Passed events=", float(DY1EventsP)/DY1Events
print "Number of events for DY=", DY2Events, " XS=", DY2XS, " Weight=", DY2W, " Passed events=", float(DY2EventsP)/DY2Events
print "Number of events for DY=", DY3Events, " XS=", DY3XS, " Weight=", DY3W, " Passed events=", float(DY3EventsP)/DY3Events
print "--------------------------------------------------------------------------------------------"

#Cuts

BasicSelection="((NTightMuons==2)&&(muon1Charge*muon2Charge<0)&&((TwoMuonSystemMass<60)||(TwoMuonSystemMass>120)))" #Tight muons
#BasicSelection="((NTightIso0p4Muons==2)&&(muon1Charge*muon2Charge<0)&&((TwoIso0p4MuonSystemMass<60)||(TwoIso0p4MuonSystemMass>120)))" #Tight Iso 0p4 muons
#BasicSelection="((mostIsomuon1Charge*mostIsomuon2Charge<0)&&((mostIsoTwoMuonSystemMass<60)||(mostIsoTwoMuonSystemMass>120)))" #Most Iso Tight muons
TTbarRejection="(NJets<3)"
LowPTMuonRejection="((muon1Pt>14)&&(muon2Pt>10)&&(jet1Pt>70))" #Constrained from trigger
METCut="(MET>60)"
MuonCleansing="(muon2JetsMuon0p4PtRatio>0.2)"
#DYRejection="((muon1Pt<30)&&(muon2Pt<30))"
DYRejection="((muon2Pt/muon1Pt)>0.2)"
FullS=BasicSelection+"&&"+TTbarRejection+"&&"+LowPTMuonRejection+"&&"+MuonCleansing+"&&"+METCut+"&&"+DYRejection
#+"&&"+TTbarRejection+"&&"+LowPTMuonRejection+"&&"+MuonCleansing+"&&"+METCut

VariablesForOptimization=["MTmin","TwoMuonSystemPt"]
OptBinning=["(100,0,200)","(250,0,500)"]
#VariablesForOptimization=["muon1Pt","muon2Pt","MT12","muon1JetsMuon0p4PtRatio","muon2JetsMuon0p4PtRatio"]
#OptBinning=["(125,0,250)","(100,0,200)","(500,0,1000)","(100,0,1)","(100,0,1)"]
#VariablesForOptimization=["MT12","MT1","MT2","MTmin"]
#OptBinning=["(500,0,1000)","(250,0,500)","(250,0,500)","(100,0,200)"]
#VariablesForOptimization=["MET","jet1Pt"]
#OptBinning=["(80,0,800)","(80,0,800)"]

TIMEStr=time.strftime("%H_%M_%S")
PDFNames="TwoMuonChannelOpt_"+TIMEStr
print "Plotting on:", PDFNames
HistFile= ROOT.TFile(PDFNames+".root", "recreate")

for i in xrange(len(VariablesForOptimization)):
    HistName=VariablesForOptimization[i].replace("(","").replace(")","").replace("[","").replace("]","").replace(":","").replace(".","").replace("-","m").replace("+","p").replace(" ","_").replace("&","_and_").replace("&&","_and_").replace("*","_times_").replace(">","g").replace("<","l").replace(",","l").replace("/","d")
    print "Extracting "+VariablesForOptimization[i]
    #Extracting histograms
    HistNameSignal="Signal_"+HistName
    HistNameW0Jets="W0Jets_"+HistName
    HistNameW1Jets="W1Jets_"+HistName
    HistNameW2Jets="W2Jets_"+HistName
    HistNameW3Jets="W3Jets_"+HistName
    HistNameTT="TT_"+HistName
    HistNameDY0="DY0_"+HistName
    HistNameDY1="DY1_"+HistName
    HistNameDY2="DY2_"+HistName
    HistNameDY3="DY3_"+HistName
    SigChain.Draw(VariablesForOptimization[i]+" >> "+HistNameSignal+OptBinning[i],FullS)
    W0Jetschain.Draw(VariablesForOptimization[i]+" >> "+HistNameW0Jets+OptBinning[i],FullS)
    W1Jetschain.Draw(VariablesForOptimization[i]+" >> "+HistNameW1Jets+OptBinning[i],FullS)
    W2Jetschain.Draw(VariablesForOptimization[i]+" >> "+HistNameW2Jets+OptBinning[i],FullS)
    W3Jetschain.Draw(VariablesForOptimization[i]+" >> "+HistNameW3Jets+OptBinning[i],FullS)
    TTchain.Draw(VariablesForOptimization[i]+" >> "+HistNameTT+OptBinning[i],FullS)
    DY0chain.Draw(VariablesForOptimization[i]+" >> "+HistNameDY0+OptBinning[i],FullS)
    DY1chain.Draw(VariablesForOptimization[i]+" >> "+HistNameDY1+OptBinning[i],FullS)
    DY2chain.Draw(VariablesForOptimization[i]+" >> "+HistNameDY2+OptBinning[i],FullS)
    DY3chain.Draw(VariablesForOptimization[i]+" >> "+HistNameDY3+OptBinning[i],FullS)
    SignalHisto=ROOT.gDirectory.Get(HistNameSignal)
    W0JetsHisto=ROOT.gDirectory.Get(HistNameW0Jets)
    W1JetsHisto=ROOT.gDirectory.Get(HistNameW1Jets)
    W2JetsHisto=ROOT.gDirectory.Get(HistNameW2Jets)
    W3JetsHisto=ROOT.gDirectory.Get(HistNameW3Jets)
    TTHisto=ROOT.gDirectory.Get(HistNameTT)
    DY0Histo=ROOT.gDirectory.Get(HistNameDY0)
    DY1Histo=ROOT.gDirectory.Get(HistNameDY1)
    DY2Histo=ROOT.gDirectory.Get(HistNameDY2)
    DY3Histo=ROOT.gDirectory.Get(HistNameDY3)
    SignalHisto.Sumw2()
    W0JetsHisto.Sumw2()
    W1JetsHisto.Sumw2()
    W2JetsHisto.Sumw2()
    W3JetsHisto.Sumw2()
    TTHisto.Sumw2()
    DY0Histo.Sumw2()
    DY1Histo.Sumw2()
    DY2Histo.Sumw2()
    DY3Histo.Sumw2()

    SignalHisto.Scale(SignalW)
    W0JetsHisto.Scale(W0JetsW)
    W1JetsHisto.Scale(W1JetsW)
    W2JetsHisto.Scale(W2JetsW)
    W3JetsHisto.Scale(W3JetsW)
    TTHisto.Scale(TTW)
    DY0Histo.Scale(DY0W)
    DY1Histo.Scale(DY1W)
    DY2Histo.Scale(DY2W)
    DY3Histo.Scale(DY3W)

    #Building full background histo
    FullBkg=DY0Histo.Clone("FullBkg_"+HistName)
    FullBkg.Sumw2()
    FullBkg.Add(DY1Histo)
    FullBkg.Add(DY2Histo)
    FullBkg.Add(DY3Histo)
    FullBkg.Add(TTHisto)
    FullBkg.Add(W0JetsHisto)
    FullBkg.Add(W1JetsHisto)
    FullBkg.Add(W2JetsHisto)
    FullBkg.Add(W3JetsHisto)

    #Stack's histos
    FullDY=DY0Histo.Clone("FullDY_"+HistName)
    FullDY.Sumw2()
    FullDY.Add(DY1Histo)
    FullDY.Add(DY2Histo)
    FullDY.Add(DY3Histo)

    FullW=W0JetsHisto.Clone("FullWJets_"+HistName)
    FullW.Sumw2()
    FullW.Add(W1JetsHisto)
    FullW.Add(W2JetsHisto)
    FullW.Add(W3JetsHisto)

    SoverSqrtSpB1, ZHisto1, EffSHisto1, EffBHisto1 = SmallerThan(SignalHisto,FullDY,"DY_ST_"+HistName)

    print "-----------------Significance study 1---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB1)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB1.index(max(SoverSqrtSpB1)))
    print "---------------------------------------------------------"    

    SoverSqrtSpB2, ZHisto2, EffSHisto2, EffBHisto2 = GreaterThan(SignalHisto,FullDY,"DY_GT_"+HistName)

    print "-----------------Significance study 2---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB2)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB2.index(max(SoverSqrtSpB2)))
    print "---------------------------------------------------------"    

    SoverSqrtSpB3, ZHisto3, EffSHisto3, EffBHisto3 = SmallerThan(SignalHisto,TTHisto,"TT_ST_"+HistName)

    print "-----------------Significance study 3---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB3)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB3.index(max(SoverSqrtSpB3)))
    print "---------------------------------------------------------"    

    SoverSqrtSpB4, ZHisto4, EffSHisto4, EffBHisto4 = GreaterThan(SignalHisto,TTHisto,"TT_GT_"+HistName)

    print "-----------------Significance study 4---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB4)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB4.index(max(SoverSqrtSpB4)))
    print "---------------------------------------------------------"

    SoverSqrtSpB5, ZHisto5, EffSHisto5, EffBHisto5 = SmallerThan(SignalHisto,FullBkg,"Fullbkg_ST_"+HistName)

    print "-----------------Significance study 5---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB5)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB5.index(max(SoverSqrtSpB5)))
    print "---------------------------------------------------------"    

    SoverSqrtSpB6, ZHisto6, EffSHisto6, EffBHisto6 = GreaterThan(SignalHisto,FullBkg,"Fullbkg_GT_"+HistName)

    print "-----------------Significance study 6---------------------"
    print "Significance before optimization =", SignalHisto.Integral()/np.sqrt(SignalHisto.Integral()+FullBkg.Integral())
    print "Maximum significance reached is =", max(SoverSqrtSpB6)
    print "At value on the variable "+HistName+" =", SignalHisto.GetBinLowEdge(SoverSqrtSpB6.index(max(SoverSqrtSpB6)))
    print "---------------------------------------------------------"



    SignalHisto.Write()
    W0JetsHisto.Write()
    W1JetsHisto.Write()
    W2JetsHisto.Write()
    W3JetsHisto.Write()
    TTHisto.Write()
    DY0Histo.Write()
    DY1Histo.Write()
    DY2Histo.Write()
    DY3Histo.Write()
    FullBkg.Write()
    FullDY.Write()
    FullW.Write()
    
    EffSHisto1.Write()
    EffBHisto1.Write()
    ZHisto1.Write()
    EffSHisto2.Write()
    EffBHisto2.Write()
    ZHisto2.Write()
    EffSHisto3.Write()
    EffBHisto3.Write()
    ZHisto3.Write()
    EffSHisto4.Write()
    EffBHisto4.Write()
    ZHisto4.Write()
    EffSHisto5.Write()
    EffBHisto5.Write()
    ZHisto5.Write()
    EffSHisto6.Write()
    EffBHisto6.Write()
    ZHisto6.Write()

HistFile.Close()


"""
HToExtract=["Jet_size","Jet[0].PT","Jet[1].PT","Muon_size","Muon[0].PT","MissingET.MET",
            "TMath::Sqrt(2*Muon[0].PT*MissingET.MET*(1-TMath::Cos(deltaPhi(MissingET.Phi,Muon[0].Phi))))"]

Binning=["(15,0,15)","(100,0,1000)","(50,0,500)","(5,0,5)","(100,0,300)","(100,0,1000)","(20,0,200)"]

EntriesListSingleT=[]
EntriesListSignal=[]
EntriesListWjets=[]
EntriesListDiboson=[]
c = ROOT.TCanvas()

for j in xrange(len(ListOfCuts)):
    #rif j!=0: continue
    for i in xrange(len(HToExtract)):



        EntriesListSignal.append(SignalHisto.GetEntries())
        EntriesListWjets.append(WJetsHisto.GetEntries())
        EntriesListSingleT.append(SingleTHisto.GetEntries())
        EntriesListDiboson.append(DibosonHisto.GetEntries())



        hsStack  = ROOT.THStack("Stack"+str(i)+str(j),"Stack"+str(i)+str(j))
        hsStack.Add(DibosonHisto); hsStack.Add(SingleTHisto); hsStack.Add(WJetsHisto); hsStack.Add(SignalHisto)
        hsStack.Write()
        #c.Draw(); c.SavePrimitive(PDFNames+"Stack"+str(i)+str(j)+".C")
        


        #TemHisto1.Draw()
    #del(TemHisto1)
    #Extracting Signal histogram
    #HistNameSig=HistName+"_Sig"
    #SigChain.Draw(HToExtract[i]+" >> "+HistNameSig+Binning[i],FullCut)
    #TemHisto2=ROOT.gDirectory.Get(HistNameSig)
    #EntriesListSignal.append(TemHisto2.GetEntries())
    #TemHisto2.Sumw2()
    #TemHisto2.Scale(1./TemHisto2.Integral())
    #TemHisto2.Write()
    #TemHisto2.Draw("same")
    #c.Draw()
    #print "one more step - SingleT entries=", EntriesListSingleT[-1]
    #print "Signal entries=", EntriesListSignal[-1]
    print "-----------------------------------------"
    #del(TemHisto2)

#print "SingleT cut flow:", EntriesListSingleT
#print "Signal cut flow:", EntriesListSignal

"""



