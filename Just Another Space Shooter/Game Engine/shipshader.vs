 const char *VertexShaderCode = "#version 400\n												\
									layout(location = 0) in vec3 in_Position;					\
									layout(location = 1) in vec4 in_Color;						\
									layout(location = 2) in vec2 in_TexCoord;					\
									uniform mat4 ml_matrix;										\
									out vec4 ex_Color;											\
									out vec2 ex_TexCoord;										\
									void main()													\
									{															\
										 gl_Position = ml_matrix*vec4(in_Position,1.0);			\
										 ex_Color = in_Color;									\
										 ex_TexCoord = in_TexCoord;								\
									}";
