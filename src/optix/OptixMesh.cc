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
#include "ignition/rendering/optix/OptixMesh.hh"
#include "ignition/rendering/optix/OptixIncludes.hh"
#include "ignition/rendering/optix/OptixMaterial.hh"
#include "ignition/rendering/optix/OptixStorage.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
// OptixMesh
//////////////////////////////////////////////////
OptixMesh::OptixMesh()
{
}

//////////////////////////////////////////////////
OptixMesh::~OptixMesh()
{
}

//////////////////////////////////////////////////
optix::GeometryGroup OptixMesh::GetOptixGeometryGroup() const
{
  return this->optixGeomGroup;
}

//////////////////////////////////////////////////
optix::Acceleration OptixMesh::GetOptixAccel() const
{
  return this->optixAccel;
}

//////////////////////////////////////////////////  
SubMeshStorePtr OptixMesh::GetSubMeshes() const
{
  return this->subMeshes;
}

//////////////////////////////////////////////////
// OptixSubMesh
//////////////////////////////////////////////////
OptixSubMesh::OptixSubMesh()
{
}

//////////////////////////////////////////////////
OptixSubMesh::~OptixSubMesh()
{
}

//////////////////////////////////////////////////
MaterialPtr OptixSubMesh::GetMaterial() const
{
  return this->material;
}

//////////////////////////////////////////////////
void OptixSubMesh::SetMaterial(MaterialPtr _material, bool unique)
{
  _material = (unique) ? _material->Clone() : _material;

  OptixMaterialPtr derived =
      boost::dynamic_pointer_cast<OptixMaterial>(_material);

  if (!derived)
  {
    gzerr << "Cannot assign material created by another render-engine"
        << std::endl;

    return;
  }

  this->SetMaterialImpl(derived);
}

//////////////////////////////////////////////////
optix::GeometryInstance OptixSubMesh::GetOptixGeometryInstance() const
{
  return this->optixGeomInstance;
}

//////////////////////////////////////////////////
void OptixSubMesh::SetMaterialImpl(OptixMaterialPtr _material)
{
  optix::Material optixMaterial = _material->GetOptixMaterial();
  this->optixGeomInstance->setMaterialCount(0);
  this->optixGeomInstance->addMaterial(optixMaterial);
  this->material = _material;
}
