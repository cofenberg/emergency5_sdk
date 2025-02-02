/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "OgrePrerequisites.h"

#include "OgreColourValue.h"
#include "OgreVector4.h"
#include "OgreMovableObject.h"
#include "OgrePlaneBoundedVolume.h"
#include "OgreHeaderPrefix.h"

namespace Ogre {


    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup Scene
    *  @{
    */
    /** Representation of a dynamic light source in the scene.
    @remarks
        Lights are added to the scene like any other object. They contain various
        parameters like type, position, attenuation (how light intensity fades with
        distance), colour etc.
    @par
        The defaults when a light is created is pure white diffuse light, with no
        attenuation (does not decrease with distance) and a range of 1000 world units.
    @par
        Lights are created by using the SceneManager::createLight method. Starting Ogre 2.0
        all Lights must be associated to a SceneNode in order to work; which holds the position
        and direction.
        Light::setDirection and Light::getDirection will redirect to the SceneNode and assert
        or crash if not attached to one.
    @par
        Remember also that dynamic lights rely on modifying the colour of vertices based on the position of
        the light compared to an object's vertex normals. Dynamic lighting will only look good if the
        object being lit has a fair level of tessellation and the normals are properly set. This is particularly
        true for the spotlight which will only look right on highly tessellated models. In the future OGRE may be
        extended for certain scene types so an alternative to the standard dynamic lighting may be used, such
            as dynamic lightmaps.
    */
    class _OgreExport Light : public MovableObject
    {
		void resetAabb(void);
		void updateLightBounds(void);
    public:
        /// Temp tag used for sorting
        Real tempSquareDist;
        /// Internal method for calculating current squared distance from some world position
        void _calcTempSquareDist(const Vector3& worldPos);

        /// Defines the type of light
        enum LightTypes
        {
            /// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
            LT_DIRECTIONAL = 0,
            /// Point light sources give off light equally in all directions, so require only position not direction
            LT_POINT = 1,
            /// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
            LT_SPOTLIGHT = 2,

            NUM_LIGHT_TYPES
        };

        /** Normal constructor. Should not be called directly, but rather the SceneManager::createLight method should be used.
        */
        Light( IdType id, ObjectMemoryManager *objectMemoryManager, SceneManager *manager );

        /** Standard destructor.
        */
        ~Light();

        /** Sets the type of light - see LightTypes for more info.
        */
        void setType(LightTypes type);

        /// Overload to avoid it. Light::setType uses the RenderQueue ID to classify lights per type.
        virtual void setRenderQueueGroup(uint8 queueID);

        /** Returns the light type.
        */
        LightTypes getType(void) const                              { return mLightType; }

        /** Sets the colour of the diffuse light given off by this source.
        @remarks
            Material objects have ambient, diffuse and specular values which indicate how much of each type of
            light an object reflects. This value denotes the amount and colour of this type of light the light
            exudes into the scene. The actual appearance of objects is a combination of the two.
        @par
            Diffuse light simulates the typical light emanating from light sources and affects the base colour
            of objects together with ambient light.
        */
        inline void setDiffuseColour(Real red, Real green, Real blue);

        /** Sets the colour of the diffuse light given off by this source.
        @remarks
            Material objects have ambient, diffuse and specular values which indicate how much of each type of
            light an object reflects. This value denotes the amount and colour of this type of light the light
            exudes into the scene. The actual appearance of objects is a combination of the two.
        @par
            Diffuse light simulates the typical light emanating from light sources and affects the base colour
            of objects together with ambient light.
        */
        inline void setDiffuseColour(const ColourValue& colour);

        /** Returns the colour of the diffuse light given off by this light source (see setDiffuseColour for more info).
        */
        const ColourValue& getDiffuseColour(void) const             { return mDiffuse; }

        /** Sets the colour of the specular light given off by this source.
        @remarks
            Material objects have ambient, diffuse and specular values which indicate how much of each type of
            light an object reflects. This value denotes the amount and colour of this type of light the light
            exudes into the scene. The actual appearance of objects is a combination of the two.
        @par
            Specular light affects the appearance of shiny highlights on objects, and is also dependent on the
            'shininess' Material value.
        */
        inline void setSpecularColour(Real red, Real green, Real blue);

        /** Sets the colour of the specular light given off by this source.
        @remarks
            Material objects have ambient, diffuse and specular values which indicate how much of each type of
            light an object reflects. This value denotes the amount and colour of this type of light the light
            exudes into the scene. The actual appearance of objects is a combination of the two.
        @par
            Specular light affects the appearance of shiny highlights on objects, and is also dependent on the
            'shininess' Material value.
        */
        inline void setSpecularColour(const ColourValue& colour);

        /** Returns the colour of specular light given off by this light source.
        */
        const ColourValue& getSpecularColour(void) const            { return mSpecular; }

        /** Sets the attenuation parameters (range, constant, linear & quadratic, @see setAttenuation)
            based on a given radius.
        @remarks
            The actual attenuation formula is:
                            1
            --------------------------------
            (distance / radius)² * 0.5 + 0.5

            The original formula never ends, that is the range is infinity. This function calculates
            a range based on "lumThreshold": When the luminosity past certain distance is below the
            established threshold, the light calculations are cut.
        @param radius
            The radius of the light. i.e. A light bulb is a couple centimeters, the sun is ~696km;
            but be sure to be consistent in the unit of measurement you use (i.e. don't use km if
            your default unit is in meters).
            Note: Having a radius = 2 means that at distance = 2 the pixel is lit 100%
            Anything inside that radius (which is supposedly impossible) will have more than 100%
            light power.
        @param lumThreshold
            Value in the range [0; 1)
            Sets range at which the luminance (in percentage) of a point would go below the threshold.
            For example lumThreshold = 0 means the attenuation range is infinity; lumThreshold = 1 means
            the range is set to 0.
        @par
            The value you want as threshold to use depends on your HDR pipeline and the power of the
            light. For example, with a power = 1 in LDR, a lumThreshold < 1 / 255 (roughly 0.00392)
            is pointless. Past that point the actual RGB value will always be (0, 0, 0).
            But for an LDR pipeline with a light power of 50, lumThreshold < 1 / (255 * 50) is
            pointless. For an HDR pipeline, the answer is more faint, as it depends on the threshold
            of your HDR tonemapping past which it stops adjusting the exposure.
        */
        void setAttenuationBasedOnRadius( Real radius, Real lumThreshold);

        /** Sets the attenuation parameters of the light source i.e. how it diminishes with distance.
        @remarks
            Lights normally get fainter the further they are away. Also, each light is given a maximum range
            beyond which it cannot affect any objects.
        @par
            Light attenuation is not applicable to directional lights since they have an infinite range and
            constant intensity.
        @par
            This follows a standard attenuation approach - see any good 3D text for the details of what they mean
            since i don't have room here!
        @param range
            The absolute upper range of the light in world units.
        @param constant
            The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation.
        @param linear
            The linear factor in the attenuation formula: 1 means attenuate evenly over the distance.
        @param quadratic
            The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.
        */
        void setAttenuation(Real range, Real constant, Real linear, Real quadratic);

        /** Returns the absolute upper range of the light.
        */
        Real getAttenuationRange(void) const                        { return mRange; }

        /** Returns the constant factor in the attenuation formula.
        */
        Real getAttenuationConstant(void) const                     { return mAttenuationConst; }

        /** Returns the linear factor in the attenuation formula.
        */
        Real getAttenuationLinear(void) const                       { return mAttenuationLinear; }

        /** Returns the quadric factor in the attenuation formula.
        */
        Real getAttenuationQuadric(void) const                      { return mAttenuationQuad; }

        /** Sets the direction in which a light points.
        @remarks
            Applicable only to the spotlight and directional light types.
        @note
            This direction will be concatenated with the parent SceneNode.
        */
        void setDirection(const Vector3& vec);

        /** Returns the light's direction.
        @remarks
            Applicable only to the spotlight and directional light types.
            Try to cache the value instead of calling it multiple times in the same scope
        */
        Vector3 getDirection(void) const;

		/** A Light must always have a Node attached to it. The direction is taken from
			the node's orientation, and thus setDirection modifies the attached node directly.
		@par
			However, when changing the range and the spot falloff; the node is not affected.
			This is intentional in case you want to create (e.g.) a node for a flashlight,
			and attach both the flashlight entity and the light to the same node; thus
			controlling the node moves both the flashlight and its visual effect.
		@par
			Despite this, there are cases where you want the changes to this light to be
			reflected in the parent node: The most common example are light volumes in
			deferred shading setups, and debug objects.
		@remarks
			This setting is only useful for non-directional lights.
			For point lights, the scale is calculated as setSize( range, range, range )
			which means a light volume should be a sphere of radius = 1;
		@par
			For spot lights, the scale is calc. as
				setSize( tan( outerAngle * 0.5 * range ), tan( outerAngle * 0.5 * range ), range );
			which means a light volume should be a cone with Z = 1, and X & Y = 2
		@param bAffect
			When true, the scene node is affected and modified by changes to range and falloff.
		*/
		void setAffectParentNode( bool bAffect );

		bool getAffectParentNode(void) const                        { return mAffectParentNode; }

        /** Sets the range of a spotlight, i.e. the angle of the inner and outer cones
            and the rate of falloff between them.
        @param innerAngle
            Angle covered by the bright inner cone
            @note
                The inner cone applicable only to Direct3D, it'll always treat as zero in OpenGL.
        @param outerAngle
            Angle covered by the outer cone
        @param falloff
            The rate of falloff between the inner and outer cones. 1.0 means a linear falloff,
            less means slower falloff, higher means faster falloff.
        */
        void setSpotlightRange(const Radian& innerAngle, const Radian& outerAngle, Real falloff = 1.0);

        /** Returns the angle covered by the spotlights inner cone.
        */
        const Radian& getSpotlightInnerAngle(void) const            { return mSpotInner; }

        /** Returns the angle covered by the spotlights outer cone.
        */
        const Radian& getSpotlightOuterAngle(void) const            { return mSpotOuter; }

        /** Returns the falloff between the inner and outer cones of the spotlight.
        */
        Real getSpotlightFalloff(void) const                        { return mSpotFalloff; }

        /** Sets the angle covered by the spotlights inner cone.
        */
        void setSpotlightInnerAngle(const Radian& val);

        /** Sets the angle covered by the spotlights outer cone.
        */
        void setSpotlightOuterAngle(const Radian& val);

        /** Sets the falloff between the inner and outer cones of the spotlight.
        */
        inline void setSpotlightFalloff(Real val);

        /** Set the near clip plane distance to be used by spotlights that use light
            clipping, allowing you to render spots as if they start from further
            down their frustum. 
        @param nearClip
            The near distance.
        */
        void setSpotlightNearClipDistance(Real nearClip) { mSpotNearClip = nearClip; }
        
        /** Get the near clip plane distance to be used by spotlights that use light
            clipping.
        */
        Real getSpotlightNearClipDistance() const { return mSpotNearClip; }
        
        /** Set a scaling factor to indicate the relative power of a light.
        @remarks
            This factor is only useful in High Dynamic Range (HDR) rendering.
            You can bind it to a shader variable to take it into account,
            @see GpuProgramParameters
        @param power
            The power rating of this light, default is 1.0.
        */
        void setPowerScale(Real power);

        /** Set the scaling factor which indicates the relative power of a 
            light.
        */
        Real getPowerScale(void) const                              { return mPowerScale; }

        /** @copydoc MovableObject::_updateRenderQueue */
        virtual void _updateRenderQueue(RenderQueue* queue, Camera *camera, const Camera *lodCamera) {}

        /** @copydoc MovableObject::getMovableType */
        const String& getMovableType(void) const;

        /** Retrieves the direction of the light including any transform from nodes it is attached to. */
        Vector3 getDerivedDirection(void) const;
        Vector3 getDerivedDirectionUpdated(void) const;

        /** @copydoc MovableObject::setVisible.
        @remarks
            Although lights themselves are not 'visible', setting a light to invisible
            means it no longer affects the scene.
        */
        //void setVisible(bool visible);

        /** Gets the details of this light as a 4D vector.
        @remarks
            Getting details of a light as a 4D vector can be useful for
            doing general calculations between different light types; for
            example the vector can represent both position lights (w=1.0f)
            and directional lights (w=0.0f) and be used in the same 
            calculations.
        */
        Vector4 getAs4DVector(void) const;

        /// Override to return specific type flag
        uint32 getTypeFlags(void) const;

        /// @copydoc AnimableObject::createAnimableValue
        AnimableValuePtr createAnimableValue(const String& valueName);

        /** Sets the maximum distance away from the camera that shadows
            by this light will be visible.
        @remarks
            Shadow techniques can be expensive, therefore it is a good idea
            to limit them to being rendered close to the camera if possible,
            and to skip the expense of rendering shadows for distance objects.
            This method allows you to set the distance at which shadows will no
            longer be rendered.
        @note
            Each shadow technique can interpret this subtely differently.
            For example, one technique may use this to eliminate casters,
            another might use it to attenuate the shadows themselves.
            You should tweak this value to suit your chosen shadow technique
            and scene setup.
        */
        void setShadowFarDistance(Real distance);
        /** Tells the light to use the shadow far distance of the SceneManager
        */
        void resetShadowFarDistance(void);
        /** Gets the maximum distance away from the camera that shadows
            by this light will be visible.
        */
        Real getShadowFarDistance(void) const;
        Real getShadowFarDistanceSquared(void) const;

        /** Set the near clip plane distance to be used by the shadow camera, if
            this light casts texture shadows.
        @param nearClip
            The distance, or -1 to use the main camera setting.
        */
        void setShadowNearClipDistance(Real nearClip) { mShadowNearClipDist = nearClip; }

        /** Get the near clip plane distance to be used by the shadow camera, if
            this light casts texture shadows.
        @remarks
            May be zero if the light doesn't have it's own near distance set;
            use _deriveShadowNearDistance for a version guaranteed to give a result.
        */
        Real getShadowNearClipDistance() const { return mShadowNearClipDist; }

        /** Derive a shadow camera near distance from either the light, or
            from the main camera if the light doesn't have its own setting.
        */
        Real _deriveShadowNearClipDistance(const Camera* maincam) const;

        /** Set the far clip plane distance to be used by the shadow camera, if
            this light casts texture shadows.
        @remarks
            This is different from the 'shadow far distance', which is
            always measured from the main camera. This distance is the far clip plane
            of the light camera.
        @param farClip
            The distance, or -1 to use the main camera setting.
        */
        void setShadowFarClipDistance(Real farClip) { mShadowFarClipDist = farClip; }

        /** Get the far clip plane distance to be used by the shadow camera, if
            this light casts texture shadows.
        @remarks
            May be zero if the light doesn't have it's own far distance set;
            use _deriveShadowfarDistance for a version guaranteed to give a result.
        */
        Real getShadowFarClipDistance() const { return mShadowFarClipDist; }

        /** Derive a shadow camera far distance from either the light, or
            from the main camera if the light doesn't have its own setting.
        */
        Real _deriveShadowFarClipDistance(const Camera* maincam) const;
                
        /** Check whether a sphere is included in the lighted area of the light 
        @note 
            The function trades accuracy for efficiency. As a result you may get
            false-positives (The function should not return any false-negatives).
        */
        bool isInLightRange(const Ogre::Sphere& sphere) const;
        
        /** Check whether a bounding box is included in the lighted area of the light
        @note 
            The function trades accuracy for efficiency. As a result you may get
            false-positives (The function should not return any false-negatives).
        */
        bool isInLightRange(const Ogre::AxisAlignedBox& container) const;
    
    protected:

        LightTypes mLightType;
        ColourValue mDiffuse;
        ColourValue mSpecular;

        Radian mSpotOuter;
        Radian mSpotInner;
        Real mSpotFalloff;
        Real mSpotNearClip;
        Real mRange;
        Real mAttenuationConst;
        Real mAttenuationLinear;
        Real mAttenuationQuad;
        Real mPowerScale;
        bool mOwnShadowFarDist;
		bool mAffectParentNode;
        Real mShadowFarDist;
        Real mShadowFarDistSquared;

        Real mShadowNearClipDist;
        Real mShadowFarClipDist;

        /// Shared class-level name for Movable type.
        static String msMovableType;
    };

    /** Factory object for creating Light instances. */
    class _OgreExport LightFactory : public MovableObjectFactory
    {
    protected:
        virtual MovableObject* createInstanceImpl( IdType id, ObjectMemoryManager *objectMemoryManager,
                                                   SceneManager *manager,
                                                   const NameValuePairList* params = 0 );
    public:
        LightFactory() {}
        ~LightFactory() {}

        static String FACTORY_TYPE_NAME;

        const String& getType(void) const;
        void destroyInstance(MovableObject* obj);  

    };
    /** @} */
    /** @} */

} // namespace Ogre

#include "OgreLight.inl"

#include "OgreHeaderPrefix.h"

#endif // __LIGHT_H__
