// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "em5/Export.h"
#include "em5/network/matchmaking/MatchmakingTypes.h"

#include <qsf/network/layered/packet/BinaryPacket.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace em5
{
	namespace packet
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    TODO(co) Comment me
		*/
		class EM5_API_EXPORT ProxyServerPropertiesResponse : public qsf::packet::BinaryPacket<ProxyServerPropertiesResponse>
		{


		//[-------------------------------------------------------]
		//[ Public definitions                                    ]
		//[-------------------------------------------------------]
		public:
			static const uint32 PACKET_ID;


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			/**
			*  @brief
			*    Default constructor
			*/
			ProxyServerPropertiesResponse();

			const std::string& getProxyServerUrl() const;
			void setProxyServerUrl(const std::string& url);

			uint16 getProxyServerPort() const;
			void setProxyServerPort(uint16 port);


		//[--------------------------------------------------------]
		//[ Public virtual em5::packet::SerializedPacket methods   ]
		//[--------------------------------------------------------]
		public:
			virtual void serialize(qsf::BinarySerializer& serializer) override;


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			std::string mProxyServerUrl;
			uint16		mProxyServerPort;


		};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // packet
} // em5
