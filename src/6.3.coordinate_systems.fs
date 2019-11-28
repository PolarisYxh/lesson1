#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

uniform sampler3D texture1;
uniform float stepsize;
uniform vec3 volExtentMin;
uniform vec3 volExtentMax;

void main()
{
    //FragColor=vec4(0.0f,0.0f,0.0f,1.0f);
    //FragColor = texture(texture1, TexCoord);
    vec4 value;
    float scalar;
    //vec3 vpos=FromtPosTovPos;
    // Initialize accumulated color and opacity
    vec4 dst = vec4(0,0,0,0);
    // Determine volume entry position
    vec3 position = TexCoord;
    // Compute ray direction
    //vec3 direction = TexCoord.xyz - vec3(0,0,3);
    vec3 direction = vec3(0,0,1);
    direction = normalize(direction);
    //float Color;
    FragColor = vec4(texture(texture1, position).rrr,1);
    // Loop for ray traversal
    /*for (int i = 0; i < 200; i++) // Some large number
    {

        // Data access to scalar value in 3D volume texture
        Color = texture(texture1, position).r;
        if(Color>0.5)value=vec4(0,0,1,0.5);
        else if(Color<=0.5)value=vec4(0,1,0,0.);

        scalar = value.x;
        // Apply transfer function
        //float4 src = tex1D(SamplerTransferFunction, scalar);
        // Front-to-back compositing
        dst = (1.0-dst.w) * value + dst;
        // Advance ray position along ray direction
        position = position + direction * stepsize;
        vec3 temp1 = sign(position - volExtentMin);
        vec3 temp2 = sign(volExtentMax - position);
        float inside = dot(temp1, temp2);
        // ... and exit loop
        if (inside < 3.0)
            break;
    }*/
    //FragColor=value;
   // FragColor=vec4(Color,0,0,1);
}