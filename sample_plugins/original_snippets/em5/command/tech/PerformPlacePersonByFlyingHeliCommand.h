// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/command/Command.h"


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
	*    EMERGENCY 5 place person from helicopter command
	*/
	class PerformPlacePersonByFlyingHeliCommand : public Command
	{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const uint32 PLUGINABLE_ID;	///< "em5::PerformPlacePersonByFlyingHeliCommand" unique command pluginable ID


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		static void pushCommandToEntity(qsf::Entity& entity, qsf::game::CommandContext& commandContext);


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		explicit PerformPlacePersonByFlyingHeliCommand(qsf::game::CommandManager* commandManager);


	//[-------------------------------------------------------]
	//[ Public virtual em5::Command methods                   ]
	//[-------------------------------------------------------]
	public:
		virtual bool checkAvailable() override;
		virtual bool checkCaller(qsf::Entity& caller) override;
		virtual bool checkContext(const qsf::game::CommandContext& context) override;
		virtual void execute(const qsf::game::CommandContext& context) override;


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		static const uint32 ACTION_PRIORITY;


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
QSF_CAMP_TYPE_NONCOPYABLE(em5::PerformPlacePersonByFlyingHeliCommand)
