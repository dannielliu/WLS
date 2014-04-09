
// =================================================================================
// HEADER
// =================================================================================

// epam_std.cc
// epam main .cc

// ================================================================================= 
// INCLUDES
// =================================================================================

// User Defined Standard G4 Program Components
#include "EpamDetectorConstruction.hh"
#include "EpamPhysicsList.hh"
#include "EpamPrimaryGeneratorAction.hh"
#include "EpamEventAction.hh"
#include "EpamSteppingAction.hh"
#include "EpamRunAction.hh"
#include "EpamDefs.hh"
#include "EpamStackingAction.hh"
#include "WLSTrackingAction.hh"

// Standard G4 Program Components
#include "G4RunManager.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
// G4 User Interface & Visualization
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
//#include "EpamVisManager.hh"

// Cpp Includes
#include <fstream>


// =================================================================================
// main()
// =================================================================================

int main(int argc, char** argv )
{
  //Random Engine
  //CLHEP::HepRandom::setTheEngine(new RanecuEngine);
	
  // Coustruct the default run manager
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  G4long seed = time(0)+getpid();
  CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::showEngineStatus();
  G4RunManager* runManager = new G4RunManager;

  // User Initializations
  EpamDetectorConstruction* EpamDetector = new EpamDetectorConstruction();
  EpamPhysicsList* EpamPhysics = new EpamPhysicsList( EpamDetector );
  runManager -> SetUserInitialization( EpamPhysics );
  runManager -> SetUserInitialization( EpamDetector );

  // User Action
  EpamRunAction* runAction = new EpamRunAction( EpamDetector );
  EpamEventAction* evtAction = new EpamEventAction( runAction );
  EpamSteppingAction* steppingAction = new EpamSteppingAction(EpamDetector, evtAction );
  EpamPrimaryGeneratorAction* primaryGenerator = new EpamPrimaryGeneratorAction( EpamDetector, evtAction );
  runManager->SetUserAction( runAction );
  runManager->SetUserAction( evtAction );
  runManager->SetUserAction( steppingAction );
  runManager->SetUserAction( primaryGenerator );
  runManager->SetUserAction( new WLSTrackingAction() );
  //runManager->SetUserAction( new WLSStackingAction() );

  G4UserStackingAction* stacking_action =
	                new EpamStackingAction(evtAction);
  runManager->SetUserAction(stacking_action);
  // Initialize G4 kernel
  runManager->Initialize();

  // Construct all particles, including heavy ions
  EpamPhysics->ConstructAllParticles();
  EpamPhysics->ShowParticleTable();
  
  //visualization manager
  G4VisManager* visManager = new G4VisExecutive;//EpamVisManager;
  visManager->Initialize();
		
  //get the pointer to the UI manager
  G4UImanager* UI = G4UImanager::GetUIpointer();
  if( argc == 1 )
    {
      //G4UIsession * session = 0;
      G4UIExecutive* session = new G4UIExecutive(argc,argv);;
      /*
#ifdef G4UI_USE_TCSH		
      session = new G4UIterminal( new G4UItcsh);
#else		
      //session = new G4UIterminal();
      session = new G4UIExecutive(argc,argv);
#endif	*/	
      UI->ApplyCommand("/control/execute vis.mac");

      session->SessionStart();
      delete session;
    }
  else{
	  G4String command = "/control/execute ";
	  G4String fileName = argv[1];
	  UI->ApplyCommand(command + fileName); 
	};

  //job termination
  delete EpamDetector;
  delete runManager;
  return 0;
}
