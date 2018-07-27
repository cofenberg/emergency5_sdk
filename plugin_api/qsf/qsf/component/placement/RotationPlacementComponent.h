// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf/component/placement/PlacementComponent.h"


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
	*     Rotation placement component class
	*
	*  @remarks
	*    The Rotation placement component manipulates the rotation of the entity
	*/
	class QSF_API_EXPORT RotationPlacementComponent : public PlacementComponent
	{


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const uint32 COMPONENT_ID;	///< "qsf::RotationPlacementComponent" unique component ID


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] prototype
		*    The prototype this component is in, no null pointer allowed
		*/
		explicit RotationPlacementComponent(Prototype* prototype);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~RotationPlacementComponent();


	//[-------------------------------------------------------]
	//[ Public virtual qsf::PlacementComponent methods        ]
	//[-------------------------------------------------------]
	public:
		virtual bool applyPlacement(glm::vec3& position, glm::quat& rotation) override;
		virtual bool applyPlacement(glm::vec3& position, const glm::quat& rotation) override;


	//[-------------------------------------------------------]
	//[ CAMP reflection system                                ]
	//[-------------------------------------------------------]
	QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // qsf


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(qsf::RotationPlacementComponent)
