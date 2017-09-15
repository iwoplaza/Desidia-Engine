var Time = 0;

Engine.registerEventListener('update', function (e) {
    var location = GameObject.getLocation(e.gameObject);
    Time += Engine.Time.delta;
    location.x = Math.sin(Time * 4) * 0.5;
    location.z = Math.cos(Time * 4) * 0.5;
    GameObject.setLocation(e.gameObject, location);
});