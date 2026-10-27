#version 450 core

layout(location = 0) in vec3 in_world_position;
layout(location = 1) in vec3 in_world_normal;

layout(location = 0) out vec4 out_color;

layout(std140, set = 0, binding = 0) uniform GlobalUniforms {
	mat4 view_projection;
	mat4 model;
	vec4 camera_position;
	vec4 ambient;
	vec4 light_direction;
	vec4 light_color;
	vec4 albedo;
	vec4 specular;
} global_uniforms;

void main() {
	vec3 albedo = global_uniforms.albedo.rgb;
	vec3 specular_color = global_uniforms.specular.rgb;
	float shininess = global_uniforms.specular.w;

	vec3 N = normalize(in_world_normal);                                              // where the surface faces
	vec3 L = normalize(-global_uniforms.light_direction.xyz);                         // towards the light
	vec3 V = normalize(global_uniforms.camera_position.xyz - in_world_position);      // towards the camera
	vec3 H = normalize(L + V);                                                        // halfway vector

	vec3 ambient = global_uniforms.ambient.rgb * global_uniforms.ambient.w * albedo;
	vec3 diffuse = albedo * max(dot(N, L), 0.0);
	vec3 specular = specular_color * pow(max(dot(N, H), 0.0), shininess);
	vec3 light = global_uniforms.light_color.rgb * global_uniforms.light_color.w;

	out_color = vec4(ambient + light * (diffuse + specular), 1);
}