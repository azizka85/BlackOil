attribute highp vec4 a_position;
attribute highp vec3 a_index;
uniform highp mat4 u_modelViewMatrix;
uniform highp mat4 u_projectionMatrix;
uniform highp float u_scaleX;
uniform highp float u_scaleY;
uniform highp float u_scaleZ;
varying highp vec3 v_index;

void main(void)
{
    vec4 position = a_position;

    position.x = u_scaleX * position.x;
    position.y = u_scaleY * position.y;
    position.z = u_scaleZ * position.z;

    gl_Position = u_projectionMatrix * u_modelViewMatrix * position;

    v_index = a_index;
}
