#include "runtime/function/render/include/render/surface.h"

#include "runtime/engine.h"
namespace Pilot
{
    bool Surface::tick(const FrameBuffer* framebuffer, UIState* uistate, SceneReleaseHandles& release_handles)
    {
        if (m_io->tick_NotQuit())
        {
            if (framebuffer && framebuffer->m_scene && framebuffer->m_scene->m_loaded)
            {
                m_rhi->tick(framebuffer, release_handles, uistate);
            }
            if (g_is_editor_mode == false)
            {
                glfwSetInputMode(
                    m_io->m_window, GLFW_CURSOR, m_io->m_is_focus_mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void Surface::updateWindow(float pos_x, float pos_y, float width, float height) const
    {
        VkViewport viewport;
        viewport.x        = pos_x;
        viewport.y        = pos_y;
        viewport.width    = width;
        viewport.height   = height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        m_ui->m_tmp_uistate->m_editor_camera->setAspect(width / height);
        m_rhi->m_vulkan_manager->updateUIRenderSceneViewport(viewport);
    }


    size_t Surface::getGuidOfPickedMesh(const Vector2& picked_uv) const
    {
        return m_rhi->m_vulkan_manager->getGuidOfPickedMesh(picked_uv);
    }

	void Surface::setSceneSelectedAxis(size_t selected_axis)
	{
		m_rhi->m_vulkan_manager->setSelectedAxis(selected_axis);
	}

} // namespace Pilot
