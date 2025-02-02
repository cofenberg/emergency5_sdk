// Copyright (C) 2012-2018 Promotion Software GmbH


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <OpenAL/al.h>

#include <vector>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace qsf
{
	class File;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace qsf
{
	namespace openal
	{


		//[-------------------------------------------------------]
		//[ Global functions                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    This function loads a OGG-file stream into a memory buffer and returns the format and frequency
		*
		*  @param[in]  file
		*    Audio file, must be valid
		*  @param[out] buffer
		*    Will receive the read buffer data, buffer is not cleared before adding new elements
		*  @param[out] format
		*    Will receive the format
		*  @param[out] frequency
		*    Will receive the frequency
		*
		*  @return
		*    "true" if all went fine and the file stream object was also destroyed automatically, else "false"
		*/
		extern bool loadOgg(File& file, std::vector<uint8>& buffer, ALenum& format, ALsizei& frequency);

		/**
		*  @brief
		*    This function loads a OGG-buffer into a memory buffer and returns the format and frequency
		*
		*  @param[in]  data
		*    Data to read, must be valid
		*  @param[in]  numberOfBytes
		*    Data size in bytes
		*  @param[out] buffer
		*    Will receive the read buffer data, buffer is not cleared before adding new elements
		*  @param[out] format
		*    Will receive the format
		*  @param[out] frequency
		*    Will receive the frequency
		*
		*  @return
		*    "true" if all went fine, else "false"
		*/
		extern bool loadOgg(const uint8* data, uint32 numberOfBytes, std::vector<uint8>& buffer, ALenum& format, ALsizei& frequency);

		/**
		*  @copydoc loadOgg
		*  @brief
		*    Does read metadata from the OGG header, but does not read sample data
		*/
		extern bool peekOgg(File& file, uint64& bufferSize, ALenum& format, ALsizei& frequency);

		/**
		*  @copydoc loadOgg
		*  @brief
		*    Does read metadata from the OGG header, but does not read sample data
		*/
		extern bool peekOgg(const uint8* data, uint32 numberOfBytes, uint64& bufferSize, ALenum& format, ALsizei& frequency);


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
	} // openal
} // qsf
