attribute highp vec4 a_position;
attribute highp vec3 a_normal;
attribute highp vec3 a_index;
uniform highp mat4 u_modelViewMatrix;
uniform highp mat4 u_projectionMatrix;
uniform highp float u_scaleX;
uniform highp float u_scaleY;
uniform highp float u_scaleZ;
varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec3 v_index;

void main(void)
{
    vec4 position = a_position;

    position.x = u_scaleX * position.x;
    position.y = u_scaleY * position.y;
    position.z = u_scaleZ * position.z;

    vec3 normal = a_normal;

    normal.x = u_scaleY * u_scaleZ * normal.x;
    normal.y = u_scaleX * u_scaleZ * normal.y;
    normal.z = u_scaleX * u_scaleY * normal.z;

    gl_Position = u_projectionMatrix * u_modelViewMatrix * position;

    v_index = a_index;
    v_normal = normalize(vec3(u_modelViewMatrix * vec4(normal, 0.0)));
    v_position = u_modelViewMatrix * position;
}
