// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_editor/editmode/polygon/PolygonEditMode.h"

#include <glm/glm.hpp>


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
		*    New ellipse polygon edit mode class
		*/
		class NewEllipsePolygonEditMode : public PolygonEditMode
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
			static const uint32 PLUGINABLE_ID;	///< "qsf::editor::NewEllipsePolygonEditMode" unique pluginable edit mode ID


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
			explicit NewEllipsePolygonEditMode(EditModeManager* editModeManager);

			/**
			*  @brief
			*    Destructor
			*/
			virtual ~NewEllipsePolygonEditMode();

			/**
			*  @brief
			*    Set the component ID of the concrete polygon to instantiate
			*
			*  @param[in] componentId
			*    The component ID of the concrete polygon to instantiate (e.g. "qsf::StringHash("qsf::BlockerPolygonComponent")")
			*/
			void setComponentId(uint32 componentId);


		//[-------------------------------------------------------]
		//[ Protected virtual qsf::editor::EditMode methods       ]
		//[-------------------------------------------------------]
		protected:
			virtual bool onStartup(EditMode* previousEditMode) override;
			virtual void onShutdown(EditMode* nextEditMode) override;
			virtual void mousePressEvent(QMouseEvent& qMouseEvent) override;
			virtual void mouseReleaseEvent(QMouseEvent& qMouseEvent) override;
			virtual void mouseMoveEvent(QMouseEvent& qMouseEvent) override;


		//[-------------------------------------------------------]
		//[ Private Qt slots (MOC)                                ]
		//[-------------------------------------------------------]
		private Q_SLOTS:
			void onCustomContextMenuRequested(const QPoint& qPoint);


		//[-------------------------------------------------------]
		//[ Private methods                                       ]
		//[-------------------------------------------------------]
		private:
			/**
			*  @brief
			*    Cancel the requested draw request
			*/
			void stopDrawing();

			/**
			*  @brief
			*    Creates a list of node positions (used for polygon debug draw request)
			*
			*  @note
			*    The position are all absolute
			*/
			void createPolygonNodes(const glm::vec3& position, std::vector<glm::vec3>& nodeList);

			/**
			*  @brief
			*    Creates a list of nodes (used for creating the "create nodes operation")
			*/
			void createPolygonNodes(const glm::vec3& position, std::vector<Node>& nodeList, glm::vec3& center);


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			unsigned int	mComponentId;			///< The component ID of the concrete polygon to instantiate (e.g. "qsf::StringHash("qsf::BlockerPolygonComponent")")
			bool			mFirstNodeInsert;		///< Has a first node already been inserted?
			glm::vec3		mFirstNodePosition;		///< World space position of the first node
			unsigned int	mDebugDrawRequestId;	///< Debug draw request ID, "qsf::getUninitialized<unsigned int>()" if invalid


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
QSF_CAMP_TYPE_NONCOPYABLE(qsf::editor::NewEllipsePolygonEditMode)
