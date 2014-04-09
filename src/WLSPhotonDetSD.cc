//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file optical/wls/src/WLSPhotonDetSD.cc
/// \brief Implementation of the WLSPhotonDetSD class
//
//
//

#include "WLSPhotonDetSD.hh"
#include "WLSPhotonDetHit.hh"
#include "WLSUserTrackInformation.hh"

#include "G4Track.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"

WLSPhotonDetSD::WLSPhotonDetSD(G4String name)
  : G4VSensitiveDetector(name)
{
  collectionName.insert("PhotonDetHitCollection");
}

WLSPhotonDetSD::~WLSPhotonDetSD() { }

void WLSPhotonDetSD::Initialize(G4HCofThisEvent* HCE)
{
  for(G4int i=0; i!=32; ++i)
    PhotonDetHitCollection[i] =
      new WLSPhotonDetHitsCollection(SensitiveDetectorName,collectionName[0]);
  //Store collection with event and keep ID
  static G4int HCID = -1;
  if (HCID<0) HCID = GetCollectionID(0);
  for(G4int i=0; i!=32; ++i)
    HCE->AddHitsCollection( HCID, PhotonDetHitCollection[i] );
}

G4bool WLSPhotonDetSD::ProcessHits(G4Step* , G4TouchableHistory* )
{
  return false;
}

//Generates a hit and uses the postStepPoint; PostStepPoint because the hit
//is generated manually when the photon hits the detector
G4bool WLSPhotonDetSD::ProcessHits_constStep(const G4Step* aStep,
                                             G4TouchableHistory* )
{
  if (aStep == NULL) return false;
  G4Track* theTrack = aStep->GetTrack();

  // Need to know if this is an optical photon
  if(theTrack->GetDefinition()
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

  // Find out information regarding the hit
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
  
  //
  G4String preVolumeName = thePostPoint->GetPhysicalVolume()->GetName();
  G4int copynumber = thePostPoint->GetPhysicalVolume()->GetCopyNo();
  //
  WLSUserTrackInformation* trackInformation
      = (WLSUserTrackInformation*)theTrack->GetUserInformation();
 
  G4TouchableHistory* theTouchable
      = (G4TouchableHistory*)(thePostPoint->GetTouchable());
  
  //G4ThreeVector photonExit   = trackInformation -> GetExitPosition();
  G4ThreeVector photonArrive = thePostPoint -> GetPosition();
  G4double      arrivalTime  = theTrack -> GetGlobalTime();
  
  // Convert the global coordinate for arriving photons into
  // the local coordinate of the detector
  photonArrive = theTouchable->GetHistory()->
                                GetTopTransform().TransformPoint(photonArrive);

  // Creating the hit and add it to the collection
  if( preVolumeName =="PhotonDet"){
    for(G4int i=0; i!=32; ++i){
      if(copynumber == i){
	PhotonDetHitCollection[i]->
	  insert(new WLSPhotonDetHit(photonArrive, arrivalTime));
      }
    }
  }
  return true;
}

void WLSPhotonDetSD::EndOfEvent(G4HCofThisEvent* ){
  for(G4int i=0; i!=32; ++i)
    G4cout<<"sd "<< PhotonDetHitCollection[i]->entries()<<G4endl;
}

void WLSPhotonDetSD::clear(){ }

void WLSPhotonDetSD::DrawAll(){ }

void WLSPhotonDetSD::PrintAll(){ }
