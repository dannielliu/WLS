
//***************************************************************
//*DISCLAIMER							*
//*								*
//*				Created Jul.15, 2006		*
//***************************************************************
//
//path: epam/src/EpamPhysicsList.cc
// 

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#include <fstream>

#include "EpamPhysicsList.hh"
#include "EpamDetectorConstruction.hh"
#include "EpamDefs.hh"

#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4VProcess.hh"

#include "G4LeptonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

#include "G4ios.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"

  // Gamma
//#include "G4PhotoElectricEffect.hh"
//#include "G4ComptonScattering.hh"
//#include "G4GammaConversion.hh"

  //   // e+/e-
//#include "G4eIonisation.hh"
//#include "G4eBremsstrahlung.hh"
//#include "G4eplusAnnihilation.hh" 

  // Gamma
//#include "G4LowEnergyRayleigh.hh" 
//#include "G4LowEnergyPhotoElectric.hh"
//#include "G4LowEnergyCompton.hh"  
//#include "G4LowEnergyGammaConversion.hh"
  // e-
//#include "G4LowEnergyIonisation.hh"
//#include "G4LowEnergyBremsstrahlung.hh" 

  // e+
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

  // muons
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"

  // hadrons and ions
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

EpamPhysicsList::EpamPhysicsList( EpamDetectorConstruction* det): G4VUserPhysicsList()
{
  detector = det;
  VerboseLevel = 1;
  OpVerbLevel = 0;
  SetVerboseLevel(0);
}

EpamPhysicsList::~EpamPhysicsList()
{
}


