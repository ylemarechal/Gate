/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/
/*! \file GateImageDeformActor.hh
    \class GateImageDeformActor :
    \brief Class of an actor that changes voxels densities during a simulation
    \author yannick.lemarechal@univ-brest.fr
	    david.sarrut@creatis.insa-lyon.fr
*/

#ifndef GATEIMAGEDEFORM_H
#define GATEIMAGEDEFORM_H 1

#include "globals.hh"
#include "GateVActor.hh"
#include "GateImageDeformActorMessenger.hh"
#include "GateActorMessenger.hh"
#include "GateClock.hh"
#include "GateVImageVolume.hh"

//-------------------------------------------------------------------------------------------------
/* \brief Class of an actor that changes voxels densities during a simulation
 *  
 *  Script example :
 *  /gate/actor/addActor     ImageDeformActor A
 *  /gate/actor/A/attachTo   patient
 *  /gate/actor/A/setPDFFile  data.txt
 * 
 * In data.txt :
 * #Phase_time  CT_files
 * 0.0    CT1.mhd
 * 0.25   CT2.mhd
 * 0.50   CT3.mhd
 * 0.75   CT4.mhd
 * 
 **/
class GateImageDeformActor  : public GateVActor
{
public:
    
  /*!
    \brief GateImageDeformActor constructor
    \param name Name of the actor
  */
  GateImageDeformActor ( G4String name, G4int depth=0 );
  
  /*!
    \brief GateImageDeformActor destructor
  */    
  virtual ~GateImageDeformActor();


  FCT_FOR_AUTO_CREATOR_ACTOR ( GateImageDeformActor )

  /*!
    \fn void SetFilename ( G4String filename );
    \param filename Name of the file containing parameters
    \brief Set file used by the actor. It should contain 2 column : The time stamp and the CT file.
  */
  void SetFilename ( G4String filename );
//   void changeVolumeDensities ( G4double time );
//   void getVolumeList();
//   void Initialize();
//   void SetInitialization(G4bool bool_ini);
  
  /*!
    \fn virtual void Construct();
    \brief from GateVActor, it reads PDF file
  */
  virtual void Construct();
  
  /*!
    \fn virtual void BeginOfRunAction ( const G4Run* );
    \brief from GateVActor. At the beginning of each run, the time is read, and compared the phases time (mTimeList). If necessary, CT densities are changed.
  */
  virtual void BeginOfRunAction ( const G4Run* ); 
  
  /*!
    \fn virtual void EndOfRunAction ( const G4Run* );
    \brief from GateVActor. Default action (save)
  */
  virtual void EndOfRunAction ( const G4Run* ); // default action (save)
  
  /*!
    \fn virtual void BeginOfEventAction ( const G4Event* );
    \brief from GateVActor.
  */
  virtual void BeginOfEventAction ( const G4Event* ) ;
//   virtual void EndOfEventAction(const G4Event*); // default action (save every n)
  
  /*!
    \fn virtual void PreUserTrackingAction  ( const GateVVolume *, const G4Track* );
    \brief from GateVActor. 
  */
  virtual void PreUserTrackingAction ( const GateVVolume *, const G4Track* ) {}
  
  /*!
    \fn virtual void PostUserTrackingAction ( const GateVVolume *, const G4Track* );
    \brief from GateVActor. 
  */
  virtual void PostUserTrackingAction ( const GateVVolume *, const G4Track* ) {}
  
  /*!
    \fn virtual void UserSteppingAction ( const GateVVolume *, const G4Step* );
    \brief from GateVActor.
  */
  virtual void UserSteppingAction ( const GateVVolume *, const G4Step* ) {}

  /*!
    \fn virtual void ResetData ( );
    \brief from GateVActor.
  */
  virtual void ResetData() {}


private :
  
  /*!
    \fn void readPDFFile ( G4String file );
    \param file Name of the file containing parameters
    \brief Read the file parameters : time stamps and voxelized volumes.
  */
  void readPDFFile ( G4String file );  // PDF : Probability density function

  GateClock *pClock;
  GateImageDeformActorMessenger* mMessenger;
  std::vector<G4String> mFileList;
  std::vector<double> mTimeList;
  G4String mPDFFile;
  G4int currentPhase;
  GateVImageVolume *pVImageVolume;
  G4int mNumberOfPhases;
  G4bool mFirstRun;
  
};


MAKE_AUTO_CREATOR_ACTOR ( ImageDeformActor,GateImageDeformActor )
#endif

