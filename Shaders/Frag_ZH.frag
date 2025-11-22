#version 430

uniform vec3 color;

uniform bool lightSwitch = true;

vec2 textureCoord;

// pipeline-ból bejövő per-fragment attribútumok
in vec3 vs_out_pos;
in vec3 vs_out_norm;
in vec2 vs_out_tex;

// kimenő érték - a fragment színe
out vec4 fs_out_col;

// textúra mintavételező objektum
uniform sampler2D texImage;
uniform sampler2D textureShine;

uniform vec3 cameraPosition;

// fényforrás tulajdonságok 
vec4 lightPosition = vec4(0);

uniform vec3 La = vec3(0.1, 0.1, 0.1 );
uniform vec3 Ld = vec3(1.0, 1.0, 1.0 );
uniform vec3 Ls = vec3(1.0, 1.0, 1.0 );

uniform float lightConstantAttenuation	= 1.0;
uniform float lightLinearAttenuation	= 0.0;
uniform float lightQuadraticAttenuation	= 0.0;

// anyag tulajdonságok 

uniform vec3 Ka = vec3( 1.0 );
uniform vec3 Kd = vec3( 1.0 );
uniform vec3 Ks = vec3( 1.0 );

uniform float Shininess = 1.0;

uniform float indicatorFactor = 0.0;
uniform vec3 indicatorColor = vec3(1.0,0.0,1.0);
uniform bool isIndicatorLocal = false;
uniform vec2 indicatorUV = vec2(0.5,0.5);
uniform float indicatorR = 0.25;

/* segítség:  normalizálás:  http://www.opengl.org/sdk/docs/manglsl/xhtml/normalize.xml
	- skaláris szorzat:   http://www.opengl.org/sdk/docs/manglsl/xhtml/dot.xml
	- clamp: http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml
	- reflect: http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml
			 reflect(beérkező_vektor, normálvektor);  pow(alap, kitevő); 
*/

struct LightProperties
{
	vec4 pos;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct MaterialProperties
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

void main()
{
	fs_out_col = vec4(color, 1);

	/*
	textureCoord = vs_out_tex;
	fs_out_col = texture(texImage, textureCoord);
	}*/
}
