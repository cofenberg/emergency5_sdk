// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <OGRE/OgreSceneManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    Grid implementation of "Ogre::SphereSceneQuery"
	*/
	class GridSphereSceneQuery : public Ogre::DefaultSphereSceneQuery
	{


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		explicit GridSphereSceneQuery(Ogre::SceneManager* creator);
		virtual ~GridSphereSceneQuery();


	//[-------------------------------------------------------]
	//[ Public virtual Ogre::SphereSceneQuery methods         ]
	//[-------------------------------------------------------]
	public:
		virtual void execute(Ogre::SceneQueryListener* listener) override;


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		void execute(Ogre::SceneQueryListener* listener, Ogre::ObjectMemoryManager& ogreObjectMemoryManager);


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // qsf
