#include "GameObject.hpp"
#include "../rendering/GLHelper.hpp"

GameObject::GameObject(string _name) {
	name = _name;
	m_transform = Transform();

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

	m_transform.updateMatrix();
}

void GameObject::draw() {
	GLHelper::saveState();
		GLHelper::transform(m_transform.getMatrix());
		for (pair<string, vector<Component*>> p : componentGroups){
			for (Component* component : p.second) {
				GLHelper::saveState();
					component->draw();
				GLHelper::loadState();
			}
		}
	GLHelper::loadState();
}

void GameObject::reload() {
	for (pair<string, vector<Component*>> p : componentGroups)
		for (Component* component : p.second)
			component->reload();
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

string GameObject::getName() const {
	return name;
}

Transform* GameObject::getTransform() {
	return &m_transform;
}

bool GameObject::doesNeedUpdates() {
	return needsUpdates;
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

ostream& operator<<(ostream& os, const GameObject& o) {
	os << "{ ";
	os << "name: '" << o.name << "', ";
	os << "location: " << o.m_transform.getLocation() << ", ";
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
	gameObject->getTransform()->setLocation(Vector3(locationNode.GetArray()[0].GetFloat(), locationNode.GetArray()[1].GetFloat(), locationNode.GetArray()[2].GetFloat()));
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
	return gameObject;
}