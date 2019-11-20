#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

uniform sampler3D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
    //FragColor=vec4(1.0f,0.0f,0.0f,0.5f);
}