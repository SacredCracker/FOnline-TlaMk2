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

varying vec2 TexCoord;
varying vec4 Color;

vec3 u_SourceColor = vec3( 0.3, 0.3, 0.0 );
vec3 u_TargetColor = vec3( 0.27, 0.3, 0.18 );

float u_Tolerance = 0.4;
float u_Falloff = 0.7;

float manhattan_length ( vec3 a )
{
    return abs( a.x ) + abs ( a.y ) + abs ( a.z );
}

void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord );
    
    float overlap = manhattan_length ( gl_FragColor.rgb - u_SourceColor );
    float mix_factor = clamp ( ( u_Tolerance - overlap ) / u_Falloff, 0.0, 1.0 );
    vec4 newcolor = vec4 ( u_TargetColor, gl_FragColor.a );
    
    gl_FragColor = mix ( gl_FragColor, newcolor, mix_factor );
    gl_FragColor *= Color;
}
/*
float Source = 0.3;
vec3 Target = vec3( 1.0, 1.0, 0.5 );
 // 0.27 0.30 0.18
float u_Tolerance = 0.7;
float u_Falloff = 0.5;

vec3 rgb2hsv ( vec3 color )
{
    vec4 K = vec4 ( 0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0 );
    vec4 p = mix ( vec4 ( color.bg, K.wz ), vec4 ( color.gb, K.xy ), step ( color.b, color.g ) );
    vec4 q = mix ( vec4 ( p.xyw, color.r ), vec4 ( color.r, p.yzx ), step ( p.x, color.r ) );

    float d = q.x - min ( q.w, q.y );
    float e = 1.0e-10;
    return vec3 ( abs ( q.z + ( q.w - q.y ) / ( 6.0 * d + e ) ), d / ( q.x + e ), q.x );
}

vec3 hsv2rgb ( vec3 hsv )
{
    vec4 K = vec4 ( 1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0 );
    vec3 p = abs ( fract ( hsv.xxx + K.xyz ) * 6.0 - K.www );
    return hsv.z * mix ( K.xxx, clamp ( p - K.xxx, 0.0, 1.0 ), hsv.y );
}

void main ( )
{
    gl_FragColor = texture2D ( ColorMap, TexCoord );
    
    vec3 hsv = rgb2hsv ( gl_FragColor.rgb );
    float saturation = hsv.y;
    vec3 luminance = vec3 ( hsv.z );
    
    float overlap = abs ( hsv.x - Source );
    float mix_factor = clamp ( ( u_Tolerance - overlap ) / u_Falloff, 0.0, 1.0 );
    vec4 newcolor = vec4 ( mix ( luminance, Target * luminance, mix_factor ), gl_FragColor.a );
    
    gl_FragColor = mix ( gl_FragColor, newcolor, mix_factor );
    gl_FragColor *= Color;
}
*/
#endif
