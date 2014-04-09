//
//***************************************************************
//*DISCLAIMER							*
//*								*
//*				Created Jul.15, 2006		*
//***************************************************************
//
//path : epam/src/EpamPrimaryGeneratorAction.cc
//

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "EpamPrimaryGeneratorAction.hh"

#include "EpamDetectorConstruction.hh"
#include "EpamEventAction.hh"
#include "EpamRunAction.hh"
#include "EpamDefs.hh"

#include "G4ParticleGun.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GeneralParticleSourceMessenger.hh"
#include "G4SingleParticleSource.hh"
#include "G4SPSPosDistribution.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSRandomGenerator.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"

#include "globals.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

EpamPrimaryGeneratorAction::EpamPrimaryGeneratorAction( EpamDetectorConstruction* myDetec,
                                                        EpamEventAction* myEvt):
  //  generalParticleSource( 0 ),
  detector( myDetec ),
  eventaction( myEvt )
  //  shootMode( SHOOT_MODE_VERTICLE_BEAM ),
  //selectMode( SELECT_MODE_ONLY_PROTON ),
  //energyLowerBound( LOWER_ENERGY_BOUND ),
  //energyUpperBound( UPPER_ENERGY_BOUND )
{
  // Set Default Particle Gun
  generalParticleSource = new G4GeneralParticleSource();
  //  generalParticleSourceMessenger = new G4GeneralParticleSourceMessenger( generalParticleSource );

  //  particleGun = new G4GeneralParticleSource();
  //  particleGun->SetParticleDefinition( G4ParticleTable::GetParticleTable()->FindParticle( "proton" ) );
  //  particleGun->SetParticleMomentumDirection( G4ParticleMomentum( 0, 0, 1 ) );
  //  particleGun->SetParticlePosition( G4ThreeVector( 0, 0, -45*mm ) );
  //  particleGun->SetParticleEnergy( 50*MeV );
  
  
} // :::: End of EpamPrimaryGeneratorAction::EpamPrimaryGeneratorAction()

