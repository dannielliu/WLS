//
//***************************************************************
//*DISCLAIMER							*
//*								*
//*				Created Jul.22, 2006		*
//***************************************************************
//
//path: epam/src/EpamVisManager.cc

//
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#include "EpamSteppingAction.hh"
#include "EpamDetectorConstruction.hh"
#include "EpamEventAction.hh"
#include "EpamRunAction.hh"
#include "EpamDefs.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrackStatus.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "WLSPhotonDetSD.hh"
#include "G4ProcessManager.hh"
#include "WLSUserTrackInformation.hh"

//ofstream outData("position.txt");
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
static const G4ThreeVector ZHat = G4ThreeVector(0.0,0.0,1.0);

G4int EpamSteppingAction::maxRndmSave = 10000;

EpamSteppingAction::EpamSteppingAction(EpamDetectorConstruction* det, EpamEventAction* evt ):
  detector(det),
  eventaction(evt)					 
{
  stepInfo.reset();
  
  secondaryParticleNumberInfo.reset();
  
  //eventaction->x_position=0;
  //eventaction->y_position=0;
  //eventaction->z_position=0;
}

EpamSteppingAction::~EpamSteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamSteppingAction::UserSteppingAction( const G4Step* theStep )
{
  //stepInfo.reset();
  
  //secondaryParticleNumberInfo.reset();
  /*
  G4StepPoint* preStepPoint = theStep->GetPreStepPoint();
  G4StepPoint* postStepPoint = theStep->GetPostStepPoint();
  G4ThreeVector preStepPosition = preStepPoint->GetPosition();
  G4ThreeVector postStepPosition = postStepPoint->GetPosition();
  */
  /*
  G4String preVolumeName = preStepPoint->GetPhysicalVolume()->GetName();
  
  if( preVolumeName == "calorimeter" ){
    stepInfo.calorimeterEnergyDeposit = theStep->GetTotalEnergyDeposit();
  }
  */
  // :::: End of Storing Energy

  G4Track* theTrack = theStep->GetTrack();
  
  //G4cout<<"theStep***"<<G4endl;
  WLSUserTrackInformation* trackInformation
      = (WLSUserTrackInformation*)theTrack->GetUserInformation();
  /*
  WLSUserEventInformation* eventInformation
    =(WLSUserEventInformation*)G4EventManager::GetEventManager()
    ->GetConstCurrentEvent()->GetUserInformation();
  */
  G4StepPoint* thePrePoint  = theStep->GetPreStepPoint();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();

  G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4String thePrePVname  = " ";
  G4String thePostPVname = " ";
  
  if (thePostPV) {
    thePrePVname  = thePrePV->GetName();
    thePostPVname = thePostPV->GetName();
  }
  
   if(!thePostPV){//out of world
    return;
  }
   
  G4OpBoundaryProcessStatus theStatus = Undefined;
  static G4OpBoundaryProcess* boundary=NULL;
  
  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm 
      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
	boundary = (G4OpBoundaryProcess*)(*pv)[i];
	break;
      }
    }
  }
  /*
  //Recording data for start
  if (theTrack->GetParentID()==0) {
     //This is a primary track
     if ( theTrack->GetCurrentStepNumber() == 1 ) {
//        G4double x  = theTrack->GetVertexPosition().x();
//        G4double y  = theTrack->GetVertexPosition().y();
        G4double z  = theTrack->GetVertexPosition().z();
//        G4double pz = theTrack->GetVertexMomentumDirection().z();
	initTheta = theTrack->GetVertexMomentumDirection().angle(ZHat);
	initZ = z;
     }
  }
  */
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    
    if(thePrePV->GetName()=="WLSFiber"){G4cout<<"wls"<<G4endl;}
    //force drawing of photons in WLS slab
    //trackInformation->SetForceDrawTrajectory(true);
    else if(thePostPV->GetName()=="World"){
      //Kill photons entering expHall from something other than Slab
      theTrack->SetTrackStatus(fStopAndKill);
      G4cout<<"opt"<<G4endl;}
    //Was the photon absorbed by the absorption process
    /*
      if(thePostPoint->GetProcessDefinedStep()->GetProcessName()
      =="OpAbsorption"){
      eventInformation->IncAbsorption();
      trackInformation->AddTrackStatusFlag(absorbed);
      }
    */
    
    // Retrieve the status of the photon
  
    /*
      G4ProcessManager* OpManager =
      G4OpticalPhoton::OpticalPhoton()->GetProcessManager();
      G4cout<<"optStep***"<<G4endl;
  
      if (OpManager) {
      G4int MAXofPostStepLoops =
      OpManager->GetPostStepProcessVector()->entries();
      G4ProcessVector* fPostStepDoItVector =
      OpManager->GetPostStepProcessVector(typeDoIt);

      for ( G4int i=0; i<MAXofPostStepLoops; i++) {
      G4VProcess* fCurrentProcess = (*fPostStepDoItVector)[i];
      opProcess = dynamic_cast<G4OpBoundaryProcess*>(fCurrentProcess);
      if (opProcess) { theStatus = opProcess->GetStatus(); break;}
      }
      }
  
      // Find the skewness of the ray at first change of boundary
      if ( initGamma == -1 &&
      (theStatus == TotalInternalReflection
      || theStatus == FresnelReflection
      || theStatus == FresnelRefraction)
      && trackInformation->isStatus(InsideOfFiber) ) {
    
      G4double px = theTrack->GetVertexMomentumDirection().x();
      G4double py = theTrack->GetVertexMomentumDirection().y();
      G4double x  = theTrack->GetPosition().x();
      G4double y  = theTrack->GetPosition().y();

      initGamma = x * px + y * py;

      initGamma = initGamma / std::sqrt(px*px + py*py) / std::sqrt(x*x + y*y);

      initGamma = std::acos(initGamma*rad);

      if ( initGamma / deg > 90.0)  { initGamma = 180 * deg - initGamma;}
      }
  
      // Record Photons that missed the photon detector but escaped from readout
      if ( !thePostPV && trackInformation->isStatus(EscapedFromReadOut) ) {
      //     UpdateHistogramSuccess(thePostPoint,theTrack);
      ResetCounters();
 
      return;
      }
    */
    
    theStatus=boundary->GetStatus();
    if(thePostPoint->GetStepStatus()==fGeomBoundary){
      // Assumed photons are originated at the fiber OR
      // the fiber is the first material the photon hits
      switch (theStatus) {
	/*
	// Exiting the fiber
	case FresnelRefraction:
	case SameMaterial:
       
	G4bool isFiber;
	isFiber = thePostPVname == "WLSFiber"
	|| thePostPVname == "Clad2";
       
	if ( isFiber ) {

	if (trackInformation->isStatus(OutsideOfFiber))
	//trackInformation->AddStatusFlag(InsideOfFiber);
	G4cout<<"track"<<G4endl;
	// Set the Exit flag when the photon refracted out of the fiber
	} 
	*/
	/*else if (trackInformation->isStatus(InsideOfFiber)) {

	// EscapedFromReadOut if the z position is the same as fiber's end
	//if (theTrack->GetPosition().z() == detector->GetWLSFiberEnd())
	if (theTrack->GetPosition().y() == 160*mm)
	{
	trackInformation->AddStatusFlag(EscapedFromReadOut);
	counterEnd++;
	}
	else // Escaped from side
	{
	trackInformation->AddStatusFlag(EscapedFromSide);
	trackInformation->SetExitPosition(theTrack->GetPosition());

	//              UpdateHistogramEscape(thePostPoint,theTrack);

	counterMid++;
	ResetCounters();
	}

	trackInformation->AddStatusFlag(OutsideOfFiber);
	trackInformation->SetExitPosition(theTrack->GetPosition());

	}
	*/
	//return;
	/*
	// Internal Reflections
	case TotalInternalReflection:
 
	// Kill the track if it's number of bounces exceeded the limit
	if (bounceLimit > 0 && counterBounce >= bounceLimit)
	{
	theTrack->SetTrackStatus(fStopAndKill);
	trackInformation->AddStatusFlag(murderee);
	ResetCounters();
	G4cout << "\n Bounce Limit Exceeded" << G4endl;
	return;
	}
 
	case FresnelReflection:

	counterBounce++;
 
	if ( thePrePVname == "WLSFiber") counterWLSBounce++;

	//else if ( thePrePVname == "Clad1") counterClad1Bounce++;

	else if ( thePrePVname == "Clad2") counterClad2Bounce++;
 
	// Determine if the photon has reflected off the read-out end
	if (theTrack->GetPosition().x() == 160*mm || theTrack->GetPosition().y() == 160*mm)
	{
	if (!trackInformation->isStatus(ReflectedAtReadOut) &&
	trackInformation->isStatus(InsideOfFiber))
	{
	trackInformation->AddStatusFlag(ReflectedAtReadOut);

	if (theStatus == TotalInternalReflection)
	{
	theTrack->SetTrackStatus(fStopAndKill);
	trackInformation->AddStatusFlag(murderee);
	//                UpdateHistogramReflect(thePostPoint,theTrack);
	ResetCounters();
	return;
	}
	}
	}
	return;

	// Reflection of the mirror
	case LambertianReflection:
	case LobeReflection:
	case SpikeReflection:
       
	// Check if it hits the mirror
	if ( thePostPVname == "Mirror" )
	trackInformation->AddStatusFlag(ReflectedAtMirror);
       
	return;
	*/
	// Detected by a detector
      case Detection:
	G4cout<<"statusStep***"<<G4endl;
	// Check if the photon hits the detector and process the hit if it does
       
	if ( thePostPVname == "PhotonDet" ) {

          G4SDManager* SDman = G4SDManager::GetSDMpointer();
          G4String SDname="WLS/PhotonDet";
          WLSPhotonDetSD* mppcSD =
	    (WLSPhotonDetSD*)SDman->FindSensitiveDetector(SDname);

          if (mppcSD) mppcSD->ProcessHits_constStep(theStep,NULL);

	  // Record Photons that escaped at the end
	  //          if (trackInformation->isStatus(EscapedFromReadOut))
	  //                              UpdateHistogramSuccess(thePostPoint,theTrack);

	  // Stop Tracking when it hits the detector's surface
          ResetCounters();
          theTrack->SetTrackStatus(fStopAndKill);

          return;
	}
       
	break;
       
      default: break;
	 
      }
    }
  }
  /*
  // Check for absorbed photons
  if (theTrack->GetTrackStatus() != fAlive  &&
  trackInformation->isStatus(InsideOfFiber))
  {
  //     UpdateHistogramAbsorb(thePostPoint,theTrack);
  ResetCounters();
  return;
  }
  */
  
 
  eventaction->updateEventInfo( &stepInfo );
  
  eventaction->updateEventSecondaryParticleNumberInfo(&secondaryParticleNumberInfo);
  //G4cout<<"hello^^^^^^^^^^^^^^^^^^^^"<<G4endl;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
