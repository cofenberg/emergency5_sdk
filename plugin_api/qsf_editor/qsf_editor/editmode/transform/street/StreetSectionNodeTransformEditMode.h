// Copyright (C) 2012-2017 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_editor/editmode/transform/node/NodeTransformEditMode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace editor
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Street network tier node transform edit mode class
		*/
		class StreetSectionNodeTransformEditMode : public NodeTransformEditMode
		{


		//[-------------------------------------------------------]
		//[ Public definitions                                    ]
		//[-------------------------------------------------------]
		public:
			static const uint32 PLUGINABLE_ID;	///< "qsf::editor::StreetSectionNodeTransformEditMode" unique pluginable edit mode ID


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			/**
			*  @brief
			*    Constructor
			*
			*  @param[in] editModeManager
			*    The edit mode manager this edit mode instance is in, no null pointer allowed (the CAMP reflection system does not like references in constructors, so we have to use a pointer instead)
			*/
			explicit StreetSectionNodeTransformEditMode(EditModeManager* editModeManager);

			/**
			*  @brief
			*    Destructor
			*/
			virtual ~StreetSectionNodeTransformEditMode();


		//[-------------------------------------------------------]
		//[ Protected virtual qsf::editor::EditMode methods       ]
		//[-------------------------------------------------------]
		protected:
			virtual void onShutdown(EditMode* nextEditMode) override;


		//[-------------------------------------------------------]
		//[ Private methods                                       ]
		//[-------------------------------------------------------]
		private:
			void constraintNodeRadiusDistances();


		//[-------------------------------------------------------]
		//[ CAMP reflection system                                ]
		//[-------------------------------------------------------]
		QSF_CAMP_RTTI()	// Only adds the virtual method "campClassId()", nothing more


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // editor
} // qsf


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(qsf::editor::StreetSectionNodeTransformEditMode)
