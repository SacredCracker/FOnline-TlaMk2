#version 110

#ifdef VERTEX_SHADER
uniform mat4 ProjectionMatrix;

attribute vec2 InPosition;
attribute vec4 InColor;
attribute vec2 InTexCoord;

varying vec4 Color;
varying vec2 TexCoord;

void main( void )
{
	gl_Position = ProjectionMatrix * vec4( InPosition, 0.0, 1.0 );
	Color = InColor;
	TexCoord = InTexCoord;
}
#endif

#ifdef FRAGMENT_SHADER
uniform sampler2D ColorMap;

varying vec4 Color;
varying vec2 TexCoord;

const vec3 c_LuminanceWeight = vec3 ( 0.2126, 0.7152, 0.072 );

void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord ) * Color;
    
	if( gl_FragColor.r < 0.05 && gl_FragColor.g < 0.05 && gl_FragColor.b < 0.05 )
		gl_FragColor.a = 0.0;
	else
	{
		vec3 color_weighted = gl_FragColor.rgb * c_LuminanceWeight;
		float luminance = color_weighted.r + color_weighted.g + color_weighted.b;
		vec4 luminance_color = vec4 ( luminance, luminance, luminance, gl_FragColor.a );
		
		gl_FragColor = luminance_color * Color;
	
		gl_FragColor.rgb = 1.0 - gl_FragColor.rgb;
		gl_FragColor.a *= luminance;
	}
}

#endif
