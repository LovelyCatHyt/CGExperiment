#version 430 core
in vec4 color;
in vec2 screenPosition;
out vec4 fColor;

void main()
{
	//float b = 3.1f;
	//mat4 m = mat4(1);
	//vec4 v = m[0];
	//fColor = vec4(1.0, 1.0, 1.0, 1.0)*v;
	vec2 pos = screenPosition.xy;
	pos = pos * pos;
	float dist = sqrt(pos.x + pos.y);

	// 棋盘格
	// 扩大, 然后离散化
	vec2 scaledPos = 8 * screenPosition;
	scaledPos.x = scaledPos.x - fract(scaledPos.x);
	scaledPos.y = scaledPos.y - fract(scaledPos.y);
	// 判断 x+y 奇偶性
	float white = scaledPos.x + scaledPos.y;
	white = step(fract(white/2),0);
		
	if(dist<1)
	{
		white = 1 - white;
	}

	fColor = vec4(0,0,0,1) + vec4(.6,.6,.6,1) * white;
}

