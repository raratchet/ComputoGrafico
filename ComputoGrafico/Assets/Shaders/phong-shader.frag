#version 330

in vec2 TexCoord;
in vec3 FragPos;
out vec4 colour;
in mat3 TBN;	
in vec3 norm1;
uniform sampler2D mainTex;
uniform sampler2D rTex;
uniform sampler2D gTex;
uniform sampler2D bTex;
uniform sampler2D blendTexture;
uniform sampler2D normalMap;  

vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition )
{
	const vec3 myLightPosition = vec3( 0.0 , 0.0, -10.0 );
	const vec3 myLightAmbient = vec3( 0.42, 0.42, 0.42 );
	const vec3 myLightDiffuse = vec3( 1.0 , 1.0 , 1.0 );
	const vec3 myLightSpecular = vec3( 1.0 , 1.0 , 1.0 );
	const vec3 myMaterialAmbient = vec3( 0.5 , 0.5, 0.5 );
	const vec3 myMaterialDiffuse = vec3( 0.5 , 0.5, 0.5 );
	const vec3 myMaterialSpecular = vec3( 0.92, 0.92, 0.92 );
	const float myMaterialShininess = 0.01;
	//normal, light, view, and light reflection vectors
	vec3 norm = normalize( myNormal );
	vec3 lightv = normalize( myLightPosition - myPosition);
	vec3 viewv = normalize( vec3(0.,0.,0.) - myPosition );
	vec3 refl = reflect( vec3(0.,0.,0.) - lightv, norm );
	//ambient light computation
	vec3 ambient = myMaterialAmbient*myLightAmbient;
	//diffuse light computation
	vec3 diffuse = max(0.0, dot(lightv, norm)) * myMaterialDiffuse *myLightDiffuse;
	//Optionally you can add a diffuse attenuation term at this
	//point
	//specular light computation
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
	 specular = pow(max(0.0, dot(viewv,refl)), myMaterialShininess)*myMaterialSpecular*	myLightSpecular;
	}
	return clamp( ambient + diffuse + specular, 0.0, 1.0);
}

void main()
{

    vec3 Normal = texture(normalMap, TexCoord).rgb;
    Normal = normalize(Normal*2-1);  
	Normal = normalize(TBN * Normal); 

	vec4 finalColour = vec4(ADSLightModel(Normal,FragPos),1.0f);
	

	vec4 blendColor =  texture(blendTexture, TexCoord);
	float mainTexture = 1- (blendColor.r+blendColor.g+blendColor.b);
	vec4 mainTextureColor = texture(mainTex,TexCoord)*mainTexture;
	vec4 rTexColor = texture(rTex,TexCoord)*blendColor.r;
	vec4 gTexColor = texture(gTex,TexCoord)*blendColor.g;
	vec4 bTexColor = texture(bTex,TexCoord)*blendColor.b;

	vec4 finalTextureColor = mainTextureColor+rTexColor+gTexColor+bTexColor;
	colour =  finalTextureColor*finalColour;
}