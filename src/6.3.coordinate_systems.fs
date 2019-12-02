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
    // Loop for ray traversal
    while(true) // Some large number
    {
        if(dst.w>1.0)
            break;
        Color=texture(texture1, position).r;
        if(Color==1)
            value = vec4(1,0,0,0.5);
        else
            value=vec4(1,1,1,0.);
        // Data access to scalar value in 3D volume texture
        dst.rgb=dst.rgb*dst.w+value.rgb*value.w*(1-dst.w);
        dst.w = (1.0-dst.w) * value.w + dst.w;
        
        // Advance ray position along ray direction
        position = position + direction * 0.02;
        if(position.z>1)
            break;
    }
    FragColor=dst;
}