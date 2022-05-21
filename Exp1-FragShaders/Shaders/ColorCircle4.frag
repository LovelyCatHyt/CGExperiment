#version 430 core
in vec4 color;
in vec2 screenPosition;
out vec4 fColor;

float get_chessBoard(vec2 pos, float scale)
{
	// 棋盘格
	// 扩大, 然后向下取整
	vec2 scaledPos = 8 * pos;
	scaledPos.x = scaledPos.x - fract(scaledPos.x);
	scaledPos.y = scaledPos.y - fract(scaledPos.y);
	// 判断 x+y 奇偶性
	float white = scaledPos.x + scaledPos.y;
	return step(fract(white/2),0);
}

void main()
{
	vec2 pos = screenPosition.xy;
	pos = pos * pos;
	float dist = sqrt(pos.x + pos.y);
			
	if(dist>=1)
	{
		fColor = vec4(0,0,0,1) + vec4(.6,.6,.6,1) * get_chessBoard(screenPosition.xy, 8);
	}
	else
	{
		vec2 mutatedPos = normalize(screenPosition.xy) * (dist * dist);
		fColor = vec4(0,0,0,1) + vec4(.6,.6,.6,1) * get_chessBoard(mutatedPos, 8);
	}
}

