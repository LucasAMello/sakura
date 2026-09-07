shader_type canvas_item;
uniform vec4 room = vec4(3380.0, 820.0, 3880.0, 1100.0);
uniform bool outside = false;
varying vec2 world_position;
void vertex() {
    world_position = (MODEL_MATRIX * vec4(VERTEX, 0.0, 1.0)).xy;
}
void fragment() {
    bool inside = world_position.x >= room.x && world_position.y >= room.y && world_position.x < room.z && world_position.y < room.w;
    if (inside == outside) COLOR.a = 0.0;
}
