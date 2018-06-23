 const char *fragmentShaderCode = "#version 400\n												\
									out	vec4 out_Color;													\
									in vec4 ex_Color;													\
									in vec2 ex_TexCoord;												\
									uniform sampler2D uTexture;											\
									void main()															\
									{																	\
											out_Color	=	texture2D(uTexture,ex_TexCoord);			\
									}";