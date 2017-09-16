Engine.registerEventListener('create', function (e) {
    e.metadata.time = 0;
    return e;
});

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);
    e.metadata.time += Engine.Time.delta;
    location.x = Math.sin(e.metadata.time * 4) * 0.5;
    location.z = Math.cos(e.metadata.time * 4) * 0.5;
    GameObject.setLocation(e.gameObject, location);
    return e;
});