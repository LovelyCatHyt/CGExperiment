#version 430 core
in vec4 color;
in vec2 screenPosition;
out vec4 fColor;

uniform mat4 projectMat;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	//float b = 3.1f;
	//mat4 m = mat4(1);
	//vec4 v = m[0];
	//fColor = vec4(1.0, 1.0, 1.0, 1.0)*v;
	vec3 hsv = rgb2hsv(color.rgb);
	// (1/2pi) = 0.15915494309189533576888376337251
	hsv.x =  fract(hsv.x + atan(screenPosition.y, screenPosition.x)*0.1591549430);
	vec2 pos = screenPosition.xy;
	pos = pos * pos;
	float dist = sqrt(pos.x + pos.y);
	
	if(dist<1)
	{
		fColor = vec4(hsv2rgb(hsv), 1.0);
	}else
	{
		// white background
		fColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
}

