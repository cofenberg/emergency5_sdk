// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/Export.h"

#include <qsf_game/command/mode/CommandMode.h>

#include <qsf/debug/DebugDrawProxy.h>
#include <qsf/reflection/CampClass.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class Map;
	class Entity;
}


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
	*    Roping from (flying) helicopter command mode
	*
	*  @remarks
	*    This command mode lets the user select a position where to place sek police men from sek helicopter (sekhc)
	*/
	class EM5_API_EXPORT RopingFromHelicopterCommandMode : public qsf::game::CommandMode
	{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const uint32 PLUGINABLE_ID;	///< "em5::RopingFromHelicopterCommandMode" unique command pluginable ID


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		RopingFromHelicopterCommandMode();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RopingFromHelicopterCommandMode();

		/**
		*  @brief
		*    Fill class with all necessary variables
		*/
		void initialize(qsf::Entity& caller);


	//[-------------------------------------------------------]
	//[ Public virtual qsf::game::CommandMode methods         ]
	//[-------------------------------------------------------]
	public:
		virtual void startup() override;
		virtual void shutdown() override;
		virtual bool executeCommandContext(qsf::game::CommandContext& commandContext, const EntityIdSet& callerIds) override;
		virtual void updateCommandMode(const qsf::Clock& clock) override;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		static const uint32 ACTION_PRIORITY;


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		bool allowRopingUnderMousePosition();
		bool getTargetUnderMouse(glm::vec3& targetPosition, qsf::Entity*& targetEntity);
		bool allowRopingAtTarget(const glm::vec3& targetPosition, const qsf::Entity* targetEntity);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		qsf::DebugDrawProxy	mDebugDrawProxy;
		qsf::Entity*		mCaller;
		qsf::Map*			mMap;


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
QSF_CAMP_TYPE_NONCOPYABLE(em5::RopingFromHelicopterCommandMode)
