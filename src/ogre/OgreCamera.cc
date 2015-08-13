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
#include "ignition/rendering/ogre/OgreCamera.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/ogre/OgreRenderTarget.hh"
#include "ignition/rendering/ogre/OgreScene.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
OgreCamera::OgreCamera() :
  renderTexture(NULL)
{
}

//////////////////////////////////////////////////
OgreCamera::~OgreCamera()
{
}

//////////////////////////////////////////////////
PixelFormat OgreCamera::GetImageFormat() const
{
  return this->renderTexture->GetFormat();
}

//////////////////////////////////////////////////
void OgreCamera::SetImageFormat(PixelFormat _format)
{
  this->renderTexture->SetFormat(_format);
}

//////////////////////////////////////////////////
gazebo::math::Angle OgreCamera::GetHFOV() const
{
  return this->xfov;
}

//////////////////////////////////////////////////
void OgreCamera::SetHFOV(const gazebo::math::Angle &_angle)
{
  double width  = static_cast<double>(this->GetImageWidth());
  double height = static_cast<double>(this->GetImageHeight());
  double ratio  = width / height;

  double hfov = _angle.Radian();
  double vfov = 2.0 * atan(tan(hfov / 2.0) / ratio);

  this->ogreCamera->setAspectRatio(ratio);
  this->ogreCamera->setFOVy(Ogre::Radian(vfov));
  this->xfov = _angle;
}

//////////////////////////////////////////////////
double OgreCamera::GetAspectRatio() const
{
  return this->ogreCamera->getAspectRatio();
}

//////////////////////////////////////////////////
void OgreCamera::SetAspectRatio(double _ratio)
{
  return this->ogreCamera->setAspectRatio(_ratio);
}

//////////////////////////////////////////////////
unsigned int OgreCamera::GetAntiAliasing() const
{
  return this->renderTexture->GetAntiAliasing();
}

//////////////////////////////////////////////////
void OgreCamera::SetAntiAliasing(unsigned int _aa)
{
  this->renderTexture->SetAntiAliasing(_aa);
}

//////////////////////////////////////////////////
void OgreCamera::Render()
{
  this->renderTexture->Render();
}

//////////////////////////////////////////////////
RenderTexturePtr OgreCamera::GetRenderTexture() const
{
  return this->renderTexture;
}

//////////////////////////////////////////////////
void OgreCamera::Init()
{
  BaseCamera::Init();
  this->CreateCamera();
  this->CreateRenderTexture();
  this->Reset();
}

//////////////////////////////////////////////////
void OgreCamera::CreateCamera()
{
  // create ogre camera object
  Ogre::SceneManager *ogreSceneManager;
  ogreSceneManager = this->scene->GetOgreSceneManager();
  this->ogreCamera = ogreSceneManager->createCamera(this->name);
  this->ogreNode->attachObject(this->ogreCamera);

  // rotate to Gazebo coordinate system
  this->ogreCamera->yaw(Ogre::Degree(-90.0));
  this->ogreCamera->roll(Ogre::Degree(-90.0));
  this->ogreCamera->setFixedYawAxis(false);

  // TODO: provide api access
  this->ogreCamera->setAutoAspectRatio(true);
  this->ogreCamera->setNearClipDistance(0.001);
  this->ogreCamera->setFarClipDistance(1000);
  this->ogreCamera->setRenderingDistance(0);
  this->ogreCamera->setAspectRatio(1);
  this->ogreCamera->setPolygonMode(Ogre::PM_SOLID);
  this->ogreCamera->setFOVy(Ogre::Degree(80));
  this->ogreCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
  this->ogreCamera->setCustomProjectionMatrix(false);
}

//////////////////////////////////////////////////
void OgreCamera::CreateRenderTexture()
{
  RenderTexturePtr base = this->scene->CreateRenderTexture();
  this->renderTexture = boost::dynamic_pointer_cast<OgreRenderTexture>(base);
  this->renderTexture->SetCamera(this->ogreCamera);
  this->renderTexture->SetFormat(PF_R8G8B8);
}
