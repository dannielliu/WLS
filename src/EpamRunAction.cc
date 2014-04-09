//
//***************************************************************
//*DISCLAIMER                                                   *
//*                                                             *
//*                                     Created Jul.23, 2006    *
//***************************************************************
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "EpamRunAction.hh"
#include "EpamDetectorConstruction.hh"
#include "EpamDefs.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"

#include <string>
#include <vector>
#include <sys/time.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EpamRunAction::EpamRunAction( EpamDetectorConstruction* det ):
  detector(det)
{
  eventInfo.reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EpamRunAction::~EpamRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EpamRunAction::BeginOfRunAction(const G4Run* aRun)
{
  //G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Check Point:: Begin of 'BeginOfRunAction'" << G4endl;
  
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  runID = aRun->GetRunID();

  //gettimeofday( &startTime, &tz );

  // Inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Initialize output file
  epamDataFile = new TFile( "EpamData.root", (runID == 0) ? "RECREATE" : "UPDATE" );

  char mathematicaFileName[100];
  sprintf( mathematicaFileName, "r%03d.energies", aRun->GetRunID() );
  epamDataMatematicaEnergies = new std::ofstream( mathematicaFileName );
  sprintf( mathematicaFileName, "r%03d.filteredEnergies", aRun->GetRunID() );
  epamDataMatematicaEnergiesFiltered = new std::ofstream( mathematicaFileName );
  sprintf( mathematicaFileName, "r%03d.particles", aRun->GetRunID() );
  epamDataMatematicaParticleInformation = new std::ofstream( mathematicaFileName );

  // Initialize TTree
  char dataTreeName[100];
  sprintf( dataTreeName, "DataTree_run%03d", aRun->GetRunID() );
  char goodDataTreeName[100];
  sprintf( goodDataTreeName, "GoodDataTree_run%03d", aRun->GetRunID() );
  epamDataTree = new TTree( dataTreeName, "Information for all events." );
  epamGoodDataTree = new TTree( goodDataTreeName, "Information for good events." );


  char vars[2000] = "EDEP_visShieldF/D:EDEP_visShieldR/D:EDEP_SiLayer1F/D:EDEP_SiLayer2F/D:EDEP_SiLayer2R/D:EDEP_Cal/D:EDEP_SiLayerWE1F/D:EDEP_SiLayerWE2F/D:EDEP_SiLayerWE2R/D:EDEP_CalWE/D:EDEP_Total/D:PEN_visShieldF/I:PEN_visShieldR/I:PEN_SiLayer1F/I:PEN_SiLayer2R/I:PEN_SiLayer1R/I:PEN_Cal/I:INFO_Z/I:INFO_A/I:INFO_Mass/D:INFO_KineticEnergy/D:INFO_PosX/D:INFO_PosY/D:INFO_PosZ/D:INFO_DirX/D:INFO_DirY/D:INFO_DirZ/D:SEC_All/I:SEC_HE/I";
  //  G4cout << line << G4endl;
  epamDataTree->Branch( "AllEvents", &eventInfo, vars );
  epamGoodDataTree->Branch( "GoodEvents", &eventInfo, vars );

  //G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Check Point:: End of 'BeginOfRunAction'" << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EpamRunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CHECK POINT:: In 'EndOfRunAction' " << G4endl;

  aRun->GetRunID();
  epamDataTree->Write();
  //epamGoodDataTree->Write();
  epamDataFile->Close();
  G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CHECK POINT:: In 'EndOfRunAction' " << G4endl;
  //delete epamDataTree;
  //delete epamGoodDataTree;
  //delete epamDataFile;

  G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CHECK POINT:: In 'EndOfRunAction' " << G4endl;  
  *epamDataMatematicaEnergies << "}" << G4endl;
  epamDataMatematicaEnergies->close();
  //delete epamDataMatematicaEnergies;
  *epamDataMatematicaEnergiesFiltered << "}" << G4endl;
  epamDataMatematicaEnergies->close();
  //delete epamDataMatematicaEnergies;
  *epamDataMatematicaParticleInformation << "}" << G4endl;
  epamDataMatematicaParticleInformation->close();

  //  gettimeofday( &endTime, &tz );
  //G4cout << "!  Time Spent: " << G4BestUnit( ( endTime.tv_sec - startTime.tv_sec ) * 1000000000, "Time" ) << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
