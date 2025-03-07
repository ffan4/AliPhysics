#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class AliAnalysisTaskCheckCascade+;
#pragma link C++ class AliAnalysisTaskCheckCascadePbPb+;
#pragma link C++ class AliAnalysisTaskCheckPerformanceCascade+;
#pragma link C++ class AliAnalysisTaskCheckPerformanceCascadePbPb+;
#pragma link C++ class AliAnalysisCentralitySelector+;
#pragma link C++ class AliAnalysisTaskCTauPbPb+;
#pragma link C++ class AliAnalysisTaskCTauPbPbaod+;
#pragma link C++ class AliAnalysisTaskLukeAOD+;
#pragma link C++ class AliAnalysisTaskLukeV0+;
#pragma link C++ class AliAnalysisTaskPerformanceStrange+;
#pragma link C++ class AliAnalysisTaskV0ForRAA+;
#pragma link C++ class AliAnalysisTaskExtractV0+;
#pragma link C++ class AliAnalysisTaskExtractV0pPb+;
#pragma link C++ class AliAnalysisTaskExtractV0AOD+;
#pragma link C++ class AliAnalysisTaskExtractV0AODRun2+;
#pragma link C++ class AliAnalysisTaskExtractPerformanceV0+;
#pragma link C++ class AliAnalysisTaskExtractPerformanceV0pPb+;
#pragma link C++ class AliAnalysisTaskLK0Spectra+;
#pragma link C++ class AliAnalysisTaskExtractCascade+;
#pragma link C++ class AliAnalysisTaskExtractCascadePbPbRun2+;
#pragma link C++ class AliAnalysisTaskExtractPerformanceCascade+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicity+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityMC+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityRun2+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityEERun2+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityAODRun2+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityRsnLikeBgSub+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityMCRun2+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityEEMCRun2+;
#pragma link C++ class AliTaskLeadingMC+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityRun2pPb+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultiplicityMCRun2pPb+;
#pragma link C++ class AliRunningCascadeCandidate+;
#pragma link C++ class AliRunningCascadeEvent+;
#pragma link C++ class AliAnalysisTaskStrangeCascadesDiscrete+;
#pragma link C++ class AliAnalysisTaskPPVsMultCrossCheckMC+;
#pragma link C++ class AliAnalysisTaskpANormalizationCheckMC+;
#pragma link C++ class AliAnalysisTaskLambdaOverK0sJets+;
#pragma link C++ class AliMiniParticle+;
#pragma link C++ class AliAnalysisTaskV0ChCorrelations+;
#pragma link C++ class AliAnalysisTaskhStrCorr+;
#pragma link C++ class AliV0ChBasicParticle+;
#pragma link C++ class AliAnalysisTaskCheckCascadepp+;
#pragma link C++ class AliAnalysisTaskCheckPerformanceCascadepp+;
#pragma link C++ class AliLightV0vertexer+;
#pragma link C++ class AliLightCascadeVertexer+;
#pragma link C++ class AliCascadeVertexerUncheckedCharges+;
#pragma link C++ class AliV0vertexerUncheckedCharges+;
#pragma link C++ class AliVWeakResult+;
#pragma link C++ class AliV0Result+;
#pragma link C++ class AliCascadeResult+;
#pragma link C++ class AliStrangenessModule+;
#pragma link C++ class AliAnalysisTaskWeakDecayVertexer+;
#pragma link C++ class AliAnalysisTaskStrEffStudy+;
#pragma link C++ class AliAnalysisTaskMCPredictions+;
#pragma link C++ class AliAnalysisTaskMCPredictionsEE+;
#pragma link C++ class AliAnalysisCorrelationEventCollection+;
#pragma link C++ class AliReconstructedFirstC+;
#pragma link C++ class AliReconstructedSecondC+;
#pragma link C++ class AliAnalysisCorrelationEvent+;
#pragma link C++ class AliAnalysisCorrelationEventCollection+;
#pragma link C++ class AliAnalysisTaskCorrelationhhK0s+;
#pragma link C++ class AliAnalysisTaskCorrelationhCasc+;
#pragma link C++ class AliAnalysisTaskCorrelationhCascDATA+;
#pragma link C++ class AliAnalysisTaskStrVsMult+;
#pragma link C++ class AliAnalysisTaskStrVsMult_BumpStudies+;
#pragma link C++ class AliAnalysisTaskStrVsMult_PileUpStudies+;
#pragma link C++ class AliAnalysisTaskStrVsMult_SelectionStudies+;
#pragma link C++ class AliEventContainer+;
#pragma link C++ class AliCascadeContainer+;
#pragma link C++ class AliV0Container+;
#pragma link C++ class AliTrackInfoContainer+;
#pragma link C++ class AliAnalysisTaskStrangeCascadesTriggerAODRun2+;
#pragma link C++ class AliMCEventContainer+;
#pragma link C++ class AliMCCascadeContainer+;
#pragma link C++ class AliMCV0Container+;
#pragma link C++ class AliMCTrackInfoContainer+;
#pragma link C++ class AliMCGenParticleContainer+;
#pragma link C++ class AliAnalysisTaskStrangeCascadesTriggerAODRun2MC+;
#pragma link C++ class AliAnalysisTaskV0multspec+;
#pragma link C++ class AliAnalysisTaskXiNucleusInteraction+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultVsEffEnergyAODRun2+;
#pragma link C++ class AliAnalysisTaskStrangenessVsMultVsEffEnergyAODMCRun2+;
//#pragma link C++ class AliRunningCascadeEvent+;
//#pragma link C++ class AliRunningCascadeTrack+;
#endif

#ifdef __CLING__
#pragma link C++ class Event+;
#pragma link C++ class std::vector<AliESDtrack>+;
#pragma link C++ class AliAnalysisTaskStrangenessRatios+;
#pragma link C++ class MiniCascade+;
#pragma link C++ class MiniCascadeMC+;
#pragma link C++ class MiniLambda+;
#pragma link C++ class MiniLambdaMC+;
#pragma link C++ class V0filler+;
#pragma link C++ class Cascfiller+;
//#pragma link C++ class std::vector<FindableHyperTriton<2>>+;
//#pragma link C++ class std::vector<FindableHyperTriton<3>>+;
#endif
