// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/Export.h"

#include <qsf/logic/action/Action.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class GameLogicComponent;
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
	*    EMERGENCY 5 DLK deploy action
	*
	*  @note
	*    - Use only in combination with extinguish command
	*/
	class EM5_API_EXPORT DLKDeployAction : public qsf::Action
	{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const qsf::NamedIdentifier ACTION_ID;	///< "em5::DLKDeployAction" unique action identifier

		enum State
		{
			STATE_INIT,
			STATE_EXTENDING_LEGS,
			STATE_LADDER_ALIGNMENT,
			STATE_DONE
		};


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		DLKDeployAction();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DLKDeployAction();

		/**
		*  @brief
		*    Initialize action with values
		*/
		void init(uint64 targetEntityId);

		/**
		*  @brief
		*    Target entity ID
		*/
		uint64 getTargetEntityId() const;


	//[-------------------------------------------------------]
	//[ Public virtual qsf::Actions methods                   ]
	//[-------------------------------------------------------]
	public:
		virtual void serialize(qsf::BinarySerializer& serializer) override;


	//[-------------------------------------------------------]
	//[ Protected virtual qsf::Action methods                 ]
	//[-------------------------------------------------------]
	protected:
		virtual bool onStartup() override;
		virtual qsf::action::Result updateAction(const qsf::Clock& clock) override;


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		void updateGameLogicComponent();
		const glm::vec3& getTargetPosition(qsf::Entity& targetEntity) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint64					 mTargetEntityId;	///< Entity that the ladder should target
		State					 mCurrentState;
		qsf::GameLogicComponent* mGameLogicComponent;


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
QSF_CAMP_TYPE_NONCOPYABLE(em5::DLKDeployAction)
