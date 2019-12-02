#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

uniform sampler3D texture1;
uniform float stepsize;
uniform vec3 volExtentMin;
uniform vec3 volExtentMax;

void main()
{
    vec4 value;
    float scalar;
    vec4 dst = vec4(0,0,0,0);
    vec3 position = TexCoord;
    vec3 direction = vec3(0,0,1);
    direction = normalize(direction);
    //float Color;
    float Color;
    while(true) // Some large number
    {
        if(dst.w>1.0||position.z>1.0)
            break;
        value=texture(texture1, position);
        // Data access to scalar value in 3D volume texture  front to back
        dst.rgb=dst.rgb+value.rgb*value.w*(1-dst.w);
        dst.w = (1.0-dst.w) * value.w + dst.w;
        // Advance ray position along ray direction
        position = position + direction * 0.01;
    }
    FragColor=dst;
}