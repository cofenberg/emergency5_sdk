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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    EMERGENCY 5 lay down person from boat action
	*/
	class EM5_API_EXPORT PlacePersonFromBoatAction : public qsf::Action
	{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const qsf::NamedIdentifier ACTION_ID;	///< "em5::PlacePersonFromBoatAction" unique action identifier

		enum State
		{
			STATE_INIT,
			STATE_PLAY_ANIMATION,
			STATE_FINISH
		};


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PlacePersonFromBoatAction();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PlacePersonFromBoatAction();

		/**
		*  @brief
		*    Initialize action with values
		*/
		void init(const qsf::Entity& targetEntity);

		uint64 getTargetId() const;


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
		void unLinkTargetEntity(qsf::Entity& targetEntity);
		bool checkActionCondition(qsf::Entity& targetEntity);
		void applyInjuryToTransportedPerson(qsf::Entity& targetEntity);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Configuration
		uint64	mTargetEntityId;
		State	mState;


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
QSF_CAMP_TYPE_NONCOPYABLE(em5::PlacePersonFromBoatAction)
