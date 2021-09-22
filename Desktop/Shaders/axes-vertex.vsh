attribute highp vec4 a_position;
attribute highp vec3 a_color;
uniform highp mat4 u_transformMatrix;
uniform highp float u_axesLength;
varying highp vec3 v_color;

void main(void)
{
    vec4 position = a_position;

    position.xyz = u_axesLength * position.xyz;

    gl_Position = u_transformMatrix * position;

    v_color = a_color;
}
