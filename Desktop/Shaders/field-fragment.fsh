uniform highp bool u_lightEnabled;
uniform highp vec3 u_selectedIndex;
uniform highp float u_paletteTransparency;
uniform highp vec3 u_color;

varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec3 v_index;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, u_paletteTransparency);

    vec3 diffColor = u_color;

    if(u_lightEnabled)
    {
        vec3 lightPosition = vec3(0.0f, 0.0f, 0.0f);
        vec3 lightVector = normalize(v_position.xyz - lightPosition);

        float colorIntensity = abs(dot(v_normal, -lightVector));

        diffColor = diffColor * colorIntensity;
    }

    resultColor.rgb += diffColor;

    float sFactor = exp2(-1000.0*length(v_index - u_selectedIndex));

    resultColor.rgb = (1.0 - 0.5*sFactor)*resultColor.rgb + 0.5*sFactor*vec3(1.0, 1.0, 1.0);

    gl_FragColor = resultColor;
}
