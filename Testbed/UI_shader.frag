#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;


void main()
{    
    color = vec4(1.0,1.0,1.0, 1.0) * texture(image, TexCoords);
}