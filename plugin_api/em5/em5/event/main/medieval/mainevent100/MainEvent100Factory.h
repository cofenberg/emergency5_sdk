// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/freeplay/factory/FreeplayEventFactory.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    EMERGENCY 2016 main event 100 factory
	*/
	class MainEvent100Factory : public FreeplayEventFactory
	{


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MainEvent100Factory();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MainEvent100Factory();


	//[-------------------------------------------------------]
	//[ Public virtual em5::FreeplayEventFactory methods      ]
	//[-------------------------------------------------------]
	public:
		virtual FreeplayEvent* tryTriggerEvent() override;


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Check if all event tags of this main event are valid
		*/
		bool checkConditions() const;


	//[-------------------------------------------------------]
	//[ CAMP reflection system                                ]
	//[-------------------------------------------------------]
	QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // em5


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(em5::MainEvent100Factory)
