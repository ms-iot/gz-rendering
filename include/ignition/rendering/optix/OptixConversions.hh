/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _IGNITION_RENDERING_OPTIXCONVERSIONS_HH_
#define _IGNITION_RENDERING_OPTIXCONVERSIONS_HH_

#include "gazebo/common/Color.hh"
#include "gazebo/math/Quaternion.hh"
#include "gazebo/math/Vector3.hh"
#include "ignition/rendering/PixelFormat.hh"
#include "ignition/rendering/optix/OptixIncludes.hh"
#include "gazebo/util/system.hh"

namespace ignition
{
  namespace rendering
  {
    /// \addtogroup gazebo_rendering
    /// \{

    /// \brief Conversions Conversions.hh rendering/Conversions.hh
    /// \brief A set of utility function to convert between Gazebo and Optix
    /// data types
    class IGNITION_VISIBLE OptixConversions
    {
      /// \brief Return the equivalent optix color
      /// \param[in] _color Gazebo color to convert
      /// \return Optix color value
      public: static float4 ConvertColor(const gazebo::common::Color &_color);

      /// \brief Return the equivalent gazebo color
      /// \param[in] _color Optix color to convert
      /// \return Gazebo color value
      public: static gazebo::common::Color ConvertColor(const float4 &_color);

      /// \brief return Optix Vector from Gazebo Vector3
      /// \param[in] _vector Gazebo vector
      /// \return Optix vector
      public: static float3 ConvertVector(const gazebo::math::Vector3 &_vector);

      /// \brief return gazebo Vector from optix Vector3
      /// \param[in] _vector Optix vector
      /// \return Gazebo vector
      public: static gazebo::math::Vector3 ConvertVector(const float3 &_vector);
    };

    /// \}
  }
}
#endif
