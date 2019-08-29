#version 110

#ifdef VERTEX_SHADER
uniform mat4 ProjectionMatrix;

attribute vec2 InPosition;
attribute vec4 InColor;
attribute vec2 InTexCoord;
attribute vec2 InTexEggCoord;

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

void main( void )
{
	gl_Position = ProjectionMatrix * vec4( InPosition, 0.0, 1.0 );
	Color = InColor;
	TexCoord = InTexCoord;
	TexEggCoord = InTexEggCoord;
}
#endif

#ifdef FRAGMENT_SHADER
uniform sampler2D ColorMap;
uniform sampler2D EggMap;

varying vec4 Color;
varying vec2 TexCoord;
varying vec2 TexEggCoord;

vec4 FormatColor( vec4 color )
{
	if( color.b - color.g > 0.01 ) 
	{
		if( color.b - color.r > 0.01 )
			return vec4( 0.0, 0.0, color.b, color.a );
		else if( color.r - color.b > 0.01 )
			return vec4( color.r, 0.0, 0.0, color.a );
		else return vec4( color.r, 0.0, color.b, color.a );
	}
	else if( color.g - color.b > 0.01 ) 
	{
		if( color.g - color.r > 0.01 )
			return vec4( 0.0, color.g, 0.0, color.a );
		else if( color.r - color.g > 0.01 )
			return vec4( color.r, 0.0, 0.0, color.a );
		else return vec4( color.r, color.g, 0.0, color.a );
	}
	else if( color.r - color.g > 0.01 ) 
	{
		if( color.r - color.b > 0.01 )
			return vec4( color.r, 0.0, 0.0, color.a );
		else if( color.b - color.r > 0.01 )
			return vec4( 0.0, 0.0, color.b, color.a );
		else return vec4( color.r, 0.0, color.b, color.a );
	}
	else if( color.r > 0.5 )
		return vec4( 1.0, 1.0, 1.0, color.a );
	return vec4( 0.0, 0.0, 0.0, color.a );
}

//#InCritter::effect Ice
void main( void ) 
{
	vec4 texColor = texture2D( ColorMap, TexCoord );
	vec4 newColor = FormatColor( texColor );
	
	if( newColor.r > 0.0 && newColor.r < 1.0 && ( newColor.g == 0.0 && newColor.b == 0.0 ) )
		gl_FragColor = mix( texColor, vec4( 0.5, 0.5, 0.0, 0.0 ), 0.4 );
	else
		gl_FragColor = texColor;
	
	/*if( newColor.r > 0.4 && newColor.r < 0.7 && ( newColor.g == 0.0 && newColor.b == 0.0 ) )
		gl_FragColor = mix( texColor, vec4( 0.0, 0.6, 0.6, newColor.a ), 0.6 );
	else*/
	//	gl_FragColor = texColor;
		
	//gl_FragColor = newColor;
	gl_FragColor.a = texColor.a * Color.a;
}

#endif
