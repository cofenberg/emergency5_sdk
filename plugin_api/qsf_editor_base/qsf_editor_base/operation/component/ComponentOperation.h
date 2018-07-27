// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_editor_base/operation/entity/EntityOperation.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class Component;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace editor
	{
		namespace base
		{


			//[-------------------------------------------------------]
			//[ Classes                                               ]
			//[-------------------------------------------------------]
			/**
			*  @brief
			*    Abstract entity component operation base class
			*
			*  @note
			*    - The unique component identifier is generated by "qsf::StringHash" by using the class name
			*      (e.g. qsf::StringHash("qsf::MetadataComponent") generating the hash value 483975945)
			*    - 96 bit are required to unique identify the entity component (entity -> component)
			*/
			class QSF_EDITOR_BASE_API_EXPORT ComponentOperation : public EntityOperation
			{


			//[-------------------------------------------------------]
			//[ Public methods                                        ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Destructor
				*/
				virtual ~ComponentOperation();

				/**
				*  @brief
				*    Return the ID of the entity component this operation is performed on
				*
				*  @return
				*    The ID of the entity component this operation is performed on
				*/
				uint32 getComponentId() const;
				void setComponentId(uint32 componentId);

				/**
				*  @brief
				*    Return the entity component this operation is performed on
				*
				*  @return
				*    The entity component this operation is performed on, can be a null pointer, do not destroy the instance
				*/
				Component* getComponent() const;


			//[-------------------------------------------------------]
			//[ Public qsf::editor::base::Operation methods           ]
			//[-------------------------------------------------------]
			public:
				virtual size_t getMemoryConsumption() const override;


			//[-------------------------------------------------------]
			//[ Protected methods                                     ]
			//[-------------------------------------------------------]
			protected:
				ComponentOperation();


			//[-------------------------------------------------------]
			//[ Protected data                                        ]
			//[-------------------------------------------------------]
			protected:
				uint32 mComponentId;	///< The unique (inside the entity) component identifier


			//[-------------------------------------------------------]
			//[ CAMP reflection system                                ]
			//[-------------------------------------------------------]
			QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


			};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
		} // base
	} // editor
} // qsf


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(qsf::editor::base::ComponentOperation)
