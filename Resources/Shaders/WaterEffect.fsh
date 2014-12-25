varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

// get wave height based on distance-to-center
float waveHeight(vec2 p) {
    float timeFactor = 4.0;
    float texFactor = 12.0;
    float ampFactor = 0.01;
    float dist = length(p);
    return cos(CC_Time.y * timeFactor + dist * texFactor) * ampFactor;
}

// get point fake normal
vec3 waveNormal(vec2 p) {
    vec2 resolution = vec2(480, 320);
    float scale = 240;
    float waveHeightRight = waveHeight(p + vec2(2.0 / resolution.x, 0)) * scale;
    float waveHeightLeft = waveHeight(p - vec2(2.0 / resolution.x, 0)) * scale;
    float waveHeightTop = waveHeight(p + vec2(0, 2.0 / resolution.y)) * scale;
    float waveHeightBottom = waveHeight(p - vec2(0, 2.0 / resolution.y)) * scale;
    
    vec3 t = vec3(1, 0, waveHeightRight - waveHeightLeft);
    vec3 b = vec3(0, 1, waveHeightTop - waveHeightBottom);
    vec3 n = cross(t, b);
    
    return normalize(n);
}

void main() {
    vec2 p = -1.0 + 2.0 * v_texCoord;
    vec2 normal = normalize(p);
    
    v_texCoord += normal * waveHeight(p);
    
    vec4 lightColor = vec4(1, 1, 1, 1);
    vec3 lightDir = vec3(1, 1, 1);
    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor * lightColor * max(0, dot(lightDir, waveNormal(p)));
    gl_FragColor.a = 1;
}