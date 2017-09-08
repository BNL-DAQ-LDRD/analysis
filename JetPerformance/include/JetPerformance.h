#ifndef __JETPERFORMANCE_H__
#define __JETPERFORMANCE_H__


#include <fun4all/SubsysReco.h>
#include <vector>

#include <TTree.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

static const double ptbins[] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0,
				20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0,
				38.0, 40.0, 42.0, 44.0, 46.0, 48.0, 50.0, 52.0, 54.0,
				56.0, 58.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0,
				74.0, 76.0, 78.0, 80.0, 82.0, 84.0, 86.0, 88.0, 90.0,
				92.0, 94.0, 96.0, 98.0, 100.0};
static const int ptbins_int[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26,
				 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52,
				 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78,
				 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
static const int nbins_pt = sizeof(ptbins)/sizeof(double) -1;

static const double etabins[] = {-1., -0.6, -0.3, 0.3, 0.6, 1.};
static const int nbins_eta = sizeof(etabins)/sizeof(double) -1;  


const float pi2 = -1.5707963;
const float threepi2 = 4.71238898;
const float pi = 3.1415926;


class PHCompositeNode;
class RawClusterContainer;
class RawCluster;
class SvtxTrackMap;
class JetMap;
class JetEvalStack;
class JetRecoEval;
class JetPerformance: public SubsysReco
{

 public:
  
  JetPerformance(const std::string &name="jetperformance_analysis.root");
  double isoconeradius,mincluspt;
  int Init(PHCompositeNode*);
  int process_event(PHCompositeNode*);
  int End(PHCompositeNode*);


 private:

  void Set_Tree_Branches();
 
  TFile *file;
  TTree *tree;
  TTree *truthjettree;
  TTree *recojettree;
  TH1F * hRecoJetpT;
  TH1F * hGenJetpT;
  TH1F * hRecoJeteta;
  TH1F * hGenJeteta;
  TH1F * hRecoJetphi;
  TH1F * hGenJetphi;
  TH1F * hRecoGenJetdelR;
  TH1F * hJER[nbins_pt][nbins_eta];
  TH1F * hJER_allpT_allEta;
  TH1F * hJES_Mean_jtpt[nbins_eta];  
  TH1F * hJES_Sigma_jtpt[nbins_eta];  
  TH1F * hJES_Mean_jteta[nbins_pt];
  TH1F * hJES_Sigma_jteta[nbins_pt];
  
  
  std::string outfilename;

  int nevents;
  TH1F *histo;

  //all truth jets
  float truthjetpt;
  float truthjetpx,truthjetpy,truthjetpz;
  float truthjetphi;
  float truthjeteta;
  float truthjetmass;
  float truthjetp;
  float truthjetenergy;

  //all reco jets
  float recojetpt;
  float recojetpx,recojetpy,recojetpz;
  float recojetphi;
  float recojeteta;
  float recojetmass;
  float recojetp;
  float recojetenergy;
  float recojetid;
  float truthjetid;
  float recogenpTratio;
  float delRrecotruth;
  

};

#endif // __JETPERFORMANCE_H__
