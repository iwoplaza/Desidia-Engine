#include "ComponentLight.hpp"
#include "../GameObject.hpp"
#include "../../scene/Scene.hpp"
#include "../../lighting/LightSource.hpp"

ComponentLight::ComponentLight(Color _color) {
	m_color = _color;
}

void ComponentLight::init() {
	m_lightSource = new LightSource(m_gameObject->getTransform()->getLocation(), m_color);
	Scene::current->addLightSource(m_lightSource);
}

void ComponentLight::update() {
	m_lightSource->setLocation(m_gameObject->getTransform()->getLocation());
}

const char* ComponentLight::getType() {
	return "ComponentLight";
}

Component* ComponentLight::parseJSON(const Value& value) {
	if (!value.HasMember("color")) {
		cerr << "[SceneLoader] Necessary parameters weren't specified for a ComponentLight (color)." << endl;
		return nullptr;
	}

	const Value& colorNode = value["color"];
	Color color = Color();
	if(colorNode.GetArray().Capacity() == 4)
		color = Color(colorNode.GetArray()[0].GetFloat(), colorNode.GetArray()[1].GetFloat(), colorNode.GetArray()[2].GetFloat(), colorNode.GetArray()[3].GetFloat());
	else if (colorNode.GetArray().Capacity() == 3)
		color = Color(colorNode.GetArray()[0].GetFloat(), colorNode.GetArray()[1].GetFloat(), colorNode.GetArray()[2].GetFloat());

	Component* component = new ComponentLight(color);
	return component;
}