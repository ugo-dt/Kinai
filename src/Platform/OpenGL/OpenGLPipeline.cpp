#include "Kinai/Platform/OpenGL/OpenGLPipeline.hpp"

namespace Kinai
{

OpenGLPipeline::OpenGLPipeline(const PipelineConfig& config)
{
	KN_PRINT_FUNC();

	this->_vao = config.vao;
	this->_shader = config.shader;
	this->_layout = config.layout;
	this->_primitive_type = config.primitive_type;
	this->_cull_mode = config.cull_mode;
	this->_face_winding = config.face_winding;
	this->_label = config.label;
}

} // Kinai
