// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/network/multiplayer/OperationMessages.h"
#include "em5/network/multiplayer/operationmessagehandler/OperationMessageHandler.h"

#include <boost/noncopyable.hpp>

#include <memory>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{
	namespace multiplayer
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    EMERGENCY 5 Manager for operation message handler
		*
		*   @note
		*     - This manager manages operation message handler which are used to transfer data from host to client
		*/
		class EM5_API_EXPORT OperationMessageHandlerManager : public boost::noncopyable
		{


		//[-------------------------------------------------------]
		//[ Public static methods                                 ]
		//[-------------------------------------------------------]
		public:
			static OperationMessageHandler* getHandlerById(OperationMessage id, bool onlyHost);
			template <typename T> static T* getHandler(bool onlyHost);


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			/**
			*  @brief
			*    Constructor
			*/
			OperationMessageHandlerManager();

			/**
			*  @brief
			*    Destructor
			*/
			~OperationMessageHandlerManager();

			/**
			*  @brief
			*    Return a operation message handler instance of a certain type
			*
			*  @return
			*    The requested operation message handler instance, null pointer on error, do no destroy the returned instance
			*/
			template <typename T> T* getHandler();

			/**
			*  @brief
			*    Return a component instance pointer by using its unique identifier
			*
			*  @param[in] id
			*    The unique component identifier generated by "qsf::StringHash"
			*
			*  @return
			*    The requested component instance, null pointer on error, do no destroy the returned instance
			*/
			inline OperationMessageHandler* getHandlerById(OperationMessage id);

			/**
			*  @brief
			*    Returns the whole handler map
			*/
			inline const std::map<OperationMessage, std::unique_ptr<OperationMessageHandler>>& getAllHandler() const;

			/**
			*  @brief
			*    Register a new handler
			*
			*  @param[in] id
			*    Operation message ID
			*  @param[in] operationMessageHandler
			*    Operation message handler to register, the operation message handler manager takes over the control of the memory
			*/
			inline void registerHandler(OperationMessage id, OperationMessageHandler& operationMessageHandler);


		//[-------------------------------------------------------]
		//[ private data                                          ]
		//[-------------------------------------------------------]
		private:
			// TODO(ca) Please implement a std::hash template specialization for OperationMessage if you want to use an unordered_map with this key type (see <http://stackoverflow.com/questions/17885563/using-c11-unordered-set-in-visual-c-and-clang>)
			//std::unordered_map<OperationMessage, std::unique_ptr<OperationMessageHandler>> mHandlerMap;
			std::map<OperationMessage, std::unique_ptr<OperationMessageHandler>> mHandlerMap;


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // multiplayer
} // em5


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "em5/network/multiplayer/operationmessagehandler/OperationMessageHandlerManager-inl.h"