//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::ConstructParticle()
{  

//#################should be check########################  

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructIons();
  ConstructShortLiveds();

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

  /*
  // Construct Leptons and Gamma
  G4LeptonConstructor leptonConstructor;
  leptonConstructor.ConstructParticle( );

  // Construct Baryons
  G4BaryonConstructor baryonConstructor;
  baryonConstructor.ConstructParticle( );
  */

  // Construct Light Ions, including He4, H2, H3, He3
  G4IonConstructor ionConstructor;
  ionConstructor.ConstructParticle( );
  
  // +++ Construction of other heavy nuclei will be invoked in
  // +++ main( ) by EpamPhysicsList::ConstructHeavyIons( )

 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamPhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamPhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamPhysicsList::ConstructMesons()
{
 //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamPhysicsList::ConstructBaryons()
{
//  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::ConstructIons()
{
//  Ions
  G4Deuteron::DeuteronDefinition();
  G4Triton::TritonDefinition();
  G4He3::He3Definition();
  G4Alpha::AlphaDefinition();
  G4GenericIon::GenericIonDefinition();
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::ConstructShortLiveds()
{
  // ShortLiveds
  ;
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::ConstructProcess()
{
  AddTransportation();

  ConstructEM();

  ConstructOp();

  //ConstructHad();

  ConstructGeneral();
}


// Transportation ///////////////////////////////////////////////////////////
//#include "EpamMaxTimeCuts.hh"
//#include "EpamMinEkineCuts.hh"
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void EpamPhysicsList::AddTransportation() {
  
  G4VUserPhysicsList::AddTransportation();
  
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    // time cuts for ONLY neutrons:
    //if(particleName == "neutron") 
    //pmanager->AddDiscreteProcess(new EpamMaxTimeCuts());
    // Energy cuts to kill charged (embedded in method) particles:
    //pmanager->AddDiscreteProcess(new EpamMinEkineCuts());
  }		      
}
*/
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"


#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
     
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4hIonisation,       -1, 2,2);
      //step limit
      pmanager->AddProcess(new G4StepLimiter,       -1,-1,3);         
      ///pmanager->AddProcess(new G4UserSpecialCuts,   -1,-1,4);  
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



// Optical Processes ////////////////////////////////////////////////////////
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
#include "G4OpWLS.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4ProcessManager.hh"
#include "G4OpMieHG.hh"
void EpamPhysicsList::ConstructOp() 
{
  G4cout << "WLSOpticalPhysics:: Add Optical Physics Processes"
           << G4endl;

  G4OpWLS* theWLSProcess = new G4OpWLS();

  G4Scintillation* theScintProcess = new G4Scintillation();
  theScintProcess->SetScintillationYieldFactor(1.);
  theScintProcess->SetTrackSecondariesFirst(true);

  G4Cerenkov* theCerenkovProcess = new G4Cerenkov();
  theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  theCerenkovProcess->SetTrackSecondariesFirst(true);

  G4OpAbsorption* theAbsorptionProcess      = new G4OpAbsorption();
  G4OpRayleigh* theRayleighScattering     = new G4OpRayleigh();
  G4OpMieHG* theMieHGScatteringProcess = new G4OpMieHG();
  G4OpBoundaryProcess*   theBoundaryProcess        = new G4OpBoundaryProcess();

  G4ProcessManager* pManager =
                G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

  if (!pManager) {
     std::ostringstream o;
     o << "Optical Photon without a Process Manager";
     G4Exception("WLSOpticalPhysics::ConstructProcess()","",
                  FatalException,o.str().c_str());
  }

//if (AbsorptionOn) 
    pManager->AddDiscreteProcess(theAbsorptionProcess);

  //pManager->AddDiscreteProcess(theRayleighScattering);
  //pManager->AddDiscreteProcess(theMieHGScatteringProcess);

  pManager->AddDiscreteProcess(theBoundaryProcess);

  theWLSProcess->UseTimeProfile("delta");
  //theWLSProcess->UseTimeProfile("exponential");

  pManager->AddDiscreteProcess(theWLSProcess);

  theScintProcess->SetScintillationYieldFactor(1.);
  theScintProcess->SetScintillationExcitationRatio(0.0);
  theScintProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theScintProcess->AddSaturation(emSaturation);

  theParticleIterator->reset();
  while ( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    pManager = particle->GetProcessManager();
    if (!pManager) {
       std::ostringstream o;
       o << "Particle " << particleName << "without a Process Manager";
       G4Exception("WLSOpticalPhysics::ConstructProcess()","",
                    FatalException,o.str().c_str());
    }

    if(theCerenkovProcess->IsApplicable(*particle)){
      pManager->AddProcess(theCerenkovProcess);
      pManager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
    }
    if(theScintProcess->IsApplicable(*particle)){
      pManager->AddProcess(theScintProcess);
      pManager->SetProcessOrderingToLast(theScintProcess,idxAtRest);
      pManager->SetProcessOrderingToLast(theScintProcess,idxPostStep);
    }

  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

void EpamPhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::SetCuts()
{
  // ================================================================ This part should be checked again.
  //G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange( 250.0*eV, 100000.0*GeV );

  G4double cutVal = 1*mm;
  SetCutValue( cutVal, "gamma" );
  SetCutValue( cutVal, "e-" );
  SetCutValue( cutVal, "e+" );

  // SetCutsWithDefault();
  
  
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
	
void EpamPhysicsList::ConstructAllParticles()
{

}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamPhysicsList::ShowParticleTable()
{
  /*
  G4cout << G4endl;
  G4cout << "#**************** Epam Particle Table ****************#" << G4endl;
  
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();

    G4cout << "+--";
    G4cout << particle->GetParticleName() << G4endl;
    G4cout << "+----PDGCode:  " << particle->GetPDGEncoding() << G4endl;
    G4cout << "+----Type:     " << particle->GetParticleType() << G4endl;
    G4cout << "+----Charge:   " << particle->GetPDGCharge() << G4endl;
    G4cout << "+----Mass:     " << G4BestUnit( particle->GetPDGMass(), "Energy" ) << G4endl;
    G4cout << "+----B Number: " << particle->GetBaryonNumber() << G4endl;
    G4cout << "+----Lifetime: " << G4BestUnit( particle->GetPDGLifeTime(), "Time" ) << ( particle->IsShortLived() ? "?" : "" ) << G4endl;

    G4cout << "+----Physics Processes (" ;

    G4ProcessVector* processVector = particle->GetProcessManager()->GetProcessList();
    G4cout << processVector->entries() << " Processes): " << G4endl;
    for( G4int processPtr = 0; processPtr < processVector->entries(); processPtr++ ){
      G4cout << "+----------" << processVector->operator[]( processPtr )->GetProcessName() << G4endl;
    }

    G4cout << G4endl;
  }
  */
  ;
}

