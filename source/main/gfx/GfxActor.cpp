#include "GfxActor.h"

#include "Beam.h"
#include "GlobalEnvironment.h" // TODO: Eliminate!
#include "SkyManager.h"

#include <OgreResourceGroupManager.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
#include <OgrePass.h>

RoR::GfxActor::~GfxActor()
{
    // Dispose videocameras
    this->SetVideoCamState(VideoCamState::VCSTATE_DISABLED);
    while (!m_videocameras.empty())
    {
        VideoCamera& vcam = m_videocameras.back();
        Ogre::TextureManager::getSingleton().remove(vcam.vcam_render_tex->getHandle());
        vcam.vcam_render_tex.setNull();
        vcam.vcam_render_target = nullptr; // Invalidated with parent texture
        gEnv->sceneManager->destroyCamera(vcam.vcam_ogre_camera);

        m_videocameras.pop_back();
    }

    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(m_custom_resource_group);
}

void RoR::GfxActor::AddMaterialFlare(int flareid, Ogre::MaterialPtr m)
{
    RoR::GfxActor::FlareMaterial binding;
    binding.flare_index = flareid;
    binding.mat_instance = m;

    if (m.isNull())
        return;
    Ogre::Technique* tech = m->getTechnique(0);
    if (!tech)
        return;
    Ogre::Pass* p = tech->getPass(0);
    if (!p)
        return;
    // save emissive colour and then set to zero (light disabled by default)
    binding.emissive_color = p->getSelfIllumination();
    p->setSelfIllumination(Ogre::ColourValue::ZERO);

    m_flare_materials.push_back(binding);
}

void RoR::GfxActor::SetMaterialFlareOn(int flare_index, bool state_on)
{
    for (FlareMaterial& entry: m_flare_materials)
    {
        if (entry.flare_index != flare_index)
        {
            continue;
        }

        const int num_techniques = static_cast<int>(entry.mat_instance->getNumTechniques());
        for (int i = 0; i < num_techniques; i++)
        {
            Ogre::Technique* tech = entry.mat_instance->getTechnique(i);
            if (!tech)
                continue;

            if (tech->getSchemeName() == "glow")
            {
                // glowing technique
                // set the ambient value as glow amount
                Ogre::Pass* p = tech->getPass(0);
                if (!p)
                    continue;

                if (state_on)
                {
                    p->setSelfIllumination(entry.emissive_color);
                    p->setAmbient(Ogre::ColourValue::White);
                    p->setDiffuse(Ogre::ColourValue::White);
                }
                else
                {
                    p->setSelfIllumination(Ogre::ColourValue::ZERO);
                    p->setAmbient(Ogre::ColourValue::Black);
                    p->setDiffuse(Ogre::ColourValue::Black);
                }
            }
            else
            {
                // normal technique
                Ogre::Pass* p = tech->getPass(0);
                if (!p)
                    continue;

                Ogre::TextureUnitState* tus = p->getTextureUnitState(0);
                if (!tus)
                    continue;

                if (tus->getNumFrames() < 2)
                    continue;

                int frame = state_on ? 1 : 0;

                tus->setCurrentFrame(frame);

                if (state_on)
                    p->setSelfIllumination(entry.emissive_color);
                else
                    p->setSelfIllumination(Ogre::ColourValue::ZERO);
            }
        } // for each technique
    }
}

void RoR::GfxActor::RegisterCabMaterial(Ogre::MaterialPtr mat, Ogre::MaterialPtr mat_trans)
{
    // Material instances of this actor
    m_cab_mat_visual = mat;
    m_cab_mat_visual_trans = mat_trans;

    if (mat->getTechnique(0)->getNumPasses() == 1)
        return; // No emissive pass -> nothing to do.

    m_cab_mat_template_emissive = mat->clone("CabMaterialEmissive-" + mat->getName(), true, m_custom_resource_group);

    m_cab_mat_template_plain = mat->clone("CabMaterialPlain-" + mat->getName(), true, m_custom_resource_group);
    m_cab_mat_template_plain->getTechnique(0)->removePass(1);
    m_cab_mat_template_plain->compile();
}

void RoR::GfxActor::SetCabLightsActive(bool state_on)
{
    if (m_cab_mat_template_emissive.isNull()) // Both this and '_plain' are only set when emissive pass is present.
        return;

    // NOTE: Updating material in-place like this is probably inefficient,
    //       but in order to maintain all the existing material features working together,
    //       we need to avoid any material swapping on runtime. ~ only_a_ptr, 05/2017
    Ogre::MaterialPtr template_mat = (state_on) ? m_cab_mat_template_emissive : m_cab_mat_template_plain;
    Ogre::Technique* dest_tech = m_cab_mat_visual->getTechnique(0);
    Ogre::Technique* templ_tech = template_mat->getTechnique(0);
    dest_tech->removeAllPasses();
    for (unsigned short i = 0; i < templ_tech->getNumPasses(); ++i)
    {
        Ogre::Pass* templ_pass = templ_tech->getPass(i);
        Ogre::Pass* dest_pass = dest_tech->createPass();
        *dest_pass = *templ_pass; // Copy the pass! Reference: http://www.ogre3d.org/forums/viewtopic.php?f=2&t=83453
    }
    m_cab_mat_visual->compile();
}

