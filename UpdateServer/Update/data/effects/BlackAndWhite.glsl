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

const vec3 c_LuminanceWeight = vec3 ( 0.2126, 0.7152, 0.072 );

// BlackAndWhite
void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord );
    
    vec3 color_weighted = gl_FragColor.rgb * c_LuminanceWeight;
    float luminance = color_weighted.r + color_weighted.g + color_weighted.b;
    vec4 luminance_color = vec4 ( luminance, luminance, luminance, gl_FragColor.a );
    
    gl_FragColor = luminance_color * Color;
}

#endif
