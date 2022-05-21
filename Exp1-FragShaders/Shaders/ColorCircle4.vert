#version 430 core
layout(location = 0) in vec4 vPosition;
out vec4 color;
out vec2 screenPosition;
uniform float ModeColor;

void main()
{ 
	gl_Position = vPosition;
	screenPosition = vPosition.xy;
	/*color = vPosition;*/
	color = vec4(1,0,0,1);
	/*if(vPosition.x <= 0)
	{
		if(vPosition.y <= 0)
			color = vec4(1.0,0.0,0.0,0.0);
		else
			color = vec4(1.0,1.0,0.0,0.0);
	}
	else
	{
		if(vPosition.y <= 0)
			color = vec4(0.0,1.0,1.0,0.0);
		else
			color = vec4(0.0,0.0,1.0,0.0);
	}
	*/
	//gl_PointSize = 30.0f;
}