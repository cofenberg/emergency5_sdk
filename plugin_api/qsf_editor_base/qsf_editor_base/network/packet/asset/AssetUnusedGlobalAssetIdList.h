// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf_editor_base/Export.h"

#include <qsf/asset/AssetSystemTypes.h>
#include <qsf/network/layered/packet/BinaryPacket.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace editor
	{
		namespace base
		{
			namespace packet
			{


				//[-------------------------------------------------------]
				//[ Classes                                               ]
				//[-------------------------------------------------------]
				/**
				*  @brief
				*    TODO(co) Comment
				*/
				class QSF_EDITOR_BASE_API_EXPORT AssetUnusedGlobalAssetIdList : public qsf::packet::BinaryPacket<AssetUnusedGlobalAssetIdList>
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
					AssetUnusedGlobalAssetIdList();

					/**
					*  @brief
					*    Destructor
					*/
					virtual ~AssetUnusedGlobalAssetIdList();

					const std::vector<GlobalAssetId>& getUnusedGlobalAssetIdList() const;
					void setUnusedGlobalAssetIdList(const std::vector<GlobalAssetId>& list);


				//[--------------------------------------------------------]
				//[ Public virtual qsf::packet::BinaryPacketBase methods   ]
				//[--------------------------------------------------------]
				public:
					virtual void serialize(BinarySerializer& serializer) override;


				//[-------------------------------------------------------]
				//[ Private data                                          ]
				//[-------------------------------------------------------]
				private:
					std::vector<GlobalAssetId> mGlobalAssetIdList;


				};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
			} // packet
		} // base
	} // editor
} // qsf
