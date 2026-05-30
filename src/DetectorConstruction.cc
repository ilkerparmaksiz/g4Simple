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
//
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Define Geometry size
  G4double  WorldSize =20*cm;
  G4double  ShieldSize = WorldSize/2+2*cm;
  G4double  DetSize = WorldSize/2;


  // Materials
  G4Material* World_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Det_mat = nist->FindOrBuildMaterial("G4_Ar");
  G4Material* Shield_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  // World Volume
  auto solidWorld = new G4Box("World",                           // its name
    0.5 * WorldSize, 0.5 * WorldSize, 0.5 * WorldSize);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
    World_mat,                                       // its material
    "World_LV");                                        // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                           // at (0,0,0)
    logicWorld,                                // its logical volume
    "World_PV",                                   // its name
    nullptr,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    0);                            // overlaps checking

  // Shield
  auto solidShield = new G4Box("Shield",0.5 * ShieldSize, 0.5 * ShieldSize, 0.5 * ShieldSize);  // its size
  auto logicShield= new G4LogicalVolume(solidShield,Shield_mat,"Shield_LV");
   new G4PVPlacement(nullptr,
    G4ThreeVector(),
    logicShield,"Shield_PV",
    logicWorld,
    false,
    0,
    0);

  auto solidDet = new G4Box("Det",0.5 * DetSize, 0.5 * DetSize, 0.5 * DetSize);  // its size
  auto logicDet= new G4LogicalVolume(solidDet,Det_mat,"Det_LV");
   new G4PVPlacement(nullptr,
    G4ThreeVector(),
    logicDet,"Det_PV",
    logicWorld,
    false,
    0,
    0);

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