void RoR::GfxActor::SetVideoCamState(VideoCamState state)
{
    if (state == m_vidcam_state)
    {
        return;
    }

    const bool enable = (state == VideoCamState::VCSTATE_ENABLED_ONLINE);
    for (VideoCamera vidcam: m_videocameras)
    {
        if (vidcam.vcam_render_target != nullptr)
        {
            vidcam.vcam_render_target->setActive(enable);
            if (enable)
                vidcam.vcam_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(vidcam.vcam_render_tex->getName());
            else
                vidcam.vcam_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(vidcam.vcam_off_tex_name);
            continue;
        }

        if (vidcam.vcam_render_window != nullptr)
        {
            vidcam.vcam_render_window->setActive(enable);
        }
    }
    m_vidcam_state = state;
}

void RoR::GfxActor::UpdateVideoCameras(float dt_sec)
{
    if (m_vidcam_state != VideoCamState::VCSTATE_ENABLED_ONLINE)
        return;

    for (GfxActor::VideoCamera vidcam: m_videocameras)
    {
#ifdef USE_CAELUM
        // caelum needs to know that we changed the cameras
        if (gEnv->sky && RoR::App::GetActiveAppState() == RoR::App::APP_STATE_SIMULATION)
        {
            gEnv->sky->notifyCameraChanged(vidcam.vcam_ogre_camera);
        }

#endif // USE_CAELUM

        // update the texture now, otherwise shuttering
        if (vidcam.vcam_render_target != nullptr)
            vidcam.vcam_render_target->update();

        if (vidcam.vcam_render_window != nullptr)
            vidcam.vcam_render_window->update();

        // get the normal of the camera plane now
        const Ogre::Vector3 abs_pos_center = vidcam.vcam_node_center->AbsPosition;
        const Ogre::Vector3 abs_pos_z = vidcam.vcam_node_dir_z->AbsPosition;
        const Ogre::Vector3 abs_pos_y = vidcam.vcam_node_dir_y->AbsPosition;
        Ogre::Vector3 normal = (-(abs_pos_center - abs_pos_z)).crossProduct(-(abs_pos_center - abs_pos_y));
        normal.normalise();

        // add user set offset
        Ogre::Vector3 pos = vidcam.vcam_node_alt_pos->AbsPosition +
            (vidcam.vcam_pos_offset.x * normal) +
            (vidcam.vcam_pos_offset.y * (abs_pos_center - abs_pos_y)) +
            (vidcam.vcam_pos_offset.z * (abs_pos_center - abs_pos_z));

        //avoid the camera roll
        // camup orientates to frustrum of world by default -> rotating the cam related to trucks yaw, lets bind cam rotation videocamera base (nref,ny,nz) as frustum
        // could this be done faster&better with a plane setFrustumExtents ?
        Ogre::Vector3 frustumUP = abs_pos_center - abs_pos_y;
        frustumUP.normalise();
        vidcam.vcam_ogre_camera->setFixedYawAxis(true, frustumUP);

        if (vidcam.vcam_type == GfxActor::VideoCamType::VCTYPE_MIRROR)
        {
            //rotate the normal of the mirror by user rotation setting so it reflects correct
            normal = vidcam.vcam_rotation * normal;
            // merge camera direction and reflect it on our plane
            vidcam.vcam_ogre_camera->setDirection((pos - gEnv->mainCamera->getPosition()).reflect(normal));
        }
        else if (vidcam.vcam_type == GfxActor::VideoCamType::VCTYPE_VIDEOCAM)
        {
            // rotate the camera according to the nodes orientation and user rotation
            Ogre::Vector3 refx = abs_pos_z - abs_pos_center;
            refx.normalise();
            Ogre::Vector3 refy = abs_pos_center - abs_pos_y;
            refy.normalise();
            Ogre::Quaternion rot = Ogre::Quaternion(-refx, -refy, -normal);
            vidcam.vcam_ogre_camera->setOrientation(rot * vidcam.vcam_rotation); // rotate the camera orientation towards the calculated cam direction plus user rotation
        }
        else if (vidcam.vcam_type == GfxActor::VideoCamType::VCTYPE_TRACKING_VIDEOCAM)
        {
            normal = vidcam.vcam_node_lookat->AbsPosition - pos;
            normal.normalise();
            Ogre::Vector3 refx = abs_pos_z - abs_pos_center;
            refx.normalise();
            // why does this flip ~2-3� around zero orientation and only with trackercam. back to slower crossproduct calc, a bit slower but better .. sigh
            // Ogre::Vector3 refy = abs_pos_center - abs_pos_y;
            Ogre::Vector3 refy = refx.crossProduct(normal);
            refy.normalise();
            Ogre::Quaternion rot = Ogre::Quaternion(-refx, -refy, -normal);
            vidcam.vcam_ogre_camera->setOrientation(rot * vidcam.vcam_rotation); // rotate the camera orientation towards the calculated cam direction plus user rotation
        }

        if (vidcam.vcam_debug_node != nullptr)
        {
            vidcam.vcam_debug_node->setPosition(pos);
            vidcam.vcam_debug_node->setOrientation(vidcam.vcam_ogre_camera->getOrientation());
        }

        // set the new position
        vidcam.vcam_ogre_camera->setPosition(pos);
    }
}
