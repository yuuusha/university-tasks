#pragma once
#include "Matrix.h"
#include <cmath>

mat3 translate(float Tx, float Ty) {
	mat3* res = new mat3(1.f);
	(*res)[0][2] = Tx;
	(*res)[1][2] = Ty;
	return *res;
}

mat3 scale(float Sx, float Sy) {
	mat3* res = new mat3(1.f);
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy;
	return *res;
}

mat3 scale(float S) {
	return scale(S, S);
}

mat3 rotate(float t) {
	mat3* res = new mat3(1.f);
	(*res)[0][0] = (float)cos(t);
	(*res)[1][1] = (*res)[0][0];
	(*res)[0][1] = (float)sin(t);
	(*res)[1][0] = -(*res)[0][1];
	return *res;
}

mat3 mirrorX() {
	mat3* res = new mat3(1.f);
	(*res)[0][0] = -1;
	return *res;
}

mat3 mirrorY() {
	mat3* res = new mat3(1.f);
	(*res)[1][1] = -1;
	return *res;
}

mat4 translate(float Tx, float Ty, float Tz) {
	mat4* res = new mat4(1.f);
	(*res)[0][3] = Tx;
	(*res)[1][3] = Ty;
	(*res)[2][3] = Tz;
	return *res;
}

mat4 scale(float Sx, float Sy, float Sz) {
	mat4* res = new mat4(1.f);
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy;
	(*res)[2][2] = Sz;
	return *res;
}

mat4 rotate(float theta, vec3 n) {
	vec3 norm_n = norm(n);
	mat3 crossM_n = crossM(norm_n);
	mat3 crossM_n2 = crossM_n * crossM_n;
	mat3 Rodriges = mat3(1.f) + crossM_n * sin(theta);
	Rodriges = Rodriges + crossM_n2 * (1 - cos(theta));

	mat4 res = mat4(vec4(Rodriges[0], 0.f),
					vec4(Rodriges[1], 0.f),
					vec4(Rodriges[2], 0.f),
					vec4(0.f, 0.f, 0.f, 1.f));

	return res;
}

mat4 rotateP(float theta, vec3 n, vec3 P) {
	return translate(P.x, P.y, P.z) * (rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}

mat4 lookAt(vec3 S, vec3 P, vec3 u) {
	vec3 e3 = vec3(S - P) * (1 / length(S - P));
	vec3 e1 = cross(u, e3) * (1 / length(cross(u, e3)));
	vec3 e2 = cross(e3, e1) * (1 / length(cross(e3, e1)));

	mat4 R = mat4( vec4(e1, 0.f),
				   vec4(e2, 0.f),
				   vec4(e3, 0.f),
				   vec4(0.f, 0.f, 0.f, 1.f));

	mat4 T = translate(-S.x, -S.y, -S.z);

	return R * T;
}

mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
	return mat4(vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
		vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
		vec4(0.f, 0.f, -2 / (zf - zn), -(zf + zn) / (zf - zn)),
		vec4(0.f, 0.f, 0.f, 1.f));
}

mat4 frustum(float l, float r, float b, float t, float n, float f) {
	return mat4(vec4(2 * n / (r - l), 0, (r + l) / (r - l), 0),
		vec4(0, 2 * n / (t - b), (t + b) / (t - b), 0),
		vec4(0, 0, -(f + n) / (f - n), -2 * f * n / (f - n)),
		vec4(0, 0, -1, 0));
}

mat4 perspective(float fovy, float aspect, float n, float f) {
	return mat4( vec4( (1/aspect) * ( 1/tan(fovy/2) ), 0, 0, 0), 
				 vec4(0, 1/tan(fovy/2), 0, 0),
				 vec4(0, 0, -(f + n) / (f - n), -2 * f * n / (f - n)),
				 vec4(0, 0, -1, 0));
}

mat3 cadrRL(vec2 Vc, vec2 V, vec2 Wc, vec2 W) {
	return translate(Wc.x, Wc.y) * (scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}