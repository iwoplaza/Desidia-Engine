#include "GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../rendering/GLHelper.hpp"

GameObject::GameObject(string _name) {
	name = _name;
	location = Vector3();
	orientation = Quaternion();
	scale = Vector3();
	transform = glm::mat4();

	componentGroups = map<string, vector<Component*>>();
}

GameObject::~GameObject() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			delete component;
}

void GameObject::init() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->init();
}

void GameObject::postInit() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->postInit();
}

void GameObject::update() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->update();

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(location.x, location.y, location.z));
	transform = transform * glm::mat4(glm::toMat4(orientation));
}

void GameObject::draw() {
	GLHelper::saveState();
		GLHelper::transform(transform);
		for (pair<string, vector<Component*>> p : componentGroups){
			for (Component* component : p.second) {
				GLHelper::saveState();
					component->draw();
				GLHelper::loadState();
			}
		}
	GLHelper::loadState();
}

void GameObject::onMouseMove() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->onMouseMove();
}

GameObject* GameObject::addComponent(Component* _component) {
	if(componentGroups.find(_component->getType()) == componentGroups.end()) {
		componentGroups[_component->getType()] = vector<Component*>();
	}

	_component->setGameObject(this);
	componentGroups[_component->getType()].push_back(_component);
	return this;
}

GameObject* GameObject::markUpdatable() {
	needsUpdates = true;
	return this;
}

string GameObject::getName() {
	return name;
}

bool GameObject::doesNeedUpdates() {
	return needsUpdates;
}

Vector3 GameObject::getLocation() {
	return location;
}

Quaternion GameObject::getOrientation() {
	return orientation;
}

Vector3 GameObject::getScale() {
	return scale;
}

glm::mat4 GameObject::getTransform() {
	return transform;
}

Vector3 GameObject::getForwardVector() {
	glm::vec3 vector = glm::vec3(0, 0, -1);
	vector = glm::quat(orientation) * vector;
	Vector3 vec3 = Vector3(vector.x, vector.y, vector.z);
	return vec3;
}

Vector3 GameObject::getRightVector() {
	glm::vec3 vector = glm::vec3(-1, 0, 0);
	vector = glm::quat(orientation) * vector;
	Vector3 vec3 = Vector3(vector.x, vector.y, vector.z);
	return vec3;
}

vector<Component*> GameObject::getComponents(string groupName) {
	if (componentGroups.find(groupName) == componentGroups.end())
		return vector<Component*>();
	return componentGroups[groupName];
}

Component* GameObject::getComponent(string groupName, int index) {
	vector<Component*> group = getComponents(groupName);
	if (group.size() <= index) return nullptr;
	return group[index];
}

Component* GameObject::getComponent(string groupName) {
	return getComponent(groupName, 0);
}

void GameObject::setLocation(const Vector3& _location) {
	location = _location;
}

void GameObject::setOrientation(const Quaternion& _orientation) {
	orientation = _orientation;
}

void GameObject::setOrientation(const Vector3& _orientation) {
	orientation = Quaternion(_orientation);
}

void GameObject::rotate(const Vector3& r) {
	orientation = Quaternion(orientation * glm::dquat(glm::vec3(r.x, r.y, r.z)));
}

void GameObject::rotateX(float _x) {
	orientation = Quaternion(orientation * glm::dquat(glm::vec3(_x, 0, 0)));
}

void GameObject::rotateY(float _y) {
	orientation = Quaternion(orientation * glm::dquat(glm::vec3(0, _y, 0)));
}

void GameObject::rotateZ(float _z) {
	orientation = Quaternion(orientation * glm::dquat(glm::vec3(0, 0, _z)));
}

void GameObject::setScale(const Vector3& _scale) {
	scale = _scale;
}

ostream& operator<<(ostream& os, const GameObject& o) {
	os << "{ ";
	os << "name: '" << o.name << "', ";
	os << "location: " << o.location << ", ";
	os << "needsUpdate: " << o.needsUpdates;
	os << " }";
	return os;
}

GameObject* GameObject::parseJSON(const Value& value) {
	if (!value.HasMember("name")) {
		std::cerr << "[SceneLoader] Parser Error: GameObject's 'name' property is undefined." << std::endl;
		return nullptr;
	}
	GameObject* gameObject = new GameObject(value["name"].GetString());
	if (!value.HasMember("location")) {
		std::cerr << "[SceneLoader] Parser Error: GameObject's 'location' property is undefined." << std::endl;
		return nullptr;
	}
	const Value& locationNode = value["location"];
	gameObject->setLocation(Vector3(locationNode.GetArray()[0].GetFloat(), locationNode.GetArray()[1].GetFloat(), locationNode.GetArray()[2].GetFloat()));
	if (value.HasMember("needsUpdates")) {
		if (value["needsUpdates"].GetBool())
			gameObject->markUpdatable();
	}
	if (value.HasMember("components")) {
		const Value& componentsNode = value["components"];
		for (Value::ConstMemberIterator itr = componentsNode.MemberBegin(); itr != componentsNode.MemberEnd(); ++itr)
		{
			const Value& componentGroupNode = itr->value;
			for (auto& componentNode : componentGroupNode.GetArray()) {
				Component* component = Component::parseJSON(itr->name.GetString(), componentNode);
				if(component != nullptr)
					gameObject->addComponent(component);
			}
		}
	}
	cout << "Parsing a GameObject: " << *gameObject << endl;
	return gameObject;
}