// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_editor/statusbar/StatusBar.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QLabel;
QT_END_NAMESPACE
namespace qsf
{
	namespace editor
	{
		class EditMode;
	}
}


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
		*    Edit mode status bar
		*
		*  @note
		*    - The UI is created via source code
		*/
		class EditModeStatusBar : public StatusBar
		{


		//[-------------------------------------------------------]
		//[ Qt definitions (MOC)                                  ]
		//[-------------------------------------------------------]
		Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
					// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


		//[-------------------------------------------------------]
		//[ Public definitions                                    ]
		//[-------------------------------------------------------]
		public:
			static const uint32 PLUGINABLE_ID;	///< "qsf::editor::EditModeStatusBar" unique pluginable status bar ID


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			/**
			*  @brief
			*    Constructor
			*
			*  @param[in] statusBarManager
			*    Optional pointer to the status bar manager this status bar should be registered to, can be a null pointer
			*  @param[in] qWidgetParent
			*    Pointer to parent Qt widget, can be a null pointer (in this case you're responsible for destroying this status bar instance)
			*/
			EditModeStatusBar(StatusBarManager* statusBarManager, QWidget* qWidgetParent);

			/**
			*  @brief
			*    Destructor
			*/
			virtual ~EditModeStatusBar();


		//[-------------------------------------------------------]
		//[ Protected virtual qsf::editor::StatusBar methods      ]
		//[-------------------------------------------------------]
		protected:
			virtual void retranslateUi() override;
			virtual void changeVisibility(bool visible) override;


		//[-------------------------------------------------------]
		//[ Private Qt slots (MOC)                                ]
		//[-------------------------------------------------------]
		private Q_SLOTS:
			// qsf::editor::EditModeManager
			void onChangeEditMode(EditMode* newEditMode, EditMode* previousEditMode);


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			QLabel* mQLabel;	///< Qt label instance, can be a null pointer, Qt will destroy the instance automatically


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
QSF_CAMP_TYPE_NONCOPYABLE(qsf::editor::EditModeStatusBar)
