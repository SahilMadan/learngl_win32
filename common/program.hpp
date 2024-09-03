#ifndef LEARNGL_WIN32_COMMON_SHADER_HPP_
#define LEARNGL_WIN32_COMMON_SHADER_HPP_

unsigned int InitPipeline(const char* vertex_path, const char* fragment_path);
void UsePipeline(unsigned int pipeline_program);
void SetPipelineUniformBool(unsigned int pipeline_program, const char* name,
                            bool value);
void SetPipelineUniformInt(unsigned int pipeline_program, const char* name,
                           int value);
void SetPipelineUniformFloat(unsigned int pipeline_program, const char* name,
                             float value);

#endif