//
//***************************************************************
//*DISCLAIMER                                                   *
//*                                                             *
//*                                     Created Jul.19, 2006    *
//***************************************************************
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "EpamEventAction.hh"
#include "EpamDetectorConstruction.hh"
#include "EpamRunAction.hh"
#include "EpamDefs.hh"
#include "EpamRunAction.hh"
//#include "Random/RandGaussT.h"
//#include "EpamIdentifier.hh"

#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

#include "G4VVisManager.hh"

#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"

#include <fstream>

#include <sys/time.h>
#include <unistd.h>

#include "WLSPhotonDetHit.hh"
#include "WLSTrajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
//using CLHEP::RandGaussT;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//------------------------Creat a File---------------------------
//
ofstream outData("PhotonInformation.txt");
//outData.open("StepInformation.txt");

//
//---------------------------------------------------------------


EpamEventAction::EpamEventAction( EpamRunAction* run ):
  runaction( run ),
  x_position(0),
  y_position(0),
  z_position(0),
  printModulo(100), drawFlag("all")
{
  detector = runaction->getDetector();
  forcedrawphotons = false;
  forcenophotons   = false;
  //  identifier = EpamIdentifier();
  //engine = HepRandom::getTheEngine();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EpamEventAction::~EpamEventAction()
{   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EpamEventAction::BeginOfEventAction( const G4Event* evt )
{
  G4int evtNb = evt->GetEventID();

  if( evtNb == 0 ){
    //HepRandom::showEngineStatus();
    gettimeofday( &startTime, &tz );
  }

  if( evtNb == 1000 ){
    gettimeofday( &endTime, &tz );
    G4cout << "Simulation Speed: " << 1000. / ( ( endTime.tv_sec - startTime.tv_sec ) + ( endTime.tv_usec - startTime.tv_usec ) / 1000000. ) << "events per second." << G4endl;
  }
  
  if( evtNb % 100000 == 0 && evtNb ){
    G4cout << "---> Begin of event: " << evtNb << G4endl;
  }

  runaction->eventInfo.reset();
  runaction->eventSecondaryParticleNumberInfo.reset();
  
  //  G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Track Point:: End of 'BeginOfEventAction'" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EpamEventAction::EndOfEventAction(const G4Event* evt)
{
  //G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Track Point:: Begin of 'EndOfEventAction'" << G4endl;
  
  // Print trajectory
  if (G4VVisManager::GetConcreteInstance() ){
    G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
    G4int n_trajectories = 0; 
    if (trajectoryContainer){
      n_trajectories = trajectoryContainer->entries();
    }
    for( G4int i=0; i < n_trajectories; i++ ){
      G4Trajectory* trj = (G4Trajectory*) ( ( *(evt->GetTrajectoryContainer()) )[i] );
      if (drawFlag == "all"){
        trj->DrawTrajectory(50);
      }
      else if ( (drawFlag == "charged") && ( trj->GetCharge() != 0.) ){
        trj->DrawTrajectory(50);
      }
      else if ( (drawFlag == "neutral") && ( trj->GetCharge() == 0.) ){
        trj->DrawTrajectory(50);
      }
      else if(trj->GetParticleName()=="opticalphoton"){
	trj->DrawTrajectory(50);
      }
    }
    //  std::getchar();
  }
  //G4cout<<"event((((((((((((("<<G4endl;
  

  //  G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CHECK POINT:: In 'EndOfEventAction' 1" << G4endl;

  // Put Statistics Error
  // -- Silicon Layers
  //G4double	fanoFactor	= 0.1;	//approximate
  //G4double	meanIonEnergy	= 3.62*eV;//Si@300K
  /*
  G4double lowEnergyDepositCut = 6*MeV;
  G4double siliconNoise = SILICON_LAYER_ELECTRONICS_NOISE;
  G4double siliconResolution = SILICON_LAYER_RESOLOTION;
  G4double siliconSigma[3];
  for( G4int ptr = 0; ptr < 3; ptr++ ){
    siliconSigma[ptr] = runaction->eventInfo.siliconLayersEnergyDeposit[ptr] * siliconResolution / 2.355;
    if( runaction->eventInfo.siliconLayersEnergyDeposit[ptr] <= lowEnergyDepositCut && runaction->eventInfo.siliconLayersEnergyDeposit[ptr] > 0 ){
      siliconSigma[ptr] *= sqrt( lowEnergyDepositCut / runaction->eventInfo.siliconLayersEnergyDeposit[ptr] );
    }
    runaction->eventInfo.siliconLayersEnergyDepositWithError[ptr] = runaction->eventInfo.siliconLayersEnergyDeposit[ptr] + RandGaussT::shoot( engine, 0.0, sqrt( siliconSigma[ptr]*siliconSigma[ptr] + siliconNoise*siliconNoise ) );
  }

  // -- Calorimeter
  //G4double efficiency = 1.0;  	//approximate
  //G4double photonYeild = 1680;	//LaBr3:Ce(0.5%)
  G4double calorimeterResolution = 3./100.;
  G4double calorimeterSigma	= runaction->eventInfo.calorimeterEnergyDeposit * calorimeterResolution / 2.355;
  runaction->eventInfo.calorimeterEnergyDepositWithError = runaction->eventInfo.calorimeterEnergyDeposit + RandGaussT::shoot( engine, 0.0, calorimeterSigma );

  */
  /*
  // Display abnormal trajectory
  if( runaction->eventInfo.resultCode > 0 && runaction->eventInfo.calculatedZfast > 1.0 &&
      G4VVisManager::GetConcreteInstance() ){
    if (G4VVisManager::GetConcreteInstance() ){
      G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
      G4int n_trajectories = 0; 
      if (trajectoryContainer){
        n_trajectories = trajectoryContainer->entries();
      }
      for( G4int i=0; i < n_trajectories; i++ ){
        G4Trajectory* trj = (G4Trajectory*) ( ( *(evt->GetTrajectoryContainer()) )[i] );
        if (drawFlag == "all"){
          trj->DrawTrajectory(50);
        }
        else if ( (drawFlag == "charged") && ( trj->GetCharge() != 0.) ){
          trj->DrawTrajectory(50);
        }
        else if ( (drawFlag == "neutral") && ( trj->GetCharge() == 0.) ){
          trj->DrawTrajectory(50);
        }
      }
  p  }
 
    runaction->eventInfo.PrintInfo();
    
    G4cout << "Press any key to countinue...";
    std::getchar();
    G4cout << G4endl;

  }
  */ 

  // Fill Tree

  //  if( runaction->eventInfo.resultCode > 0 ){
  //    runaction->epamGoodDataTree->Fill();
    //}
  runaction->epamDataTree->Fill();
  
  for (G4int i=0; i<288; i++)
    {
      outData<<runaction->eventSecondaryParticleNumberInfo.fiberPhotonNumber[i]<<"  ";
    }
  outData<<G4endl;
  G4cout<<"event&&&&&"<<G4endl;

  // Get Hits from the detector if any
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  G4String colName = "PhotonDetHitCollection";
  mppcCollID = SDman->GetCollectionID(colName);

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  WLSPhotonDetHitsCollection* mppcHC = 0;

  // Get the hit collections
  if (HCE)
  {
     if (mppcCollID>=0) mppcHC = 
                        (WLSPhotonDetHitsCollection*)(HCE->GetHC(mppcCollID));
  }

  // Get hit information about photons that reached the detector in this event
  if (mppcHC)
  {
//     G4int n_hit = mppcHC->entries();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EpamEventAction::updateEventInfo( EpamEventKeyInformation* info )
{
  if( info->visibleLightShieldEnergyDeposit[0] > 0 ){
    runaction->eventInfo.visibleLightShieldEnergyDeposit[0] += info->visibleLightShieldEnergyDeposit[0];
  }

  if( info->visibleLightShieldEnergyDeposit[1] > 0 ){
    runaction->eventInfo.visibleLightShieldEnergyDeposit[1] += info->visibleLightShieldEnergyDeposit[1];
  }

  for( G4int ptr = 0; ptr < 3; ptr ++ ){
    if( info->siliconLayersEnergyDeposit[ptr]>0 ){
      runaction->eventInfo.siliconLayersEnergyDeposit[ptr] += info->siliconLayersEnergyDeposit[ptr];
    }
  }

  if( info->calorimeterEnergyDeposit > 0 ){
    runaction->eventInfo.calorimeterEnergyDeposit += info->calorimeterEnergyDeposit;
  }
  
  if( info->ifPrimaryReachVisibleLightShield[0] == true )
    runaction->eventInfo.ifPrimaryReachVisibleLightShield[0] = true;
  if( info->ifPrimaryReachVisibleLightShield[1] == true )
    runaction->eventInfo.ifPrimaryReachVisibleLightShield[1] = true;
  
  for( G4int ptr = 0; ptr < 3; ptr++ ){
    if( info->ifPrimaryReachSiliconLayer[ptr] == true )
      runaction->eventInfo.ifPrimaryReachSiliconLayer[ptr] = true;
  }
  if( info->ifPrimaryReachCalorimeter == true )
    runaction->eventInfo.ifPrimaryReachCalorimeter = true;
  
  if( info->secondaryParticleNumber == 1  ){
    runaction->eventInfo.secondaryParticleNumber += 1;
    //G4cout<<"**** "<<(runaction->eventInfo.secondaryParticleNumber)<<G4endl;
  }
  if( info->highEnergySecondaryParticleNumber == 1 ){
    runaction->eventInfo.highEnergySecondaryParticleNumber += 1;
    //G4cout<<"********** "<<runaction->eventInfo.highEnergySecondaryParticleNumber<<G4endl;
  }
  
}

void EpamEventAction::updateEventParticleInfo( EpamEventKeyInformation* info )
{
  runaction->eventInfo.particleZ = info->particleZ;
  runaction->eventInfo.particleA = info->particleA;
  runaction->eventInfo.particleMass = info->particleMass;
  runaction->eventInfo.particleEnergy = info->particleEnergy;
  runaction->eventInfo.particlePosition[0] = info->particlePosition[0];
  runaction->eventInfo.particlePosition[1] = info->particlePosition[1];
  runaction->eventInfo.particlePosition[2] = info->particlePosition[2];
  runaction->eventInfo.particleDirection[0] = info->particleDirection[0];
  runaction->eventInfo.particleDirection[1] = info->particleDirection[1];
  runaction->eventInfo.particleDirection[2] = info->particleDirection[2];
  
}

void EpamEventAction::updateEventSecondaryParticleNumberInfo( EpamEventSecondaryParticleNumberInformation* info)
{
  for (G4int ptr=0; ptr<320; ptr++)
    {
      if (info->fiberPhotonNumber[ptr]==1)
	{
	  runaction->eventSecondaryParticleNumberInfo.fiberPhotonNumber[ptr] += info->fiberPhotonNumber[ptr];
	}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
