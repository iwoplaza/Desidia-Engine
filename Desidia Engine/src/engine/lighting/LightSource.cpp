#include "LightSource.hpp"
#include "../scene/Scene.hpp"

LightSource::LightSource(Vector3 _location, Color _color) {
	enable();
	m_location = _location;
	m_color = _color;
}

LightSource::LightSource() : LightSource(Vector3(), Color(1, 1, 1, 1)) {}

LightSource::~LightSource() {
	disable();
}

void LightSource::enable() {
	Scene* scene = Scene::current;
	scene->addLightSource(this);
}

void LightSource::disable() {
	Scene* scene = Scene::current;
	scene->removeLightSource(this);
}

Vector3 LightSource::getLocation() {
	return m_location;
}

Color LightSource::getColor() {
	return m_color;
}

void LightSource::setLocation(const Vector3& _location) {
	m_location = _location;
}

void LightSource::setColor(const Color& _color) {
	m_color = _color;
}