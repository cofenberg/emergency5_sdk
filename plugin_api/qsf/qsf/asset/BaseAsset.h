// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "qsf/asset/AssetSystemTypes.h"
#include "qsf/base/flyweight/FlyweightString.h"
#include "qsf/reflection/object/Object.h"

#include <boost/container/flat_set.hpp>

#include <vector>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class BinarySerializer;
}


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
	*    Asset base class
	*
	*  @remarks
	*    It's recommended to access assets only via asset proxies.
	*
	*    The asset is in fact "asset metadata", not the "asset data". Because writing all the time "asset metadata"
	*    would be quite uncomfortable, we just call it "asset".
	*
	*    The human readable asset name is directly used to e.g. create the file name of the asset. Our artists are to lazy
	*    to provide an asset name and a nice looking human readable asset name which is e.g. presented inside a GUI. :D
	*
	*    There are two types of asset identification: Global asset ID and local asset ID
	*    - Global asset identification:
	*      - ID is generated by an asset server and is used as ID which is unique on the asset server across all projects
	*    - Local asset identification:
	*      - Local UTF-8 asset name, e.g. "sample/mesh/house/house01" which follows the convention "<project name>/<asset type>/<asset category>/<asset name>"
	*      - Local asset ID which is generated by using "qsf::StringHash" on the local UTF-8 asset name (e.g. qsf::StringHash("sample/mesh/house/house01"))
	*    - Usually, one only deals with the local asset ID because it's easier due to the possible local asset name
	*/
	class QSF_API_EXPORT BaseAsset : public Object
	{


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
		friend class GeneralMetaclasses;	// Only the plugin system is allowed to create and manage plugin instances
		friend class AssetPackage;			// Asset package may change the global asset ID


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		typedef boost::container::flat_set<GlobalAssetId> DerivedFromSet;


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] globalAssetId
		*    The global asset identifier
		*/
		explicit BaseAsset(GlobalAssetId globalAssetId);

		/**
		*  @brief
		*    Destructor
		*/
		inline virtual ~BaseAsset();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] source
		*    Source to copy from
		*
		*  @return
		*    Reference to this base asset
		*/
		inline BaseAsset& operator =(const BaseAsset& source);

		//[-------------------------------------------------------]
		//[ Properties                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Return the global asset identifier
		*
		*  @return
		*    The global asset identifier
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline GlobalAssetId getGlobalAssetId() const;

		/**
		*  @brief
		*    Return the asset revision
		*
		*  @return
		*    The asset revision
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*
		*  @remarks
		*    Assets which do not have source data committed yet default to the revision number "0". "REVISION_HEAD" is a query constant,
		*    as opposed to a common valid value. In other words: Revision "0" does exist, but holds a pure meta asset (which possibly has
		*    just been locally constructed) while "REVISION_HEAD"(-1) does not really exist, but rather instructs that the latest existing
		*    revision should be used looked up and used instead.
		*/
		inline AssetRevision getRevision() const;

		/**
		*  @brief
		*    Set the asset revision
		*
		*  @param[in] revision
		*    The new asset revision
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setRevision(AssetRevision revision);

		/**
		*  @brief
		*    Return the type name
		*
		*  @return
		*    The UTF-8 type name (example: "mesh"), do no destroy the returned instance, completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*    - Used in the construction of local asset names "<project name>/<asset type>/<asset category>/<asset name>.<cached asset type>" (e.g. "mesh" -> "sample/mesh/house/house01.mesh")
		*/
		inline const std::string& getTypeName() const;

		/**
		*  @brief
		*    Set the type name
		*
		*  @param[in] typeName
		*    The UTF-8 type name (example: "mesh"), completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		void setTypeName(const std::string& typeName);

		/**
		*  @brief
		*    Return the type ID
		*
		*  @return
		*    The asset type ID (e.g. qsf::StringHash("mesh"))
		*
		*  @note
		*    - The asset type ID is generated by using "qsf::StringHash" on the UTF-8 asset type name
		*/
		inline AssetTypeId getTypeId() const;

		/**
		*  @brief
		*    Return the category name
		*
		*  @return
		*    The UTF-8 category name (example: "house"), do no destroy the returned instance, completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*    - Used in the construction of local asset names "<project name>/<asset type>/<asset category>/<asset name>.<cached asset type>" (e.g. "house" -> "sample/mesh/house/house01.mesh")
		*/
		inline const std::string& getCategory() const;

		/**
		*  @brief
		*    Set the category name
		*
		*  @param[in] category
		*    The UTF-8 category name (example: "house"), completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setCategory(const std::string& category);

		/**
		*  @brief
		*    Return the name
		*
		*  @return
		*    The UTF-8 name (example: "ambulance"), do no destroy the returned instance, completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*    - Used in the construction of local asset names "<project name>/<asset type>/<asset category>/<asset name>.<cached asset type>" (e.g. "house01" -> "sample/mesh/house/house01.mesh")
		*/
		inline const std::string& getName() const;

		/**
		*  @brief
		*    Set the name
		*
		*  @param[in] name
		*    The UTF-8 name (example: "ambulance"), completely lower case
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setName(const std::string& name);

		/**
		*  @brief
		*    Return the description
		*
		*  @return
		*    The UTF-8 description, do no destroy the returned instance
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline const std::string& getDescription() const;

		/**
		*  @brief
		*    Set the description
		*
		*  @param[in] description
		*    The UTF-8 description
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setDescription(const std::string& description);

		/**
		*  @brief
		*    Return the tags as semicolon separated string
		*
		*  @return
		*    The UTF-8 tags as semicolon separated string (e.g. "car;person"), tags are not case-sensitive
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline const std::string& getTags() const;

		/**
		*  @brief
		*    Set the tags as semicolon separated string
		*
		*  @param[in] tags
		*    The UTF-8 tags as semicolon separated string (e.g. "car;person"), tags are not case-sensitive
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setTags(const std::string& tags);

		/**
		*  @brief
		*    Return whether or not a given tag is there
		*
		*  @param[in] tag
		*    The UTF-8 tag to check (e.g. "car"), tags are not case-sensitive
		*
		*  @return
		*    "true" if the tag has been found, else "false"
		*/
		bool hasTag(const std::string& tag) const;

		/**
		*  @brief
		*    Return the login of the user that submitted this revision of the asset
		*
		*  @return
		*    The UTF-8 login of the user that submitted this revision of the asset
		*/
		inline const std::string& getAuthor() const;

		/**
		*  @brief
		*    Set the login of the user that submitted this revision of the asset
		*
		*  @param[in] author
		*    The UTF-8 login of the user that submitted this revision of the asset
		*/
		inline void setAuthor(const std::string& author);

		inline const std::string& getDateCreated() const;
		inline void setDateCreated(const std::string& dateCreated);

		inline const std::string& getDateModified() const;
		inline void setDateModified(const std::string& dateModified);

		/**
		*  @brief
		*    Return the hash of the asset source data
		*
		*  @return
		*    The SHA-2 256 bit hash (example: "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") of the asset source data as ASCII string, do no destroy the returned instance
		*/
		inline const std::string& getHash() const;

		/**
		*  @brief
		*    Set the hash of the asset source data
		*
		*  @param[in] hash
		*    The SHA-2 256 bit hash (example: "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") of the asset source data as ASCII string
		*/
		inline void setHash(const std::string& hash);

		inline const std::vector<GlobalAssetId>& getDependencies() const;
		inline void setDependencies(const std::vector<GlobalAssetId>& dependencies);

		inline const DerivedFromSet& getDerivedFrom() const;
		inline void setDerivedFrom(const DerivedFromSet& derivedFrom);

		std::string getDerivedFromAsString() const;
		void setDerivedFromByString(const std::string& derivedFrom);

		inline uint32 getDeriveranceIndex() const;
		inline void setDeriveranceIndex(const uint32 deriveranceIndex);

		/**
		*  @brief
		*    Return the asset datasource path
		*
		*  @return
		*    The asset datasource path
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline const std::string& getDatasourcePath() const;

		/**
		*  @brief
		*    Set the asset datasource path
		*
		*  @param[in] datasource
		*    The new asset datasource path
		*
		*  @note
		*    - Connected to the CAMP reflection system
		*/
		inline void setDatasourcePath(const std::string& datasourcePath);


	//[-------------------------------------------------------]
	//[ Public virtual "qsf::BaseAsset" methods               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Serialization of the asset
		*/
		virtual void serialize(BinarySerializer& serializer, uint32 version);


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		inline void setGlobalAssetId(GlobalAssetId globalAssetId);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		AssetTypeId				   mTypeId;				///< Type ID (e.g. qsf::StringHash("mesh")), "qsf::getUninitialized<AssetTypeId>()" if invalid
		// Connected to the CAMP reflection system
		GlobalAssetId			   mGlobalAssetId;		///< The global asset identifier
		AssetRevision			   mRevision;			///< The asset revision
		FlyweightString			   mTypeName;			///< UTF-8 type name, completely lower case
		FlyweightString			   mCategory;			///< UTF-8 category name, completely lower case
		FlyweightString 		   mName;				///< UTF-8 name, completely lower case
		FlyweightString			   mDescription;		///< UTF-8 description
		FlyweightString			   mTags;				///< The UTF-8 tags as semicolon separated string (e.g. "car;person"), tags are not case-sensitive
		FlyweightString			   mAuthor;				///< UTF-8 login of the user that submitted this revision of the asset
		FlyweightString 		   mDateCreated;		///< TODO(co) Review this: Can we use "qsf::Time" instead of a string to store time stamps?
		FlyweightString 		   mDateModified;		///< TODO(co) Review this: Can we use "qsf::Time" instead of a string to store time stamps?
		std::string				   mHash;				///< The SHA-2 256 bit hash (example: "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") of the asset source data as ASCII string
		std::vector<GlobalAssetId> mDependencies;		///< Global asset IDs of the assets this asset directly depends on
		DerivedFromSet			   mDerivedFrom;		///< Global asset IDs of the assets this asset is derived from (empty if not derived)
		uint32					   mDeriveranceIndex;	///< Deriverance index used by asset compilers to identify existing derived assets when recompiling the asset this asset was derived from
		FlyweightString			   mDatasourcePath;		///< The datasource path the asset was imported from


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
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "qsf/asset/BaseAsset-inl.h"


//[-------------------------------------------------------]
//[ CAMP reflection system                                ]
//[-------------------------------------------------------]
QSF_CAMP_TYPE_NONCOPYABLE(qsf::BaseAsset)
