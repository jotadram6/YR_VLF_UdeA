from Generic import *
import CMS_lumi, tdrstyle
CMS_lumi.cmsText = "CMS"
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_14TeV = "3000 fb^{-1}"
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


BasePath="/home/joser/VLF_YR/MergedRootFiles_20180525/"

#Signal

SigChain=ROOT.TChain("Delphes")
SigChain.Add(BasePath+"MF100_MS80_BR_1_0_PU0_part10_ntuple.root")
SigChain.Add(BasePath+"MF100_MS80_BR_1_0_PU0_part21_ntuple.root")

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

SignalEvents=30465+30452
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

TTbarRejection="(NJets<3)"
LowPTMuonRejection="((muon1Pt>10)&&(muon2Pt>5))"
DYRejection="((muon1Pt<30)&&(muon2Pt<30))"
TriggerOnly=LowPTMuonRejection
Cut1=LowPTMuonRejection+"&&"+TTbarRejection
Cut2=LowPTMuonRejection+"&&"+TTbarRejection+"&&"+DYRejection

CutFlow=[TriggerOnly,Cut1,Cut2]

VariablesForPlotting=["MET","jet1Pt","muon1Pt","muon2Pt","MT12"]
OptBinning=["(40,0,400)","(20,0,200)","(80,0,160)","(50,0,100)","(60,0,600)"]
XAxis=["p_{T}^{miss} [GeV]","p_{T}(j_{1}) [GeV]","p_{T}(#mu_{1}) [GeV]","p_{T}(#mu_{2}) [GeV]","M_{T}^{1,2} [GeV]"]


TIMEStr=time.strftime("%H_%M_%S")
PDFNames="Results_TwoMuonChannel_"+TIMEStr
print "Plotting on:", PDFNames
HistFile= ROOT.TFile(PDFNames+".root", "recreate")

for j in xrange(len(CutFlow)):
    for i in xrange(len(VariablesForPlotting)):
        HistName=VariablesForPlotting[i].replace("(","").replace(")","").replace("[","").replace("]","").replace(":","").replace(".","").replace("-","m").replace("+","p").replace(" ","_").replace("&","_and_").replace("&&","_and_").replace("*","_times_").replace(">","g").replace("<","l").replace(",","l").replace("/","d")+"_Cut"+str(j)
        print "Extracting "+VariablesForPlotting[i]
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
        SigChain.Draw(VariablesForPlotting[i]+" >> "+HistNameSignal+OptBinning[i],CutFlow[j])
        W0Jetschain.Draw(VariablesForPlotting[i]+" >> "+HistNameW0Jets+OptBinning[i],CutFlow[j])
        W1Jetschain.Draw(VariablesForPlotting[i]+" >> "+HistNameW1Jets+OptBinning[i],CutFlow[j])
        W2Jetschain.Draw(VariablesForPlotting[i]+" >> "+HistNameW2Jets+OptBinning[i],CutFlow[j])
        W3Jetschain.Draw(VariablesForPlotting[i]+" >> "+HistNameW3Jets+OptBinning[i],CutFlow[j])
        TTchain.Draw(VariablesForPlotting[i]+" >> "+HistNameTT+OptBinning[i],CutFlow[j])
        DY0chain.Draw(VariablesForPlotting[i]+" >> "+HistNameDY0+OptBinning[i],CutFlow[j])
        DY1chain.Draw(VariablesForPlotting[i]+" >> "+HistNameDY1+OptBinning[i],CutFlow[j])
        DY2chain.Draw(VariablesForPlotting[i]+" >> "+HistNameDY2+OptBinning[i],CutFlow[j])
        DY3chain.Draw(VariablesForPlotting[i]+" >> "+HistNameDY3+OptBinning[i],CutFlow[j])
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

        #SignalHisto.SetLineColor(ROOT.kSpring); SignalHisto.SetFillStyle(0); SignalHisto.SetLineWidth(2)
        #FullDY.SetFillColor(ROOT.kOrange)
        #TTHisto.SetFillColor(ROOT.kRed)
        #FullW.SetFillColor(ROOT.kBlue)
        SignalHisto.GetXaxis().SetTitle(XAxis[i]); FullDY.GetXaxis().SetTitle(XAxis[i]); FullW.GetXaxis().SetTitle(XAxis[i]); TTHisto.GetXaxis().SetTitle(XAxis[i])
        SignalHisto.SetTitle(""); FullDY.SetTitle(""); FullW.SetTitle(""); TTHisto.SetTitle("")
        SetCos(SignalHisto,ROOT.kSpring,0,ROOT.kSpring,2,1,1)
        SetCos(FullDY,ROOT.kOrange,1001,ROOT.kOrange,2,1,1)
        SetCos(FullW,ROOT.kBlue,1001,ROOT.kBlue,2,1,1)
        SetCos(TTHisto,ROOT.kRed,1001,ROOT.kRed,2,1,1)
        hs = ROOT.THStack("Stack_"+HistName,"")
        hs.Add(TTHisto)
        hs.Add(FullW)
        hs.Add(FullDY)

        #MyCanvas=ROOT.TCanvas("Canvas_"+HistName, "", 800, 800)
        MyCanvas=YOURcanvas("Canvas_"+HistName)
        CMS_lumi.cmsText = "CMS"
        CMS_lumi.extraText = "Preliminary"
        CMS_lumi.lumi_14TeV = "3000 fb^{-1}"
        tdrstyle.setTDRStyle()
        MyCanvas.cd()
        hs.Draw("hist")
        hs.GetXaxis().SetTitle(XAxis[i])
        hs.GetYaxis().SetTitle("Events")
        SignalHisto.Draw("hist same")
        hs.Write()
        CMS_lumi.CMS_lumi(MyCanvas,14,22)
        MyCanvas.Update()
        MyCanvas.Write()
        MyCanvas.Close()        
        
        if i==0 and j==0:
            print "-----------------Cut flow table---------------------"
            print "------S------DY------TT------W-------"
        if i==0:
            print "------%.2f------%.2f------%.2f------%.2f-------" % (SignalHisto.Integral(),FullDY.Integral(),TTHisto.Integral(),FullW.Integral())

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
    

HistFile.Close()




