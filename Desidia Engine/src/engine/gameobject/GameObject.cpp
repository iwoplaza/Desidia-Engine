#include "GameObject.hpp"
#include "../rendering/GLHelper.hpp"

GameObject::GameObject(string _name) {
	name = _name;
	location = Vector3();
	orientation = Quaternion();

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

void GameObject::update() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->update();
}

void GameObject::draw() {
	GLHelper::saveState();
		GLHelper::translate(location.x, location.y, location.z);
		GLHelper::rotate(orientation);
		for (pair<string, vector<Component*>> p : componentGroups){
			for (Component* component : p.second) {
				GLHelper::saveState();
					component->draw();
				GLHelper::loadState();
			}
		}
	GLHelper::loadState();
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

void GameObject::setLocation(const Vector3& _location) {
	location = _location;
}

Quaternion GameObject::getOrientation() {
	return orientation;
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