#version 310 es
precision highp float;

layout(location = COLOR0) in vec4 v_color;
layout(location = TEXCOORD0) in vec2 v_texCoord;

layout(binding = 0) uniform sampler2D u_tex0;

layout(std140) uniform fs_ub {
    vec4 u_textColor;
    vec4 u_effectColor;
};

layout(location = SV_Target0) out vec4 FragColor;

void main()
{
    float dist = texture(u_tex0, v_texCoord).x;
#ifdef GLES2
    float width = 0.04;
#else
    float width = fwidth(dist);
#endif
    float alpha = smoothstep(0.5-width, 0.5+width, dist);
    //glow
    float mu = smoothstep(0.5, 1.0, sqrt(dist));
    vec4 color = u_effectColor*(1.0-alpha) + u_textColor*alpha;
    FragColor = v_color * vec4(color.rgb, max(alpha,mu)*color.a);
}