EpamPrimaryGeneratorAction::~EpamPrimaryGeneratorAction()
{
  //delete generalParticleSource;
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // ****** This method will be invoked at the begining of each event

  if( anEvent->GetEventID() == 0 ){
    /*
    G4ParticleTable* theParticleTable = G4ParticleTable::GetParticleTable();
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand( "/generator/select gps" );
    UI->ApplyCommand( "/gps/source/clear" );
    UI->ApplyCommand( "/gps/source/add 1" );

    UI->ApplyCommand( "/gps/particle proton" );
    UI->ApplyCommand( "/gps/pos/type Point" );
    UI->ApplyCommand( "/gps/pos/center 0 0 40 mm" );
    UI->ApplyCommand( "/gps/ang/type planar" );
    UI->ApplyCommand( "/gps/ang/rot1 0 0 -1" );
    UI->ApplyCommand( "/gps/ene/type Lin" );
    UI->ApplyCommand( "/gps/ene/min 60 MeV" );
    UI->ApplyCommand( "/gps/ene/max 70 MeV" );
    */
    
    /*
    //    generalParticleSource->ClearAll();
    //    generalParticleSource->AddaSource(1);
    
    // Print information on first event
    G4cout << "#**************** Primary Generator Information ****************#" << G4endl;

    G4cout << "+--Particle Select Mode: ";
    switch( selectMode ){
    case SELECT_MODE_ONLY_PROTON:
      G4cout << "Only proton." << G4endl;
      break;
    case SELECT_MODE_ONLY_ELECTRON:
      G4cout << "Only electron." << G4endl;
      break;
    case SELECT_MODE_PROTON_AND_ELECTRON:
      G4cout << "Electron & Proton." << G4endl;
      break;
    case SELECT_MODE_ISOTOPE_H:
      G4cout << "Isotopes of H." << G4endl;
      break;
    case SELECT_MODE_ISOTOPE_HE:
      G4cout << "Isotopes of He." << G4endl;
      break;
    case SELECT_MODE_ISOTOPE_TILL_C:
      G4cout << "Elements no heavier than C." << G4endl;
      break;
    case SELECT_MODE_ISOTOPE_TILL_SI:
      G4cout << "Elements no heavier than Si." << G4endl;
      break;
    case SELECT_MODE_ISOTOPE_TILL_FE:
      G4cout << "Elements no heavier than Fe." << G4endl;
      break;
    case SELECT_MODE_POSITRON:
      G4cout << "Only Positron." << G4endl;
      break;
    case SELECT_MODE_ANTI_PROTON:
      G4cout << "Only Anti-proton." << G4endl;
      break;
    default:
      G4int particleZ = int( selectMode / 100. );
      G4int particleA = selectMode - particleZ*100;
      G4ParticleDefinition* particle = theParticleTable->FindIon( particleZ, particleA, 0.0 );
      if( particle != NULL ){
        G4cout << "Only shoot " << particle->GetParticleTable() << G4endl;
      }
      else{
        G4cout << "Wrong Particle Choice Code: " << selectMode << ". Exiting..." << G4endl;
        exit(1);
      }
    } // :::: End of printing Information

    // Set Particle Sources regarding to SELECT_MODE
    G4bool ifGenerateASeriesOfNucleus = false;
    G4int heaviestNucleusToGenerate = 0;

    G4int EpamNucleis[][2] = 
      {
        { 1, 1 }, { 1, 2 }, { 1, 3 },
        { 2, 3 }, { 2, 4 },
        { 3, 6 }, { 3, 7 },
        { 4, 7 }, { 4, 9 }, { 4, 10 },
        { 5, 10 }, { 5, 11 },
        { 6, 12 }, { 6, 13 }, { 6, 14 },
        { 7, 14 }, { 7, 15 },
        { 8, 16 }, { 8, 17 }, { 8, 18 },
        { 9, 18 }, { 9, 19 },
        { 10, 20 }, { 10, 21 }, { 10, 22 },
        { 11, 22 }, { 11, 23 },
        { 12, 24 }, { 12, 25 }, { 12, 26 }, { 12, 28 },
        { 13, 26 }, { 13, 27 },
        { 14, 28 }, { 14, 29 }, { 14, 30 }, { 14, 31 },
        { 15, 30 }, { 15, 31 }, { 15, 32 }, { 15, 33 },
        { 16, 32 }, { 16, 33 }, { 16, 34 }, { 16, 35 }, { 16, 36 }, { 16, 37 },
        { 17, 34 }, { 17, 35 }, { 17, 36 }, { 17, 37 }, { 17, 38 }, { 17, 39 }, { 17, 40 },
        { 18, 36 }, { 18, 37 }, { 18, 38 }, { 18, 39 }, { 18, 40 }, { 18, 42 }, { 18, 43 },
        { 19, 38 }, { 19, 39 }, { 19, 40 }, { 19, 41 }, { 19, 44 }, { 19, 45 },
        { 20, 40 }, { 20, 41 }, { 20, 42 }, { 20, 43 }, { 20, 44 }, { 20, 45 }, { 20, 46 }, { 20, 47 }, { 20, 48 }, { 20, 49 },
        { 21, 44 }, { 21, 45 }, { 21, 46 }, { 21, 47 }, { 21, 48 }, { 21, 49 }, { 21, 50 },
        { 22, 44 }, { 22, 46 }, { 22, 47 }, { 22, 48 }, { 22, 49 }, { 22, 50 }, { 22, 51 }, { 22, 52 },
        { 23, 47 }, { 23, 48 }, { 23, 49 }, { 23, 50 }, { 23, 51 }, { 23, 51 }, { 23, 52 }, { 23, 53 },
        { 24, 49 }, { 24, 50 }, { 24, 51 }, { 24, 52 }, { 24, 53 }, { 24, 54 }, { 24, 55 }, { 24, 56 },
        { 25, 52 }, { 25, 53 }, { 25, 54 }, { 25, 55 }, { 25, 56 }, { 25, 57 },
        { 26, 52 }, { 26, 54 }, { 26, 55 }, { 26, 56 }, { 26, 57 }, { 26, 58 }, { 26, 59 }, { 26, 60 },
        { 27, 55 }, { 27, 56 }, { 27, 57 }, { 27, 58 }, { 27, 59 }, { 27, 60 }, { 27, 61 },
        { INT_MAX, INT_MAX }
      };

    switch( selectMode ){
    case SELECT_MODE_ONLY_PROTON:
      //      G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CHECK POINT:: PrimaryGeneratorAction" << G4endl;
      //      G4cout << (G4long) theParticleTable->FindParticle( "proton" ) << G4endl;
      //      G4ParticleDefinition* aP = theParticleTable->FindParticle( "proton" );
      //      G4cout << aP->GetPDGEncoding() << G4endl;

      UI->ApplyCommand( "/gps/particle proton" );
      
      //      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "proton" ) );
      break;
    case SELECT_MODE_ONLY_ELECTRON:
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "e-" ) );      
      break;
    case SELECT_MODE_PROTON_AND_ELECTRON:
      generalParticleSource->SetCurrentSourceIntensity( 0.5 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "proton" ) );
      generalParticleSource->AddaSource( 0.5 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "e-" ) );
      break;
    case SELECT_MODE_ISOTOPE_H:
      generalParticleSource->SetCurrentSourceIntensity( 1 / 3.0 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "proton" ) );
      generalParticleSource->AddaSource( 1 / 3.0 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "deutron" ) );
      generalParticleSource->AddaSource( 1 / 3.0 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "triton" ) );
      break;
    case SELECT_MODE_ISOTOPE_HE:
      generalParticleSource->SetCurrentSourceIntensity( 1 / 2.0 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "He3" ) );
      generalParticleSource->AddaSource( 1 / 2.0 );
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "alpha" ) );
      break;
    case SELECT_MODE_ISOTOPE_TILL_C:
      ifGenerateASeriesOfNucleus = true;
      heaviestNucleusToGenerate = 6;
      break;
    case SELECT_MODE_ISOTOPE_TILL_SI:
      ifGenerateASeriesOfNucleus = true;
      heaviestNucleusToGenerate = 14;
      break;
    case SELECT_MODE_ISOTOPE_TILL_FE:
      ifGenerateASeriesOfNucleus = true;
      heaviestNucleusToGenerate = 28;
      break;
    case SELECT_MODE_POSITRON:
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "e+" ) );
      break;
    case SELECT_MODE_ANTI_PROTON:
      generalParticleSource->SetParticleDefinition( theParticleTable->FindParticle( "anti_proton" ) );
      break;
    default:
      G4int particleZ = (int)( selectMode / 100. );
      G4int particleA = selectMode - particleZ*100;
      generalParticleSource->SetParticleDefinition( theParticleTable->FindIon( particleZ, particleA, 0.0 ) );
    } // :::: End of Switching selectMode
    
    G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CHECK POINT:: PrimaryGeneratorAction" << G4endl;

    if( ifGenerateASeriesOfNucleus == true ){
      generalParticleSource->SetCurrentSourceIntensity( 1.0 );
      for( G4int ptr = 0; EpamNucleis[ptr][0] <= heaviestNucleusToGenerate; ptr++ ){
        generalParticleSource->AddaSource( 1.0 );
        generalParticleSource->SetParticleDefinition( theParticleTable->FindIon( EpamNucleis[ptr][0], EpamNucleis[ptr][1], 0.0 ) );
      }
    } // :::: End of Setting Select Mode

    G4cout << "+--Primary Particle Souce Type: ";
    
    // Set Source Mode & Particle Energy
    G4int numberOfSources = generalParticleSource->GetNumberofSource();
    for( G4int sourceIndex = 0; sourceIndex < numberOfSources; sourceIndex++ ){
      G4SPSPosDistribution* posDistribute = 0;
      G4SPSAngDistribution* angDistribution = 0;
      
      // Set Source Mode
      switch( shootMode ){
      case SHOOT_MODE_VERTICLE_BEAM:
        //        posDistribute = generalParticleSource->GetCurrentSource()->GetPosDist();
        //        posDistribute->SetPosDisType( "Point" );
        //        posDistribute->SetCentreCoords( G4ThreeVector( 0.0, 0.0, (-0.5)*WORLD_DIAM ) );
                
        //        angDistribution = generalParticleSource->GetCurrentSource()->GetAngDist();
        //        angDistribution->SetAngDistType( "planar" );

        //        G4cout << "Beam" << G4endl;

        UI->ApplyCommand( "/gps/pos/type Point" );
        UI->ApplyCommand( "/gps/pos/center 0.0 0.0 -49.0 mm" );
        UI->ApplyCommand( "/gps/ang/type planar" );
        UI->ApplyCommand( "/gps/ang/rot1 0 0 1" );

        break;
      case SHOOT_MODE_THROUGH_WINDOW:
        posDistribute = generalParticleSource->GetCurrentSource()->GetPosDist();
        posDistribute->SetPosDisType( "Plane" );
        posDistribute->SetPosDisShape( "Circle" );
        posDistribute->SetCentreCoords( G4ThreeVector( 0.0, 0.0, FE_COLLIMATOR_CENTER_POSITION - ( FE_COLLIMATOR_PART_ONE_THICKNESS + FE_COLLIMATOR_PART_TWO_THICKNESS + FE_COLLIMATOR_PART_THREE_THICKNESS ) / 2.0 ) );
        posDistribute->SetRadius( CORE_DIAM / 2.0 );

        angDistribution = generalParticleSource->GetCurrentSource()->GetAngDist();
        angDistribution->SetAngDistType( "cos" );
        angDistribution->SetMaxTheta( 30*degree );

        G4cout << "Limited Angle Isotropic" << G4endl;

        break;
      case SHOOT_MODE_ISOTROPIC:
        posDistribute = generalParticleSource->GetCurrentSource()->GetPosDist();
        posDistribute->SetPosDisShape( "Surface" );
        posDistribute->SetPosDisType( "Sphere" );
        posDistribute->SetCentreCoords( G4ThreeVector( 0.0, 0.0, 0.0 ) );
        posDistribute->SetRadius( WORLD_DIAM / 2.0 - 1*cm );

        angDistribution = generalParticleSource->GetCurrentSource()->GetAngDist();
        angDistribution->SetAngDistType( "iso" );

        G4cout << "Isotropic" << G4endl;

        break;
      } // ::::End of Selecting shootMode
      // Set Particle Energy
      //      G4SPSEneDistribution* eneDistribution = generalParticleSource->GetCurrentSource()->GetEneDist();
      //      eneDistribution->SetEnergyDisType( "Lin" );
      UI->ApplyCommand( "/gps/ene/type Lin" );
      G4double particleBaryonNumber = generalParticleSource->GetParticleDefinition()->GetBaryonNumber();
      G4double eMin = energyLowerBound * ( particleBaryonNumber ? particleBaryonNumber : 1 );
      G4double eMax = energyUpperBound * ( particleBaryonNumber ? particleBaryonNumber : 1 );
      //      eneDistribution->SetEmin( 50*MeV );
      //      eneDistribution->SetEmax( 60*MeV );
      UI->ApplyCommand( "/gps/ene/min 50 MeV" );
      UI->ApplyCommand( "/gps/ene/max 60 MeV" );
      

      G4cout << "+--Particle Energy (Kinetic) is from " << G4BestUnit( eMin, "Energy" ) << " to " << G4BestUnit( eMax, "Energy" ) << "(/Nuclei)" << G4endl;
      
    } // :::: End of 'for'
  */
  } // :::: End of first event

  generalParticleSource->GeneratePrimaryVertex( anEvent );
  
  //generalParticleSource->GeneratePrimaryVertex( anEvent );
  //  G4cout << "&&&&&&&" << G4endl;
  
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

