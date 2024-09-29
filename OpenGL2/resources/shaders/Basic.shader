#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;


out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform float angle;

void main()
{
    v_TexCoord = texCoord;

    //mat2 rotation = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    //vec2 rotatedPosition = rotation * position.xy;

    gl_Position = u_MVP * position;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
    color = u_Color;
}