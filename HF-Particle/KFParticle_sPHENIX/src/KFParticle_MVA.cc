/**********************************/
/*  Program to arrange, init,     */
/*   and calc an MVA response     */
/*   Cameron Dean, LANL, 06/15/20 */
/**********************************/
#include <KFPVertex.h>
#include <KFParticle.h>

#include "KFParticle_MVA.h"
#include "KFParticle_Tools.h"

using namespace std;

KFParticle_MVA::KFParticle_MVA()
  : m_nPars(1)
  , m_mva_variable_list()
  , m_mva_type()
  , m_mva_path()
{
}

KFParticle_MVA::~KFParticle_MVA() {}

KFParticle_Tools kfpTools;

tuple<TMVA::Reader *, vector<Float_t>> KFParticle_MVA::initMVA()
{
  TMVA::Tools::Instance();  //Start TMVA
  TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

  vector<Float_t> reader_floats;

  for (unsigned int i = 0; i < nMVApars; ++i)
  {
    reader_floats.push_back(0);
    reader->AddVariable(m_mva_variable_list[i].c_str(), &reader_floats[i]);
  }
  reader->BookMVA(method.c_str(), m_mva_path.c_str());

  return make_tuple(reader, reader_floats);
}

Float_t KFParticle_MVA::evaluateMVA(TMVA::Reader *reader, vector<Float_t> reader_floats, KFParticle particle, KFPVertex vertex)
{
  KFParticle kfpvertex(vertex);
  map<string, float> possibleVariables =
      {
          {"motherIPchi2", particle.GetDeviationFromVertex(kfpvertex)},
          {"motherFDchi2", kfpTools.flightDistanceChi2(particle, vertex)}};

  for (unsigned int iPar = 0; iPar < nMVApars; ++iPar) reader_floats[iPar] = possibleVariables.find(m_mva_variable_list[iPar])->second;

  return (Float_t) reader->EvaluateMVA(method.c_str());
}