/****************************************************************************
**
** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
** Contact: Tegesoft Information (contact@tegesoft.com)
**
** This file is part of the CAMP library.
**
** The MIT License (MIT)
**
** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/


#pragma once


#include <camp/config.hpp>
#include <camp/stringid.hpp>
#include <camp/detail/observernotifier.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace camp
{
class Enum;

namespace detail
{
/**
 * \brief Manages creation, storage, retrieval and destruction of metaenums
 *
 * camp::EnumManager is the place where all metaenums are stored and accessed.
 * It consists of a singleton which is created on first use and destroyed at global exit.
 *
 * \sa Enum
 */
class CAMP_API EnumManager : public ObserverNotifier, public boost::noncopyable
{
public:

    /**
     * \brief Get the unique instance of the class
     *
     * \return Reference to the unique instance of EnumManager
     */
    static EnumManager& instance();

    /**
     * \brief Create and register a new metaenum
     *
     * This is the entry point for every metaenum creation. This
     * function also notifies registered observers after successful creations.
     *
     * \param id ID (result of "camp::StringId(camp::Enum::name())") of the metaenum, no reference by intent
     * \param name Name of the metaenum to create (must be unique), must stay valid as long as this instance exists
     *
     * \return Reference to the new metaenum
     */
    Enum& addClass(StringId id, const char* name);

    /**
     * \brief Get the total number of metaenums
     *
     * \return Number of metaenums that have been registered
     */
    std::size_t count() const;

    /**
     * \brief Get a metaenum from its global index
     *
     * This function, together with EnumManager::count, provides a way to iterate through
     * all the metaenums that have been declared.
     *
     * \param index Global index of the metaenum to get
     *
     * \return Reference to the index-th metaenum
     *
     * \throw OutOfRange index is out of range
     */
    const Enum& getByIndex(std::size_t index) const;

    /**
     * \brief Get a metaenum from an ID
     *
     * \param id The ID (result of "camp::StringId(camp::Enum::name())") of the metaenum, no reference by intent
     *
     * \return Reference to the requested metaenum
     *
     * \throw EnumNotFound id is not the name of an existing metaenum
     */
    const Enum& getById(StringId id) const;

    /**
     * \brief Get a metaenum from an ID
     *
     * This version returns a null pointer if no metaenum is found, instead
     * of throwing an exception.
     *
     * \param id The ID (result of "camp::StringId(camp::Enum::name())") of the metaenum, no reference by intent
     *
     * \return Pointer to the requested metaenum, or null pointer if not found
     */
    const Enum* getByIdSafe(StringId id) const;

    /**
     * \brief Check if a given type has a metaenum
     *
     * \param id The ID (result of "camp::StringId(camp::Enum::name())") of the metaenum, no reference by intent
     *
     * \return True if the enum exists, false otherwise
     */
    bool enumExists(StringId id) const;

private:

    /**
     * \brief Default constructor
     */
    EnumManager();

    /**
     * \brief Destructor
     *
     * The destructor destroys all the registered metaenums and notifies the observers.
     */
    ~EnumManager();

    struct EnumEntry
    {
        uint32_t id;
        Enum* enumPtr;
        EnumEntry(uint32_t _id, Enum* _enumPtr) :
            id(_id),
            enumPtr(_enumPtr)
        {}
    };
    struct OrderByEnumId
    {
        inline bool operator()(const EnumEntry& left, uint32_t right) const
        {
            return (left.id < right);
        }
    };
    typedef std::vector<EnumEntry> SortedEnumVector; ///< Enum ID sorted vector storing enums (for CPU cache efficient searches, "camp::EnumManager::EnumEntry" instead of a direct "camp::Enum*" is used)
    SortedEnumVector m_enums;
};

} // namespace detail

} // namespace camp
